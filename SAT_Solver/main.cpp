#include <bits/stdc++.h>
using namespace std;
class SATSolver
{
private:
    int n; // number of variables * 2;
    vector<int> color, order, comp, assignment;
    vector<vector<int>> g, gr;
    bool valid;
    inline int complement(int a)
    {
        return (a & 1) ? a - 1 : a + 1;
    }
    void addedge(int x, int y)
    {
        g[x].emplace_back(y);
        gr[y].emplace_back(x);
    }
    void addor(int node_a, int node_b)
    {
        // not node_a then node_b;
        // not node_b then node_a;
        // true ---> true
        // false ---> false
        // false ----> true
        addedge(complement(node_a), node_b);
        addedge(complement(node_b), node_a);
    }
    void addxor(int node_a, int node_b)
    {
        addor(node_a, node_b);
        addor(complement(node_a), complement(node_b));
    }
    void dfs1(int s)
    {
        color[s] = 1;
        for (auto v : g[s])
        {
            if (color[v] == 0)
            {
                dfs1(v);
            }
        }
        order.push_back(s);
        color[s] = 2;
    }
    void dfs2(int s, int cid)
    {
        comp[s] = cid;
        for (auto v : gr[s])
        {
            if (comp[v] == -1)
            {
                dfs2(v, cid);
            }
        }
    }

public:
    void init(int n_) // n_ is # variables
    {
        valid = false;
        n = 2 * n_;
        g.assign(n, vector<int>());
        gr.assign(n, vector<int>());
    }
    void make_or(int not_var_a, int var_a, int not_var_b, int var_b) // or
    {
        int node_a = 2 * var_a;
        int node_b = 2 * var_b;
        if (not_var_a)
            node_a = complement(node_a);
        if (not_var_b)
            node_b = complement(node_b);
        addor(node_a, node_b);
    }
    void make_xor(int not_var_a, int var_a, int not_var_b, int var_b) // xor
    {
        int node_a = 2 * var_a;
        int node_b = 2 * var_b;
        if (not_var_a)
            node_a = complement(node_a);
        if (not_var_b)
            node_b = complement(node_b);
        addxor(node_a, node_b);
    }
    void make_true(int var_a) // forces var_a to "true";
    {
        make_or(0, var_a, 0, var_a);
    }
    void make_false(int var_a) // forces var_a to "false";
    {
        make_or(1, var_a, 1, var_a);
    }
    void make_bicondition(int not_var_a, int var_a, int not_var_b, int var_b) // both true or both false...opposite of xor
    {
        int node_a = 2 * var_a;
        int node_b = 2 * var_b;
        if (not_var_a)
            node_a = complement(node_a);
        if (not_var_b)
            node_b = complement(node_b);
        addxor(complement(node_a), node_b);
    }
    bool run()
    {
        valid = true;
        color.assign(n, 0);
        comp.assign(n, -1);
        assignment.assign(n / 2, 0);
        order.clear();
        order.reserve(n);
        for (int i = 0; i < n; i++)
        {
            if (color[i] == 0)
            {
                dfs1(i);
            }
        }
        for (int i = 0, cid = 0; i < n; i++)
        {
            int v = order[n - 1 - i];
            if (comp[v] == -1)
            {
                dfs2(v, cid++);
            }
        }
        for (int i = 0; i < n; i += 2)
        {
            if (comp[i] == comp[i + 1])
                return false;
            assignment[i / 2] = comp[i] > comp[i + 1];
        }
        return true;
    }
    vector<int> solution()
    {
        return assignment;
    }
};
signed main()
{
    return 0;
}