manacherģ��
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





hdu��У�ڶ����Ļ��Ĵ��� pam + hash O(n) 
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
    int nxt[maxn][N],fail[maxn];//�ڵ�ǰ״̬��β����ַ���״̬,ʧ��������״̬
    int len[maxn],S[maxn],ppos[maxn];//״̬i��ʾ�Ļ��ĳ���,�����,״̬��Ӧ�״γ��ֵ�λ��
    int cnt[maxn],num[maxn];//״̬���ִ���,��״̬ĩβ��β������������·������Ŀ
    int last,n,p;//�ϸ�״̬,�ܳ���,��ǰ״̬���
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
