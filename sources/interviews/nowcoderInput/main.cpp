#include <iostream>
#include <vector>

using namespace std;

int main()
{

    int n;
    cin >> n;
    vector<vector<int>> arrays;
    for (int i = 0; i < n; i++)
    {
        vector<int> array;

        int a;
        while (cin >> a)
        {
            array.push_back(a);
            if (cin.get() == '\n')
            {
                break;
            }
        }
        arrays.push_back(array);
    }

    for (vector<int> &array : arrays)
    {
        for (int item : array)
        {
            cout << item << " ";
        }
        cout << endl;
    }

    return 0;
}