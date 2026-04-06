# CT16 -- Binary Search Trees: Day 2 (Remove)

## Overview

An in-class code-together activity implementing the **remove** operation on a Binary Search Tree (BST). Students start with a fully working BST from CT15 (insert, search, traversals, height all provided) and implement `find_min_` and `remove` -- the hardest BST operation. Remove has three distinct cases: removing a leaf, removing a node with one child, and removing a node with two children (using the in-order successor). The session closes with a degenerate BST demo that motivates AVL trees.

## Learning Objectives

- Implement **find_min_** iteratively, understanding it returns the leftmost node (minimum) of any subtree
- Explain why the in-order successor is the **minimum of the right subtree** and why it safely replaces a removed node
- Implement **remove** for Case 1 (leaf): delete the node and return nullptr to the parent
- Implement **remove** for Case 2 (one child): bypass the node by returning its only child to the parent
- Implement **remove** for Case 3 (two children): copy the in-order successor's value, then recursively delete the successor
- Demonstrate the **degenerate BST** produced by sorted insertion and explain why it motivates AVL trees

## Project Structure

```
ct16-bst-remove/
├── CMakeLists.txt
├── assignment.json
├── README.md
├── include/
│   └── BinarySearchTree.h      # Node struct + class declaration
├── src/
│   ├── BinarySearchTree.cpp    # CT15 methods provided; find_min_ and remove_ are TODOs
│   └── main.cpp                # Demo: find_min_, remove all 3 cases, degenerate BST
├── tests/
│   └── ct16_test.cpp           # Google Test suite
└── images/
    ├── remove_cases.png         # All three remove cases side by side
    └── degenerate_bst.png       # Sorted insertion creating a right spine
```

## What You'll Do

Open `BinarySearchTree.cpp` -- CT15 methods are already implemented and ready to use. Your two tasks today are `find_min_` (Section 7) and `remove_` (Section 8). After implementing each, use `main.cpp` to test your output. The session ends with the degenerate BST demo: insert 1, 2, 3, 4, 5 in order, observe a height of 4 (= n-1), and discuss why this motivates AVL trees.

## Files

| File | Focus | TODOs |
|---|---|---|
| `BinarySearchTree.cpp` | find_min_ and remove_ | 2 (find_min_ body, remove_ body) |
| `main.cpp` | Demo: find_min_, 3 remove cases, degenerate BST | 0 (run as-is to verify output) |

## Teaching Order

### 1. `BinarySearchTree.h` -- Review interface additions

Walk through the header changes from CT15: `remove()` is now public, `find_min_()` and `remove_()` are now private helpers. Remind students of the `bool& removed` output parameter pattern.

### 2. `BinarySearchTree.cpp` -- Two TODOs

1. **Section 7: find_min_** -- iterative leftmost walk; used internally by remove_
2. **Section 8: remove / remove_** -- three cases: leaf (delete, return nullptr), one child (bypass), two children (copy successor, delete successor)

### 3. `main.cpp` -- Demo driver (5 sections)

1. **Section 1: Build and verify** -- insert 50, 30, 70, 20, 40, 60, 80; print in-order and height from CT15
2. **Section 2: Remove Case 1** -- remove leaf (20); show in-order before/after
3. **Section 3: Remove Case 2** -- insert 65, remove 60 (one child); show bypass
4. **Section 4: Remove Case 3** -- re-insert 20, 25; remove 30 (two children); show in-order successor
5. **Section 5: Degenerate BST** -- insert 1..5 sorted; height = 4 = n-1; AVL motivation

## Diagrams

| File | Description |
|---|---|
| `images/remove_cases.png` | All three remove cases side by side with before/after pointers |
| `images/degenerate_bst.png` | Inserting 1, 2, 3, 4, 5 in order forming a right-spine linked list |

## Grading (30 points)

| Category | Points | What is tested |
|---|---|---|
| Build | 0 | Project must compile (tests won't run otherwise) |
| find_min_ (via remove) | 10 | Correct in-order successor selection in two-children case |
| Remove Case 1 -- leaf | 8 | Leaf removed, tree unchanged otherwise, returns true/false correctly |
| Remove Case 2 -- one child | 6 | Bypassed correctly for left-child and right-child variants |
| Remove Case 3 -- two children | 6 | In-order successor replaces node; successor deleted; tree valid BST |
