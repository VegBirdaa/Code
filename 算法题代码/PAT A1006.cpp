#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct Time {
	int hour;
	int minute;
	int second;
};
struct Log {
	string id;
	Time login;
	Time logout;
};
bool cmp_login(Log l1, Log l2)
{
	
	if (l1.login.hour != l2.login.hour)
		return l1.login.hour < l2.login.hour;
	if (l1.login.minute != l2.login.minute)
		return l1.login.minute < l2.login.minute;
	return l1.login.second < l2.login.second;
}

bool cmp_logout(Log l1, Log l2)
{
	if (l1.logout.hour != l2.logout.hour)
		return l1.logout.hour > l2.logout.hour;
	if (l1.logout.minute != l2.logout.minute)
		return l1.logout.minute > l2.logout.minute;
	return l1.logout.second > l2.logout.second;
}
int main()
{
	int M;
	cin >> M;
	vector<Log> logs;
	for (int i = 0; i < M; i++)
	{
		string id, login, logout;
		Log l;
		cin >> id;
		cin >> login;
		cin >> logout;
		
		l.id = id;
		l.login.hour = atoi(login.substr(0, 2).c_str());
		l.login.minute= atoi(login.substr(3, 2).c_str());
		l.login.second= atoi(login.substr(6, 2).c_str());
		
		l.logout.hour = atoi(logout.substr(0, 2).c_str());
		l.logout.minute = atoi(logout.substr(3, 2).c_str());
		l.logout.second = atoi(logout.substr(6, 2).c_str());
		logs.push_back(l);	
	}
	
	sort(logs.begin(), logs.end(),cmp_login);
	cout << logs[0].id<<" ";
	sort(logs.begin(), logs.end(), cmp_logout);
	cout << logs[0].id;
}
