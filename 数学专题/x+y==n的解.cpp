#include <bits/stdc++.h>
using namespace std;
int num[64];

int main()
{
	int cases,t=0;
	scanf("%d",&cases);
	while(cases--){
		int n,p=0;
		memset(num,0,sizeof(num));
		scanf("%d",&n);
		for(int i=2;i*i<=n;++i){
			if(n%i==0){
				while(n%i==0){
					++num[p];
					n/=i;
				}
				++p;
			}
		}
		if(n!=1){
			++num[p];
			++p;
		}
		for(int i=0;i<p;++i)
			num[i]*=2;
		int ans=1;
		for(int i=0;i<p;++i)
			ans*=(num[i]+1);
		printf("%d\n",(ans+1)/2);
	}
}
