#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define lson node<<1,s,mid
#define rson node<<1|1,mid+1,t
#define lnode node<<1
#define rnode node<<1|1
#define M(x) memset(x,0,sizeof(x));
#define N 20010
struct rec{
    int x1,x2,h,w;
    rec(){}
    rec(int a,int b,int c,int d)
    {
        x1=a;x2=b;h=c;w=d;
    }
    bool operator<(const rec &a)const
    {
        return (h<a.h)||(h==a.h)&&(w>a.w);
    }
}a[N];
int seg[N*4],change[N*4],sum[N*4];
bool lseg[N*4],rseg[N*4];
int n;
void pushup(int node,int s,int t)
{
    if(change[node])
    {
        seg[node]=t-s+1;
        sum[node]=2;
        lseg[node]=rseg[node]=1;
    }
    else
    {
        if(s!=t)
        {
            seg[node]=seg[lnode]+seg[rnode];
            lseg[node]=lseg[lnode];
            rseg[node]=rseg[rnode];
            sum[node]=sum[lnode]+sum[rnode];
            if(rseg[lnode]&&lseg[rnode])
                sum[node]-=2;
        }
        else seg[node]=lseg[node]=rseg[node]=sum[node]=0;
    }
}
void updata(int node,int s,int t,int l,int r,int w)
{
    if(l<=s&&t<=r)
    {
        change[node]+=w;
        pushup(node,s,t);
    }
    else
    {
        int mid=s+t>>1;
        if(l<=mid) updata(lson,l,r,w);
        if(mid<r) updata(rson,l,r,w);
        pushup(node,s,t);
    }
}
int main()
{
    int s,t,x1,x2,y1,y2;
    M(seg);M(lseg);M(rseg);M(change);M(sum);
    while(scanf("%d",&n)!=EOF)
    {
        s=N;t=-N;
        for(int i=0;i<n;++i)
        {
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            a[i<<1]=rec(x1,x2,y1,1);
            a[i<<1|1]=rec(x1,x2,y2,-1);
            s=min(s,x1);t=max(t,x2);
        }
        sort(a,a+2*n);
        int ans=0,last=0;
        //printf("ok\n");
        for(int i=0;i<2*n;++i)
        {
            updata(1,s,t,a[i].x1,a[i].x2-1,a[i].w);
            ans+=abs(seg[1]-last)+sum[1]*(a[i+1].h-a[i].h);
            last=seg[1];
        }
        printf("%d\n",ans);
    }
}
