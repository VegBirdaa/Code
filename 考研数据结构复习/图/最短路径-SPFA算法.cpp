#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct Node {
	int weight;
	int num;
};
const int INF = (int)1e9; //���������
const int MAXN = 1000;  
vector<Node> graph[MAXN];	//�ڽӱ�
int dis[MAXN];  //�����������̾���
int fre[MAXN]; //ÿ���ڵ����Ӵ���
bool inque[MAXN];  //�Ƿ��ڶ�����

bool SPFA(int s,int n)
{
	//��ʼ����������
	fill(dis, dis + MAXN, INF);
	fill(inque, inque + MAXN, false);
	fill(fre, fre + MAXN, 0);
	queue<int> q;  //ʹ�ö����Ż�Bellman-Ford
	dis[s] = 0;
	//Դ�������
	q.push(s);
	inque[s] = true;
	fre[s] = 1;
	//���岿��
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