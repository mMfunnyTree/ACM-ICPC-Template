#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <set>
#include <utility>
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
bool f[N];
const double eps=1e-8;
double cross(Point p0,Point p1,Point p2)
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
double solve()
{
    if(n<3) return 0;
    double ans=0;
    int i=0,j,k;
    P[n]=P[0];
    for(int i=0;i<n;++i)
    {
        j=(i+1)%n;k=(j+1)%n;
        while(i!=k)
        {
            while(j!=k&&cross(P[i],P[k],P[j])-cross(P[i],P[k],P[j+1])<-eps)
                j=(j+1)%n;
            ans=max(ans,cross(P[i],P[k],P[j])/2);
            k=(k+1)%n;
        }
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
    if(top) --top;
    for(int i=0;i<=top;++i) P[i]=sta[i];
    n=top+1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(scanf("%d",&n),n!=-1)
    {
        for(int i=0;i<n;++i) P[i].input();
        Graham();
        printf("%.2f\n",solve());
    }
    return 0;
}
