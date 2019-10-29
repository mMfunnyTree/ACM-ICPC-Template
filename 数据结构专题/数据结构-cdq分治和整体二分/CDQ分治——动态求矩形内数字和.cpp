/*
你有一个N*N的棋盘，每个格子内有一个整数，初始时的时候全部为0，现在需要维护两种操作：
1 x y A 1<=x,y<=N，A是正整数，将格子x,y里的数字加上A
2 x1 y1 x2 y2，1<=x1<= x2<=N，1<=y1<= y2<=N，输出x1 y1 x2 y2这个矩形内的数字和
3 无 终止程序
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 500010
#define M 200010
struct rec{
    int x,y,t,k,w,be;
}a[M*4],tmp[M*4];
int c[N],ans[M];
int n,m;
void add(int x,int w)
{
    for(;x<=n;x+=x&-x) c[x]+=w;
}
int getsum(int x)
{
    int ans=0;
    for(;x;x-=x&-x) ans+=c[x];
    return ans;
}
bool cmp(const rec &a,const rec &b)
{
    return a.y<b.y||a.y==b.y&&a.k<b.k;
}
void solve(int l,int r)
{
    if(l==r) return;
    int mid=l+r>>1;
    for(int i=l;i<=r;++i)
        if(a[i].t<=mid&&a[i].k==1) add(a[i].x,a[i].w);
        else if(a[i].t>mid&&a[i].k==2) ans[a[i].be]+=getsum(a[i].x)*a[i].w;
    for(int i=l;i<=r;++i)
        if(a[i].t<=mid&&a[i].k==1) add(a[i].x,-a[i].w);
    int ll=l,rr=mid+1;
    for(int i=l;i<=r;++i)
        if(a[i].t<=mid) tmp[ll++]=a[i];
        else tmp[rr++]=a[i];
    for(int i=l;i<=r;++i) a[i]=tmp[i];
    solve(l,mid);solve(mid+1,r);
}
int main()
{
    scanf("%d",&n);
    int tot=0,k,x1,y1,x2,y2,w;
    while(true)
    {
        scanf("%d",&k);
        if(k==1)
        {
            scanf("%d%d%d",&x1,&y1,&w);
            a[++tot].x=x1;a[tot].y=y1;a[tot].t=tot;a[tot].k=k;a[tot].w=w;
        }
        else if(k==2)
        {
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            a[++tot].x=x2;a[tot].y=y2;a[tot].t=tot;a[tot].k=2;a[tot].w=1;a[tot].be=++m;
            a[++tot].x=x2;a[tot].y=y1-1;a[tot].t=tot;a[tot].k=2;a[tot].w=-1;a[tot].be=m;
            a[++tot].x=x1-1;a[tot].y=y2;a[tot].t=tot;a[tot].k=2;a[tot].w=-1;a[tot].be=m;
            a[++tot].x=x1-1;a[tot].y=y1-1;a[tot].t=tot;a[tot].k=2;a[tot].w=1;a[tot].be=m;
        }
        else break;
    }
    sort(a+1,a+tot+1,cmp);
    solve(1,tot);
    for(int i=1;i<=m;++i) printf("%d\n",ans[i]);
    return 0;
}
