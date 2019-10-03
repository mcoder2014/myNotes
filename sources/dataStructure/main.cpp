#include <iostream>
#include <vector>

#include "DataStructure"

using std::cout;
using std::endl;

int main()
{

    srand(static_cast<unsigned int>(time(nullptr)));
    unsigned int array_size = 10;
    std::vector<int> test_array(array_size);

    std::cout << "Test Array:\t" ;
    for(int &item : test_array)
    {
        item = rand()%100;
        std::cout << item << "\t";
    }

    std::cout << endl;

    // 数组实现的栈
    Mcoder::Stack<int> stack(50);
    cout << "stack is empty: " << stack.empty()<<std::endl;

    for (int &item : test_array)
    {
        stack.push(item);
    }
    for(int item:test_array)
    {
        int t = stack.pop();
        std::cout << t << "\t";
    }
    std::cout << std::endl;


    // 队列

    // 双向链表

    // 带有哨兵节点的双向链表

    // 三个数组实现的链表

    // 类似链表结构实现的有根数

    return 0;
}
