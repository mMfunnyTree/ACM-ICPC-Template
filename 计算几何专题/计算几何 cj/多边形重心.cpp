#include <cstdiO>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define N 1000010
struct Point{
    double x,y;
    Point(){}
    Point(double _x,double _y):x(_x),y(_y){}
    void input()
    {
        scanf("%lf%lf",&x,&y);
    }
}P[N];
const double eps=1e-8;
int n;
double cross(Point p0,Point p1,Point p2)
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
//求多边形重心的思路把多边形划分为三角形，算出三角形的重心
//三角形的质量都集中在重心，可以把三角形看成一个点
//然后就变成了求一些离散的质点的重心，套用重心公式即可
Point center(Point P[],int n)
{
    P[n]=P[0];
    double area,sum_area=0,sum_x=0,sum_y=0;
    for(int i=0;i<n;++i)
    {
        area=cross(P[0],P[i],P[i+1])/2;
        sum_area+=area;
        sum_x+=(P[0].x+P[i].x+P[i+1].x)/3*area;
        sum_y+=(P[0].y+P[i].y+P[i+1].y)/3*area;
    }
    return Point(sum_x/sum_area,sum_y/sum_area);
}
int main()
{
    int ca;
    scanf("%d",&ca);
    while(ca--)
    {
        scanf("%d",&n);
        for(int i=0;i<n;++i) P[i].input();
        Point p;
        p=center(P,n);
        printf("%.2f %.2f\n",p.x+eps,p.y+eps);
    }
    return 0;
}
