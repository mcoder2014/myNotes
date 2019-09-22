#include <iostream>
#include <time.h>
#include <vector>
#include "sort.h"


int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    unsigned int array_size = 10;
    std::vector<int> test_array(array_size);

    for(int &item : test_array)
    {
        item = rand()%100;
    }

    std::cout << "Test Array:\t" << test_array;

    // Test Intertion sort
    std::vector<int> test_insertion(test_array);
    insertion(test_insertion);

    // Merge Sort
    std::vector<int> test_merge(test_array);
    merge_sort(test_merge, 0, static_cast<int>(test_merge.size() - 1));

    return 0;
}
