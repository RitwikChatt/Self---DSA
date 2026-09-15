# Self - DSA

A daily log of Data Structures & Algorithms practice in C++. Each session's work is saved as a single `.cpp` file named after the date it was solved, so the repo doubles as a running journal of what was practiced and when.

## File naming

Files follow an `MMDDYY.cpp` pattern, e.g. [091526.cpp](091526.cpp) was written on September 15, 2026. Files are self-contained — one `#include<bits/stdc++.h>` per file with all helper structures and functions for that day's problems, typically exercised via `main()`.

Compiled binaries (`*.exe`) are build artifacts and are git-ignored, along with `.vscode/`.

## Topics covered

Problems span core interview/competitive-programming DSA topics, including:

- **Arrays & strings** — two pointers, sliding window, prefix sums, sorting
- **Recursion & backtracking**
- **Linked lists**
- **Trees & BSTs** — traversals, balanced BST construction
- **Graphs** — BFS/DFS, Union-Find / Disjoint Set
- **Heaps & priority queues**
- **Dynamic programming** — including string DP (e.g. edit distance)
- **Bit manipulation & bitmasking**
- **Hashing & math**
- **Tries**

## Status

Not every file holds a finished solution — some are skeleton stubs (just `main()`) reserved for a topic that hasn't been tackled yet. This is a personal practice log rather than a curated solutions library, so style and completeness vary day to day.

## Building

Each file builds independently with g++:

```sh
g++ -g <file>.cpp -o <file>.exe
./<file>.exe
```

The repo includes VS Code tasks (`.vscode/tasks.json`) preconfigured to build and debug the currently open file with MinGW `g++`.
