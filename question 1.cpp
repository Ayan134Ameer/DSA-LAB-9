#include <iostream>
using namespace std;

struct Node
{
    int key;
    int height;
    Node *left;
    Node *right;
};

int height(Node *root)
{
    if(root == NULL)
        return 0;

    return root->height;
}

int balance(Node *root)
{
    if(root == NULL)
        return 0;

    return height(root->left) - height(root->right);
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

Node* leftRotate(Node *root)
{
    Node *x = root->right;
    Node *t2 = x->left;

    x->left = root;
    root->right = t2;

    root->height = 1 + max(height(root->left), height(root->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
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

    int b = balance(root);

    if(b > 1 && value < root->left->key)
    {
        Node *x = root->left;
        Node *t2 = x->right;

        x->right = root;
        root->left = t2;

        root->height = 1 + max(height(root->left), height(root->right));
        x->height = 1 + max(height(x->left), height(x->right));

        return x;
    }

    if(b < -1 && value > root->right->key)
        return leftRotate(root);

    if(b > 1 && value > root->left->key)
    {
        root->left = leftRotate(root->left);
        Node *x = root->left;
        Node *t2 = x->right;

        x->right = root;
        root->left = t2;

        root->height = 1 + max(height(root->left), height(root->right));
        x->height = 1 + max(height(x->left), height(x->right));

        return x;
    }

    if(b < -1 && value < root->right->key)
    {
        Node *y = root->right;
        Node *t2 = y->left;

        y->left = root;
        root->right = t2;

        root->height = 1 + max(height(root->left), height(root->right));
        y->height = 1 + max(height(y->left), height(y->right));

        return y;
    }

    return root;
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
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 15);

    root = leftRotate(root);

    display(root);

    cout << endl;
    cout << "Height: " << height(root);

    return 0;
}
