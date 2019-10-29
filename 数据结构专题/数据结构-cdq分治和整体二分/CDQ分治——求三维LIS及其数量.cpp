/*
给定n个三维坐标，求其LIS及其数量，
当x1<=x2,y1<=y2,z1<=z2是，p1<=p2。
先排序掉一维，然后剩下两维分治，
用一个带长度和方案数的结构体树状数组维护。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 100010
const int mod=(1<<30)-1;
struct Point{
    int x,y,z,id;
}q[N],tmp[N];
struct rec{
    int len,num;
    void init()
    {
        len=num=0;
    }
}dp[N],c[N];
int a[N];
int n,tot;
void updata(rec &a,rec b)
{
    if(a.len<b.len) a=b;
    else if(a.len==b.len) a.num+=b.num,a.num&=mod;
}
void add(int x,const rec &a)
{
    for(;x<=tot;x+=x&-x) updata(c[x],a);
}
rec getmax(int x)
{
    rec ans;ans.init();
    for(;x;x-=x&-x) updata(ans,c[x]);
    return ans;
}
void clr(int x)
{
    for(;x<=tot;x+=x&-x) c[x].init();
}
bool cmp1(Point &p1,Point &p2)
{
    return p1.x<p2.x||p1.x==p2.x&&p1.y<p2.y||p1.x==p2.x&&p1.y==p2.y&&p1.z<p2.z;
}
bool cmp2(Point &p1,Point &p2)
{
    return p1.y<p2.y||p1.y==p2.y&&p1.id<p2.id;
}
void solve(int s,int t)
{
    if(s==t) return;
    int mid=s+t>>1;
    solve(s,mid);
    for(int i=s;i<=t;++i) tmp[i]=q[i];
    sort(tmp+s,tmp+t+1,cmp2);
    rec ans;
    for(int i=s;i<=t;++i)
        if(tmp[i].id<=mid)
            add(tmp[i].z,dp[tmp[i].id]);
        else
        {
            ans=getmax(tmp[i].z);++ans.len;
            updata(dp[tmp[i].id],ans);
        }
    for(int i=s;i<=t;++i)
        if(tmp[i].id<=mid) clr(tmp[i].z);
    solve(mid+1,t);
}
int main()
{
    int ca;
    scanf("%d",&ca);
    while(ca--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d%d",&q[i].x,&q[i].y,&q[i].z);
            a[i]=q[i].z;dp[i].len=dp[i].num=1;
        }
        sort(a+1,a+n+1);
        tot=unique(a+1,a+n+1)-a-1;
        for(int i=1;i<=n;++i)
            q[i].z=lower_bound(a+1,a+tot+1,q[i].z)-a;
        sort(q+1,q+n+1,cmp1);
        for(int i=1;i<=n;++i) q[i].id=i;
        solve(1,n);
        rec ans;ans.init();
        for(int i=1;i<=n;++i) updata(ans,dp[i]);
        printf("%d %d\n",ans.len,ans.num);
    }
    return 0;
}
