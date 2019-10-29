#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define N 1010
struct Point{
    double x,y;
    Point(){}
    Point(double _x,double _y):x(_x),y(_y){}
    bool operator<(const Point &p)const
    {
        return x<p.x||x==p.x&&y<p.y;
    }
}P[N],sta[N];
int n;
const double eps=1e-8;
double cross(Point p0,Point p1,Point p2)
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
double area(Point P[],int n)
{
    P[n+1]=P[1];
    double ans=0;
    for(int i=1;i<=n;++i)
        ans+=cross(P[1],P[i],P[i+1]);
    return -ans/2;
}
void Reverse(Point P[],int n)
{
    for(int i=1;i<=(n+1)/2;++i)
        swap(P[i],P[n-i+1]);
}
void Graham()
{
    sort(P+1,P+n+1);
    int top=2;
    sta[1]=P[1];sta[2]=P[2];
    for(int i=3;i<=n;++i)
    {
        while(top>1&&cross(sta[top-1],sta[top],P[i])>-eps) --top;
        sta[++top]=P[i];
    }
    int k=top;
    for(int i=n-1;i>0;--i)
    {
        while(top>k&&cross(sta[top-1],sta[top],P[i])>-eps) --top;
        sta[++top]=P[i];
    }
    if(top>1) --top;
    for(int i=1;i<=top;++i) P[i]=sta[i];
    n=top;
}
double dis(Point p1,Point p2)
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
int main()
{
    double r;
    while(scanf("%d%lf",&n,&r)!=EOF)
    {
        for(int i=1;i<=n;++i)
            scanf("%lf%lf",&P[i].x,&P[i].y);
        if(area(P,n)) Reverse(P,n);
        Graham();
        double len=0;
        P[n+1]=P[1];
        for(int i=1;i<=n;++i)
            len+=dis(P[i],P[i+1]);
        len+=acos(-1)*r*2;
        printf("%.0f\n",len);
    }
    return 0;
}
