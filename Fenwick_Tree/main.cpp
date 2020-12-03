#include <bits/stdc++.h>
using namespace std;

template <typename T = int>
class Fenwick
{
    // ATTENTION: This is always 1 indexed. //
private:
    int n; // positions from 1 to n;
    vector<T> BIT;

public:
    void init(int n_)
    {
        n = n_;
        BIT.assign(n + 1, 0);
    }
    void add(int pos, T val)
    {
        assert(pos <= n && pos >= 1);
        while (pos <= n)
        {
            BIT[pos] += val;
            pos += pos & (-pos);
        }
    }
    T query(int r)
    {
        assert(r >= 0 && r <= n);
        T sum = 0;
        while (r > 0)
        {
            sum += BIT[r];
            r -= r & (-r);
        }
        return sum;
    }
    T query(int l, int r)
    {
        return query(r) - query(l - 1);
    }
    T at(int pos)
    {
        assert(pos >= 1 && pos <= n);
        T sum = BIT[pos];
        int z = pos - (pos & -pos);
        pos--;
        while (pos != z)
        {
            sum -= BIT[pos];
            pos -= pos & (-pos);
        }
        return sum;
    }
    void set(int pos, T val)
    {
        T now = at(pos);
        add(pos, val - now);
    }
    /*

    for operation update(l,r,x), query(pos); // reverse operations only
    use: make simple fenwick tree, BIT
    use: update(l,r,x) ==> add(l,x) and add(r+1,-x) ==> increments all values in range[l..r] by x
    use: query(pos) ===> query(pos) ==> find value at position pos
    
    for operation update(l,r,x) and query(l); // range update & range query
    use: make 2 Fenwick tree, BIT1 and BIT2
    use: update(l,r,x) ==> BIT1.add(l,x) and BIT1.add(r+1,-x) and BIT2.add(l,x*(l-1)) and BIT2.add(r+1,-(x*r)) ==> increments all values in range[l..r] by x
    use: query(l) ==> BIT1.query(l)*l - BIT2.query(l) ==> returns prefix sum [1...l] 
    use: query(l,r) ==> query(r) - query(l-1) ==> range sum [l...r]

    */
};
signed main()
{
    return 0;
}