#include<math.h>
#define MAXN 1000
#define offset 10000
#define eps 1e-8
#define PI acos(-1.0)//3.14159265358979323846
//判断一个数是否为0,是则返回true,否则返回false
#define zero(x)(((x)>0?(x):-(x))<eps)
//返回一个数的符号，正数返回1，负数返回2，否则返回0
#define _sign(x)((x)>eps?1:((x)<-eps?2:0))
struct point
{
    double x,y;
};
struct line
{
    point a,b;
};//直线通过的两个点，而不是一般式的三个系数
//求矢量[p0,p1],[p0,p2]的叉积
//p0是顶点
//若结果等于0，则这三点共线
//若结果大于0，则p0p2在p0p1的逆时针方向
//若结果小于0，则p0p2在p0p1的顺时针方向
double xmult(point p1,point p2,point p0)
{
    return(p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
//计算dotproduct(P1-P0).(P2-P0)
double dmult(point p1,point p2,point p0)
{
    return(p1.x-p0.x)*(p2.x-p0.x)+(p1.y-p0.y)*(p2.y-p0.y);
}
//两点距离
double distance(point p1,point p2)
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
//判三点共线
int dots_inline(point p1,point p2,point p3)
{
    return zero(xmult(p1,p2,p3));
}
//判点是否在线段上,包括端点
int dot_online_in(point p,line l)
{
    return zero(xmult(p,l.a,l.b))&&(l.a.x-p.x)*(l.b.x-p.x)<eps&&(l.a.y-p.y)*(l.b.y-p.y)<eps;
}
//判点是否在线段上,不包括端点
int dot_online_ex(point p,line l)
{
    return dot_online_in(p,l)&&(!zero(p.x-l.a.x)||!zero(p.y-l.a.y))&&(!zero(p.x-l.b.x)||!zero(p.y-l.b.y));
}
//判两点在线段同侧,点在线段上返回0
int same_side(point p1,point p2,line l)
{
    return xmult(l.a,p1,l.b)*xmult(l.a,p2,l.b)>eps;
}
//判两点在线段异侧,点在线段上返回0
int opposite_side(point p1,point p2,line l)
{
    return xmult(l.a,p1,l.b)*xmult(l.a,p2,l.b)<-eps;
}
//判两直线平行
int parallel(line u,line v)
{
    return zero((u.a.x-u.b.x)*(v.a.y-v.b.y)-(v.a.x-v.b.x)*(u.a.y-u.b.y));
}
//判两直线垂直
int perpendicular(line u,line v)
{
    return zero((u.a.x-u.b.x)*(v.a.x-v.b.x)+(u.a.y-u.b.y)*(v.a.y-v.b.y));
}
//判两线段相交,包括端点和部分重合
int intersect_in(line u,line v)
{
    if(!dots_inline(u.a,u.b,v.a)||!dots_inline(u.a,u.b,v.b))
        return!same_side(u.a,u.b,v)&&!same_side(v.a,v.b,u);
    return dot_online_in(u.a,v)||dot_online_in(u.b,v)||dot_online_in(v.a,u)||dot_online_in(v.b,u);
}
//判两线段相交,不包括端点和部分重合
int intersect_ex(line u,line v)
{
    return opposite_side(u.a,u.b,v)&&opposite_side(v.a,v.b,u);
}
//计算两直线交点,注意事先判断直线是否平行!
//线段交点请另外判线段相交(同时还是要判断是否平行!)
point intersection(line u,line v)
{
    point ret=u.a;
    double t=((u.a.x-v.a.x)*(v.a.y-v.b.y)-(u.a.y-v.a.y)*(v.a.x-v.b.x))/((u.a.x-u.b.x)*(v.a.y-v.b.y)-(u.a.y-u.b.y)*(v.a.x-v.b.x));
    ret.x+=(u.b.x-u.a.x)*t;
    ret.y+=(u.b.y-u.a.y)*t;
    return ret;
}
//点到直线上的最近点
point ptoline(point p,line l)
{
    point t=p;
    t.x+=l.a.y-l.b.y,t.y+=l.b.x-l.a.x;
    return intersection(p,t,l.a,l.b);
}
//点到直线距离
double disptoline(point p,line l)
{
    return fabs(xmult(p,l.a,l.b))/distance(l.a,l.b);
}
//点到线段上的最近点
point ptoseg(point p,line l)
{
    point t=p;
    t.x+=l.a.y-l.b.y,t.y+=l.b.x-l.a.x;
    if(xmult(l.a,t,p)*xmult(l.b,t,p)>eps)
        return distance(p,l.a)<distance(p,l.b)?l.a:l.b;
    return intersection(p,t,l.a,l.b);
}
//点到线段距离
double disptoseg(point p,line l)
{
    point t=p;
    t.x+=l.a.y-l.b.y,t.y+=l.b.x-l.a.x;
    if(xmult(l.a,t,p)*xmult(l.b,t,p)>eps)
        return distance(p,l.a)<distance(p,l.b)?distance(p,l.a):distance(p,l.b);
    return fabs(xmult(p,l.a,l.b))/distance(l.a,l.b);
}
struct TPoint
{
    double x,y;
    TPoint operator-(TPoint&a)
    {
        TPoint p1;
        p1.x=x-a.x;
        p1.y=y-a.y;
        return p1;
    }
};

struct TLine
{
    double a,b,c;
};

//求p1关于p2的对称点
TPoint symmetricalPoint(TPoint p1,TPoint p2)
{
    TPoint p3;
    p3.x=2*p2.x-p1.x;
    p3.y=2*p2.y-p1.y;
    return p3;
}
//p点关于直线L的对称点
TPoint symmetricalPointofLine(TPoint p,TLine L)
{
    TPoint p2;
    double d;
    d=L.a*L.a+L.b*L.b;
    p2.x=(L.b*L.b*p.x-L.a*L.a*p.x-2*L.a*L.b*p.y-2*L.a*L.c)/d;
    p2.y=(L.a*L.a*p.y-L.b*L.b*p.y-2*L.a*L.b*p.x-2*L.b*L.c)/d;
    return p2;
}
//求线段所在直线,返回直线方程的三个系数
//两点式化为一般式
TLine lineFromSegment(TPoint p1,TPoint p2)
{
    TLine tmp;
    tmp.a=p2.y-p1.y;
    tmp.b=p1.x-p2.x;
    tmp.c=p2.x*p1.y-p1.x*p2.y;
    return tmp;
}
//求直线的交点
//求直线的交点，注意平行的情况无解，避免RE
TPoint LineInter(TLine l1,TLine l2)
{
    //求两直线得交点坐标
    TPoint tmp;
    double a1=l1.a;
    double b1=l1.b;
    double c1=l1.c;
    double a2=l2.a;
    double b2=l2.b;
    double c2=l2.c;
    //注意这里b1=0
    if(fabs(b1)<eps){
        tmp.x=-c1/a1;
        tmp.y=(-c2-a2*tmp.x)/b2;
    }
    else{
        tmp.x=(c1*b2-b1*c2)/(b1*a2-b2*a1);
        tmp.y=(-c1-a1*tmp.x)/b1;
    }
    //cout<<"交点坐标"<<endl;
    //cout<<a1*tmp.x+b1*tmp.y+c1<<endl;
    //cout<<a2*tmp.x+b2*tmp.y+c2<<endl;
    return tmp;
}
//矢量（点）V以P为顶点逆时针旋转angle(弧度)并放大scale倍
point rotate(point v,point p,double angle,double scale){
    point ret=p;
    v.x-=p.x,v.y-=p.y;
    p.x=scale*cos(angle);
    p.y=scale*sin(angle);
    ret.x+=v.x*p.x-v.y*p.y;
    ret.y+=v.x*p.y+v.y*p.x;
    return ret;
}
//矢量（点）V以P为顶点逆时针旋转angle(弧度)
point rotate(point v,point p,double angle){
    double cs=cos(angle),sn=sin(angle);
    v.x-=p.x,v.y-=p.y;
    p.x+=v.x*cs-v.y*sn;
    p.y+=v.x*sn+v.y*cs;
    return p;
}
