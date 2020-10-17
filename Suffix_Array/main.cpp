#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Node
{
    int rk0, rk1, idx;
    Node()
    {
        rk0 = rk1 = idx = -1;
    }
    Node(int rk0, int rk1, int idx) : rk0(rk0), rk1(rk1), idx(idx)
    {
    }
    inline pair<int, int> toPair() const
    {
        return {rk0, rk1};
    }
};
inline bool operator<(const Node &a, const Node &b)
{
    return a.toPair() < b.toPair();
}
vector<int> sa(const string &s)
{
    int n = (int)s.size();
    vector<Node> a(n);
    for (int i = 0; i < n; i++)
    {
        a[i].rk0 = s[i] - 'a' + 1;
        a[i].rk1 = (i + 1 < n) ? s[i + 1] - 'a' + 1 : 0;
        a[i].idx = i;
    }
    sort(a.begin(), a.end());
    vector<int> ind(n);
    for (int k = 4; k < 2 * n; k *= 2)
    {
        int ranknow = 0;
        int prev_rank0;
        prev_rank0 = a[0].rk0;
        a[0].rk0 = ranknow;
        ind[a[0].idx] = 0;
        for (int i = 1; i < n; i++)
        {
            if (prev_rank0 == a[i].rk0 && a[i - 1].rk1 == a[i].rk1)
            {
                a[i].rk0 = ranknow;
            }
            else
            {
                prev_rank0 = a[i].rk0;
                a[i].rk0 = ++ranknow;
            }
            ind[a[i].idx] = i;
        }
        for (int i = 0; i < n; i++)
        {
            int nxt = a[i].idx + k / 2;
            a[i].rk1 = (nxt < n) ? a[ind[nxt]].rk0 : 0;
        }
        sort(a.begin(), a.end());
    }
    vector<int> sa_(n);
    for (int i = 0; i < n; i++)
    {
        sa_[i] = a[i].idx;
    }
    return sa_;
}
vector<int> lcp(const string &s, const vector<int> &sa)
{
    int k = 0;
    int n = (int)s.size();
    vector<int> lcp(n, 0);
    vector<int> rank(n, 0);
    for (int i = 0; i < n; i++)
    {
        rank[sa[i]] = i;
    }
    for (int i = 0; i < n; i++)
    {
        if (rank[i] == n - 1)
        {
            k = 0;
            continue;
        }
        int j = sa[rank[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k])
            k++;
        lcp[rank[i]] = k;
        if (k)
            k--;
    }
    return lcp;
}
int main()
{
    return 0;
}