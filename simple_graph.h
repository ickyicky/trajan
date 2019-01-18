#ifndef ICKY_SIMPLE_GRAPH_H
#define ICKY_SIMPLE_GRAPH_H

#include <utility>
#include <vector>
#include <set>
#include <initializer_list>
#include <iostream>

namespace icky
{

class SimpleGraph
{
private:
  using IntVector = std::vector<int>;
	using Pair = std::pair<int,int>;
	using Set = std::set<Pair>;
	using PairVector = std::vector<Pair>;

  class Vertex
  {
    int number;
    bool excluded;
    int tarjan_numb;
    IntVector connected;
    friend class SimpleGraph;

    Vertex(int&);
    bool is_connected(Vertex&);
    void connect(int);
    inline bool operator==(const Vertex&);
    inline bool operator!=(const Vertex&);
  };

  using VertexVector = std::vector<Vertex>;
  VertexVector vertexes;

  void connect(int, int);
  void clear_values();
  void tarjan_algorithm(Vertex&, IntVector&, Vertex&, int);

public:
  SimpleGraph(int, PairVector&);
  ~SimpleGraph();
  Set get_wide_bridges();
};


}

#endif
