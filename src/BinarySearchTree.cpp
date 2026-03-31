// =============================================================================
// CT15: Binary Search Tree — Day 2 (Remove)
// =============================================================================
//
// CT14 methods (constructor, insert, search, traversals, height) are provided
// and fully implemented — students can use them from the start of class.
//
// Today's focus: find_min_ and remove (all three cases).
//

#include "BinarySearchTree.h"
#include <iostream>

// =============================================================================
// 1. Constructor / Destructor  [PROVIDED — from CT14]
// =============================================================================

BinarySearchTree::BinarySearchTree() : root_(nullptr) {}

BinarySearchTree::~BinarySearchTree() {
    destroy_(root_);
}

void BinarySearchTree::destroy_(Node* node) {
    if (!node) return;
    destroy_(node->left);
    destroy_(node->right);
    delete node;
}

// =============================================================================
// 2. insert / insert_  [PROVIDED — from CT14]
// =============================================================================

void BinarySearchTree::insert(int value) {
    root_ = insert_(root_, value);
}

Node* BinarySearchTree::insert_(Node* node, int value) {
    if (!node) return new Node(value);

    if (value < node->data) {
        node->left = insert_(node->left, value);
    } else if (value > node->data) {
        node->right = insert_(node->right, value);
    }

    return node;
}

// =============================================================================
// 3. search / search_  [PROVIDED — from CT14]
// =============================================================================

bool BinarySearchTree::search(int value) const {
    return search_(root_, value);
}

bool BinarySearchTree::search_(Node* node, int value) const {
    if (!node) return false;
    if (value == node->data) return true;
    if (value < node->data) {
        return search_(node->left, value);
    } else {
        return search_(node->right, value);
    }
}

// =============================================================================
// 4. Traversals  [PROVIDED — from CT14]
// =============================================================================

void BinarySearchTree::inorder() const {
    inorder_(root_);
    std::cout << std::endl;
}

void BinarySearchTree::inorder_(Node* node) const {
    if (!node) return;
    inorder_(node->left);
    std::cout << node->data << " ";
    inorder_(node->right);
}

void BinarySearchTree::preorder() const {
    preorder_(root_);
    std::cout << std::endl;
}

void BinarySearchTree::preorder_(Node* node) const {
    if (!node) return;
    std::cout << node->data << " ";
    preorder_(node->left);
    preorder_(node->right);
}

void BinarySearchTree::postorder() const {
    postorder_(root_);
    std::cout << std::endl;
}

void BinarySearchTree::postorder_(Node* node) const {
    if (!node) return;
    postorder_(node->left);
    postorder_(node->right);
    std::cout << node->data << " ";
}

// =============================================================================
// 5. height / height_  [PROVIDED — from CT14]
// =============================================================================

int BinarySearchTree::height() const {
    return height_(root_);
}

int BinarySearchTree::height_(Node* node) const {
    if (!node) return -1;
    return 1 + std::max(height_(node->left), height_(node->right));
}

// =============================================================================
// 6. is_empty  [PROVIDED — from CT14]
// =============================================================================

bool BinarySearchTree::is_empty() const {
    return root_ == nullptr;
}

// =============================================================================
// 7. find_min_
// =============================================================================

// ---------------------------------------------------------------------------
// find_min_() — return the leftmost node in a subtree
// ---------------------------------------------------------------------------
//
// ! DISCUSSION: The minimum of any subtree is its leftmost node.
//   - by the BST property, smaller values always go left
//   - keep walking left until there is no left child
//   - this node has no smaller value in its subtree
//   - find_min_ is used by remove_ to locate the in-order successor
//
Node* BinarySearchTree::find_min_(Node* node) const {
    // Walk left until we can't go further
    while (node->left) {
        node = node->left;
    }
    return node;
}

// =============================================================================
// 8. remove / remove_
// =============================================================================

// ---------------------------------------------------------------------------
// remove() — public wrapper
// ---------------------------------------------------------------------------
bool BinarySearchTree::remove(int value) {
    bool removed = false;
    root_ = remove_(root_, value, removed);
    return removed;
}

// ---------------------------------------------------------------------------
// remove_() — recursive remove (three cases)
// ---------------------------------------------------------------------------
//
// ? SEE DIAGRAM: images/cpp_diagrams.md #2-4 — all three remove cases with code
//
// ! DISCUSSION: Removing a node has three cases based on its children.
//   - Case 1 — leaf (no children): simply delete it, return nullptr to parent
//   - Case 2 — one child: bypass the node, return its only child to parent
//   - Case 3 — two children: the tricky case — see below
//
// ! DISCUSSION: Case 3 — two children — the key insight.
//   - we cannot just delete the node; it has two subtrees to preserve
//   - solution: find the in-order successor (minimum of the RIGHT subtree)
//   - the successor is the smallest value that is still LARGER than node->data
//   - copy the successor's value into the current node (no pointer changes)
//   - then delete the successor from the right subtree (it has at most one child)
//   - the BST property is maintained throughout
//
Node* BinarySearchTree::remove_(Node* node, int value, bool& removed) {
    // Base case: value not in the tree
    if (!node) return nullptr;

    if (value < node->data) {
        node->left = remove_(node->left, value, removed);
    } else if (value > node->data) {
        node->right = remove_(node->right, value, removed);
    } else {
        // Found the node to remove
        removed = true;

        // ------------------------------------
        // Case 1: Leaf node — no children
        // ------------------------------------
        if (!node->left && !node->right) {
            delete node;
            return nullptr;
        }

        // ------------------------------------
        // Case 2: One child
        // ------------------------------------
        if (!node->left) {
            Node* successor = node->right;
            delete node;
            return successor;
        }
        if (!node->right) {
            Node* predecessor = node->left;
            delete node;
            return predecessor;
        }

        // ------------------------------------
        // Case 3: Two children — in-order successor
        // ------------------------------------
        Node* successor = find_min_(node->right);
        node->data = successor->data;

        bool dummy = false;
        node->right = remove_(node->right, successor->data, dummy);
    }

    return node;
}
