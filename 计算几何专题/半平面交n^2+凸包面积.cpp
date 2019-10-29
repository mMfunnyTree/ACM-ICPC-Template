#include<cmath>
#include<cstdio>
#include<vector>

using namespace std;
const double eps = 1e-8;
const double PI = acos(-1);
const int N =1e5;

int dcmp(double x) {if(fabs(x) < eps) return 0;else return x < 0?-1:1;}
struct point{
    double x,y;
    point operator - (point p){return {x-p.x,y-p.y};}
    bool friend operator == (point a, point b) { return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;}
}st[N],g;
struct Polygon{
    point p[N];
    int sz;
}r,t;
double cross3(point p0,point p1,point p2)  {return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);}

void cut(point a,point b){
    r.p[r.sz]=r.p[0];
    t.sz=0;
    for(int i=0;i<r.sz;i++) {
        double s1,s2;
        double d1=dcmp(s1=cross3(r.p[i],a,b));
        double d2=dcmp(s2=cross3(r.p[i+1],a,b));
        if(d1>=0) t.p[t.sz++]=r.p[i];
        if(d1*d2<0){
            g.x=(s2*r.p[i].x-s1*r.p[i+1].x)/(s2-s1);
            g.y=(s2*r.p[i].y-s1*r.p[i+1].y)/(s2-s1);
            t.p[t.sz++]=g;
        }
    }
    for(int i=0;i<t.sz;i++)
        r.p[i]=t.p[i];
    r.sz=t.sz;
}
double PolygonArea() {
    int n = r.sz;
    double area = 0;
    for(int i = 1; i < n - 1; i++)
        area += fabs(cross3(r.p[0],r.p[i],r.p[i+1]));
    return area/2;
}
int main(){
    int n;
    double x,y;
    scanf("%d",&n);
    n*=2;
    for(int i=0;i<n;i++) {
        scanf("%lf%lf",&x,&y);
        st[i]={x,y};
    }
    r.sz=4;
    r.p[0]={0,0};
    r.p[1]={1e4,0};
    r.p[2]={1e4,1e4};
    r.p[3]={0,1e4};
    for(int i=0;i<n;i+=2)
        cut(st[i],st[i+1]);
    printf("%.1f\n",PolygonArea());
}
