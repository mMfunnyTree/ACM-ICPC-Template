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
    TPoint operator-(const TPoint &p)const//�������
    {
        return TPoint(x-p.x,y-p.y,z-p.z);
    }
    TPoint operator^(const TPoint &p)const//�������
    {
        return TPoint(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);
    }
    double operator*(const TPoint &p)const//�������
    {
        return x*p.x+y*p.y+z*p.z;
    }
    TPoint operator+(const TPoint &p)const//�����ӷ����������ǵ���
    {
        return TPoint(x+p.x,y+p.y,z+p.z);
    }
    TPoint operator/(const double k)const//������һ�������������ǵ���
    {
        return TPoint(x/k,y/k,z/k);
    }
    TPoint operator*(const double k)const//������һ������������ʱ����
    {
        return TPoint(x*k,y*k,z*k);
    }
    void input()
    {
        scanf("%lf%lf%lf",&x,&y,&z);
    }
    void output()//��������
    {
        printf("%.3f %.3f %.3f\n",x,y,z);
    }
};
double dis(TPoint p1,TPoint p2)//������ʱ����
{
    TPoint p=p1-p2;
    return sqrt(p1.x*p2.x+p1.y*p2.y+p1.z*p2.z);
}
struct Fac{
    int a,b,c;//͹��һ�����ϵ�������ı��
    bool ok;//�����Ƿ�������͹���е���
};
struct T3dhull{
    int n;//��ʼ����
    TPoint P[N];//��ʼ��
    int trianglecnt;//͹������������
    Fac tri[N*8];//͹��������
    int belong[N][N];//��i����j�������ĸ���
    double vlen(TPoint p)//��������
    {
        return sqrt(p.x*p.x+p.y*p.y+p.z*p.z);
    }
    double volume(TPoint a,TPoint b,TPoint c,TPoint p)//�������������
    {
        return ((b-a)^(c-a))*(p-a)/6;
    }
    double ptoplane(TPoint &p,Fac &f)//������ͬ������
    {
        TPoint p1=P[f.b]-P[f.a],p2=P[f.c]-P[f.a],p3=p-P[f.a];
        return (p1^p2)*p3;
    }
    void deal(int p,int a,int b)
    {
        int f=belong[a][b];//�뵱ǰ�棨cnt�����ߣ�ab�����Ǹ���
        Fac add;
        if(tri[f].ok)
        {
            //���p���ܿ�����f��������������f�������ߣ��Ա�����µ�͹����
            if(ptoplane(P[p],tri[f])>eps) dfs(p,f);
            else//����p��ֻ����cnt�棬������f�棬��p���a��b�����һ��������
            {
                add.a=b;add.b=a;add.c=p;add.ok=1;
                belong[p][b]=belong[b][a]=belong[a][p]=trianglecnt;
                tri[trianglecnt++]=add;
            }
        }
    }
    void dfs(int p,int cnt)//p���͹����ʱ����͹��
    {
        tri[cnt].ok=0;//ɾ����ǰ��
        //����ѱ߷������������뵱ǰ�����ڵ���
        deal(p,tri[cnt].a,tri[cnt].c);
        deal(p,tri[cnt].c,tri[cnt].b);
        deal(p,tri[cnt].b,tri[cnt].a);
    }
    bool same(int s,int e)//�ж��������Ƿ�Ϊͬһ��
    {
        TPoint a=P[tri[s].a],b=P[tri[s].b],c=P[tri[s].c];
        return fabs(volume(a,b,c,P[tri[e].a]))<eps
            &&fabs(volume(a,b,c,P[tri[e].b]))<eps
            &&fabs(volume(a,b,c,P[tri[e].c]))<eps;
    }
    void construct()//����͹��
    {
        trianglecnt=0;
        if(n<4) return;
        bool tmp=true;
        for(int i=1;i<n;++i)//ǰ���㲻����
            if(vlen(P[0]-P[i])>eps)
            {
                swap(P[1],P[i]);tmp=false;break;
            }
        if(tmp) return;
        tmp=true;
        for(int i=2;i<n;++i)//ǰ���㲻����
            if(vlen((P[0]-P[1])^(P[i]-P[0]))>eps)
            {
                swap(P[2],P[i]);tmp=false;break;
            }
        if(tmp) return;
        tmp=true;
        for(int i=3;i<n;++i)//ǰ�ĵ㲻����
            if(fabs(volume(P[0],P[1],P[2],P[i]))>eps)
            {
                swap(P[3],P[i]);tmp=false;break;
            }
        if(tmp) return;
        Fac add;
        for(int i=0;i<4;++i)//������ʼ������
        {
            add.a=(i+1)%4,add.b=(i+2)%4,add.c=(i+3)%4,add.ok=1;
            if(ptoplane(P[i],add)>0) swap(add.b,add.c);
            belong[add.a][add.b]=belong[add.b][add.c]=belong[add.c][add.a]=trianglecnt;
            tri[trianglecnt++]=add;
        }
        for(int i=4;i<n;++i)//������͹��
        {
            for(int j=0;j<trianglecnt;++j)
            //�жϵ�i�ܷ񿴵���j
                if(tri[j].ok&&ptoplane(P[i],tri[j])>eps)
                {
                    //����ܿ����������j������i��ɼ�����
                    dfs(i,j);break;
                }
        }
        int cnt=trianglecnt;
        trianglecnt=0;
        //�������յõ���͹��
        for(int i=0;i<cnt;++i)
            if(tri[i].ok) tri[trianglecnt++]=tri[i];
    }
    double min_dis(TPoint p)//͹���е�p��͹������̾���
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
    bool f[N];//����Ƿ��������湲��
    int face_num()//����͹���ж��ٸ���
    {
        memset(f,0,sizeof(f));
        int num=0;
        for(int i=0;i<trianglecnt;++i)
            if(!f[i])
            {
                ++num;
                for(int j=i+1;j<trianglecnt;++j)
                //�����i�������
                    if(same(i,j)) f[j]=true;
            }
        return num;
    }
    TPoint center()//��ά͹������
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
        for(int i=0;i<hull.n;++i)//����㼯
            hull.P[i].input();
        hull.construct();//����͹��
        TPoint p=hull.center();//��͹������
        printf("%.3f\n",hull.min_dis(p));
    }
    return 0;
}
