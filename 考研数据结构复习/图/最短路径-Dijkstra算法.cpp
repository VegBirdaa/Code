#include<iostream>
using namespace std;
const int MAXV = 1000; //������󶥵���
const int INF = 1000000000; //��INFΪһ���ܴ����
int G[MAXV][MAXV]; //����ͼ���ڽӾ���
int d[MAXV]; //������㵽���������̾���
bool vis[MAXV] = { false }; //��ʼ��Ϊδ����

void Dijkstra(int, int);
int main()
{
	//��ʼ���ڽӾ���
	fill(G[0], G[0] + MAXV*MAXV, INF);
	int n = 6;
	G[0][1] = 12; G[0][2] = 10; G[0][4] = 30; G[0][5] = 100;
	G[1][2] = 5;
	G[2][3] = 50;
	G[3][5] = 10;
	G[4][3] = 20; G[4][5] = 60;
	Dijkstra(0, n);
	for (int i = 0; i < n; i++)
		cout << d[i]<<" ";
}
void Dijkstra(int s,int n) //sΪ��㡢nΪ�ܽ����
{
	fill(d, d + MAXV, INF); //��ʼ��������
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
		
		if (u == -1) return; //ʣ�µĽ�����㲻��ͨ
		vis[u] = true;
		//��uΪ�н飬ˢ����̾����
		for (int v = 0; v < n; v++)
			if (vis[v] == false && G[u][v] != INF && d[u] + G[u][v] < d[v])
				d[v] = d[u] + G[u][v];
		
	}
}