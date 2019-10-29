#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 510
const double eps=1e-8;
struct Point{
    double x,y;
}a[N];
int n;
double dis(Point p1,Point p2)
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
Point circumcenter(Point p1,Point p2,Point p3)//求三角形外心
{
    Point p;
    double a1=p2.x-p1.x,b1=p2.y-p1.y,c1=(a1*a1+b1*b1)/2;
    double a2=p3.x-p1.x,b2=p3.y-p1.y,c2=(a2*a2+b2*b2)/2;
    double d=a1*b2-a2*b1;
    p.x=p1.x+(c1*b2-c2*b1)/d;
    p.y=p1.y+(a1*c2-a2*c1)/d;
    return p;
}
void min_cover_circle(Point p[],int n,Point &c,double &r)
{
    random_shuffle(a+1,a+n+1);//随机化序列
    c=a[1];r=0;
    for(int i=2;i<=n;++i)
        if(dis(p[i],c)>r+eps)//第一个点
        {
            c=p[i];r=0;
            for(int j=1;j<i;++j)
                if(dis(p[j],c)>r+eps)//第二个点
                {
                    c.x=(p[i].x+p[j].x)/2;
                    c.y=(p[i].y+p[j].y)/2;
                    r=dis(p[i],c);
                    for(int k=1;k<j;++k)
                        if(dis(p[k],c)>r+eps)//第三个点
                        {
                            c=circumcenter(p[i],p[j],p[k]);
                            r=dis(p[i],c);
                        }
                }
        }
}
int main()
{
    Point c;
    double r;
    while(scanf("%d",&n),n)
    {
        for(int i=1;i<=n;++i)
            scanf("%lf%lf",&a[i].x,&a[i].y);
        min_cover_circle(a,n,c,r);
        printf("%.2f %.2f %.2f\n",c.x,c.y,r);
    }
}
