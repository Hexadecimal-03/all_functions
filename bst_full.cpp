#include <iostream>
using namespace std;

int sum = 0;

class node
{
    public:
    int value;
    node* left;
    node* right;

    node (int d)
    {
        value = d;
        left = NULL;
        right = NULL;
    }
};

node* insertinbst (node* root, int data)
{
    if (root == NULL)
    {
        return new node (data);
    }

    if (data <= root->value)
    {
        root->left = insertinbst (root->left, data);
    }
    else
    {
        root->right = insertinbst (root->right, data);
    }

    return root;
}

node* buildbst()
{
    int n, data;
    node* root = NULL;
    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        cin >> data;
        root = insertinbst (root, data);
    }

    return root;
}

node* searchbst (node* root, int data)  //Returns the pointer to the node if present and returns the NULL if the node is not present
{
    if (root->value == data)
    {
        return root;
    }

    if (root == NULL)
    {
        return NULL;
    }

    if (data <= root->value)
    {
        return searchbst (root->left, data);
    }
    else
    {
        return searchbst (root->right, data);
    }
}

node* deletebst (node* root, int data)      //deleting a node in bst but keeping the bst property
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (data < root->value)
    {
        root->left = deletebst (root->left, data);
        return root;
    }
    else if (data == root->value)
    {
        if (root->left == NULL and root->right == NULL)
        {
            delete root;
            return NULL;
        }
        if (root->left != NULL and root->right == NULL)
        {
            node* temp;
            temp = root->left;
            delete root;
            return temp;
        }
        if (root->left == NULL and root->right != NULL)
        {
            node* temp;
            temp = root->right;
            delete root;
            return temp;
        }

        node* replace = root->right;

        while (replace->left != NULL)
        {
            replace = replace->left;
        }

        root->value = replace->value;
        root->right = deletebst (root->right, replace->value);
        return root;
    }
    else
    {
        root->right = deletebst (root->right, data);
        return root;
    }
}

void replacegrsum (node* &root)     //replaces all smaller nodes with sum of all greater nodes
{
    if (root == NULL)
    {
        return;
    }

    replacegrsum (root->right);
    root->value = root->value + sum;    //Need to make a global sum variable and initialize it to 0
    sum = root->value;
    replacegrsum (root->left);
}

int main()
{

    return 0;
}