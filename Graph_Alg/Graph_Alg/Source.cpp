#include<iostream>
#include<stack>
#include<queue>
#include<list>
#include<map>
#include<algorithm>
#include<set>
#include <fstream>
#include <ctime>
#include <string>

using namespace std;

# define INF 0x3f3f3f3f
 
struct Graph{
private:
	int V,E;
	string cheakTypeOfGraph()
	{
		//<Disconected Graph> OR <No.Edge Close to V>
		if( E<=V || ((pow(V,2.0)-E) > V - E))
			return "Sparse";
		else
			return "Dense";
	}
public:
	
	map<int,vector< pair<int, int> > > DicVertix;
	Graph()
	{
			
	}
	Graph(char *PathFile){
		E = 0;V = 0;

		FILE *fp;
		int u,v,w;
		
		fp = freopen(PathFile, "r" ,stdin);
		while( !feof(fp) )
		{ 
			fscanf(fp,"%u%u%u",&u,&v,&w);
			addEdge(u,v,w);
			E++;
		}
		fclose(fp);		
		cout<<"File : "<<PathFile<<" Loaded !!"<<endl;

		
		V = DicVertix.size();
		cout<<"No. of Vertics :: "<<V<<" ,No. of Edges :: "<<E-1<<" ,Type :: "<<cheakTypeOfGraph()<<" Graph .."<<endl;
		cout<<endl;
	}

	void addEdge(int u, int v, int w){	
		if(DicVertix.find(u) == DicVertix.end())
			DicVertix[u].push_back(make_pair(u, 0));//Add vertix A to A with Weight 0
				
		if(DicVertix.find(v) == DicVertix.end())
			DicVertix[v].push_back(make_pair(v, 0));//Add vertix A to A with Weight 0
		
		DicVertix[u].push_back(make_pair(v, w));
	  //DicVertix[v].push_back(make_pair(u, w));for Undirectd
	}
    



	void print_SPSP(map<int,int> dist,int src) {
		cout<<"Vertex Distance from Source: "<<src<<endl;
		for (map<int, int>::const_iterator itr = dist.begin(); itr != dist.end(); itr++){
		if(itr->second != INF)	
			cout << "Vertex: " << itr->first << "Distance: "<< itr->second << endl;
		else
			cout << "Vertex: " << itr->first << "Distance: INF"<< endl;
		}
	}	
	void print_APSP(map<int ,map<int ,int>> dist)
	{
		for (map<int ,map<int ,int>>::const_iterator itr = dist.begin(); itr != dist.end(); itr++){			
			cout << "Vertex: " << itr->first ;
			for (map<int ,int>::const_iterator itrRow = (itr->second).begin(); itrRow != (itr->second).end(); itrRow++){
				if(itrRow->second != INF)
					//cout<<" D("<<itrRow->first<<","<<itrRow->second<<")  ";
  					cout<<" "<<itrRow->second<<" ";
				else
					cout<<" INF ";
			}
			cout<<endl;
		}
	}
};
class GraphDijkstra
{
public:
	 map<int,int> shortestPath(Graph g, int src){
			
		 map<int,int> dist; //Store [Vector/ShortestPath]
		 for (std::pair<const int,vector< pair<int, int>>>& p: g.DicVertix) 
			 dist[p.first]= INF;

		dist[src] = 0;
		
		set< pair<int, int> > setds;		
		setds.insert(make_pair(0, src));
		
		while (!setds.empty())
		{
			pair<int, int> tmp = *(setds.begin());
		    setds.erase(setds.begin());
 
			int u = tmp.second;
			for(int VecIndx = 0; VecIndx < g.DicVertix[u].size() ; VecIndx++)//for (itr = g.DicVertix[u].begin(); itr != g.DicVertix[u].end(); ++itr)			
			{
					int v = (g.DicVertix[u])[VecIndx].first; //(*itr).first;
					int weight = (g.DicVertix[u])[VecIndx].second; //(*itr).second;
			
				if (dist[v] > dist[u] + weight)
		        {
		            if (dist[v] != INF)
		                setds.erase(setds.find(make_pair(dist[v], v)));
 
					dist[v] = dist[u] + weight;
		            setds.insert(make_pair(dist[v], v));
		        }
		    }
		} 
		return dist;
	}
	 
};
class GraphBellman_Ford{
public:	
	map<int,int> shortestPath(Graph g, int src){
		
		map<int,int> dist;
		
		for (std::pair<const int,vector< pair<int, int>>>& p: g.DicVertix) {
			dist[p.first]= INF;
		}

		dist[src] = 0;
		
		map<int,vector< pair<int, int> > >::iterator indexOf_VwithAllE;
		for (int j = 0; j < g.DicVertix.size() - 1; j++)
			for ( indexOf_VwithAllE  = g.DicVertix.begin();indexOf_VwithAllE != g.DicVertix.end(); ++indexOf_VwithAllE){
				int u = indexOf_VwithAllE->first;
				for(int VecIndx = 0; VecIndx < g.DicVertix[u].size() ; VecIndx++)//for (itr = g.DicVertix[u].begin(); itr != g.DicVertix[u].end(); ++itr)
				{
					
					int v = (g.DicVertix[u])[VecIndx].first; //(*itr).first;
					int weight = (g.DicVertix[u])[VecIndx].second; //(*itr).second;
				    
					if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
				        dist[v] = dist[u] + weight;
				}
			}


		for (map<int,vector< pair<int, int> > >::const_iterator indexOf_VwithAllE  = g.DicVertix.begin();indexOf_VwithAllE != g.DicVertix.end(); ++indexOf_VwithAllE){
				int u = indexOf_VwithAllE->first;
				for(int VecIndx = 0; VecIndx < g.DicVertix[u].size() ; VecIndx++)//for (itr = g.DicVertix[u].begin(); itr != g.DicVertix[u].end(); ++itr)
				{
					int v = (g.DicVertix[u])[VecIndx].first; //(*itr).first;
					int weight = (g.DicVertix[u])[VecIndx].second; //(*itr).second;
				    
					if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
				        printf("Graph contains negative weight cycle");
				}
			}
	   
		return dist;
	}

};
class GraphFloyd_Warsall{
public:
	map<int ,map<int ,int>> shortestPath (Graph g)
	{
		map<int ,map<int ,int>> _dist;
		
		for (std::pair<const int,vector< pair<int, int>>>& p: g.DicVertix) 
			for (std::pair<const int,vector< pair<int, int>>>& q: g.DicVertix) 
				_dist[p.first][q.first]= INF;
		
		/* Initialize the solution matrix same as input graph matrix. Or 
	       we can say the initial values of shortest distances are based
	       on shortest paths considering no intermediate vertex. */

		for (map<int,vector< pair<int, int> > >::const_iterator indexOf_VwithAllE  = g.DicVertix.begin();indexOf_VwithAllE != g.DicVertix.end(); ++indexOf_VwithAllE){
			int u = indexOf_VwithAllE->first;
            for(int VecIndx = 0; VecIndx < g.DicVertix[u].size() ; VecIndx++)//for (itr = g.DicVertix[u].begin(); itr != g.DicVertix[u].end(); ++itr)
			{
					int v = (g.DicVertix[u])[VecIndx].first; //(*itr).first;
					int weight = (g.DicVertix[u])[VecIndx].second; //(*itr).second;	
				
					_dist[u][v] = weight;
            }
		}

				
		for (int k = 0; k < g.DicVertix.size(); k++)
			for (int i = 0; i < g.DicVertix.size(); i++)	        
				for (int j = 0; j < g.DicVertix.size(); j++)
	            {
	                // If vertex k is on the shortest path from
	                // i to j, then update the value of dist[i][j]
	                if (_dist[i][k] + _dist[k][j] < _dist[i][j])
	                    _dist[i][j] = _dist[i][k] + _dist[k][j];
	            }

				
		return _dist;
	}
	
};
class GraphJohnson{
private:
	Graph addExtraSource(Graph g){
		for (map<int,vector< pair<int, int> > >::const_iterator itrForV  = g.DicVertix.begin();itrForV != g.DicVertix.end(); ++itrForV)
			g.addEdge(-1,itrForV->first,0);		
		return g;
	}
	Graph delExtraSource(Graph g){
		g.DicVertix.erase (g.DicVertix.find (-1));   
		return g;
	}
	Graph reWeightEdges(Graph g){
		//By w(u, v) + h[u] – h[v]. Eq with h[]from Bellmanford
		
		Graph New_g;
		GraphBellman_Ford graph;
		map<int,int> h = graph.shortestPath(g,-1);

		//Reweight
		for (map<int,vector< pair<int, int> > >::const_iterator U  = g.DicVertix.begin();U != g.DicVertix.end(); ++U){
				int u = U->first;
				for(int VecIndx = 0; VecIndx < g.DicVertix[u].size() ; VecIndx++)//for (itr = g.DicVertix[u].begin(); itr != g.DicVertix[u].end(); ++itr)
				{
					int v = (g.DicVertix[u])[VecIndx].first; //(*itr).first;
					
					//By NewW = w(u, v) + h[u] – h[v]
					(g.DicVertix[u])[VecIndx].second = (g.DicVertix[u])[VecIndx].second + h[u] - h[v];
				}
			}
		return g;
	}
public :
	map<int ,map<int ,int>> shortestPath (Graph g)
	{
		Graph newGraph = delExtraSource(
			reWeightEdges(addExtraSource(g)));

		map<int ,map<int ,int>> _dist;		
		for (std::pair<const int,vector< pair<int, int>>>& p: newGraph.DicVertix) 
			for (std::pair<const int,vector< pair<int, int>>>& q: newGraph.DicVertix) 
				_dist[p.first][q.first]= INF;

				
		GraphDijkstra Dij_SP;
		for (std::pair<const int,vector< pair<int, int>>>& p: newGraph.DicVertix) {
			map<int,int> h = Dij_SP.shortestPath(newGraph,p.first);
			for (std::pair<const int,vector< pair<int, int>>>& q: newGraph.DicVertix) 
				_dist[p.first][q.first]= h[q.first];
		}

		return _dist;
	}
};

int main()
{
	
	/*
	info_g.addEdge(0, 1, -2);
	info_g.addEdge(1, 2, -1);
	info_g.addEdge(2, 0, 4);
	info_g.addEdge(2, 3, 2);
	info_g.addEdge(2, 4, -3);
	info_g.addEdge(5, 3, 1);
	info_g.addEdge(5, 4, -4);*/
	
	/*
	info_g.print_APSP( Johnson_g.shortestPath(info_g));
	cout<<endl;
	cout<<endl;
	cout<<endl;
	
	cout<<"Floyd : "<<endl;
	
	info_g.print_APSP( Floyd_g.shortestPath(info_g));
	cout<<endl;
	cout<<endl;
	cout<<endl;


	cout<<"Dijkstra : "<<endl;
	GraphDijkstra Dijkstra_g;
	info_g.print_SPSP( 	Dijkstra_g.shortestPath(info_g,0),0);
	cout<<endl;
	cout<<endl;
	cout<<endl;

	cout<<"Bellman : "<<endl;
	GraphBellman_Ford Bellman_Ford_g;
	info_g.print_SPSP( Bellman_Ford_g.shortestPath(info_g,0),0);
	

	

	//FloydWarsall
	/*Graph info_g;
	info_g.addEdge(0, 3, 10);
    info_g.addEdge(0, 1, 5);
    info_g.addEdge(1, 2, 3);
    info_g.addEdge(2, 3, 1);
	GraphFloyd_Warsall g;
	g.shortestPath(info_g);*/

	//---------------------------------
	//Dijkstra Alg
	/*Graph info_g;
	info_g.addEdge(0, 1, 4);
    info_g.addEdge(0, 7, 8);
    info_g.addEdge(1, 2, 8);
    info_g.addEdge(1, 7, 11);
    info_g.addEdge(2, 3, 7);
    info_g.addEdge(2, 8, 2);
    info_g.addEdge(2, 5, 4);
    info_g.addEdge(3, 4, 9);
    info_g.addEdge(3, 5, 14);
    info_g.addEdge(4, 5, 10);
    info_g.addEdge(5, 6, 2);
    info_g.addEdge(6, 7, 1);
    info_g.addEdge(6, 8, 6);
    info_g.addEdge(7, 8, 7);
	GraphDijkstra g;
	g.shortestPath(info_g,0);*/

	//---------------------------------
	//BellmanFord Alg
	/*Graph info_g;
	info_g.addEdge(0,1,-1);
	info_g.addEdge(0,2,4);
	info_g.addEdge(1,2,3);
	info_g.addEdge(1,3,2);
	info_g.addEdge(1,4,2);
	info_g.addEdge(3,2,5);
	info_g.addEdge(3,1,1);
	info_g.addEdge(4,3,-3);
	GraphBellman_Ford g;
	g.shortestPath(info_g,0);
	*/
	system
		("pause");
    return 0;
}