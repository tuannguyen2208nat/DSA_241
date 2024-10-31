#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <queue>

using namespace std;

void interleaveQueue(queue<int> &q)
{
    queue<int> st;
    int halfnum = q.size() / 2;
    for (int i = 0; i < halfnum; i++)
    {
        st.push(q.front());
        q.pop();
    }
    while (!st.empty())
    {
        q.push(st.front());
        st.pop();
        q.push(q.front());
        q.pop();
    }
}
int main()
{
    queue<int> q;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int element;
        cin >> element;
        q.push(element);
    }
    interleaveQueue(q);
    while (!q.empty())
    {
        cout << q.front() << ' ';
        q.pop();
    }
}