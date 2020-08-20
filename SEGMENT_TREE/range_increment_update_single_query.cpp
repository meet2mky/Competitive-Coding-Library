#include <iostream>
using namespace std;

const int N = 2e6;
int n;
int t[N];
void update(int l, int r, int value) // add value to all element in [l...r)
{
    l += n;
    r += n;
    for (; l < r; l >>= 1, r >>= 1)
    {
        if (l & 1)
        {
            t[l++] += value;
        }
        if (r & 1)
        {
            t[--r] += value;
        }
    }
}
int query(int pos)
{
    pos += n;
    int res = t[pos];
    for (pos >>= 1; pos > 0; pos >>= 1)
    {
        res += t[pos];
    }
    return res;
}
// to inspect all elements of array in O(n) after some updates
void push()
{
    for (int i = 1; i < n; i++)
    {
        t[i << 1] += t[i];
        t[i << 1 | 1] += t[i];
        t[i] = 0;
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("range_increment_update_single_query_input.txt", "r", stdin);
    freopen("range_increment_update_single_query_output.txt", "w", stdout);
#endif
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> t[i + n];
    }
    // [1,2,3,1,2,3,4]
    cout << query(3) << endl;
    cout << query(6) << endl;

    update(0, 2, 5);

    //[ 6, 7, 3, 1, 2, 3, 4 ]
    cout << query(1) << endl;
    cout << query(2) << endl;

    update(1, 4, 10);

    //[ 6, 17, 13, 11, 2, 3, 4 ]
    cout << query(1) << endl;
    cout << query(2) << endl;

    push();
    cout << "Array: ";
    for (int i = 0; i < n; i++)
    {
        cout << t[i + n] << ' ';
    }
    return 0;
}