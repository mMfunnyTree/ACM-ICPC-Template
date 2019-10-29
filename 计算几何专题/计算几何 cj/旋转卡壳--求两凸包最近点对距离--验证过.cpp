/*
---------------
点集编号从0开始
---------------
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define N 10010
struct Point{
    double x,y;
    Point(){}
    Point(double _x,double _y):x(_x),y(_y){}
    void input()
    {
        scanf("%lf%lf",&x,&y);
    }
}P[N],Q[N],b[N];
int n,m;
const double eps=1e-8;
const double inf=1e20;
double cross(Point p0,Point p1,Point p2)
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
double dot(Point p0,Point p1,Point p2)
{
    return (p1.x-p0.x)*(p2.x-p0.x)+(p1.y-p0.y)*(p2.y-p0.y);
}
double area(Point a[],int n)
{
    double ans=0;
    a[n]=a[0];
    for(int i=0;i<n;++i)
        ans+=cross(a[0],a[i],a[i+1]);
    return ans/2.0;
}
void Reverse(Point a[],int n)
{
    for(int i=0;i<n;++i) b[i]=a[i];
    for(int i=0;i<n;++i) a[i]=b[n-i-1];
}
double dis(Point p1,Point p2)
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
//计算p3到线段p1,p2的最短距离
double get_dis(Point p1,Point p2,Point p3)
{
    if(dis(p1,p2)<eps) return dis(p1,p3);
    if(dot(p1,p2,p3)<-eps) return dis(p1,p3);
    if(dot(p2,p1,p3)<-eps) return dis(p2,p3);
    return fabs(cross(p1,p2,p3))/dis(p1,p2);
}
//计算线段p1,p2到线段p3,p4的最短距离
double get_dis(Point p1,Point p2,Point p3,Point p4)
{
    return min(get_dis(p1,p2,p3),get_dis(p1,p2,p4));
}
//旋转卡壳
double solve(Point P[],Point Q[],int n,int m)
{
    int yP=0,yQ=0;
    //找出P中y最小的点和Q中y最大的点
    for(int i=0;i<n;++i)
        if(P[i].y<P[yP].y) yP=i;
    for(int i=0;i<m;++i)
        if(Q[i].y>Q[yQ].y) yQ=i;
    P[n]=P[0];Q[m]=Q[0];
    double tmp,ans=inf;
    for(int i=0;i<n;++i)
    {
        while(tmp=cross(P[yP+1],Q[yQ+1],P[yP])-cross(P[yP+1],Q[yQ],P[yP])>eps)
            yQ=(yQ+1)%m;
        if(tmp<-eps) ans=min(ans,get_dis(P[yP],P[yP+1],Q[yQ]));
        else ans=min(ans,get_dis(P[yP],P[yP+1],Q[yQ],Q[yQ+1]));
        yP=(yP+1)%n;
    }
    return ans;
}
int main()
{
    while(scanf("%d%d",&n,&m),n)
    {
        for(int i=0;i<n;++i) P[i].input();
        for(int i=0;i<m;++i) Q[i].input();
        //将P和Q按顺时针排列
        if(area(P,n)<-eps) Reverse(P,n);
        if(area(Q,m)<-eps) Reverse(Q,m);
        //求出分别绕两个多边形旋转的最小值
        printf("%.5f\n",min(solve(P,Q,n,m),solve(Q,P,m,n)));
    }
    return 0;
}
