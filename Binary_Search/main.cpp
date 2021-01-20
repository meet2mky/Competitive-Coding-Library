#include <iostream>
using namespace std;
int count(int arr[], int x, int n)
{
    if (x > arr[n - 1])
        return 0;
    if (x < arr[0])
        return 0;
    int L = -1, R = -1;
    if (arr[0] == x)
    {
        L = 0;
    }
    else
    {
        int l = 0, r = n - 1; // arr[l] < x && arr[r] <= x
        while (r - l > 1)
        {
            int m = (r + l) / 2;
            if (arr[m] >= x)
                r = m;
            else
                l = m;
        }
        L = r;
    }
    if (arr[n - 1] == x)
    {
        R = n - 1;
    }
    else
    {
        int l = 0, r = n - 1; // arr[l] <= x && arr[r] > x
        while (r - l > 1)
        {
            int m = (r + l) / 2;
            if (arr[m] > x)
                r = m;
            else
                l = m;
        }
        R = l;
    }
    if (R < L)
        return 0;
    return R - L + 1;
}
signed main()
{
    int arr[] = {1, 2, 3, 4, 4, 4, 5, 6, 6, 7, 8, 9, 10, 10, 11, 11}; // change
    int n = sizeof(arr) / sizeof(int);
    int x = 10; // change
    cout << "Count of " << x << " is: " << count(arr, x, n);
    return 0;
}