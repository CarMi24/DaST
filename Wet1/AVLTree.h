#ifndef GENERIC_RANK_TREE
#define GENERIC_RANK_TREE
#include <memory>
using std::shared_ptr;

template <class T>
class genericRankTree
{
    template <class T,class Rank = int>
    class Node
    {
        public:
        Node<T>* left;
        Node<T>* right;
        Node<T>* parent;
        shared_ptr<T> data;

    };

    Node<T>* root;
    int size;
    Node<T>* max;
    Node<T>* min;
    void rotateLL();
    void rotateRR();
    void rotateLR();
    void rotateRL();

    public:
    AVLTree(int size=0);
    ~genericRankTree()=default;
    genericRankTree(const genericRankTree& tree) = delete;
    genericRankTree& operator=(const genericRankTree& tree) = delete;
    void insert(const T& data);
    void remove(const T& data);
    

    
};

#endif