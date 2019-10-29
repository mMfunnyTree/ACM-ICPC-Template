/*ɨ����ģ��*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define LL long long
#define inf 1<<30
using namespace std;
const int N=205;
int n;
double y[N];
struct LINE     //  �洢�߶���Ϣ��
{
    double x;   //  ���߶����ڵ�λ�ã�
    double y_up,y_down;     //  �����߶ε����¶˵㣻
    int flag;
}line[N];
struct node
{
    double l,r;
    double x;       //  ��¼��һ��������λ�ã������������
    int cover;      //  ��¼���ǵ��߶�������ͬһ������߶�����
    bool flag;      //  ���ֻ��һ������Ľڵ㣬��10-15��15-20����һ�����䣬���ǽ�һ��һ��������������ɢ����һ���ڵ㣻
}node[N<<2];
bool cmp(LINE a,LINE b)
{
    return a.x<b.x;
}
void build(int rt,int l,int r)      //  ������
{
    node[rt].l=y[l];    //  ά�����䣻
    node[rt].r=y[r];
    node[rt].x=-1;
    node[rt].flag=false;
    node[rt].cover=0;
    if(l+1==r){             //  �����������ģ���10-15,15-20;
        node[rt].flag=true; //  ���Ϊ�ڵ㣻
        return;
    }
    int mid=(l+r)>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid,r);   //  ͬ42�У����Դ˴�mid����Ҫ+1��
}
double Insert_query(int rt,double x,double l,double r,int flag) //  ��ѯ+����x����l,r�����������
{
    if(l>=node[rt].r||r<=node[rt].l) return 0;  //  �÷���ڵ㲻������Ҫ��ѯ�����䣻
    if(node[rt].flag){  //  �ҵ�ֻ��һ�������Ҷ�ӽڵ㣻
        if(node[rt].cover>0){
            double pre=node[rt].x;
            double ans=(x-pre)*(node[rt].r-node[rt].l); //  ���������
            node[rt].x=x;       //  ���¶�λ��һ��xλ�ã������´μ��������
            node[rt].cover+=flag;   //  ���¸��ǵ��߶�����
            return ans;
        }else{
            node[rt].x=x;
            node[rt].cover+=flag;
            return 0;
        }
    }
    double ans1,ans2;
    ans1=Insert_query(rt<<1,x,l,r,flag);    //  ֱ������������飬���з�������������
    ans2=Insert_query(rt<<1|1,x,l,r,flag);  //  52�б�֤��ѯ�Ŀ����ԣ�
    return ans1+ans2;
}
int main()
{
    int Case=0;
    double x1,x2,y1,y2;
    while(~scanf("%d",&n)&&n){
        int cnt=-1;
        for(int i=0;i<n;i++){
            scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
            y[++cnt]=y1;
            line[cnt].x=x1;
            line[cnt].y_down=y1;
            line[cnt].y_up=y2;
            line[cnt].flag=1;   //  ��ʾ����߶Σ�
            y[++cnt]=y2;
            line[cnt].x=x2;
            line[cnt].y_down=y1;
            line[cnt].y_up=y2;
            line[cnt].flag=-1;  //  ��ʾ�ұ��߶Σ�
        }
        sort(y,y+cnt+1);        //  �����и߶���С�������򣬽����佨����ʾ��
        sort(line,line+cnt+1,cmp);      //  ���򣬷�������x����ĵ㣻
        build(1,0,cnt);
        double area=0;
        for(int i=0;i<=cnt;i++){
            area+=Insert_query(1,line[i].x,line[i].y_down,line[i].y_up,line[i].flag);
        }
        printf("Test case #%d\nTotal explored area: %.2lf\n\n",++Case,area);
    }
    return 0;
}

