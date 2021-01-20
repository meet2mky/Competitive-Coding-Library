#include <bits/stdc++.h>
using namespace std;

/*

*/

template <typename T>
class Segment // single update range query
{
private:
    int n;
    vector<T> tree;

public:
    void init(int n_)
    {
        n = n_;
        tree.assign(2 * n, T());
    }
    void init(const vector<T> &arr)
    {
        n = arr.size();
        tree.assign(2 * n, T());
        for (int i = 0; i < n; i++)
        {
            tree[i + n] = arr[i];
        }
    }
    void set(int idx, T val)
    {
        tree[idx + n] = val;
    }
    void build()
    {
        for (int i = n - 1; i >= 1; i--)
        {
            tree[i].combine(tree[i << 1], tree[i << 1 | 1]);
        }
    }
    void update(int idx, T val)
    {
        tree[idx += n] = val;
        for (idx >>= 1; idx > 0; idx >>= 1)
        {
            tree[idx].combine(tree[idx << 1], tree[idx << 1 | 1]);
        }
    }
    T query(int l, int r)
    {
        T resl = T();
        T resr = T();
        for (l += n, r += n; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
            {
                resl.combine(resl, tree[l++]);
            }
            if (r & 1)
            {
                resr.combine(tree[--r], resr);
            }
        }
        resl.combine(resl, resr);
        return resl;
    }
    T get(int idx)
    {
        return tree[idx + n];
    }
};
int main()
{
    return 0;
}