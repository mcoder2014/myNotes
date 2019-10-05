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

    // 二叉查找树
    Mcoder::BinarySearchTree<int> binary_search_tree;
    for (int item : test_array)
    {
        binary_search_tree.insert(item);
    }
    std::cout << "Minimum: " << binary_search_tree.minimum()->data
              << "\tMaximum: " << binary_search_tree.maximum()->data
              << "\n";

    std::vector<int> bst_inorder_array = binary_search_tree.inorder_iterative();
    std::cout << "inorder:";
    for (int item: bst_inorder_array)
    {
        std::cout << "\t" << item;
    }
    std::cout << "\n";


    for(int i=0; i < 5; i++)
    {
        Mcoder::BinarySearchTreeNode<int> * node = binary_search_tree.search(
                    binary_search_tree.root, test_array[i]);
        if(node != nullptr)
        {
            binary_search_tree.remove(node);
            delete node;
        }
        std::cout << "Remove: " << test_array[i] << "\n";
    }

    std::cout << "Minimum: " << binary_search_tree.minimum()->data
              << "\tMaximum: " << binary_search_tree.maximum()->data
              << "\n";

    bst_inorder_array = binary_search_tree.inorder_iterative();
    std::cout << "inorder:";
    for (int item: bst_inorder_array)
    {
        std::cout << "\t" << item;
    }
    std::cout << "\n";

    return 0;
}
