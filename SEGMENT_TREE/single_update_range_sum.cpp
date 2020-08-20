#include <iostream>
using namespace std;

// single updates & range sum query
const int N = 2e6;
int t[N];
int n;
void build()
{
    for (int i = n - 1; i > 0; i--)
    {
        t[i] = t[i << 1] + t[i << 1 | 1];
    }
}
void update(int pos, int value)
{
    pos += n;
    t[pos] = value;
    for (pos >>= 1; pos > 0; pos >>= 1)
    {
        t[pos] = t[pos << 1] + t[pos << 1 | 1];
    }
}
int query(int l, int r) // [l...r)
{
    int res = 0;
    l += n;
    r += n;
    for (; l < r; l >>= 1, r >>= 1)
    {
        if (l & 1)
        {
            res += t[l++];
        }
        if (r & 1)
        {
            res += t[--r];
        }
    }
    return res;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("single_update_range_sum_input.txt", "r", stdin);
    freopen("single_update_range_sum_output.txt", "w", stdout);
#endif

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> t[i + n];
    }
    build();
    cout << query(0, n) << endl;
    update(1, 10);
    cout << query(0, n) << endl;
    update(2, 10);
    cout << query(0, n) << endl;
    return 0;
}