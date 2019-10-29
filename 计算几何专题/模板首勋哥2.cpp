//平面几何模板整理
//在原来的内容上进行了一些修改 
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <string>
#include <cmath>
#include <iostream>
using namespace std;
const int maxn=10050;
const double eps=1e-8;//精度范围

//*********平面点，线，简单图形的表示********* 
struct point{
	//平面点的表示，坐标值为实数，适用于对时间要求不太高的情况
	//优点是可以进行精确计算，在大部分情况下都是使用这种表示法表示平面上的点 
	//缺点是运算起来可能会比较慢 
	double x,y;
	point(double x0=0,double y0=0){
		x=x0;y=y0;
	}
};

struct point2{
	int x,y;
	//如果仅仅是进行定性判断或者是不涉及实数计算的算法（如求凸包），可以使用以下平面点的表示法
	//注意如果涉及到计算的话，最好还是使用坐标值为实数的点表示法 
	point2(int x0=0,int y0=0){
		x=x0;y=y0;
	}
};
struct line{
	//待定系数法表示直线，形如ax+by+c=0可以表示平面上的一条直线 
	//该表示法可以方便利用解析几何的知识解决问题 
	//用这种表示法需要记住一些公式，例如两直线交点坐标公式，下面有写 
	double a,b,c;
	line(double a0=0,double b0=0,double c0=0){
		a=a0;b=b0;c=c0;
	} 
}; 

struct line2{
	//两点式表示一条直线或线段 
	//实际上很多时候不用刻意使用结构体，使用两个point数组亦可表示
	point p1,p2;
	line2(point _p1,point _p2){
		p1=_p1;p2=_p2;
	}
};

struct circle{
	//点径式表示一个圆
	//其实有时也不用刻意使用结构体表示圆 
	point o;
	double r;
};

typedef point vctor;//将point另命名为向量，这样一个点坐标就可表示为一条由坐标原点指向该点坐标的向量 

//任意多边形可以使用一组按照顺时针或逆时针给出的点序列表示

//*********点，向量的运算符的重载*********
vctor operator + (vctor a,vctor b){
	//平面两向量相加 
	return vctor(a.x+b.x,a.y+b.y);
} 
vctor operator - (vctor a,vctor b){
	//平面两向量相减 
	return vctor(a.x-b.x,a.y-b.y);
}
vctor operator * (vctor a,double k){
	//向量的数乘，乘以一个实数 
	return vctor(a.x*k,a.y*k); 
}
vctor operator / (vctor a,double k){
	//向量的数乘，除以一个实数 
	return vctor(a.x/k,a.y/k);
}
bool operator == (point a,point b){
	//判断两点是否为同一点 
	return a.x==b.x&&a.y==b.y;
}

point p[maxn],res[maxn],d[maxn],tmp[maxn],q;
int cnt,n,m,r; 

//*********点，线的基本操作********* 
int sig(double x){
	//返回实数x的符号，如果x非常接近精确度的范围，那么x=0
	//否则x>0即为正数，返回1，x<0返回-1 
	return fabs(x)<eps?0:(x>0)?1:-1;
}
 
double dot(point a,point b,point c){
	//求向量ab与向量ac的点积
	//就是高中数学的点积，所有高中学过的点积知识均适用 
	//以下情况可能会用到点积的运算
	//1.判断夹角是锐角，直角还是钝角，判垂直 
	//2.求两向量的夹角
	//3.求点到直线的最短距离
	//具体应用下面会写到 
	return (b.x-a.x)*(c.x-a.x)+(b.y-a.y)*(c.y-a.y); 
}

double cross(point a,point b,point c){
	//求向量ab与向量ac的叉积
	//平面向量ab与向量ac的叉积定义为(sig)*|ab|*|ac|*sin(theta)
	//sig表示符号，由ab与ac的位置关系决定
	//如果ab在ac的顺时针方向，那么sig=1，ab在ac逆时针方向时sig=-1，ab与ac共线时sig=0，整个叉积为0 
	//sin(theta)表示两向量夹角的正弦 
	//叉积的几何意义为以两向量为邻边组成的平行四边形的有向面积
	//注意是有向面积，意味着可能会出现值为负的面积，除了定性判断或者计算多边形的面积，一般加上绝对值 
	//以下情况可能会用到叉积的运算
	//1.判断一个点在一个向量的顺时针方向还是逆时针方向 
	//2.判断折线的折向
	//3.求三角形面积，求多边形面积，求点到直线的最短距离 
	//4.几乎所有几何算法，如极角排序，凸包，半平面交，旋转卡壳
	//具体应用下面会写到 
	return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x); 
}

point rotate(point p,double theta){
	//将一个点向逆时针旋转theta弧度，返回这个点 
	double x=p.x*cos(theta)-p.y*sin(theta);
	double y=p.x*sin(theta)+p.y*cos(theta);
	return point(x,y);
}

point midpoint(point a,point b){
	//中点坐标公式，其实不需要写函数，因为已经重载了运算符 
	return (a+b)/2; 
} 

double dist(point a,point b){
	//求两点距离 
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

double dist2(point a,point b){
	//返回两点距离的平方，有时可以方便计算用 
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
} 

double dist_point_to_line(point p1,point p2,point p3){
	//求点p3到线段p1p2的最短距离，解释如下 
	if(dot(p1,p2,p3)<0)	return dist(p1,p3);
	//如果向量p1p3和向量p1p2形成钝角，那么最短距离当然是向量p1p3的模 
	if(dot(p2,p1,p3)<0)	return dist(p2,p3);
	//如果向量p2p3和向量p2p1形成钝角，那么最短距离当然是向量p2p3的模
	return fabs(cross(p1,p2,p3))/dist(p1,p2); 
	//其余情况，我们让p1,p2,p3组成一个三角形
	//那么三角形面积除以线段p1p2的长就是三角形的高，也就是p3到线段p1p2的（最短）距离了 
}

double area(point p[],int n){
	//求多边形的面积，转化为求三角形的面积求解
	//不断以原点(0,0)，p[i]和p[i+1](i=1,2,...,n)作三角形，求出这些三角形的（有向）面积加起来 
	//这样求出来的一系列三角形（有向）面积有正有负，但是没关系
	//把所有正的面积减去负的面积，剩下的就是多边形的面积了
	//多边形的顶点必须以顺时针或逆时针给出 
	p[n+1]=p[1];
	double s=0;
	for(int i=1;i<=n;i++)	s+=cross(point(0,0),p[i],p[i+1]);//s为面积 
	return fabs(s)/2.0;
} 

double angle(point a,point b,point c){
	//求向量ab和向量ac的夹角
	//定性判断只需判断点积符号即可 
	return acos(dot(a,b,c)/(dist(a,b)*(dist(a,c))));
}

bool iscross(point p1,point p2,point p3,point p4){
	if(min(p1.x,p2.x)>max(p3.x,p4.x)||
        min(p3.x,p4.x)>max(p1.x,p2.x)||
        min(p1.y,p2.y)>max(p3.y,p4.y)||
        min(p3.y,p4.y)>max(p1.y,p2.y))return 0;
	double r1=cross(p1,p2,p3);
	double r2=cross(p1,p2,p4);
	double r3=cross(p3,p4,p1);
	double r4=cross(p3,p4,p2);
	if(sig(r1*r2)<=0&&sig(r3*r4)<=0)return 1;
	return 0;
}

point cross_point(line l1,line l2){
	//求两直线l1,l2交点坐标，前提条件为两直线相交，使用解方程法 
	//x=(b1*c2-b2*c1)/(a1*b2-a2*b1) 
	//y=(c1*a2-c2*a1)/(a1*b2-a2*b1)
	double a1=l1.a,b1=l1.b,c1=l1.c;
	double a2=l2.a,b2=l2.b,c2=l2.c;
	double x=(b1*c2-b2*c1)/(a1*b2-a2*b1);
	double y=(c1*a2-c2*a1)/(a1*b2-a2*b1);
	return point(x,y);
}

point cross_point2(point p1,point p2,point p3,point p4){
	//求线段p1p2和p3p4的交点坐标，前提条件为两线段相交
	//方法同求直线交点坐标，只是直线方程的系数需要自己去求 
	double a1=p1.y-p2.y;
	double b1=p2.x-p1.x;
	double c1=p1.x*p2.y-p2.x*p1.y;
	double a2=p3.y-p4.y;
	double b2=p4.x-p3.x;
	double c2=p3.x*p4.y-p4.x*p3.y;
	double x=(b1*c2-b2*c1)/(a1*b2-a2*b1);
	double y=(c1*a2-c2*a1)/(a1*b2-a2*b1);
	return point(x,y);
}

//*********极角排序*********
//对于平面上的所有点，我们取一个点作为原点，以平行于x轴坐标轴且向右的射线为极轴
//在这个极坐标平面上，任一点的角度定义为极轴向逆时针旋转的角度 
//将所有点的坐标按照角度从小到大排序，就将所有点进行了极角排序
//也可以使用atan2(y,x)函数，该函数返回一个弧度，取值范围为(-pi,pi]
//它返回的是向量(x,y)与坐标轴形成的夹角。 
int cmp(point a,point b){
	//极角排序 
	return atan2(a.y,a.x)<atan2(b.y,b.x);
} 

//*********凸包算法*********
//给定平面上的一些点，要求一个多边形，使得平面上的所有点或者在这个多边形上，或者在多边形内
//简单地说就是求一个多边形把所有平面上所有点围起来
//有四种算法：卷包裹法，Greham扫描法，Jarvis步进法，完美凸包算法
//这里仅给出时间复杂度较好的Greham扫描法，算法复杂度为O(n*logn) 
int cmp2(point a,point b){
	//求凸包前必须先将所有点进行坐标排序，
	//排序之后，所有点按照纵坐标从下到上的顺序排序，如果纵坐标相同则按横坐标从左到右的顺序排
	return a.y<b.y||a.y==b.y&&a.x<b.x; 
} 
int convex(int n,point p[]){
	 //该函数传入平面上点的个数和所有点的坐标（已排序）
	 //返回凸包上点的个数，同时求出的凸包按逆时针顺序存在数组res[]内
	 int now=1;
	 for(int i=1;i<=n;i++){
	 	while(now>2&&sig(cross(res[now-2],p[i],res[now-1]))>0)	now--;
		//res[]数组相当于一个栈
		//首先凸包是一个多边形，至少要有三个点，故now>2 
		//当res[now-2],p[i],res[now-1]三点按顺序组成的折线的折向向右时，说明res[now-1]不满足条件
		//因为凸包的点要按逆时针给出，而此时三点是顺时针顺序 
		//故将res[now-1]弹出，继续循环直到res[now-2],p[i],res[now-1]组成的折线折向向左
		//此时三点是逆时针顺序，故res[]中压入p[i] 
	 	res[now++]=p[i];
	 	//循环到满足条件的点时，压入栈中 
	 } 
	 //此时已求出半个凸包（从最左下方的点到最右上方的点的一个逆时针凸包）
	 //但凸包应该是一个闭合多边形，故还要从右上方到左下方来一遍 
	 int k=now;
	 for(int i=n-1;i>=1;i--){
	 	while(now>k&&sig(cross(res[now-2],p[i],res[now-1]))>0)	now--;
	 	res[now++]=p[i];
	 }
	 //此时求出的凸包会多出一个左下角的点，删掉这个点 
	 if(n>1)	now--;
	 return now-1;
}

//*********半平面交*********
//如果我们规定直线的一侧（例如右侧）为有效区域（半平面）
//那么平面上的多条直线组合起来就可以划出一块区域 
//这块区域称为平面交，求平面交的算法叫做半平面交算法
//直白的说，半平面交就是将一块区域不断地用一条直线进行切割然后扔掉不要的部分 
//当用直线不断切割平面时，被切割的区域可能会不断的产生新的点，也可能会有原来在平面交上的点被删掉 
//因此这个算法就是对一个点序列进行不断的删除和添加操作
//需要用两个数组d[]和tmp[]，先将d[]求平面交的结果放到tmp[]里，再将tmp[]复制给d[] 
//由于篇幅所限，可能有些难理解，如果不好理解就不必深入，直接CV代码也可以 
void init(int n){
	//初始化平面，向d[]中放入按顺时针给出的点序列
	//点序列可以是给定的多边形，如该函数就传入了多边形的顶点数 
	//也可以是无限大平面（此时d[]中放入的是四个无穷大的点(inf,inf),(inf,-inf),(-inf,-inf),(-inf,inf)） 
	for(int i=1;i<=n;i++)
		d[i]=p[i];
	d[n+1]=d[1];d[0]=d[n];
	//由于切割时可能涉及到当前点的前一个点或后一个点的操作
	//故在d[0]和d[n+1]补充上d[1]的前一个点和d[n]的后一个点 
	m=n;//m为全局变量，表示当前平面交区域的顶点数 
} 
void cut(point a,point b){
	//用向量ab切割平面以得到一个新的半平面交，规定有效区域为ab右边
	//由于这种规定，最后得到的平面交总是顺时针的顶点序列 
	//m为平面交的顶点的数量 
	//tmp[]为临时数组，存放平面交的，最后再复制给d[] 
	int cnt=1;//cnt为新的半平面交的顶点个数，最后再复制给m 
	for(int i=1;i<=m;i++){
		//判断所有点是否在新的半平面交内，然后对这些点进行一些操作 
		double r=cross(a,b,d[i]);
		if(sig(r)<=0)	tmp[cnt++]=d[i];
		//如果r<=0说明该点在平面交内，直接放进tmp[]即可
		else{
			double r1=cross(a,b,d[i-1]);
			if(sig(r1)<0)	tmp[cnt++]=cross_point2(a,b,d[i],d[i-1]);
			//由于r>=0，故d[i]在新的平面交外，而这个点的前一个点有可能在新的平面交内
			//这里我们需要判断一下这个点的前一个点是否在平面交内
			//如果是，把这个点和这个点的前一个点作为一条线段
			//然后求这条线段和ab的交点，这个交点一定在新的半平面交上，放入tmp[] 
			double r2=cross(a,b,d[i+1]);
			if(sig(r2)<0)	tmp[cnt++]=cross_point2(a,b,d[i],d[i+1]);
			//同样d[i]的后一个点有可能在新的半平面交内，像上述一样操作 
		} 
	} 
	//接下来就是对cnt和tmp[]的复制操作 
	m=cnt-1;
	for(int i=1;i<=m;i++)
		d[i]=tmp[i];
	d[m+1]=d[1];d[0]=d[m];
}
int getcut(int n){
	//p[]中存入了用于求交的直线，用相邻的两个点坐标表示一条直线 
	init(n);//先初始化，将所有点放入d[]中
	for(int i=1;i<=n;i+=2){
		cut(p[i],p[i+1]);//用给出的直线不断的切割 
	}
	return m;//返回半平面交的顶点数 
}

//*********旋转卡壳*********
//求凸多边形上距离最远的一对顶点，复杂度为O(n)，一般结合凸包算法计算
//首先选取凸多边形的一条边，一般是p1p2 
//然后从p3开始，查找p3,p4,...,pn
//以p1p2为底的三角形p1p2pi(i=3,4,...,n)的面积是一个单峰函数，也就是说一定有一个最大值
//假设查找到pk时三角形面积最大 
//那么三角形p1p2pk的两条边p1pk和p2pk中，(p1,pk)和(p2,pk)中就可能有一对点是最远的一对顶点
//用一个ans记录一下两对点距离较大的那一对点的距离 
//然后再以p2p3为底，从原来的pk接着往下找
//由于面积是单峰函数，故一定又可以找到可能为最远顶点对的两对点，用这两对点中距离较大的维护ans
//然后再以p3p4为底……一直到以pnp1为底时结束，查找了一圈
//得到的ans就是凸多边形距离最远的一对顶点的距离
//由于篇幅所限，不好理解的话，直接照着CV 
//如果多边形顶点个数比较少，暴力O(n^2)也可以 
double caliper(int n){
	//p[]中逆时针给出了凸多边形的顶点，n为凸多边形的顶点数
	//返回距离最远的一对顶点的距离 
	int now=2;
	//now表示当前查找的点的下标 
	double ans=0;
	for(int i=1;i<=n;i++){
		while(sig(cross(p[i],p[i+1],p[now+1])-cross(p[i],p[i+1],p[now]))>0)	now=now%n+1;
		//如果当前面积大于上一个面积，说明单峰函数还没达到极值，我们让now=now+1
		//直到当前面积小于等于上一个面积为止，说明三角形的面积已达最大 
		//注意取余，查找到最后一个点的下一个时，即回到第一个点 
		double d1=dist(p[i],p[now]);
		double d2=dist(p[i+1],p[now]);
		ans=max(ans,max(d1,d2));//ans维护最大距离 
	}
	return ans;
}

//*********pick定理*********
//皮克定理是一个计算点阵中顶点在格点上的多边形面积公式，该公式可以表示为2S=2a+b-2
//a表示多边形内部的点数，b表示多边形边上的点数，S表示多边形的面积
//计算多边形内的点的个数，只需将公式变形为a=(2S-b+2)/2 
//设两点p1(x1,y1),p2(x2,y2)
//则线段p1p2的点数=gcd(abs(x1-x2),abs(y1-y2))（注意只计算了线段两个端点中的一个）
//以下是一个计算格点三角形内部点的算法 
int gcd(int x,int y){
	//求最大公约数 
	return y==0?x:gcd(y,x%y);
}
//这里需要使用坐标为整数的向量的叉积
int cross(point2 a,point2 b,point2 c){
	return (b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
} 
int pick(point2 p1,point2 p2,point2 p3){
	//返回格点三角形内部的点数 
	//由于是格点三角形，故坐标均为整数 
	int s=abs(cross(p1,p2,p3));//求出三角形面积的2倍 
	int b1=gcd(abs(p1.x-p2.x),abs(p1.y-p2.y));
	int b2=gcd(abs(p2.x-p3.x),abs(p2.y-p3.y));
	int b3=gcd(abs(p3.x-p1.x),abs(p3.y-p1.y));
	//求出三边上的格点数 
	int b=b1+b2+b3; 
	return (s-b+2)/2;
} 

//*********最小圆覆盖*********
//最小圆覆盖指给定平面上的一些点，求作一个圆使得平面上的所有点均在这个圆内，并且圆的面积最小 
//可以发现，这个最小圆至少应该过平面上的两个点
//我我们先用p[1]和p[i]做圆，再从2到i-1判断是否有点不在这个圆上
//如果都在，则说明已经找到覆盖1到i-1的圆
//如果没有都在，假设我们找到第一个不在这个圆上的点为p[j]
//于是我们用两个已知点p[j]与p[i]去找覆盖1到j-1的最小覆盖圆
//而对于两个已知点p[j]与p[i]求最小覆盖圆
//只要从1到j-1中，第k个点求过p[k],p[j],p[i]三个点的圆
//再判断k+1到j-1是否都在圆上，若都在，说明找到圆
//若有不在的，则再用新的点p[k]更新圆即可
//由于篇幅所限，不必深入，直接CV即可 
point func(point p1,point p2,point p3){
	//这个函数返回的是三角形的外心，也就是对三角形其中两条边作中垂线得到的交点 
	line l1=(p1.x-p2.x,p1.y-p2.y,(dist2(point(0,0),p1)-dist2(point(0,0),p2))/2);
	line l2=(p2.x-p3.x,p2.y-p3.y,(dist2(point(0,0),p2)-dist2(point(0,0),p3))/2);
	return cross_point(l1,l2);
}

void circlecover(){
	q=p[1];r=0;
	//初始化圆心为p[1] 
	for(int i=2;i<=n;i++){
		//先确定过p[i]的圆 
		if(dist(q,p[i])-r>eps){
			q=p[i];r=0;
			for(int j=1;j<=i-1;j++){
				//寻找不在当前圆覆盖上的点p[j]，确定过两点的圆 
				if(dist(q,p[j])-r>eps){
					q=(p[i]+p[j])/2;r=dist(q,p[j]);
					for(int k=1;k<=j-1;k++){
						//寻找不在当前圆覆盖上的点p[k]，确定过两三点的圆
						if(dist(q,p[k])-r>eps){
							q=func(p[i],p[j],p[k]);//求外心，外心即为三角形外接圆的圆心 
							r=dist(q,p[k]);
						}
					}
				}
			}
		}
	}
}

int main(){
	
}
