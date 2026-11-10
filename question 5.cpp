#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;
};

Node* createNode(int value)
{
    Node *n = new Node;
    n->data = value;
    n->left = NULL;
    n->right = NULL;
    return n;
}

Node* insert(Node *root, int value)
{
    if(root == NULL)
        return createNode(value);

    if(value < root->data)
        root->left = insert(root->left, value);
    else
        root->right = insert(root->right, value);

    return root;
}

int height(Node *root)
{
    if(root == NULL)
        return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    if(leftHeight > rightHeight)
        return leftHeight + 1;

    return rightHeight + 1;
}

void inorder(Node *root, int arr[], int &i)
{
    if(root == NULL)
        return;

    inorder(root->left, arr, i);
    arr[i++] = root->data;
    inorder(root->right, arr, i);
}

Node* buildBalanced(int arr[], int start, int end)
{
    if(start > end)
        return NULL;

    int mid = (start + end) / 2;

    Node *root = createNode(arr[mid]);

    root->left = buildBalanced(arr, start, mid - 1);
    root->right = buildBalanced(arr, mid + 1, end);

    return root;
}

bool isBalanced(Node *root)
{
    if(root == NULL)
        return true;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    if(leftHeight - rightHeight > 1 || rightHeight - leftHeight > 1)
        return false;

    return isBalanced(root->left) && isBalanced(root->right);
}

void display(Node *root)
{
    if(root == NULL)
        return;

    cout << root->data << " ";
    display(root->left);
    display(root->right);
}

int countNodes(Node *root)
{
    if(root == NULL)
        return 0;

    return 1 + countNodes(root->left) + countNodes(root->right);
}

int main()
{
    Node *root = NULL;
    int n, value;

    cout << "Enter number of nodes: ";
    cin >> n;

    for(int i = 0; i < n; i++)
    {
        cin >> value;
        root = insert(root, value);
    }

    if(isBalanced(root))
        cout << "Tree is already balanced" << endl;
    else
        cout << "Tree is unbalanced" << endl;

    int arr[1000];
    int i = 0;

    inorder(root, arr, i);

    root = buildBalanced(arr, 0, i - 1);

    cout << "Balanced BST: ";
    display(root);

    return 0;
}
