# patient-records-bst

Console-based C++ app for storing and managing patient records using a Binary Search Tree (BST).

## What it does
- Add patients (name, phone, id)
- Delete them by ID
- Search by ID
- Show all patients in preorder / inorder / postorder
- Validates input so you can't completely mess it up
- Option to wipe the whole tree before exiting

## How it works
It’s a basic BST where each node is a patient record.  
IDs determine where nodes go in the tree.  
Insert, delete, search are all the usual `O(log n)` on average (unless you make it a stick with sorted inserts).

## Requirements
- C++11 or newer
- Works on Linux, macOS, and Windows (no platform-specific code)

## Build
g++ -std=c++11 main.cpp -o patient_records_bst
./patient_records_bst

Notes

Phone number must start with 09 and be exactly 10 digits.

If you insert IDs in sorted order (like 1, 2, 3…), your tree will become a glorified linked list.

License

For educational purposes.
