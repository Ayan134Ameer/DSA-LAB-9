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

void inorder(Node *root, int arr[], int &i)
{
    if(root == NULL)
        return;

    inorder(root->left, arr, i);
    arr[i++] = root->key;
    inorder(root->right, arr, i);
}

int kthSmallest(Node *root, int k)
{
    int arr[1000];
    int i = 0;

    inorder(root, arr, i);

    if(k < 1 || k > i)
        return -1;

    return arr[k - 1];
}

int kthLargest(Node *root, int k)
{
    int arr[1000];
    int i = 0;

    inorder(root, arr, i);

    if(k < 1 || k > i)
        return -1;

    return arr[i - k];
}

int main()
{
    Node *root = NULL;
    int n, value, k;

    cout << "Enter number of nodes: ";
    cin >> n;

    for(int i = 0; i < n; i++)
    {
        cin >> value;
        root = insert(root, value);
    }

    cout << "Enter k: ";
    cin >> k;

    cout << "Kth Smallest: " << kthSmallest(root, k) << endl;
    cout << "Kth Largest: " << kthLargest(root, k) << endl;

    cout << "Left Height: " << height(root->left) << endl;
    cout << "Right Height: " << height(root->right) << endl;

    return 0;
}
