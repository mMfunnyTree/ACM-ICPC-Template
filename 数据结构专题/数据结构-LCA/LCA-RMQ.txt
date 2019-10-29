///ZOJ 3195 LCA在线做法
///LCA转RMQ 应用深度搜索，把树变成序列，按照两个点第一次出现的位置，给出范围
///找范围最小深度的位置，从而找到最近公共祖先
#include<iostream>
using namespace std;
const int maxn = 100005 ;
struct Edge {
    int form,to,dist;
};
vector<Edge> edges ;
vector<int>G[maxn] ;
bool vis[maxn] ;///标记数组
int len[maxn] ;///节点到根的长度
int ver[maxn<<1] ;///遍历的节点序列
int first[maxn] ;///第一次出现的位置
int R[maxn<<1] ;///遍历的深度
int d[maxn][50] ;///dp数组，里面放的是RMQ的位置，不是数值
int n,tot ;
void add_edge(int from,int to,int dist) {
    edges.push_back((Edge) {from,to,dist}) ;
    int mm = edges.size() ;
    G[from].push_back(mm-1) ;
}
void dfs(int u,int dept) {
    vis[u] = true ;
    ver[tot] = u ;
    R[tot] = dept ;
    first[u] = tot ;
    tot++ ;
    for(int i=0; i<G[u].size(); i++) {
        if(!vis[edges[G[u][i]].to]) {
            len[edges[G[u][i]].to] = len[u]+ edges[G[u][i]].dist ;
            dfs(edges[G[u][i]].to,dept+1) ;
            ver[tot] = u ;
            R[tot] = dept ;
            tot++ ;
        }
    }
}
void RMQ_init(){
    for(int i=0;i<tot;i++){///初始化，存的是位置
        d[i][0] = i ;
    }
    for(int j=1;(1<<j)<=tot;j++){
        for(int i=0;i+(1<<j)-1<tot;i++){///取最深度最小时的位置
            int a = d[i][j-1] ;
            int b = d[i+(1<<(j-1))][j-1] ;
            if(R[a]<R[b])d[i][j] = d[i][j-1] ;
            else d[i][j] = d[i+(1<<(j-1))][j-1] ;
        }
    }
}
int RMQ(int l,int r){///返回范围最小深度的位置
    if(l>r)return 0;
    int k=0;
    while((1<<(k+1)) <= r-l+1) k++;
    int a = d[l][k] ;
    int b = d[r-(1<<k)+1][k] ;
    if(R[a]<R[b])return a ;
    else return b ;
}
int LCA(int u ,int v)  ///返回点u和点v的LCA
{
    int x = first[u] , y = first[v];
    if(x > y) swap(x,y);
    int res = RMQ(x,y);
    return ver[res];
}
int main() {
    int x=0;
    while(~scanf("%d",&n)) {
        if(x==1)printf("\n") ;
        x=1;
        memset(vis,false,sizeof(vis)) ;
        memset(d,false,sizeof(d)) ;
        memset(G,false,sizeof(G)) ;
        edges.clear() ;
        for(int i=0; i<n-1; i++) {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w) ;
            add_edge(u,v,w) ;
            add_edge(v,u,w) ;
        }
        tot = 0;
        dfs(0,1) ;
        RMQ_init() ;
        int q ;
        scanf("%d",&q) ;
        for(int i=0; i<q; i++) {
            int a,b,c ;
            scanf("%d%d%d",&a,&b,&c) ;
            int ans = 0 ;
            ///和两个点的时候有点区别
            ans+=len[a]+len[b]+len[c]-(len[LCA(a,b)]+len[LCA(a,c)]+len[LCA(b,c)]);
            printf("%d\n",ans) ;
        }
    }
    return 0;
}
