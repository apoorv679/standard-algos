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
// 0 1 3 4 2 7 5 9 8 6 

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

void topSort(vector<vector<int>>& g, vector<int>& indegree) {
    queue<int> q;
    for (int i = 0; i < indegree.size(); i++) {
        if (indegree[i] == 0) q.push(i);
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        order.push_back(v);

        for (int i = 0; i < g[v].size(); i++) {
            indegree[g[v][i]]--;
            if (indegree[g[v][i]] == 0) {
                q.push(g[v][i]);
            }
        }
    }
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

    vector<int> indegree(g.size(), 0);
    for (int i = 0; i < g.size(); i++) {
        for (int j = 0; j < g[i].size(); j++) {
            indegree[g[i][j]]++;
        }
    }

    /*
    visited is not required as the check indegree[node] == 0 ensures that 
    it is added to the queue only when all its parents have been visited
    */
    topSort(g, indegree);

    /*
    for a node having a cycle, the indegree will never be 0
    */
    if (order.size() != g.size()) {
        cout << "Graph contains a cycle!\n";
        return 0;
    }

    cout << "topological order:\n";
    for (int i = 0; i < order.size(); i++) {
        cout << order[i] << " ";
    }

    return 0;
}