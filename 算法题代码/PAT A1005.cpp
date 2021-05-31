#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
string dic[10] = { "zero","one","two","three","four","five","six","seven","eight","nine" };  //数字字典 用于数字向英文的转换
int main()
{
	string s;
	cin >> s;
	int sum = 0;
	for (int i = 0; i < s.size(); i++)
		sum += s[i] - '0';
	if (sum == 0) {
		cout << "zero"; 
		return 0;
	}
	vector<string> v;
	while (sum != 0)
	{
		v.push_back(dic[sum % 10]);
		sum /= 10;
	}
	reverse(v.begin(), v.end()); 
	for (int i = 0; i < v.size(); i++)
		if (i == 0)
			cout << v[i];
		else
			cout << " " << v[i];
	
}
