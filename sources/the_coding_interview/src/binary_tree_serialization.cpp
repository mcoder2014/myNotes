// [0 1 2 3 4 5]
//  p l r
// 1,#,3，

#include <iostream>
#include <string>
#include <queue>

using namespace std;

class BinaryTree
{
public:
    BinaryTree* left;
    BinaryTree* right;
    int value;

    BinaryTree(int value = 0):left(nullptr), right(nullptr), value(value){}

};

bool endNode(deque<BinaryTree*>& layer)
{
    for(BinaryTree* node:layer)
    {
        if(node != nullptr) {
            return false;
        }
    }
    return true;
}

string serial(BinaryTree* root)
{
    vector<string> nodes;
    
    // 层次遍历数据结构
    deque<BinaryTree*> layer;

    BinaryTree * ptr = root;
    layer.push_back(ptr);
    
    // nil 作为每层结尾 nullptr 作为空节点占位符
    BinaryTree nil;
    layer.push_back(&nil);

    while(layer.size() != 0) 
    {
        ptr = layer.front();
        layer.pop_front();

        if(ptr == &nil)
        {
            // 换层，确定后续节点都为 nullptr
            if(endNode(layer))
            {
                // 如果没有后续的层，结束
                break;
            }
            layer.push_back(&nil);
        }
        else if (ptr == nullptr) 
        {
            // 空节点
            nodes.push_back("#");

            layer.push_back(nullptr);
            layer.push_back(nullptr);
        }
        else
        {
            // 正常节点
            nodes.push_back(to_string(ptr->value));

            layer.push_back(ptr->left);
            layer.push_back(ptr->right);
        }
    }

    // 整理字符串
    string retValue;
    for(string& str: nodes)
    {
        retValue = retValue + str + ',';
    }
    return retValue;
}

vector<string> split(string& tree)
{
    if(tree.size() == 0)
    {
        return vector<string>();
    }

    string tmp;
    vector<string> nodes;
    for(char ch:tree)
    {
        if(ch == ',')
        {
            // 分割符
            nodes.push_back(tmp);
            tmp.clear();
        }
        else
        {
            tmp.push_back(ch);
        }
        
    }
    return nodes;
}

BinaryTree *recover(string& tree)
{
    vector<string> nodes = split(tree);
    if(nodes.size() == 0)
    {
        return nullptr;
    }

    vector<BinaryTree*> realNodes(nodes.size(), nullptr);
    for(int i = 0; i < nodes.size(); i++)
    {
        if(nodes[i] == "#")
        {
            // 空节点
        }
        else
        {
            realNodes[i] = new BinaryTree(stoi(nodes[i]));
        }
    }
    for(int i = 0; i < nodes.size()/2; i++)
    {
        if(realNodes[i] != nullptr)
        {
            realNodes[i]->left = realNodes[2*(i + 1)-1];
            realNodes[i]->right = realNodes[2*(i+1)];
        }
    }

    return realNodes[0];

}

int main()
{

//   1
//   / \
//   2  3
//   /\ /\
//      4 5


    string test = "1,2,3,#,#,4,5,";

    BinaryTree * root = recover(test);

    string ser = serial(root);

    cout << "ser" << ser << endl;

    return 0;
}