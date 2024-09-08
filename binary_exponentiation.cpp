/*
good article: https://www.geeksforgeeks.org/binary-exponentiation-for-competitive-programming/

can check out matrix exponentiation for solving recurrence relations in log(n) time
eg. calculating n-th Fibonacci number in O(log(n)) 
-> good video on this: https://www.youtube.com/watch?v=EEb6JP3NXBI
*/

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

ull exp(ull a, ull b) {
    if (b == 0) return 1;
    if (a == 1 || b == 1) return a;

    ull res = exp(a, b >> 1);
    if (b & 1) {
        return a * res * res;
    }

    return res * res;
}

ull exp_iterative(ull a, ull b) {
    ull res = 1;
    while (b) {
        if (b & 1) res *= a;
        a *= a;
        b >>= 1;
    }

    return res;
}

// (a^b) % MOD - where MOD is some large prime number
#define MOD 1000000007

// (A * B) mod M = ((A mod M) * (B mod M)) mod M
ull moduloExp(ull a, ull b) {
    ull res = 1;
    while (b) {
        // we don't do ((res % MOD) * (a % MOD)) % MOD,
        // idea is that res and a are always within bounds
        if (b & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }

    return res;
}

// more generic: (a ^ b) % p
ull moduloExpP(ull a, ull b, ull p) {
    ull res = 1;

    a = a % p;
    if (a == 0) return 0; // in case a is divisible by p

    while (b) {
        if (b & 1) res = (res * a) % p;
        a = (a * a) % p;
        b >>= 1;
    }

    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    ull a, b;
    cin >> a >> b;

    // cout << exp(a, b) << "\n";
    // cout << exp_iterative(a, b) << "\n";
    // cout << moduloExp(a, b) << "\n";

    ull p;
    cin >> p;
    cout << moduloExpP(a, b, p) << "\n";

    return 0;
}