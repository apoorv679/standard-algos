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
// 0

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
        // g[v].push_back(u);  // undirected graph does not have a topological order
    }
    return g;
}

void topSort(vector<vector<int>>& g, unordered_set<int>& visited, int v) {
    if (visited.find(v) != visited.end()) {
        return;
    }

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

    int start;
    cin >> start;
    topSort(g, visited, start);

    // basically dfs will complete in the reverse topological order
    reverse(order.begin(), order.end());

    cout << "topological order:\n";
    for (int i = 0; i < order.size(); i++) {
        cout << order[i] << " ";
    }

    /*
    at this stage it might be required to check if any node is missed
    in the order vector which would happen if they cannot be reached
    from start node.
    instead, we can run topSort algorithm on all nodes with indegree = 0
    To calculate indegree, we can run over all the edges and keep a counter
    */

    return 0;
}