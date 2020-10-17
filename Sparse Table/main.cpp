/************************************************************************
* Works only when the array is immutable, ie. the values of array are not updated.
* The main idea of sparse table is to pre-calculate the ans for each interval of size 2^i
* s.t. 1 <= 2^i <= n as there can be only nlogn intervals of this type it can be done in nlogn time
* now let's say our we want some answer for range [i....j) then length of this will be |j-i| now this 
* range can be divided in log(|j-i|) subranges of type 2^k  and the result can be combined to get the 
* actual answer for the range [i...j)
*
*
* To, support our implementation lets take an array ST[][] where ST[i][j] will store the answer for range [i..(i+2^j))
* ST[i][0] = [i...i+1) is just single element of array that is A[i];
* ST[i][k] = [i....i + 2^k) ===> [i....i+2^(k-1)) INTERSECTION [i + 2^(k-1)......i + 2^(k-1) + 2^(k-1))
* ST[i][k] = combine( ST[i][k-1] ,ST[i+(1<<(k-1))][k-1] );
* ***************************************************************************************************/
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e7; // max array size
const int K = 25;  // log(N) ~ 25
int ST[N][K];
int n;
vector<int> arr;
int combine(int num)
{
    return num;
}
int combine(int num1, int num2)
{
    return num1 + num2;
}
void build()
{
    // To build ST table .. This example follows sum queries
    // O(nlogn)
    for (int j = 0; (1 << j) <= n; j++)
    {
        for (int i = 0; i + (1 << j) <= n; i++)
        {
            if (j == 0)
            {
                ST[i][j] = combine(arr[i]);
            }
            else
            {
                ST[i][j] = combine(ST[i][j - 1], ST[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
}
int query(int l, int r)
{
    // returns sum of arr from [l...r)
    // O(logn)
    int res = 0;
    while (r - l > 0)
    {
        int j = 32 - __builtin_clz(r - l) - 1;
        res += ST[l][j];
        l += (1 << j);
    }
    return res;
}
void util(int l, int r)
{
    cout << "Sum of values: ";
    for (int i = l; i < r; i++)
    {
        if (i == l)
        {
            cout << arr[i];
        }
        else
        {
            cout << " + " << arr[i];
        }
    }
    cout << " is: " << query(l, r) << endl;
}
int main()
{
    freopen("input.txt", "r", stdin);
    //freopen("output.txt","w",stdout);
    cin >> n;
    arr.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    build();
    util(0, n);
    util(0, 3);
    util(4, 9);
    util(3, 8);
}