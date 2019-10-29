#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define N 50010
const double eps=1e-12;
struct Point{
    double x,y,angle;
    Point(){}
    Point(double _x,double _y):x(_x),y(_y){}
    void input()
    {
        scanf("%lf%lf",&x,&y);
    }
    void output()
    {
        printf("%.5f %.5f\n",x+eps,y+eps);
    }
    void f(double &a,double &b)
    {
        a=x;b=y;
    }
    bool operator<(const Point &a)const
    {
        return y<a.y||y==a.y&&x<a.x;
    }
    Point operator-(const Point &a)const
    {
        return Point(x-a.x,y-a.y);
    }
    double operator*(const Point &a)const
    {
        return x*a.x+y*a.y;
    }
    bool operator!=(const Point &a)const
    {
        return x!=a.x||y!=a.y;
    }
    Point operator+(const Point &a)const
    {
        return Point(x+a.x,y+a.y);
    }
}P[N],sta[N],Q[5];
//Q数组记录最小矩形的四个点
int n;
const double inf=1e20;
double cross(Point p0,Point p1,Point p2)
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
void Graham()
{
    sort(P,P+n);
    int cnt=0;
    for(int i=1;i<n;++i)
        if(P[i]!=P[i-1]) P[++cnt]=P[i];
    int top=1;
    sta[0]=P[0];sta[1]=P[1];
    for(int i=2;i<=cnt;++i)
    {
        while(top&&cross(sta[top-1],sta[top],P[i])>-eps) --top;
        sta[++top]=P[i];
    }
    int k=top;
    for(int i=cnt-1;i>=0;--i)
    {
        while(top>k&&cross(sta[top-1],sta[top],P[i])>-eps) --top;
        sta[++top]=P[i];
    }
    if(top) --top;
    for(int i=0;i<=top;++i) P[i]=sta[i];
    n=top+1;
}
double dis(Point p1,Point p2)
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
double dis_lp(Point p1,Point p2,Point p3)
{
    return fabs(cross(p1,p2,p3))/dis(p1,p2);
}
Point intersect(Point p1,Point p2,Point p3)//过点p3与向量p1p2垂直的向量与直线p1p2的交点
{
    double x1,x2,x3,y1,y2,y3,d,dx,dy,a1,b1,c1,a2,b2,c2;
    p1.f(x1,y1);p2.f(x2,y2);p3.f(x3,y3);
    a1=x2-x1;b1=y2-y1;c1=x3*(x2-x1)+y3*(y2-y1);
    a2=y2-y1;b2=x1-x2;c2=x1*y2-x2*y1;
    d=a1*b2-a2*b1;dx=c1*b2-c2*b1;dy=a1*c2-a2*c1;
    return Point(dx/d,dy/d);
}
double solve()
{
    P[n]=P[0];
    int i1=0,i2=0;
    for(int i=1;i<n;++i)
    {
        if(P[i].y<P[i1].y) i1=i;
        if(P[i].y>P[i2].y) i2=i;
    }
    int i3=i1+1,i4=i2+1;
    double ans=inf,a,h;
    for(int i=0;i<n;++i)
    {
        while(cross(P[i1],P[i2],P[i1+1])-cross(P[i1],P[i2+1],P[i1+1])<-eps)
            i2=(i2+1)%n;
        h=dis_lp(P[i1],P[i1+1],P[i2]);
        while((P[i1+1]-P[i1])*(P[i3+1]-P[i3])>eps) i3=(i3+1)%n;
        while((P[i1+1]-P[i1])*(P[i4+1]-P[i4])<-eps) i4=(i4+1)%n;
        a=fabs((P[i1+1]-P[i1])*(P[i3]-P[i4]))/dis(P[i1+1],P[i1]);
        if(ans>a*h)
        {
            ans=a*h;
            Q[0]=intersect(P[i1],P[i1+1],P[i3]);
            Q[1]=intersect(P[i1],P[i1+1],P[i4]);
            Point p=P[i2]+(P[i1]-P[i1+1]);
            Q[2]=intersect(P[i2],p,P[i3]);
            Q[3]=intersect(P[i2],p,P[i4]);
        }
        i1=(i1+1)%n;
    }
    return ans;
}
bool cmp(Point p1,Point p2)
{
    return p1.angle<p2.angle;
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;++i) P[i].input();
    Graham();
    if(n==1)
    {
        printf("%.5f\n",0);
        for(int i=1;i<=4;++i)
            P[0].output();
    }
    else if(n==2)
    {
        printf("%.5f\n",0);
        sort(P,P+1);
        P[0].output();P[0].output();
        P[1].output();P[1].output();
    }
    else
    {
        printf("%.5f\n",solve()+eps);
        sort(Q,Q+4);
        for(int i=1;i<4;++i)
            Q[i].angle=atan2(Q[i].y-Q[0].y,Q[i].x-Q[0].x);
        sort(Q+1,Q+4,cmp);
        for(int i=0;i<4;++i)
            Q[i].output();
    }
}
