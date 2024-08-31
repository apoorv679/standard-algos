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
// level 0: 0
// level 1: 1 3
// level 2: 2 7 4 6
// level 3: 9 8 5

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

void bfs(vector<vector<int>>& g, int n) {
    queue<int> q;
    q.push(n);
    unordered_set<int> visited;  // can use boolean array too
    int level = 0;
    vector<int> next;

    cout << "level " << level << ": ";
    while (!q.empty()) {
        int v = q.front();
        q.pop();

        if (visited.find(v) == visited.end()) {
            visited.insert(v);

            cout << v << " ";  // printing bfs

            for (int i = 0; i < g[v].size(); i++) {
                if (visited.find(g[v][i]) == visited.end()) {
                    next.push_back(g[v][i]);
                }
            }
        }

        /*
        instead of directly pushing into the queue, we hold all the nodes 
        reachable in the next level separately. this is useful in case we want 
        to process nodes by level, or know which level does each node belong to
        (say for getting the length of the shortest path in an undirected graph)
        */
        if (q.empty() && !next.empty()) {
            for (int i = 0; i < next.size(); i++) {
                q.push(next[i]);
            }
            next.clear();

            level++;
            cout << "\nlevel " << level << ": ";
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
    could be that we are asked to do bfs over all nodes
    in that case, we can pass the visited from main()
    and run bfs on the nodes which are not visited
    */
    int start;
    cin >> start;
    bfs(g, start);

    return 0;
}