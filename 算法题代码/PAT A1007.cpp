#include<iostream>
#include<vector>
using namespace std;
int main()
{
    int N;
    cin>>N;
    vector<int> nums(N);
    bool flag=false;
    for(int i=0;i<N;i++)
    { 
        cin>>nums[i];
        if(nums[i]>=0)
            flag=true;
    }
    
    if(flag){
        vector<int> dp(N);
        dp[0]=nums[0];
        for(int i=1;i<N;i++)
           dp[i]=max(dp[i-1]+nums[i],nums[i]);
        int i=0,max=dp[0];
        for(int j=1;j<N;j++)
            if(dp[j]>max)
            {
                max=dp[j];
                i=j;
            }
        int k=i,min_index=(int)1e9;
        for(int m=max;k>=0;k--)
        {
            m-=nums[k];
            if(m==0)
                min_index=min(min_index,k);
        }
        cout<<max<<" "<<nums[min_index]<<" "<<nums[i];    
    }else
        cout<<0<<" "<<nums[0]<<" "<<nums[N-1];
}
