#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
#define lson node<<1,s,mid
#define rson node<<1|1,mid+1,t
#define lnode node<<1
#define rnode node<<1|1
#define M(x) memset(x,0,sizeof(x));
#define N 110
struct rec{
    int l,r,w;
    double x1,x2,h;
    rec(){}
    rec(double a,double b,double c,int d)
    {
        x1=a;x2=b;h=c;w=d;
    }
    bool operator<(const rec &a)const
    {
        return (h<a.h)||(h==a.h)&&(w>a.w);
    }
}a[N*2];
int change[N*8];
double seg[N*8],b[N*2],fx[N*2];
int n;
map<double,int>mp;
void pushup(int node,int s,int t)
{
    if(change[node])
        seg[node]=fx[t+1]-fx[s];
    else if(s!=t)
        seg[node]=seg[lnode]+seg[rnode];
    else seg[node]=0;

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
    int ca=0;
    double x1,x2,y1,y2;
    M(seg);M(change);
    while(scanf("%d",&n),n)
    {
        for(int i=0;i<n;++i)
        {
            scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
            b[i<<1]=x1;b[i<<1|1]=x2;
            a[i<<1]=rec(x1,x2,y1,1);
            a[i<<1|1]=rec(x1,x2,y2,-1);
        }
        sort(b,b+2*n);
        int tot=1;
        mp.clear();
        mp[b[0]]=1;fx[1]=b[0];
        for(int i=1;i<2*n;++i)
            if(b[i]!=b[i+1])
            {
                mp[b[i]]=++tot;
                fx[tot]=b[i];
            }
        for(int i=0;i<2*n;++i)
            a[i].l=mp[a[i].x1],a[i].r=mp[a[i].x2];
        sort(a,a+2*n);
        double ans=0;
        for(int i=0;i<2*n;++i)
        {
            updata(1,1,tot-1,a[i].l,a[i].r-1,a[i].w);
            ans+=seg[1]*(a[i+1].h-a[i].h);
        }
        printf("Test case #%d\nTotal explored area: %.2f\n\n",++ca,ans);
    }
    return 0;
}
