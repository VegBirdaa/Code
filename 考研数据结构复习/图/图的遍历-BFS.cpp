#include<iostream>
#include<vector>
#include<queue>
using namespace std;
const int n = 6;
bool inq[n] = { false };
int G1[n][n];  //use adjacency matrix to save the graph 
vector<int> G2[n]; //use adjacency table to save the graph

void bfs1(int);
void bfsTrave();
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
	bfsTrave();
}

void bfs1(int u) //u is the number of  the node that we want to visit
{
	queue<int> q;
	q.push(u);
	inq[u] = true;
	while (!q.empty()) 
	{
		int node = q.front();
		cout << node<<" ";
		q.pop();
		for (int v = 0; v < n; v++)
		{
			if (G1[node][v] == 1&&inq[v]==false)
			{
				q.push(v);
				inq[v] = true;
			}
		}
	}
}
void bfs2(int u)
{
	queue<int> q;
	q.push(u);
	inq[u] = true;
	while (!q.empty())
	{
		int node = q.front();    
		cout << node << " ";
		q.pop();
		for (int i = 0; i < G2[node].size(); i++)
		{
			if (inq[G2[node][i]] == false) 
			{
				q.push(G2[node][i]);
				inq[G2[node][i]] = true;
			}
		}
	}
}
//travel the graph
void bfsTrave()
{
	for (int i = 0; i < n; i++)
	{
		if (inq[i] == false)
			bfs1(i); //bfs2(i);
	}
}

