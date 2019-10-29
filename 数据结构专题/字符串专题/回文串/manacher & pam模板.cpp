manacher模板
void manacher(char s[],int len){
    int l=0;
    Ma[l++]='$';
    Ma[l++]='#';
    for(int i=0;i<len;i++){
        Ma[l++]=s[i];
        Ma[l++]='#';
    }
    Ma[l]=0;
    int mx=0,id=0;
    for(int i=0;i<l;i++){
        Mp[i]=mx>i?min(Mp[2*id-i],mx-i):1;
        while(Ma[i+Mp[i]]==Ma[i-Mp[i]])Mp[i]++;
        if(i+Mp[i]>mx){
            mx=i+Mp[i];
            id=i;
        }
    }
}





hdu多校第二场的回文串题 pam + hash O(n) 
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int N = 26;
const int maxn = 3e5+10;
const int base=31;
ull hs[maxn],ht[maxn],po[maxn];
ull geth(int l,int r){return hs[r]-po[r-l+1]*hs[l-1];}
ull gett(int l,int r){return ht[l]-po[r-l+1]*ht[r+1];}

struct pam{
    int nxt[maxn][N],fail[maxn];//在当前状态首尾添加字符的状态,失配跳到的状态
    int len[maxn],S[maxn],ppos[maxn];//状态i表示的回文长度,缓存池,状态对应首次出现的位置
    int cnt[maxn],num[maxn];//状态出现次数,以状态末尾结尾但不包含本条路径的数目
    int last,n,p;//上个状态,总长度,当前状态编号
    int newnode(int l){
        memset(nxt[p],0,sizeof nxt[p]);
        cnt[p]=num[p]=0;
        len[p]=l;
        return p++;
    }
    void init(){
        p=0;
        newnode(0);newnode(-1);
        last=n=0;
        S[n]=-1;
        fail[0]=1;
    }
    int get_fail(int x){
        while(S[n-len[x]-1]!=S[n])x=fail[x];return x;
    }
    void add(int c,int pos){
        c-='a';
        S[++n]=c;
        int cur=get_fail(last);
        if(!nxt[cur][c]){
            int now=newnode(len[cur]+2);
            ppos[now]=pos;
            fail[now]=nxt[get_fail(fail[cur])][c];
            nxt[cur][c]=now;
            num[now]=num[fail[now]]+1;
        }last=nxt[cur][c];cnt[last]++;
    }
    void Count(){
        for(int i=p-1;i>=0;--i)cnt[fail[i]]+=cnt[i];
    }
}p;
char s[maxn];
ull ans[maxn];
int main(){
    po[0]=1;for(int i=1;i<maxn;++i)po[i]=po[i-1]*base;
    while(scanf("%s",s+1)!=EOF){
        p.init();
        int len=strlen(s+1);
        for(int i=1;i<=len;++i){
            p.add(s[i],i);ans[i]=0;hs[i]=hs[i-1]*base+s[i];
        }ht[len]=s[len];
        for(int i=len-1;i;--i)ht[i]=ht[i+1]*base+s[i];
        p.Count();
        for(int i=2;i<p.p;++i){
            int mid = (2*p.ppos[i]-p.len[i]+1)/2;
            int mmid= (p.ppos[i]-p.len[i]+1+mid)/2;
            if(geth(p.ppos[i]-p.len[i]+1,mmid) == gett(mmid+( (mid - p.ppos[i]-p.len[i] ) %2==0),mid) ){
                ans[p.len[i]]+=p.cnt[i];
            }
        }
        for(int i=1;i<=len;++i){
            printf("%llu%c",ans[i]," \n"[i==len]);
        }
    }
    return 0;
}
