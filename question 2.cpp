#include <iostream>
using namespace std;

class AVLTree
{
    struct Node
    {
        int key;
        int height;
        Node *left;
        Node *right;
    };

    Node *root;

    int height(Node *n)
    {
        if(n == NULL)
            return 0;

        return n->height;
    }

    int balance(Node *n)
    {
        if(n == NULL)
            return 0;

        return height(n->left) - height(n->right);
    }

    Node* createNode(int value)
    {
        Node *n = new Node;
        n->key = value;
        n->height = 1;
        n->left = NULL;
        n->right = NULL;
        return n;
    }

    Node* rightRotate(Node *y)
    {
        Node *x = y->left;
        Node *t2 = x->right;

        x->right = y;
        y->left = t2;

        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));

        return x;
    }

    Node* leftRotate(Node *x)
    {
        Node *y = x->right;
        Node *t2 = y->left;

        y->left = x;
        x->right = t2;

        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));

        return y;
    }

    Node* insertNode(Node *n, int value)
    {
        if(n == NULL)
            return createNode(value);

        if(value < n->key)
            n->left = insertNode(n->left, value);
        else if(value > n->key)
            n->right = insertNode(n->right, value);
        else
            return n;

        n->height = 1 + max(height(n->left), height(n->right));

        int b = balance(n);

        if(b > 1 && value < n->left->key)
            return rightRotate(n);

        if(b < -1 && value > n->right->key)
            return leftRotate(n);

        if(b > 1 && value > n->left->key)
        {
            n->left = leftRotate(n->left);
            return rightRotate(n);
        }

        if(b < -1 && value < n->right->key)
        {
            n->right = rightRotate(n->right);
            return leftRotate(n);
        }

        return n;
    }

    void displayTree(Node *n)
    {
        if(n == NULL)
            return;

        cout << n->key << " ";
        displayTree(n->left);
        displayTree(n->right);
    }

public:
    AVLTree()
    {
        root = NULL;
    }

    void insert(int value)
    {
        root = insertNode(root, value);
    }

    void rotateRootLeft()
    {
        if(root != NULL && root->right != NULL)
            root = leftRotate(root);
    }

    void display()
    {
        displayTree(root);
    }
};

int main()
{
    AVLTree tree;

    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    tree.insert(55);

    tree.rotateRootLeft();

    tree.display();

    return 0;
}
