#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 1e5+10;
struct Node{
    int idx,l,r,delt;
    int kind;
    bool operator < (const Node &rhs)const{
        return l<rhs.l;
    }
}node[maxn];

int ans[maxn],del[maxn];
/*******反向BIT*******/
inline int lowbit(int x){return x&(-x);}
int arr[maxn],MAX;
void add(int x,int d){
    while(x){
        arr[x]+=d;
        x-=lowbit(x);
    }
}
int sum(int x){
    int ret=0;
    while(x<=MAX){
        ret+=arr[x];
        x+=lowbit(x);
    }return ret;
}
/****离散化****/
int vec[maxn],vec_idx;
int hs(int x){
    return lower_bound(vec,vec+vec_idx,x)-vec+1;
}
/*****CDQ*****/
void cdq(int l,int r){
    if(l==r)return;
    int mid = (l+r)>>1;
    cdq(l,mid);
    cdq(mid+1,r);
    int j=l;
    for(int i=mid+1;i<=r;i++){
        if(node[i].kind==2){
            for(;j<=mid && node[j].l<=node[i].l;j++){
                if(node[j].kind==1){
                    add(hs(node[j].r),node[j].delt);
                }
            }
            ans[node[i].idx]+=sum(hs(node[i].r));
        }
    }
    for(int i=l;i<j;i++){
        if(node[i].kind==1){
            add(hs(node[i].r),-node[i].delt);
        }
    }
    inplace_merge(node+l,node+mid+1,node+r+1);
}
int vis[maxn];
int main(){
    int n,m;
    while(scanf("%d%d",&m,&n)!=EOF){
        int cnt=0;
        vec_idx=0;
        memset(arr,0,sizeof(arr));
        memset(ans,0,sizeof(ans));
        memset(vis,0,sizeof(vis));
        vector<int> v;
        char op[3];
        for(int i=1;i<=n;i++){
            scanf("%s",op);
            if(op[0]=='1'){
                scanf("%d%d",&node[i].l,&node[i].r);
                node[i].kind=1;
                node[i].idx=i;
                node[i].delt=1;
                vec[vec_idx++]=node[i].r;
                v.push_back(i);
            } else if(op[0]=='2'){
                scanf("%d%d",&node[i].l,&node[i].r);
                node[i].kind=2;
                node[i].idx=i;
                vec[vec_idx++]=node[i].r;
                vis[i]=1;
            } else{
                int tmp;
                scanf("%d",&tmp);
                node[i].kind=1;
                node[i].l=node[v[tmp-1]].l;
                node[i].r=node[v[tmp-1]].r;
                node[i].delt=-1;
                node[i].idx=i;
            }
        }
        sort(vec,vec+vec_idx);
        MAX = vec_idx+10;
        cdq(1,n);
        for(int i=1;i<=n;i++){
            if(vis[i]){
                printf("%d\n",ans[i]);
            }
        }
    }
    return 0;
}
