#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 100010
struct rec{
    int x,y,k,cnt,id;
    rec(){}
    rec(int x,int y,int k,int cnt,int id):
        x(x),y(y),k(k),cnt(cnt),id(id){}
}q[N*3],q1[N*3],q2[N*3];
const int inf=1e9;
int a[N],ans[N*3],c[N];
int n,m,nn;
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
    for(int i=s;i<=t;++i)
    {
        if(q[i].k) q[i].cnt=getsum(q[i].y)-getsum(q[i].x-1);
        else if(q[i].y<=r) add(q[i].x,q[i].cnt);
    }
    for(int i=s;i<=t;++i)
        if(!q[i].k&&q[i].y<=r) add(q[i].x,-q[i].cnt);
}
void solve(int s,int t,int l,int r)
{
    if(l==r)
    {
        for(int i=s;i<=t;++i)
            if(q[i].k) ans[q[i].id]=l;
        return;
    }
    int mid=l+(r-l>>1);
    calc(s,t,l,mid);
    int t1=0,t2=0;
    for(int i=s;i<=t;++i)
    {
        if(q[i].k)
        {
            if(q[i].cnt>=q[i].k) q1[++t1]=q[i];
            else q[i].k-=q[i].cnt,q2[++t2]=q[i];
        }
        else
        {
            if(q[i].y<=mid) q1[++t1]=q[i];
            else q2[++t2]=q[i];
        }
    }
    for(int i=1;i<=t1;++i) q[s+i-1]=q1[i];
    for(int i=1;i<=t2;++i) q[t-t2+i]=q2[i];
    if(t1) solve(s,s+t1-1,l,mid);
    if(t2) solve(s+t1,t,mid+1,r);
}
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            q[i]=rec(i,a[i],0,1,i);
            ans[i]=0;
        }
        nn=n;
        scanf("%d",&m);
        int x,y,k,z;
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d%d",&z,&x,&y);
            if(z==1)
            {
                ++nn;q[nn]=rec(x,a[x],0,-1,nn);
                ++nn;q[nn]=rec(x,y,0,1,nn);
                a[x]=y;
                ans[nn]=0;
            }
            else
            {
                scanf("%d",&k);
                ++nn;q[nn]=rec(x,y,k,0,nn);
            }
        }
        memset(ans,0,sizeof(ans));
        solve(1,nn,1,inf);
        for(int i=1;i<=nn;++i)
            if(ans[i]) printf("%d\n",ans[i]);
    }
    return 0;
}
