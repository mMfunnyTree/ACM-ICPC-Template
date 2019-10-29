#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5+10;
const int inf = 0x3f3f3f3f;
int tot=0,r=0;
int siz[maxn],v[maxn],num[maxn],rd[maxn],son[maxn][2];
/**subtree size,point value,point time,rand value,son**/
void push_up(int rt){
    siz[rt]=siz[son[rt][0]]+siz[son[rt][1]]+num[rt];
}
void rotate(int &rt,int d){
    int k=son[rt][d^1];
    son[rt][d^1]=son[k][d];
    son[k][d]=rt;
    push_up(rt);push_up(k);
    rt=k;
}
void ins(int &rt,int x){
    if(!rt){
        rt=++tot;
        siz[rt]=num[rt]=1;
        v[rt]=x;rd[rt]=rand();
        return;
    }
    if(v[rt]==x){
        num[rt]++;siz[rt]++;return;
    }
    int d=(x>v[rt]);
    ins(son[rt][d],x);
    if(rd[rt]<rd[son[rt][d]])rotate(rt,d^1);
    push_up(rt);
}
void del(int &rt,int x){
    if(!rt)return;
    if(x<v[rt])del(son[rt][0],x);
    else if(x>v[rt])del(son[rt][1],x);
    else{
        if(!son[rt][0]&&!son[rt][1]){
            num[rt]--;siz[rt]--;
            if(!num[rt])rt=0;
        }
        else if(son[rt][0]&&!son[rt][1]){
            rotate(rt,1);
            del(son[rt][1],x);
        }
        else if(!son[rt][0]&&son[rt][1]){
            rotate(rt,0);
            del(son[rt][0],x);
        }
        else{
            int d=(rd[son[rt][0]] >rd[son[rt][1]] );
            rotate(rt,d);
            del(son[rt][d],x);
        }
    }push_up(rt);
}
int rk(int rt,int x){
    if(!rt)return 0;
    if(v[rt]==x)return siz[son[rt][0]]+1;
    if(v[rt]<x)return siz[son[rt][0]]+num[rt]+rk(son[rt][1],x);
    return rk(son[rt][0],x);
}
int find(int rt,int x){
    if(!rt)return 0;
    if(siz[son[rt][0]]>=x)return find(son[rt][0],x);
    if(siz[son[rt][0]]+num[rt]<x)return find(son[rt][1],x-num[rt]-siz[son[rt][0]]);
    return v[rt];
}
int pre(int rt,int x){
    if(!rt)return -inf;
    if(v[rt]>=x)return pre(son[rt][0],x);
    return max(v[rt],pre(son[rt][1],x));
}
int nxt(int rt,int x){
    if(!rt)return inf;
    if(v[rt]<=x)return nxt(son[rt][1],x);
    return min(v[rt],nxt(son[rt][0],x));
}
int main(){
    int n;scanf("%d",&n);
    int op,x;
    for(int i=0;i<n;i++){
        scanf("%d%d",&op,&x);
        if(op==1)ins(r,x);
        else if(op==2)del(r,x);
        else if(op==3)printf("%d\n",rk(r,x));
        else if(op==4)printf("%d\n",find(r,x));
        else if(op==5)printf("%d\n",pre(r,x));
        else printf("%d\n",nxt(r,x));
    }
    return 0;
}
