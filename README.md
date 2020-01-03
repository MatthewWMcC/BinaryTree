# BinaryTree
The primary file used here is expr.c. This file has functions that create and manipulate binary trees that manipulate mathematical expressions. This program uses pointers and linked lists to join nodes.

To run the program simply compile and execute the mainexpr.c file. This file holds commands to create a series of binary trees and
print their contents however it can be edited to create different trees.

The functions in this program have been fully optimized so that they have no memory leaks using valgrind.

The program allows you to: Join strings, Create nodes, Join nodes using mathematical operations, Evaluate the binary tree so that the root node contains the algebraic expression made up of the leaf nodes, Duplicate the binary tree, Print the bianry tree, Free the binary tree.

An expr.h file is included which outlines the node struct that will be used throughout expr.c.
