#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define N 1010
const double eps=1e-8;
const double inf=1e20;
struct TPoint{
    double x,y,z;
    TPoint(){}
    TPoint(double _x,double _y,double _z):x(_x),y(_y),z(_z){}
    TPoint operator-(const TPoint &p)const//向量相减
    {
        return TPoint(x-p.x,y-p.y,z-p.z);
    }
    TPoint operator^(const TPoint &p)const//向量叉积
    {
        return TPoint(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);
    }
    double operator*(const TPoint &p)const//向量点积
    {
        return x*p.x+y*p.y+z*p.z;
    }
    TPoint operator+(const TPoint &p)const//向量加法，求重心是调用
    {
        return TPoint(x+p.x,y+p.y,z+p.z);
    }
    TPoint operator/(const double k)const//向量除一个数，求重心是调用
    {
        return TPoint(x/k,y/k,z/k);
    }
    TPoint operator*(const double k)const//向量乘一个数，求重心时调用
    {
        return TPoint(x*k,y*k,z*k);
    }
    void input()
    {
        scanf("%lf%lf%lf",&x,&y,&z);
    }
    void output()//用来测试
    {
        printf("%.3f %.3f %.3f\n",x,y,z);
    }
};
double dis(TPoint p1,TPoint p2)//求重心时调用
{
    TPoint p=p1-p2;
    return sqrt(p1.x*p2.x+p1.y*p2.y+p1.z*p2.z);
}
struct Fac{
    int a,b,c;//凸包一个面上的三个点的编号
    bool ok;//该面是否是最终凸包中的面
};
struct T3dhull{
    int n;//初始点数
    TPoint P[N];//初始点
    int trianglecnt;//凸包上三角形数
    Fac tri[N*8];//凸包三角形
    int belong[N][N];//点i到点j是属于哪个面
    double vlen(TPoint p)//向量长度
    {
        return sqrt(p.x*p.x+p.y*p.y+p.z*p.z);
    }
    double volume(TPoint a,TPoint b,TPoint c,TPoint p)//四面体有向体积
    {
        return ((b-a)^(c-a))*(p-a)/6;
    }
    double ptoplane(TPoint &p,Fac &f)//点在面同的正向
    {
        TPoint p1=P[f.b]-P[f.a],p2=P[f.c]-P[f.a],p3=p-P[f.a];
        return (p1^p2)*p3;
    }
    void deal(int p,int a,int b)
    {
        int f=belong[a][b];//与当前面（cnt）共边（ab）的那个面
        Fac add;
        if(tri[f].ok)
        {
            //如果p点能看到面f，则继续深度搜索f的三条边，以便更新新的凸包面
            if(ptoplane(P[p],tri[f])>eps) dfs(p,f);
            else//否则p点只看到cnt面，看不到f面，则p点和a、b点组成一个三角形
            {
                add.a=b;add.b=a;add.c=p;add.ok=1;
                belong[p][b]=belong[b][a]=belong[a][p]=trianglecnt;
                tri[trianglecnt++]=add;
            }
        }
    }
    void dfs(int p,int cnt)//p点的凸包外时更新凸包
    {
        tri[cnt].ok=0;//删除当前面
        //下面把边反过来，处理与当前面相邻的面
        deal(p,tri[cnt].a,tri[cnt].c);
        deal(p,tri[cnt].c,tri[cnt].b);
        deal(p,tri[cnt].b,tri[cnt].a);
    }
    bool same(int s,int e)//判断两个面是否为同一面
    {
        TPoint a=P[tri[s].a],b=P[tri[s].b],c=P[tri[s].c];
        return fabs(volume(a,b,c,P[tri[e].a]))<eps
            &&fabs(volume(a,b,c,P[tri[e].b]))<eps
            &&fabs(volume(a,b,c,P[tri[e].c]))<eps;
    }
    void construct()//构建凸包
    {
        trianglecnt=0;
        if(n<4) return;
        bool tmp=true;
        for(int i=1;i<n;++i)//前两点不共点
            if(vlen(P[0]-P[i])>eps)
            {
                swap(P[1],P[i]);tmp=false;break;
            }
        if(tmp) return;
        tmp=true;
        for(int i=2;i<n;++i)//前三点不共线
            if(vlen((P[0]-P[1])^(P[i]-P[0]))>eps)
            {
                swap(P[2],P[i]);tmp=false;break;
            }
        if(tmp) return;
        tmp=true;
        for(int i=3;i<n;++i)//前四点不共面
            if(fabs(volume(P[0],P[1],P[2],P[i]))>eps)
            {
                swap(P[3],P[i]);tmp=false;break;
            }
        if(tmp) return;
        Fac add;
        for(int i=0;i<4;++i)//构建初始四面体
        {
            add.a=(i+1)%4,add.b=(i+2)%4,add.c=(i+3)%4,add.ok=1;
            if(ptoplane(P[i],add)>0) swap(add.b,add.c);
            belong[add.a][add.b]=belong[add.b][add.c]=belong[add.c][add.a]=trianglecnt;
            tri[trianglecnt++]=add;
        }
        for(int i=4;i<n;++i)//构建新凸包
        {
            for(int j=0;j<trianglecnt;++j)
            //判断点i能否看到面j
                if(tri[j].ok&&ptoplane(P[i],tri[j])>eps)
                {
                    //如果能看到则遍历面j和其他i点可见的面
                    dfs(i,j);break;
                }
        }
        int cnt=trianglecnt;
        trianglecnt=0;
        //保存最终得到的凸包
        for(int i=0;i<cnt;++i)
            if(tri[i].ok) tri[trianglecnt++]=tri[i];
    }
    double min_dis(TPoint p)//凸包中点p到凸包的最短距离
    {
        double ans=inf,V,S,H;
        for(int i=0;i<trianglecnt;++i)
        {
            V=fabs(volume(P[tri[i].a],P[tri[i].b],P[tri[i].c],p));
            S=vlen((P[tri[i].b]-P[tri[i].a])^(P[tri[i].c]-P[tri[i].a]))/2;
            H=3*V/S;
            ans=min(ans,H);
        }
        return ans;
    }
    bool f[N];//标记是否与其它面共面
    int face_num()//计算凸包有多少个面
    {
        memset(f,0,sizeof(f));
        int num=0;
        for(int i=0;i<trianglecnt;++i)
            if(!f[i])
            {
                ++num;
                for(int j=i+1;j<trianglecnt;++j)
                //标记与i共面的面
                    if(same(i,j)) f[j]=true;
            }
        return num;
    }
    TPoint center()//三维凸包重心
    {
        TPoint p(0,0,0),o(0,0,0);
        double sum_v=0,V;
        for(int i=0;i<trianglecnt;++i)
        {
            V=-volume(P[tri[i].a],P[tri[i].b],P[tri[i].c],o);
            p=p+(o+P[tri[i].a]+P[tri[i].b]+P[tri[i].c])/4.0*V;
            sum_v+=V;
        }
        return p/sum_v;
    }
}hull;
int main()
{
    while(scanf("%d",&hull.n)!=EOF)
    {
        for(int i=0;i<hull.n;++i)//输入点集
            hull.P[i].input();
        hull.construct();//构建凸包
        TPoint p=hull.center();//求凸包重心
        printf("%.3f\n",hull.min_dis(p));
    }
    return 0;
}
