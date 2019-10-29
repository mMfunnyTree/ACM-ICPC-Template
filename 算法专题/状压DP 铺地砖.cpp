/*优化:不去盲目的列举所有状态i和j然后判断状态j能否到达i,这样效率很低,因为能到达i的状态j很少
因此对于每种状态i,由i区搜索能到达i的状态j,大大提高效率
有298ms->32ms
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <queue>
#include <algorithm>
#include <map>
#include <cmath>
#include <iomanip>
#define INF 99999999
typedef long long LL;
using namespace std;

const int MAX=(1<<11)+10;
int n,m;
LL temp[MAX],dp[MAX],bin[15];

bool check(int i){
	while(i){
		if(i&1){
			i>>=1;
			if(!(i&1))return false;//第j列是1则第j+1列必须是1
			i>>=1;//继续判断下一列
		}else i>>=1;//继续判断下一列
	}
	return true;
}

void Init(){
	memset(temp,0,sizeof temp);
	for(int i=0;i<bin[m];++i)if(check(i))temp[i]=1;//初始化第一行
}

void dfs(int k,int i,int j){
	if(k == m){dp[i]+=temp[j];return;}
	if(k>m)return;
	if((i>>k)&1){
		dfs(k+1,i,j);
		if((i>>(k+1))&1)dfs(k+2,i,j|(1<<k)|(1<<(k+1)));
	}
	else dfs(k+1,i,j|(1<<k));
}

void DP(){
	for(int k=2;k<=n;++k){
		for(int i=0;i<bin[m];++i)dp[i]=0;
		for(int i=0;i<bin[m];++i)dfs(0,i,0);
		for(int i=0;i<bin[m];++i)temp[i]=dp[i];
	}
}

int main(){
	bin[0]=1;
	for(int i=1;i<12;++i)bin[i]=2*bin[i-1];
	while(~scanf("%d%d",&n,&m),n+m){
		if(n<m)swap(n,m);//始终保持m<n,提高效率
		Init();
		DP();
		printf("%lld\n",temp[bin[m]-1]);//输出最后一行到达时的状态必须全部是1
	}
	return 0;
}
