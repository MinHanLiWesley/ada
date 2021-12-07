#include <iostream>
#include <math.h>
#include <string>
#include <vector>
using namespace std;

// #define DEBUG

void println(long long *arr, long long size, string name)
{
    cout << name << ": ";
    for (long long i = 0; i < size; i++)
    {
        cout << arr[i] << ", ";
    }
    cout << endl;
}

typedef struct Candy
{
    long long sweetness;
    long long idx;
} Candy;

typedef struct Final_lst
{
    long long max;
    long long cnt;
    long long *arr;
} Final_lst;

void find_max_2(Candy *candy_lst, vector<Candy> &candy_stack, long long size, Final_lst *final_lst)
{
    if (size == 1)
    {
        candy_stack.push_back(candy_lst[0]);
        final_lst->cnt = 1;
        final_lst->max = candy_lst[0].sweetness;
        final_lst->arr[0] = candy_lst[0].idx;
    }
    else
    {
        long long A, B, C;
        // element in stack
        long long stack_cnt = 0;
        // use to calcaulate  elements between zeros
        long long cont_stack_cnt = 0;
        // element in candy_lst
        long long n = 0;
        int started = 0;
        while (n < size)
        {
// if next is 0 or nothing and there are three elements in stack
#ifdef DEBUG
            cout << "now: " << candy_lst[n].sweetness << endl;
#endif
            // if (((n + 1) == size || (n < (size - 1) && candy_lst[n + 1] == 0)) && stack_cnt > 1)
            //     goto check;

            if (candy_lst[n].sweetness == 0)
            {
                if (cont_stack_cnt >= 3)
                {
                    A = candy_stack[stack_cnt - 3].sweetness + candy_stack[stack_cnt - 2].sweetness;
                    B = candy_stack[stack_cnt - 2].sweetness + candy_stack[stack_cnt - 1].sweetness;
                    if (A < 0 || B < 0)
                    {
                        if (A < B)
                        //pop A
                        {
                            Candy temp = candy_stack[stack_cnt - 1];
                            for (int i = 0; i < 3; i++)
                            {
                                candy_stack.pop_back();
                                stack_cnt--;
                                cont_stack_cnt--;
                            }
                            candy_stack.push_back(temp);
                            stack_cnt++;
                        }
                        else
                        // pop B
                        {
                            for (int i = 0; i < 2; i++)
                            {
                                candy_stack.pop_back();
                                stack_cnt--;
                                cont_stack_cnt--;
                            }
                        }
                    }
                }
                candy_stack.push_back(candy_lst[n++]);
                stack_cnt++;
                started = 0;
            }
            if (!started)
            {
                candy_stack.push_back(candy_lst[n++]);
                stack_cnt++;
                cont_stack_cnt++;
                started = 1;
                continue;
            }

            // if empty, push until three element insides
            while (stack_cnt < 3)
            {
                candy_stack.push_back(candy_lst[n++]);
                stack_cnt++;
                cont_stack_cnt++;
            }

            // A = stack[-3] + stack[-2]
            // B = stack[-2] + stack[-1]
            // C = stack[-1] + array[n]
            A = candy_stack[stack_cnt - 3].sweetness + candy_stack[stack_cnt - 2].sweetness;
            B = candy_stack[stack_cnt - 2].sweetness + candy_stack[stack_cnt - 1].sweetness;
            C = candy_stack[stack_cnt - 1].sweetness + candy_lst[n].sweetness;

            if (A < 0)
            {
                //popB
                if (B <= A)
                {

                    for (int i = 0; i < 2; i++)
                    {
                        candy_stack.pop_back();
                        stack_cnt--;
                        cont_stack_cnt--;
                    }
                    for (int i = 0; i < 2; i++)
                    {
                        candy_stack.push_back(candy_lst[n++]);
                        stack_cnt++;
                        cont_stack_cnt++;
                    }
                }
                else
                {
                    // pop A
                    Candy temp = candy_stack[stack_cnt - 1];
                    for (int i = 0; i < 3; i++)
                    {
                        candy_stack.pop_back();
                        stack_cnt--;
                        cont_stack_cnt--;
                    }
                    candy_stack.push_back(temp);
                    stack_cnt++;
                    cont_stack_cnt++;
                    // push new 2 elements
                    for (int i = 0; i < 2; i++)
                    {
                        candy_stack.push_back(candy_lst[n++]);
                        stack_cnt++;
                        cont_stack_cnt++;
                    }
                }
            }
            else
            {
                if (B <= 0)
                {
                    if (B <= C)
                    // pop B
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            candy_stack.pop_back();
                            stack_cnt--;
                            cont_stack_cnt--;
                        }
                        for (int i = 0; i < 2; i++)
                        {
                            candy_stack.push_back(candy_lst[n++]);
                            stack_cnt++;
                            cont_stack_cnt++;
                        }
                    }
                    else
                    // pop C
                    {
                        candy_stack.pop_back();
                        stack_cnt--;
                        cont_stack_cnt--;
                        n++;
                        candy_stack.push_back(candy_lst[n++]);
                        stack_cnt++;
                        cont_stack_cnt++;
                    }
                }
                // A > 0 and B > 0
                else
                {
                    // fill
                    for (int i = 0; i < 2; i++)
                    {
                        candy_stack.push_back(candy_lst[n++]);
                        stack_cnt++;
                        cont_stack_cnt++;
                    }
                }
            }
        }

        // no things to push
        if (stack_cnt == 1)
        {
            final_lst->cnt = 1;
            final_lst->max = candy_stack[stack_cnt - 1].sweetness;
            final_lst->arr[0] = candy_stack[stack_cnt - 1].idx;
        }
        else
        {

            A = candy_stack[stack_cnt - 3].sweetness + candy_stack[stack_cnt - 2].sweetness;
            B = candy_stack[stack_cnt - 2].sweetness + candy_stack[stack_cnt - 1].sweetness;
            if (A < 0 && B < 0)
            {
                //pop A
                if (A < B)
                {
                    Candy temp = candy_stack[stack_cnt - 1];
                    for (int i = 0; i < 3; i++)
                    {
                        candy_stack.pop_back();
                        stack_cnt--;
                        cont_stack_cnt--;
                    }
                    candy_stack.push_back(temp);
                    stack_cnt++;
                }
                //pop B
                else
                {
                    for (int i = 0; i < 2; i++)
                    {
                        candy_stack.pop_back();
                        stack_cnt--;
                        cont_stack_cnt--;
                    }
                }
            }
            else if (A < 0 && A < B)
            {
                Candy temp = candy_stack[stack_cnt - 1];
                for (int i = 0; i < 3; i++)
                {
                    candy_stack.pop_back();
                    stack_cnt--;
                    cont_stack_cnt--;
                }
                candy_stack.push_back(temp);
                stack_cnt++;
            }
            else if (B < 0 && B < A)
            {
                for (int i = 0; i < 2; i++)
                {
                    candy_stack.pop_back();
                    stack_cnt--;
                    cont_stack_cnt--;
                }
            }

            // calculate max
            // long long max = 0;

            long long temp_stack_cnt = stack_cnt;
            final_lst->max = 0;
            for (long long i = 0; i < stack_cnt; i++)
            {
                if (candy_stack[i].idx == 0)
                {
                    temp_stack_cnt--;
                    continue;
                }
                final_lst->max += candy_stack[i].sweetness;
                final_lst->arr[i] = candy_stack[i].idx;
            }
            final_lst->cnt = temp_stack_cnt;
        }
    }
}

long long clean_input(Candy *raw_candy, Candy *candy_lst, long long size)
{
    long long remove_cnt = 0;
    long long remain_cnt = 0;
    // int is_neg = 0;
    long long has_neg = 0;
    long long started = 0;
    long long renew = 0;
    Candy pos, neg;
    pos.sweetness = INT64_MIN;
    neg.sweetness = INT64_MIN;
    pos.idx = 0;
    neg.idx = 0;
    // long long pos = INT64_MIN, neg = INT64_MIN;
    long long cont_pos = 0, cont_neg = 0, cont_zero = 0;
    for (long long i = 0; i < size; i++)
    {
#ifdef DEBUG
        // println(raw_candy, size, "raw candy");
        // println(candy_lst, remain_cnt, "candy_lst");
#endif
        // remove the first negative part
        if (!started || !renew)
        {
            cont_zero = 0;
            if (raw_candy[i].sweetness <= 0)
            {
                remove_cnt++;
                if (neg.sweetness < raw_candy[i].sweetness)
                    neg = raw_candy[i];
                // neg = max(neg, raw_candy[i].sweetness);
                continue;
            }
            else
            {
                started = 1;
                renew = 1;
                pos = raw_candy[i];
                // add first pos to list
                candy_lst[remain_cnt++] = raw_candy[i];
                continue;
            }
        }

        // now started
        if (raw_candy[i].sweetness < 0)
        {
            cont_zero = 0;
            cont_pos = 0;
            has_neg = 1;
            if (cont_neg)
            {
                if (candy_lst[remain_cnt - 1].sweetness < raw_candy[i].sweetness)
                    candy_lst[remain_cnt - 1] = raw_candy[i];
                // candy_lst[remain_cnt - 1] = max(candy_lst[remain_cnt - 1], raw_candy[i]);
                remove_cnt++;
            }
            else
            {
                candy_lst[remain_cnt++] = raw_candy[i];
                neg = raw_candy[i];
                cont_neg = 1;
            }
        }
        else if (raw_candy[i].sweetness == 0)
        {
            renew = 0;
            cont_neg = 0;
            cont_pos = 0;
            has_neg = 0;
            // check the prev is neg or not
            if (candy_lst[remain_cnt - 1].sweetness < 0)
            {
                // candy_lst[remain_cnt - 1] = 0;
                candy_lst[remain_cnt - 1] = raw_candy[i];
            }
            else
            {
                if (!cont_zero)
                {
                    candy_lst[remain_cnt++] = raw_candy[i];
                    cont_zero = 1;
                }
                else
                {
                    remove_cnt++;
                    continue;
                }
            }
        }
        // candy>0
        else
        {
            if (has_neg)
            {
                if (cont_pos)
                {
                    if (candy_lst[remain_cnt - 1].sweetness < raw_candy[i].sweetness)
                        candy_lst[remain_cnt - 1] = raw_candy[i];
                    // candy_lst[remain_cnt - 1] = max(candy_lst[remain_cnt - 1], raw_candy[i]);
                    remove_cnt++;
                }
                else
                {
                    candy_lst[remain_cnt++] = raw_candy[i];
                    cont_pos = 1;
                }
            }
            else
            {
                if (pos.sweetness < raw_candy[i].sweetness)
                    pos = raw_candy[i];
                // pos = max(pos, raw_candy[i].sweetness);
                candy_lst[remain_cnt - 1] = pos;
            }
            cont_neg = 0;
            cont_zero = 0;
            // is_neg = 0;
        }
    }

    // all negative or positive
    if (remain_cnt == 1 || started == 0)
    {
        if (candy_lst[0].sweetness <= 0 || started == 0)
        // neg is answer
        {
            candy_lst[0] = neg;
            remain_cnt = 1;
#ifdef DEBUG
            cout << "max neg: " << neg.sweetness << endl;
#endif
        }
        else

        {
            candy_lst[0] = pos;
            remain_cnt = 1;
#ifdef DEBUG
            cout << "max pos: " << pos.sweetness << endl;
#endif
        }
    }
    else
    {
        // make sure the last element is positive
        if (candy_lst[remain_cnt - 1].sweetness <= 0)
        {
            remain_cnt--;
        }
#ifdef DEBUG
        // make sure there are two  or more elements in candy_lst
        if (remain_cnt == 1)
        {
            cout << "max pos(0): " << candy_lst[0].sweetness << endl;
        }
        else
        {
            cout << "final candy_lst: ";
            for (int i = 0; i < remain_cnt; i++)
            {
                cout << candy_lst[i].sweetness << ", ";
            }
            cout << endl;
        }
#endif
    }
    return remain_cnt;
}

int main()
{
    long long t, flag;
#ifdef DEBUG
    // t = 1, flag = 0;
    cin >> t >> flag;
#else
    cin >> t >> flag;

#endif
    long long n = 0;
    long long remain_cnt = 0;
    long long max = 0;
    Candy *raw_candy = new Candy[100005]();
    Candy *candy_lst = new Candy[100005]();
    Final_lst *final_lst = new Final_lst();
    final_lst->arr = new long long[100005]();
    while (t--)
    {
        n = 0;
        remain_cnt = 0;
        max = 0;

        cin >> n;
        for (long long i = 0; i < n; i++)
        {
            cin >> raw_candy[i].sweetness;
            raw_candy[i].idx = i + 1;
            candy_lst[i].sweetness = 0;
            candy_lst[i].idx = 0;
            final_lst->arr[i] = 0;
        }

        final_lst->cnt = 0;
        final_lst->max = 0;

        vector<Candy> candy_stack;

        // // int raw_candy[] = {-3, 0, 2, 3, 0, 0, -1, 2, 3, -1, -10};
        // long long raw_candy[] = {-1, -2, -3, -4};
        // long long candy_lst[20];

        remain_cnt = clean_input(raw_candy, candy_lst, n);
#ifdef DEBUG
        cout << "remain_cnt: " << remain_cnt << endl;
#endif
        find_max_2(candy_lst, candy_stack, remain_cnt, final_lst);
#ifdef DEBUG
        cout << "real max: " << final_lst->max << endl;
#else

        cout << final_lst->max << endl;
#endif
        if (flag)
        {
            cout << final_lst->cnt << " ";
            for (long long i = 0; i < final_lst->cnt; i++)
            {
                if (final_lst->arr[i] == 0)
                    return 1;
                cout << final_lst->arr[i] << " ";
            }
            cout << endl;
        }
#ifdef DEBUG
        long long max = 0;
        for (long long i = 0; i < final_lst->cnt; i++)
        {
            max += candy_stack[i].sweetness;
        }

        assert(max == final_lst->max);
#endif
        // long long max = 0;
        // for (long long i = 0; i < final_lst->cnt; i++)
        // {
        //     max += raw_candy[final_lst->arr[i]-1].sweetness;
        // }
        // if( max != final_lst->max)
        // {
        //     return 1;
        //     cout << "FATAL ERROR!!!!" << endl;
        //     cout << "final_lst->max: " << final_lst->max << endl;
        //     cout << "max: " << max << endl;
        // }
        // assert(max == final_lst->max);
        candy_stack.clear();
    }

    return 0;
}