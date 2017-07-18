class Solution {
public:
bool Find(int target, vector<vector<int> > array) {
    if (array.empty())return false;
    //if (target < array[0][0])return false;
    int _length = array.size();
    for (int i = 0; i < _length; i++)
    {
        if (array[i].empty())continue;
        else if(target >= array[i][0])
        {
            if (target <= array[i][array[i].size() - 1])
            {
                for (int j = array[i].size() - 1; j >= 0; j--)
                {
                    if (target == array[i][j])return 1;
                    else if (target > array[i][j])break;
                }
            }
            else {
                continue;
            }
        }
        else return false;
    }
    return false;
}
};
