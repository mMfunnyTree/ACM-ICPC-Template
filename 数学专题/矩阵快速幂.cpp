#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007
struct mat{
    ll a[2][2];
    mat(){memset(a,0,sizeof(a));}
    mat operator * (const mat& b)const{
        mat ret=mat();
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                for(int k=0;k<2;k++){
                    ret.a[i][j]=(ret.a[i][j]+a[i][k]*b.a[k][j]+mod)%mod;
                }
            }
        }return ret;
    }
    mat operator *= (const mat& b){
        return *this = *this*b;
    }
};
mat qpow(mat a,ll n){
    mat ret=mat();
    for(int i=0;i<2;i++)ret.a[i][i]=1;
    while(n){
        if(n&1){
            ret*=a;
        }a*=a;
        n>>=1;
    }return ret;
}

int main(){
    int x,y,n;
    cin>>x>>y>>n;
    x+=mod;y+=mod;
    mat a = mat();
    a.a[0][0]=1;a.a[0][1]=1;
    a.a[1][0]=1e9+6;a.a[1][1]=0;
    if(n==1)return cout<<x%mod,0;
    a = qpow(a,n-2);
    cout<<((a.a[0][0]*y)%mod - (a.a[0][1]*x)%mod+mod)%mod<<endl;
    return 0;
}
