#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
typedef long double ld;
const ld pi=acosl(-1.0L);
ld area(ld x,ld y,ld r,ld xx,ld yy,ld rr)
{
    if(r>rr) swap(r,rr);
    ld d=sqrtl((x-xx)*(x-xx)+(y-yy)*(y-yy));
    if(d>=r+rr) return 0;
    if(d<=rr-r) return pi*r*r;
    ld k=acosl((r*r+d*d-rr*rr)/(d*r*2));
    ld kk=acosl((rr*rr+d*d-r*r)/(d*rr*2));
    return r*r*k+rr*rr*kk-sinl(k)*(r*r+d*d-rr*rr)/(2*d)*r-sinl(kk)*(rr*rr+d*d-r*r)/(2*d)*rr;
}
int main()
{
    ld x,x0,y,y0,r,r0;
    cin>>x>>y>>r>>x0>>y0>>r0;
    cout.precision(20);
    cout<<fixed<<area(x,y,r,x0,y0,r0)<<endl;
    return 0;
}
/*
D. Area of Two Circles' Intersection
time limit per test2 seconds
memory limit per test256 megabytes
inputstandard input
outputstandard output
You are given two circles. Find the area of their intersection.

Input
The first line contains three integers x1,?y1,?r1 (?-?109?¡Ü?x1,?y1?¡Ü?109,?1?¡Ü?r1?¡Ü?109) ¡ª the position of the center and the radius of the first circle.

The second line contains three integers x2,?y2,?r2 (?-?109?¡Ü?x2,?y2?¡Ü?109,?1?¡Ü?r2?¡Ü?109) ¡ª the position of the center and the radius of the second circle.

Output
Print the area of the intersection of the circles. The answer will be considered correct if the absolute or relative error doesn't exceed 10?-?6.

Sample test(s)
input
0 0 4
6 0 4
output
7.25298806364175601379
input
0 0 5
11 0 5
output
0.00000000000000000000
*/
