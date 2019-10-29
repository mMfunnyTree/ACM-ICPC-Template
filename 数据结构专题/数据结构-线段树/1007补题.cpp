#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;

#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
#define intmid  int mid = (l+r)>>1

int n,q;
int minv[maxn<<2],cur[maxn<<2];/**线段树数组**/
int b[maxn];

int d[maxn];                    /**树状数组**/
int l,r;
char op[20];

int lowbit(int x){return x&(-x);}

void upd(int x,int v){/**树状数组操作**/
    while(x<=n){
        d[x]+=v;
        x+=lowbit(x);
    }
}

int sum(int x){/**树状数组操作**/
    int ret=0;
    while(x){
        ret+=d[x];
        x-=lowbit(x);
    }return ret;
}

void push_up(int rt){
    minv[rt]=min(minv[rt<<1],minv[rt<<1|1]);
}

void push_down(int l,int r,int rt){
    if(cur[rt]){
        intmid;
        cur[rt<<1]   += cur[rt];
        cur[rt<<1|1] += cur[rt];
        minv[rt<<1]  += cur[rt];
        minv[rt<<1|1]+= cur[rt];
        cur[rt]=0;
    }
}

void build(int l,int r,int rt){/**建树函数**/
    cur[rt]=0;
    if(l==r){
        scanf("%d",&minv[rt]);
        b[l]=minv[rt];
        d[l]=0;
        return ;
    }
    intmid;
    build(lson);build(rson);push_up(rt);
}

void getans(int l,int r,int rt){
    /**当区间[l,r]中有0，说明要更新答案，如果是叶子直接修改，否则看左右区间**/
    intmid;
    if(l==r){
        upd(l,1);
        minv[rt]=b[l];/**更新完之后，要对该点修改值为结点的b值**/
        return;
    }
    push_down(l,r,rt);/**先push_down，把lazy信息给儿子**/
    if(minv[rt<<1]==0)getans(lson);
    if(minv[rt<<1|1]==0)getans(rson);
    push_up(rt);/**把更新完的儿子信息返回给父亲**/
}

void update(int L,int R,int v,int l,int r,int rt){
    intmid;
    if(L<=l && R>=r){
        cur[rt]+=v;
        minv[rt]+=v;
        if(minv[rt]==0){/**如果结点维护的区间里有需要修改的，直接getans修改**/
            getans(l,r,rt);
        }
        return ;
    }
    push_down(l,r,rt);
    if(L<=mid)update(L,R,v,lson);
    if(R>mid)update(L,R,v,rson);
    push_up(rt);
}

int main(){
    while(scanf("%d%d",&n,&q)!=EOF){
        build(1,n,1);/**build函数用来构造这颗线段树，一开始所有的lazy标记置0**/
        while(q--){
            scanf("%s%d%d",op,&l,&r);
            if(op[0]=='a'){
                update(l,r,-1,1,n,1);/**对线段树区间进行-1操作，当区间被减空了说明要进行getans操作**/
            } else {
                printf("%d\n",sum(r)-sum(l-1));/**树状数组维护区间和**/
            }
        }
    }
    return 0;
}
