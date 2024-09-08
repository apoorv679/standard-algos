/*
Can solve questions like:
If we have 1x1 and 2x1 rectangles, in how may ways can we form a rectangle of Nx1?
Hint: try to make a recurrence relation from base case
*/

#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

typedef unsigned long long ull;

// specific to multiplying 2x2 matrices, can be generalised
void multiply(vector<vector<ull>>& A, vector<vector<ull>>& B) {
    // Matrix to store the result
    vector<vector<ull>> C(2, vector<ull>(2));

    // Matrix Multiply
    C[0][0] = (A[0][0] * B[0][0] + A[0][1] * B[1][0]) % MOD;
    C[0][1] = (A[0][0] * B[0][1] + A[0][1] * B[1][1]) % MOD;
    C[1][0] = (A[1][0] * B[0][0] + A[1][1] * B[1][0]) % MOD;
    C[1][1] = (A[1][0] * B[0][1] + A[1][1] * B[1][1]) % MOD;

    // Copy the result back to the first matrix
    // avoids making a new matrix for each multiplication
    A[0][0] = C[0][0];
    A[0][1] = C[0][1];
    A[1][0] = C[1][0];
    A[1][1] = C[1][1];
}

vector<vector<ull>> exp(vector<vector<ull>>& M, int n) {
    // need to substitute with identity, which is 1 for integers
    // and identity matrix (I) for matrices (all left diagonal values are 1)
    vector<vector<ull>> res = {
        {1, 0},
        {0, 1}};

    while (n) {
        if (n & 1) multiply(res, M);
        multiply(M, M);
        n >>= 1;
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

    int n;
    cin >> n;

    if (n == 0 || n == 1) return n;

    vector<vector<ull>> M = {
        {1, 1},
        {1, 0}};

    vector<vector<ull>> res = exp(M, n - 1);

    /*
    finally we multiply with base case:
    {Fn   0} = M ^ (n-1) * F
    {Fn-1 0}

    fib(0) = 0
    fib(1) = 1
    so F = {
        {1 0}
        {0 0}
    }
    */

    vector<vector<ull>> F = {
        {1, 0},
        {0, 0}};

    multiply(res, F);

    cout << "N-th Fibonacci number: " << res[0][0] << "\n";

    return 0;
}