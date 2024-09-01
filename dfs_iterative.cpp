// Test Input:

// graph used: https://www.youtube.com/watch?v=pcKY4hjDrxk&t=734s (0-indexed)

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
// 0 3 2 8 9 1 6 7 4 5

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> buildGraph() {
    int v, e;
    cin >> v >> e;

    vector<vector<int>> g(v, vector<int>());
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);  // undirected graph
    }
    return g;
}

void dfs(vector<vector<int>>& g, int n) {
    stack<int> s;
    s.push(n);
    unordered_set<int> visited;  // can use boolean array too

    while (!s.empty()) {
        int v = s.top();
        s.pop();

        if (visited.find(v) == visited.end()) {
            visited.insert(v);

            cout << v << " ";  // printing dfs

            for (int i = 0; i < g[v].size(); i++) {
                if (visited.find(g[v][i]) == visited.end()) {
                    s.push(g[v][i]);
                }
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
    /*
    could be that we are asked to do dfs over all nodes
    in that case, we can run dfs in a for loop over all 
    the nodes which are not visited
    */
    int start;
    cin >> start;
    dfs(g, start);

    return 0;
}