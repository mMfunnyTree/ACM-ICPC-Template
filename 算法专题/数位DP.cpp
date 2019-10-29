//Ҫ49
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll num[30];
ll dp[30][2];
ll dfs(int pos,int pre,int lim)
{
    if(!pos)return 1;
    if(!lim && ~dp[pos][pre])
        return dp[pos][pre];
    ll ans = 0, top = lim?num[pos]:9;
    for(int i=0;i<=top;i++)
    {
        if(pre&&i==9)continue;
        int nl = i==top&&lim;
        ans+=dfs(pos-1,i==4,nl);
    }
    return lim?ans:dp[pos][pre]=ans;
}

ll solve(ll n)
{
    int len=0;
    while(n)
    {
        num[++len]=n%10;
        n/=10;
    }
    return dfs(len,0,1);
}

int main()
{
    int t;
    cin>>t;
    memset(dp,-1,sizeof(dp));
    while(t--)
    {
        ll n;
        cin>>n;
        cout<<n+1-solve(n)<<endl;
    }
    return 0;
}

//Ҫ49
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll dp[30][10][2];
ll num[30];

ll dfs(int pos,int pre,int sta,int lim)
{
    if(!pos)return sta;
    if((!lim)&&(dp[pos][pre][sta]!=-1))
        return dp[pos][pre][sta];
    int top = lim?num[pos]:9;
    ll ret=0;
    for(int i=0;i<=top;i++)
    {
        ret += dfs(pos-1,i,sta||(pre==4&&i==9),lim&&(i==top));
    }
    return lim?ret:dp[pos][pre][sta]=ret;
}

ll solve(ll n)
{
    int len=0;
    while(n)
    {
        num[++len]=n%10;
        n/=10;
    }
    return dfs(len,0,0,1);
}

int main()
{
    int t;
    cin>>t;
    memset(dp,-1,sizeof(dp));
    while(t--)
    {
        ll n;
        cin>>n;
        cout<<solve(n)<<endl;
    }
    return 0;
}
