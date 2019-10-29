#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll count(ll n,ll x)
{
    ll ret=0,k;
    for(ll i=1;k = n/i;i*=10)
    {
        ll high = k/10;
        ret += high * i;
        ll cur  = k%10;
        if(cur>x)
        {
            ret +=i;
        }
        else if(cur==x)
        {
            ret += n-k*i +1;
        }
    }
    return ret;
}

int main()
{
    ll t;cin>>t;
    while(t--)
    {
        ll n;cin>>n;
        cout<<count(n,1)<<endl;
    }
    return 0;
}
