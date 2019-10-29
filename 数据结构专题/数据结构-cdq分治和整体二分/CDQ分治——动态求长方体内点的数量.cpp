/*
1 x y z 添加一个点
2 x1 y1 z1 x2 y2 z2 查找长方体内点的数量
CDQ分治套CDQ分治套树状数组
第一重CDQ分治计算左边的修改对右边的询问的影响，
第二重CDQ分治处理三维偏序问题
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 50010
struct rec{
    int k,x,y,z,w,id;
    rec(){}
    rec(int k,int x,int y,int z,int w,int id):
        k(k),x(x),y(y),z(z),w(w),id(id){}
    bool operator==(const rec &a)
    {
        return x==a.x&&y==a.y&&z==a.z;
    }
}q[N*8],qq[N*8],tmp[N*8];
int ans[N],tree[N*2],a[N*2],b[N*2],c[N*2],kind[N];
int n,ta,tb,tc;
bool cmp1(rec &a,rec &b)
{
    if(a==b) return a.id<b.id;
    return a.x<b.x||a.x==b.x&&a.y<b.y||a.x==b.x&&a.y==b.y&&a.z<b.z;
}
bool cmp2(rec &a,rec &b)
{
    return a.y<b.y;
}
inline void add(int x,int w)
{
    for(;x<=tc;x+=x&-x) tree[x]+=w;
}
inline int getsum(int x)
{
    int ans=0;
    for(;x;x-=x&-x) ans+=tree[x];
    return ans;
}
void cdq(int l,int r)
{
    if(l==r) return;
    int mid=l+r>>1;
    for(int i=l;i<=r;++i) tmp[i]=qq[i];
    sort(qq+l,qq+mid+1,cmp2);
    sort(qq+mid+1,qq+r+1,cmp2);
    int ll=l;
    for(int i=mid+1;i<=r;++i)
    {
        while(ll<=mid&&qq[ll].y<=qq[i].y)
        {
            if(qq[ll].k==1) add(qq[ll].z,1);
            ++ll;
        }
        if(qq[i].k==2) ans[qq[i].id]+=getsum(qq[i].z)*qq[i].w;
    }
    for(int i=l;i<ll;++i)
        if(qq[i].k==1) add(qq[i].z,-1);
    for(int i=l;i<=r;++i) qq[i]=tmp[i];
    cdq(l,mid);cdq(mid+1,r);
}
void solve(int l,int r)
{
    if(l==r) return;
    int mid=l+r>>1,n=0;
    for(int i=l;i<=mid;++i)
        if(q[i].k==1) qq[++n]=q[i];
    for(int i=mid+1;i<=r;++i)
        if(q[i].k==2) qq[++n]=q[i];
    if(n)
    {
        sort(qq+1,qq+n+1,cmp1);
        cdq(1,n);
    }
    solve(l,mid);solve(mid+1,r);
}
int main()
{
    int ca;
    scanf("%d",&ca);
    while(ca--)
    {
        scanf("%d",&n);
        int nn=0,k,a1,b1,c1,a2,b2,c2;
        ta=tb=tc=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d%d%d",&k,&a1,&b1,&c1);
            kind[i]=k;
            if(k==1)
            {
                q[++nn]=rec(k,a1,b1,c1,1,i);
                c[++tc]=c1;
            }
            else
            {
                scanf("%d%d%d",&a2,&b2,&c2);
                --a1;--b1;--c1;
                c[++tc]=c1;c[++tc]=c2;
                q[++nn]=rec(k,a2,b2,c2,1,i);
                q[++nn]=rec(k,a1,b2,c2,-1,i);
                q[++nn]=rec(k,a2,b1,c2,-1,i);
                q[++nn]=rec(k,a2,b2,c1,-1,i);
                q[++nn]=rec(k,a1,b1,c2,1,i);
                q[++nn]=rec(k,a1,b2,c1,1,i);
                q[++nn]=rec(k,a2,b1,c1,1,i);
                q[++nn]=rec(k,a1,b1,c1,-1,i);
            }
        }
        sort(c+1,c+tc+1);tc=unique(c+1,c+tc+1)-c-1;
        for(int i=1;i<=nn;++i)
            q[i].z=lower_bound(c+1,c+tc+1,q[i].z)-c;
        memset(ans,0,sizeof(ans));
        solve(1,nn);
        for(int i=1;i<=n;++i)
            if(kind[i]==2) printf("%d\n",ans[i]);
    }
    return 0;
}
