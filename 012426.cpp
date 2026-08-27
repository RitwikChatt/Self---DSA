#include<bits/stdc++.h>
using namespace std;

vector<vector<string>> possiblePalindromePartitionings;

bool isPalindrome(string s) {
    int n = s.length();
    int l = 0, r = n - 1;
    while(l <= r) {
        if(s[l] != s[r]) {
            return false;
        }
        l++, r--;
    }
    return true;
}

void partitionUtil(string s, vector<string>& palindromes) {
    if(s.empty()) {
        possiblePalindromePartitionings.push_back(palindromes);
        return;
    }
    int n = s.length();
    for(int partition = 1; partition <= n; partition++) {
        string prefix = s.substr(0, partition);
        string remaining = s.substr(partition);
        if(isPalindrome(prefix)) {
            palindromes.push_back(prefix);
            partitionUtil(remaining, palindromes);
            palindromes.pop_back();
        }
    }
}

vector<vector<string>> partition(string s) {
    vector<string> palindromes;
    partitionUtil(s, palindromes);
    return possiblePalindromePartitionings;
}

void partitionArray(vector<int>& arr, int pi) {
    int i = 0, j = 0, n = arr.size();
    while(i < n) {
        if(arr[i] <= pi) {
            swap(arr[i], arr[j]);
            j++;
        }
        i++;
    }
}

void sort012(vector<int>& arr) {
    int n = arr.size();
    int i = 0, j = 0, k = n - 1;
    while(i < k) {
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

void partitionArrayOddEven(vector<int>& arr) {
    int n = arr.size();
    int i = 0, j = 0;
    while(i < n) {
        if(arr[i] & 1) {
            swap(arr[i], arr[j]);
            j++;
        } 
        i++;
    }
}

bool isVowel(char ch) {
    set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
    return vowels.find(ch) != vowels.end();   
}

void sortVowelsConsonants(vector<char>& letters) {
    int n = letters.size();
    int i = 0, j = 0;
    while(i < n) {
        if(isVowel(letters[i])) {
            swap(letters[i], letters[j]);
            j++;
        }
        i++;
    }
}

int partitionArrayAroundPivot(vector<int>& arr, int start, int end) {
    int i = start, j = start;
    int pi = arr[end];
    while(i <= end) {
        if(arr[i] <= pi) {
            swap(arr[i], arr[j]);
            j++;
        }
        i++;
    }
    return j - 1;
}

void quickSort(vector<int>& arr, int start, int end) {
    if(start >= end) {
        return;
    }
    int pivot = partitionArrayAroundPivot(arr, start, end);
    quickSort(arr, start, pivot - 1);
    quickSort(arr, pivot + 1, end);
}

int inversions = 0;

int countInversionsBrute(vector<int>& arr) {
    int n = arr.size();
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(arr[i] > arr[j]) {
                cnt++;
            }
        }
    }
    return cnt;
}

vector<int> mergeSortedArrays(vector<int>& a, vector<int>& b) {
    int n = a.size(), m = b.size();
    int i = 0, j = 0, k = 0;
    vector<int> mergedArray(n + m);
    while(i < n and j < m) {
        if(a[i] <= b[j]) {
            mergedArray[k++] = a[i++];
        } else {
            inversions += n - i;
            mergedArray[k++] = b[j++];
        }
    }
    while(i < n) {
        mergedArray[k++] = a[i++];
    }
    while(j < m) {
        mergedArray[k++] = b[j++];
    }
    return mergedArray;
}

vector<int> mergeSort(vector<int>& arr, int start, int end) {
    if(start == end) {
        return vector<int>{arr[start]};
    }
    int mid = start + (end - start) / 2;
    vector<int> firstHalf = mergeSort(arr, start, mid);
    vector<int> secondHalf = mergeSort(arr, mid + 1, end);
    return mergeSortedArrays(firstHalf, secondHalf);
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
    for(int usi = 0; usi < n - 1; usi++) {
        int minIdx = usi;
        for(int i = usi + 1; i < n; i++) {
            if(arr[i] < arr[minIdx]) {
                minIdx = i;
            }
        }
        swap(arr[minIdx], arr[usi]);
    }
}

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for(int usi = 1; usi < n; usi++) {
        int key = arr[usi], i;
        for(i = usi - 1; i >= 0 and arr[i] > key; i--) {
            arr[i + 1] = arr[i];
        }
        arr[i + 1] = key;
    }
}

vector<vector<string>> allPossiblePalindromePartitions;

void partitionAnotherUtil(string s, vector<string>& palindromePartitions) {
    
}

vector<vector<string>> partitionAnother(string s) {
    vector<string> palindromePartitions;
    partitionAnotherUtil(s, palindromePartitions);
    return allPossiblePalindromePartitions;
}

int main() {
    string s = "abaaba";
    vector<vector<string>> res = partitionAnother(s);
    for(auto x : res) {
        for(auto y : x) {
            cout << y << ' ';
        }
        cout << endl;
    }
    return 0;
}