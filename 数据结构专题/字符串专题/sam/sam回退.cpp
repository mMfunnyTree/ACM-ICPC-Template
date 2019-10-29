#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e6+10;
int s[maxn];
int pa[maxn<<1];
map<int,int>son[maxn<<1];
int deep[maxn<<1],cnt,root,last;

inline int newnode(int _deep){
    deep[++cnt]=_deep;
    return cnt;
}
int lans;
inline void sam(int alp,int val){
    int tmp1=-1,tmp2=-1,tmpu;
    int ccnt = cnt,llast = last;

    int np=newnode(deep[last]+1);
    /**/tmp1 = np;
    int u=last;
    son[np].clear();
    while(u && !son[u][alp])son[u][alp]=np,u=pa[u];
    if(!u)pa[np]=root;
    else{
        int v=son[u][alp];
        if(deep[v]==deep[u]+1)pa[np]=v;
        else{
            int nv=newnode(deep[u]+1);
            /**/tmp2 = nv;tmpu = u;
            son[nv].clear();
            for(auto p:son[v])son[nv].insert(p);
            pa[nv]=pa[v],pa[v]=pa[np]=nv;
            while(u&&son[u][alp]==v)son[u][alp]=nv,u=pa[u];
        }
    }
    last=np;
    if(!val)return;                              /******如果val=0说明不用删除*******/
    lans = deep[np] - deep[pa[np]];              /*********记下这个字符的贡献**********/

    int uu=llast;
    while(uu && son[uu][alp]==np)son[uu][alp]=0,uu=pa[uu]; /******对应while(u && !son[u][alp])son[u][alp]=np,u=pa[u];********/
    if(tmp2!=-1){
        while(tmpu && son[tmpu][alp]==tmp2)son[tmpu][alp]=v,tmpu=pa[tmpu];/****对应while(u&&son[u][alp]==v)son[u][alp]=nv,u=pa[u];*****/
    }
    last = llast;
    cnt  = ccnt;
}

inline void pre(){
    cnt=0;
    son[1].clear();
    root=last=newnode(0);
}
int A,B;
const int mod = 1e9+7;
int main(){
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF){
        pre();
        for(int i=0;i<n;++i){
            scanf("%d",s+i);sam(s[i],0);
        }
        ll ans = 0;
        ll th = 1;
        for(int c=1;c<=m;++c){
            sam(c,1);
            th = th*3%mod;
            lans=lans*th%mod;
            ans ^= lans;
        }
        cout<<ans<<endl;
    }
    return 0;
}
