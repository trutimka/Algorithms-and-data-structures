#include <algorithm>
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

  Graph<VertexT> GetTransposedGraph() const;

 private:
  std::unordered_map<VertexT, std::vector<EdgeT>> adjacent_;
  size_t count_edges_;
};
}  // namespace Graphs

template <class Graph>
class AbstractDijkstraVisitor {
 public:
  virtual void DiscoverVertex(const typename Graph::VertexT& vertex,
                              const typename Graph::WeightT& weight) = 0;
  ~AbstractDijkstraVisitor() = default;

 private:
  std::vector<typename Graph::VertexT> distances_;
  std::vector<typename Graph::VertexT> visited_;
};

template <class Graph>
class DijkstraVisitor : public AbstractDijkstraVisitor<Graph> {
 public:
  explicit DijkstraVisitor(size_t count_vertexes) {
    distances_.resize(count_vertexes, kStartDist);
  }
  void DiscoverVertex(const typename Graph::VertexT& vertex,
                      const typename Graph::WeightT& weight) override;

  void PrintDistances(const std::string& sep = " ") const;

  bool IsQueueEmpty() const { return queue_.empty(); }

  const typename Graph::WeightT& GetDistance(
      const typename Graph::VertexT& vertex) const {
    return distances_[vertex];
  }

  std::pair<typename Graph::VertexT, typename Graph::WeightT>
  GetAndPopTopEdge();

 private:
  const int kStartDist = 2009000999;
  std::vector<typename Graph::WeightT> distances_;
  std::priority_queue<
      std::pair<typename Graph::VertexT, typename Graph::WeightT>,
      std::vector<std::pair<typename Graph::VertexT, typename Graph::WeightT>>,
      std::greater<std::pair<typename Graph::VertexT, typename Graph::WeightT>>>
      queue_;
};

void SetFastStream();
int ReadEdges(std::vector<Graphs::Edge<int, int>>& edges);

template <class Graph, typename Vertex, class Visitor>
void Dijkstra(const Graph& graph, const Vertex& start, Visitor& visitor);

int main() {
  SetFastStream();

  int count_maps;
  std::cin >> count_maps;

  while (count_maps > 0) {
    --count_maps;

    std::vector<Graphs::Edge<int, int>> edges;
    int count_vertexes = ReadEdges(edges);
    std::vector<int> vertexes;
    for (int i = 1; i <= count_vertexes; ++i) {
      vertexes.push_back(i);
    }

    Graphs::Graph<int, int> graph(vertexes, edges);

    int start;
    std::cin >> start;
    DijkstraVisitor<Graphs::Graph<int, int>> visitor(count_vertexes);

    Dijkstra(graph, start, visitor);

    visitor.PrintDistances();
  }

  return 0;
}

void SetFastStream() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int ReadEdges(std::vector<Graphs::Edge<int, int>>& edges) {
  int count_vertex;
  int count_edges;
  std::cin >> count_vertex >> count_edges;

  for (int i = 0; i < count_edges; ++i) {
    size_t first;
    size_t second;
    int weight;
    std::cin >> first >> second >> weight;
    Graphs::Edge<int, int> edge_first(first, second, weight);
    Graphs::Edge<int, int> edge_second(second, first, weight);
    edges.emplace_back(edge_first);
    edges.emplace_back(edge_second);
  }

  return count_vertex;
}

template <class Graph, typename Vertex, class Visitor>
void Dijkstra(const Graph& graph, const Vertex& start, Visitor& visitor) {
  visitor.DiscoverVertex(start, 0);

  while (!visitor.IsQueueEmpty()) {
    auto pair = visitor.GetAndPopTopEdge();

    if (visitor.GetDistance(pair.first) < pair.second) {
      continue;
    }

    for (const auto& edge : graph.GetOutgoingEdges(pair.first)) {
      int new_dist = pair.second + edge.GetWeight();
      if (visitor.GetDistance(edge.GetTarget()) > new_dist) {
        visitor.DiscoverVertex(edge.GetTarget(), new_dist);
      }
    }
  }
}

template <class Graph>
std::pair<typename Graph::VertexT, typename Graph::WeightT>
DijkstraVisitor<Graph>::GetAndPopTopEdge() {
  auto pair = queue_.top();
  queue_.pop();
  return pair;
}

template <class Graph>
void DijkstraVisitor<Graph>::DiscoverVertex(
    const typename Graph::VertexT& vertex,
    const typename Graph::WeightT& weight) {
  distances_[vertex] = weight;
  queue_.push({vertex, weight});
}

template <class Graph>
void DijkstraVisitor<Graph>::PrintDistances(const std::string& sep) const {
  for (auto& dist : distances_) {
    std::cout << dist << sep;
  }
  std::cout << '\n';
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