#include <iostream>
using namespace std;
const int N = 2e6;
const int N_2 = 1e6;
int h, n;         // n <= N_2 == array size, h is tree hight
int t[N], d[N_2]; // d is delayed to be propagated to it's children
void build()
{
    for (int i = n - 1; i > 0; i--)
    {
        t[i] = t[i << 1] + t[i << 1 | 1];
    }
}
void apply(int pos, int value, int k)
{
    t[pos] += value * k;
    if (pos < n)
    {
        d[pos] += value;
    }
}
void build(int pos)
{
    pos >>= 1;
    int k = 2;
    while (pos > 0)
    {
        t[pos] = t[pos << 1] + t[pos << 1 | 1] + d[pos] * k;
        k <<= 1;
        pos >>= 1;
    }
}
void push(int pos)
{
    for (int s = h, k = (1 << (h - 1)); s > 0; s--, k >>= 1)
    {
        int i = pos >> s;
        if (d[i] != 0)
        {
            apply(i << 1, d[i], k);
            apply(i << 1 | 1, d[i], k);
            d[i] = 0;
        }
    }
}
void update(int l, int r, int value) // increments range [l..r) by value
{
    l += n;
    r += n;
    int l0 = l;
    int r0 = r;
    int k = 1;
    for (; l < r; l >>= 1, r >>= 1, k <<= 1)
    {
        if (l & 1)
        {
            apply(l++, value, k);
        }
        if (r & 1)
        {
            apply(--r, value, k);
        }
    }
    build(l0);
    build(r0 - 1);
}
int query(int l, int r)
{
    int res = 0;
    l += n;
    r += n;
    push(l);
    push(r - 1);
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
    freopen("range_increment_update_range_sum_input.txt", "r", stdin);
    freopen("range_increment_update_range_sum_output.txt", "w", stdout);
#endif
    cin >> n;
    h = 8 * sizeof(int) - __builtin_clz(n);
    for (int i = 0; i < n; i++)
    {
        cin >> t[i + n];
    }
    build();
    // [1,2,3,1,2,3,12,1]
    cout << query(0, n) << endl;
    update(4, n, 5);
    //[1,2,3,1,7,8,17,6]
    cout << query(2, 5) << endl;

    update(1, 6, 10);
    //[1,12,13,11,17,18,17,6]

    cout << query(0, 4) << endl;
    cout << query(4, n) << endl;
    return 0;
}