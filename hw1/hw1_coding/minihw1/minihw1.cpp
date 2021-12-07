#include <iostream>

using namespace std;


long long int max_score(long long int p[],long long int n,long long int x,long long int y,long long int z)
{
    // long long int max_real = INT64_MIN;
    long long int max_ongoing = x * p[0] + z * p[1];
    long long int max_real = max_ongoing;
    for (int i = 2; i < n; i++)
    {
        max_ongoing = max(x * p[i-1] + z * p[i],max_ongoing + z * p[i] + (long long int)(y - z) * p[i - 1]);
        max_real = max(max_real, max_ongoing);
    }


    return max_real;
}

int main()
{
    long long int n, x, y, z;
    
    cin >> n >> x >> y >> z;

    long long int *p = new long long int[n]();
    // int p[] = {-12, 7, -127, -1, -2, -7};
    for (int i = 0; i < n; i++)
    {
        cin >> p[i];
    }

    long long int ans = max_score(p, n, x, y, z);

    cout << ans;

    return 0;
}