/*
dp[i]=min(dp[j]+(F[n]-F[j])*(T[i]-T[j]+S)
dp[j]+F[j]*T[j]-F[j]*S-F[n]*T[j]=T[i]*F[j]+dp[i]-F[n]*(T[i]+S)
                y               =  k * x  +dp[i]-    c
其中k不是单调的，且可能为负，
考虑CDQ分治：
把每天看作一个点。将点按照k升序排列。
定义sovle(l,r)为解决l,r内的所有询问，且保证solve结束后点按照x,y升序排列。
1.按照点的查询顺序分成[l,mid]与[mid+1,r]
2.递归处理左区间
3.此时左区间已经按照x,y排好序，扫一遍求出左区间的下凸线
4.计算左区间对右区间的影响。此时右区间按照-a/b升序排列，扫一遍更新右区间答案。
5.递归处理右区间
6.将区间按照x,y升序排列
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 300010
typedef long long LL;
struct rec{
    LL x,y,id,k;
    bool operator<(const rec a)
    {
        return x<a.x||x==a.x&&y<a.y;
    }
}a[N],q[N];
LL F[N],T[N],dp[N];
int n,S;
inline LL cross(rec &p0,rec &p1,rec &p2)
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
bool cmp(rec a,rec b)
{
    return a.k<b.k;
}
void solve(int l,int r)
{
    if(l==r)
    {
        a[l].x=F[l];
        a[l].y=dp[l]+F[l]*(T[l]-S)-F[n]*T[l];
        return;
    }
    int mid=l+r>>1,ll=l,rr=mid+1;
    for(int i=l;i<=r;++i)
        if(a[i].id<=mid) q[ll++]=a[i];
        else q[rr++]=a[i];
    for(int i=l;i<=r;++i) a[i]=q[i];
    solve(l,mid);
    int s=1,t=0;
    for(int i=l;i<=mid;++i)
    {
        while(s<t&&cross(q[t-1],q[t],a[i])<=0) --t;
        q[++t]=a[i];
    }
    for(int i=mid+1;i<=r;++i)
    {
        LL c=F[n]*(T[a[i].id]+S);
        while(s<t&&q[s].y-a[i].k*q[s].x+c>=q[s+1].y-a[i].k*q[s+1].x+c) ++s;
        dp[a[i].id]=min(dp[a[i].id],q[s].y-a[i].k*q[s].x+c);
    }
    solve(mid+1,r);
    ll=l;rr=mid+1;
    for(int i=l;i<=r;++i)
        if(ll<=mid&&(rr>r||a[ll]<a[rr])) q[i]=a[ll++];
        else q[i]=a[rr++];
    for(int i=l;i<=r;++i) a[i]=q[i];
}
int main()
{
    scanf("%d%d",&n,&S);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld%lld",&T[i],&F[i]);
        T[i]+=T[i-1];F[i]+=F[i-1];
        a[i].id=i;a[i].k=T[i];
    }
    sort(a+1,a+n+1,cmp);
    memset(dp,0x7f,sizeof(dp));
    dp[0]=0;
    solve(0,n);
    printf("%lld\n",dp[n]);
    return 0;
}
