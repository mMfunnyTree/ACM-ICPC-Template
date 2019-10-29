#include <bits/stdc++.h>
using namespace std;
const int maxnode = 20000 * 1000 + 10;
const int sigma_size = 2;
int ans;
struct Trie
{
    int ch[maxnode][sigma_size];
    int val[maxnode];
    int sz; // 结点总数
    void clear()
    {
        sz = 1;    // 初始时只有一个根结点
        memset(ch[0], 0, sizeof(ch[0]));
    }
    int idx(char c)
    {
        return c - '0';    // 字符c的编号
    }

    // 插入字符串s，附加信息为v。注意v必须非0，因为0代表“本结点不是单词结点”
    void insert(string s, int v)
    {
        int u = 0, n = s.size();
        for(int i = 0; i < n; i++)
        {
            int c = idx(s[i]);
            if(!ch[u][c])   // 结点不存在
            {
                memset(ch[sz], 0, sizeof(ch[sz]));
                val[sz] = 0;  // 中间结点的附加信息为0
                ch[u][c] = sz++; // 新建结点
            }
            else ans=max(ans,i);
            u = ch[u][c]; // 往下走
        }
        val[u] = v; // 字符串的最后一个字符的附加信息为v
    }
};

Trie trie;

string s;

string get(string ss)
{
    string ret;
    for(int i=0; i<1000; i++)
        ret+=ss[i%ss.size()];
    return ret;
}

int main()
{
    int n;
    scanf("%d",&n);
    trie.clear();
    while(n--)
    {
        cin>>s;
        s=get(s);
        trie.insert(s,1);
    }
    cout<<ans+1;
    return 0;
}
