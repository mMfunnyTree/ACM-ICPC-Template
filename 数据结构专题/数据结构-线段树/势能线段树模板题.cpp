#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
const int maxn = 1e6+10;
int n,m;
ll sum[maxn<<2],maxv[maxn<<2],maxv2[maxn<<2],maxcnt[maxn<<2];
void push_up(int rt){
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
    maxv[rt]=max(maxv[rt<<1],maxv[rt<<1|1]);
    if(maxv[rt<<1] > maxv[rt<<1|1]){
        maxv2[rt]=max(maxv[rt<<1|1],maxv2[rt<<1]);
        maxcnt[rt]=maxcnt[rt<<1];
    }
    else if(maxv[rt<<1] == maxv[rt<<1|1]){
        maxv2[rt]=max(maxv2[rt<<1],maxv2[rt<<1|1]);
        maxcnt[rt]=maxcnt[rt<<1]+maxcnt[rt<<1|1];
    }
    else{
        maxv2[rt]=max(maxv[rt<<1],maxv2[rt<<1|1]);
        maxcnt[rt]=maxcnt[rt<<1|1];
    }
}
void build(int l,int r,int rt){
    if(l==r){
        scanf("%lld",sum+rt);
        maxv[rt]=sum[rt];maxv2[rt]=-1;maxcnt[rt]=1;return;
    }int mid=l+r>>1;
    build(lson);build(rson);push_up(rt);
}
void push_tag(int rt,int v){
    if(v>=maxv[rt])return;
    sum[rt]-=maxcnt[rt]*(maxv[rt]-v);maxv[rt]=v;
}
void push_down(int rt){
    push_tag(rt<<1,maxv[rt]);push_tag(rt<<1|1,maxv[rt]);
}
void update(int L,int R,int v,int l,int r,int rt){
    if(maxv[rt]<=v)return;
    int mid=l+r>>1;
    if(L<=l&&R>=r&&maxv2[rt]<v){
        push_tag(rt,v);
        return;
    }
    push_down(rt);
    if(L<=mid)update(L,R,v,lson);
    if(R>mid)update(L,R,v,rson);
    push_up(rt);
}
ll querysum(int L,int R,int l,int r,int rt){
    if(L<=l&&R>=r){
        return sum[rt];
    }ll ret=0,mid=l+r>>1;
    push_down(rt);
    if(L<=mid)ret+=querysum(L,R,lson);
    if(R>mid) ret+=querysum(L,R,rson);return ret;
}
ll querymax(int L,int R,int l,int r,int rt){
    if(L<=l&&R>=r){
        return maxv[rt];
    }ll ret=0,mid=l+r>>1;
    push_down(rt);
    if(L<=mid)ret=max(ret,querymax(L,R,lson));
    if(R>mid) ret=max(ret,querymax(L,R,rson));return ret;
}
int main(){
    int T;cin>>T;
    int tp,x,y,t;
    while(T--){
        scanf("%d%d",&n,&m);
        build(1,n,1);
        while(m--){
            scanf("%d%d%d",&tp,&x,&y);
            if(tp==0){
                scanf("%d",&t);update(x,y,t,1,n,1);
            }
            else if(tp==2)printf("%lld\n",querysum(x,y,1,n,1));
            else printf("%lld\n",querymax(x,y,1,n,1));
        }
    }
    return 0;
}
