#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 2e3 + 5;
const int mod = 1e9 + 7;
struct Point {
    int x, y;
    Point(int _x = 0, int _y = 0): x(_x), y(_y) {}
    Point operator + (const Point &b) const {
        return Point(x + b.x, y + b.y);
    }
    Point operator - (const Point &b) const {
        return Point(x - b.x, y - b.y);
    }
    LL operator * (const Point &b) const {
        return ((LL)x * b.x + (LL)y * b.y);
    }
    LL operator ^ (const Point &b) const {
        return ((LL)x * b.y - (LL)y * b.x);
    }
    bool operator < (const Point &b) const {
        if((x - b.x) == 0) return y < b.y;
        else return x < b.x;
    }
} p[maxn], w;
struct node {
    int u, v;
    bool operator <(const node &b) const {
        return ((p[u] - p[v]) ^ (p[b.u] - p[b.v])) > 0;
    }
};
vector<node> f;
int id[maxn];
int main() {
    int n, i, j, l, r;
    LL A = 0, B = 1LL << 60;
    scanf("%d", &n);
    for(i = 0; i < n; i++) scanf("%d%d", &p[i].x, &p[i].y);
    for(i = 0; i < n; i++) id[i] = i;
    sort(p, p + n);
    for(i = 0; i < n; i++) {
        for(j = i + 1; j < n; j++) f.push_back(node{i, j});
    }
    sort(f.begin(), f.end());
    for(auto e : f) {
        i = e.u;
        j = e.v;
        if(id[i] > id[j]) swap(i, j);
        w = p[id[i]] - p[id[j]];
        A = max(A, abs((p[0] - p[id[j]]) ^ w) + abs((p[n - 1] - p[id[j]]) ^ w));
        if(id[i] && id[j] + 1 < n) B = min(B, abs((p[id[i] - 1] - p[id[j]]) ^ w) + abs((p[id[j] + 1] - p[id[j]]) ^ w));
        swap(id[i], id[j]);
        swap(p[id[i]], p[id[j]]);
    }
    cout << B << " " << A << endl;
    return 0;
}
