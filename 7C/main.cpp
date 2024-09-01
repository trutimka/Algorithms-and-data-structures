#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

template <typename ElementType>
class DSU;

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

  Graphs::Graph<Vertex, WeightType> BuildMinimalSpanningTree(DSU<VertexT>& dsu);

  Graph<VertexT> GetTransposedGraph() const;

 private:
  std::unordered_map<VertexT, std::vector<EdgeT>> adjacent_;
  size_t count_edges_;
};
}  // namespace Graphs

template <typename ElementType>
class DSU {
 public:
  DSU(const std::vector<ElementType>& elements);

  void Unite(const ElementType& first_element,
             const ElementType& second_element);

  bool IsInTheSameComponent(const ElementType& first_element,
                            const ElementType& second_element);

 private:
  ElementType& FindRoot(const ElementType& element);
  std::unordered_map<ElementType, ElementType> parents_;
  std::unordered_map<ElementType, size_t> rank_;
};

void SetFastStream();
Graphs::Graph<int, int> ReadGraph();
int SolutionUsingMinimalSpanningTree(Graphs::Graph<int, int>& graph);

int main() {
  SetFastStream();

  Graphs::Graph<int, int> graph = ReadGraph();
  std::cout << SolutionUsingMinimalSpanningTree(graph);
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
  std::cin >> count_vertex >> count_edges;

  std::vector<int> vertexes;
  std::vector<Graphs::Edge<int, int>> edges;
  for (int i = 1; i <= count_vertex; ++i) {
    vertexes.push_back(i);
  }

  for (int i = 0; i < count_edges; ++i) {
    size_t first;
    size_t second;
    int weight;
    std::cin >> first >> second >> weight;
    Graphs::Edge<int, int> edge_first(first, second, weight);
    edges.emplace_back(edge_first);
  }

  Graphs::Graph<int, int> graph(vertexes, edges);
  return graph;
}

int SolutionUsingMinimalSpanningTree(Graphs::Graph<int, int>& graph) {
  DSU dsu(graph.GetVertexes());
  auto mst = graph.BuildMinimalSpanningTree(dsu);
  auto edges = mst.GetEdges();
  int answer = 0;
  for (auto& edge : edges) {
    answer += edge.GetWeight();
  }
  return answer;
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
Graphs::Graph<Vertex, WeightType>
Graphs::Graph<Vertex, WeightType>::BuildMinimalSpanningTree(DSU<VertexT>& dsu) {
  int count = 0;
  auto edges = this->GetEdges();
  auto vertexes = this->GetVertexes();
  std::vector<Edge<Vertex, WeightType>> remaining_edges;

  sort(edges.begin(), edges.end(),
       [](Graphs::Edge<int, int> first, Graphs::Edge<int, int> second) -> bool {
         return first.GetWeight() < second.GetWeight();
       });

  for (auto& edge : edges) {
    if (!dsu.IsInTheSameComponent(edge.GetStart(), edge.GetTarget())) {
      dsu.Unite(edge.GetStart(), edge.GetTarget());
      ++count;
      remaining_edges.push_back(edge);
    }

    if (count == static_cast<int>(this->GetCountVertexes()) - 1) {
      break;
    }
  }
  return Graphs::Graph<Vertex, WeightType>(vertexes, remaining_edges);
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

template <typename ElementType>
ElementType& DSU<ElementType>::FindRoot(const ElementType& element) {
  if (parents_[element] != element) {
    parents_[element] = FindRoot(parents_[element]);
  }
  return parents_[element];
}

template <typename ElementType>
bool DSU<ElementType>::IsInTheSameComponent(const ElementType& first_element,
                                            const ElementType& second_element) {
  auto first_root = FindRoot(first_element);
  auto second_root = FindRoot(second_element);
  return first_root == second_root;
}

template <typename ElementType>
DSU<ElementType>::DSU(const std::vector<ElementType>& elements) {
  for (auto& element : elements) {
    parents_[element] = element;
    rank_[element] = 0;
  }
}

template <typename ElementType>
void DSU<ElementType>::Unite(const ElementType& first_element,
                             const ElementType& second_element) {
  auto first_root = FindRoot(first_element);
  auto second_root = FindRoot(second_element);

  if (first_root != second_root) {
    if (rank_[first_root] < rank_[second_root]) {
      parents_[first_root] = second_root;
    } else if (rank_[first_root] > rank_[second_root]) {
      parents_[second_root] = first_root;
    } else {
      parents_[second_root] = first_root;
      ++rank_[first_root];
    }
  }
}