// This header file declares two classes named Node and Tree respectively and a global function.

// Date Created: 28 MAR 2016
// Date Revised: 04 APR 2016
// Author: Diwei Chen

#ifndef AhDecode_ahdecode_h
#define AhDecode_ahdecode_h
#include <string>
#include <iostream>
#include <memory>

// class represents a node located in a binary tree.
// node is classified as internal node or leaf node
// each internode node as specified has the weight which is the sum of the weights of its children.
// each leaf node as specified represents an input character which will be stored in its symbol 
class Node {
public:
    Node();
    Node(char s, char t) : symbol_{s}, tag_{t} {};
    Node(char t) : tag_{t} {};
    Node(int w, int a, bool i) : weight_{w}, address_{a}, is_leaf_{i} {};
    Node(char s, int w, int a, bool i) : symbol_{s}, weight_{w}, address_{a}, is_leaf_{i} {};
    char GetSymbol() const {return symbol_;};
    void SetSymbol(char symbol) {symbol_ = symbol;};
    int GetWeight() const {return weight_;};
    void SetWeight(int weight) {weight_ = weight;};
    const int GetAddress() const {return address_;};
    void SetAddress(int& address) {address_ = address;};
    bool IsLeaf() {return is_leaf_;};
    void SetIsLeaf(bool b) {is_leaf_ = b;};
    char GetTag() const {return tag_;};
    void SetTag(char tag) {tag_ = tag;};
    std::shared_ptr<Node> GetParentNode() const {return parent_node_;};
    void SetParentNode(std::shared_ptr<Node> parent) {parent_node_ = parent;};
    std::shared_ptr<Node> GetLeftNode() const {return left_node_;};
    void SetLeftNode(std::shared_ptr<Node> left) {left_node_ = left;};
    std::shared_ptr<Node> GetRightNode() const {return right_node_;};
    void SetRightNode(std::shared_ptr<Node> right) {right_node_ = right;};
    std::shared_ptr<Node> GetPreNode() const {return pre_node_;};
    void SetPreNode(std::shared_ptr<Node> pre_node) {pre_node_ = pre_node;};
    std::shared_ptr<Node> GetNextNode() const {return next_node_;};
    void SetNextNode(std::shared_ptr<Node> next_node) {next_node_ = next_node;};
    bool hasLeft() {
        if (left_node_ != nullptr)  return true;
        return false;
    };
    bool hasRight() {
        if (right_node_ != nullptr) return true;
        return false;
    };
private:
    char symbol_;       // store an input character
    int weight_ = 0;    // if this is a leaf node, the weight counts the number of the input character it represents
                        // if this is a internal node, the weight is the sum of the weights of its children
    int address_;       // initially used to specify the space of root node, is trivial
    bool is_leaf_ = true;       // nodes is classified as internal node or leaf node
    char tag_;                  // if this node is the left/right child of its parent, tag_ = '0'/'1'
    std::shared_ptr<Node> parent_node_ = nullptr;       // this node's parent node
    std::shared_ptr<Node> left_node_ = nullptr;         // this node's left child node
    std::shared_ptr<Node> right_node_ = nullptr;        // this node's right child node
    std::shared_ptr<Node> pre_node_ = nullptr;          // this node's front node in the doubly linked list in its tree
    std::shared_ptr<Node> next_node_ = nullptr;         // this node's next node in the doubly linked list in its tree
    
};

// class represents a binary tree.
// the nodes in the tree have implicit numbering, where the weights are increased from bottom to top,
// left to right at their level.
// in addition, the nodes are constructed in a doubly linked list in decreasing order by their weight
// from top to bottom, right to left
class Tree {
public:
    Tree();
    Tree(std::string& s) {str = s;};
    void Build(int argc);
    std::shared_ptr<Node> FindSymbolNode(std::shared_ptr<Node> root, char str, std::string& output);
    std::shared_ptr<Node> GetFirstNodeOfPreBlock(std::shared_ptr<Node> p);
    void SwapCurrentAndPreNode(std::shared_ptr<Node> q, std::shared_ptr<Node> pre_node);
    void InterchangeTwoNode(std::shared_ptr<Node> q, std::shared_ptr<Node> p);
    std::shared_ptr<Node> SlideAndIncrement(std::shared_ptr<Node> p);
    void Update(std::shared_ptr<Node> root, char symbol, std::string& output, int argc);
private:
    std::string str;            // store the string input by users
    std::shared_ptr<Node> root_ = nullptr;          // the root node of the tree
};

std::string BinaryExpression(char ch);


#endif
