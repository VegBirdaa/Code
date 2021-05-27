#include<iostream>
#include<map>
#include<cmath>
#include<vector>
using namespace std;
int main()
{
    map<int,double> m1,m2;
    int n1,n2;
    cin>>n1;
    for(int i=0;i<n1;i++)
    {
        int a;
        double b;
        cin>>a>>b;
        m1[a]=b;
    }
    cin>>n2;
     for(int i=0;i<n2;i++)
    {
        int a;
        double b;
        cin>>a>>b;  
        m2[a]=b;
    }
    
    vector<double> v(1001);
    int n=0;
    for(int i=0;i<v.size();i++)
    { 
        
        v[i]=m1[i]+m2[i];
        if(v[i]!=0) n++;
    }
    cout<<n;
    for(int i=1000;i>=0;i--)
        if(v[i]!=0)
        {
           cout<<" ";
            printf("%d %.1f",i,v[i]);  //用printf格式化输出   decimal place小数位
        }
    
}
