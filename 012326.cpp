#include<bits/stdc++.h>
using namespace std;

int inversions = 0;

vector<int> merge(vector<int>& a, vector<int>& b) {
    int n = a.size(), m = b.size();
    int i = 0, j = 0, k = 0;
    vector<int> res(n + m);
    while(i < n and j < m) {
        if(a[i] <= b[j]) {
            res[k++] = a[i++];
        } else {
            res[k++] = b[j++];
            inversions += n - i;
        }
    }
    while(i < n) {
        res[k++] = a[i++];
    } 
    while(j < m) {
        res[k++] = b[j++];
    }
    return res;
}

vector<int> mergeSort(vector<int>& arr, int start, int end) {
    if(start == end) {
        return vector<int>{arr[start]};
    }
    int mid = start + (end - start) / 2;
    vector<int> firstHalf = mergeSort(arr, start, mid);
    vector<int> secondHalf = mergeSort(arr, mid + 1, end);
    return merge(firstHalf, secondHalf);
}

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for(int pass = 1; pass < n; pass++) {
        bool swapped = false;
        for(int i = 0; i < n - pass; i++) {
            if(arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        if(!swapped) {
            return;
        }
    }
}

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for(int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for(int j = i + 1; j < n; j++) {
            if(arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for(int i = 1; i < n; i++) {
        int key = arr[i], j;
        for(j = i - 1; j >= 0 and arr[j] > key; j--) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = key;
    }
}

int main() {
    vector<int> arr = {2, 7, 15, 3, 1, -3, 10};
    insertionSort(arr);
    for(auto it : arr) {
        cout << it << ' ';
    }
    return 0;
}