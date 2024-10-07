#include <iostream>
#include <stack>
#include <vector>

using namespace std;

vector<int> stock_span(const vector<int> &ns)
{
    // STUDENT ANSWER
    if (ns.size() == 0)
    {
        return ns;
    }
    stack<int> st;
    vector<int> get_value;

    for (int i = 0; i < ns.size(); i++)
    {
        st.push(ns[i]);
    }
    while (!st.empty())
    {
        int val = 1;
        int i = st.size() - 1;
        while (i >= 0)
        {
            if (st.top() < ns[i])
            {
                cout << "break" << endl;
                st.pop();
                break;
            }
            cout << val << " ";
            val += 1;
            i--;
        }
        result.push(val);
    }
    while (!result.empty())
    {
        get_value.push_back(result.top());
        result.pop();
    }
    return get_value;
}

int main()
{
    std::vector<int> st = {100, 80, 60, 70, 60, 75, 85};
    st = stock_span(st);
    for (int i = 0; i < st.size(); i++)
    {
        std::cout << st[i] << " ";
    }
}