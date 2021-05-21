#include<iostream>

using namespace std;
const int MAXV = 1000; //设置最大顶点数
const int INF = (int)1e9; //设INF为一个很大的数
int G[MAXV][MAXV]; //定义图的邻接矩阵
int dis[MAXV];
int vis[MAXV] = {false};

int Prim(int n,int s) //s为初始点
{
	fill(dis, dis + MAXV, INF);
	dis[s] = 0;
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		int min = INF, index = -1;
		for (int i = 0; i < n; i++)
			if (vis[i]==false&&dis[i] < min)
			{
				min = dis[i];
				index = i;
			}

		if (index == -1) return -1;//找不到 即不连通
		vis[index] = true;
		ans += dis[index];
		for (int j = 0; j < n; j++)
		{
			if (G[index][j] != INF && vis[j] == false && G[index][j] < dis[j])
				dis[j] = G[index][j];
		}
		
	}
	return ans;
}

int main()
{
	//初始化邻接矩阵

	fill(G[0], G[0] + MAXV * MAXV, INF);
	
	int v=6,e=10;
	for (int i = 0; i < 10; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		G[u][v] = G[v][u] = w;
	}
	cout << Prim(v, 0);
}
