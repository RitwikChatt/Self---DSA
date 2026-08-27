#include<bits/stdc++.h>
using namespace std;

void partitionArrayInTwoParts(vector<int>& arr, int pi) {
    int n = arr.size();
    int i = 0, j = 0;
    while(i < n) {
        if(arr[i] <= pi) {
            swap(arr[i], arr[j]);
            i++, j++;
        } else {
            i++;
        }
    }
}

void partitionArrayInThreeParts(vector<int>& arr) {
    int n = arr.size();
    int i = 0, j = 0, k = n - 1;
    while(i <= k) {
        if(arr[i] == 0) {
            swap(arr[i], arr[j]);
            i++, j++;
        } else if(arr[i] == 1) {
            i++;
        } else {
            swap(arr[i], arr[k]);
            k--;
        }
    }
}

int partition(vector<int>& arr, int start, int end) {
    int pivot = arr[end];
    int i = start, j = start;
    while(i <= end) {
        if(arr[i] <= pivot) {
            swap(arr[i], arr[j]);
            i++, j++;
        } else {
            i++;
        }
    }
    return j - 1;
}

void quickSort(vector<int>& arr, int start, int end) {
    if(start >= end) {
        return;
    }
    int pi = partition(arr, start, end);
    quickSort(arr, start, pi - 1);
    quickSort(arr, pi + 1, end);
}

void sortABC(vector<char>& abc) {
    int n = abc.size();
    int i = 0, j = 0, k = n - 1;
    while(i <= k) {
        if(abc[i] == 'a') {
            swap(abc[i], abc[j]);
            i++, j++;
        } else if(abc[i] == 'b') {
            i++;
        } else {
            swap(abc[i], abc[k]);
            k--;
        }
    }
}

int main() {
    
    return 0;
}