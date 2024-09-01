#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <queue>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Graphs {
template <class Vertex, typename WeightType>
class Edge {
 public:
  Edge(const Vertex& from, const Vertex& to,
       const WeightType& weight = WeightType())
      : from_(from), to_(to), weight_(weight) {}

  const Vertex& GetStart() const { return from_; }
  const Vertex& GetTarget() const { return to_; }
  const WeightType& GetWeight() const { return weight_; };
  void SetWeight(const WeightType& weight) { weight_ = weight; };

 private:
  Vertex from_;
  Vertex to_;
  WeightType weight_;
};

template <typename Vertex = int, typename WeightType = int>
class Graph {
 public:
  using VertexT = Vertex;
  using EdgeT = Edge<VertexT, WeightType>;
  using WeightT = WeightType;

  Graph(const std::vector<VertexT>& vertexes, const std::vector<EdgeT>& edges);

  const std::vector<EdgeT>& GetOutgoingEdges(const VertexT& vertex) const {
    return adjacent_.at(vertex);
  }

  std::vector<VertexT> GetVertexes() const;

  size_t GetCountVertexes() const { return adjacent_.size(); }

  size_t GetCountEdges() const { return count_edges_; }

  std::vector<EdgeT> GetEdges() const;

  Graph<VertexT> GetTransposedGraph() const;

 private:
  std::unordered_map<VertexT, std::vector<EdgeT>> adjacent_;
  size_t count_edges_;
};
}  // namespace Graphs

template <typename T>
class SparseTable {
 public:
  explicit SparseTable(const std::vector<T>& array);

  T GetMinimalElementOnRange(int left, int right);

 private:
  std::vector<std::vector<T>> table_;
  std::vector<T> array_;
};

void SetFastStream();
Graphs::Graph<int, int> ReadGraph();

enum class Colors {
  KWhite = 0,
  KGray,
  KBlack,
};

template <class Graph, class Visitor>
void DFS(Graph& graph, const typename Graph::VertexT& vertex, Visitor& visitor);

template <class Graph>
class AbstractDFSVisitor {
 public:
  virtual void DiscoverVertex(const Graph::VertexT& vertex) = 0;
  virtual void FinishVertex(const Graph::VertexT& vertex) = 0;
  virtual Colors GetColor(const Graph::VertexT& vertex) = 0;
  virtual ~AbstractDFSVisitor() = default;

 protected:
  std::unordered_map<typename Graph::VertexT, Colors> colors_;
};

template <class Graph>
class OrderDFSVisitor : public AbstractDFSVisitor<Graph> {
 public:
  void DiscoverVertex(const Graph::VertexT& vertex) final;

  void ReturnToVertex(const Graph::VertexT& vertex);

  void FinishVertex(const Graph::VertexT& vertex) final;

  Colors GetColor(const Graph::VertexT& vertex) final;

  std::pair<int, int> GetLeftAndRightBorders(
      const typename Graph::VertexT& first_vertex,
      const typename Graph::VertexT& second_vertex) const;

  const std::vector<int>& GetOrder() const { return order_; }

  int GetHeightForVertex(const typename Graph::VertexT& vertex) const {
    return heights_.at(vertex);
  }

  virtual ~OrderDFSVisitor() = default;

 private:
  using BaseClass = AbstractDFSVisitor<Graph>;
  int height_ = 0;
  std::vector<int> order_;
  std::unordered_map<typename Graph::VertexT, int> first_in_;
  std::unordered_map<typename Graph::VertexT, int> heights_;
};

template <class Visitor>
void WriteAnswersForQueries(const Visitor& visitor);

int main() {
  SetFastStream();

  Graphs::Graph<int, int> graph = ReadGraph();
  OrderDFSVisitor<Graphs::Graph<int, int>> visitor;
  DFS(graph, 0, visitor);

  WriteAnswersForQueries<OrderDFSVisitor<Graphs::Graph<int, int>>>(visitor);

  return 0;
}

void SetFastStream() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

Graphs::Graph<int, int> ReadGraph() {
  int count_vertex;
  int count_edges;
  std::cin >> count_vertex;
  count_edges = count_vertex - 1;

  std::vector<int> vertexes;
  std::vector<Graphs::Edge<int, int>> edges;
  for (int i = 0; i < count_vertex; ++i) {
    vertexes.push_back(i);
  }

  for (int i = 0; i < count_edges; ++i) {
    size_t first;
    size_t second;
    std::cin >> first >> second;
    --first;
    --second;
    Graphs::Edge<int, int> edge_first(first, second);
    Graphs::Edge<int, int> edge_second(second, first);
    edges.emplace_back(edge_first);
    edges.emplace_back(edge_second);
  }

  Graphs::Graph<int, int> graph(vertexes, edges);
  return graph;
}

template <class Graph, class Visitor>
void DFS(Graph& graph, const typename Graph::VertexT& vertex,
         Visitor& visitor) {
  visitor.DiscoverVertex(vertex);

  for (const auto& outgoing_edge : graph.GetOutgoingEdges(vertex)) {
    const auto& neighbour = outgoing_edge.GetTarget();
    if (visitor.GetColor(neighbour) == Colors::KWhite) {
      DFS(graph, neighbour, visitor);
      visitor.ReturnToVertex(vertex);
    }
  }

  visitor.FinishVertex(vertex);
}

template <typename Vertex, typename WeightType>
Graphs::Graph<Vertex, WeightType>::Graph(const std::vector<VertexT>& vertexes,
                                         const std::vector<EdgeT>& edges) {
  count_edges_ = edges.size();
  for (const auto& vertex : vertexes) {
    adjacent_[vertex];
  }
  for (const auto& edge : edges) {
    adjacent_[edge.GetStart()].push_back(edge);
  }
}

template <typename Vertex, typename WeightType>
std::vector<Vertex> Graphs::Graph<Vertex, WeightType>::GetVertexes() const {
  std::vector<VertexT> vertexes;
  for (auto& key_value_pair : adjacent_) {
    vertexes.push_back(key_value_pair.first);
  }
  return vertexes;
}

template <typename Vertex, typename WeightType>
std::vector<typename Graphs::Graph<Vertex, WeightType>::EdgeT>
Graphs::Graph<Vertex, WeightType>::GetEdges() const {
  std::vector<typename Graphs::Graph<Vertex, WeightType>::EdgeT> edges;
  for (auto& key_value_pair : adjacent_) {
    for (auto& to : adjacent_.at(key_value_pair.first)) {
      edges.push_back(to);
    }
  }

  return edges;
}

template <typename Vertex, typename WeightType>
Graphs::Graph<Vertex> Graphs::Graph<Vertex, WeightType>::GetTransposedGraph()
    const {
  std::vector<EdgeT> new_edges;
  for (const auto& key_value_pair : adjacent_) {
    for (const auto& edge : adjacent_[key_value_pair.first]) {
      EdgeT new_edge(edge.GetTarget(), key_value_pair);
      new_edges.emplace_back(new_edge);
    }
  }

  return new_edges;
}

template <typename T>
SparseTable<T>::SparseTable(const std::vector<T>& array) : array_(array) {
  int size = static_cast<int>(array.size());
  int log_size = static_cast<int>(log2(array.size())) + 1;
  table_ = std::vector<std::vector<T>>(
      array.size() * 2,
      std::vector<T>(log_size, std::numeric_limits<T>::max()));

  for (int i = 0; i < size; ++i) {
    table_[i][0] = i;
  }
  for (int j = 1; (1 << j) <= size; ++j) {
    for (int i = 0; (i + (1 << j) - 1) < size; ++i) {
      auto prev1 = table_[i][j - 1];
      auto prev2 = table_[i + (1 << (j - 1))][j - 1];
      if (array_[prev1] < array_[prev2]) {
        table_[i][j] = prev1;
      } else {
        table_[i][j] = prev2;
      }
    }
  }
}

template <typename T>
T SparseTable<T>::GetMinimalElementOnRange(int left, int right) {
  int pos = static_cast<int>(log2(right - left + 1));
  auto prev1 = table_[left][pos];
  auto prev2 = table_[right - (1 << pos) + 1][pos];
  return std::min(array_[prev1], array_[prev2]);
}

template <class Visitor>
void WriteAnswersForQueries(const Visitor& visitor) {
  SparseTable<int> table(visitor.GetOrder());

  int count_requests;
  std::cin >> count_requests;

  for (int i = 0; i < count_requests; ++i) {
    int first_vertex;
    int second_vertex;
    std::cin >> first_vertex >> second_vertex;
    --first_vertex;
    --second_vertex;
    auto borders = visitor.GetLeftAndRightBorders(first_vertex, second_vertex);
    int height_root =
        table.GetMinimalElementOnRange(borders.first, borders.second);
    std::cout << -2 * height_root + visitor.GetHeightForVertex(first_vertex) +
                     visitor.GetHeightForVertex(second_vertex)
              << '\n';
  }
}

template <class Graph>
void OrderDFSVisitor<Graph>::DiscoverVertex(const Graph::VertexT& vertex) {
  BaseClass::colors_[vertex] = Colors::KGray;
  order_.push_back(height_);
  heights_[vertex] = height_;
  ++height_;
  first_in_[vertex] = order_.size() - 1;
}

template <class Graph>
void OrderDFSVisitor<Graph>::ReturnToVertex(const Graph::VertexT& vertex) {
  order_.push_back(heights_[vertex]);
}

template <class Graph>
void OrderDFSVisitor<Graph>::FinishVertex(const Graph::VertexT& vertex) {
  BaseClass::colors_[vertex] = Colors::KBlack;
  --height_;
}

template <class Graph>
Colors OrderDFSVisitor<Graph>::GetColor(const Graph::VertexT& vertex) {
  if (BaseClass::colors_.contains(vertex)) {
    return BaseClass::colors_[vertex];
  }
  return Colors::KWhite;
}

template <class Graph>
std::pair<int, int> OrderDFSVisitor<Graph>::GetLeftAndRightBorders(
    const typename Graph::VertexT& first_vertex,
    const typename Graph::VertexT& second_vertex) const {
  std::pair<int, int> borders;
  borders.first =
      std::min(first_in_.at(first_vertex), first_in_.at(second_vertex));
  borders.second =
      std::max(first_in_.at(first_vertex), first_in_.at(second_vertex));
  return borders;
}