#pragma once
#include <iostream>
#include <algorithm>  // std::max

// =============================================================================
// CT15: Binary Search Trees — Day 2 (Remove)
// =============================================================================
//
// A Binary Search Tree (BST) is a linked structure where every node obeys
// the BST property:
//   - all values in the LEFT subtree are LESS than the node's value
//   - all values in the RIGHT subtree are GREATER than the node's value
//
// In CT14 you implemented insert, search, traversals, and height.
// In CT15 you implement the hardest operation: remove.
//
// ? SEE DIAGRAM: images/bst_property.png — BST property: left < parent < right
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
    // Constructor / Destructor
    // -------------------------------------------------------------------------

    /// Constructs an empty BST (root_ = nullptr).
    BinarySearchTree();

    /// Destroys the entire tree, freeing all heap-allocated nodes.
    ~BinarySearchTree();

    // -------------------------------------------------------------------------
    // Modifiers
    // -------------------------------------------------------------------------

    /// Inserts value into the BST. Duplicates are silently ignored.
    void insert(int value);

    /// Removes value from the BST.
    /// Returns true if the value was found and removed, false if not found.
    /// Handles three cases: leaf, one child, two children (in-order successor).
    bool remove(int value);

    // -------------------------------------------------------------------------
    // Queries
    // -------------------------------------------------------------------------

    /// Returns true if value exists in the BST, false otherwise.
    bool search(int value) const;

    /// Returns the height of the tree.
    /// An empty tree has height -1. A single-node tree has height 0.
    int height() const;

    /// Returns true if the tree contains no nodes.
    bool is_empty() const;

    // -------------------------------------------------------------------------
    // Traversals
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
    // Private recursive helpers
    // -------------------------------------------------------------------------

    Node* insert_(Node* node, int value);
    bool search_(Node* node, int value) const;

    // ? SEE DIAGRAM: images/header_diagrams.md #1 — find_min_ walks left to the minimum
    //
    /// Returns pointer to the node with the minimum value in the subtree.
    /// The minimum is always the leftmost node.
    /// Used by remove_ to locate the in-order successor.
    Node* find_min_(Node* node) const;

    // ? SEE DIAGRAM: images/header_diagrams.md #2 — three remove cases at a glance
    //
    /// Recursively removes value from the subtree rooted at node.
    /// Sets removed = true when the value is found and deleted.
    /// Returns the (possibly changed) root of the subtree.
    Node* remove_(Node* node, int value, bool& removed);

    void inorder_(Node* node) const;
    void preorder_(Node* node) const;
    void postorder_(Node* node) const;
    int height_(Node* node) const;
    void destroy_(Node* node);
};
