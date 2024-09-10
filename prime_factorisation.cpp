#include <bits/stdc++.h>
using namespace std;

#define printArr(arr)                    \
    for (auto i : arr) cout << i << " "; \
    cout << "\n";

/*
    Time complexity: O(sqrt(n))
    Why?

    In worst case, we have to go through entire list.
    In case we find a prime factor, we update n which causes the
    sqrt to come down as well
*/
void primeFactors() {
    int n;
    cin >> n;

    vector<int> factors;

    /*
        first we divide by the smallest prime number 2
        and keep on adding 2s until the numbers becomes odd
    */
    while (n % 2 == 0) {
        factors.push_back(2);
        n /= 2;
    }

    /*
        factors can only be odd now
        also we keep on dividing until all instances of the prime number
        are removed from the number

        so for eg, by the time i = 9, we would have already removed all 3s from the factors
        and so it will not divide n at all
    */
    for (int i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }

    /*
        if the last number is a prime factor > sqrt(n)
        for eg. n = 65
        we require this as we are not pushing the pair of the divisor
        eg. when 5 divides 65, we don't automatically push 13

        why? because the dividend might not always be prime
    */
    if (n > 2) factors.push_back(n);

    printArr(factors);
}

/*
    Prime factors in O(log(n))

    If there are multiple queries Q,
    then we can do some pre-computation to answer each query
    in O(log(n)) instead of O(sqrt(n))
*/

// build SPF (Shortest Prime Factor) till N using sieve

// Time Complexity: O(Nlog(log(n)))
vector<int> spf(int N) {
    vector<int> SPF(N + 1);
    for (int i = 2; i <= N; i++) SPF[i] = i;

    for (int i = 2; i * i <= N; i++) {
        if (SPF[i] == i) {  // prime
            for (int j = i * i; j <= N; j += i) {
                if (SPF[j] == j) SPF[j] = i;
            }
        }
    }

    return SPF;
}

// Qlog(n) + nlog(log(n)) for pre-compute. 
// Lesser than Qsqrt(n) that we would get with normal factorisation
void primeFactorsQueries() {
    int q;
    cin >> q;

    vector<int> SPF = spf(1000);  // this will be te max range of inputs
    for (int i = 1; i <= q; i++) {
        int n;
        cin >> n;

        while (n != 1) {
            cout << SPF[n] << " ";
            n /= SPF[n];
        }
        cout << "\n";
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

    // primeFactors();
    primeFactorsQueries();

    return 0;
}