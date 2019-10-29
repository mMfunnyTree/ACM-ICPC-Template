#include<iostream>
#include <stdio.h>
#include <math.h>
#define eps 1e-8
using namespace std;
const int MAXN=105;
int m;
double r;
int cCnt,curCnt;//��ʱcCntΪ�����и�õ��Ķ���εĶ��������ݴ涥�����
struct point
{
    double x,y;
};
point points[MAXN],p[MAXN],q[MAXN];//����Ķ���εĶ��㣨˳ʱ�룩��pΪ��������и�õ��Ķ���ζ�������顢�ݴ�˵Ķ���
void getline(point x,point y,double &a,double &b,double   &c){//����x��yȷ��һ��ֱ��a��b��cΪ��ϵ��
    a = y.y - x.y;
    b = x.x - y.x;
    c = y.x * x.y - x.x * y.y;
}
void initial(){
    for(int i = 1; i <= m; ++i)p[i] = points[i];
    p[m+1] = p[1];
    p[0] = p[m];
    cCnt = m;//cCntΪ�����и�õ��Ķ���εĶ������������ʼ��Ϊ����εĶ���ĸ���
}
point intersect(point x,point y,double a,double b,double c){//��x��y�γɵ�ֱ������ֱ֪��a��b��c���Ľ���
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
        if(a*p[i].x + b*p[i].y + c >= 0)q[++curCnt] = p[i];// c���ھ������⣬���ܻ�ƫС��������Щ�㱾Ӧ���Ҳ��û�ڣ�
        //��Ӧ�ý����ж�
        else {
            if(a*p[i-1].x + b*p[i-1].y + c > 0){//���p[i-1]��ֱ�ߵ��Ҳ�Ļ���
                //��p[i],p[i-1]�γɵ�ֱ������ֱ֪�ߵĽ�����Ϊ�˵�һ������(�����Ļ������ھ��ȵ����⣬�˵�������ܻ���������)
                q[++curCnt] = intersect(p[i],p[i-1],a,b,c);
            }
            if(a*p[i+1].x + b*p[i+1].y + c > 0){//ԭ��ͬ��
                q[++curCnt] = intersect(p[i],p[i+1],a,b,c);
            }
        }
    }
    for(int i = 1; i <= curCnt; ++i)p[i] = q[i];//��q���ݴ�ĺ˵Ķ���ת�Ƶ�p��
    p[curCnt+1] = q[1];p[0] = p[curCnt];
    cCnt = curCnt;
}
void solve(){
  //ע�⣺Ĭ�ϵ���˳ʱ�룬�����Ŀ����˳ʱ�룬����������
    initial();
    for(int i = 1; i <= m; ++i){
        double a,b,c;
        getline(points[i],points[i+1],a,b,c);
        cut(a,b,c);
    }
  /*
    ���Ҫ�����ƽ�r���øò��ִ����ϸ�����
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
 /*   //����κ˵����
    double area = 0;
    for(int i = 1; i <= curCnt; ++i)
        area += p[i].x * p[i + 1].y - p[i + 1].x * p[i].y;
    area = fabs(area / 2.0);
 */
}
void GuiZhengHua(){
     //������������ʱ���˳ʱ�룬˳ʱ�����ʱ��
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
        //GuiZhengHua();//���㰴��ʱ�����У����������
        points[m+1]=points[1];
        solve();
        if(cCnt) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
