# Adaptive-Huffman-Algorithm-Invariant

// Date Created: 28 MAR 2016
// Date Revised: 04 APR 2016
// Author: Diwei Chen

The encoder(ahencode) is built based on Vitter's Adaptive Huffman algorithm(invariant). Initially, the program initilises a binary tree with a root node and stores the input string. Then it starts to analyse the input characters(which always treated as block-based, 1 byte, implemented as data type char). When the encoder firstly meet a new character(it knows nothing at first), it updates the tree and searches for the NYT node(at the very begining, it is the root node) and then expands the NYT node with two child nodes; left node becomes the new NYT node and right node stores the character with symbol. Both of the weight of former NYT node and its right child node then increased by 1. This process is implemented in function Update(). 

For each time, it FindSymbolNode() in the tree and outputs the searching path(searches left child node represented as '0', right as '1') and Update() the weight of the tree. As the weights updated, in order to maintain the implicit numbering(the weights of nodes incresed from bottom to top, left to right), the doubly linked list is built within the tree(sequenced by increasing weight from left to right, bottom to top) and the sequence is maintained by SildeAndIncrement() function. If the found node is a leaf node and it has the same weight as the block in front of it or it is an internal node and its weight + 1 equals to the weight of the block in front of it(nodes of same weight and same type form a block), all the nodes in a given block shift to the left one spot to make room for the found node, which slides over the block to the right.

Thus, each time when handling with a character, the encoder searches for the character in the tree and stores its searching path. If meeting a new character, the 8 bits binary expression of it is attched.

Since both of the encoder and the decoder(ahdecode) implement the same Vitter's Adaptive Huffman algorithm(invariant) to construct the data structure(binary tree and doubly linked list), the datastructure built by them will be exactly the same. While the encoder takes each character of input to constuct the tree and outputs the path walking through the tree corresponding to each character(when meet new character, its 8-bit binary expression is attached), the decoder takes the path as input and transfers the 8-bit binary expression to the character that it represents by the function BinaryExpression() and uses those characters and path to build the same data structure by the same Update() function and the same SlideAndIncrement() function. Therefore, they will keep building the same binary tree and doubly linked list. Therefore, the decoder can decode the output of the encoder.


