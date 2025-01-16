// A C++ Program to detect
// cycle in an undirected graph
#include <iostream>
#include <vector>
using namespace std;

// A recursive function that
// uses visited[] and parent to detect
// cycle in subgraph reachable
// from vertex v.
bool isCyclicUtil(int v, vector<vector<int>>& adj, 
                  bool visited[], int parent) {
    // Mark the current node as visited
    visited[v] = true;

    // Recur for all the vertices
    // adjacent to this vertex
    for (int i : adj[v]) {
        // If an adjacent vertex is not visited,
        // then recur for that adjacent
        if (!visited[i]) {
            if (isCyclicUtil(i, adj, visited, v))
                return true;
        }
        // If an adjacent vertex is visited and
        // is not parent of current vertex,
        // then there exists a cycle in the graph.
        else if (i != parent)
            return true;
    }
    return false;
}

// Returns true if the graph contains
// a cycle, else false.
bool isCyclic(int V, vector<vector<int>>& adj) {
    // Mark all the vertices as not visited
    bool* visited = new bool[V]{false};

    // Call the recursive helper function
    // to detect cycle in different DFS trees
    for (int u = 0; u < V; u++) {
        // Don't recur for u if it is already visited
        if (!visited[u])
            if (isCyclicUtil(u, adj, visited, -1))
                return true;
    }
    return false;
}

// Driver program to test above functions
int main() {
    int V = 3;
    vector<vector<int>> adj(V);

    adj[1].push_back(0);
    adj[0].push_back(1);
    adj[0].push_back(2);
    adj[2].push_back(0);
    adj[1].push_back(2);
    adj[2].push_back(1);

    isCyclic(V, adj) ? cout << "Contains cycle\n"
                     : cout << "No Cycle\n";

    V = 3;
    vector<vector<int>> adj2(V);

    adj2[0].push_back(1);
    adj2[1].push_back(0);
    adj2[1].push_back(2);
    adj2[2].push_back(1);

    isCyclic(V, adj2) ? cout << "Contains Cycle\n"
                      : cout << "No Cycle\n";

    return 0;
}