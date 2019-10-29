#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;

#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
#define intmid  int mid = (l+r)>>1

int n,q;
int minv[maxn<<2],cur[maxn<<2];/**�߶�������**/
int b[maxn];

int d[maxn];                    /**��״����**/
int l,r;
char op[20];

int lowbit(int x){return x&(-x);}

void upd(int x,int v){/**��״�������**/
    while(x<=n){
        d[x]+=v;
        x+=lowbit(x);
    }
}

int sum(int x){/**��״�������**/
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

void build(int l,int r,int rt){/**��������**/
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
    /**������[l,r]����0��˵��Ҫ���´𰸣������Ҷ��ֱ���޸ģ�������������**/
    intmid;
    if(l==r){
        upd(l,1);
        minv[rt]=b[l];/**������֮��Ҫ�Ըõ��޸�ֵΪ����bֵ**/
        return;
    }
    push_down(l,r,rt);/**��push_down����lazy��Ϣ������**/
    if(minv[rt<<1]==0)getans(lson);
    if(minv[rt<<1|1]==0)getans(rson);
    push_up(rt);/**�Ѹ�����Ķ�����Ϣ���ظ�����**/
}

void update(int L,int R,int v,int l,int r,int rt){
    intmid;
    if(L<=l && R>=r){
        cur[rt]+=v;
        minv[rt]+=v;
        if(minv[rt]==0){/**������ά��������������Ҫ�޸ĵģ�ֱ��getans�޸�**/
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
        build(1,n,1);/**build����������������߶�����һ��ʼ���е�lazy�����0**/
        while(q--){
            scanf("%s%d%d",op,&l,&r);
            if(op[0]=='a'){
                update(l,r,-1,1,n,1);/**���߶����������-1�����������䱻������˵��Ҫ����getans����**/
            } else {
                printf("%d\n",sum(r)-sum(l-1));/**��״����ά�������**/
            }
        }
    }
    return 0;
}
