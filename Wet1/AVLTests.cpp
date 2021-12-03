
#include <iostream>
#include "AVLTree.h"

void insertionTests();
void removalTests();
void toArrayTests();
void fillTreeTests();

using std::log2f;
using std::ceil;
int main()
{
    insertionTests();
    removalTests();
    toArrayTests();
    fillTreeTests();
    return 0;
}

void fillTreeTests()
{
    std::cout<<"******fillTreeTests*******"<<std::endl<<std::endl;
    AVLTree<int> tree(4);
    int arr[4] = {1,4,16,64};
    tree.fillAlmostCompleteBTree(arr);
    std::cout<<tree <<std::endl;

    AVLTree<int> tree2(1);
    int arr2[1] = {24};
    tree2.fillAlmostCompleteBTree(arr2);
    std::cout<<tree2<<std::endl;
}
void toArrayTests()
{
    std::cout<<"******toArrayTests*******"<<std::endl<<std::endl;
    
    AVLTree<int> tree;
    tree.insert(1);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(24);
    tree.insert(24);
    std::cout<< tree;
    int *arr = new int[tree.getSize()];
    tree.toArray(arr);
    for(int i = 0; i<tree.getSize(); i++)
    {
        std::cout<<arr[i]<<",";
    }
    std::cout<<std::endl;

    delete[] arr;
}
void insertionTests()
{
    std::cout<<"******insertionTests*******"<<std::endl<<std::endl;

    //tree 1
    AVLTree<int> tree1;
    tree1.insert(20);
    tree1.insert(4);
    std::cout<< "tree 1  : " << tree1 << std::endl;

    //tree 2
    AVLTree<int> tree2;
    tree2.insert(20);
    tree2.insert(4);
    tree2.insert(26);
    tree2.insert(3);
    tree2.insert(9);
    std::cout<< "tree 2  : " << tree2 << std::endl;


    //tree 3
    AVLTree<int> tree3;
    tree3.insert(20);
    tree3.insert(4);
    tree3.insert(26);
    tree3.insert(3);
    tree3.insert(9);
    tree3.insert(21);
    tree3.insert(30);
    tree3.insert(2);
    tree3.insert(7);
    tree3.insert(11);
    std::cout<< "tree 3  : " << tree3 << std::endl;


    // //inserting 15
    // //case 1a
    // tree1.insert(15);
    // std::cout<< "insert 15 - 1a  : " << tree1 << std::endl;
    //  //case 2a
    // tree2.insert(15);
    // std::cout<< "insert 15 - 2a  : " << tree2 << std::endl;
    //  //case 3a
    // tree3.insert(15);
    // std::cout<< "insert 15 - 3a  : " << tree3 << std::endl;

    //inserting 8
    //case 1b
    tree1.insert(8);
    std::cout<< "insert 8 - 1b  : " << tree1 << std::endl;
     //case 2b
    tree2.insert(8);
    std::cout<< "insert 8 - 2b  : " << tree2 << std::endl;
     //case 3b
    tree3.insert(8);
    std::cout<< "insert 8 - 3b  : " << tree3 << std::endl;

}
void removalTests()
{
    std::cout<<"******removalTests*******"<<std::endl<<std::endl;
    //removal tests - AVL removal
    AVLTree<int> tree2;
    tree2.insert(2);
    tree2.insert(1);
    tree2.insert(4);
    tree2.insert(3);
    tree2.insert(5);

    std::cout<< "tree 2  : " << tree2 << std::endl;
    tree2.remove(1);
    std::cout<<"case 1 :"<< tree2<<std::endl;

    AVLTree<int> tree3;
    tree3.insert(6);
    tree3.insert(2);
    tree3.insert(9);
    tree3.insert(1);
    tree3.insert(8);
    tree3.insert(4);
    tree3.insert(3);
    tree3.insert(5);
    tree3.insert(12);
    tree3.insert(7);
    tree3.insert(11);
    tree3.insert(10);
    tree3.insert(13);

    std::cout<< "tree 3  : " << tree3 << std::endl;
    tree3.remove(1);
    std::cout<<"case 2:"<< tree3<<std::endl;

    AVLTree<int> tree4;
    tree4.insert(5);
    tree4.insert(2);
    tree4.insert(8);
    tree4.insert(1);
    tree4.insert(7);
    tree4.insert(3);
    tree4.insert(10);
    tree4.insert(6);
    tree4.insert(4);
    tree4.insert(9);
    tree4.insert(11);
    tree4.insert(12);
    std::cout<< "tree 4  : " << tree4 << std::endl;
    tree4.remove(1);
    std::cout<<"case 3:"<< tree4<<std::endl;

}