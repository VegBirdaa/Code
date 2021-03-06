#include<iostream>
#include<vector>
using namespace std;
const int MAXV = 1000; //设置最大顶点数
const int INF = 1000000000; //设INF为一个很大的数
int G[MAXV][MAXV]; //定义图的邻接矩阵
int d[MAXV]; //定义起点到各个点的最短距离
bool vis[MAXV] = { false }; //初始化为未访问

void Dijkstra(int, int,vector<int>&);
void Path(int, int, vector<int>);
int main()
{
	//初始化邻接矩阵
	
	fill(G[0], G[0] + MAXV*MAXV, INF);
	int n = 6;
	G[0][1] = 12; G[0][2] = 10; G[0][4] = 30; G[0][5] = 100;
	G[1][2] = 5;
	G[2][3] = 50;
	G[3][5] = 10;
	G[4][3] = 20; G[4][5] = 60;
	//记录前置结点的数组
	vector<int> pre(n);
	Dijkstra(0, n,pre);
	//输出最短路径长度以及最短路径
	for (int i = 0; i < n; i++)
	{
		cout << "距离结点" << i << "最短距离：";
		cout << d[i] << "    路径：";
		Path(0,i,pre);
		cout << i<<endl;
	}
}
void Dijkstra(int s,int n,vector<int>& pre) //s为起点、n为总结点数
{
	pre[s] = s;
	fill(d, d + MAXV, INF); //初始距离数组
	d[s] = 0;
	for (int i = 0; i < n; i++)
	{
		int u = -1, MIN = INF;
		for (int j = 0; j < n; j++)
			if (vis[j] == false && d[j] < MIN)
			{
				u = j;
				MIN = d[j];
			}  

		if (u == -1) return; //剩下的结点和起点不连通
		vis[u] = true;
		//以u为中介，刷新最短距离表
		for (int v = 0; v < n; v++)
			if (vis[v] == false && G[u][v] != INF && d[u] + G[u][v] < d[v])
			{	
				pre[v] = u;
				d[v] = d[u] + G[u][v];
			}
	}
}

void Path(int s,int p, vector<int> pre)
{
	if (p == s) 
		return; 
	
	Path(s, pre[p], pre);
	cout << pre[p] << "  ";
}
