#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Utiliy
{
    enum
    {
        MOD = 1000000007LL
    };

public:
    T powmod(T a, T e, T m = MOD)
    {
        assert(e >= 0);
        a %= m;
        T res = 1;
        while (e > 0)
        {
            if (e & 1)
            {
                res *= a;
                if (res >= m)
                    res %= m;
            }
            e >>= 1;
            a *= a;
            if (a >= m)
            {
                a %= m;
            }
        }
        return res;
    }
    T pow(T a, T e)
    {
        assert(e >= 0);
        T res = 1;
        while (e > 0)
        {
            if (e & 1)
            {
                res *= a;
            }
            e >>= 1;
            a *= a;
        }
        return res;
    }
    T gcd(T a, T b)
    {
        while (b)
        {
            a %= b;
            swap(a, b);
        }
        return a;
    }
    T lcm(T a, T b)
    {
        return (a * b) / gcd(a, b);
    }
    T gcdext(T a, T b, T &x, T &y)
    {
        x = 1, y = 0;
        T x1 = 0, y1 = 1, a1 = a, b1 = b;
        while (b1)
        {
            T q = a1 / b1;
            tie(x, x1) = make_tuple(x1, x - q * x1);
            tie(y, y1) = make_tuple(y1, y - q * y1);
            tie(a1, b1) = make_tuple(b1, a1 - q * b1);
        }
        return a1;
    }
    T mod(T x, T m = MOD)
    {
        x %= m;
        if (x < 0)
            x += m;
        return x;
    }
    T addmod(T a, T b, T m = MOD)
    {
        return (a + b >= m) ? a + b - m : a + b;
    }
    T submod(T a, T b, T m = MOD)
    {
        return (a - b < 0) ? a - b + m : a - b;
    }
    T mulmod(T a, T b, T m = MOD)
    {
        return (a * b) % m;
    }
    T modinv(T a, T m = MOD)
    {
        return powmod(a, m - 2, m);
    }
    template <class X>
    X vmin(const X &a)
    {
        return a;
    }
    template <class Y, class... U>
    Y vmin(const Y &head, const U &... tail)
    {
        return min(head, vmin(tail...));
    }
    template <class X>
    X vmax(const X &a)
    {
        return a;
    }
    template <class Y, class... U>
    Y vmax(const Y &head, const U &... tail)
    {
        return max(head, vmax(tail...));
    }
};
signed main()
{
    return 0;
}