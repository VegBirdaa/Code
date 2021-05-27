#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
bool cmp(int a, int b)
{
    return a > b;
}


int main()
{
    int N;
    cin >> N;
   if(N==6174)
       cout<<"7641 - 1467 = 6174"<<endl;
    while (N != 6174&&N!=0) {
        vector<int> v;
        while (N != 0)
        {
            v.push_back(N % 10);
            N /= 10;
        }

        sort(v.begin(), v.end(), cmp);
        int num1 = 0, coe = 1000;
        for (int x : v)
        {
            num1 += coe * x;
            coe /= 10;
        }


        sort(v.begin(), v.end());
        coe = 1;
        int num2 = 0;
        for (int i = v.size() - 1; i >= 0; i--)
        {
            num2 += v[i] * coe;
            coe *= 10;
        }
        N = num1 - num2;
        //使用printf格式化输出
        printf("%03d - %04d = %04d\n",num1,num2,N);
    }
    return 0;
}
