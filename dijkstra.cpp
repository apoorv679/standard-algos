// Test Input:

// graph used: https://www.youtube.com/watch?v=bZkzH5x0SKU (0-indexed)

// 6 9
// 0 1 2
// 0 3 8
// 1 3 5
// 1 4 6
// 4 5 1
// 3 4 3
// 3 5 2
// 5 2 3
// 4 2 9
// 0 2

// Expected Output:
// shortest distance from 0
// vertice 0: 0
// vertice 1: 2
// vertice 2: 12
// vertice 3: 7
// vertice 4: 8
// vertice 5: 9
// shortest path from 0 to 2
// 0 1 3 5 2 


#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

vector<vector<pii>> buildGraph() {
    int v, e;
    cin >> v >> e;

    vector<vector<pii>> g(v, vector<pii>());
    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        g[u].push_back(make_pair(v, w));
        g[v].push_back(make_pair(u, w));  // undirected graph
    }
    return g;
}

void dijkstra(vector<vector<pii>>& g, int src, int dest) {
    int vertices = g.size();
    vector<int> d(vertices, INT_MAX);  // current shortest distance from src
    d[src] = 0;

    priority_queue<pii, vector<pii>, greater<pii>> h;  // min heap
    unordered_set<int> visited;
    vector<int> parent(vertices, -1); // required to get the actual path

    h.push(make_pair(d[src], src));
    while (!h.empty()) {
        int u = h.top().second;
        h.pop();

        visited.insert(u);

        for (int i = 0; i < g[u].size(); i++) {
            int v = g[u][i].first;
            int w = g[u][i].second;
            /*
            visited is not necessary for dijkstra,
            as once a node is processed, even if it was pushed to the heap twice
            due to a second optimisation, it will not change anything. 
            but with hash set we can do a lookup in O(1) time and O(V) space only
            therefore, having it is beneficial
            */ 
            if (visited.find(v) != visited.end()) {
                continue;
            }

            // relax edge
            if (d[v] == INT_MAX || d[v] > d[u] + w) {
                d[v] = d[u] + w;
                parent[v] = u;

                h.push(make_pair(d[v], v));
            }
        }
    }

    // print shortest distance values
    cout << "shortest distance from " << src << "\n";
    for (int i = 0; i < vertices; i++) {
        cout << "vertice " << i << ": " << d[i] << "\n";
    }

    // print shortest path
    cout << "shortest path from " << src << " to " << dest << "\n";
    int idx = dest;
    string path = "";
    while (idx != -1) {
        path = to_string(idx) + " " + path;
        idx = parent[idx];
    }
    cout << path << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    vector<vector<pii>> g = buildGraph();

    int source, destination;
    cin >> source >> destination;
    dijkstra(g, source, destination);

    return 0;
}