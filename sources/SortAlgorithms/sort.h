#ifndef SORT_H
#define SORT_H

#include <vector>
#include <iostream>

// Insertion Sort
void insertion(std::vector<int> &A);

// Merge Sort
void merge(std::vector<int>& A, int p, int q, int r);
void merge_sort(std::vector<int>& A, int p, int r);

// Helper
std::ostream& operator << (std::ostream& out, std::vector<int> value);


#endif // SORT_H
