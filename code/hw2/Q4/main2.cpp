#include <bits/stdc++.h>
using namespace std;

#define ll long long
class Node;
class Pair;
ll ans_arr[100001];
class Node
{
public:
    bool empty;
    ll l; // if no left => -1
    ll r;
    ll val;
    Pair *pair_ptr;
    // index
    Node() : empty(0), l(0), r(0), val(0), pair_ptr() {}

    Node(ll val_in) : empty(0), l(0), r(0), val(val_in), pair_ptr() {}
};

class Pair
{
public:
    ll left; // left idx in node arr
    ll right;
    ll val; // pair value
    bool lazy;

    // index
    Pair(deque<Node> &candy_lst, ll left_in, ll right_in) : left(left_in), right(right_in), val(candy_lst[left_in].val + candy_lst[right_in].val), lazy(0) {}
};

void clear_node(deque<Node> &candy_lst, ll i, ll j)
{

    ll tmp_left = candy_lst[i].l;
    ll tmp_right = candy_lst[j].r;
    // clear node in arr
    candy_lst[i].empty = 1;
    if (candy_lst[i].l != -1)
    {
        //put lazy tag in heap (i.l)
        Pair *tmp_pair_lft = candy_lst[candy_lst[i].l].pair_ptr;
        tmp_pair_lft->lazy = 1;
        candy_lst[candy_lst[i].l].r = tmp_right;
    }
    candy_lst[i].l = candy_lst[i].r = -1;
    //put lazy tag in heap (j)
    Pair *tmp_pair_rgt = candy_lst[j].pair_ptr;
    tmp_pair_rgt->lazy = 1;
    candy_lst[j].empty = 1;
    if (candy_lst[j].r != -1)
    {
        candy_lst[candy_lst[j].r].l = tmp_left;
    }
    candy_lst[j].r = candy_lst[j].l = -1;
}
struct cmp
{
    bool operator()(const Pair *a, const Pair *b)
    {
        /*
         The function call operator () can be overloaded for objects
         of class type. When you overload ( ), you are not creating 
         a new way to call a function.
         Rather, you are creating an operator function that can be 
         passed an arbitrary number of parameters.
         priority_queue優先判定為!cmp，所以「由大排到小」需「反向」定義
         實現「最小值優先」
         */
        return a->val > b->val;
    }
};

void push_new_pair(deque<Node> &candy_lst, priority_queue<Pair *, vector<Pair *>, cmp> &pq, ll l, ll r)
{
    Pair *pair = new Pair(candy_lst, l, r);
    // update pair ptr in candy list
    candy_lst[l].pair_ptr = pair;
    // push to pq
    pq.push(pair);
}

void print_ans(ll *ans_arr, ll N)
{
    for (ll i = 1; i <= N; i++)
    {
        printf("%lld ", ans_arr[i]);
        ans_arr[i] = 0;
    }
    printf("\n");
}

ll clean_input(deque<Node> &candy_lst, ll *raw_candy, long long size, ll &total)
{
    ll Max = raw_candy[0];
    candy_lst.emplace_back(raw_candy[0]);
    total = raw_candy[0];
    // now started
    for (long long i = 1; i < size; i++)
    {
        Max = max(raw_candy[i], Max);
        // now started
        if (raw_candy[i] * candy_lst.back().val < 0)
            candy_lst.emplace_back(raw_candy[i]), total += raw_candy[i];
        else
        {
            if(raw_candy[i] > candy_lst[candy_lst.size() - 1].val)
            {
                total += (raw_candy[i] - candy_lst.back().val);
                candy_lst[candy_lst.size() - 1].val = raw_candy[i];
            }
        }
    }
    return Max;
}

int main()
{
    int T, flag;
    // cin >> T >> flag;
    scanf(" %d %d", &T, &flag);
    ll raw_candy[100000];

    priority_queue<Pair *, vector<Pair *>, cmp> pq_big;
    priority_queue<Pair *, vector<Pair *>, cmp> pq_small;
    deque<Node> candy_lst_big;   //k
    deque<Node> candy_lst_small; //k-1
    while (T--)
    {
        ll N = 0, k_big = 0, k_small = 0, total_big = 0, total_small = 0;
        // scanf(" lld", &N);
        scanf(" %lld", &N);

        // clear vector candy_lst

        // ans_arr

        // first store value in num
        //TODO  change it to rawinput  (check)
        for (ll i = 0; i < N; i++)
        {
            // scanf(" lld", &(arr[i].val));
            scanf(" %lld", raw_candy + i);
        }

        // preprocessing input
        ans_arr[1] = clean_input(candy_lst_big, raw_candy, N, total_big);
        //TODO  modify k, pair_arr should refer to k not N (check)
        k_big = candy_lst_big.size();

        // Copying vector by assign function
        candy_lst_small.assign(candy_lst_big.begin(), candy_lst_big.end());

        // small part
        total_small = total_big;
        k_small = k_big - 1;
        // delete the smallest corner element in candy_big to candy_small
        if (candy_lst_small.front().val > candy_lst_small.back().val)
            total_small -= candy_lst_small.back().val, candy_lst_small.pop_back();
        else
            total_small -= candy_lst_small.front().val, candy_lst_small.pop_front();

        ans_arr[k_big] = total_big;
        ans_arr[k_small] = total_small;
        // only do heapify when input is larger than 2
        // big part
        if (k_big > 2)
        {
            // make ll and pq_object
            for (ll i = 0; i < k_big; i++)
            {

                // circular
                if (i == 0)
                {
                    candy_lst_big[i].l = k_big - 1;
                    candy_lst_big[i].r = 1;
                }
                else if (i == k_big - 1)
                {
                    candy_lst_big[i].l = k_big - 2;
                    candy_lst_big[i].r = 0;
                }
                else
                {
                    candy_lst_big[i].l = i - 1;
                    candy_lst_big[i].r = i + 1;
                }
                candy_lst_big[i].empty = 0;
                Pair *pair = new Pair(candy_lst_big, i, candy_lst_big[i].r);
                candy_lst_big[i].pair_ptr = pair;
                pq_big.push(pair);
            }

            for (ll i = 0; i < k_small; i++)
            {
                // circular
                if (i == 0)
                {
                    candy_lst_small[i].l = k_small - 1;
                    candy_lst_small[i].r = 1;
                }
                else if (i == k_small - 1)
                {
                    candy_lst_small[i].l = k_small - 2;
                    candy_lst_small[i].r = 0;
                }
                else
                {
                    candy_lst_small[i].l = i - 1;
                    candy_lst_small[i].r = i + 1;
                }
                candy_lst_small[i].empty = 0;
                Pair *pair = new Pair(candy_lst_small, i, candy_lst_small[i].r);
                candy_lst_small[i].pair_ptr = pair;
                pq_small.push(pair);
            }

            /*
           after preprocessing,
           1. assure k > 1 and k -= 2
           2. find the min pair in heap (pq.top)
           3. check lazy tag
           4. substract the total by pair.val and store it in ans arr
           5. clear_node(pair.l, arr[pair.l].r) put lazy tag in here
           6. push new node into heap

           */
            // big
            while (k_big > 1)
            {
                // step 1
                k_big -= 2;
                if (pq_big.empty())
                    break;
                // step 2
                while (pq_big.top()->lazy == 1 && !pq_big.empty())
                {
                    pq_big.pop();
                    // exit(1);
                }
                Pair *min_pair = pq_big.top();
                min_pair->lazy = 1;
                total_big -= min_pair->val;
                //step 3
                ans_arr[k_big] = total_big;
                //step 4
                ll tmp_left = candy_lst_big[min_pair->left].l;
                ll tmp_right = candy_lst_big[min_pair->right].r;
                clear_node(candy_lst_big, min_pair->left, candy_lst_big[min_pair->left].r);
                //step 5
                push_new_pair(candy_lst_big, pq_big, tmp_left, tmp_right);
                // //step 6
                // k -= 2;
            }

            // small
            while (k_small > 1)
            {
                k_small -= 2;
                if (pq_small.empty())
                    break;
                while (pq_small.top()->lazy == 1 && !pq_small.empty())
                {
                    pq_small.pop();
                    // exit(1);
                }
                Pair *min_pair = pq_small.top();
                min_pair->lazy = 1;
                total_small -= min_pair->val;
                //step 3
                ans_arr[k_small] = total_small;
                //step 4
                ll tmp_left = candy_lst_small[min_pair->left].l;
                ll tmp_right = candy_lst_small[min_pair->right].r;
                clear_node(candy_lst_small, min_pair->left, candy_lst_small[min_pair->left].r);
                //step 5
                push_new_pair(candy_lst_small, pq_small, tmp_left, tmp_right);
            }
        }
        // print_ans

        print_ans(ans_arr, N);

        //clear
        candy_lst_big.clear();
        candy_lst_small.clear();

        // clear pq
        while (!pq_big.empty())
        {
            pq_big.pop();
        }
        while (!pq_small.empty())
        {
            pq_small.pop();
        }
    }

    return 0;
}