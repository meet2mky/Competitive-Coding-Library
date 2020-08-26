// This is main Mo's algorithm
// to use hilbert curve order reverse sign of right border
// if index of blocknum is odd
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
const int N = 500009;
int n, m, q, block_size, l, r;
int arr[N];
int happy[N];
int answer[N];
int cnt[N];
pair<int, pair<int, int>> queries[N];
int pending;
int extra;
bool mo_order(const pair<int, pair<int, int>> &a, const pair<int, pair<int, int>> &b)
{
    if (a.first / block_size == b.first / block_size)
    {
        a.second.first < b.second.first;
    }
    return (a.first / block_size < b.first / block_size);
}
void add(int idx)
{
    if (cnt[arr[idx]] == 0)
    {
        pending++;
    }
    else if (cnt[arr[idx]] == happy[arr[idx]])
    {
        extra++;
    }
    cnt[arr[idx]]++;
    if (cnt[arr[idx]] == happy[arr[idx]])
    {
        pending--;
    }
}
void remove(int idx)
{
    if (cnt[arr[idx]] == happy[arr[idx]])
    {
        pending++;
    }
    cnt[arr[idx]]--;
    if (cnt[arr[idx]] == 0)
    {
        pending--;
    }
    if (cnt[arr[idx]] == happy[arr[idx]])
    {
        extra--;
    }
}
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cin >> n >> m;
    block_size = static_cast<int>(sqrt(n)) + 1;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    for (int i = 0; i < m; i++)
    {
        cin >> happy[i + 1];
    }
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        cin >> l >> r;
        l--;
        r--;
        int block_num = l / block_size;
        queries[i] = {l, {(block_num & 1) ? -r : r, i}};
    }
    sort(queries, queries + q, mo_order);
    int curr_left = 0;
    int curr_right = -1;
    for (int i = 0; i < q; i++)
    {
        l = queries[i].first;
        r = queries[i].second.first;
        if (r < 0)
            r = -r;
        int idx = queries[i].second.second;
        while (curr_left < l)
        {
            remove(curr_left++);
        }
        while (curr_right > r)
        {
            remove(curr_right--);
        }
        while (curr_left > l && extra == 0)
        {
            add(--curr_left);
        }
        while (curr_right < r && extra == 0)
        {
            add(++curr_right);
        }
        answer[idx] = (extra == 0 && pending == 0) ? 1 : 0;
        // cerr << "L: " << curr_left << " R: " << curr_right << " extra: " << extra << " pending: " << pending << endl;
    }
    for (int i = 0; i < q; i++)
    {
        cout << answer[i] << '\n';
    }
    return 0;
}