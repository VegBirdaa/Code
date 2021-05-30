#include<iostream>
#include<vector>
#include<unordered_set>
#define INF (int)1e9
using namespace std;

class node {
public:
	int num;
	int weight;
	node()
	{
		num = weight = 0;
	}
	node(int n, int m)
	{
		num = n;
		weight = m;
	}
};

int dijkstra(int s,int d,vector<int> &path,vector<int> value_of_node,vector<node>* adj)
{
	int n = value_of_node.size();	
	vector<int> dis(n);
	vector<bool> vis(n);
	fill(path.begin(), path.end(), 0);
	
	fill(vis.begin(), vis.end(), false);
	fill(dis.begin(), dis.end(), INF);
	dis[s] = 0;
	path[s] = 1;
	vector<int> max_teams(n);
    max_teams[s]=value_of_node[s];
	for (int i = 0; i < n; i++)
	{
		int min = INF, index = -1;
		for(int j=0;j<n;j++)
			if (vis[j] == false && dis[j] < min)
			{
				min = dis[j];
				index = j;
			}

		vis[index] = true;
		
		for (int j = 0; j < adj[index].size(); j++)
		{
			int node = adj[index][j].num,w=adj[index][j].weight;
			if (vis[node] == false && dis[index] + w < dis[node])
			{
				dis[node] = dis[index] + w;
				path[node] = path[index];
                max_teams[node]=max_teams[index]+value_of_node[node];
				
			}
			else if (vis[node] == false && dis[index] + w == dis[node])
			{
				path[node] += path[index];
				if(max_teams[node]<max_teams[index]+value_of_node[node])
                    max_teams[node]=max_teams[index]+value_of_node[node];
			}
		}
		
	}
	return max_teams[d];
}
int main()
{
	int N, M, C1, C2;
	cin >> N >> M >> C1 >> C2;
	vector<int> value_of_node(N);
	vector<node>* adj = new vector<node>[N];
	for (int i = 0; i < N; i++)
		cin >> value_of_node[i];

	for (int i = 0; i < M; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		adj[a].emplace_back(b, c);
		adj[b].emplace_back(a, c);

	}
	
	vector<int> path(N);
	
	int ans =dijkstra(C1, C2, path,  value_of_node, adj);
	cout << path[C2] << " " << ans<<endl;
}
