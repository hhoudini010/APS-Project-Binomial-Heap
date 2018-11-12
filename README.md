# APS-Project-Binomial-Heap
Implementing Binomial Heap with one application and comparing the Heap operations with the AVL Tree
So the main aim of this project was to implement all the operations of a Binomial Heap like insert,delete,merge etc. and then compare the running time of these operations when the same operations is being performed on AVL Trees as well.
This project also invloves creating one application where Binomial Heaps can be used.

## Getting Started
The following instruction will help you how to copy and run the project on your local machine for testing purposes.

### Steps to Run the programs.
#### 1. AVL tree 
To compile, type the command `g++ -std=c++11 AVL.cpp -o avl` <br />
To execute, type `./avl`
To run 
#### 2. Binomial heap
To compile, type the command `g++ -std=c++11 binomial1.cpp -o binomial` <br />
To execute, type `./binomial`

#### 3. Dijkstra's Algorithm
To compile, type the command `g++ -std=c++11 dij.cpp -o dij` <br />
To execute, type `./dij`

### AVL Tree
AVL Tree will contain only unique values.
On successful compiltation, the program will have a menu driven functionality in which the user needs to enter which functionality he/she needs to perform.
#### AVL Operations are as follows
##### 1. Insert
  On selecting this operation the user needs to first enter the number of nodes he/she needs to insert into the AVL Tree and then accordingly enter the node's value to be inserted in the AVL Tree.

##### 2.)Display
  It display the AVL Tree in InOrder fashion.

##### 3.)Delete
  It asks for the node value to be deleted and then prints the output message of the operation accordingly

##### 4.)GetMin
  It prints the smallest element present in the AVL Tree.

##### 5.)Extract Min
  It returns the smallest element from the AVL Tree. It removes the smallest element from the tree as well.

##### 6.)Merge
  It invloves merging two AVL Trees. For this operation, the user needs to create a second new AVL Tree(through this operation only) and then this newly created tree will be merged with the already present AVL tree.

### Binomial Heap
On successful compiltation, the program will have a menu driven functionality in which the user needs to enter which functionality he/she needs to perform.

#### Operations on Binomial heap are as follows : 
##### 1. Insert
On selecting this operation the user needs to first enter the number of nodes he/she needs to insert into the Binomial Heap and then accordingly enter the node's value.

##### 2. Delete
On selecting this operation, the user needs to type the key of the node to be deleted. If it is present in the heap, it will be deleted; else an error message would be displayed.

##### 3. Extract minimum :
This operation would print the smallest element present in the heap and also delete it from the heap.

##### 4.Merge
This operation would require the user to input another heap and then this heap would be merged with the existing heap and would be printed.

##### 5.Decrease key
On selecting this operation, the user needs to type the key of the node whose key is to be decreased. If the node is not present in the heap, an error is printed; else, A new key is requested from the user. The value of this key is checked if it is greater than the node's key. If it is, then an error is printed; else the node's key is decreased.

##### 6. Print heap
This operation prints all the nodes currently present in the heap.

## Application
Dijkstra's algorithm have been implmented using binomial heap.
