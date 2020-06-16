#ifndef SORT_H
#define SORT_H

#include <vector>
#include <iostream>

// Insertion Sort
void insertion(std::vector<int> &A);

// Merge Sort
void merge(std::vector<int>& A, int p, int q, int r);
void merge_sort(std::vector<int>& A, int p, int r);

// Heap sort
// count from 0 1
class Heap
{
public:
    std::vector<int> data;
    uint heap_size;
    int& operator[](uint index){return data[index];}
    void max_heapify(Heap& heap, uint i);
    void build_max_heap(Heap& heap);
    std::vector<int> heapsort(Heap& heap);
    static uint parent(uint i){return (i-1)/2;}
    static uint left(uint i){return 2 * i + 1;}
    static uint right(uint i){return 2 * i +2;}
};

class Priority_queue
        :public Heap
{
    int maximum(){return this->data[0];}
    int extract_maximum();
    void increase_key(int i, int key);
    void heap_insert(int key);
};

// Quick sort
void quicksort(std::vector<int>& A, int p, int r);
int partition(std::vector<int>& A, int p, int r);

// Randomized quick sort
int randomized_partition(std::vector<int>& A, int p, int r);
void randomized_quicksort(std::vector<int>& A, int p, int r);

// Counting sort 计数排序
std::vector<int> counting_sort(std::vector<int>& A, int k);

// randomized select 随机找到 第i个大小的元素 归并法
int randomized_select(std::vector<int>& A, int p, int r, int i);


// Helper
std::ostream& operator << (std::ostream& out, std::vector<int> value);


#endif // SORT_H
