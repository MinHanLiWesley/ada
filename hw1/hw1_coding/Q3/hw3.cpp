#include <algorithm>
#include <iostream>
#include <vector>

#include <math.h>
using namespace std;

/*
1. sort by x
2. divide
for each part:
    1. sort y
    2. pop own stack till it's empty or the distance to central line is smaller than top.distance
    3. Binary search (std::lower_bound) top.y in the oppsite stack.
    4. calculate the size upon the lower bound and store it
    5. push its self to its own stack

use vector<pair<long long,long long>> vec to store points
make_pair(first,last) x,y

vec.push_back(make_pair<long long,long long>(x,y));
vector<pair<long long,long long >> ::iterator iter;
for(iter=vec.negin();iter!=vec.end();iter++)
10,20,30,30,30,40,50
iter = lower_bound(vec.begin(),vec.end(),30); 
iter2 = lower_bound(vec.begin(),vec.end(),35);
iter3 = lower_bound(vec.begin(),vec.end(),55);
iter - vec.begin() = 2
iter2 - vec.begin() = 5
iter3 - vec.begin() = 7

vec.size()
vec.pop_back()
vec.push_back()


## stack ##
use struct
{
    long long cent_dis;
    pair<long long,long long> pt;
}

merge(l, r){
    mid = (l + r) / 2
    merge(l, mid)
    merge(mid + 1, r)
    line = (x[mid] + x[mid+1]) / 2
    conquer(line)
}
*/
// struct in stack(vector)
typedef struct Good
{
    double distance;
    pair<double, double> pt;
} Good;

//operator in std::lower_bound
bool smaller_than(const pair<double, double> &a, const pair<double, double> &b, double central_x)
{
    return abs(a.first - central_x) < abs(b.first - central_x);
}

//operator for sort by second elements in ascending
bool sortbyY(const pair<double, double> &a, const pair<double, double> &b)
{
    return (a.second < b.second);
}

bool Y_smaller_than_in_stack(pair<double, double> &opposite, double Y)
{
    return opposite.second <= Y;
}
// // if empty
// if (left_stack.empty())
// {
//     temp.pt = make_pair(vec[i].first,vec[i].second);
//     temp.distance = abs(central_x - vec[i].first);
//     left_stack.push_back(temp);
// }

long long calculate(vector<pair<double, double>> &vec, long long l, long long mid, long long r, double central_x, vector<pair<double, double>> &left_stack, vector<pair<double, double>> &right_stack)
{

    // int started = 0;
    // left = 1, right = 2
    int direction = 0;
    long long pts_cnt = r - l + 1;
    long long i = l;
    // 1. sort y
    sort(vec.begin() + l, vec.begin() + r + 1, sortbyY);

    long long gp_cnt = 0;
    while (pts_cnt--)
    {
        // check it is right(1) or left(2)
        direction = vec[i].first < central_x ? 1 : 2;

        // 2. pop own stack
        if (direction == 1)
        {

            // make sure the distance is descending from top to down

            // double distance = abs(central_x - vec[i].first);
            while (!left_stack.empty() && !smaller_than(left_stack.back(), vec[i], central_x))
            {
                // pop
                left_stack.pop_back();
            }

            // 3. binary search if there are elements inside the other stack
            if (!right_stack.empty())
            {
                // if the stack has element
                if (!left_stack.empty())
                {

                    auto iter = lower_bound(right_stack.begin(), right_stack.end(), left_stack.back().second, Y_smaller_than_in_stack);
                    // 4. calculate the size
                    gp_cnt += (right_stack.end() - iter);
                }
                else
                    gp_cnt += right_stack.size();
            }

            //5. push it self to the stack
            left_stack.push_back(make_pair(vec[i].first, vec[i].second));
        }
        //direction == 2
        else
        {
            // make sure the distance is descending from top to down

            while (!right_stack.empty() && !smaller_than(right_stack.back(), vec[i], central_x))
            {
                // pop
                right_stack.pop_back();
            }

            // 3. binary search if there are elements inside the other stack
            if (!left_stack.empty())
            {
                // if the stack has element
                if (!right_stack.empty())
                {
                    auto iter = lower_bound(left_stack.begin(), left_stack.end(), right_stack.back().second, Y_smaller_than_in_stack);
                    // 4. calculate the size
                    gp_cnt += (left_stack.end() - iter);
                }
                else
                    gp_cnt += left_stack.size();
            }

            //5. push it self to the stack
            right_stack.push_back(make_pair(vec[i].first, vec[i].second));
        }
        i++;
    }
    left_stack.clear();
    right_stack.clear();
    return gp_cnt;
}

long long find_gp(vector<pair<double, double>> &vec, long long l, long long r, vector<pair<double, double>> &left_stack, vector<pair<double, double>> &right_stack)
{
    long long ans = 0;

    if (l < r)
    {

        long long mid = (l + r) / 2;
        // find the central x
        double central_x = (vec[mid].first + vec[mid + 1].first) / 2.;
        ans += find_gp(vec, l, mid, left_stack, right_stack);
        ans += find_gp(vec, mid + 1, r, left_stack, right_stack);

        ans += calculate(vec, l, mid, r, central_x, left_stack, right_stack);
    }
    return ans;
}

int main()
{
    long long N = 0;
    cin >> N;
    vector<pair<double, double>> vec;
    vector<pair<double, double>> left_stack;
    vector<pair<double, double>> right_stack;
    for (long long i = 0; i < N; i++)
    {
        double x, y;
        cin >> x >> y;
        vec.push_back(make_pair(x, y));
    }
    // sort x
    sort(vec.begin(), vec.end());

    long long ans = 0;
    ans = find_gp(vec, 0, N - 1, left_stack, right_stack);

    cout << ans << endl;

    return 0;
}