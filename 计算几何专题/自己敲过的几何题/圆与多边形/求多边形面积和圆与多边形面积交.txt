#include <bits/stdc++.h>
using namespace std;
const int N=222;
#define double long double
typedef double type;
typedef pair<type,type> Pt;
typedef pair<Pt,Pt> Line;
typedef pair<Pt,type> Circle;
#define X first
#define Y second
#define O first
#define R second
Pt operator+( const Pt& p1 , const Pt& p2 ){
  return { p1.X + p2.X , p1.Y + p2.Y };
}
Pt operator-( const Pt& p1 , const Pt& p2 ){
  return { p1.X - p2.X , p1.Y - p2.Y };
}
Pt operator*( const Pt& tp , const type& tk ){
  return { tp.X * tk , tp.Y * tk };
}
Pt operator/( const Pt& tp , const type& tk ){
  return { tp.X / tk , tp.Y / tk };
}
type operator*( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
type operator^( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
type norm2( const Pt& tp ){
  return tp * tp;
}
double norm( const Pt& tp ){
  return sqrt( norm2( tp ) );
}
Pt perp( const Pt& tp ){
  return { tp.Y , -tp.X };
}
void scan(Pt& p){
  cin>>p.X>>p.Y;
}
void print(const Pt& pp){
  cout<<fixed<<setprecision(12)<<pp.X<<" "<<pp.Y<<"\n";
}
inline double myacos(double x){
  return acosl(min((double)1., max((double)-1., x)));
}
const double eps=1e-8;
int n, m;
Pt p[N], q[N], target;
const int K=60;
const int B=60;
double Area(){
  double ret=0;
  for(int i=0; i<n; i++)
    ret+=p[i]^p[(i+1)%n];
  return fabs(ret*.5);
}
const Pt O={0, 0};
double dist2O(const Pt& p1, const Pt& p2){
  double ret=min(norm(p1), norm(p2));
  if(((O-p1)*(p2-p1)) < -eps) return ret;
  if(((O-p2)*(p1-p2)) < -eps) return ret;
  return fabs((p2-p1)^(O-p1))/norm(p2-p1);
}
double cal(Pt p1, Pt p2, double R){
  if(norm(p1-p2)<eps) return 0;
  if(norm(p1)<R+eps and norm(p2)<R+eps)
    return fabs(p1^p2)*.5;
  if(dist2O(p1, p2)>R-eps){
    double alpha=myacos((p1*p2)/norm(p1)/norm(p2));
    return fabs(alpha*R*R*.5);
  }
  if(norm(p2) < norm(p1)) swap(p1, p2);
  if(norm(p1) < R+eps){
    Pt mid=p1;
    {
      double bl=0, br=1;
      Pt dlt=p2-p1;
      for(int _=0; _<B; _++){
        double bmid=(bl+br)*.5;
        Pt tmp=p1+dlt*bmid;
        if(norm(tmp)<R) bl=bmid;
        else br=bmid;
      }
      mid=p1+dlt*br;
    }
    return cal(p1, mid, R)+cal(p2, mid, R);
  }
  double mp=((p2-p1)*(O-p1))/norm2(p2-p1);
  Pt mid1=p1, mid2=p2;
  {
    double bl=0, br=mp;
    Pt dlt=p2-p1;
    for(int _=0; _<B; _++){
      double bmid=(bl+br)*.5;
      Pt tmp=p1+dlt*bmid;
      if(norm(tmp)>R) bl=bmid;
      else br=bmid;
    }
    mid1=p1+dlt*br;
  }
  {
    double bl=1, br=mp;
    Pt dlt=p2-p1;
    for(int _=0; _<B; _++){
      double bmid=(bl+br)*.5;
      Pt tmp=p1+dlt*bmid;
      if(norm(tmp)>R) bl=bmid;
      else br=bmid;
    }
    mid2=p1+dlt*br;
  }
  return cal(p1, mid1, R)+
         cal(mid1, mid2, R)+
         cal(mid2, p2, R);
}
double cal(double R){
  double ret=0;
  for(int i=0; i<n; i++){
    double arr=cal(q[i], q[(i+1)%n], R);
    if((q[i]^q[(i+1)%n])>0) ret+=arr;
    else ret-=arr;
  }
  return fabs(ret);
}
int main(){
  cin>>n;
  for(int i=0; i<n; i++) scan(p[i]);
  double area=Area();
  cin>>m; while(m--){
    scan(target);
    double P, Q;
    cin>>P>>Q;
    double goal=(1.-P/Q)*area;
    for(int i=0; i<n; i++) q[i]=p[i]-target;
    double bl=0, br=1e4;
    for(int i=0; i<K; i++){
      double bmid=(bl+br)*.5;
      double ret=cal(bmid);
      if(ret<goal) bl=bmid;
      else br=bmid;
    }
    cout<<fixed<<setprecision(12)<<br<<"\n";
  }
}
