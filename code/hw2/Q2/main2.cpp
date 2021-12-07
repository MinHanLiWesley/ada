#include <algorithm>
#include <cstring>
#include <iostream>
#include <numeric>

using namespace std;

#define GCD(a, b) (gcd((a), (b)) == 1 ? (long long)-1 : (long long)gcd((a), (b)))

#define GCD3(a, b, c) (gcd((a), (b)) == 1 ? (long long)-1 : (long long)gcd(gcd((a), (b)), (c) == 1 ? (long long)-1 : (long long)gcd(gcd((a), (b)), (c))))

int main()
{
    cin.sync_with_stdio(false), cin.tie(NULL);
    long long int length, num[500], dp[500][500];
    cin >> length;
    // memset(dp, (long long)-1e9, sizeof(dp));
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            dp[i][j] = -1;
        }
    }

    for (int i = 0; i < length; i++)
        cin >> num[i];

    for (int i = 0; i < length - 2; i++)
    {
        dp[i][i + 1] = GCD(num[i], num[i + 1]);
    }

    for (int i = 0; i < length - 3; i++)
    {
        if (GCD3(num[i], num[i + 1], num[i + 2])>0)
        {
            dp[i][i + 2] = GCD(num[i], num[i + 1]) + GCD(num[i + 1], num[i + 2]);
        }
    }

    for (int k = 4; k < length; k++)
    {
        for (int i = 0, j = i + k; j < length; ++i, ++j)
        {
            //case 1
            if (GCD(num[i], num[j]) > 0 && dp[i+1][j-1] > 0)
            {
                dp[i][j] = max(dp[i][j],dp[i + 1][j - 1] + GCD(num[i], num[j]));
            }
            //case 2

            // i i+ 1 j
            if(GCD3(num[i],num[i+1],num[j])>0 && dp[i+2][j-1] > 0)
            {
                dp[i][j] =  max(dp[i][j],GCD(num[i], num[i + 1]) + GCD(num[i + 1], num[j]) + dp[i + 2][j - 1]);
            }
            // i j-1 j
            if(GCD3(num[i],num[j-1],num[j])>0 && dp[i+1][j-2] > 0)
            {
                dp[i][j] =  max(dp[i][j],GCD(num[i], num[j-1]) + GCD(num[j -1], num[j]) + dp[i + 1][j - 2]);
            }
            for (int l = i + 2; l < j-1; l++)
            {

                if(dp[i+1][l-1] > 0 && dp[l+1][j-1] > 0 && GCD3(num[i],num[l],num[j]) > 0)
                {
                    dp[i][j] = max(dp[i + 1][l - 1] + dp[l + 1][j - 1] + GCD(num[i], num[l]) + GCD(num[l], num[j]), dp[i][j]);
                }
            }

            //case 3
            for (int m = i + 1; m < j; m++)
            {
                if(dp[i][m] != -1 && dp[m+1][j]  != -1)
                {
                    dp[i][j] = max(dp[i][j], dp[i][m] + dp[m + 1][j]);
                }
            }
        }
    }

    cout << dp[0][length - 1] << '\n';
}
