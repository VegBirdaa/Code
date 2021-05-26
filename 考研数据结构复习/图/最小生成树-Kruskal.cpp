#include<iostream>
#include<algorithm>
const int MAXE = 10000;
const int MAXV = 100;
using namespace std;

struct Edge {
	int u, v;
	int cost;
}E[MAXE];

int father[MAXV]; //每个节点的父亲节点
int findFather(int n)
{
	int x = n;
	while (x != father[x])
		x = father[x];

	int a = n;
	//路径压缩
	while (a != father[a])
	{
		int z = a;
		a = father[a];
		father[z] = x;
	}
	return x;
}
//自定义比较函数
bool cmp(Edge e1, Edge e2)
{
	return e1.cost < e2.cost;
}

int Kruskal(int n, int m) //n为节点数、m为边数
{
	int ans = 0, num_edge = 0; //最小权值和为0，边的数量为0
	//初始化father数组
	for (int i = 1; i <= n; i++)
		father[i] = i;
	//将边按权值从小到大排序
	sort(E, E + m, cmp);
	for (int i = 0; i < m; i++)
	{
		int fu = findFather(E[i].u);
		int fv = findFather(E[i].v);
		if (fu != fv)
		{
			father[fu] = fv;
			num_edge++;
			ans += E[i].cost;
			//如果边数等于节点数减1，结束循环
			if (num_edge == n - 1)
				break;
		}
	}
	//不连通 返回-1
	if (num_edge != n - 1)
		return -1;
	return ans;
}

int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++)
		cin >> E[i].u >> E[i].v >> E[i].cost;

	cout << Kruskal(n, m);


}
