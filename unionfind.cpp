// resources:
// https://www.youtube.com/watch?v=wU6udHRIkcc

// Test Input:
// 8 9
// 1 2
// 3 4
// 5 6
// 7 8
// 2 4
// 2 5
// 1 3
// 6 8
// 5 7

// Expected Output:
// 1 2
// -1 -2 1 -1 -1 -1 -1 -1 -1
// 3 4
// -1 -2 1 -2 3 -1 -1 -1 -1
// 5 6
// -1 -2 1 -2 3 -2 5 -1 -1
// 7 8
// -1 -2 1 -2 3 -2 5 -2 7
// 2 4
// -1 -4 1 1 3 -2 5 -2 7
// 2 5
// -1 -6 1 1 3 1 5 -2 7
// 1 3
// cycle found: 1 3
// -1 -6 1 1 3 1 5 -2 7
// 6 8
// -1 -8 1 1 3 1 1 1 7
// 5 7
// cycle found: 5 7
// -1 -8 1 1 3 1 1 1 7
//

#include <bits/stdc++.h>
using namespace std;

struct UnionFind {
    int size = 0;
    vector<int> parent;

    UnionFind() {
        return;
    }

    UnionFind(int n) {
        for (int i = 0; i <= n; i++) {
            parent.push_back(-1);
        }
        size = n;
    }

   public:
    int Find(int x) {
        int pos = x;
        while (parent[x] >= 0) {
            x = parent[x];
        }

        // collapsing find
        if (pos != x) {
            parent[pos] = x;
        }

        return x;
    }

    void Union(int x, int y) {
        int xParent = Find(x);
        int yParent = Find(y);

        if (xParent == yParent)  // cycle detection, Kruskal's MST Algo.
        {
            cout << "cycle found: " << x << " " << y << "\n";
            return;
        }

        /*
        weighted union
        if the set that y belongs to has more weight,
        make x a child of y
        NOTE: the weights are in negative, so comparison is inverted
        */
        if (parent[xParent] > parent[yParent]) {
            parent[yParent] += parent[xParent];  // inc. wt.
            parent[xParent] = yParent;
            return;
        }

        parent[xParent] += parent[yParent];
        parent[yParent] = xParent;
    }

    void Print() {
        for (int i = 0; i <= size; i++) {
            cout << parent[i] << " ";
        }
        cout << "\n";
    }
};

int main() {
    int n, e;
    cin >> n >> e;

    UnionFind *obj = new UnionFind(n);

    int x, y;
    for (int i = 0; i < e; i++) {
        cin >> x >> y;
        cout << x << " " << y << "\n";
        obj->Union(x, y);
        obj->Print();
    }

    return 0;
}