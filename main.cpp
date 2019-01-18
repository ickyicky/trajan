#include "simple_graph.h"
#include <iostream>
using namespace std;
using namespace icky;

int main()
{
	int n,a,b;
	cin>>n;
	vector<pair<int,int>> vectora;

	while(cin>>a>>b)
		vectora.push_back(pair<int,int>{a,b});

	auto graph = SimpleGraph(n, vectora);

	for(auto &xx: graph.get_wide_bridges())
		cout<<xx.first<<"-"<<xx.second<<endl;
	return 0;
}
