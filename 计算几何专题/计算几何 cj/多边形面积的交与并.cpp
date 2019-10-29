/* 
 * 多边形的交，多边形的边一定是要按逆时针方向给出 
 * 还要判断是凸包还是凹包，调用相应的函数 
 * 面积并，只要和面积减去交即可 
 */  
#include <bits/stdc++.h>  
using namespace std;  
  
const int maxn = //300;  
const double eps = 1e-8;  
int dcmp(double x)  
{  
    if(x > eps) return 1;  
    return x < -eps ? -1 : 0;  
}  
struct Point  
{  
    double x, y;  
};  
double cross(Point a,Point b,Point c) ///叉积  
{  
    return (a.x-c.x)*(b.y-c.y)-(b.x-c.x)*(a.y-c.y);  
}  
Point intersection(Point a,Point b,Point c,Point d)  
{  
    Point p = a;  
    double t =((a.x-c.x)*(c.y-d.y)-(a.y-c.y)*(c.x-d.x))/((a.x-b.x)*(c.y-d.y)-(a.y-b.y)*(c.x-d.x));  
    p.x +=(b.x-a.x)*t;  
    p.y +=(b.y-a.y)*t;  
    return p;  
}  
//计算多边形面积  
double PolygonArea(Point p[], int n)  
{  
    if(n < 3) return 0.0;  
    double s = p[0].y * (p[n - 1].x - p[1].x);  
    p[n] = p[0];  
    for(int i = 1; i < n; ++ i)  
        s += p[i].y * (p[i - 1].x - p[i + 1].x);  
    return fabs(s * 0.5);  
}  
double CPIA(Point a[], Point b[], int na, int nb)//ConvexPolygonIntersectArea  
{  
    Point p[20], tmp[20];  
    int tn, sflag, eflag;  
    a[na] = a[0], b[nb] = b[0];  
    memcpy(p,b,sizeof(Point)*(nb + 1));  
    for(int i = 0; i < na && nb > 2; i++)  
    {  
        sflag = dcmp(cross(a[i + 1], p[0],a[i]));  
        for(int j = tn = 0; j < nb; j++, sflag = eflag)  
        {  
            if(sflag>=0) tmp[tn++] = p[j];  
            eflag = dcmp(cross(a[i + 1], p[j + 1],a[i]));  
            if((sflag ^ eflag) == -2)  
                tmp[tn++] = intersection(a[i], a[i + 1], p[j], p[j + 1]); ///求交点  
        }  
        memcpy(p, tmp, sizeof(Point) * tn);  
        nb = tn, p[nb] = p[0];  
    }  
    if(nb < 3) return 0.0;  
    return PolygonArea(p, nb);  
}  
double SPIA(Point a[], Point b[], int na, int nb)///SimplePolygonIntersectArea 调用此函数  
{  
    int i, j;  
    Point t1[4], t2[4];  
    double res = 0, num1, num2;  
    a[na] = t1[0] = a[0], b[nb] = t2[0] = b[0];  
    for(i = 2; i < na; i++)  
    {  
        t1[1] = a[i-1], t1[2] = a[i];  
        num1 = dcmp(cross(t1[1], t1[2],t1[0]));  
        if(num1 < 0) swap(t1[1], t1[2]);  
        for(j = 2; j < nb; j++)  
        {  
            t2[1] = b[j - 1], t2[2] = b[j];  
            num2 = dcmp(cross(t2[1], t2[2],t2[0]));  
            if(num2 < 0) swap(t2[1], t2[2]);  
            res += CPIA(t1, t2, 3, 3) * num1 * num2;  
        }  
    }  
    return res;  
}  
Point p1[maxn], p2[maxn];  
int n1, n2;  
int main()  
{  
    while(cin>>n1>>n2)  
    {  
        for(int i = 0; i < n1; i++) scanf("%lf%lf", &p1[i].x, &p1[i].y);  
        for(int i = 0; i < n2; i++) scanf("%lf%lf", &p2[i].x, &p2[i].y);  
        double Area = SPIA(p1, p2, n1, n2);  
    }  
    return 0;  
}  