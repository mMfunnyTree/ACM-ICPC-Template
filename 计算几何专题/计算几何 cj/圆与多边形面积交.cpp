#include<algorithm>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<iostream>
using namespace std;
struct Point{
    double x,y;
    Point(){}
    Point(double x0,double y0):x(x0),y(y0){}
}p[200005];
struct Line{
    Point s,e;
    Line(){}
    Line(Point s0,Point e0):s(s0),e(e0){}
};
int n;
double R;
const double eps=1e-8;
const double Pi=acos(-1);
double sgn(double x){
    if (x>eps) return 1.0;
    if (x<-eps) return -1.0;
    return 0;
}
Point operator *(Point p1,double x){
    return Point(p1.x*x,p1.y*x);
}
Point operator /(Point p1,double x){
    return Point(p1.x/x,p1.y/x);
}
double operator /(Point p1,Point p2){
    return p1.x*p2.x+p1.y*p2.y;
}
double operator *(Point p1,Point p2){
    return p1.x*p2.y-p1.y*p2.x;
}
Point operator +(Point p1,Point p2){
    return Point(p1.x+p2.x,p1.y+p2.y);
}
Point operator -(Point p1,Point p2){
    return Point(p1.x-p2.x,p1.y-p2.y);
}
double dis(Point p1){
    return sqrt(p1.x*p1.x+p1.y*p1.y);
}
double dis(Point p1,Point p2){
    return dis(Point(p1.x-p2.x,p1.y-p2.y));
}
double sqr(double x){
    return x*x;
}
double dist_line(Line p){
    double A,B,C,dist;
    A=p.s.y-p.e.y;
    B=p.s.x-p.e.x;
    C=p.s.x*p.e.y-p.s.y*p.e.x;
    dist=fabs(C)/sqrt(sqr(A)+sqr(B));
    return dist;
}
double get_cos(double a,double b,double c){
    return (b*b+c*c-a*a)/(2*b*c);
}
double get_angle(Point p1,Point p2){
    if (!sgn(dis(p1))||!sgn(dis(p2))) return 0.0;
    double A,B,C;
    A=dis(p1);
    B=dis(p2);
    C=dis(p1,p2);
    if (C<=eps) return 0.0;
    return acos(get_cos(C,A,B));
}
Point get_point(Point p){
    double T=sqr(p.x)+sqr(p.y);
    return Point(sgn(p.x)*sqrt(sqr(p.x)/T),sgn(p.y)*sqrt(sqr(p.y)/T));
}
double S(Point p1,Point p2,Point p3){
    return fabs((p2-p1)*(p3-p1))/2;
}
double work(Point p1,Point p2,Point O){
    p1=p1-O;p2=p2-O;
    O=Point(0,0);
    double f=sgn(p1*p2),res=0;
    if (!sgn(f)||!sgn(dis(p1))||!sgn(dis(p2))) return 0.0;
    double l=dist_line(Line(p1,p2));
    double a=dis(p1);
    double b=dis(p2);
    double c=dis(p1,p2);
    if (a<=R&&b<=R){
        return fabs(p1*p2)/2.0*f;
    }
    if (a>=R&&b>=R&&l>=R){
        double ang=get_angle(p1,p2);
        return fabs((ang/(2.0))*(R*R))*f;
    }
    if (a>=R&&b>=R&&l<=R&&(get_cos(a,b,c)<=0||get_cos(b,a,c)<=0)){
        double ang=get_angle(p1,p2);
        return fabs((ang/(2.0))*(R*R))*f;
    }
    if (a>=R&&b>=R&&l<=R&&(get_cos(a,b,c)>0&&get_cos(b,a,c)>0)){
        double dist=dist_line(Line(p1,p2));
        double len=sqrt(sqr(R)-sqr(dist))*2.0;
        double ang1=get_angle(p1,p2);
        double cos2=get_cos(len,R,R);
        res+=fabs(len*dist/2.0);
        double ang2=ang1-acos(cos2);
        res+=fabs((ang2/(2))*(R*R));
        return res*f;
    }
    if ((a>=R&&b<R)||(a<R&&b>=R)){
        if (b>a) swap(a,b),swap(p1,p2);
        double T=sqr(p1.x-p2.x)+sqr(p1.y-p2.y);
        Point u=Point(sgn(p1.x-p2.x)*sqrt(sqr(p1.x-p2.x)/T),sgn(p1.y-p2.y)*sqrt(sqr(p1.y-p2.y)/T));
        double dist=dist_line(Line(p1,p2));
        double len=sqrt(R*R-dist*dist);
        double len2=sqrt(sqr(dis(p2))-sqr(dist));
        if (fabs(dis(p2+u*len2)-dist)<=eps) len+=len2;
        else len-=len2;
        Point p=p2+u*len;
        res+=S(O,p2,p);
        double ang=get_angle(p1,p);
        res+=fabs((ang/2.0)*R*R);
        return res*f;
    }
    return 0;
}
int main(){
    Point O=Point(0,0);
    while (scanf("%lf",&R)!=EOF){
        scanf("%d",&n);
        for (int i=1;i<=n;i++)//顺时针逆时针均可！！！
         scanf("%lf%lf",&p[i].x,&p[i].y);
        p[n+1]=p[1];
        double ans=0;
        for (int i=1;i<=n;i++)
         ans+=work(p[i],p[i+1],O);
        ans=fabs(ans);
        printf("%.2f\n",ans);
    }
}
