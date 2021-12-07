#include <algorithm>
#include <cstring>
#include <iostream>
#include <numeric>

using namespace std;

#define GCD(a, b) (gcd((a), (b)) == 1 ? (long long)-1 : (long long)gcd((a), (b)))

#define GCD3(a, b, c) (gcd((a), (b)) == 1 ? (long long)-1 : (long long)gcd(gcd((a), (b)), (c) == 1 ? (long long)-1 : (long long)gcd(gcd((a), (b)), (c))))

int main()
{
    cout << GCD3(2, 3, 5) <<endl;
    cout << GCD3(2, 3, 6) <<endl;
    cout << GCD3(2, 4, 5) <<endl;
    cout << GCD3(5, 10, 5) <<endl;
}