#include <iostream>
#include <vector>

using namespace std;

vector<int> updateArrayPerRange(vector<int> &nums, vector<vector<int>> &operations)
{

    for (int i = 0; i < int(nums.size()); i++)
    {
        int index = abs((i - int(operations[0].size() - 1)));
        cout << index << endl;
        int max = operations[0][index] >= operations[1][index] ? operations[0][index] : operations[1][index];
        int min = operations[0][index] <= operations[1][index] ? operations[0][index] : operations[1][index];
        cout << "max : " << max << " " << "min : " << min << endl;
        cout << "X : " << operations[2][index] << endl;
        if ((nums[i] <= max) && nums[i] >= min)
        {
            nums[i] = nums[i] + operations[2][index];
        }
    }

    return nums;
}

int main()
{
    vector<int> nums{13, 0, 6, 9, 14, 16};                            // Corrected semicolon
    vector<vector<int>> operations{{5, 5, 16}, {3, 4, 0}, {0, 2, 8}}; // Corrected spacing if necessary

    updateArrayPerRange(nums, operations);
}