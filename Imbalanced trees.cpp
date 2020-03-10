#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
#define FILENAME "input.txt"
#define N_NODES  10

// A tree node
struct Node
{
    Node *parent;
    int val;      // The (integer) value
    int bf;       // Balance factor of this node
    Node *left;   // Left child pointer
    Node *right;  // Right child pointer
};

int findImbalance (Node*key, Node *&rootp)
{
    if (key==rootp)
        return 0;
    else if (key == key->parent->left)
        key->parent->bf--;
    else if (key == key->parent->right)
        key->parent->bf++;


    if (key->parent->bf > 1){
        cout << "Imbalance at " << key->parent->val << ", left subtree." << endl;
        return -1;
    }
    if (key->parent->bf < -1){
        cout << "Imbalance at " << key->parent->val << ", right subtree." << endl;
        return -1;
    }

    return findImbalance(key->parent, rootp);
}

// Insert a node into the tree, balancing if needed.
// *tp is a pointer to the root of the tree (reference variable);
// 'nv' is the new (integer) value to add.
// 'allNodes' is an array of all of the nodes we've allocated, for easy
//clean-up
// 'allNodesN' is the number of nodes set in allNodes

int insertNode(Node *&tp, int nv, Node *allNodes[], int allNodesN)
{
    Node *newp;
    newp = new Node;
    if (tp == 0)
    {
        // Setup our new node

        newp->val = nv;
        newp->bf = 0;
        newp->left = 0;
        newp->right = 0;
        tp = newp;
        allNodes[allNodesN] = newp;
        return (1);
    }

    // Ignore existing values
    if (nv == tp->val)
        return (0);
    if (nv < tp->val)
    {
        // Insert into the LEFT subtree
        newp = tp;
        while(true)
        {
            if (nv < newp->val && newp->left != 0)
                newp = newp -> left;
            else if (nv < newp->val && newp->left == 0)
            {
                //newp = newp -> left;
                break;
            }
            if (nv > newp->val && newp->right !=0)
                newp= newp->right;
            else if (nv > newp->val && newp->right == 0)
            {
                //newp = newp -> right;
                break;
            }
        }
    }
    else
    {
        // Insert into the RIGHT subtree
        newp = tp;
        while(true)
        {
            if (nv < newp->val && newp->left != 0)
                newp = newp -> left;
            else if (nv < newp->val && newp->left == 0)
            {
                //newp = newp -> left;
                break;
            }
            if (nv > newp->val && newp->right !=0)
                newp= newp->right;
            else if (nv > newp->val && newp->right == 0)
            {
                //newp = newp -> right;
                break;
            }
        }
        //newp = temp;
    }
    Node *temp = new Node;
    temp->val = nv;
    temp->bf = 0;
    temp->left = 0;
    temp->right = 0;
    temp->parent = newp;
    allNodes[allNodesN] = newp;
    //cout << temp -> parent -> val << endl;
    if (temp->val > newp->val)
    {
        newp->right = temp;
        return findImbalance(newp->right, tp);
    }
    if(temp->val < newp->val)
    {
        newp->left = temp;
        return findImbalance(newp->left, tp);
    }
    //cout << newp->left->parent->val << endl;
    //cout << newp->right->parent->val << endl;

return 0;

}

int main()
{
    Node *rootp = 0;           // Root of the tree
    Node *allNodes[N_NODES];   // Bookkeeping array so we can free
                            // everything
    string ent;                // Input string from file
    ifstream infile(FILENAME); // Input file
    int nums[N_NODES];         // Input integers
    int i, j, status;
    while (true)
    {
        // Read a set of insertions
        i = 0, j = 0;
        rootp = 0;
        while (getline(infile, ent))
        {
            nums[i++] = atoi(ent.c_str());
            if (i == N_NODES)
                break;
        }
        if (i != N_NODES)
            break;
        cout << "Read " << i << " nodes." << endl;
        for (; j < N_NODES; j++)
        {
            status = insertNode(rootp, nums[j], allNodes, j);
            if (status == -1)
                break;
        }
        if (j == N_NODES)
        {
            cout << "No imbalances detected." << endl;
        }

        // Free everything
        for (int k = 0; k < j; k++)
        {
            delete allNodes[k];
            allNodes[k] = 0;
        }
    }
    cout << "Done." << endl;
    return (0);
}

