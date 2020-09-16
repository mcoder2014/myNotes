#include <iostream>

#include <vector>
#include <string>

#include <alloca.h>

#include <ext/new_allocator.h>
#include <ext/mt_allocator.h>
#include <ext/pool_allocator.h>
#include <ext/debug_allocator.h>

using namespace std;

int main()
{
    allocator<int> alloc;
    int *p = alloc.allocate(2); //分配足够存放2个Int数据的空间
    int *free_space = p;
    alloc.construct(free_space, 1); //构造分配空间内对象，使用allocate分配的空间必须使用construct来构造对象
    free_space++;
    alloc.construct(free_space, 2);
    alloc.deallocate(p, 2); //释放空间
    return 0;
}