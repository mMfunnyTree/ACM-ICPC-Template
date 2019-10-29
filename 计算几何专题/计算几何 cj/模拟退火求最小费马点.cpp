#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define N 110
#define inf 10010
struct Point{
    double x,y;
}a[N];
const int fx[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
int n;
double dis(Point p1,Point p2)
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
double get_sum(Point p)
{
    double ans=0;
    for(int i=1;i<=n;++i)
        ans+=dis(a[i],p);
    return ans;
}
double solve()
{
    Point p,p1,p2;
    p.x=p.y=0;
    double ans=get_sum(p);
    int x1=inf,y1=inf,x2=-inf,y2=-inf;
    for(int i=1;i<=n;++i)
    {
        x1=min(x1,(int)a[i].x);
        y1=min(y1,(int)a[i].y);
        x2=max(x2,(int)a[i].x);
        y2=max(y2,(int)a[i].y);
    }
    double diff,minn,d;
    int i;
    srand(0);
    for(int z=1;z<=20;++z)
    {
        p1.x=x1+rand()%(x2-x1+1);
        p1.y=y1+rand()%(y2-y1+1);
        minn=get_sum(p1);
        diff=10000;
        while(diff>0.001)
        {
            for(i=0;i<4;++i)
            {
                p2.x=p1.x+fx[i][0]*diff;
                p2.y=p1.y+fx[i][1]*diff;
                d=get_sum(p2);
                if(d<minn)
                {
                    minn=d;p1=p2;break;
                }
            }
            if(i==4) diff*=0.9;
        }
        if(minn<ans) ans=minn;
    }
    return ans;
}
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=1;i<=n;++i)
            scanf("%lf%lf",&a[i].x,&a[i].y);
        printf("%.0f\n",solve());
    }
    return 0;
}
