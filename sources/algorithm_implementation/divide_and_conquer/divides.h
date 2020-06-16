#ifndef DIVIDES_H
#define DIVIDES_H

#include <vector>
#include <iostream>

std::vector<int> find_max_crossing_subarray(std::vector<int>& A, int low, int mid, int high);
std::vector<int> find_maximum_subarray(std::vector<int>& A, int low, int high);

std::vector<int> find_maximum_subarray_nonrecursive(std::vector<int>& A);

#endif // DIVIDES_H
