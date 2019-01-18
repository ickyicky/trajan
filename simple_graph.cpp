#ifndef ICKY_SIMPLE_GRAPH
#define ICKY_SIMPLE_GRAPH

#include "simple_graph.h"

namespace icky
{
//Vertex
SimpleGraph::Vertex::Vertex(int &number): number(number), excluded(false), tarjan_numb(0)
{}

bool SimpleGraph::Vertex::is_connected(Vertex &v)
{
	bool found = false;
	for(auto vv: connected)
		if(vv == v.number)
		{
			found = true;
			break;
		}
	return found;
}

void SimpleGraph::Vertex::connect(int i)
{
	connected.push_back(i);
}

inline bool SimpleGraph::Vertex::operator==(const Vertex& y)
{
        return (number == y.number);
    }

inline bool SimpleGraph::Vertex::operator!=(const Vertex& y)
{
        return !(number == y.number);
    }

//SimpleGraph
void SimpleGraph::connect(int first_i, int second_i)
{
	if(first_i > vertexes.size() || second_i > vertexes.size())
		throw "Invalid edge indexes!";

	auto &first = vertexes[first_i];
	auto &second = vertexes[second_i];
	if(!first.is_connected(second))
	{
		first.connect(second.number);
		second.connect(first.number);
	}
}

void SimpleGraph::clear_values()
{
	for(auto &each: vertexes)
		each.tarjan_numb = 0;
}

void SimpleGraph::tarjan_algorithm(Vertex &v, IntVector &found, Vertex &parent, int current_number = 1)
{
	int low = current_number;
	v.tarjan_numb = current_number++;
	int children = 0;
	bool is_alriculation = false;

	for(auto &vc_i: v.connected)
	{
		auto &vc = vertexes[vc_i];
		if(vc.excluded || vc == parent)
			continue;

		int number;
		if(vc.tarjan_numb == 0)//this means, it wasn't visited yet
		{
			tarjan_algorithm(vc, found, v, current_number);
			number = vc.tarjan_numb;
			if(number >= low)
				is_alriculation = true;
			children++;
		}
		else
			number = vc.tarjan_numb;

		if(number < low)
			low = number;
	}

	if(is_alriculation && (parent != v || children >= 2))
		found.push_back(v.number);

	v.tarjan_numb = low;
}

SimpleGraph::SimpleGraph(int v_number, PairVector &edges)
{
	for(int i = 0; i < v_number; i++)
		vertexes.push_back(Vertex(i));

	for(auto &u: edges)
		connect(u.first, u.second);
}

SimpleGraph::~SimpleGraph()
{	}

SimpleGraph::Set SimpleGraph::get_wide_bridges()
{
	Set bridges;
	IntVector found;
	for(auto &v: vertexes)
	{
		found.clear();
		clear_values();
		v.excluded = true;
		auto &vx = vertexes[(v.number+1)%vertexes.size()];
		tarjan_algorithm(vx, found, vx);

		for(auto any: vertexes)
			if(!any.excluded && any.tarjan_numb == 0)	//so if it wasnt visited, the graph was already inconsistend witout v, all edges
			{
				found = v.connected;
				break;
			}//if it was not visited

		for(auto vv_i: found)						//now we have a situation, that every edge connected to v and vv is an wide bridge,
		{
			auto &vv = vertexes[vv_i];
			if(v.is_connected(vv))				//so if vv is connected to v, vv and v gives us the wide bridge
			{
				for(auto vv_c_i: vv.connected)				//but only if vv wasn't leaf connected to v
				{
					auto &vv_c = vertexes[vv_c_i];
					if(!vv_c.excluded)								//so it is connected with any of not excluded vertexes
					{
						if(vv.number > v.number)			//simple if, so we dont have reapeating edges
							bridges.insert(Pair{v.number, vv.number});
						else
							bridges.insert(Pair{vv.number, v.number});
						break;
					}//if not excluded
				}//for vv_c connected with vv
			}//if vv is connected to v
		}//for vv in found

		v.excluded = false;
	}//for v in vertexes

return bridges;
}

}

#endif
