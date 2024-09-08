// Test Input:
// 50

// Expected Output:
// 2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 

#include <bits/stdc++.h>
using namespace std;

#define printArr(arr)                    \
    for (auto i : arr) cout << i << " "; \
    cout << "\n";

/*
Time Complexity: O(nlog(log(n)))
Why?

For each prime p, inner loop will run n/p times
so, n/2 + n/3 + n/5....etc
n(1/2 + 1/3 + 1/5...)
The inner sum is a harmonic progression converging log(log(n)) -> see proof separately
=> total = nlog(log(n))

See also: segmented sieve
It has same time complexity (GFG mentions O(n * ln(sqrt(n)) but says it is nearly the same)
Advantages?
1. better locality of reference (caching by CPU)
2. requires O(sqrt(n)) space as opposed to O(n) by normal sieve
*/

vector<int> sieveOfEratosthenes(int n) {
    vector<bool> isPrime(true, n + 1);
    isPrime[0] = false;
    isPrime[1] = false;

    for (int i = 2; i * i <= n; i++) {
        if (!isPrime[i]) continue;

        /*
            if number is prime, mark all its multiples upto n as not prime
            why start from i * i instead of just i?
            because smaller multiples of i would have been marked as not prime already
        */ 
        for (int j = i * i; j <= n; j += i) {
            isPrime[j] = false;
        }
    }

    vector<int> result;
    for (int i = 0; i <= n; i++) {
        if (isPrime[i]) result.push_back(i);
    }

    return result;
}

// TODO: sieve algorithm in O(n)
vector<int> fastSieve(int n) {

}

/*
EXTRAS: more algos related to prime numbers
*/

// O(sqrt(n)) check number is prime or not
bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// TODO: prime factorisation

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

    printArr(sieveOfEratosthenes(n));

    return 0;
}