/*****************************************************************
IN GOD WE TRUST !!   

Author:- meet2mky
Date: -
Problem:-
Institue:- NITA
******************************************************************/
#include <iostream>
#include <bitset>
#include <map>
#include <unordered_map>
#include <vector>
#include <cstring>
#include <set>
#include <utility>
#include <algorithm>
#include <queue>
#include <cassert>
#include <cctype>
#include <stack>
#include <ctime>
#include <iterator>
#include <sstream>
using namespace std;
#define sync                      \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define repi(i, a, b) for (int i = (a); i > (b); i--)
#define all(x) (x).begin(), (x).end()
#define setall(x, val) fill(all(x), val)
#define pb push_back
#define mp make_pair
#define vb vector<bool>
#define vi vector<int>
#define vvi vector<vi>
#define pii pair<int, int>
#define endl '\n'
#define MOD 1000000007
#define ll long long
#define ld long double
#define SZ(z) (int)(z).size()
#define test(t) \
    int t;      \
    cin >> t;   \
    while (t--)

//#define int long long
#define inf 0x3f3f3f3f

//variadic functions
template <typename T>
T sum() { return 0; }
template <typename T, typename... Args>
T sum(T a, Args... args) { return a + sum(args...); }

#define error(args...)                           \
    {                                            \
        string _s = #args;                       \
        replace(_s.begin(), _s.end(), ',', ' '); \
        stringstream _ss(_s);                    \
        istream_iterator<string> _it(_ss);       \
        err(_it, args);                          \
    }

void err(istream_iterator<string> it)
{
}
template <typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args)
{
    cerr << *it << " = " << a << endl;
    err(++it, args...);
}

const int MAXN = 1e5; // max bit size
int BIT[MAXN + 1];
void init(int n, vi &a)
{
    rep(i, 1, n + 1)
    {
        int num = a[i - 1];
        int pos = i;
        while (pos <= n)
        {
            BIT[pos] += num;
            pos += (pos & (-pos));
        }
    }
    // O(n logn)
}
int query(int i, int n)
{ // [0....i]
    assert(i + 1 <= n);
    int res = 0;
    int pos = i + 1;
    while (pos > 0)
    {
        res += BIT[pos];
        pos -= (pos & (-pos));
    }
    return res;
}
void update(int i, int value, int n) // add value to a[i]
{
    int pos = i + 1;
    while (pos <= n)
    {
        BIT[pos] += value;
        pos += (pos & (-pos));
    }
}
int find_at(int i, int n)
{
    return query(i, n) - query(i - 1, n);
}
void update_2(int i, int value, int n) // set a[i] to value
{
    int a_i = find_at(i, n);
    int value_to_be_added = value - a_i;
    update(i, value_to_be_added, n);
}

int query(int l, int r, int n)
{ // [l.....r]
    return query(r, n) - query(l - 1, n);
}
void solve()
{
    int n;
    cin >> n;
    vi a(n);
    rep(i, 0, n)
    {
        cin >> a[i];
    }
    init(n, a);
    // do stuff

    cout << find_at(0, n) << endl;

    cout << find_at(1, n) << endl;

    cout << query(0, n - 1, n) << endl;

    update(5, 10, n);

    cout << query(0, n - 1, n) << endl;

    update_2(0, 0, n);

    cout << query(0, n - 1, n) << endl;
}
signed main()
{
    sync;
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    solve();
    return 0;
}