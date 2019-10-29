#include <bits/stdc++.h>
using namespace std;

int n,m,t;
char s[10][10];
bool vis[10][10];
int fx[]={1,-1,0,0};
int fy[]={0,0,1,-1};

struct node{
    int x,y,step;
    node(int x=0,int y=0,int step=0):x(x),y(y),step(step){}
};


vector<node> vec;
int bfs(node st,node ed){
    memset(vis,0,sizeof vis);
    queue<node> q;
    q.push(st);
    vis[st.x][st.y]=1;

    while(!q.empty()){
        node now = q.front();q.pop();
        if(now.x==ed.x && now.y==ed.y)return
    }
}

node st,ed;

int lll(node now){
    int ret=0;
    for(int i=0;i<4;i++){
        int xx=now.x+fx[i];
        int yy=now.y+fy[i];
        if(xx<0||xx==n||yy<0||yy==m||(s[xx][yy]!='J'&&s[xx][yy]!='.'))continue;
        ret++;
    }return ret;
}

int main(){
    int c;cin>>c;
    while(c--){
        vec.clear();
        scanf("%d%d%d",&n,&m,&t);
        for(int i=0;i<n;i++){
            scanf("%s",s[i]);
            for(int j=0;j<m;j++){
                if(s[i][j]=='J'||s[i][j]=='.')vec.push_back(node(i,j,0));
                else if(s[i][j]=='S')st=node(i,j,0);
                else if(s[i][j]=='E')ed=node(i,j,0);
            }
        }
        int ans = min(lll(st),lll(ed));
        if(!ans){
            puts("0");continue;
        }
        int ans0 = 0x3f3f3f3f;
        for(int i=0;i<vec.size();i++){
            if(s[vec[i].x][vec[i].y]=='J'){
                ans0=min(ans0,bfs(st,vec[i]) + bfs(vec[i],ed));
            }
            if(ans0<0x3f3f3f3f)break;
        }
        if(ans0==0x3f3f3f3f){
            puts("0");continue;
        }
    }
    return 0;
}

