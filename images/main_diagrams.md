# CT16 -- Main Demo Diagrams

Visual walkthrough of the tree states in `main.cpp`.

---

## 1. Build the Tree
*`main.cpp` Section 1 -- insert 50, 30, 70, 20, 40, 60, 80*

![Section 1: Build Tree](svgs/main_section1.svg)

---

## 2. Remove 20 (Case 1 -- Leaf)
*`main.cpp` Section 2 -- 20 has no children, just delete it*

![Section 2: Remove 20](svgs/main_section2.svg)

---

## 3. Remove 60 (Case 2 -- One Child)
*`main.cpp` Section 3 -- insert 65, then remove 60 (only child is 65)*

![Section 3: Remove 60](svgs/main_section3.svg)

---

## 4. Remove 30 (Case 3 -- Two Children)
*`main.cpp` Section 4 -- insert 20 and 25, then remove 30 (successor is 40)*

![Section 4: Remove 30](svgs/main_section4.svg)

---

## 5. Degenerate BST
*`main.cpp` Section 5 -- sorted insertion creates a linked list, motivates AVL trees*

![Section 5: Degenerate BST](svgs/main_section5.svg)
