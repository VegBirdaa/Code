#include<iostream>
#include<vector>
const int INF = INT_MAX;
using namespace std;

class node {
public:
	int num;
	int edge;
	node(int num, int edge) {
		this->num = num;
		this->edge = edge;
	}
};
void Dijkstra(vector<node>* adj, vector<int>& dis, vector<int>& path, vector<vector<int>> cost, vector<int>& cost_s, int s, int d);
void DFS(int, int, vector<int>&);
int main()
{
	int N, M, S, D;
	cin >> N >> M >> S >> D;
	vector<node>* adj = new vector<node>[N];
	vector<vector<int>> cost(N, vector<int>(N));
	
	for (int j = 0; j < M; j++)
	{
		int n, m, dis, co;
		cin >> n >> m >> dis >> co;
		adj[n].emplace_back(m,dis);
		adj[m].emplace_back(n, dis);
		cost[n][m] = cost[m][n] = co;
	}

	vector<int> path(N);

	vector<int> dis(N);
	
	vector<int> cost_s(N);

	Dijkstra(adj, dis, path, cost, cost_s, S, D);

	DFS(S, D, path);
	cout << D << " "<<dis[D]<<" "<<cost_s[D];
}

void Dijkstra(vector<node>* adj, vector<int>& dis, vector<int>& path, vector<vector<int>> cost,vector<int>& cost_s,int s,int d)
{
	int n = cost.size();
	vector<bool> vis(n);
	fill(vis.begin(), vis.end(), false);
	fill(dis.begin(), dis.end(), INF);
	for (int i = 0; i < adj[s].size(); i++)
		cost_s[adj[s][i].num] = cost[s][adj[s][i].num];
	cost_s[s] = 0;
	
	path[s] = s;
	dis[s] = 0;
	for(int k=0;k<n;k++)
	{
		int min = INF,index=-1;
		for(int i=0;i<n;i++)
			if (vis[i] == false && dis[i] < min)
			{
				index = i;
				min = dis[i];
			}
		vis[index] = true;
		for (int i = 0; i < adj[index].size(); i++)
		{
		
			int point = adj[index][i].num;
			int weight = adj[index][i].edge;
			if (vis[point] == false && dis[index] + weight < dis[point])
			{
				path[point] = index;
				dis[point] = dis[index] + weight;
				cost_s[point] = cost_s[index] + cost[index][point];
			}
			else if (vis[point] == false && dis[index] + weight == dis[point])
			{
				if (cost_s[point] > cost_s[index] + cost[index][point])
				{
					cost_s[point] = cost_s[index] + cost[index][point];
					path[point] = index;
				}
			}
		}
	}

}

void DFS(int s,int d, vector<int>& path) 
{
	if (d == s)
		return;
	DFS(s, path[d],path);
	cout << path[d] << " ";
}
