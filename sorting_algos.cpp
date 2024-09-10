// Test Input:
// 10
// 5 8 4 4 2 0 -23 3 4 7

// Expected Output:
// <some>sort: -23 0 2 3 4 4 4 5 7 8 

#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007
#define forn(n) for (int i = 0; i < n; i++)
#define printv(v)                      \
    for (auto i : v) cout << i << " "; \
    cout << "\n";

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;

/*
    Sorting Terminology:

    1. In-place Sorting:
        Requires O(1) space, as it modifies the array iself
        Examples: Selection Sort, Bubble Sort Insertion Sort and Heap Sort.

    2. Internal Sorting:
        All the data is placed in the main memory.
        In internal sorting, the problem cannot take input beyond its size.
        Example: heap sort, bubble sort, selection sort, quick sort, shell sort, insertion sort.

    3. External Sorting:
        All the data that needs to be sorted cannot be placed in memory at a time.
        External Sorting is used for the massive amount of data.
        Examples: Merge sort, etc.

    4. Stable sorting:
        Does not change relative positioning of equal elements
        Examples: Merge Sort, Insertion Sort, Bubble Sort.

    5. Unstable sorting:
        Does not guarantee that two equal elements will maintian their relatove positioning
        Examples: Selection Sort, Quick Sort, Heap Sort, Shell Sort.

    6. Online sorting:
        Can process its input piece-by-piece in a serial fashion, i.e.,
        in the order that the input is fed to the algorithm,
        without having the entire input available from the beginning.
        Examples: insertion sort
        (it considers one input element per iteration and produces a
        partial solution without considering future elements
        in essence, in the k-th iteration, it will have a k length sorted array,
        while the rest of the array is unsorted)

    7. Adaptive sorting:
        Takes advantage of pre-existing order in the data to improve performance.
        For example insertion sort takes time proportional to number of inversions in
        the input array.
*/

/*
    Selection sort
    ==============
    Logic: For each i, swap arr[i] until arr[i] is the smallest
    So after each loop, we get the correct element in the i-th position
    It sorts the array left to right

    Time Complexity: O(n^2)
    Space Complexity: O(1)
    Properties: [[in-place, internal, unstable, offline]]

    Special:
    1. selection sort can be made stable => see: stable selection sort
    2. take O(n^2) no matter what is the relative ordering of elements
*/
void selectionsort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                swap(arr[i], arr[j]);
            }
        }

        // see state after each pass
        printv(arr);
    }
}

/*
    Bubble sort
    ===========
    Logic: For each i, swap arr[j] and arr[j+1] until the largest element "bubbles" to the last
    So after each loop, we get the correct element in the (n-1-i)-th position
    It sorts the array right to left

    Time Complexity: O(n^2)
    Space Complexity: O(1)
    Properties: [[in-place, internal, stable, offline]]

    Special:
    1. Best case TC: O(n) when array is already sorted, if we use the 'swapped' check
    2. Hence useful when we know array is almost sorted
    3. Above property is intuitive too, because comparing adjacent elements is how
    we would determine if an array is already sorted too
*/
void bubblesort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;

    for (int i = 0; i < n; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // see state after each pass
        printv(arr);
        // if no elements were swapped, array is in sorted state
        if (!swapped) break;
    }
}

/*
    Insertion sort
    ==============
    Logic: For each el at i-th position, assume the left portion to be sorted
    And we try to put (or "insert") the element el at the correct position
    in the sorted array. Somewhat like putting a card at the right position
    in playing cards

    Time Complexity: O(n^2)
    Space Complexity: O(1)
    Properties: [[in-place, internal, stable, online]]

    Special:
    1. Online algorithm. So can be used to sort a data stream
    2. Best case TC: O(n) when array is already sorted
    3. Efficient for small lists and nearly sorted lists
    4. Adaptive. the number of inversions is directly proportional to number of swaps.
    For example, no swapping happens for a sorted array and it takes O(n) time only.
*/
void insertionsort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 1; i < n; i++) {
        int el = arr[i];
        int j = i - 1;

        // if the first j is already smaller than el
        // it means el is at the correct position
        // and we don't check any further
        while (j >= 0 && arr[j] > el) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = el;

        // see state after each pass
        printv(arr);
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

    int n;
    cin >> n;

    vector<int> v(n);
    forn(v.size()) cin >> v[i];

    // selectionsort(v);
    // cout << "selection: ";

    // bubblesort(v);
    // cout << "bubblesort: ";

    insertionsort(v);
    cout << "insertionsort: ";

    printv(v);

    return 0;
}