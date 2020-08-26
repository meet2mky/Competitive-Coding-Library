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
#include <cmath>
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

/*
Given n strings from 1 to n
for each l,r,str. find the count i, i <=r && i >= l s.t. strings[i] == str
*/
const int MAXN = 100009;
string here;
int n, q, cl, cr, l, r;
int block_size;
int hasof[MAXN];
vector<tuple<int, int, int, int>> query;
vector<int> answer;
map<int, int> mp_;
bool comp_(const tuple<int, int, int, int> &a, const tuple<int, int, int, int> &b)
{
    if (get<0>(a) / block_size == get<0>(b) / block_size)
    {
        return (get<1>(a) < get<1>(b));
    }
    return (get<0>(a) / block_size < get<0>(b) / block_size);
}
int fun(const string &str)
{
    int res = 0;
    rep(i, 0, SZ(str))
    {
        res = res * 31 + str[i] - 'a' + 1;
    }
    return res;
}
void add(int x)
{
    mp_[hasof[x]]++;
}
void remove(int x)
{
    mp_[hasof[x]]--;
}
void solve()
{
    cin >> n;
    block_size = static_cast<int>(sqrt(n)) + 1;
    rep(i, 0, n)
    {
        cin >> here;
        hasof[i] = fun(here);
    }
    cin >> q;
    query.reserve(q);
    answer.reserve(q);

    rep(i, 0, q)
    {
        cin >> l >> r >> here;
        l--;
        r--;
        cl = fun(here);
        query[i] = std::tie(l, r, cl, i);
    }
    cl = 0, cr = -1;
    int idx, value;
    sort(all(query), comp_);
    rep(i, 0, q)
    {
        std::tie(l, r, value, idx) = query[i];

        while (cr < r)
        {
            add(++cr);
        }
        while (cr > r)
        {
            remove(cr--);
        }
        while (cl < l)
        {
            remove(cl++);
        }
        while (cl > l)
        {
            add(--cl);
        }
        answer[idx] = mp_[value];
    }
    rep(i, 0, q)
    {
        cout << answer[i] << '\n';
    }
}
signed main()
{
    sync;
#ifndef ONLINE_JUDGE
    freopen("count_of_string_in_range_input.txt", "r", stdin);
    freopen("count_of_string_in_range_output.txt", "w", stdout);
#endif
    solve();
    return 0;
}