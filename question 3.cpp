#include <iostream>
using namespace std;

struct Node
{
    int key;
    int height;
    Node *left;
    Node *right;
};

int height(Node *n)
{
    if(n == NULL)
        return 0;

    return n->height;
}

int getBalance(Node *n)
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

Node* insert(Node *root, int value)
{
    if(root == NULL)
        return createNode(value);

    if(value < root->key)
        root->left = insert(root->left, value);
    else if(value > root->key)
        root->right = insert(root->right, value);
    else
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int b = getBalance(root);

    if(b > 1 && value < root->left->key)
        return rightRotate(root);

    if(b < -1 && value > root->right->key)
        return leftRotate(root);

    if(b > 1 && value > root->left->key)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if(b < -1 && value < root->right->key)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void showBalance(Node *root)
{
    if(root == NULL)
        return;

    showBalance(root->left);

    cout << "Node " << root->key << " Balance Factor: " << getBalance(root) << endl;

    showBalance(root->right);
}

void display(Node *root)
{
    if(root == NULL)
        return;

    cout << root->key << " ";
    display(root->left);
    display(root->right);
}

int main()
{
    Node *root = NULL;

    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 3);
    root = insert(root, 7);

    root = insert(root, 12);

    showBalance(root);

    cout << "Height: " << height(root) << endl;

    cout << "Final AVL Tree: ";
    display(root);

    return 0;
}
