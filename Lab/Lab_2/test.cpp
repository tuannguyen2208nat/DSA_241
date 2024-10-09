#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int sumOfMaxSubarray(vector<int> &nums, int k)
{
    // STUDENT ANSWER
    int max = 0;
    int val = 0;
    queue<int> qu;
    for (int i = 0; i < int(nums.size()); i++)
    {
        val += nums[i];
        qu.push(nums[i]);
        if (qu.size() == k)
        {
            if (max < val)
            {
                max = val;
            }
            val -= qu.front();
            qu.pop();
        }
    }
    return max;
}

int main()
{
    // vector<int> nums{1, 2, 4, 3, 6};
    // int k = 3;
    // cout << sumOfMaxSubarray(nums, k);
    // cout << endl;
    vector<int> nums{8016};
    int k = 1;
    cout << sumOfMaxSubarray(nums, k);
    return 0;
}