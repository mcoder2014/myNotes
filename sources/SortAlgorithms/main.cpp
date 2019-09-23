#include <iostream>
#include <time.h>
#include <vector>
#include "sort.h"


int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    unsigned int array_size = 17;
    std::vector<int> test_array(array_size);

    for(int &item : test_array)
    {
        item = rand()%100;
    }

    std::cout << "Test Array:\t" << test_array;

    // Test Intertion sort
    std::vector<int> test_insertion(test_array);
    insertion(test_insertion);
    std::cout << "Insertion:\t" << test_insertion;

    // Merge Sort
    std::vector<int> test_merge(test_array);
    merge_sort(test_merge, 0, static_cast<int>(test_merge.size() - 1));
    std::cout << "Merge sort:\t" << test_merge;

    // Heap sort
    std::vector<int> test_heap(test_array);
    Heap heap;
    heap.data = test_heap;
    heap.heapsort(heap);
    std::cout << "Heap:\t\t" << heap.data;

    // Quick sort
    std::vector<int> test_quick(test_array);
    quicksort(test_quick, 0, static_cast<int>(test_quick.size() - 1));
    std::cout << "Quick sort:\t" << test_quick;

    // Randomized quick sort
    std::vector<int> test_randomized_quick(test_array);
    randomized_quicksort(test_randomized_quick, 0, static_cast<int>(test_randomized_quick.size() - 1));
    std::cout << "Randomized quick sort:\t" << test_randomized_quick;

    // Counting sort
    std::vector<int> test_counting_sort(test_array);
    std::vector<int> test_counting_sort_result = counting_sort(test_counting_sort, test_insertion[test_insertion.size() - 1]);
    std::cout << "Counting sort:\t" << test_counting_sort_result;

    return 0;
}
