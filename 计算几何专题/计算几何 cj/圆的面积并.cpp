/*
两个剪枝。

首先把所有被内含的圆删掉。

其次我们可以一段一段的求simpson值，累加。

因为中间可能会有空的部分。
*/
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#define N 1100
#define pr pair<double,double>
#define Fabs(x) ((x)>0?(x):-(x))
using namespace std;
const double pi=acos(-1.0);
const double EPS=1e-13;
const double INF=1e100;
struct Point
{
    int x,y;
    friend double dis(Point a,Point b)
    {
        return sqrt((double)(a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
    }
};
struct Circle
{
    Point p;
    int r;
    void read(){scanf("%d%d%d",&p.x,&p.y,&r);}
    friend bool operator <(Circle a,Circle b)
    {
        if(a.p.x-a.r<b.p.x-a.r)
            return a.p.x+a.r<b.p.x+a.r;
        return a.p.x-a.r<b.p.x-a.r;
    }
    pr f(double x)
    {
        if(r<=fabs(p.x-x))  return pr(0,0);
        double t=r*r-(p.x-x)*(p.x-x);
        t=sqrt(t);
        return pr(p.y-t,p.y+t);
    }
}O[N];
bool ban[N];
pr p[N];
int n;
double Cut(double x)
{
    double ret=0,last=-INF;
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
        p[++cnt]=O[i].f(x);
        if(p[cnt]==pr(0,0))
            cnt--;
    }
    sort(p+1,p+cnt+1);
    for(int i=1;i<=cnt;i++)
    {
        if(p[i].first>last)
            ret+=p[i].second-p[i].first,last=p[i].second;
        else if(p[i].second>last)
            ret+=p[i].second-last,last=p[i].second;
    }
    return ret;
}
double Simpson(double l,double r,double mid,double Cl,double Cr,double Cm)
{
    double tCl=Cut((l+mid)/2),tCr=Cut((mid+r)/2);
    double ans=(r-l)*(Cl+Cr+4*Cm)/6,lans=(mid-l)*(Cl+Cm+4*tCl)/6,rans=(r-mid)*(Cr+Cm+4*tCr)/6;
    if(Fabs(lans+rans-ans)<EPS)
        return ans;
    else
        return Simpson(l,mid,(l+mid)/2,Cl,Cm,tCl)+Simpson(mid,r,(mid+r)/2,Cm,Cr,tCr);
}
int main()
{
    int i,j,k;
    double l,r;
    scanf("%d",&n);
    l=INF,r=-INF;
    for(i=1;i<=n;i++)
    {
        O[i].read();
        l=min(l,(double)O[i].p.x-O[i].r);
        r=max(r,(double)O[i].p.x+O[i].r);
    }
    sort(O+1,O+n+1);
    for(i=1;i<=n;i++)
    {
        if(ban[i])  continue;
        for(j=i+1;j<=n;j++)
        {
            if(ban[j])  continue;
            if(dis(O[i].p,O[j].p)+O[j].r<=O[i].r)
                ban[j]=1;
        }
    }
    for(i=1;i<=n;i++)
    {
        if(ban[i])
        {
            swap(ban[i],ban[n]);
            swap(O[i--],O[n--]);
        }
    }
    printf("%.3lf\n",Simpson(l,r,(l+r)/2,0,0,Cut((l+r)/2)));
    return 0;
}