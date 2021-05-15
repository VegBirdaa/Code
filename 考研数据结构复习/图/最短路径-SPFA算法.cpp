#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct Node {
	int weight;
	int num;
};
const int INF = (int)1e9; //代表无穷大
const int MAXN = 1000;  
vector<Node> graph[MAXN];	//邻接表
int dis[MAXN];  //到各个点的最短距离
int fre[MAXN]; //每个节点的入队次数
bool inque[MAXN];  //是否在队列中

bool SPFA(int s,int n)
{
	//初始化各个数组
	fill(dis, dis + MAXN, INF);
	fill(inque, inque + MAXN, false);
	fill(fre, fre + MAXN, 0);
	queue<int> q;  //使用队列优化Bellman-Ford
	dis[s] = 0;
	//源点入队列
	q.push(s);
	inque[s] = true;
	fre[s] = 1;
	//主体部分
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		inque[s] = false;
		for (int i = 0; i < graph[u].size(); i++)
		{
			int v = graph[u][i].num;
			int w = graph[u][i].weight;
			if (dis[u] + w < dis[v])
			{
				dis[v] = dis[u] + w;
				if(inque[v]==false)
				{
					q.push(v);
					inque[v] = true;
					fre[v]++;
					if (fre[v] > n - 1)
						return false;
				}
				
				
			}
		}
	}
	return true;
}

int main()
{

}