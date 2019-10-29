#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define N 100010
const double inf=1e20;
struct Point{
    double x,y;
}a[N];
int tmp[N];
int n;
bool cmpxy(Point &p1,Point &p2)
{
    return (p1.x<p2.x)||(p1.x==p2.x&&p1.y<p2.y);
}
bool cmpy(int i,int j)
{
    return a[i].y<a[j].y;
}
double dis(Point &p1,Point &p2)
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
double closest_pair(int l,int r)
{
    double d=inf;
    if(l==r) return d;
    if(l+1==r) return dis(a[l],a[r]);
    int mid=l+r>>1;
    double d1=closest_pair(l,mid);
    double d2=closest_pair(mid+1,r);
    d=min(d1,d2);
    int k=0;
    for(int i=l;i<=r;++i)
        if(fabs(a[i].x-a[mid].x)<=d)
            tmp[++k]=i;
    sort(tmp+1,tmp+k+1,cmpy);
    for(int i=1;i<k;++i)
        for(int j=i+1;j<=k&&a[tmp[j]].y-a[tmp[i]].y<d;++j)
            d=min(d,dis(a[tmp[i]],a[tmp[j]]));
    return d;
}
int main()
{
    while(scanf("%d",&n),n)
    {
        for(int i=1;i<=n;++i)
            scanf("%lf%lf",&a[i].x,&a[i].y);
        sort(a+1,a+n+1,cmpxy);
        double ans=closest_pair(1,n);
        if(ans<=10000) printf("%.4f\n",ans);
        else printf("INFINITY\n");
    }
    return 0;
}
