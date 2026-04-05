# CT16 -- Implementation Diagrams

Code-block diagrams referenced from `BinarySearchTree.cpp`.

---

## 1. find_min_() Implementation
*`BinarySearchTree.cpp::find_min_()` -- iterative loop walks left until no left child*

![find_min_ Implementation](svgs/find_min_impl.svg)

---

## 2. remove_() Case 1 -- Leaf Node
*`BinarySearchTree.cpp::remove_()` -- no children: delete node, return nullptr*

![Remove Case 1: Leaf](svgs/remove_case1_impl.svg)

---

## 3. remove_() Case 2 -- One Child
*`BinarySearchTree.cpp::remove_()` -- bypass the node, return its only child*

![Remove Case 2: One Child](svgs/remove_case2_impl.svg)

---

## 4. remove_() Case 3 -- Two Children (Steps 1 & 2)
*`BinarySearchTree.cpp::remove_()` -- find the in-order successor, copy its value into the node*

![Remove Case 3: Steps 1 & 2](svgs/remove_case3_impl.svg)

---

## 5. remove_() Case 3 -- Two Children (Step 3 & Result)
*`BinarySearchTree.cpp::remove_()` -- delete the original successor, final tree*

![Remove Case 3: Step 3 & Result](svgs/remove_case3_impl_pt2.svg)
