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

    // Stack which is realized using array, and cannot auto resize
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


    // Queue which is realized using array with fixed size
    // (need set size when initialized)
    Mcoder::Queue<int> queue(11);
    cout << "queue is empty: " << queue.empty()
         << "\t queue is full: " << queue.full() << endl;

    for (int item : test_array)
    {
        queue.enqueue(item);
    }

    cout << "queue is empty: " << queue.empty()
         << "\t queue is full: " << queue.full() << endl;
    for (int item : test_array)
    {
        int value = queue.dequeue();
        cout << value << "\t";
    }
    cout << endl;


    // 双向链表

    // 带有哨兵节点的双向链表

    // 三个数组实现的链表

    // 类似链表结构实现的有根数

    return 0;
}
