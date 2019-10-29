/*
给定N个三维的点，问对于点i，
有多少个点三个坐标都小于点i(1<=i<=n)
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 100010
struct rec{
    int x,y,z,id;
    bool operator==(const rec &a)
    {
        return x==a.x&&y==a.y&&z==a.z;
    }
}a[N],tmp[N];
int ans[N],c[N];
int n;
bool cmp1(rec &a,rec &b)
{
    if(a==b) return a.id<b.id;
    return a.x<b.x||a.x==b.x&&a.y<b.y||a.x==b.x&&a.y==b.y&&a.z<b.z;
}
bool cmp2(rec &a,rec &b)
{
    return a.y<b.y||a.y==b.y&&a.id<b.id;
}
inline void add(int x,int w)
{
    for(;x<=100000;x+=x&-x) c[x]+=w;
}
inline int getsum(int x)
{
    int ans=0;
    for(;x;x-=x&-x) ans+=c[x];
    return ans;
}
void solve(int l,int r)
{
    if(l==r) return;
    int mid=l+r>>1;
    for(int i=l;i<=r;++i) tmp[i]=a[i];
    sort(a+l,a+mid+1,cmp2);
    sort(a+mid+1,a+r+1,cmp2);
    int ll=l;
    for(int i=mid+1;i<=r;++i)
    {
        while(ll<=mid&&a[ll].y<=a[i].y) add(a[ll++].z,1);
        ans[a[i].id]+=getsum(a[i].z);
    }
    for(int i=l;i<ll;++i) add(a[i].z,-1);
    for(int i=l;i<=r;++i) a[i]=tmp[i];
    solve(l,mid);solve(mid+1,r);
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
            scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z);
            a[i].id=i;
        }
        sort(a+1,a+n+1,cmp1);
        memset(ans,0,sizeof(ans));
        solve(1,n);
        for(int i=n-1;i>0;--i)
            if(a[i]==a[i+1]) ans[a[i].id]=ans[a[i+1].id];
        for(int i=1;i<=n;++i)
            printf("%d\n",ans[i]);
    }
    return 0;
}
