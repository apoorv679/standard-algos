// Test Input:
// 18
// 1 5
// 1 3
// 1 6
// 1 4
// 1 0
// 1 1
// 1 2
// 1 -1
// 1 0
// 1 4
// 1 -2
// 4 0
// 2 7
// 2 4
// 3 4
// 2 4
// 3 5
// 4 0

// Expected Output:
// 5 inserted!
// 3 inserted!
// 6 inserted!
// 4 inserted!
// 0 inserted!
// 1 inserted!
// 2 inserted!
// -1 inserted!
// 0 inserted!
// 4 inserted!
// -2 inserted!
// -2 -1 0 1 2 3 4 5 6
// 7 not found.
// 4 found!
// 4 deleted!
// 4 not found.
// 5 deleted!
// -2 -1 0 1 2 3 6

/*
    - BST offer O(log(n)) insert, search and delete opeartions
    and also maintain the data in a sorted order
    - Can work with a data stream
    - Balanced BST like AVL tree or Red-Black tree can avoid
    worst case of a skewed tree (sorted data stream - O(n) operations)
    - AVL trees have stricter balancing rules, hence have lesser average
    height, but they have more rotations in insertion/deletion operations
    Red-Black trees are better suited if there are more insertion/deletion
    whereas AVL trees are better when search, min, max, traversal etc are more
    frequent
    - If sorted order is not required, hashing is faster with
    expected time complexity of O(1)
*/

#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007
#define forn(n) for (int i = 0; i < n; i++)
#define printv(v)                      \
    for (auto i : v) cout << i << " "; \
    cout << "\n";

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    int height;

    TreeNode() : val(0), height(1), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), height(1), left(nullptr), right(nullptr) {}
};

int height(TreeNode* root) {
    if (root == nullptr) return 0;
    return root->height;
}

int getBalance(TreeNode* root) {
    if (root == nullptr) return 0;
    return height(root->left) - height(root->right);
}

TreeNode* leftRotate(TreeNode* z) {
    if (z == nullptr) return nullptr;

    /*
        Where z is the root

          z                    y
         / \                 /   \
        T1  y               z     x
           / \       ==>   / \   / \
          T2  x           T1 T2 T3 T4
             / \
            T3  T4
    */

    TreeNode* y = z->right;
    TreeNode* T2 = y->left;

    y->left = z;
    z->right = T2;

    z->height = 1 + max(height(z->left), height(z->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;  // new root
}

TreeNode* rightRotate(TreeNode* z) {
    if (z == nullptr) return nullptr;

    /*
        Where z is the root

              z                    y
             / \                 /   \
            y   T1              x     z
           / \         ==>     / \   / \
          x   T2              T3 T4 T2 T1
         / \
        T3  T4
    */

    TreeNode* y = z->left;
    TreeNode* T2 = y->right;

    y->right = z;
    z->left = T2;

    z->height = 1 + max(height(z->left), height(z->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;  // new root
}

TreeNode* balanceInsert(TreeNode* root, int val) {
    /*
        updating height & balancing each node using AVL rotations
    */
    root->height = 1 + max(height(root->left), height(root->right));
    int bal = getBalance(root);

    // left-left case: the value we are inserting and the
    // cause of the unbalance is lesser than the root->left,
    // which means it is in the left sub-tree of root->left
    if (bal > 1 && val < root->left->val) {
        return rightRotate(root);
    }

    // left-right case: first do a left rotation on the left sub-tree
    // this will convert it to a left-left case
    // then we can do a right rotation as normal
    if (bal > 1 && val > root->left->val) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // right-right case
    if (bal < -1 && val > root->right->val) {
        return leftRotate(root);
    }

    // right-left case
    if (bal < -1 && val < root->right->val) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

TreeNode* insert(TreeNode* root, int val) {
    if (root == nullptr) {
        return new TreeNode(val);
    }

    if (val == root->val) return root;  // not allowing duplicates

    if (val < root->val)
        // insert val in left sub-tree and
        // return the root of the modified tree
        root->left = insert(root->left, val);
    else
        // insert val in right sub-tree and
        // return the root of the modified tree
        root->right = insert(root->right, val);

    // return root; // without balancing
    return balanceInsert(root, val);
}

TreeNode* search(TreeNode* root, int x) {
    if (root == nullptr) return nullptr;

    if (x == root->val) return root;

    if (x < root->val) return search(root->left, x);
    return search(root->right, x);
}

TreeNode* getInorderSuccessor(TreeNode* root) {
    if (root == nullptr) return nullptr;

    TreeNode* curr = root->right;
    while (curr != nullptr && curr->left != nullptr) curr = curr->left;
    return curr;
}

/*
    didn't look into balancing while deleting
    see GFG: https://www.geeksforgeeks.org/deletion-in-an-avl-tree/
*/
TreeNode* balanceRemove(TreeNode* root) {
    if (root == nullptr) return nullptr;

    /*
        updating height & balancing each node using AVL rotations
    */
    root->height = 1 + max(height(root->left), height(root->right));
    int bal = getBalance(root);

    // left-left case: the value we are inserting and the
    // cause of the unbalance is lesser than the root->left,
    // which means it is in the left sub-tree of root->left
    if (bal > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }

    // left-right case: first do a left rotation on the left sub-tree
    // this will convert it to a left-left case
    // then we can do a right rotation as normal
    if (bal > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // right-right case
    if (bal < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }

    // right-left case
    if (bal < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

TreeNode* remove(TreeNode* root, int val) {
    if (root == nullptr) return nullptr;

    if (val < root->val)
        root->left = remove(root->left, val);
    else if (val > root->val)
        root->right = remove(root->right, val);
    else {
        if (root->left == nullptr && root->right == nullptr) {
            root = nullptr;
        } else if (root->left == nullptr || root->right == nullptr) {
            TreeNode* temp = root->left ? root->left : root->right;
            *root = *temp;
        } else {
            /*
                replace root with its immediate inorder successor or predecessor
                which would be right most node on the left sub-tree or,
                which would be left most node on the right sub-tree
            */
            TreeNode* s = getInorderSuccessor(root);
            root->val = s->val;

            /*
                since we have copied this value, we need to remove it from
                the right sub-tree and return the modified root
            */
            root->right = remove(root->right, s->val);
        }
    }

    // return root; // without balancing
    return balanceRemove(root);
}

void inorder(TreeNode* root) {
    if (root == nullptr) return;

    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n;
    cin >> n;

    /*
        Apparently, C++ does not support string in switch case
        1: insert
        2: search
        3: delete
        4: inorder traversal
    */
    int cmd, x;
    TreeNode* root = nullptr;

    forn(n) {
        cin >> cmd;
        cin >> x;

        switch (cmd) {
            case 1:
                root = insert(root, x);
                cout << x << " inserted!\n";
                break;
            case 2:
                if (search(root, x) != nullptr)
                    cout << x << " found!\n";
                else
                    cout << x << " not found.\n";
                break;
            case 3:
                root = remove(root, x);
                cout << x << " deleted!\n";
                break;
            case 4:
                inorder(root);
                cout << "\n";
                break;
            default:
                cout << "invalid command\n";
                break;
        }
    }

    return 0;
}