#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 100010
const int inf=1e9;
struct rec{
    int w,id;
    rec(){}
    rec(int w,int id):w(w),id(id){}
    bool operator<(const rec a)const
    {
        return w<a.w;
    }
}a[N];
struct interval{
    int l,r,k,id,cnt;
}q[N],tmp[N];
int n,m;
int c[N],ans[N];
inline void add(int x,int w)
{
    for(;x<=n;x+=x&-x) c[x]+=w;
}
inline int getsum(int x)
{
    int ans=0;
    for(;x;x-=x&-x) ans+=c[x];
    return ans;
}
void calc(int s,int t,int l,int r)
{
    int x=lower_bound(a+1,a+n+1,rec(l,0))-a;
    for(int i=x;i<=n&&a[i].w<=r;++i) add(a[i].id,1);
    for(int i=s;i<=t;++i)
        q[i].cnt=getsum(q[i].r)-getsum(q[i].l-1);
    for(int i=x;i<=n&&a[i].w<=r;++i) add(a[i].id,-1);
}
void solve(int s,int t,int l,int r)
{
    if(l==r)
    {
        for(int i=s;i<=t;++i) ans[q[i].id]=l;
        return;
    }
    int mid=l+(r-l>>1);
    calc(s,t,l,mid);
    int ss=s-1,tt=t+1;
    for(int i=s;i<=t;++i)
    {
        if(q[i].cnt>=q[i].k) tmp[++ss]=q[i];
        else q[i].k-=q[i].cnt,tmp[--tt]=q[i];
    }
    for(int i=s;i<=t;++i) q[i]=tmp[i];
    if(ss>=s) solve(s,ss,l,mid);
    if(tt<=t) solve(tt,t,mid+1,r);
}
bool cmp(rec a,rec b)
{
    return a.w<b.w;
}
int main()
{
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i].w);a[i].id=i;
        }
        sort(a+1,a+n+1,cmp);
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d%d",&q[i].l,&q[i].r,&q[i].k);
            q[i].cnt=0;q[i].id=i;
        }
        solve(1,m,-inf,inf);
        for(int i=1;i<=m;++i) printf("%d\n",ans[i]);
    }
    return 0;
}
