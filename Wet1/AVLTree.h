#ifndef AVLTREE_H
#define AVLTREE_H
#include <memory>
#include <math.h>

using std::shared_ptr;
using std::max;
using std::ceil;
using std::log2f;
using std::pow;
//to do:
//minmax update method
//remove leaves from complete


template <class T>
class AVLTree
{
    template <class S>
    class Node
    {  
        Node<S>* left;
        Node<S>* right;
        Node<S>* parent;
        shared_ptr<S> data;
        int h;
        int balance;
        void setParent(Node<S> *parent)
        {
            this->parent = parent;
        }
        void setSon(Node<S> *son)
        {
            *(son->data) < *(data) ?  left=son : right = son;
        }
        bool isBalanced()
        {
            return std::abs(balance) < 2;
        }

        bool isLeaf()
        {
            return (!right && !left);
        }
        Node(): left(nullptr), right(nullptr), parent(nullptr), data(new T),h(0),balance(0){}
        Node(const S& data): left(nullptr), right(nullptr), parent(nullptr), data(new T(data)),h(0),balance(0){}
        friend class AVLTree<T>;
    };

    //Tree fields
    Node<T>* root;
    Node<T>* max;
    Node<T>* min;
    int size;
    
    //private funcs to help maintenance the tree

    //balancing helpers
    void rotateLL(Node<T>* bad_node);
    void rotateRR(Node<T>* bad_node);
    void rotateLR(Node<T>* bad_node);
    void rotateRL(Node<T>* bad_node);
    void updateTree(Node<T> *new_node);
    void balanceTree(Node<T> *bad_node);
    void updateHeightBalance(Node<T> *changed_node);
    
   


    //manage helpers
    AVLTree<T>::Node<T>* scan(const T& data, bool to_add);
    int getNodeHeight(Node<T> *node);
    void printInOrder(Node<T>* subtree,std::ostream & os);
    void deletePostOrder(Node<T> *node);
    void updateMinMax(Node<T> *new_node);

    //removal helpers
    void removeLeaf(Node<T> *to_remove, Node<T> *parent);
    void removeSingleSon(Node<T> *to_remove,Node<T> *son);
    void binaryRemoval(Node<T> *to_remove);
    Node<T>* createCompleteBTree(int h);
    void removeLeaves(Node<T> *subtree, int * n);
    void fillArrayInOrder(Node<T>* subtree,T* arr, int *i);
    void fillDataInOrder(Node<T> *subtree,T* arr, int* i);
    public:
    AVLTree(int size=0) : root(nullptr),max(nullptr),min(nullptr),size(size)
    {
        if(size>0)
        {
            int h = int(ceil(log2f(size)));
            root = createCompleteBTree(h);
            int n = int(pow(2,h+1))-1-size;
            removeLeaves(root,&n);
        }
    }
    ~AVLTree();
    AVLTree(const AVLTree& tree) = delete;
    AVLTree& operator=(const AVLTree& tree) = delete;
    void insert(const T& data);
    void remove(const T& data);
    bool isEmpty();
    bool search(const T& data);
    void fillAlmostCompleteBTree(T* sorted_array);
    void toArray(T*array);
    int getSize() const;
    template<class U>
    friend std::ostream& operator<<(std::ostream &os, AVLTree<U> & tree);

};

template<class T>
void AVLTree<T>::removeLeaves(Node<T> *subtree,int *n)
{
    if(subtree->isLeaf()&& *n>0)
    {
        if(subtree->parent->right == subtree)
        {
            subtree->parent->right = nullptr;
        }
        else
        {
            subtree->parent->left = nullptr;
        }
        delete subtree;
        *(n)-=1;
        return;
    }
    if(*n==0)
    {
        return;
    }
    removeLeaves(subtree->right,n);
    removeLeaves(subtree->left,n);
    updateHeightBalance(subtree);
}
template<class T>
void AVLTree<T>::fillAlmostCompleteBTree(T* sorted_array)
{
    int i = 0;
    fillDataInOrder(root,sorted_array,&i);
}

template <class T>
void AVLTree<T>::fillDataInOrder(Node<T> *subtree,T* arr, int* i)
{
    if(subtree == nullptr)
        {
            return;
        }
        fillDataInOrder(subtree->left,arr,i);
        *(subtree->data) = arr[*i];
        *(i) += 1;
        fillDataInOrder(subtree->right,arr,i);
}
template <class T>
AVLTree<T>::Node<T>* AVLTree<T>::createCompleteBTree(int h)
{
    if(h==0)
    {
        return new Node<T>;
    }
    Node<T>* subtree = new Node<T>;
    subtree->left = createCompleteBTree(h-1);
    subtree->left->setParent(subtree);
    subtree->right = createCompleteBTree(h-1);
    subtree->right->setParent(subtree);
    subtree->h = h;
    return subtree;
}
template <class T>
int AVLTree<T>::getSize() const
{
    return size;
}
template <class T>
void AVLTree<T>::fillArrayInOrder(Node<T> *subtree,T* arr, int* i)
{
    if(subtree == nullptr)
    {
        return;
    }
    fillArrayInOrder(subtree->left,arr,i);
    arr[*i] = *(subtree->data);
    *(i) += 1;
    fillArrayInOrder(subtree->right,arr,i);
}
template <class T>
void AVLTree<T>::toArray(T* array)
{
    int i = 0;
    fillArrayInOrder(this->root,array,&i);
}


template<class T>
AVLTree<T>::~AVLTree()
{
    deletePostOrder(this->root);
}

template<class T>
void AVLTree<T>::deletePostOrder(Node<T> *node)
{
       if(node==nullptr)
       {
           return;
       }
       deletePostOrder(node->left);
       deletePostOrder(node->right);
       delete node;
}

template <class T>
bool AVLTree<T>::isEmpty()
{
    return !(root);
}

//rotations
template<class T>
void  AVLTree<T>::rotateLL(Node<T>* bad_node)
{
    Node<T> *temp = bad_node->left;
    bad_node->left=temp->right;
    if(temp->right)
    {
        temp->right->setParent(bad_node);
    }
     temp->setParent(bad_node->parent);
    if(bad_node->parent)
    {
        bad_node->parent->setSon(temp);
    }
    temp->right=bad_node;
    bad_node->setParent(temp);

    updateHeightBalance(temp->left);
    updateHeightBalance(temp->right);
    updateHeightBalance(temp);
}
template<class T>
void  AVLTree<T>::rotateRR(Node<T>* bad_node)
{
    Node<T> *temp = bad_node->right;
    bad_node->right=temp->left;
    if(temp->left)
    {
        temp->left->setParent(bad_node);
    }
    temp->setParent(bad_node->parent);
    if(bad_node->parent)
    {
        bad_node->parent->setSon(temp);
    }
    temp->left = bad_node;
    bad_node->setParent(temp);
    
    

    updateHeightBalance(temp->left);
    updateHeightBalance(temp->right);
    updateHeightBalance(temp);
}
template<class T>
void AVLTree<T>::rotateLR(Node<T>* bad_node)
{
    Node<T> *temp = bad_node->left->right;
    temp->setParent(bad_node->parent);
    if(bad_node->parent)
    {
        bad_node->parent->setSon(temp);
    }
    bad_node->left->right=temp->left;
    if(temp->left)
    {
        temp->left->setParent(bad_node->left);
    }
    temp->left=bad_node->left;
    bad_node->left->setParent(temp);
    
    bad_node->left = (temp->right);
    if(temp->right)
    {
        temp->right->setParent(bad_node->left);
    }
    temp->right = bad_node;
    bad_node->setParent(temp);

    updateHeightBalance(temp->right);
    updateHeightBalance(temp->left);
    updateHeightBalance(temp);
}
template<class T>
void AVLTree<T>::rotateRL(Node<T>* bad_node)
{
    Node<T> *temp = bad_node->right->left;
    temp->setParent(bad_node->parent);
    if(bad_node->parent)
    {
        bad_node->parent->setSon(temp);
    }
    bad_node->right->left =  temp->right;
    if(temp->right)
    {
        temp->right->setParent(bad_node->right);
    }    
    temp->right= bad_node->right;
    bad_node->right->setParent(temp);
    
    bad_node->right = temp->left;
    if(temp->left)
    {
        temp->left->setParent(bad_node->right);
    }
    temp->left = bad_node;
    bad_node->setParent(temp);

    updateHeightBalance(temp->right);
    updateHeightBalance(temp->left);
    updateHeightBalance(temp);
}


template <class T>
int AVLTree<T>::getNodeHeight(Node<T> *node)
{
    return (node==nullptr) ? -1:node->h;
}

template <class T>
void AVLTree<T>::updateHeightBalance(Node<T> *node)
{
    if(node == nullptr)
    {
        return;
    }
    int left_h = getNodeHeight(node->left);
    int right_h = getNodeHeight(node->right);
    node->h = std::max(left_h,right_h) + 1;
    node->balance = left_h-right_h;
}
template <class T>
void AVLTree<T>::balanceTree(Node<T> *bad_node)
{
    if(bad_node->balance>0)
    {
        if(bad_node->left->balance>=0)
        {
            rotateLL(bad_node);
            return;
        }
        rotateLR(bad_node);
        return;
    }
    if(bad_node->right->balance<=0)
    {
        rotateRR(bad_node);
        return;
    }
    rotateRL(bad_node);
    return;
}

template <class T>
void AVLTree<T>::updateTree(Node<T> *node)
{
    while(node != nullptr)
    {
        updateHeightBalance(node);
        if(!node->isBalanced())
        {
            balanceTree(node);
            if(node==root)
            {
                root=node->parent;
            }
        }
        node = node->parent;

    }
}
//scan the tree to find a data. 
//if @param to_add is true returns the parent of the place where the data should be added.
//else returns the node to that holds the data or nullptr if the data is not in the tree.
template<class T>
AVLTree<T>::Node<T>* AVLTree<T>::scan(const T& data, bool to_add)
{
    Node<T>* target_parent = nullptr;
    Node<T>* target = root; 
    while(target != nullptr && (to_add || !(data==*(target->data))))
    {
        target_parent = target;
        target=(data < *(target->data)) ? target->left:target->right;
    }

    return to_add ? target_parent:target;
}

//returns true if data is in the tree. false otherwise
template <class T>
bool AVLTree<T>::search(const T& data)
{
    return scan(data,false)!=nullptr;
}

template <class T>
void AVLTree<T>::insert(const T& data)
{
    if(this->isEmpty())
    {
        root = new Node<T>(data);
        this->size++;
        return;
    }
    Node<T> *to_add = new Node<T>(data);
    Node<T>* new_parent = scan(data,true);
    new_parent->setSon(to_add);
    to_add->setParent(new_parent);
    updateTree(new_parent);
    this->size++;
    //updateMinMax(to_add);
}
template<class T>
void AVLTree<T>::removeLeaf(Node<T> *to_remove, Node<T> *parent)
{
       if(parent && parent->right == to_remove)
        {
            parent->right = nullptr;
        }
        else if(parent)
        {
            to_remove->parent->left = nullptr;
        }
        delete to_remove;
        return;
}
template <class T>
void AVLTree<T>::removeSingleSon(Node<T> *to_remove,Node<T> *son)
{

    son->setParent(to_remove->parent);
    if(to_remove->parent)
    {
        to_remove->parent->setSon(son);
    }
    delete to_remove;
}
template <class T>
void AVLTree<T>::binaryRemoval(Node<T> *to_remove)
{
    if(to_remove->left && to_remove->right)
    {
        Node<T> *next = to_remove->right;
        while(next->left!=nullptr)
        {
            next = next->left;
        }
        shared_ptr<T> temp = next->data;
        next->data = to_remove->data;
        to_remove->data = temp;
        to_remove = next;
    }
    if(to_remove->isLeaf())
    {
       removeLeaf(to_remove,to_remove->parent);
       return;
    }
    Node<T>* son = to_remove->left==nullptr ? to_remove->right:to_remove->left; 
    removeSingleSon(to_remove, son);
 
}

template <class T>
void AVLTree<T>::remove(const T& data)
{
    Node<T> *to_remove = scan(data,false);
    if(to_remove==nullptr)
    {return;}
    Node<T> *removed_parent = to_remove->parent;
    binaryRemoval(to_remove);
    updateTree(removed_parent);
    this->size--;
}
template<class T>
void AVLTree<T>::printInOrder(AVLTree<T>::Node<T>* subtree,std::ostream & os)
{
    if(subtree==nullptr)
    {
        return;
    }
    printInOrder(subtree->left,os);
    if(subtree==root)
    {
        os <<"h:" << subtree->h<<",b:" << subtree->balance<< "{>"<< *(subtree->data) << "<} ";
    }
    else
    {
        os << "h:" << subtree->h<<",b:" << subtree->balance<<"{"<< *(subtree->data) << "} ";

    }
    printInOrder(subtree->right,os);

}
template<class T>
std::ostream& operator<<(std::ostream& os,AVLTree<T>& tree)
{
    tree.printInOrder(tree.root,os);
    return os;
}

#endif