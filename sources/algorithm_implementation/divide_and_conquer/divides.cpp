#include "divides.h"
#include "sort.h"
#include "limits"

std::vector<int> find_max_crossing_subarray(std::vector<int> &A, int low, int mid, int high)
{
    int left_sum = std::numeric_limits<int>::min();
    int sum = 0;
    int max_left = mid;
    for(int i = mid; i >= low; i--)
    {
        sum = sum + A[static_cast<uint>(i)];
        if(sum > left_sum)
        {
            left_sum = sum;
            max_left = i;
        }
    }

    int right_sum = std::numeric_limits<int>::min();
    int max_right = mid + 1;
    sum = 0;
    for (int j = mid + 1; j <= high; j++)
    {
        sum = sum + A[static_cast<uint>(j)];
        if(sum > right_sum)
        {
            right_sum = sum;
            max_right = j;
        }
    }

    std::vector<int> value(3);
    value[0] = max_left;
    value[1] = max_right;
    value[2] = left_sum + right_sum;
    return value;
}

std::vector<int> find_maximum_subarray(std::vector<int> &A, int low, int high)
{
    std::vector<int> value(3);
    if(low == high)
    {
        value[0] = low;
        value[1] = high;
        value[2] = A[static_cast<uint>(low)];
        return value;
    }
    else
    {

        int mid = (low + high) / 2;
        std::vector<int> left = find_maximum_subarray(A, low, mid);
        std::vector<int> right = find_maximum_subarray(A, mid + 1, high);
        std::vector<int> cross = find_max_crossing_subarray(A, low, mid, high);

        if(left[2] >= right[2] && left[2] >= cross[2])
        {
            return left;
        }
        else if (right[2] >= left[2] && right[2] >= cross[2])
        {
            return right;
        }
        else
        {
            return cross;
        }
    }
}


std::vector<int> find_maximum_subarray_nonrecursive(std::vector<int> &A)
{
    int max_left = 0;
    int max_right = 0;
    int max_sum = A[0];

    for(int i = 1; i < static_cast<int>(A.size()); i++)
    {
        int tmp_left = i;
        int tmp_sum = 0;
        int tmp_max_sum = std::numeric_limits<int>::min();
        for(int j = i; j >= 0; j--)
        {
            tmp_sum += A[j];
            if(tmp_sum > tmp_max_sum)
            {
                tmp_max_sum = tmp_sum;
                tmp_left = j;
            }
        }
        if(tmp_max_sum > max_sum)
        {
            max_left = tmp_left;
            max_right = i;
            max_sum = tmp_max_sum;
        }
    }

    return std::vector<int>({max_left, max_left, max_sum});
}
