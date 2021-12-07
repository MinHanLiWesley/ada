#include <bits/stdc++.h>
#include <stdio.h>
#define F(a, b) for (int(a) = 0; (a) < (b); ++(a))
#define Fi(a, x, b) for (int(a) = (x); (a) <= (b); ++(a))
typedef long long ll;

using namespace std;

ll *Comp_array;

inline void Read(int &x)
{
    x = 0;
    char c;
    for (c = getchar(); c < '0' || c > '9'; c = getchar())
        ;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = (x << 3) + (x << 1) + c - '0';
}

void Write(ll x)
{
    if (x >= 10)
        Write(x / 10);
    putchar(x % 10 + '0');
}

class Node
{
public:
    Node(int _pos, Node *_parent, int _cat_size);
    Node(Node *_parent, int _cat_size);
    ~Node();
    int pos;
    Node *parent;
    int cat_size;
};

Node::Node(Node *_parent, int _cat_size)
{
    pos = 0;
    parent = _parent;
    cat_size = _cat_size;
}
Node::Node(int _pos, Node *_parent, int _cat_size)
{
    pos = _pos;
    parent = _parent;
    cat_size = _cat_size;
}
Node ::~Node()
{
}

class Cat
{
public:
    Cat(int N);
    ~Cat();
    map<int, Node *> garden;
    vector<Node> cat_map;
    void insert_map(Node *head_node, int cat_num, int dest);
    void move_single_cat(int cat_num, int dest);
    void place_feed(int dest, int rad);
    Node *find(Node *i);
    ll pair_num;
    ll Comb(int N);
};

Cat::Cat(int N)
{
    pair_num = 0;
    cat_map.resize(N + 1, Node(nullptr, 1));
    Fi(i, 1, N)
    {
        int coords;
        Read(coords);
        // scanf("%d", &coords);

        auto it = garden.lower_bound(coords);
        // found
        if (it != garden.end() && !(garden.key_comp()(coords, it->first)))
        {
            cat_map[i].parent = it->second;
            ++it->second->cat_size;

            pair_num += (Comb(it->second->cat_size) - Comb(it->second->cat_size - 1));
        }
        else
        {
            Node *tmp = new Node(coords, nullptr, 1);
            cat_map[i].parent = tmp;
            garden.emplace_hint(it, coords, tmp);
        }
    }
}

Cat::~Cat()
{
}
Node *Cat::find(Node *i)
{

    if (i->parent != nullptr)
    {
        Node *old_parent = i->parent;
        i->parent = find(i->parent);
        /*
            1-> A Node-> B Node -> C Node
        ==> 1->C Node, A Node -> C Node, B Node -> C Node
        we should reduce size of A Node and B Node since the child Node deesn't point to them anymore.
        However, we can't reduce C Node becuz 1, A Node and B Node are still pointing to it.    
        */
        // if the old_parent is empty, delete it.
        if (old_parent != i->parent && (old_parent->cat_size -= i->cat_size) == 0)
        {
            delete old_parent;
        }
        return i->parent;
    }
    else
    {
        return i;
    }
}
void Cat::insert_map(Node *head_node, int cat_num, int dest)
{

    auto it = garden.lower_bound(dest);
    if (it != garden.end() && !(garden.key_comp()(dest, it->first)))
    // found
    {
        pair_num += (Comb(it->second->cat_size + 1) - Comb(it->second->cat_size));
        ++it->second->cat_size;
        cat_map[cat_num].parent = it->second;
    }
    // not found
    else
    {
        //搬單隻貓
        //opcode = 2

        Node *tmp = new Node(dest, nullptr, 1);
        cat_map[cat_num].parent = tmp;

        garden.emplace_hint(it, dest, tmp);
    }
}

void Cat::move_single_cat(int cat_num, int dest)
{
    // extract cat_num
    Node *src_node = find(&cat_map[cat_num]);
    int src = src_node->pos;
    pair_num -= (Comb(src_node->cat_size) - Comb(src_node->cat_size - 1));
    --src_node->cat_size;
    if (src_node->cat_size == 0)
    {
        delete src_node;
        src_node = nullptr;
        garden.erase(src);
    }
    //insert to dest
    insert_map(src_node, cat_num, dest);
}

void Cat::place_feed(int dest, int rad)
{
    auto dest_it = garden.lower_bound(dest);
    Node *dest_ptr = nullptr;
    int assemble_cat_num = 0;
    //dest exist
    if (dest_it != garden.end() && !(garden.key_comp()(dest, dest_it->first)))
    {
        dest_ptr = dest_it->second;
        pair_num -= Comb(dest_ptr->cat_size);
    }
    else
    {
        Node *tmp = new Node(dest, nullptr, 0);
        dest_ptr = tmp;
        garden.emplace_hint(dest_it, dest, tmp);
    }

    auto it = garden.lower_bound(dest - rad);

    while (it != garden.end() && it->first <= dest + rad)
    {
        if (it->second->pos == dest)
        {
            advance(it, 1);
            continue;
        }
        assemble_cat_num += it->second->cat_size;
        pair_num -= Comb(it->second->cat_size);
        it->second->parent = dest_ptr;

        // auto tmp_it = it;
        // advance(it, 1);
        it = garden.erase(it);
    }
    dest_ptr->cat_size += assemble_cat_num;
    pair_num += Comb(dest_ptr->cat_size);
}

ll Cat::Comb(int N)
{
    if (N == 1)
        return 0;
    else if (Comp_array[N] > 0)
        return Comp_array[N];
    else
        return Comp_array[N] = ((ll)N * (N - 1)) >> 1;
}
int main()
{
    int N;
    Read(N);
    Comp_array = new ll[N+1]();
    // scanf("%d", &N);
    int M;
    Read(M);
    // scanf("%d", &M);
    Cat cat(N);

    while (M--)
    {
        int opcode;
        Read(opcode);
        // scanf("%d", &opcode);
        // 放食物
        if (opcode == 1)
        {
            int dest, rad;
            Read(dest);
            Read(rad);
            // scanf("%d %d", &dest, &rad);
            cat.place_feed(dest, rad);
        }
        else
        {
            int cat_num, dest;
            Read(cat_num);
            Read(dest);
            // scanf("%d %d", &cat_num, &dest);
            cat.move_single_cat(cat_num, dest);
        }
        Write(cat.pair_num);
        putchar('\n');
        // printf("%lld\n", cat.pair_num);
    }

    return 0;
}