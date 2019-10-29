#include <bits/stdc++.h>
using namespace std;
typedef long long int LL ;
const int N = 100000+7;

#define abs(x)  (((x)>0)?(x):-(x))

/***************************************/


const double PI  = acos(-1.0);
const double eps = 1e-8;
const double INF = 1e18;
#define pb push_back
#define mp make_pair

///*************基础***********/
double torad(double deg) { return deg / 180 * PI; }
inline int dcmp(double x)
{
    if(fabs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
}
struct Point
{
    double x, y;
    Point(double x=0, double y=0):x(x),y(y) { }
    inline void read()
    {
        scanf("%lf%lf", &x, &y);
    }
};
typedef vector<Point> Polygon;
typedef Point Vector;

inline Vector operator+ (Vector A, Vector B) { return Vector(A.x + B.x, A.y + B.y); }
inline Vector operator- (Point A, Point B) { return Vector(A.x - B.x, A.y - B.y); }
inline Vector operator* (Vector A, double p) { return Vector(A.x * p, A.y * p); }
inline Vector operator/ (Vector A, double p) { return Vector(A.x / p, A.y / p); }

inline bool operator < (Point a, Point b) { return a.x < b.x || (a.x == b.x && a.y < b.y); }
inline bool operator == (Point a, Point b) { return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0; }

inline double Dot(Vector A, Vector B){ return A.x * B.x + A.y * B.y;}
double msqrt(double x) {
    if(x<0) return 0;
    else return sqrt(x);
}
double Length(Vector A) { return msqrt(Dot(A, A)); }
double Length2(Vector A) { return Dot(A, A); }
inline double Angle(Vector A, Vector B) { return acos(Dot(A, B) / Length(A) / Length(B)); }
inline double angle(Vector v) { return atan2(v.y, v.x); }
inline double Cross(Vector A, Vector B) { return A.x * B.y - A.y * B.x; }//A x B > 0表示A在B的顺时针方向上
inline Vector Unit(Vector x) { return x / Length(x); }  //单位向量
inline Vector Normal(Vector x) { return Point(-x.y, x.x) / Length(x); } //垂直法向量
inline double Area2(Point A, Point B, Point C) { return Cross(B - A, C - A); }
double Cross3(Point p0,Point p1,Point p2)  {return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);}///返回结果为正说明p0p1在p0p2的顺时针方向，正说明p2在向量p0p1的左边（三点构成逆时针方向）
                                                                                                    ///也可以说明p0在向量p1p2的左边（三点构成逆时针方向）,为负则相反,为0则三点共线(叉积的性质很重要)
inline Vector Rotate(Vector A, double rad)
{
    return Vector(A.x * cos(rad) - A.y*sin(rad), A.x*sin(rad) + A.y * cos(rad));
}
/****************直线与线段**************/


//求直线p+tv和q+tw的交点 Cross(v, w) == 0无交点
Point GetLineIntersection(Point p, Vector v, Point q, Vector w)
{
    Vector u = p - q;
    double t = Cross(w, u) / Cross(v, w);
    return p + v * t;
}

//线段到直线的方位
int SegToLine(Point a,Point b,Point c,Point d) {///Seg:ab  Line:cd  已验证
    int x = dcmp(Cross3(a,c,d));
    int y = dcmp(Cross3(b,c,d));
    if(x==y&&y==0) return 0;//线上
    if(x+y==2) return 1;//同侧 左边
    if(x+y==-2) return 2;//同侧 右边
    if(x+y==0) return -1;//异侧
    if(x+y==1) return -2;//一点在线上，另一点左边
    return -3;//一点在线上，另一点右边
}

//直线ab与直线cd的交点
Point LineToLine(Point a,Point b,Point c,Point d) {   ///已验证
    double x = Cross3(a,c,d),y = Cross3(b,c,d);
    int xx=dcmp(x),yy=dcmp(y);
    if(xx==yy&&xx==0) return {-1e10,1e10};//重合
    else if(dcmp(x-y)==0) return {-1e10,-1e10};//平行
    else {
        Vector u = a-c;
        Vector v = (b-a)/Length((b-a));
        Vector w = (d-c)/Length((d-c));
        return a + (Point)(v*(Cross(w,u)/Cross(v,w)));
    }
}

//点p在直线ab的投影
inline Point GetLineProjection(Point P, Point A, Point B) { ///已验证
    Vector v = B - A;
    return A + v * (Dot(v, P - A) / Dot(v, v));
}


//点到直线距离
inline double DistanceToLine(Point P, Point A, Point B) ///已验证
{
    Vector v1 = B - A, v2 = P - A;
    return fabs(Cross(v1, v2)) / Length(v1); // 如果不取绝对值，得到的是有向距离
}
//点在p线段上(包括端点)
inline bool OnSegment(Point p, Point a1, Point a2)
{
    return dcmp(Cross(a1-p, a2-p)) == 0 && dcmp(Dot(a1-p, a2-p)) <= 0;
}
// 过两点p1, p2的直线一般方程ax+by+c=0
// (x2-x1)(y-y1) = (y2-y1)(x-x1)
inline void getLineGeneralEquation(Point p1, Point p2, double& a, double& b, double &c)
{
    a = p2.y - p1.y;
    b = p1.x - p2.x;
    c = -a * p1.x - b * p1.y;
}
//点到线段距离
double DistanceToSegment(Point p, Point a, Point b) ///已验证
{
    if(a == b) return Length(p - a);
    Vector v1 = b - a, v2 = p - a, v3 = p - b;
    if(dcmp(Dot(v1, v2)) < 0) return Length(v2);
    else if(dcmp(Dot(v1, v3)) > 0) return Length(v3);
    else return fabs(Cross(v1, v2)) / Length(v1);
}
//两线段最近距离
inline double dis_pair_seg(Point p1, Point p2, Point p3, Point p4)
{
    return min(min(DistanceToSegment(p1, p3, p4), DistanceToSegment(p2, p3, p4)),
               min(DistanceToSegment(p3, p1, p2), DistanceToSegment(p4, p1, p2)));
}
//线段相交判定
inline bool SegmentProperIntersection(Point a, Point b, Point c, Point d)
{
    if(max(a.x , b.x) < min(c.x , d.x)) return false;
    if(max(a.y , b.y) < min(c.y , d.y)) return false;
    if(max(c.x , d.x) < min(a.x , b.x)) return false;
    if(max(c.y , d.y) < min(a.y , b.y)) return false;
    return dcmp(Cross(b-a,c-a))*dcmp(Cross(b-a,d-a))<=0
    && dcmp(Cross(d-c,a-c))*dcmp(Cross(d-c,b-c))<=0;
}
// 有向直线。它的左边就是对应的半平面
struct Line
{
    Point p, q;    // 直线上任意一点,p作为起点
    Vector v;   // 方向向量
    double ang; // 极角，即从x正半轴旋转到向量v所需要的角（弧度）
    Line() {}
//    Line(Point P, Vector v):p(P),v(v)
//    {
//        ang = atan2(v.y, v.x);
//    }
    Line(Point P, Point Q):p(P), q(Q)
    {
        v = q - p;
        ang = atan2(v.y, v.x);
    }
    inline bool operator < (const Line& L) const
    {
        return ang < L.ang;
    }
    inline Point point(double t)
    {
        return p + v * t;
    }
    inline Line move(double d)
    {
        return Line(p + Normal(v) * d, v);
    }
    inline void read()
    {
        Point q;
        p.read(), q.read();
        v = q - p;
        ang = atan2(v.y, v.x);
    }
};
//两直线交点
inline Point GetLineIntersection(Line a, Line b) ///已验证
{
    return GetLineIntersection(a.p, a.v, b.p, b.v);
}


// 点p在有向直线L的左边（线上不算）
bool OnLeft(const Line& L, const Point& p) ///已验证
{
    return Cross(L.v, p - L.p) > 0;
}

int PointToLine(Point p,Point a,Point b) {///1:左 -1:右 0:线上 已验证
    return dcmp(Cross3(p, a, b));
}

//// 二直线交点，假定交点惟一存在
//Point GetLineIntersection(const Line& a, const Line& b) {
//  Vector u = a.P-b.P;
//  double t = Cross(b.v, u) / Cross(a.v, b.v);
//  return a.P+a.v*t;
//}


// 半平面交主过程
vector<Point> HalfplaneIntersection(vector<Line> L) ///已验证
{
    int n = L.size();
    sort(L.begin(), L.end()); // 按极角排序

    int first, last;         // 双端队列的第一个元素和最后一个元素的下标
    vector<Point> p(n);      // p[i]为q[i]和q[i+1]的交点
    vector<Line> q(n);       // 双端队列
    vector<Point> ans;       // 结果

    q[first=last=0] = L[0];  // 双端队列初始化为只有一个半平面L[0]
    for(int i = 1; i < n; i++)
    {
        while(first < last && !OnLeft(L[i], p[last-1])) last--;
        while(first < last && !OnLeft(L[i], p[first])) first++;
        q[++last] = L[i];
        if(fabs(Cross(q[last].v, q[last-1].v)) < eps)   // 两向量平行且同向，取内侧的一个
        {
            last--;
            if(OnLeft(q[last], L[i].p)) q[last] = L[i];
        }
        if(first < last) p[last-1] = GetLineIntersection(q[last-1], q[last]);
    }
    while(first < last && !OnLeft(q[first], p[last-1])) last--; // 删除无用平面
    if(last - first <= 1) return ans; // 空集
    p[last] = GetLineIntersection(q[last], q[first]); // 计算首尾两个半平面的交点


    // 从deque复制到输出中
    for(int i = first; i <= last; i++) ans.push_back(p[i]);
    return ans;
}


/***********多边形**************/
//求多边形面积
double PolygonArea(vector<Point> p) { ///已验证
  int n = p.size();
  double area = 0;
  for(int i = 1; i < n - 1; i++)
    area += Cross(p[i]-p[0], p[i+1]-p[0]);
  return area / 2;
}

//判断点是否在多边形内
int isPointInPolygon(Point p, Polygon poly) /// 已验证
{
    int wn = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++)
    {
        if (OnSegment(p, poly[i], poly[(i + 1) % n])) return -1;    //边界
        int k = dcmp(Cross(poly[(i + 1) % n] - poly[i], p - poly[i]));
        int d1 = dcmp(poly[i].y - p.y);
        int d2 = dcmp(poly[(i + 1) % n].y - p.y);
        if (k > 0 && d1 <= 0 && d2 > 0) wn++;
        if (k < 0 && d2 <= 0 && d1 > 0) wn--;
    }
    if (wn != 0) return 1;  //内部
    return 0;   //外部
}


//多边形重心 点集逆时针给出
Point PolyGravity(Point *p, int n) {
    Point tmp, g = Point(0, 0);
    double sumArea = 0, area;
    for (int i=2; i<n; ++i) {
        area = Cross(p[i-1]-p[0], p[i]-p[0]);
        sumArea += area;
        tmp.x = p[0].x + p[i-1].x + p[i].x;
        tmp.y = p[0].y + p[i-1].y + p[i].y;
        g.x += tmp.x * area;
        g.y += tmp.y * area;
    }
    g.x /= (sumArea * 3.0); g.y /= (sumArea * 3.0);
    return g;
}


//多边形重心计算模板
Point bcenter(vector<Point> pnt) ///已验证
{
    int n = pnt.size();
    Point p, s;
    double tp, area = 0, tpx = 0, tpy = 0;
    p.x = pnt[0].x;
    p.y = pnt[0].y;
    //FE(i, 1, n)
    for(int i=1;i<=n;i++)
    {
        s.x = pnt[(i == n) ? 0 : i].x;
        s.y = pnt[(i == n) ? 0 : i].y;
        tp = (p.x * s.y - s.x * p.y);
        area += tp / 2;
        tpx += (p.x + s.x) * tp;
        tpy += (p.y + s.y) * tp;
        p.x = s.x;
        p.y = s.y;
    }
    s.x = tpx / (6 * area);
    s.y = tpy / (6 * area);
    return s;
}

// 点集凸包
// 如果希望在凸包的边上有输入点，把两个 <= 改成 <
// 注意：输入点集会被修改
vector<Point> ConvexHull(vector<Point>& p) /// 已验证
{
    // 预处理，删除重复点
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    int n = p.size();
    int m = 0;
    vector<Point> ch(n+1);
    for(int i = 0; i < n; i++)
    {
        while(m > 1 && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    int k = m;
    for(int i = n-2; i >= 0; i--)
    {
        while(m > k && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    if(n > 1) m--;
    ch.resize(m);
    return ch;
}


inline double Dist2(Point a, Point b)
{
    return msqrt(a.x - b.x) + msqrt(a.y - b.y);
}


// 返回点集直径的平方
double diameter2(vector<Point>& points)
{
    vector<Point> p = ConvexHull(points);
    int n = p.size();
    if(n == 1) return 0;
    if(n == 2) return Dist2(p[0], p[1]);
    p.push_back(p[0]); // 免得取模
    double ans = 0;
    for(int u = 0, v = 1; u < n; u++)
    {
        // 一条直线贴住边p[u]-p[u+1]
        for(;;)
        {
            // 当Area(p[u], p[u+1], p[v+1]) <= Area(p[u], p[u+1], p[v])时停止旋转
            // 即Cross(p[u+1]-p[u], p[v+1]-p[u]) - Cross(p[u+1]-p[u], p[v]-p[u]) <= 0
            // 根据Cross(A,B) - Cross(A,C) = Cross(A,B-C)
            // 化简得Cross(p[u+1]-p[u], p[v+1]-p[v]) <= 0
            int diff = Cross(p[u+1]-p[u], p[v+1]-p[v]);
            if(diff <= 0)
            {
                ans = max(ans, Dist2(p[u], p[v])); // u和v是对踵点
                if(diff == 0)
                    ans = max(ans, Dist2(p[u], p[v+1])); // diff == 0时u和v+1也是对踵点
                break;
            }
            v = (v + 1) % n;
        }
    }
    return ans;
}

//两凸包最近距离
double RC_Distance(Point *ch1, Point *ch2, int n, int m)
{
    int q=0, p=0;
    //REP(i, n)
    for(int i=1;i<=n;i++)
    if(ch1[i].y-ch1[p].y < -eps) p=i;
    //REP(i, m)
    for(int i=1;i<=m;i++)
    if(ch2[i].y-ch2[q].y > eps) q=i;
    ch1[n]=ch1[0];
    ch2[m]=ch2[0];


    double tmp, ans=1e100;
    //REP(i, n)
    for(int i=1;i<=n;i++)
    {
        while((tmp = Cross(ch1[p+1]-ch1[p], ch2[q+1]-ch1[p]) - Cross(ch1[p+1]-ch1[p], ch2[q]- ch1[p])) > eps)
            q=(q+1)%m;
        if(tmp < -eps) ans = min(ans,DistanceToSegment(ch2[q],ch1[p],ch1[p+1]));
        else ans = min(ans,dis_pair_seg(ch1[p],ch1[p+1],ch2[q],ch2[q+1]));
        p=(p+1)%n;
    }
    return ans;
}

//两凸包最近距离
//使用vector
double RC_Distance(vector<Point> ch1, vector<Point> ch2)
{
    int q = 0, p = 0, n = ch1.size(), m = ch2.size();
    //REP(i, n)
    for(int i=1;i<=n;i++)
    if(ch1[i].y-ch1[p].y < -eps) p=i;
    //REP(i, m)
    for(int i=1;i<=m;i++)
    if(ch2[i].y-ch2[q].y > eps) q=i;
    ch1.push_back(ch1[0]), ch2.push_back(ch2[0]);


    double tmp, ans=1e100;
    //REP(i, n)
    for(int i=1;i<=n;i++)
    {
        while((tmp = Cross(ch1[p+1]-ch1[p], ch2[q+1]-ch1[p]) - Cross(ch1[p+1]-ch1[p], ch2[q]- ch1[p])) > eps)
            q=(q+1)%m;
        if(tmp < -eps) ans = min(ans,DistanceToSegment(ch2[q],ch1[p],ch1[p+1]));
        else ans = min(ans,dis_pair_seg(ch1[p],ch1[p+1],ch2[q],ch2[q+1]));
        p=(p+1)%n;
    }
    return ans;
}

//凸包最大内接三角形
double RC_Triangle(Point* res,int n)
{
    if(n < 3)    return 0;
    double ans = 0, tmp;
    res[n] = res[0];
    int j, k;
    //REP(i, n)
    for(int i=1;i<=n;i++)
    {
        j = (i+1)%n;
        k = (j+1)%n;
        while((j != k) && (k != i))
        {
            while(Cross(res[j] - res[i], res[k+1] - res[i]) > Cross(res[j] - res[i], res[k] - res[i])) k= (k+1)%n;
            tmp = Cross(res[j] - res[i], res[k] - res[i]);
            if(tmp > ans) ans = tmp;
            j = (j+1)%n;
        }
    }
    return ans;
}

//凸包最大内接三角形
double RC_Triangle(vector<Point> res, Point& a, Point& b, Point& c)
{
    int n = res.size();
    if(n < 3)    return 0;
    double ans=0, tmp;
    res.push_back(res[0]);
    int j, k;
    //REP(i, n)
    for(int i=1;i<=n;i++)
    {
        j = (i+1)%n;
        k = (j+1)%n;
        while((j != k) && (k != i))
        {
            while(Cross(res[j] - res[i], res[k+1] - res[i]) > Cross(res[j] - res[i], res[k] - res[i])) k= (k+1)%n;
            tmp = Cross(res[j] - res[i], res[k] - res[i]);
            if(tmp > ans)
            {
                a = res[i], b = res[j], c = res[k];
                ans = tmp;
            }
            j = (j+1)%n;
        }
    }
    return ans;
}


//判断两凸包是否有交点
bool ConvexPolygonDisjoint(const vector<Point> ch1, const vector<Point> ch2)
{
    int c1 = ch1.size();
    int c2 = ch2.size();
    for(int i = 0; i < c1; i++)
        if(isPointInPolygon(ch1[i], ch2) != 0)
            return false; // 内部或边界上
    for(int i = 0; i < c2; i++)
        if(isPointInPolygon(ch2[i], ch1) != 0)
            return false; // 内部或边界上
    for(int i = 0; i < c1; i++)
        for(int j = 0; j < c2; j++)
            if(SegmentProperIntersection(ch1[i], ch1[(i+1)%c1], ch2[j], ch2[(j+1)%c2]))
                return false;
    return true;
}

inline double dist(Point a, Point b)
{
    return Length(a - b);
}

////模拟退火求费马点 保存在ptres中
//double fermat_point(Point *pt, int n, Point& ptres)
//{
//    Point u, v;
//    double step = 0.0, curlen, explen, minlen;
//    int i, j, k;
//    bool flag;
//    u.x = u.y = v.x = v.y = 0.0;
//    //REP(i, n)
//    for(int i=1;i<=n;i++)
//    {
//        step += fabs(pt[i].x) + fabs(pt[i].y);
//        u.x += pt[i].x;
//        u.y += pt[i].y;
//    }
//    u.x /= n;
//    u.y /= n;
//    flag = 0;
//    while(step > eps)
//    {
//        for(k = 0; k < 10; step /= 2, ++k)
//            for(i = -1; i <= 1; ++i)
//                for(j = -1; j <= 1; ++j)
//                {
//                    v.x = u.x + step*i;
//                    v.y = u.y + step*j;
//                    curlen = explen = 0.0;
//                    //REP(i, n)
//                    for(int i=1;i<=n;i++)
//                    {
//                        curlen += dist(u, pt[idx]);
//                        explen += dist(v, pt[idx]);
//                    }
//                    if(curlen > explen)
//                    {
//                        u = v;
//                        minlen = explen;
//                        flag = 1;
//                    }
//                }
//    }
//    ptres = u;
//    return flag ? minlen : curlen;
//}

//多边形费马点
//到所有顶点的距离和最小
Point Fermat(int np, Point* p)
{
    double nowx = 0, nowy = 0;
    double nextx = 0, nexty = 0;
    //REP(i, np)
    for(int i=1;i<=np;i++)
    {
        nowx += p[i].x;
        nowy += p[i].y;
    }
    for (nowx /= np, nowy /= np;; nowx = nextx, nowy = nexty)
    {
        double topx = 0, topy = 0, bot = 0;
        //REP(i, np)
        for(int i=1;i<=np;i++)
        {
            double d = msqrt(msqrt(nowx - p[i].x) + msqrt(nowy - p[i].y));
            topx += p[i].x / d;
            topy += p[i].y / d;
            bot += 1 / d;
        }
        nextx = topx / bot;
        nexty = topy / bot;
        if (dcmp(nextx - nowx) == 0 && dcmp(nexty - nowy) == 0)
            break;
    }
    Point fp;
    fp.x = nowx;
    fp.y = nowy;
    return fp;
}


//最近点对
//使用前先对输入的point进行排序,使用cmpxy函数
Point point[N];
int tmpt[N];
inline double dist(int x, int y)
{
    Point& a = point[x];
    Point& b = point[y];
    return msqrt(msqrt(a.x - b.x) + msqrt(a.y - b.y));
}
inline bool cmpxy(Point a, Point b)
{
    if(a.x != b.x)
        return a.x < b.x;
    return a.y < b.y;
}
inline bool cmpy(int a, int b)
{
    return point[a].y < point[b].y;
}
double Closest_Pair(int left, int right)
{
    double d = INF;
    if(left==right)
        return d;
    if(left + 1 == right)
        return dist(left, right);
    int mid = (left+right)>>1;
    double d1 = Closest_Pair(left,mid);
    double d2 = Closest_Pair(mid+1,right);
    d = min(d1,d2);
    int k=0;
    //分离出宽度为d的区间
    //FE(i, left, right)
    for(int i=left;i<=right;i++)
    {
        if(fabs(point[mid].x-point[i].x) <= d)
            tmpt[k++] = i;
    }
    sort(tmpt,tmpt+k,cmpy);
    //线性扫描
    //REP(i, k)
    for(int i=0;i<k;i++)
    {
        for(int j = i+1; j < k && point[tmpt[j]].y-point[tmpt[i]].y<d; j++)
        {
            double d3 = dist(tmpt[i],tmpt[j]);
            if(d > d3)
                d = d3;
        }
    }
    return d;
}


/************圆************/
struct Circle
{
    Point c;
    double r;
    Circle() {}
    Circle(Point c, double r):c(c), r(r) {}
    inline Point point(double a) //根据圆心角求点坐标
    {
        return Point(c.x+cos(a)*r, c.y+sin(a)*r);
    }
    inline void read()
    {
        scanf("%lf%lf%lf", &c.x, &c.y, &r);
    }
};

//求a点到b点(逆时针)在的圆上的圆弧长度
double DisOnCircle(Point a, Point b, Circle C)
{
    double ang1 = angle(a - C.c);
    double ang2 = angle(b - C.c);
    if (ang2 < ang1) ang2 += 2 * PI;
    return C.r * (ang2 - ang1);
}

//直线与圆交点 返回个数
int LineCircle(Point p1,Point p2,Circle c ,vector<Point>& p) { /// 已验证
    Point m = GetLineProjection(c.c, p1, p2);
    double h2 = Length2(c.c-m);
    int fg = dcmp(c.r*c.r-h2);
    double len = Length(p2-p1);
    if(!fg){
        p.push_back(m);
        return 1;
    }else if(fg>0) {
        double rate = msqrt(c.r*c.r-h2)/len;
        p.push_back(m-(p2-p1)*rate);
        p.push_back(m+(p2-p1)*rate);
        return 2;
    }else return 0;
}

//两圆交点 返回个数
int getCircleCircleIntersection(Circle C1, Circle C2, vector<Point>& sol) { ///已验证
    double d = Length(C1.c - C2.c);
    if(dcmp(d) == 0) {
        if(dcmp(C1.r - C2.r) == 0) return -1; // 重合，无穷多交点
        return 0;
    }
    if(dcmp(C1.r + C2.r - d) < 0) return 0;
    if(dcmp(fabs(C1.r-C2.r) - d) > 0) return 0;


    double a = angle(C2.c - C1.c);
    double da = acos((C1.r*C1.r + d*d - C2.r*C2.r) / (2*C1.r*d));
    Point p1 = C1.point(a-da), p2 = C1.point(a+da);
    sol.push_back(p1);
    if(p1 == p2) return 1;
    sol.push_back(p2);
    return 2;
}


//两圆的公切线, -1表示无穷条切线
//返回切线的条数, -1表示无穷条切线
//a[i]和b[i]分别是第i条切线在圆A和圆B上的切点
int getTangents(Circle A, Circle B, Point* a, Point* b) ///已验证
{
    int cnt = 0;
    if (A.r < B.r) swap(A, B), swap(a, b);
    ///****************************
    long long d2 = (A.c.x - B.c.x) * (A.c.x - B.c.x) + (A.c.y - B.c.y) * (A.c.y - B.c.y);
    long long rdiff = A.r - B.r;
    long long rsum = A.r + B.r;
    if (d2 < rdiff * rdiff) return 0;   //内含

    ///***************************************
    double base = atan2(B.c.y - A.c.y, B.c.x - A.c.x);
    if (d2 == 0 && A.r == B.r) return -1;    //无线多条切线
    if (d2 == rdiff * rdiff)    //内切, 1条切线
    {
        ///**********************
        a[cnt] = A.point(base); b[cnt] = B.point(base); cnt++;
        return 1;
    }
    //有外公切线
    double ang = acos((A.r - B.r) / msqrt(d2 * 1.0));
    a[cnt] = A.point(base + ang); b[cnt] = B.point(base + ang); cnt++;
    a[cnt] = A.point(base - ang); b[cnt] = B.point(base - ang); cnt++;
    if (d2 == rsum * rsum)  //一条内公切线
    {
        a[cnt] = A.point(base); b[cnt] = B.point(PI + base); cnt++;
    }
    else if (d2 > rsum * rsum)  //两条内公切线
    {
        double ang = acos((A.r + B.r) / msqrt(d2 * 1.0));
        a[cnt] = A.point(base + ang); b[cnt] = B.point(PI + base + ang); cnt++;
        a[cnt] = A.point(base - ang); b[cnt] = B.point(PI + base - ang); cnt++;
    }
    return cnt;
}



// 过点p到圆C的切线。v[i]是第i条切线的向量。返回切线条数
int getTangents(Point p,Circle c,vector<Point>& v) {//存入的向量
    Vector u = c.c - p;
    double dist = Length(u);
    if(dist < c.r) return 0;
    else if(dcmp(dist - c.r) == 0){   // p在圆上，只有一条切线
        v.push_back(Rotate(u, PI/2));
        return 1;
    }else{
        double ang = asin(c.r / dist);
        v.push_back(Rotate(u, -ang));
        v.push_back(Rotate(u, ang));
        return 2;
    }
}



// 过点p到圆C的切点
int getTangentPoints(Point p, Circle C, vector<Point>& v) /// 已验证
{
    Vector u = C.c - p;
    double dist = Length(u);
    if(dist < C.r) return 0;
    else if(dcmp(dist - C.r) == 0)   // p在圆上，只有一条切线
    {
        v.push_back(p);
        return 1;
    }
    else
    {
        double ang = asin(C.r / dist);
        double d = msqrt(dist * dist - C.r * C.r);
        v.push_back(p + Unit(Rotate(u, -ang)) * d);
        v.push_back(p + Unit(Rotate(u, +ang)) * d);
        return 2;
    }
}

//圆A与圆B的切点
void getTangentPoints(Circle A, Circle B, vector<Point>& a)
{
    if (A.r < B.r) swap(A, B);
    ///****************************
    long long d2 = msqrt(A.c.x - B.c.x) + msqrt(A.c.y - B.c.y);
    long long rdiff = A.r - B.r, rsum = A.r + B.r;
    if (d2 < rdiff * rdiff) return;   //内含

    ///***************************************
    double base = atan2(B.c.y - A.c.y, B.c.x - A.c.x);
    if (d2 == 0 && A.r == B.r) return;    //无线多条切线
    if (d2 == rdiff * rdiff)    //内切, 1条切线
    {
        ///**********************
        a.push_back(A.point(base));
        a.push_back(B.point(base));
        return;
    }
    //有外公切线
    double ang = acos((A.r - B.r) / msqrt(d2 * 1.0));
    a.push_back(A.point(base + ang)); a.push_back(B.point(base + ang));
    a.push_back(A.point(base - ang)); a.push_back(B.point(base - ang));
    if (d2 == rsum * rsum)  //一条内公切线
    {
        a.push_back(A.point(base));
        a.push_back(B.point(PI + base));
    }
    else if (d2 > rsum * rsum)  //两条内公切线
    {
        double ang = acos((A.r + B.r) / msqrt(d2 * 1.0));
        a.push_back(A.point(base + ang));
        a.push_back(B.point(PI + base + ang));
        a.push_back(A.point(base - ang));
        a.push_back(B.point(PI + base - ang));
    }
}


//三角形外接圆
Circle CircumscribedCircle(Point p1, Point p2, Point p3) /// 已验证
{
    double Bx = p2.x-p1.x, By = p2.y-p1.y;
    double Cx = p3.x-p1.x, Cy = p3.y-p1.y;
    double D = 2*(Bx*Cy-By*Cx);
    double cx = (Cy*(Bx*Bx+By*By) - By*(Cx*Cx+Cy*Cy))/D + p1.x;
    double cy = (Bx*(Cx*Cx+Cy*Cy) - Cx*(Bx*Bx+By*By))/D + p1.y;
    Point p = Point(cx, cy);
    return Circle(p, Length(p1-p));
}


//三角形内切圆
Circle InscribedCircle(Point p1, Point p2, Point p3) /// 已验证
{
    double a = Length(p2-p3);
    double b = Length(p3-p1);
    double c = Length(p1-p2);
    Point p = (p1*a+p2*b+p3*c)/(a+b+c);
    return Circle(p, DistanceToLine(p, p1, p2));
}


//半径为r 与a b两直线相切的圆心
vector<Point> CircleTangentToLinesGivenRadius(Line a, Line b, double r)
{
    vector<Point> ans;
    Line L1 = a.move(-r), L2 = a.move(r);
    Line L3 = b.move(-r), L4 = b.move(r);
    ans.push_back(GetLineIntersection(L1, L3));
    ans.push_back(GetLineIntersection(L1, L4));
    ans.push_back(GetLineIntersection(L2, L3));
    ans.push_back(GetLineIntersection(L2, L4));
    return ans;
}


//与两圆相切 半径为r的所有圆心
vector<Point> CircleTangentToTwoDisjointCirclesWithRadius(Circle c1, Circle c2, double r)
{
    vector<Point> ans;
    Vector v = c2.c - c1.c;
    double dist = Length(v);
    int d = dcmp(dist - c1.r -c2.r - r*2);
    if(d > 0) return ans;
    getCircleCircleIntersection(Circle(c1.c, c1.r+r), Circle(c2.c, c2.r+r), ans);
    return ans;
}


//多边形与圆相交面积
Point GetIntersection(Line a, Line b) //线段交点
{
    Vector u = a.p-b.p;
    double t = Cross(b.v, u) / Cross(a.v, b.v);
    return a.p + a.v*t;
}


inline bool InCircle(Point x, Circle c)
{
    return dcmp(c.r - Length(c.c - x)) >= 0;
}

inline bool OnCircle(Point x, Circle c)
{
    return dcmp(c.r - Length(c.c - x)) == 0;
}

//线段与圆的交点
int getSegCircleIntersection(Line L, Circle C, Point* sol)
{
    Vector nor = Normal(L.v);
    Line pl = Line(C.c, nor);
    Point ip = GetIntersection(pl, L);
    double dis = Length(ip - C.c);
    if (dcmp(dis - C.r) > 0) return 0;
    Point dxy = Unit(L.v) * msqrt(msqrt(C.r) - msqrt(dis));
    int ret = 0;
    sol[ret] = ip + dxy;
    if (OnSegment(sol[ret], L.p, L.point(1))) ret++;
    sol[ret] = ip - dxy;
    if (OnSegment(sol[ret], L.p, L.point(1))) ret++;
    return ret;
}

//线段切割圆
double SegCircleArea(Circle C, Point a, Point b)
{
    double a1 = angle(a - C.c);
    double a2 = angle(b - C.c);
    double da = fabs(a1 - a2);
    if (da > PI) da = PI * 2.0 - da;
    return dcmp(Cross(b - C.c, a - C.c)) * da * msqrt(C.r) / 2.0;
}

//多边形与圆相交面积
double PolyCiclrArea(Circle C, Point *p, int n)
{
    double ret = 0.0;
    Point sol[2];
    p[n] = p[0];
    //REP(i, n)
    for(int i=1;i<=n;i++)
    {
        //double t1, t2;
        int cnt = getSegCircleIntersection(Line(p[i], p[i+1]-p[i]), C, sol);
        if (cnt == 0)
        {
            if (!InCircle(p[i], C) || !InCircle(p[i+1], C)) ret += SegCircleArea(C, p[i], p[i+1]);
            else ret += Cross(p[i+1] - C.c, p[i] - C.c) / 2.0;
        }
        if (cnt == 1)
        {
            if (InCircle(p[i], C) && !InCircle(p[i+1], C)) ret += Cross(sol[0] - C.c, p[i] - C.c) / 2.0, ret += SegCircleArea(C, sol[0], p[i+1]);
            else ret += SegCircleArea(C, p[i], sol[0]), ret += Cross(p[i+1] - C.c, sol[0] - C.c) / 2.0;
        }
        if (cnt == 2)
        {
            if ((p[i] < p[i + 1]) ^ (sol[0] < sol[1])) swap(sol[0], sol[1]);
            ret += SegCircleArea(C, p[i], sol[0]);
            ret += Cross(sol[1] - C.c, sol[0] - C.c) / 2.0;
            ret += SegCircleArea(C, sol[1], p[i+1]);
        }
    }
    return fabs(ret);
}

double area(vector<Point>p) //计算凸包的面积
{
    double ans = 0;
    int sz = p.size();
    for (int i = 1; i < sz - 1; i++)
        ans += Cross(p[i] - p[0], p[i + 1] - p[0]);
    return ans / 2.0;
}

double seg(Point o, Point a, Point b)
{
    if (dcmp(b.x - a.x) == 0) return (o.y - a.y) / (b.y - a.y);
    return (o.x - a.x) / (b.x - a.x);
}

vector<Point> pp[110];
pair<double, int> s[2200];
double polyunion(vector<Point>*p, int n)//求n个多凸包的面积交
{
    double ret = 0;
    for (int i = 0; i < n; i++)
    {
        int sz = p[i].size();
        for (int j = 0; j < sz; j++)
        {
            int m = 0;
            s[m++] = mp(0, 0);
            s[m++] = mp(1, 0);
            Point a = p[i][j], b = p[i][(j + 1) % sz];
            for (int k = 0; k < n; k++)
            {
                if (i != k)
                {
                    int siz = p[k].size();
                    for (int ii = 0; ii < siz; ii++)
                    {
                        Point c = p[k][ii], d = p[k][(ii + 1) % siz];
                        int c1 = dcmp(Cross(b - a, c - a));
                        int c2 = dcmp(Cross(b - a, d - a));
                        if (c1 == 0 && c2 == 0)
                        {
                            if (dcmp(Dot(b - a, d - c)) > 0 && i > k)
                            {
                                s[m++] = mp(seg(c, a, b), 1);
                                s[m++] = mp(seg(d, a, b), -1);
                            }
                        }
                        else
                        {
                            double s1 = Cross(d - c, a - c);
                            double s2 = Cross(d - c, b - c);
                            if (c1 >= 0 && c2 < 0) s[m++] = mp(s1 / (s1 - s2), 1);
                            else if (c1 < 0 && c2 >= 0) s[m++] = mp(s1 / (s1 - s2), -1);
                        }
                    }
                }
            }
            sort(s, s + m);
            double pre = min(max(s[0].first, 0.0), 1.0), now;
            double sum = 0;
            int cov = s[0].second;
            for (int j = 1; j < m; j++)
            {
                now = min(max(s[j].first, 0.0), 1.0);
                if (!cov) sum += now - pre;
                cov += s[j].second;
                pre = now;
            }
            ret += Cross(a, b)*sum;
        }
    }
    return ret / 2;
}

int main(){
    return 0;
}
