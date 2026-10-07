# Self - DSA

A daily log of Data Structures & Algorithms practice in C++. Each session's work is saved as a single `.cpp` file named after the date it was solved, so the repo doubles as a running journal of what was practiced and when.

## File naming

Files follow an `MMDDYY.cpp` pattern, e.g. [100726.cpp](100726.cpp) was written on October 7, 2026. Files are self-contained — one `#include<bits/stdc++.h>` per file with all helper structures and functions for that day's problems, typically exercised via `main()`.

Compiled binaries (`*.exe`) are build artifacts and are git-ignored, along with `.vscode/`.

## Topics covered

Problems span core interview/competitive-programming DSA topics, including:

- **Arrays & strings** — two pointers, sliding window, prefix sums, sorting
- **Recursion & backtracking**
- **Linked lists**
- **Trees & BSTs** — traversals, balanced BST construction
- **Graphs** — BFS/DFS, Union-Find / Disjoint Set
- **Heaps & priority queues**
- **Dynamic programming** — including string DP (e.g. edit distance), path DP (e.g. min side jumps), unbounded knapsack / rod cutting, and the LCS family (longest common subsequence/substring, shortest common supersequence, min insertions/deletions), distinct subsequences, wildcard matching, and stock buy/sell (up to k transactions), with both 2D and space-optimised 1D variants
- **Fenwick Tree (BIT) & Segment Tree** — range sum/max queries and updates
- **Bit manipulation & bitmasking**
- **Hashing & math**
- **Tries**

## Status

Not every file holds a finished solution — some are skeleton stubs (just `main()`) reserved for a topic that hasn't been tackled yet, and a few have a function left unimplemented (e.g. `cutRod` in [092826.cpp](092826.cpp), `numDistinct` in [100626.cpp](100626.cpp), later implemented in [100726.cpp](100726.cpp)). This is a personal practice log rather than a curated solutions library, so style and completeness vary day to day.

## Building

Each file builds independently with g++:

```sh
g++ -g <file>.cpp -o <file>.exe
./<file>.exe
```

The repo includes VS Code tasks (`.vscode/tasks.json`) preconfigured to build and debug the currently open file with MinGW `g++`.
