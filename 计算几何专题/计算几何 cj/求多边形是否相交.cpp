#include <cstdio>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long ll;
struct Point{
    ll x,y;
    Point(ll x=0,ll y=0):x(x),y(y) {}
    void in(){
        cin>>x>>y;
    }
};
typedef Point Vector;
inline Point operator + (Point a, Point b) { return Point(b.x + a.x, b.y + a.y); }
inline Point operator - (Point a, Point b) { return Point(a.x - b.x, a.y - b.y); }
inline bool operator < (const Point &a, const Point &b)  { return a.x == b.x ? a.y < b.y : a.x < b.x; }
inline bool operator == (const Point &a, const Point &b) { return a.x - b.x == 0 && a.y - b.y == 0; }
inline ll dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }//µã»ý
inline ll cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }//²æ»ý
bool OnSegment(Point p,Point a1,Point a2){
    return p==a1||p==a2||cross(a1-p,a2-p)==0&&dot(a1-p,a2-p)<0;
}
bool SegmenProper(Point a1,Point a2,Point b1,Point b2){
    ll c1=cross(a2-a1,b1-a1),c2=cross(a2-a1,b2-a1);
    ll c3=cross(b2-b1,a1-b1),c4=cross(b2-b1,a2-b1);
    bool flag=c1*c2<0&&c3*c4<0;
    if(OnSegment(a1,b1,b2)||OnSegment(a2,b1,b2)) flag=true;
    if(OnSegment(b1,a1,a2)||OnSegment(b2,a1,a2)) flag=true;
    return flag;
}
bool ispointinpolygon(Point* p, ll n, Point c) {
    bool flag = 0;
    for (ll i = 0, j = n - 1; i < n; j = i++) {
    if (((p[i].y > c.y) != (p[j].y > c.y)) && (1.0*c.x < 1.0*(p[j].x - p[i].x) * (c.y - p[i].y) / (p[j].y - p[i].y) + 1.0*p[i].x))
        flag = !flag;
    }
    return flag;
}
int main() {
    int ca;
    scanf("%d", &ca);
    while (ca--) {
        Point A[5],B[5];
        for(ll i=0;i<3;i++)
            A[i].in();
        for(ll i=0;i<3;i++)
            B[i].in();
        if(cross(A[1]-A[0],A[2]-A[0])<0) swap(A[1],A[2]);
        if(cross(B[1]-B[0],B[2]-B[0])<0) swap(B[1],B[2]);
        A[3]=A[0];B[3]=B[0];
        bool flag=false;
        for(ll i=0;i<3;i++){
            for(ll j=0;j<3;j++){
                if(SegmenProper(A[i],A[i+1],B[j],B[j+1])) flag=true;
            }
        }
        if(flag) printf("intersect\n");
        else{
            for(ll i=0;i<3;i++){
                if(ispointinpolygon(B,3,A[i])) flag=true;
                if(ispointinpolygon(A,3,B[i])) flag=true;
            }
            if(flag) printf("contain\n");
            else printf("disjoint\n");
        }
    }
    return 0;
}