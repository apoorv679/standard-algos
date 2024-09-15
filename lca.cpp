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

struct Node {
    int val;
    Node* left;
    Node* right;

    Node() : val(0), left(nullptr), right(nullptr) {}
    Node(int x) : val(x), left(nullptr), right(nullptr) {}
};

/*
    stores the path to the node with value x
    needs nodes with unique values to work
*/
bool findPath(Node* root, int x, vector<Node*>& path) {
    if (root == nullptr) return false;

    path.push_back(root);
    if (root->val == x) return true;

    if (findPath(root->left, x, path) || findPath(root->right, x, path)) return true;

    path.pop_back();
    return false;
}

/*
    This is a two pass intuitive solution, but requires O(N) space in worst case
    Time Complexity: O(N)
*/
Node* findLCA(Node* root, int n1, int n2) {
    vector<Node*> path1, path2;

    // if either of n1 or n2 are not found, they cannot have a LCA
    if (!findPath(root, n1, path1) || !findPath(root, n2, path2)) return nullptr;

    int i;
    // wherever the path diverges, the node just before that is the
    // last common node on the path to either values
    for (i = 0; i < path1.size() && i < path2.size(); i++) {
        if (path1[i]->val != path2[i]->val) break;
    }

    // if the paths never diverge, but one of the path ends, then that
    // means that one of the path is a sub-path of the other path
    return path1[i - 1];
}

/*
    Logic:
    If either value match the root, return the node
    The first node where both left and right are not null will have
    either of n1 or n2 on the left, and the other on the right

    If both nodes are on the same path, the method returns as soon
    as it finds the first matching value

    For this to work, we should ensure that both values do infact exist,
    as otherwise, if only a single value exists, it will return that node
    instead of returning nullptr

    To enable that, we can implement a find method and do a tree traversal to
    ensure both values exist

    Time Complexity: O(N)
    Space complexity: O(1)
*/
bool find(Node* root, int x) {
    if (root == nullptr) return false;

    if (root->val == x) return true;
    if (find(root->left, x) || find(root->right, x)) return true;

    return false;
}

Node* findLCAUtil(Node* root, int n1, int n2) {
    if (root == nullptr) return nullptr;

    if (root->val == n1 || root->val == n2) return root;

    Node* left = findLCAUtil(root->left, n1, n2);
    Node* right = findLCAUtil(root->right, n1, n2);

    if (left && right) return root;

    return left ? left : right;
}

Node* findLCAImproved(Node* root, int n1, int n2) {
    if (root == nullptr) return nullptr;

    // if either key is not found, return nullptr
    if (!find(root, n1) || !find(root, n2)) return nullptr;

    return findLCAUtil(root, n1, n2);
}

/*
    Finding LCA in BST
    Since the tree is a BST, we can eliminate parts of the tree
    based on the value we are searching

    If both nodes exist, the first node with value 
    n1 <= node->val <= n2, will be the ancestor

    We can do a check for the existence of both n1 and n2 before
    running this to ensure that LCA exists, if not stated otherwise 
    in the problem statement
*/

Node* findLCAInBST(Node* root, int n1, int n2) {
    if (root == nullptr) return nullptr;

    if (n1 < root->val && n2 < root->val) return findLCAInBST(root->left, n1, n2);
    if (n1 > root-> val && n2 > root->val) return findLCAInBST(root->right, n1, n2);

    // either n1 or n2 == root->val OR n1 < root->val < n2 OR n2 < root->val < n1
    return root;
}

// RMQ on LCA is also a standard problem, but is usually 
// a bit advanced for LC style interviews, so not covered here
// see GFG: https://www.geeksforgeeks.org/find-lca-in-binary-tree-using-rmq

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    // cout << "LCA(4, 5) = " << findLCA(root, 4, 5)->val;
    // cout << "\nLCA(4, 6) = " << findLCA(root, 4, 6)->val;
    // cout << "\nLCA(3, 4) = " << findLCA(root, 3, 4)->val;
    // cout << "\nLCA(2, 4) = " << findLCA(root, 2, 4)->val;
    // cout << "\nLCA(1, 4) = " << findLCA(root, 1, 4)->val;

    cout << "LCA(4, 5) = " << findLCAImproved(root, 4, 5)->val;
    cout << "\nLCA(4, 6) = " << findLCAImproved(root, 4, 6)->val;
    cout << "\nLCA(3, 4) = " << findLCAImproved(root, 3, 4)->val;
    cout << "\nLCA(2, 4) = " << findLCAImproved(root, 2, 4)->val;
    cout << "\nLCA(1, 4) = " << findLCAImproved(root, 1, 4)->val;

    /*
        Expected Output:

        LCA(4, 5) = 2
        LCA(4, 6) = 1
        LCA(3, 4) = 1
        LCA(2, 4) = 2
        LCA(1, 4) = 1
    */

    return 0;
}