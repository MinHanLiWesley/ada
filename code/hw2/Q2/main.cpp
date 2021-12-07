#include <algorithm>
#include <cstring>
#include <iostream>
#include <numeric>

using namespace std;

// #define GCD(a, b) (gcd((a), (b)) == 1 ? (long long)-1 : (long long)gcd((a), (b)))

// #define GCD3(a, b, c) (gcd((a), (b)) == 1 ? (long long)-1 : (long long)gcd(gcd((a), (b)), (c)) == 1 ? (long long)-1 : (long long)gcd(gcd((a), (b)), (c))))

// bool gcd3(long long int a, long long int b, long long int c)
// {
//     if (gcd(a, b))
// }

long long int GCD(long long int GCD_chart[][500], long long int num[], int i, int j)
{
    if (GCD_chart[i][j] == 0)
        GCD_chart[i][j] = gcd(num[i], num[j]);
    return GCD_chart[i][j];
}

int main()
{
    // cin.sync_with_stdio(false), cin.tie(NULL);
    long long int length, num[500], dp[500][500], GCD_chart[500][500];
    scanf(" %lld", &length);
    // cin >> length;
    // memset(dp, (long long)-1e9, sizeof(dp));
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            dp[i][j] = -1;
        }
    }

    for (int i = 0; i < length; i++)
        scanf(" %lld", num + i);

    //length = 2
    for (int i = 0; i < length - 1; i++)
    {
        if (GCD(GCD_chart, num, i, i + 1) != 1)
            dp[i][i + 1] = GCD(GCD_chart, num, i, i + 1);
    }
    //length = 3
    for (int i = 0; i < length - 2; i++)
    {
        // long long int a = gcd(num[i], num[i + 1]);
        // long long int b = gcd(num[i+1], num[i + 2]);

        // if (a > 1 && b > 1 && gcd(a,b) > 1)
        // {
        //     dp[i][i + 2] = gcd(num[i], num[i + 1]) + gcd(num[i + 1], num[i + 2]);
        // }
        if (GCD(GCD_chart, num, i, i + 1) != 1 && GCD(GCD_chart, num, i + 1, i + 2) != 1 && GCD(GCD_chart, num, i, i + 2) != 1)
        {
            dp[i][i + 2] = GCD(GCD_chart, num, i, i + 1) + GCD(GCD_chart, num, i + 1, i + 2);
        }
    }

    //length = 4 up
    for (int k = 4; k <= length; k++)
    {
        for (int i = 0, j = i + k - 1; i < length - (k - 1); ++i, ++j)
        {
            //case 1
            if (GCD(GCD_chart, num, i, j) != 1 && dp[i + 1][j - 1] > 0)
            {
                dp[i][j] = max(dp[i][j], dp[i + 1][j - 1] + GCD(GCD_chart, num, i, j));
            }
            //case 2

            // i i+ 1 j
            if (GCD(GCD_chart, num, i, i + 1) != 1 && GCD(GCD_chart, num, i + 1, j) != 1 && GCD(GCD_chart, num, i, j) != 1 && dp[i + 2][j - 1] > 0)
            {
                dp[i][j] = max(dp[i][j], GCD(GCD_chart, num, i, i + 1) + GCD(GCD_chart, num, i + 1, j) + dp[i + 2][j - 1]);
            }

            // i j-1 j
            if (GCD(GCD_chart, num, i, j - 1) != 1 && GCD(GCD_chart, num, j - 1, j) != 1 && GCD(GCD_chart, num, i, j) != 1 && dp[i + 1][j - 2] > 0)
            {
                dp[i][j] = max(dp[i][j], GCD(GCD_chart, num, i, j - 1) + GCD(GCD_chart, num, j - 1, j) + dp[i + 1][j - 2]);
            }
            for (int l = i + 2; l <= j - 2; l++)
            {
                if (dp[i + 1][l - 1] > 0 && dp[l + 1][j - 1] > 0 && GCD(GCD_chart, num, i, l) != 1 && GCD(GCD_chart, num, l, j) != 1 && GCD(GCD_chart, num, i, j) != 1)
                {
                    dp[i][j] = max(dp[i + 1][l - 1] + dp[l + 1][j - 1] + GCD(GCD_chart, num, i, l) + GCD(GCD_chart, num, l, j), dp[i][j]);
                }
            }

            //case 3
            for (int m = i + 1; m < j; m++)
            {
                if (dp[i][m] != -1 && dp[m + 1][j] != -1)
                {
                    dp[i][j] = max(dp[i][j], dp[i][m] + dp[m + 1][j]);
                }
            }
        }
    }

    cout << dp[0][length - 1];
}
