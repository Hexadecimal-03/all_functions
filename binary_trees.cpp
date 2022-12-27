#include <iostream>
#include <math.h>
#include <queue>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

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

node* buildtree()   //Build the binary tree (prebuild)
{
    int d;
    cin >> d;

    if (d == -1)
    {
        return NULL;
    }

    node* root = new node(d);
    root->left = buildtree();
    root->right = buildtree();

    return root;
}

node* gentree ()    //Using ints and bool values
{
    string s;
    cin >> s;
    
    if (s == "false")
    {
        return NULL;
    }
    else if (s == "true")
    {
        cin >> s;
    }

    node* root = new node(stoi(s));
    root->left = gentree();
    root->right = gentree();
    return root;
}


void preprint (node* root)  //Preprint the binary tree
{
    if (root == NULL)
    {
        return;
    }

    cout << root->value << " ";
    preprint (root->left);
    preprint (root->right);
    return;
}

void postprint (node* root)     //Postprint the binary tree
{
    if (root == NULL)
    {
        return;
    }

    postprint (root->left);
    postprint (root->right);
    cout << root->value << " ";
    return;
}

void inprint (node* root)       //Inprint the binary tree
{
    if (root == NULL)
    {
        return;
    }

    inprint (root->left);
    cout << root->value << " ";
    inprint (root->right);
    return;
}

int height (node* root)     //Returns the height of the Tree
{
    if (root == NULL)
    {
        return 0;
    }

    int ls = height (root->left);
    int rs = height (root->right);

    return max(ls, rs) + 1;
}

void printkthlevel (node* root, int k)     //Prints kth level of the tree
{
    if (root == NULL)
    {
        return;
    }

    if (k == 1)
    {
        cout << root->value << " ";
        return;
    }

    printkthlevel (root->left, k-1);
    printkthlevel (root->right, k-1);
    return;
}

void printalllevels (node* root)    //Print the tree levelwise but n^2 complexity
{
    int h = height (root);
    int i;

    for (i = 1; i <= h; ++i)
    {
        printkthlevel (root, i);
        cout << endl;
    }

    return;
}

void bfs (node* root)   //Breadth First Search for level wise tree in O(n)
{
    queue<node*> q;
    q.push(root);

    while (!q.empty())
    {
        node* f = q.front();
        cout << f->value << " ";
        q.pop();

        if (f->left)
        {
            q.push(f->left);
        }

        if (f->right)
        {
            q.push(f->right);
        }
    }
}

class hbpair       //pair to store height and bool of balance
{
    public:
    int height;
    bool balance;
};

hbpair isbalanced (node* root)  //A balanced tree has difference in height of left and right node less than 2 recursively
{
    hbpair p;

    if (root == NULL)
    {
        p.height = 0;
        p.balance = true;
        return p;
    }

    hbpair left = isbalanced (root->left);
    hbpair right = isbalanced (root->right);

    p.height = max(left.height, right.height) + 1;

    if ((abs(left.height - right.height) <= 1) && left.balance && right.balance)
    {
        p.balance = true;
    }
    else
    {
        p.balance = false;
    }

    return p;
}

node* levelbuild()      //To build the tree levelwise
{
    int d;
    cin >> d;
    node* root = new node(d);
    queue<node*> q;
    q.push(root);

    while (!q.empty())
    {
        node* f = q.front();
        q.pop();

        int c1, c2;
        cin >> c1 >> c2;

        if (c1 != -1)
        {
            f->left = new node(c1);
            q.push(f->left);
        }

        if (c2 != -1)
        {
            f->right = new node(c2);
            q.push(f->right);
        }
    }

    return root;
}

void printleafnodes (node* root)    //Print all leaf nodes
{
    if (root == NULL)
    {
        return;
    }

    if (root->left == NULL && root->right == NULL)
    {
        cout << root->value << " ";
        return;
    }

    printleafnodes (root->left);
    printleafnodes (root->right);
    return;
}

void printnosibs (node* root)   //Prints the nodes which don't have siblings
{
    if (root == NULL)
    {
        return;
    }

    if (root->left != NULL && root->right == NULL)
    {
        cout << root->left->value << " ";
    }
    else if (root->left == NULL && root->right != NULL)
    {
        cout << root->right->value << " ";
    }

    printnosibs (root->left);
    printnosibs (root->right);

    return;
}

void rootwiseprint (node* root)     //print root wise "root->left => root <= root->right" Null as end and preprint
{
    if (root == NULL)
    {
        return;
    }

    if (root->left == NULL)
    {
        cout << "END";
    }
    else
    {
        cout << root->left->value;
    }

    cout << " => " << root->value << " <= ";

    if (root->right == NULL)
    {
        cout << "END";
    }
    else
    {
        cout << root->right->value;
    }
    cout << endl;

    rootwiseprint(root->left);
    rootwiseprint(root->right);

    return;
}

node* removeleaves (node* root)     //Removes all the leaves from the tree
{
    if (root == NULL || (root->left == NULL && root->right == NULL))
    {
        return NULL;
    }
    root->left = removeleaves(root->left);
    root->right = removeleaves(root->right);

    return root;
}

int lca (node* root, int a1, int a2)       //returns the lowest common anscestor of the two distinct values of the nodes 
{
    if (root == NULL)
    {
        return -1;
    }

    if (root->value == a1 || root->value == a2)
    {
        return root->value;
    }

    int left = lca (root->left, a1, a2);
    int right = lca (root->right, a1, a2);  

    if (left != -1 && right != -1)
    {
        return root->value;
    }

    return (left != -1)? left: right;
}

vector <pair <int, int> > levelpair (node* root)       //Returns a vector with first as the value of the node and second as the level of the node, the vector is stored with ascending order of the level.
{
    int level, l;
    vector <pair <int, int> > vect;

    queue <pair <node*, int> > q;
    q.push(make_pair(root, 1));

    while (!q.empty())
    {
        node* f = q.front().first;
        level = q.front().second;
        vect.push_back (make_pair (f->value, level));
        q.pop();

        if (f->left)
        {
            l = level+1;
            q.push(make_pair (f->left, l));
        }

        if (f->right)
        {
            l = level+1;
            q.push(make_pair (f->right, l));
        }
    }

    return vect;
}

node* buildfromarray (int arr[], int s, int e)  //Builds the tree from an array as in-build type
{
    if (s > e)
    {
        return NULL;
    }

    int mid = (s+e)/2;
    node* root = new node (arr[mid]);
    root->left = buildfromarray (arr, s, mid-1);
    root->right = buildfromarray (arr, mid+1, e);

    return root;
}

int main()
{
    node* root;
    root = buildtree();
    printalllevels (root);
    return 0;
}