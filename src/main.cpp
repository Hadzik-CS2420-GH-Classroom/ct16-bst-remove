// =============================================================================
// CT15: Binary Search Tree — Day 2 (Remove) — Demo Driver
// =============================================================================
//
// This demo builds on CT14. The BST (insert, search, traversals, height)
// is already working. Today we implement find_min_ and remove.
//
// Tree used (insert order: 50, 30, 70, 20, 40, 60, 80):
//
//              50
//            /    \
//          30      70
//         /  \    /  \
//        20  40  60   80
//

#include "BinarySearchTree.h"
#include <iostream>
#include <cmath>   // std::log2

int main() {

    // =============================================================================
    // Section 1: find_min_ demo
    // =============================================================================
    //
    // ! DISCUSSION: find_min_ walks left until there is no left child.
    //   - the leftmost node of ANY subtree is its minimum value
    //   - we use this in remove to find the in-order successor:
    //     the minimum of the RIGHT subtree is the next-larger value
    //   - example: for the tree below, find_min_(root) = 20
    //     find_min_(root->right) = 60 — that is 50's in-order successor
    //
    std::cout << "=== Section 1: Build tree and verify find_min_ ===" << std::endl;

    BinarySearchTree bst;
    for (int v : {50, 30, 70, 20, 40, 60, 80}) bst.insert(v);

    std::cout << "Tree: 50, 30, 70, 20, 40, 60, 80" << std::endl;
    std::cout << "In-order (verify tree): ";
    bst.inorder();   // 20 30 40 50 60 70 80
    std::cout << "Height: " << bst.height() << std::endl;  // 2
    std::cout << std::endl;

    // =============================================================================
    // Section 2: Remove — All Three Cases
    // =============================================================================
    //
    // ! DISCUSSION: Remove has three cases — complexity increases with children.
    //   - Case 1 (leaf):        just unlink and delete
    //   - Case 2 (one child):   bypass the node, reconnect child to grandparent
    //   - Case 3 (two children): copy in-order successor value, delete successor
    //
    std::cout << "=== Section 2: Remove — Case 1 (leaf) ===" << std::endl;

    // --- Case 1: Remove a leaf (20) ---
    //
    // ! DISCUSSION: 20 is a leaf — no children.
    //   - simply delete the node and set its parent's left pointer to nullptr
    //   - the tree shrinks by one node; everything else is unchanged
    //
    std::cout << "Remove 20 (leaf):" << std::endl;
    std::cout << "  remove(20) returned: " << (bst.remove(20) ? "true" : "false") << std::endl;
    std::cout << "  In-order after: ";
    bst.inorder();  // expected: 30 40 50 60 70 80
    std::cout << std::endl;

    // =============================================================================
    // Section 3: Remove — Case 2 (one child)
    // =============================================================================

    // --- Case 2: Remove a node with one child ---
    //
    // ! DISCUSSION: Insert 65 to give 60 a right child, then remove 60.
    //   - 60 has no left child; its only child is 65
    //   - we bypass 60: 70's left pointer now points directly to 65
    //   - 65 is reconnected; 60 is deleted
    //
    std::cout << "=== Section 3: Remove — Case 2 (one child) ===" << std::endl;

    bst.insert(65);
    std::cout << "Inserted 65 (gives 60 a right child)." << std::endl;
    std::cout << "In-order: ";
    bst.inorder();  // expected: 30 40 50 60 65 70 80

    std::cout << "\nRemove 60 (one child — 65):" << std::endl;
    std::cout << "  remove(60) returned: " << (bst.remove(60) ? "true" : "false") << std::endl;
    std::cout << "  In-order after: ";
    bst.inorder();  // expected: 30 40 50 65 70 80
    std::cout << std::endl;

    // =============================================================================
    // Section 4: Remove — Case 3 (two children) + Degenerate BST motivation
    // =============================================================================

    // --- Case 3: Remove a node with two children ---
    //
    // ! DISCUSSION: Re-insert 20 and 25 to give 30 two children.
    //   - 30 has left child (subtree rooted at 20) and right child (40)
    //   - in-order successor = minimum of right subtree = 40
    //   - copy 40 into the node where 30 was
    //   - delete 40 from the right subtree (it's a leaf there, Case 1)
    //   - result: node formerly holding 30 now holds 40; tree is still valid BST
    //
    std::cout << "=== Section 4: Remove — Case 3 (two children) ===" << std::endl;

    bst.insert(20);
    bst.insert(25);
    std::cout << "Inserted 20 and 25 (gives 30 two children: 20 and 40)." << std::endl;
    std::cout << "In-order: ";
    bst.inorder();  // expected: 20 25 30 40 50 65 70 80

    std::cout << "\nRemove 30 (two children — in-order successor is 40):" << std::endl;
    std::cout << "  remove(30) returned: " << (bst.remove(30) ? "true" : "false") << std::endl;
    std::cout << "  In-order after: ";
    bst.inorder();  // expected: 20 25 40 50 65 70 80

    std::cout << "\nRemove 999 (not in tree — returns false):" << std::endl;
    std::cout << "  remove(999) returned: " << (bst.remove(999) ? "true" : "false") << std::endl;
    std::cout << std::endl;

    // =============================================================================
    // Section 5: Degenerate BST — motivates AVL trees
    // =============================================================================
    //
    // ! DISCUSSION: Sorted insertion creates a right-spine — a degenerate tree.
    //   - inserting 1, 2, 3, 4, 5 in order: each new value is larger than all
    //     existing values, so it always goes to the far right
    //   - the tree becomes a linked list leaning right
    //   - height = n - 1 = 4 for 5 nodes
    //   - search/insert/remove are now O(n) — no better than a linked list!
    //
    // ? SEE DIAGRAM: images/degenerate_bst.png — sorted insertion creating a right spine
    //
    // ! DISCUSSION: This motivates AVL trees.
    //   - AVL trees detect imbalance after every insert/remove
    //   - they perform rotations to keep the tree balanced
    //   - guaranteed height ≈ log2(n), so all operations stay O(log n)
    //
    std::cout << "=== Section 5: Degenerate BST ===" << std::endl;

    BinarySearchTree degen;
    for (int v : {1, 2, 3, 4, 5}) {
        degen.insert(v);
    }

    std::cout << "Inserted 1, 2, 3, 4, 5 in sorted order." << std::endl;
    std::cout << "In-order: ";
    degen.inorder();  // 1 2 3 4 5
    std::cout << "Height: " << degen.height()
              << "  (expected " << 5 - 1 << " — equals n-1, not log2(n)!)" << std::endl;
    std::cout << std::endl;

    std::cout << "A balanced 5-node BST would have height "
              << static_cast<int>(std::log2(5)) << "." << std::endl;
    std::cout << "This degenerate tree is " << degen.height() << " levels deep." << std::endl;
    std::cout << "=> Next topic: AVL trees maintain balance automatically." << std::endl;

    return 0;
}
