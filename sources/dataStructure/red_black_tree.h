#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>
#include <vector>

namespace Mcoder
{

template<typename basetype>
class RedBlackTreeNode
{
public:
    RedBlackTreeNode<basetype> *parent;
    RedBlackTreeNode<basetype> *lchild;
    RedBlackTreeNode<basetype> *rchild;

    basetype data;
    bool color;     // true for red, false for black

    RedBlackTreeNode()
    {
        parent = nullptr;
        lchild = nullptr;
        rchild = nullptr;
    }

    RedBlackTreeNode(RedBlackTreeNode<basetype> * NIL)
        :parent(NIL),lchild(NIL),rchild(NIL)
    {}
};

template<typename basetype>
class RedBlackTree{
public:
    RedBlackTreeNode<basetype> NIL;
    RedBlackTreeNode<basetype> *root;

    RedBlackTree()
    {}
    ~RedBlackTree()
    {}
    std::vector<basetype> inorder_iterative()
    {}
    std::vector<basetype> inorder_iterative(RedBlackTreeNode<basetype> *root)
    {}
    RedBlackTreeNode<basetype> *search(RedBlackTreeNode<basetype> *x, const basetype& key)
    {}
    RedBlackTreeNode<basetype> *search_iterative(const basetype& key)
    {}
    RedBlackTreeNode<basetype> *minimum()
    {}
    RedBlackTreeNode<basetype> *minimum(RedBlackTreeNode<basetype> *node)
    {}
    RedBlackTreeNode<basetype> *maximum()
    {}
    RedBlackTreeNode<basetype> *maximum(RedBlackTreeNode<basetype> *node)
    {}
    RedBlackTreeNode<basetype> *successor(RedBlackTreeNode<basetype> *node)
    {}
    RedBlackTreeNode<basetype> *insert(basetype key)
    {}
    RedBlackTreeNode<basetype> *insert(RedBlackTreeNode<basetype> *node)
    {}
    void insert_fixup(RedBlackTreeNode<basetype> *node)
    {}
    void left_rotation(RedBlackTreeNode<basetype> *node)
    {}
    void right_rotation(RedBlackTreeNode<basetype> *node)
    {}




};

}
#endif // RED_BLACK_TREE_H
