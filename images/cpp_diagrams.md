# CT16 -- Implementation Diagrams

Code-block diagrams referenced from `BinarySearchTree.cpp`.

---

## 1. find_min_() Implementation
*`BinarySearchTree.cpp::find_min_()` -- iterative loop walks left until no left child*

![find_min_ Implementation](svgs/find_min_impl.svg)

---

## 2. remove() -- Public Wrapper
*`BinarySearchTree.cpp::remove()` -- sets up the call, delegates to recursive remove_()*

![remove() Wrapper](svgs/remove_wrapper.svg)

---

## 3. remove_() -- Function Signature
*`BinarySearchTree.cpp::remove_()` -- what each parameter means and why it returns Node\**

![remove_() Signature](svgs/remove_signature.svg)

---

## 4. remove_() -- Finding the Node
*`BinarySearchTree.cpp::remove_()` -- recursive search: go left, go right, or found it*

![remove_() Find Node](svgs/remove_find_node.svg)

---

## 5. remove_() Case 1 -- Leaf Node
*`BinarySearchTree.cpp::remove_()` -- no children: delete node, return nullptr*

![Remove Case 1: Leaf](svgs/remove_case1_impl.svg)

---

## 6. remove_() Case 2a -- Only a Right Child
*`BinarySearchTree.cpp::remove_()` -- no left child: save right child, delete node, return right child*

![Remove Case 2a: Right Child](svgs/remove_case2a_impl.svg)

---

## 7. remove_() Case 2b -- Only a Left Child
*`BinarySearchTree.cpp::remove_()` -- no right child: save left child, delete node, return left child*

![Remove Case 2b: Left Child](svgs/remove_case2b_impl.svg)

---

## 8. remove_() Case 3 -- Two Children (Steps 1 & 2)
*`BinarySearchTree.cpp::remove_()` -- find the in-order successor, copy its value into the node*

![Remove Case 3: Steps 1 & 2](svgs/remove_case3_impl.svg)

---

## 9. remove_() Case 3 -- Two Children (Step 3 & Result)
*`BinarySearchTree.cpp::remove_()` -- delete the original successor, final tree*

![Remove Case 3: Step 3 & Result](svgs/remove_case3_impl_pt2.svg)
