#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define N 20010
struct Point{
    double x,y;
    Point(){}
    Point(double a,double b):x(a),y(b){}
    void f(double &a,double &b)
    {
        a=x;b=y;
    }
    void input()
    {
        scanf("%lf%lf",&x,&y);
    }
    void output()
    {
        printf("%.1f %.1f\n",x,y);
    }
}P[N];
struct Line{
    Point s,t;
    double angle;
    Line(){}
    Line(Point a,Point b):s(a),t(b){}
    void get_angle()
    {
        angle=atan2(t.y-s.y,t.x-s.x);
    }
}L[N];
int n,m;
int que[N];
const double eps=1e-8;
int sig(double x)
{
    if(x>eps) return 1;
    if(x<-eps) return -1;
    return 0;
}
double cross(Point p0,Point p1,Point p2)
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
bool cmp(Line l1,Line l2)
{
    int t=sig(l1.angle-l2.angle);
    if(t>0) return true;
    else if(t<0) return false;
    else if(sig(cross(l1.s,l1.t,l2.s))>0) return true;
    else return false;
}
Point intersect(Line l1,Line l2)
{
    double u=cross(l2.s,l2.t,l1.s),v=cross(l2.t,l2.s,l1.t);
    Point p;
    p.x=(u*l1.t.x+v*l1.s.x)/(u+v);
    p.y=(u*l1.t.y+v*l1.s.y)/(u+v);
    return p;
}
Line Move(Line l,double r)//将直线向内推进r
{
    double k,dx,dy,tx,ty;
    dx=l.t.x-l.s.x;
    dy=l.t.y-l.s.y;
    k=r/sqrt(dx*dx+dy*dy);
    tx=k*dy;ty=-k*dx;
    l.s.x+=tx;l.s.y+=ty;
    l.t.x+=tx;l.t.y+=ty;
    return l;
}
bool judge(Line l,Line l1,Line l2)
{
    Point p=intersect(l1,l2);
    if(sig(cross(l.s,l.t,p))>0) return true;
    else return false;
}
void solve(Line L[],int n)
{
    sort(L+1,L+n+1,cmp);
    int cnt=1;
    for(int i=2;i<=n;++i)
        if(sig(L[i].angle-L[i-1].angle)!=0)
            L[++cnt]=L[i];
    n=cnt;
    int head=1,tail=2;
    que[1]=1;que[2]=2;
    for(int i=3;i<=n;++i)
    {
        while(head<tail&&judge(L[i],L[que[tail]],L[que[tail-1]])) --tail;
        while(head<tail&&judge(L[i],L[que[head]],L[que[head+1]])) ++head;
        que[++tail]=i;
    }
    while(head<tail&&judge(L[que[head]],L[que[tail]],L[que[tail-1]])) --tail;
    while(head<tail&&judge(L[que[tail]],L[que[head]],L[que[head+1]])) ++head;
    m=0;
    if(head==tail) return;
    que[tail+1]=que[head];
    for(int i=head;i<=tail;++i)
        P[++m]=intersect(L[que[i]],L[que[i+1]]);
}
double area(Point P[],int n)
{
    P[n+1]=P[1];
    double ans=0;
    for(int i=1;i<=n;++i)
        ans+=cross(P[1],P[i],P[i+1]);
    return -ans/2;
}
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        L[1]=Line(Point(0,0),Point(0,10000));L[1].get_angle();
        L[2]=Line(Point(0,10000),Point(10000,10000));L[2].get_angle();
        L[3]=Line(Point(10000,10000),Point(10000,0));L[3].get_angle();
        L[4]=Line(Point(10000,0),Point(0,0));L[4].get_angle();
        for(int i=5;i<=n+4;++i)
        {
            L[i].t.input();L[i].s.input();L[i].get_angle();
        }
        solve(L,n+4);
        printf("%.1f\n",area(P,m)+eps);
    }
    return 0;
}
