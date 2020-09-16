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
#include <cmath>
#include <cassert>
#include <cctype>
#include <iomanip>
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
#define vb vector<bool>
#define vi vector<int>
#define vvi vector<vi>
#define pii pair<int, int>
#define sp(x) setprecision(x)
#define endl '\n'
#define ll long long
#define ld long double
#define SZ(z) (int)(z).size()
#define inf 0x3f3f3f3f
#define linf 0x3f3f3f3f3f3f3f3f
#define eps 0.0000001 // eps = 1e-7
#define PI 3.141592653589793238

//#define int long long
const int MOD = 1000000007;

//variadic functions
template <typename T>
T sum() { return 0; }
template <typename T, typename... Args>
T sum(T a, Args... args) { return a + sum(args...); }

//Debugger  -------------------------------------------->
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
//Debugger  <--------------------------------------------
/*****************************************************************
Read the problem carefully!!
Take inputs carefully
Care for array index out of bound errors
Check for overflow
Divide the problem in several parts if possible
Keep Calm and believe on yourself.
Do not panic & work hard you will get it right one day
******************************************************************/

struct Node
{
    // something a node represents
    // when it is condensed with other nodes
    int cnt; // let's say count of nodes in this case
    Node(int cnt = 0) : cnt(cnt)
    {
    }
};
Node combine(const Node &a, const Node &b)
{
    Node t;
    t.cnt = a.cnt + b.cnt;
    return t;
}
const int N = 1e5; // g size
vi g[N], gc[N];    // undirected graph & condensed tree
vi tin(N), p(N), low(N), sz(N);
vb vis(N);
int n, m, timer, u, v, a, b, c, d, e;
vector<Node> nd(N);
vector<pair<int, int>> tree_edges;
int f(int now)
{
    if (now == p[now])
    {
        return now;
    }
    return p[now] = f(p[now]);
}
void uni(int a, int b)
{
    a = f(a);
    b = f(b);
    if (a != b)
    {
        if (sz[a] < sz[b])
        {
            swap(a, b);
        }
        p[b] = a;
        sz[a] += sz[b];
        nd[a] = combine(nd[a], nd[b]);
    }
}
void init()
{
    for (int i = 0; i < n; i++)
    {
        p[i] = i;
        sz[i] = 1;
        vis[i] = false;
        g[i].clear();
        gc[i].clear();
        nd[i].cnt = 1;
        timer = 0;
        tree_edges.clear();
    }
}
void input()
{
    cin >> n >> m;
    init();
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;
        g[a - 1].push_back(b - 1);
        g[b - 1].push_back(a - 1);
    }
}
void dfs(int src, int p)
{
    vis[src] = true;
    tin[src] = low[src] = timer++;
    for (auto to : g[src])
    {
        if (to == p)
            continue;
        if (vis[to] == true)
        {
            low[src] = min(low[src], tin[to]);
            uni(to, src); // condense
        }
        else
        {
            dfs(to, src);
            low[src] = min(low[src], low[to]);
            if (low[to] > tin[src])
            {
                // to ---- src
                tree_edges.push_back({to, src}); // store
            }
            else
            {
                uni(to, src); // condense
            }
        }
    }
}
void bcc_edge_tree() // or forest if g isn't connected
{
    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
        {
            dfs(i, -1);
        }
    }
    for (auto x : tree_edges)
    {
        gc[f(x.first)].push_back(f(x.second));
        gc[f(x.second)].push_back(f(x.first));
    }
}
Node dfs1(int src, int p)
{
    vis[src] = true;
    for (auto to : gc[src])
    {
        if (to == p)
            continue;
        if (!vis[to])
        {
            Node here = dfs1(to, src);
            nd[src] = combine(nd[src], here);
        }
    }
    return nd[src];
}
void solve()
{
    input();
    bcc_edge_tree();
    for (int i = 0; i < n; i++)
        vis[i] = false;
    for (int i = 0; i < n; i++)
    {
        if (!vis[f(i)])
        {
            Node compnd = dfs1(f(i), -1);
            // do stuff with this tree
        }
    }
}
signed main()
{
    sync;
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}