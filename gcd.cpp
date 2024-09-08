#include <bits/stdc++.h>
using namespace std;

/*
Based on Euclid's theorem that
gcd(a, b); where a > b
= gcd(a - b, b)

and instead of subtracting over and over, we directly take mod

Time Complexity: O(log(min(a,b)))
*/
int gcd(int a, int b) {
    if (a < b) return gcd(b, a);
    if (b == 0) return a;

    return gcd(b, a % b);
}

// TODO: extended gcd

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int a, b;
    cin >> a >> b;
    cout << gcd(a, b) << "\n";

    return 0;
}