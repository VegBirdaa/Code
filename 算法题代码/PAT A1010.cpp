#include<iostream>
#include<vector>
#include<unordered_map>
#include<cmath>
using namespace std;

unordered_map<char,int> dic; //表示[0-9,a-z]与数字的对应关系

long long toDecimal(string s,long long radix)   
{   
    long long num=0;
    int p=0;
    for(int i=s.size()-1;i>=0;i--)
    {
        num+=(long long)pow(radix,p)*dic[s[i]];
        if(num<0||(long long)pow(radix,p)<0)   //若进制的值太大 返回-1
            return -1;
        p++;
    }
    return num;
    
}
int main()
{
    //输入
    string inputs[2];
    cin>>inputs[0]>>inputs[1];
    long long tag,radix;
    cin>>tag>>radix;
    
    
    //初始化dic
    for(int i=0;i<=9;i++)
        dic[i+'0']=i;
    char ch='a';
    for(int i=10;i<=35;i++)
        dic[ch++]=i;
    
    long long num_tag=toDecimal(inputs[tag-1],radix);
    
    int index=(tag==1)?1:0;  
    int max_num=2;
    for(int i=0;i<inputs[index].size();i++)
    {
        max_num=max(max_num,dic[inputs[index][i]]+1);
    }
    long long l=max_num,r=num_tag;
  
    while(l<r) //二分查找
    {
        long long mid=(l+r)/2;
        long long num2=toDecimal(inputs[index],mid);
        if(num2>=num_tag||num2<0)
            r=mid;
        else 
            l=mid+1;
    }
    if(toDecimal(inputs[index],l)==num_tag)
        cout<<l;
    else
        cout<<"Impossible";
}
