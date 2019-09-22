#include <iostream>
#include <vector>
#include <time.h>

#include "divides.h"

std::ostream& operator << (std::ostream& out, std::vector<int> value)
{
    for(auto item:value)
    {
        out << item <<" ";
    }
    out << std::endl;

    return out;
}

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    unsigned int array_size = 10;
    std::vector<int> test_array(array_size);

    for(int &item : test_array)
    {
        item = rand()%100;
        item -= 40;
    }

    std::cout << "Test Array:\t" << test_array;

    std::vector<int> max_subarray(test_array);
    std::vector<int> max_sub = find_maximum_subarray(max_subarray,0, max_subarray.size()-1);

    std::cout << "Result\t"
              << "Left\t" << max_sub[0]
              << "\tRight\t" << max_sub[1]
              << "\tSum\t" << max_sub[2] << std::endl;

    std::vector<int> max_sub_nonrecursive = find_maximum_subarray_nonrecursive(max_subarray);
    std::cout << "Result\t"
              << "Left\t" << max_sub_nonrecursive[0]
              << "\tRight\t" << max_sub_nonrecursive[1]
              << "\tSum\t" << max_sub_nonrecursive[2] << std::endl;

    return 0;
}
