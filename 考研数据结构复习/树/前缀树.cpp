#include<iostream>
#include<vector>
using namespace std;
class Trie {
private:
	vector<Trie*> children;
	bool isEnd;
public:
	//构造函数
	Trie():children(26),isEnd(false){}

	//插入
	void insert(string word)
	{
		Trie* node = this;
		for (char ch : word)
		{
			ch -= 'a';
			if (node->children[ch] == nullptr)
				node->children[ch] = new Trie();
			node = node->children[ch];
		}
		node->isEnd = true;
	}
	//前缀匹配
	Trie* matchPrefix(string word)
	{
		Trie* node = this;
		for (char ch : word)
		{
			ch -= 'a';
			if (node->children[ch] == nullptr)
				return nullptr;
			node = node->children[ch];
		}
		return node;
	}

	
	//查找
	bool search(string word)
	{
		Trie* node = matchPrefix(word);
		//到达其中一个终结点时 返回真
		return node != nullptr && node->isEnd;
	}

};
