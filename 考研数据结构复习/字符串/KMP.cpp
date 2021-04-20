#include<iostream>
#include<vector>
using namespace std;

vector<int> next_array;
void getNext(string s) {
	int j = -1,len=s.length();
	next_array.push_back(-1);//��ʼ��next[0]=-1
	for (int i = 1; i < len; i++) { //��ȡnext[1]~next[len-1]
		while (j != -1 && s[i] != s[j + 1]) 
			j = next_array[j]; //������j=next[j]
		if (s[i] == s[j + 1]) j++; //���s[i]==s[j+1],��jָ�����λ��
		next_array.push_back(j);
	}
}

int KMP(string s, string p) {
	int n = s.length(), m = p.length();
	getNext(p);
	int j = -1;
	for (int i = 0; i < n; i++) {
		while (j != -1 && s[i] != p[j + 1])
			j = next_array[j]; //���ϻ��ˣ�֪��jΪ-1����s[i]==p[j+1]
		if (s[i] == p[j + 1]) 
			j++;//s[i]��p[j+1]ƥ��ɹ�����j+1
		if (j == m - 1)
			return 1; //ƥ��ɹ�
	}
	return -1;
}

