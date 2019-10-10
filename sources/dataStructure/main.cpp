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

    /// Stack which is realized using array, and cannot auto resize
    {
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
    }


    /// Queue which is realized using array with fixed size
    /// (need set size when initialized)
    {
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
    }

    // 双向链表

    // 带有哨兵节点的双向链表

    // 三个数组实现的链表

    // 类似链表结构实现的有根数

    /// 二叉查找树 binary search tree
    {
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

        // 前序后继验证
        Mcoder::BinarySearchTreeNode<int> * pre = binary_search_tree.predecessor(
                    binary_search_tree.search_iterative( bst_inorder_array[5]));
        Mcoder::BinarySearchTreeNode<int> * successor = binary_search_tree.successor(
                    binary_search_tree.search_iterative( bst_inorder_array[5]));
        std::cout << "For node " << bst_inorder_array[5]
                  << "\tPredecessor: " << pre->data
                  << "\tSuccessor: " << successor->data
                  << std::endl;

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
    }

    /// 红黑树验证
    {
        Mcoder::RedBlackTree<int> red_black_tree;
        red_black_tree.NIL.data = -1;

        std::vector<int> test_array({64,25,1,0,6,59,44,46,68,79});

        // Test insert
        for (auto item:test_array)
        {
            red_black_tree.insert(item);
            std::vector<std::string> infos = red_black_tree.debug();
            std::cout << "\nINSERT TEST:\tRed Black Debug Info:\tAdded node:"<< item <<"\n";
            for(std::string &line: infos)
                std::cout << line << "\n";
        }

        // test inorder
        std::vector<int> inorder_list = red_black_tree.inorder_iterative();
        std::cout << "Test inorder:\t";
        for(int item:inorder_list)
        {
            std::cout << item << "\t";
        }
        std::cout << endl;

        // test successor predecessor
        Mcoder::RedBlackTreeNode<int> *pre = red_black_tree.predecessor(red_black_tree.search(red_black_tree.root, inorder_list[5]));
        Mcoder::RedBlackTreeNode<int> *suc = red_black_tree.successor(red_black_tree.search_iterative(inorder_list[5]));

        std::cout << "Test search and predecessor and successor:\t"
                  << "Search node: " << inorder_list[5]
                  << "\tPredecessor: " << pre->data
                  << "\tSuccessor: " << suc->data << "\n";

        // Test min max
        std::cout << "Min:\t" << red_black_tree.minimum()->data
                  << "\tMax:\t" << red_black_tree.maximum()->data << "\n";

        // Test Deletion
        for (int item:test_array)
        {
            red_black_tree.remove(red_black_tree.search_iterative(item));
            std::vector<std::string> infos = red_black_tree.debug();
            std::cout << "\nDELETE TEST\tRed Black Debug Info:\tDeleted node:\t"<< item <<"\n";
            for(std::string &line: infos)
                std::cout << line << "\n";
        }


    }


    return 0;
}
