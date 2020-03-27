#include <iostream>
#include "binaryTree.h"

using namespace std;

BinaryTreeNode* CreateBinaryTreeNode(int value)
{
    BinaryTreeNode* pNode = new BinaryTreeNode();
    pNode->m_nValue = value;
    pNode->m_pLeft = NULL;
    pNode->m_pRight = NULL;

    return pNode;
}

void ConnectTreeNodes(BinaryTreeNode* pParent, BinaryTreeNode* pLeft, BinaryTreeNode* pRight)
{
    if(pParent != NULL)
    {
        pParent->m_pLeft = pLeft;
        pParent->m_pRight = pRight;
    }
}

void PrintTreeNode(BinaryTreeNode* pNode)
{
    if(pNode != NULL)
    {
        cout << "value of this node is: " << pNode->m_nValue << endl;

        if(pNode->m_pLeft != NULL)
            cout << "value of its left child is: "<< pNode->m_pLeft->m_nValue << endl;
        else
            cout << "left child is null.\n";

        if(pNode->m_pRight != NULL)
            cout << "value of its right child is: " << pNode->m_pRight->m_nValue << endl;
        else
            cout << "right child is null.\n";
    }
    else
    {
        cout << "this node is null.\n";
    }

    cout << endl;
}

void PrintTree(BinaryTreeNode* pRoot)
{
    PrintTreeNode(pRoot);

    if(pRoot != NULL)
    {
        if(pRoot->m_pLeft != NULL)
            PrintTree(pRoot->m_pLeft);

        if(pRoot->m_pRight != NULL)
            PrintTree(pRoot->m_pRight);
    }
}

void DestroyTree(BinaryTreeNode* pRoot)
{
    if(pRoot != NULL)
    {
        BinaryTreeNode* pLeft = pRoot->m_pLeft;
        BinaryTreeNode* pRight = pRoot->m_pRight;

        delete pRoot;
        pRoot = NULL;

        DestroyTree(pLeft);
        DestroyTree(pRight);
    }
}
