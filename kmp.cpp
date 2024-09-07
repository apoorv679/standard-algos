// good explanation:
// https://www.youtube.com/watch?v=BXCEFAzhxGY
// for code: https://www.youtube.com/watch?v=JoF0Z7nVSrA

// Test Input :
// 2
// adsgwadsxdsgwadsgz dsgwadsgz
// adsgwadsgwadsgwadsgz dsgwadsg

// Expected Output
// 10 
// 2 7 12 

#define loop(n) for (int i = 0; i < n; i++)

#define printArr(arr)                    \
    for (auto i : arr) cout << i << " "; \
    cout << "\n";

#include <bits/stdc++.h>
using namespace std;

vector<int> buildLongestPrefixSuffix(string pattern) {
    vector<int> lps(pattern.length());
    // prefix should be proper prefix i.e. prefix != original string
    lps[0] = 0;
    int prevLPS = 0;  // length of longest prefix-suffix at any point
    int idx = 1;      // starting from 1 as lps[0] is always 0

    while (idx < pattern.length()) {
        if (pattern[idx] == pattern[prevLPS]) {
            lps[idx] = prevLPS + 1;
            prevLPS++;
            idx++;
        } else {
            if (prevLPS == 0) {
                lps[idx] = 0;
                idx++;
            } else {
                prevLPS = lps[prevLPS - 1];
            }
        }
    }

    // printArr(lps);

    return lps;
}

vector<int> kmp(string text, string pattern) {
    vector<int> lps = buildLongestPrefixSuffix(pattern);

    vector<int> result;
    int i = 0, j = 0;

    while (j < text.length()) {
        if (pattern[i] == text[j]) {
            i++;
            j++;
        } else {
            if (i == 0) {
                j++;
            } else {
                // move i to the position just after the prefix
                // which matches the suffix before the mismatch happened
                i = lps[i - 1];
            }
        }

        if (i == pattern.length()) {
            // match found
            result.push_back(j - pattern.length() + 1);
            i = lps[i - 1];
        }
    }

    return result;
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

    loop(n) {
        string text, pattern;
        cin >> text >> pattern;

        printArr(kmp(text, pattern));
    }

    return 0;
}