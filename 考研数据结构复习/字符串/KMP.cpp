#include<iostream>
#include<vector>
using namespace std;

vector<int> next_array;
void getNext(string s) {
	int j = -1,len=s.length();
	next_array.push_back(-1);//初始化next[0]=-1
	for (int i = 1; i < len; i++) { //获取next[1]~next[len-1]
		while (j != -1 && s[i] != s[j + 1]) 
			j = next_array[j]; //反复令j=next[j]
		if (s[i] == s[j + 1]) j++; //如果s[i]==s[j+1],令j指向这个位置
		next_array.push_back(j);
	}
}

int KMP(string s, string p) {
	int n = s.length(), m = p.length();
	getNext(p);
	int j = -1;
	for (int i = 0; i < n; i++) {
		while (j != -1 && s[i] != p[j + 1])
			j = next_array[j]; //不断回退，知道j为-1或者s[i]==p[j+1]
		if (s[i] == p[j + 1]) 
			j++;//s[i]与p[j+1]匹配成功，令j+1
		if (j == m - 1)
			return 1; //匹配成功
	}
	return -1;
}

