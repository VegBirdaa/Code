#include<iostream>
#include<vector>
using namespace std;
const int n = 6;
bool vis[n] = { false };
int G1[n][n];  //use adjacency matrix to save the graph 
vector<int> G2[n]; //use adjacency table to save the graph

void dfs1(int, int);
void dfsTrave();
int main() 
{
	//initial the graph
	G1[0][1] = G1[0][2] = 1;
	G1[1][3] = G1[1][4] = 1;
	G1[2][1] = G1[2][4] = 1;
	G1[4][3] = G1[4][5] = 1;
	G1[5][3] = 1;


	G2[0].push_back(1);G2[0].push_back(2);
	G2[1].push_back(3); G2[1].push_back(4);
	G2[2].push_back(1); G2[2].push_back(4);
	G2[4].push_back(3); G2[4].push_back(5);
	G2[5].push_back(3);
	dfsTrave();
}

void dfs1(int u, int depth) //u is the number of  the node that we want to visit
{
	vis[u] = true;
	cout << u<<" ";
	for (int i = 0; i < n; i++)
		if (G1[u][i] == 1 && vis[i] == false)
			dfs1(i, depth + 1);
}
void dfs2(int u, int depth)
{
	vis[u] = true;
	cout << u << " ";
	for (int i = 0; i < G2[i].size(); i++)
		if (vis[i] == false)
			dfs2(i, depth + 1);
}
//travel the graph
void dfsTrave()
{
	for (int i = 0; i < n; i++)
		if (vis[i] == false)
			dfs1(i, 1);  //dfs2(i,1)
}

