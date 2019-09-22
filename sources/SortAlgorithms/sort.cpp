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

        std::cout  << "Round:" << i << "\t" << A;
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

    std::cout << A;
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
