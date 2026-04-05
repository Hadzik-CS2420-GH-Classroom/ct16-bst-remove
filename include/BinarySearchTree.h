#pragma once
#include <iostream>
#include <algorithm>  // std::max

// =============================================================================
// CT16: Binary Search Trees — Day 2 (Remove)
// =============================================================================
//
// A Binary Search Tree (BST) is a linked structure where every node obeys
// the BST property:
//   - all values in the LEFT subtree are LESS than the node's value
//   - all values in the RIGHT subtree are GREATER than the node's value
//
// In CT15 you implemented insert, search, traversals, and height.
// In CT16 you implement the hardest operation: remove.
//

// -----------------------------------------------------------------------------
// Node — the building block of the BST
// -----------------------------------------------------------------------------
struct Node {
    int   data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// -----------------------------------------------------------------------------
// BinarySearchTree — manages a tree of Node objects
// -----------------------------------------------------------------------------
class BinarySearchTree {
public:
    // -------------------------------------------------------------------------
    // Constructor / Destructor  [CT15 — provided, already implemented]
    // -------------------------------------------------------------------------

    /// Constructs an empty BST (root_ = nullptr).
    BinarySearchTree();

    /// Destroys the entire tree, freeing all heap-allocated nodes.
    ~BinarySearchTree();

    // -------------------------------------------------------------------------
    // insert  [CT15 — provided, already implemented]
    // -------------------------------------------------------------------------

    /// Inserts value into the BST. Duplicates are silently ignored.
    void insert(int value);

    // -------------------------------------------------------------------------
    // remove  [CT16 — NEW]
    // -------------------------------------------------------------------------
    //
    // ? SEE DIAGRAM: images/header_diagrams.md #1 — why we need find_min_
    // ? SEE DIAGRAM: images/header_diagrams.md #3 — three remove cases at a glance
    //
    // ! DISCUSSION: BST remove — the hardest BST operation.
    //   - Returns true if the value was found and removed, false otherwise
    //   - Three cases depending on the node's children:
    //
    //   Case 1 — LEAF (no children):
    //     - Simply delete the node, return nullptr to the parent
    //
    //   Case 2 — ONE CHILD:
    //     - Replace the node with its only child
    //     - The child "moves up" to take the deleted node's spot
    //
    //   Case 3 — TWO CHILDREN:
    //     - Find the IN-ORDER SUCCESSOR (smallest node in right subtree)
    //     - Copy the successor's data into this node
    //     - Recursively remove the successor from the right subtree
    //     - This preserves the BST property because the successor is the
    //       smallest value that is still greater than everything on the left
    //
    // Time: O(log n) average, O(n) worst (degenerate tree)

    bool remove(int value);

    // -------------------------------------------------------------------------
    // search  [CT15 — provided, already implemented]
    // -------------------------------------------------------------------------

    /// Returns true if value exists in the BST, false otherwise.
    bool search(int value) const;

    // -------------------------------------------------------------------------
    // height  [CT15 — provided, already implemented]
    // -------------------------------------------------------------------------

    /// Returns the height of the tree.
    /// An empty tree has height -1. A single-node tree has height 0.
    int height() const;

    // -------------------------------------------------------------------------
    // is_empty  [CT15 — provided, already implemented]
    // -------------------------------------------------------------------------

    /// Returns true if the tree contains no nodes.
    bool is_empty() const;

    // -------------------------------------------------------------------------
    // Traversals  [CT15 — provided, already implemented]
    // -------------------------------------------------------------------------

    /// In-order traversal: Left → Root → Right. Produces sorted output.
    void inorder() const;

    /// Pre-order traversal: Root → Left → Right.
    void preorder() const;

    /// Post-order traversal: Left → Right → Root.
    void postorder() const;

private:
    Node* root_;

    // -------------------------------------------------------------------------
    // insert_  [CT15 — provided, already implemented]
    // -------------------------------------------------------------------------
    Node* insert_(Node* node, int value);

    // -------------------------------------------------------------------------
    // search_  [CT15 — provided, already implemented]
    // -------------------------------------------------------------------------
    bool search_(Node* node, int value) const;

    // -------------------------------------------------------------------------
    // find_min_  [CT16 — NEW / TODO]
    // -------------------------------------------------------------------------
    //
    // ? SEE DIAGRAM: images/header_diagrams.md #2 — find_min_ walks left to the minimum
    //
    // ! DISCUSSION: Find the minimum value in a subtree.
    //   - The minimum is always the leftmost node — keep going left
    //   - Used by remove to find the in-order successor (find_min_ of right subtree)
    //   - Iterative: just follow left pointers until left is nullptr
    //   - Returns a pointer to the leftmost node

    Node* find_min_(Node* node) const;

    // -------------------------------------------------------------------------
    // remove_  [CT16 — NEW / TODO]
    // -------------------------------------------------------------------------
    //
    // ? SEE DIAGRAM: images/cpp_diagrams.md #2-5 — all three remove cases with code
    //
    // ! DISCUSSION: Recursive remove.
    //   - Returns the (possibly changed) root of the subtree
    //   - removed is set to true if the value was found and deleted
    //   - Handle the three cases: leaf, one child, two children

    Node* remove_(Node* node, int value, bool& removed);

    // -------------------------------------------------------------------------
    // Traversal & utility helpers  [CT15 — provided, already implemented]
    // -------------------------------------------------------------------------
    void inorder_(Node* node) const;
    void preorder_(Node* node) const;
    void postorder_(Node* node) const;
    int height_(Node* node) const;
    void destroy_(Node* node);
};
