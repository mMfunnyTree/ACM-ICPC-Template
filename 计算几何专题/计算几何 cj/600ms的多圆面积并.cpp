#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;
typedef double du;
const du pi2=M_PI*2;
struct point{
    du x,y;
    point(du a=0,du b=0){x=a;y=b;}
    du len(){return sqrt(x*x+y*y);}
};
point operator-(point a,point b){return point(a.x-b.x,a.y-b.y);}
bool operator<(point a,point b){return a.x==b.x?a.y<b.y:a.x<b.x;}
bool operator==(point a,point b){return a.x==b.x&&a.y==b.y;}
struct circle{
    point o;
    du r;
    du oint(du t1,du t2){return r*(r*(t2-t1)+o.x*(sin(t2)-sin(t1))-o.y*((cos(t2)-cos(t1))));}
}c[1010];
bool operator<(circle a,circle b){return a.o==b.o?a.r<b.r:a.o<b.o;}
bool operator==(circle a,circle b){return a.o==b.o&&a.r==b.r;}
struct angle{
    du a;
    int d;
    angle(du x=0,int y=0){a=x;d=y;}
}p[2010];
bool operator<(angle a,angle b){return a.a<b.a;}
int n;
du solve(int u){
    int i,M,cnt;
    du len,an,f,l,r,s;
    point d;
    cnt=0;
    M=0;
    for(i=1;i<=n;i++){
        if(i!=u){
            d=c[i].o-c[u].o;
            len=d.len();
            if(c[u].r+len<=c[i].r)return 0;
            if(c[u].r>=c[i].r+len||len>=c[i].r+c[u].r)continue;
            an=atan2(d.y,d.x);
            f=acos((c[u].r*c[u].r+len*len-c[i].r*c[i].r)/(2*c[u].r*len));
            l=an-f;
            r=an+f;
            if(l<-M_PI)l+=pi2;
            if(r>M_PI)r-=pi2;
            if(l>r)cnt++;
            p[++M]=angle(l,1);
            p[++M]=angle(r,-1);
        }
    }
    p[0]=-M_PI;
    p[++M]=M_PI;
    sort(p+1,p+M+1);
    s=0;
    for(i=1;i<=M;cnt+=p[i++].d){
        if(cnt==0)s+=c[u].oint(p[i-1].a,p[i].a);
    }
    return s*.5;
}
int main(){
    int i;
    du s;
    scanf("%d",&n);
    for(i=1;i<=n;i++)scanf("%lf%lf%lf",&c[i].o.x,&c[i].o.y,&c[i].r);
    sort(c+1,c+n+1);
    n=unique(c+1,c+n+1)-c-1;
    for(i=1;i<=n;i++)s+=solve(i);
    printf("%.3lf",s);
}