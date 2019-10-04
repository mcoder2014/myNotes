#ifndef ROOTEDTREES_H
#define ROOTEDTREES_H

namespace Mcoder
{

template<typename basetype>
class Tree_node
{
    Tree_node<basetype> *parent;
    Tree_node<basetype> *lchild;
    Tree_node<basetype> *right_sibling;

    basetype data;
};

template<typename basetype>
class Tree
{
public:
    Tree()
    {}
    ~Tree()
    {}

};

}

#endif // ROOTEDTREES_H
