/**模拟退火求最小球覆盖**/
#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-15;
int n;
struct point{
    double x,y,z;
    point(){x=y=z=0;}
}p[105];
double dist(point a,point b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z));
}
double solve(){
    double step=100,ans=1e30,mt;
    point z=point();
    int s=1;
    while(step>eps){
        for(int i=1;i<=n;i++){
            if(dist(z,p[s])<dist(z,p[i]))s=i;
        }
        mt = dist(z,p[s]);
        ans = min(ans,mt);
        z.x+=(p[s].x-z.x)/mt*step;
        z.y+=(p[s].y-z.y)/mt*step;
        z.z+=(p[s].z-z.z)/mt*step;
        step*=0.98;
    }return ans;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        scanf("%lf%lf%lf",&p[i].x,&p[i].y,&p[i].z);
    }
    printf("%.10f\n",solve());
    return 0;
}
