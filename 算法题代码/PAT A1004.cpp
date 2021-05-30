#include<iostream>
#include<vector>
#include<queue>
using namespace std;
vector<int> layer;

vector<bool> is_leaf(101);
vector<vector<int>> children(101);

int main()
{
	int N, M;
	cin >> N >> M;

	fill(is_leaf.begin(), is_leaf.end(), true);
	for (int i = 0; i < M; i++)
	{
		int non_leaf;
		cin >> non_leaf;
		is_leaf[non_leaf] = false;
		int num;
		cin >> num;
		for (int j = 0; j < num; j++)
		{
			int child;
			cin >> child;
			children[non_leaf].push_back(child);
		}
	}
	queue<int> q;
	q.push(1);
	
	while (!q.empty())
	{
		int count = 0;
		int q_size = q.size();
		
		for (int i = 0; i < q_size; i++)
		{
			int node = q.front();
			if (children[node].size())
				for (int each : children[node])
					q.push(each);
			if (is_leaf[node])
				count++;
			q.pop();
		}
		
		layer.push_back(count);

	}

	for (int i = 0; i < layer.size(); i++)
        if(i==0)cout<<layer[i];
        else cout << " " << layer[i];
		
}
