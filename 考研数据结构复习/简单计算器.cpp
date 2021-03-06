#include<iostream>
#include<stack>
#include<queue>
#include<map>
#include<string>
using namespace std;

map<char, int> priority;
void iniPriority() {
	priority['+'] = 0;
	priority['-'] = 0;
	priority['*'] = 1;
	priority['/'] = 1;
}

class node {
public:
	double op_num;
	char op_mark;
	int flag; //0为操作数、1为操作符
	node() {
		op_num = 0;
		op_mark = '0';
		flag = 0;
	}
};

int main() {
	string s;
	stack<node> op;
	queue<node> postfix;
	cin >> s;
	//s.erase(); //清除字符串中的空格
	iniPriority();
	int j = 0;

    /*
	将输入字符串转换成后缀表达式
	*/
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
			//字符串处理数字
			string s1 = s.substr(j, i - j);
			node n;
			n.op_num = stod(s1);
			n.flag = 0;
			postfix.push(n);
			//处理运算符
			node n1;
			n1.op_mark = s[i];
			n1.flag = 1;
			if (op.empty()||priority[n1.op_mark]>priority[op.top().op_mark]) {
				op.push(n1);//当符号栈为空或当前符号优先级高于栈顶符号优先级，则入栈
			}
			else {
				while (!op.empty() && (priority[n1.op_mark] <= priority[op.top().op_mark])) {
					postfix.push(op.top());//当前符号优先级小于等于栈顶符号优先级，先谈栈再入栈
					op.pop();
				}
				op.push(n1);
			}
			j = i + 1;
		}
		else if (i == s.size()-1) {
			string s1 = s.substr(j, i - j+1);
			node n;
			n.op_num = stoi(s1);
			n.flag = 0;
			postfix.push(n);
		}
		
	}
	
	//处理完字符串后，若符号栈中有剩余符号，则依次弹出
	while (!op.empty()) {
		postfix.push(op.top());
		op.pop();
	}

	//while (!postfix.empty()) {
	//	if (postfix.front().flag == 0)
	//		cout << postfix.front().op_num << endl;
	//	else
	//		cout << postfix.front().op_mark << endl;
	//	postfix.pop();
	//}

	/*
	后缀表达式的计算
	*/


	while (!postfix.empty()) {
		if (postfix.front().flag == 0) {//如果队列头是数字，则入栈
			op.push(postfix.front());
			postfix.pop();
		}
		else {
			//如果是运算符，则弹出两个数字参与运算
			double num1 = op.top().op_num;
			op.pop();
			double num2 = op.top().op_num;
			op.pop();
			double result=0.0;
			switch (postfix.front().op_mark)
			{
			case '+':
				result = num1 + num2;
				break;
			case '-':
				result = num2 - num1;
				break;
			case'*':
				result = num1 * num2;
				break;

			case '/':
				result = num2 / num1;
			default:
				break;
			}
			postfix.pop();
			node n;
			n.op_num = result;
			n.flag = 0;
			//将运算结果压栈
			op.push(n);
		}
	}
	cout << op.top().op_num<<endl;
}
