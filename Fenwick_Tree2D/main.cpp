#include <bits/stdc++.h>
using namespace std;
template <typename T = int>
class Fenwick2D
{
private:
    int n, m;
    vector<vector<T>> BIT;

public:
    void init(int n_, int m_)
    {
        n = n_;
        m = m_;
        BIT.assign(n_ + 1, vector<T>(m_ + 1, 0));
    }
    void add(int x, int y, T val)
    {
        assert(x >= 1 && x <= n && y >= 1 && y <= m);
        for (int x_ = x; x_ <= n; x_ += x_ & (-x_))
        {
            for (int y_ = y; y_ <= m; y_ += y_ & (-y_))
            {
                BIT[x_][y_] += val;
            }
        }
    }
    T query(int x, int y)
    {
        assert(x >= 0 && x <= n && y >= 0 && y <= m);
        T sum = 0;
        for (int x_ = x; x_ > 0; x_ -= x_ & (-x_))
        {
            for (int y_ = y; y_ > 0; y_ -= y_ & (-y_))
            {
                sum += BIT[x_][y_];
            }
        }
        return sum;
    }
    T query(int x1, int y1, int x2, int y2)
    {
        assert(x1 >= 1 && x1 <= n && y1 >= 1 && y1 <= m);
        assert(x2 >= 1 && x2 <= n && y2 >= 1 && y2 <= m);
        assert(x2 >= x1 && y2 >= y1);
        return query(x2, y2) - query(x2, y1 - 1) - query(x1 - 1, y2) + query(x1 - 1, y1 - 1);
    }
    T at(int x, int y)
    {
        assert(x >= 1 && x <= n && y >= 1 && y <= m);
        return query(x, y, x, y);
    }
    void set(int x, int y, T val)
    {
        assert(x >= 1 && x <= n && y >= 1 && y <= m);
        add(x, y, -at(x, y) + val);
    }
};
signed main()
{
    return 0;
}