#include <iostream>
#include <vector>
#ifdef DEBUG
#include <cassert>
#endif
using namespace std;

#define DTYPE long long

#define POS 1
#define NEG 0
/* treat zero as negative */
DTYPE N;
int flag;

struct element
{
    int index;
    DTYPE data;
};
#ifdef DEBUG
void output_table(vector<element> &table)
{
    for (int i = 0; i < table.size(); i++)
        cout << table[i].data << endl;
}
#endif
void solve(vector<DTYPE> &table)
{
    vector<element> new_table;
    new_table.resize(0);
    int state = table[0] > 0 ? POS : NEG;
    int old_state = state;

    /* input processing */
    element current_max_element;
    current_max_element.data = table[0];
    current_max_element.index = 1;
    for (int i = 0; i < table.size(); i++)
    {
        state = table[i] > 0 ? POS : NEG;
        if (state == old_state)
        {
            if (table[i] > current_max_element.data)
            {
                current_max_element.data = table[i];
                current_max_element.index = i + 1;
            }
            if (i == table.size() - 1)
                new_table.push_back(current_max_element);
        }
        else
        {
            new_table.push_back(current_max_element);
            state = table[i] > 0 ? POS : NEG;
            current_max_element.data = table[i];
            current_max_element.index = i + 1;
            if (i == table.size() - 1)
                new_table.push_back(current_max_element);
        }
        old_state = state;
    }
    if (new_table.size() == 1)
        ;
    else
    {
        if (new_table[0].data <= 0)
            new_table.erase(new_table.begin());
        if (new_table[new_table.size() - 1].data <= 0)
            new_table.pop_back();
    }
#ifdef DEBUG
    cout << "Output modified table:" << endl;
    output_table(new_table);
    cout << "----------------------------------" << endl;
#endif
    vector<element> stack;
    stack.resize(0);
    stack.push_back(new_table[0]);
    if (new_table.size() > 2)
    {
        stack.push_back(new_table[1]);
        stack.push_back(new_table[2]);

        DTYPE state1, state2, state3;
        for (int i = 3; i < new_table.size(); i += 2)
        {
            state1 = stack[stack.size() - 3].data + stack[stack.size() - 2].data;
            state2 = stack[stack.size() - 2].data + stack[stack.size() - 1].data;
            state3 = stack[stack.size() - 1].data + new_table[i].data;
            if (state1 < 0)
            {
                if (state1 < state2)
                {
                    // remove element of state1
                    stack.erase(stack.end() - 3);
                    stack.erase(stack.end() - 2);
                }
                else
                {
                    //remove element of state2
                    stack.erase(stack.end() - 2);
                    stack.erase(stack.end() - 1);
                }
                stack.push_back(new_table[i]);
                stack.push_back(new_table[i + 1]);
            }
            else
            {
                if (state2 < 0)
                {
                    if (state2 < state3)
                    {
                        // remove the element in state2
                        stack.erase(stack.end() - 2);
                        stack.erase(stack.end() - 1);
                        stack.push_back(new_table[i]);
                        stack.push_back(new_table[i + 1]);
                    }
                    else
                    {
                        // remove the element in state3
                        stack.erase(stack.end() - 1);
                        stack.push_back(new_table[i + 1]);
                    }
                }
                else
                {
                    //state1 and state2 are all larger than 0
                    stack.push_back(new_table[i]);
                    stack.push_back(new_table[i + 1]);
                }
            }
        }
        state1 = stack[stack.size() - 3].data + stack[stack.size() - 2].data;
        state2 = stack[stack.size() - 2].data + stack[stack.size() - 1].data;
        if (state1 < 0)
        {
            if (state1 < state2)
            {
                // remove element of state1
                stack.erase(stack.end() - 3);
                stack.erase(stack.end() - 2);
            }
            else
            {
                //remove element of state2
                stack.erase(stack.end() - 2);
                stack.erase(stack.end() - 1);
            }
        }
        else
        {
            if (state2 < 0)
            {
                // remove the element in state2
                stack.erase(stack.end() - 2);
                stack.erase(stack.end() - 1);
            }
        }
    }

    DTYPE global_max = 0;
    for (int i = 0; i < stack.size(); i++)
    {
        global_max += stack[i].data;
    }

#ifdef DEBUG
    cout << "######### Result = ";
#endif
    cout << global_max << endl;
#ifndef DEBUG
    if (flag == 1)
    {
#endif
        cout << stack.size() << " ";
        for (int i = 0; i < stack.size(); i++)
        {
            cout << stack[i].index;
#ifdef DEBUG
            cout << "(" << stack[i].data << ")";
#endif
            cout << " ";
        }
        cout << endl;
#ifndef DEBUG
    }
#endif
    return;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> flag;
    for (int i = 0; i < N; i++)
    {
        int num_c, temp;
        vector<DTYPE> table;
        cin >> num_c;
        table.resize(num_c);
        for (int j = 0; j < num_c; j++)
        {
            cin >> temp;
            table[j] = temp;
        }

        solve(table);
    }
    return 0;
}