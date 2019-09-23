#include "sort.h"

#include <limits>

void insertion(std::vector<int> &A)
{
    for (unsigned int i = 1; i < A.size(); i++)
    {
        int key = A[i];
        int j = static_cast<int>(i-1);

        while(j >= 0 && A[static_cast<uint>(j)] > key)
        {
            A[static_cast<uint>(j+1)] = A[static_cast<uint>(j)];
            j--;
        }
        A[static_cast<uint>(j+1)] = key;

//        std::cout  << "Round:" << i << "\t" << A;
    }
}

void merge(std::vector<int> &A, int p, int q, int r)
{
    int n1 = q - p + 2;
    int n2 = r - q + 1;
    std::vector<int> L(static_cast<uint>(n1));
    std::vector<int> R(static_cast<uint>(n2));
    for(int i = 0; i < n1 - 1; i++)
        L[static_cast<uint>(i)] = A[static_cast<uint>(p + i)];
    for (int j = 0; j < n2 - 1; j++)
        R[static_cast<uint>(j)] = A[static_cast<uint>(q + j +1)];

    L[static_cast<uint>(n1 - 1)] = std::numeric_limits<int>::max();
    R[static_cast<uint>(n2 - 1)] = std::numeric_limits<int>::max();

    uint i = 0, j = 0;
    for(uint k = static_cast<uint>(p); k <= static_cast<uint>(r); k++)
    {
        if(L[i] <= R[j])
        {
            A[k] = L[i];
            i++;
        }
        else
        {
            A[k] = R[j];
            j++;
        }
    }
}

void merge_sort(std::vector<int> &A, int p, int r)
{
    if(p < r)
    {
        int q = (p + r)/2;
        merge_sort(A, p, q);
        merge_sort(A, q + 1, r);
        merge(A, p, q, r);
    }

//    std::cout << A;
}

std::ostream& operator << (std::ostream& out, std::vector<int> value)
{
    for(auto item:value)
    {
        out << item <<" ";
    }
    out << std::endl;

    return out;
}

void Heap::max_heapify(Heap &heap, uint i)
{
    uint l = left(i);
    uint r = right(i);
    uint largest = i;
    if(l < heap.heap_size && heap[l] > heap[i])
        largest = l;
    if(r < heap.heap_size && heap[r] > heap[largest])
        largest = r;
    if(largest != i)
    {
        int tmp = heap[i];
        heap[i] = heap[largest];
        heap[largest] = tmp;
        max_heapify(heap, largest);
    }

}

void Heap::build_max_heap(Heap &heap)
{
    heap.heap_size = static_cast<uint>(heap.data.size());
    for(int i = heap.heap_size/2 - 1; i >= 0; i--)
        max_heapify(heap, static_cast<uint>(i));
}

std::vector<int> Heap::heapsort(Heap &heap)
{
    build_max_heap(heap);
    for (uint i = heap.heap_size-1; i > 0; i--)
    {
        // Exchange A[i] A[0]
        int tmp = heap[0];
        heap[0] = heap[i];
        heap[i] = tmp;

        heap.heap_size--;
        max_heapify(heap, 0);
    }
    return heap.data;
}

int Priority_queue::extract_maximum()
{
    if(this->data.size() < 1)
    {
        std::cout << "heap underflow" << std::endl;
        return 0;
    }
    int max = data[0];
    data[0] = data[heap_size-1];
    heap_size--;
    max_heapify(*this, 0);

    return max;
}

void Priority_queue::increase_key(int i, int key)
{
    if(key < data[static_cast<uint>(i)])
    {
        std::cout << "new key is smaller than current key" << std::endl;
        return;
    }
    data[static_cast<uint>(i)] = key;
    while(i > 0 && data[parent(static_cast<uint>(i))] < data[static_cast<uint>(i)])
    {
        int tmp = data[static_cast<uint>(i)];
        data[static_cast<uint>(i)] = data[parent(static_cast<uint>(i))];
        data[parent(static_cast<uint>(i))] = tmp;
    }
}

void Priority_queue::heap_insert(int key)
{
    heap_size++;
    data.resize(heap_size);
    data[heap_size-1] = std::numeric_limits<int>::min();
    increase_key(static_cast<int>(heap_size-1), key);
}

void quicksort(std::vector<int> &A, int p, int r)
{
    if(p < r)
    {
        int q = partition(A, p, r);
        quicksort(A, p, q-1);
        quicksort(A, q + 1, r);
    }
}

int partition(std::vector<int> &A, int p, int r)
{
    int x = A[static_cast<uint>(r)];
    int i = p - 1;
    for(int j = p; j < r; j++)
    {
        if(A[static_cast<uint>(j)] <= x)
        {
            i++;
            // exchange A[i] A[j]
            int tmp = A[static_cast<uint>(i)];
            A[static_cast<uint>(i)] = A[static_cast<uint>(j)];
            A[static_cast<uint>(j)] = tmp;
        }
    }
    int tmp = A[static_cast<uint>(i+1)];
    A[static_cast<uint>(i+1)] = A[static_cast<uint>(r)];
    A[static_cast<uint>(r)] = tmp;

    return i + 1;
}

int randomized_partition(std::vector<int> &A, int p, int r)
{
    srand(static_cast<uint>(time(nullptr)));
    int i = rand() %(r-p) + p;

    // echange A[i] A[r]
    int x = A[static_cast<uint>(i)];
    A[static_cast<uint>(i)] = A[static_cast<uint>(r)];
    A[static_cast<uint>(r)] = x;
    i = p - 1;

    for(int j = p; j < r; j++)
    {
        if(A[static_cast<uint>(j)] <= x)
        {
            i++;
            // exchange A[i] A[j]
            int tmp = A[static_cast<uint>(i)];
            A[static_cast<uint>(i)] = A[static_cast<uint>(j)];
            A[static_cast<uint>(j)] = tmp;
        }
    }
    int tmp = A[static_cast<uint>(i+1)];
    A[static_cast<uint>(i+1)] = A[static_cast<uint>(r)];
    A[static_cast<uint>(r)] = tmp;

    return i + 1;
}

void randomized_quicksort(std::vector<int> &A, int p, int r)
{
    if(p < r)
    {
        int q = randomized_partition(A, p, r);
        randomized_quicksort(A, p, q-1);
        randomized_quicksort(A, q + 1, r);
    }
}
