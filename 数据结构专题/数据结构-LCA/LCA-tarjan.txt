///输入T样例数目、输入一个树n个顶点，m个查询，输出两个点的最短距离
#include<bits/stdc++.h>
using namespace std;
const int maxn = 40005 ;
struct Edge {
    int form,to,dist;
};
vector<Edge> edges ;
vector<int>G[maxn] ;
void add_edge(int from,int to,int dist) {
    edges.push_back((Edge){from,to,dist}) ;
    int mm = edges.size() ;
    G[from].push_back(mm-1) ;
}
vector<Edge> edges2 ;
vector<int>G2[maxn] ;
void add_edge2(int from,int to,int dist=0) {
    edges2.push_back((Edge){from,to,dist}) ;
    int mm = edges2.size() ;
    G2[from].push_back(mm-1) ;
}
int f[maxn] ;
bool vis[maxn] ;
int len[maxn] ;
int find(int x){
    return x==f[x]?x:f[x]=find(f[x]);
}
void LCA(int u){
    f[u] = u ;
    vis[u] = true ;
    for(int i=0;i<G[u].size();i++){
        if(!vis[edges[G[u][i]].to]){
            len[edges[G[u][i]].to] = len[u]+edges[G[u][i]].dist;
            LCA(edges[G[u][i]].to) ;
            f[edges[G[u][i]].to] = u ;
        }
    }
    for(int i=0;i<G2[u].size();i++){
        if(vis[edges2[G2[u][i]].to]){///这句话要记牢
           edges2[G2[u][i]].dist = len[edges2[G2[u][i]].to]+len[u]-2*len[find(edges2[G2[u][i]].to)];
           edges2[G2[u][i]^1].dist = edges2[G2[u][i]].dist
        }
    }
}
int main() {
    int t ;
    scanf("%d",&t) ;
    while(t--) {
        memset(G,0,sizeof(G)) ;
        memset(G2,0,sizeof(G2)) ;
        memset(len,0,sizeof(len)) ;
        memset(vis,false,sizeof(vis)) ;
        edges.clear() ;
        edges2.clear() ;

        int n,m;
        scanf("%d%d",&n,&m) ;
        for(int i=0; i<n-1; i++) {
            int u,v,w ;
            scanf("%d%d%d",&u,&v,&w) ;
            add_edge(u,v,w) ;
            add_edge(v,u,w) ;
        }
        for(int i=0; i<m; i++) {
            int u,v ;
            scanf("%d%d",&u,&v) ;
            add_edge2(u,v) ;
            add_edge2(v,u) ;
        }
        LCA(1) ;
        for(int i=0; i<m; i++) {
            printf("%d\n",edges2[2*i].dist) ;
        }
    }
    return 0;
}
