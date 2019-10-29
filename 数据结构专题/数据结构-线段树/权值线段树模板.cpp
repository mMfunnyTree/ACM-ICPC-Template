// luogu-judger-enable-o2
/******权值线段树模板******/
/**
权值线段树维护全局值域信息，每个结点记录值域的值出现次数
如果值域太大，需要离线操作
**/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn =  1e5+10;
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
#define intmid int mid = (l+r)>>1

ll t[maxn*4+1];
ll dt[maxn],tot;
ll hs(int x){return lower_bound(dt+1,dt+1+tot,x)-dt;}

void update(int p,int v,int l,int r,int rt){
    //单点修改 所到的值域都需要修改 复杂度logn
    t[rt]+=v;
    if(l==r)return ;
    intmid;
    if(p<=mid)update(p,v,lson);
    else update(p,v,rson);
}

int kth(int k,int l,int r,int rt){
    //如果左边多于k个，那么去左边找，否则找到右边
    if(l==r)return l;
    intmid;
    if(t[rt<<1]>=k)return kth(k,lson);
    return kth(k-t[rt<<1],rson);
}

int Rank(int p,int l,int r,int rt){
    //查询小于p的数出现的总次数，即区间[1,p-1]的数字个数，即rank
    if(l==r)return 1;
    intmid;
    if(p<=mid)return Rank(p,lson);
    return t[rt<<1]+Rank(p,rson);
}
struct node{
    ll first,second;
}p[maxn];
signed main(){
    int n;cin>>n;
    for(int i=1;i<=n;i++){
        scanf("%lld%lld",&p[i].first,&p[i].second);
        if(p[i].first!=4)dt[++tot]=p[i].second;
    }
    sort(dt+1,dt+1+tot);
    tot=unique(dt+1,dt+1+tot)-dt-1;
    for(int i=1;i<=n;i++){
        if(p[i].first==1)update(hs(p[i].second),1,1,tot,1);
        else if(p[i].first==2)update(hs(p[i].second),-1,1,tot,1);
        else if(p[i].first==3)printf("%lld\n",Rank(hs(p[i].second),1,tot,1));
        else if(p[i].first==4)printf("%lld\n",dt[kth(p[i].second,1,tot,1)]);
        else if(p[i].first==5)printf("%lld\n",dt[kth(Rank(hs(p[i].second),1,tot,1)-1,1,tot,1)] );
        else if(p[i].first==6)printf("%lld\n",dt[kth(Rank(hs(p[i].second)+1,1,tot,1),1,tot,1)]);
    }
    return 0;
}
