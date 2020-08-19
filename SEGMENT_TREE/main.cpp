#include <iostream>
using namespace std;

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
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> t[i + n];
    }
    build();
    return 0;
}