#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define N 50010
struct Point{
    double x,y;
    Point(){}
    Point(double _x,double _y):x(_x),y(_y){}
    bool operator<(const Point &a)const
    {
        return x<a.x||x==a.x&&y<a.y;
    }
    void input()
    {
        scanf("%lf%lf",&x,&y);
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
    double ans=0;
    P[n]=P[0];
    for(int i=0;i<n;++i)
        ans+=cross(P[0],P[i],P[i+1]);
    return -ans/2;
}
void Reverse(Point P[],int n)
{
    for(int i=0;i<(n+1)/2;++i)
        swap(P[i],P[n-i-1]);
}
double dis2(Point p1,Point p2)
{
    return (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y);
}
double solve(Point P[],int n)
{
    int i1=0,i2=0;
    P[n]=P[0];
    for(int i=1;i<n;++i)
    {
        if(P[i].y>P[i1].y) i1=i;
        if(P[i].y<P[i2].y) i2=i;
    }
    double ans=0,tmp;
    for(int i=0;i<n;++i)
    {
        while(tmp=cross(P[i1],P[i2],P[i1+1])-cross(P[i1],P[i2+1],P[i1+1])<-eps)
            i2=(i2+1)%n;
        ans=max(ans,max(dis2(P[i1],P[i2]),dis2(P[i1+1],P[i2+1])));
        i1=(i1+1)%n;
    }
    return ans;
}
void Graham()
{
    sort(P,P+n);
    int top=1;
    sta[0]=P[0];sta[1]=P[1];
    for(int i=2;i<n;++i)
    {
        while(top&&cross(sta[top-1],sta[top],P[i])>-eps) --top;
        sta[++top]=P[i];
    }
    int k=top;
    for(int i=n-2;i>=0;--i)
    {
        while(top>k&&cross(sta[top-1],sta[top],P[i])>-eps) --top;
        sta[++top]=P[i];
    }
    if(top) top--;
    for(int i=0;i<=top;++i) P[i]=sta[i];
    n=top+1;
}
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=0;i<n;++i) P[i].input();
        if(area(P,n)<0) Reverse(P,n);
        Graham();
        printf("%.0f\n",solve(P,n));
    }
    return 0;
}
