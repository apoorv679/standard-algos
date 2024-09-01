// Test Input:

// 10 13
// 0 1
// 0 3
// 1 2
// 3 2
// 2 9
// 2 8
// 1 7
// 1 4
// 1 6
// 4 7
// 4 5
// 4 6
// 7 6

// Expected Output:
// topological order:
// 0 3 1 4 5 7 6 2 8 9 

#include <bits/stdc++.h>
using namespace std;

vector<int> order;

vector<vector<int>> buildGraph() {
    int v, e;
    cin >> v >> e;

    vector<vector<int>> g(v, vector<int>());
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        // g[v].push_back(u);  // only DAGs can have a topological order
    }
    return g;
}

/*
cycle detection in directed graph:
topological sorting can help detect cycles in a directed graph
a graph (directed/undirected) will have a cycle if it has a "back-edge"

back-edge: an edge that connects a node to one of its ancestors in a DFS tree
i.e. if a node has an edge to another node which has not yet been processed by
the dfs recursion.
In other words, the node is not present in the order vector in below code
Since searching in a vector is O(n), we can use an unordered_set::processed to keep
track of this property

cycle detection in undirected graph:
if a node has an edge to another node which is not its parent 
*/
void topSort(vector<vector<int>>& g, unordered_set<int>& visited, int v) {
    visited.insert(v);
    for (int i = 0; i < g[v].size(); i++) {
        if (visited.find(g[v][i]) == visited.end()) {
            topSort(g, visited, g[v][i]);
        }
    }

    order.push_back(v);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    vector<vector<int>> g = buildGraph();
    unordered_set<int> visited;

    for (int i = 0; i < g.size(); i++) {
        if (visited.find(i) == visited.end()) {
            topSort(g, visited, i);
        }
    }
    
    // basically dfs will complete in the reverse topological order
    reverse(order.begin(), order.end());

    cout << "topological order:\n";
    for (int i = 0; i < order.size(); i++) {
        cout << order[i] << " ";
    }

    return 0;
}