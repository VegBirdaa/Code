#include<iostream>

using namespace std;
const int MAXV = 1000; //设置最大顶点数
const int INF = (int)1e9; //设INF为一个很大的数
int G[MAXV][MAXV]; //定义图的邻接矩阵
int dis[MAXV][MAXV];

void Floyd(int);
int main()
{
	//初始化邻接矩阵

	fill(G[0], G[0] + MAXV * MAXV, INF);
	int n = 6;
	G[0][1] = 12; G[0][2] = 10; G[0][4] = 30; G[0][5] = 100;
	G[1][2] = 5;
	G[2][3] = 50;
	G[3][5] = 10;
	G[4][3] = 20; G[4][5] = 60;
	Floyd(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			if (dis[i][j] == INF)
				cout << "INF ";
			else
				cout << dis[i][j] << " ";
		cout << endl;
	}
}

void Floyd(int n)  //n为边数
{
	//初始化dis矩阵
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i == j)
				dis[i][j] = 0;	//对角线元素设置为0
			else
				dis[i][j] = G[i][j];
	//循环遍历
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (dis[i][k] != INF && dis[k][j] != INF && dis[i][k] + dis[k][j] < dis[i][j])
					dis[i][j] = dis[i][k] + dis[k][j];
					
}
