#include <gtest/gtest.h>
#include "BinarySearchTree.h"
#include <sstream>
#include <string>

// =============================================================================
// Helper: capture cout output from a traversal
// =============================================================================
static std::string capture_traversal(BinarySearchTree& bst, char which) {
    std::ostringstream oss;
    std::streambuf* old = std::cout.rdbuf(oss.rdbuf());
    switch (which) {
        case 'i': bst.inorder();   break;
        case 'r': bst.preorder();  break;
        case 'o': bst.postorder(); break;
    }
    std::cout.rdbuf(old);
    return oss.str();
}

// =============================================================================
// Sanity: provided CT15 methods still work
// =============================================================================

TEST(CT15Sanity, InsertAndInorder) {
    BinarySearchTree bst;
    for (int v : {50, 30, 70, 20, 40, 60, 80}) bst.insert(v);
    std::string out = capture_traversal(bst, 'i');
    EXPECT_EQ(out, "20 30 40 50 60 70 80 \n");
}

TEST(CT15Sanity, HeightBalancedTree) {
    BinarySearchTree bst;
    for (int v : {50, 30, 70, 20, 40, 60, 80}) bst.insert(v);
    EXPECT_EQ(bst.height(), 2);
}

// =============================================================================
// Remove — Case 1: leaf
// =============================================================================

TEST(BSTRemove, LeafRemoveReturnsTrue) {
    BinarySearchTree bst;
    for (int v : {50, 30, 70, 20, 40, 60, 80}) bst.insert(v);
    EXPECT_TRUE(bst.remove(20));
}

TEST(BSTRemove, LeafGone) {
    BinarySearchTree bst;
    for (int v : {50, 30, 70, 20, 40, 60, 80}) bst.insert(v);
    bst.remove(20);
    EXPECT_FALSE(bst.search(20));
}

TEST(BSTRemove, LeafOtherNodesIntact) {
    BinarySearchTree bst;
    for (int v : {50, 30, 70, 20, 40, 60, 80}) bst.insert(v);
    bst.remove(20);
    std::string out = capture_traversal(bst, 'i');
    EXPECT_EQ(out, "30 40 50 60 70 80 \n");
}

TEST(BSTRemove, RemoveRootSingleNode) {
    BinarySearchTree bst;
    bst.insert(10);
    EXPECT_TRUE(bst.remove(10));
    EXPECT_TRUE(bst.is_empty());
    EXPECT_EQ(bst.height(), -1);
}

// =============================================================================
// Remove — Case 2: one child
// =============================================================================

TEST(BSTRemove, OneChildRightSubtreeReconnected) {
    BinarySearchTree bst;
    for (int v : {50, 30, 70, 20, 40, 80}) bst.insert(v);
    EXPECT_TRUE(bst.remove(70));
    EXPECT_FALSE(bst.search(70));
    EXPECT_TRUE(bst.search(80));
    std::string out = capture_traversal(bst, 'i');
    EXPECT_EQ(out, "20 30 40 50 80 \n");
}

TEST(BSTRemove, OneChildLeftSubtreeReconnected) {
    BinarySearchTree bst;
    for (int v : {50, 30, 70, 20}) bst.insert(v);
    EXPECT_TRUE(bst.remove(30));
    EXPECT_FALSE(bst.search(30));
    EXPECT_TRUE(bst.search(20));
    std::string out = capture_traversal(bst, 'i');
    EXPECT_EQ(out, "20 50 70 \n");
}

// =============================================================================
// Remove — Case 3: two children
// =============================================================================

TEST(BSTRemove, TwoChildrenInorderSuccessorReplaces) {
    BinarySearchTree bst;
    for (int v : {50, 30, 70, 20, 40, 60, 80}) bst.insert(v);
    EXPECT_TRUE(bst.remove(30));
    EXPECT_FALSE(bst.search(30));
    EXPECT_TRUE(bst.search(40));
    EXPECT_TRUE(bst.search(20));
    std::string out = capture_traversal(bst, 'i');
    EXPECT_EQ(out, "20 40 50 60 70 80 \n");
}

TEST(BSTRemove, TwoChildrenRemoveRoot) {
    BinarySearchTree bst;
    for (int v : {50, 30, 70, 20, 40, 60, 80}) bst.insert(v);
    EXPECT_TRUE(bst.remove(50));
    EXPECT_FALSE(bst.search(50));
    EXPECT_TRUE(bst.search(60));
    std::string out = capture_traversal(bst, 'i');
    EXPECT_EQ(out, "20 30 40 60 70 80 \n");
}

// =============================================================================
// Remove — non-existent value
// =============================================================================

TEST(BSTRemove, NonExistentReturnsFalse) {
    BinarySearchTree bst;
    for (int v : {50, 30, 70}) bst.insert(v);
    EXPECT_FALSE(bst.remove(999));
}

TEST(BSTRemove, NonExistentTreeUnchanged) {
    BinarySearchTree bst;
    for (int v : {50, 30, 70, 20, 40, 60, 80}) bst.insert(v);
    bst.remove(45);
    std::string out = capture_traversal(bst, 'i');
    EXPECT_EQ(out, "20 30 40 50 60 70 80 \n");
}

TEST(BSTRemove, RemoveFromEmptyReturnsFalse) {
    BinarySearchTree bst;
    EXPECT_FALSE(bst.remove(10));
}

// =============================================================================
// Remove — sequential removals
// =============================================================================

TEST(BSTRemove, RemoveAllNodes) {
    BinarySearchTree bst;
    for (int v : {10, 5, 15}) bst.insert(v);
    EXPECT_TRUE(bst.remove(5));
    EXPECT_TRUE(bst.remove(15));
    EXPECT_TRUE(bst.remove(10));
    EXPECT_TRUE(bst.is_empty());
    EXPECT_EQ(bst.height(), -1);
}

TEST(BSTRemove, RemoveMultipleSequential) {
    BinarySearchTree bst;
    for (int v : {50, 30, 70, 20, 40, 60, 80}) bst.insert(v);
    bst.remove(20);
    bst.remove(80);
    bst.remove(50);
    std::string out = capture_traversal(bst, 'i');
    EXPECT_EQ(out, "30 40 60 70 \n");
}

// =============================================================================
// is_empty after remove
// =============================================================================

TEST(BSTRemove, EmptyAfterRemovingOnlyNode) {
    BinarySearchTree bst;
    bst.insert(1);
    bst.remove(1);
    EXPECT_TRUE(bst.is_empty());
}

// =============================================================================
// Degenerate BST — height confirms n-1
// =============================================================================

TEST(BSTDegenerate, SortedInsertionHeight) {
    BinarySearchTree bst;
    for (int v : {1, 2, 3, 4, 5}) bst.insert(v);
    EXPECT_EQ(bst.height(), 4);  // n-1 = 4
}

TEST(BSTDegenerate, SortedInsertionIsStillValidBST) {
    BinarySearchTree bst;
    for (int v : {1, 2, 3, 4, 5}) bst.insert(v);
    std::string out = capture_traversal(bst, 'i');
    EXPECT_EQ(out, "1 2 3 4 5 \n");
}
