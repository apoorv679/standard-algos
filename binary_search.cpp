/*
    Good articles:
    1. https://www.topcoder.com/thrive/articles/Binary%20Search
    2. https://leetcode.com/discuss/general-discussion/1233854/a-noobs-guide-to-the-binary-search-algorithm
*/

// Test Input:
// 10
// 5 8 4 4 2 0 -23 3 4 7
// 4

// Expected Output:
// found at index: 4

#include <bits/stdc++.h>
using namespace std;

int binary_search(vector<int> list, int x) {
    // can define bounds to be [l,h] or [l,h), but need to write logic accordingly
    int l = 0, h = list.size() - 1;

    while (l <= h) {
        int mid = l + (h - l) / 2; // avoid overflow
        if (x == list[mid]) return mid;

        if (x < list[mid])
            h = mid - 1;
        else
            l = mid + 1;
    }

    return -1;
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
    vector<int> list(n);
    for (int i = 0; i < n; i++) {
        cin >> list[i];
    }

    int x;
    cin >> x;

    sort(list.begin(), list.end()); // binary search can only be done over sorted data
    cout << "found at index: " << binary_search(list, x) << "\n";

    return 0;
}