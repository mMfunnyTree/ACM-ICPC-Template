#include<iostream>
#include <stdio.h>
#include <math.h>
#define eps 1e-8
using namespace std;
const int MAXN=105;
int m;
double r;
int cCnt,curCnt;//此时cCnt为最终切割得到的多边形的顶点数、暂存顶点个数
struct point
{
    double x,y;
};
point points[MAXN],p[MAXN],q[MAXN];//读入的多边形的顶点（顺时针）、p为存放最终切割得到的多边形顶点的数组、暂存核的顶点
void getline(point x,point y,double &a,double &b,double   &c){//两点x、y确定一条直线a、b、c为其系数
    a = y.y - x.y;
    b = x.x - y.x;
    c = y.x * x.y - x.x * y.y;
}
void initial(){
    for(int i = 1; i <= m; ++i)p[i] = points[i];
    p[m+1] = p[1];
    p[0] = p[m];
    cCnt = m;//cCnt为最终切割得到的多边形的顶点数，将其初始化为多边形的顶点的个数
}
point intersect(point x,point y,double a,double b,double c){//求x、y形成的直线与已知直线a、b、c、的交点
    double u = fabs(a * x.x + b * x.y + c);
    double v = fabs(a * y.x + b * y.y + c);
    point pt;
    pt.x=(x.x * v + y.x * u) / (u + v);
    pt.y=(x.y * v + y.y * u) / (u + v);
    return  pt;
}
void cut(double a,double b ,double c){
    curCnt = 0;
    for(int i = 1; i <= cCnt; ++i){
        if(a*p[i].x + b*p[i].y + c >= 0)q[++curCnt] = p[i];// c由于精度问题，可能会偏小，所以有些点本应在右侧而没在，
        //故应该接着判断
        else {
            if(a*p[i-1].x + b*p[i-1].y + c > 0){//如果p[i-1]在直线的右侧的话，
                //则将p[i],p[i-1]形成的直线与已知直线的交点作为核的一个顶点(这样的话，由于精度的问题，核的面积可能会有所减少)
                q[++curCnt] = intersect(p[i],p[i-1],a,b,c);
            }
            if(a*p[i+1].x + b*p[i+1].y + c > 0){//原理同上
                q[++curCnt] = intersect(p[i],p[i+1],a,b,c);
            }
        }
    }
    for(int i = 1; i <= curCnt; ++i)p[i] = q[i];//将q中暂存的核的顶点转移到p中
    p[curCnt+1] = q[1];p[0] = p[curCnt];
    cCnt = curCnt;
}
void solve(){
  //注意：默认点是顺时针，如果题目不是顺时针，规整化方向
    initial();
    for(int i = 1; i <= m; ++i){
        double a,b,c;
        getline(points[i],points[i+1],a,b,c);
        cut(a,b,c);
    }
  /*
    如果要向内推进r，用该部分代替上个函数
    for(int i = 1; i <= m; ++i){
        Point ta, tb, tt;
        tt.x = points[i+1].y - points[i].y;
        tt.y = points[i].x - points[i+1].x;
        double k = r / sqrt(tt.x * tt.x + tt.y * tt.y);
        tt.x = tt.x * k;
        tt.y = tt.y * k;
        ta.x = points[i].x + tt.x;
        ta.y = points[i].y + tt.y;
        tb.x = points[i+1].x + tt.x;
        tb.y = points[i+1].y + tt.y;
        double a,b,c;
        getline(ta,tb,a,b,c);
        cut(a,b,c);
    }*/
 /*   //多边形核的面积
    double area = 0;
    for(int i = 1; i <= curCnt; ++i)
        area += p[i].x * p[i + 1].y - p[i + 1].x * p[i].y;
    area = fabs(area / 2.0);
 */
}
void GuiZhengHua(){
     //规整化方向，逆时针变顺时针，顺时针变逆时针
    for(int i = 1; i <=m; i ++)q[i]=points[m-i+1];
    for(int i=1;i<=m;i++)points[i]=q[i];
}
int main()
{
    int ca;
    scanf("%d",&ca);
    while(ca--)
    {
        scanf("%d",&m);
        int i;
        for(i=1;i<=m;i++)
            scanf("%lf%lf",&points[i].x,&points[i].y);
        //GuiZhengHua();//若点按逆时针排列，则调整方向
        points[m+1]=points[1];
        solve();
        if(cCnt) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
