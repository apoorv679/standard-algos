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

void merge(vector<int>& arr, int l, int mid, int h) {
    int i = l, j = mid + 1;
    vector<int> temp;

    while (i <= mid && j <= h) {
        if (arr[i] > arr[j])
            temp.push_back(arr[j++]);
        else
            temp.push_back(arr[i++]);
    }

    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= h) temp.push_back(arr[j++]);

    for (int i = 0; i < temp.size(); i++) arr[l++] = temp[i];
}

void mergesortutil(vector<int>& arr, int l, int h) {
    if (l >= h) return;

    int mid = l + (h - l) / 2;
    mergesortutil(arr, l, mid);
    mergesortutil(arr, mid + 1, h);
    merge(arr, l, mid, h);

    // see state after each merge
    cout << "range " << l << " to " << h << ": ";
    for (int i = l; i <= h; i++) cout << arr[i] << " ";
    cout << "\n";
}

/*
    Merge sort
    ==============
    Logic: DnC. Divide larger array recursively and stitch together each sorted part

    Time Complexity: O(nlog(n)) in all;
     - best: when array is already sorted
     - average: random order
     - worst: reverse sorted
    Space Complexity: O(n)
    Properties: [[NOT in-place, external, stable, offline]]

    Special:
    1. Used to sort large dataset, as it is an external sort
    2. Stable so is useful when sorting by multiple parameters is required,
    for eg. when sortin objects
    3. Can be parallelised as each subarray can be sorted independently
    4. Optimised and has a guaranteed nlogn time, even in worst case
    5. only downside is the extra space required
*/
void mergesort(vector<int>& arr) {
    mergesortutil(arr, 0, arr.size() - 1);
}

int partition(vector<int>& arr, int l, int h) {
    /*
        intuition: i represents the last position where an element
        <= pivot is found. Once we have processed al the elements
        other than the pivot, we can safely insert it at (i+1)th position
    */
    int pivot = arr[h];

    int i = l - 1, j = h;
    for (int j = l; j < h; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[h]);

    return i + 1;
}

void quicksortutil(vector<int>& arr, int l, int h) {
    if (l >= h) return;

    int p = partition(arr, l, h);  // O(n)

    // see state after each partition
    cout << "range " << l << " to " << h << ": ";
    for (int i = l; i <= h; i++) cout << arr[i] << " ";
    cout << "\n";

    quicksortutil(arr, l, p - 1);
    quicksortutil(arr, p + 1, h);
}

/*
    Quick sort
    ==============
    Logic: DnC. Pick a 'pivot' element and put it in it's correct position.
    This is done by moving the elements > pivot on its right, and <= on the left

    Time Complexity: O(nlog(n)) in best/average, O(n^2) in worst;
     - best: in each iteration, pivot divides the array equally
     - average: random order
     - worst: already sorted
    Space Complexity: O(1)
    Properties: [[in-place, internal, unstable, offline]]

    ** Optimising quicksort **
    1. Selecting the right pivot is imp for quicksort.
    We can pick a random pivot to mostly avoid getting the worst case
    (choose an index between l and h randomly, and swap with h.
    Then continue the algorithm as usual)
    or,
    We can pick the median of the elements as that will always divide the
    array into equal parts. Median of unsorted array can be found in O(n) time
    (see GFG)
    2. There is a faster parition algo (Hoare's partition) which on average do(es
    three times lesser swaps than the one implemented below (Lomuto's partition).
    (see GFG)

    Special:
    1. Fastest general purpose sorting algorithm
    2. Is cache friendly as it operates over the same array
    3. Is tail recursive, and hence all tail optimisations can be done
    4. Not good for small data sets
*/
void quicksort(vector<int>& arr) {
    quicksortutil(arr, 0, arr.size() - 1);
}

void heapify(vector<int>& arr, int n, int i) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int largest = i;

    if (l < n && arr[l] > arr[largest]) {
        largest = l;
    }

    if (r < n && arr[r] > arr[largest]) {
        largest = r;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

/*
    Heap sort
    ==============
    Logic: Imagine array as a binary heap, which is a complete tree 
    with the heap property that each root is either >= (max heap) or 
    <= (min heap) than its child nodes. Keeping this in mind, we find
    the max in between the i-th node and its left (2i + 1) and right (2i + 2) 
    child node, and if the parent is not the largest, we swap them, and then 
    go down the tree recursively. This causes greater elements to go to the 
    top while maintaing the heap property at each node

    Time Complexity: O(nlog(n)) in all cases;
     - best: in each iteration, pivot divides the array equally
     - average: random order
     - worst: already sorted
    Space Complexity: O(log(n)) due to call stack, O(1) iterative heapify impl.
    Properties: [[in-place, internal, unstable, offline]]
    Heapsort can be made stable as well [see GFG] 

    Special:
    1. Usually 2-3 times slower than well implemented quicksort
    as it has high constant factor and due to lack of locality of reference
*/
void heapsort(vector<int>& arr) {
    int n = arr.size();
    // build heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // extract max and heapify
    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

/*
    C++ STL uses sorting "weapon" called Introsort
    (https://www.geeksforgeeks.org/introsort-cs-sorting-weapon/)

    It starts with quicksort and switches to heapsort if recursion 
    depth goes beyomd a certain limit (to avoid quicksort's O(n^2) case) 
    and finally insertion sort when the number of elements is low
    (<= 16 - decided according to empirical research)
*/

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

    // insertionsort(v);
    // cout << "insertionsort: ";

    // mergesort(v);
    // cout << "mergesort: ";

    // quicksort(v);
    // cout << "quicksort: ";

    // heapsort(v);
    // cout << "heapsort: ";

    printv(v);

    return 0;
}