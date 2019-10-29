#include <bits/stdc++.h>
using namespace std;
const int maxnode = 20000 * 1000 + 10;
const int sigma_size = 2;
int ans;
struct Trie
{
    int ch[maxnode][sigma_size];
    int val[maxnode];
    int sz; // �������
    void clear()
    {
        sz = 1;    // ��ʼʱֻ��һ�������
        memset(ch[0], 0, sizeof(ch[0]));
    }
    int idx(char c)
    {
        return c - '0';    // �ַ�c�ı��
    }

    // �����ַ���s��������ϢΪv��ע��v�����0����Ϊ0��������㲻�ǵ��ʽ�㡱
    void insert(string s, int v)
    {
        int u = 0, n = s.size();
        for(int i = 0; i < n; i++)
        {
            int c = idx(s[i]);
            if(!ch[u][c])   // ��㲻����
            {
                memset(ch[sz], 0, sizeof(ch[sz]));
                val[sz] = 0;  // �м���ĸ�����ϢΪ0
                ch[u][c] = sz++; // �½����
            }
            else ans=max(ans,i);
            u = ch[u][c]; // ������
        }
        val[u] = v; // �ַ��������һ���ַ��ĸ�����ϢΪv
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
