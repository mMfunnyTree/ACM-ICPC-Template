#define _FORTIFY_SOURCE 0
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstdlib>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
struct FastIO{
  static const int S=1310720;
  int wpos,pos,len;char wbuf[S];
  FastIO():wpos(0){}
  inline int xchar(){
    static char buf[S];
    if(pos==len)pos=0,len=fread(buf,1,S,stdin);
    if(pos==len)return -1;
    return buf[pos++];
  }
  inline int xuint(){//-1±Ì æø’¡À
    int c=xchar();
    while(c<=32&&~c)c=xchar();
    if(c==-1)return -1000000000;
    int f=0;
    int a=0;
    for(;c<45;c=xchar());
    if(c==45)f=1,c=xchar();
    while(c>47)a=a*10+c-48,c=xchar();
    if(f)a=-a;
    return a;
  }
}io;
const int N=100010;
int n,m,i,j,w[N],bit[N],f[N];ll ans;
int H,W,tot;
int g[N];
int xx[N],yy[N],id[N],at[N],www[N],q[N];
inline int getid(int x,int y){
  return (x-1)*W+y;
}
struct P{
  int x,y;
  P(){}
  P(int _x,int _y){x=_x,y=_y;}
}a[N],b[N];
struct E{int x,y,p;E(){}E(int _x,int _y,int _p){x=_x,y=_y,p=_p;}}e[1000010];
typedef pair<int,int>PI;
PI c[N];
int mi[N],who[N];bool used[1000010];
//inline bool cmp(const P&a,const P&b){return a.x==b.x?a.y<b.y:a.x<b.x;}
inline bool cmp(int x,int y){
  return b[x].x==b[y].x?b[x].y<b[y].y:b[x].x<b[y].x;
}
inline bool cmpe(const E&a,const E&b){return a.p<b.p;}
inline int dis(int x,int y){return abs(a[x].x-a[y].x)+abs(a[x].y-a[y].y);}
inline void ins(int x,int p){for(;x<=n;x+=x&-x)if(w[p]<=w[bit[x]])bit[x]=p;}
inline int ask(int x){int t=0;for(;x;x-=x&-x)if(w[bit[x]]<=w[t])t=bit[x];return t;}
inline void solve(){
  sort(q+1,q+n+1,cmp);
  sort(c+1,c+n+1);
  int i,j,k;
  for(www[n]=n,i=n-1;i;i--){
    www[i]=c[i].first==c[i+1].first?www[i+1]:i;
  }
  for(i=1;i<=n;i++){
    at[c[i].second]=www[i];
  }
  for(i=1;i<=n;i++){
    k=at[q[i]];
    j=ask(k);
    ins(k,q[i]);
    if(j){
      //if(tot>=50000&&(i&3))continue;
      int v=dis(q[i],j);
      //if(tot<=10000||v<=9000000){
      //newedge(id[q[i]],id[j],v);
        e[++m]=E(id[q[i]],id[j],v);//
        //fk[++m]=(((ull)dis(q[i],j))<<34)|(((ull)id[q[i]])<<17)|id[j];
      //}
    }
  }
}
inline void ManhattanMst(){
  if(n<=1)return;
  int i,j,k;
  w[0]=~0U>>1;
  for(i=1;i<=n;i++){
    b[i]=P(-a[i].x,a[i].x-a[i].y);
    q[i]=i;
    c[i]=PI(b[i].y,i);
    w[i]=a[i].x+a[i].y;
    bit[i]=0;
  }
  solve();
  for(i=1;i<=n;i++){
    b[i]=P(-a[i].y,a[i].y-a[i].x);
    q[i]=i;
    c[i]=PI(b[i].y,i);
    bit[i]=0;
  }
  solve();
  for(i=1;i<=n;i++){
    b[i]=P(a[i].y,-a[i].x-a[i].y);
    q[i]=i;
    c[i]=PI(b[i].y,i);
    w[i]=a[i].x-a[i].y;
    bit[i]=0;
  }
  solve();
  for(i=1;i<=n;i++){
    b[i]=P(-a[i].x,a[i].y+a[i].x);
    q[i]=i;
    c[i]=PI(b[i].y,i);
    bit[i]=0;
  }
  solve();
}
inline bool check(int x,int y){
  while(f[x]>=0&&f[f[x]]>=0)x=f[x]=f[f[x]];
  f[x]>=0?(x=f[x]):0;
  while(f[y]>=0&&f[f[y]]>=0)y=f[y]=f[f[y]];
  f[y]>=0?(y=f[y]):0;
  if(x==y)return 0;
  f[x]<f[y]?(f[x]+=f[y],f[y]=x):(f[y]+=f[x],f[x]=y);
  return 1;
}
inline int F(int x){
  while(f[x]>=0&&f[f[x]]>=0)x=f[x]=f[f[x]];
  f[x]>=0?(x=f[x]):0;
  return x;
}
inline void up(int x,int y,int z){
  if(z<mi[x]){
    mi[x]=z;
    who[x]=y;
  }
}
int main(){
  while(1){
    H=io.xuint();
    if(H==-1000000000)break;
    W=io.xuint();
    m=0;
    tot=H*W;
    for(i=1;i<=tot;i++)xx[i]=io.xuint();
    for(i=1;i<=tot;i++)yy[i]=io.xuint();
    for(i=1;i<=H;i++){
      n=W;
      for(j=1;j<=n;j++){
        int o=getid(i,j);
        id[j]=o;
        a[j].x=xx[o];
        a[j].y=yy[o];
      }
      ManhattanMst();
    }
    for(i=1;i<=W;i++){
      n=H;
      for(j=1;j<=n;j++){
        int o=getid(j,i);
        id[j]=o;
        a[j].x=xx[o];
        a[j].y=yy[o];
      }
      ManhattanMst();
    }
    for(i=1;i<=tot;i++)f[i]=-1;
    for(i=1;i<=m;i++)used[i]=0;
    ans=0;
    int ret=tot-1;
    while(ret){
      for(i=1;i<=tot;i++)mi[i]=~0U>>1,who[i]=0;
      for(i=1;i<=tot;i++)g[i]=F(i);
      for(i=1;i<=m;i++)if(!used[i]){
        int x=g[e[i].x],y=g[e[i].y];
        if(x==y){
          used[i]=1;
          continue;
        }
        up(x,y,e[i].p);
        up(y,x,e[i].p);
      }
      for(i=1;i<=tot;i++){
        int y=who[i];
        if(!y)continue;
        //printf("%d %d %d\n",i,y,mi[i]);
        if(check(i,y)){
          ret--;
          ans+=mi[i];
        }
      }
    }
    printf("%lld\n",ans);
  }
}