// This cpp file defines the functionality of the functions declared in ahdecode.h

// Date Created: 28 MAR 2016
// Date Revised: 04 APR 2016
// Author: Diwei Chen

#include <bitset>
#include "ahdecode.h"

// find if the symbol exists in the binary tree
//      if exists, return the leaf node that stores the symbol
//      if not, return the NYT node
// time complexity: O(n)
std::shared_ptr<Node> Tree::FindSymbolNode(std::shared_ptr<Node> root, char symbol, std::string& output) {
    std::shared_ptr<Node> current = root;
    std::shared_ptr<Node> p;
    while (current->GetWeight() != 0) {
        if (current->IsLeaf()) {
            if (current->GetSymbol() == symbol) {
                p = current;
                while (p != root) {
                    p = p->GetParentNode();
                }
                return current;
            }
            else {
                current = current->GetNextNode();
            }
        }
        else {
            current = current->GetNextNode();
        }
    }
    p = current;    // current points to NYT at this time
    while (p != root) {
        p = p->GetParentNode();
    }
    return current;
}


// return first node of the block before p's block in the linked list
// blocks are nodes of same weight and same type (i.e. either leaf node or internal node) form a Block
std::shared_ptr<Node> Tree::GetFirstNodeOfPreBlock(std::shared_ptr<Node> p) {
    int wt = p->GetWeight();
    std::shared_ptr<Node> tmp = p;
    std::shared_ptr<Node> pre_node = p->GetPreNode();       // pre_node is the node in front of p
    
    while ((!p->IsLeaf() && pre_node->IsLeaf() && (wt == pre_node->GetWeight() - 1)) ||
           (p->IsLeaf() && !pre_node->IsLeaf() && (wt == pre_node->GetWeight()))) {
        tmp = pre_node;
        pre_node = pre_node->GetPreNode();
    }
    
    return tmp;
}

// swap current node and the node in front of it in the doubly linked list
void Tree::SwapCurrentAndPreNode(std::shared_ptr<Node> q, std::shared_ptr<Node> pre_node) {
    std::shared_ptr<Node> tmp_q_parent_node = q->GetParentNode();   // two directions
    std::shared_ptr<Node> tmp_q_next_node = q->GetNextNode();       // two directions
    char tmp_q_tag = q->GetTag();
    
    q->SetParentNode(pre_node->GetParentNode());
    if (pre_node->GetTag() == '0')          // if pre_node is the left child of its parent
        pre_node->GetParentNode()->SetLeftNode(q);
    else if (pre_node->GetTag() == '1')     // if pre_node is the right child of its parent
        pre_node->GetParentNode()->SetRightNode(q);
    q->SetTag(pre_node->GetTag());
    q->SetNextNode(pre_node);
    q->SetPreNode(pre_node->GetPreNode());
    
    pre_node->GetPreNode()->SetNextNode(q);
    pre_node->SetPreNode(q);
    pre_node->SetParentNode(tmp_q_parent_node);
    if (tmp_q_tag == '0')
        tmp_q_parent_node->SetLeftNode(pre_node);
    else if (tmp_q_tag == '1')
        tmp_q_parent_node->SetRightNode(pre_node);
    pre_node->SetNextNode(tmp_q_next_node);
    tmp_q_next_node->SetPreNode(pre_node);
    pre_node->SetTag(tmp_q_tag);
}

// interchange the positions of the two nodes, and all of their relations with others are exchanged
void Tree::InterchangeTwoNode(std::shared_ptr<Node> q, std::shared_ptr<Node> p) {
    std::shared_ptr<Node> tmp_q_parent_node = q->GetParentNode();   // two directions
    std::shared_ptr<Node> tmp_q_pre_node = q->GetPreNode();     //two directions
    std::shared_ptr<Node> tmp_q_next_node = q->GetNextNode();       // two directions
    std::shared_ptr<Node> p_pre_node = p->GetPreNode();
    std::shared_ptr<Node> p_next_node = p->GetNextNode();
    char tmp_q_tag = q->GetTag();
    
    // set the relationship between q and its parent
    q->SetParentNode(p->GetParentNode());
    if (p->GetTag() == '0') {
        p->GetParentNode()->SetLeftNode(q);
    }
    else if (p->GetTag() == '1') {
        p->GetParentNode()->SetRightNode(q);
    }
    q->SetTag(p->GetTag());
    // set the relationship between q and the node in front of it
    q->SetPreNode(p->GetPreNode());
    p_pre_node->SetNextNode(q);
    // set the relationship between q and the node next to it
    q->SetNextNode(p->GetNextNode());
    p_next_node->SetPreNode(q);
    
    p->SetParentNode(tmp_q_parent_node);
    if (tmp_q_tag == '0') {
        tmp_q_parent_node->SetLeftNode(p);
    }
    else if (tmp_q_tag == '1') {
        tmp_q_parent_node->SetRightNode(p);
    }
    p->SetPreNode(tmp_q_pre_node);
    tmp_q_pre_node->SetNextNode(p);
    p->SetNextNode(tmp_q_next_node);
    tmp_q_next_node->SetPreNode(p);
    p->SetTag(tmp_q_tag);
    
}

// all the nodes in a given block shift to the left one spot to make room for node p,
// which slides over the block to the right
std::shared_ptr<Node> Tree::SlideAndIncrement(std::shared_ptr<Node> p) {
    int wt = p->GetWeight();
    std::shared_ptr<Node> b = Tree::GetFirstNodeOfPreBlock(p);
    std::shared_ptr<Node> former_parent_of_p;
    // two conditions
    //      1st: if p is a leaf node and it has the same weight as the block in front of it
    //      2nd: if p is a internal node and its weight + 1 equals to the weight of the block in front of it
    // slide p over the block to the right
    if ((p->IsLeaf() && !b->IsLeaf() && (b->GetWeight() == wt)) ||
        (!p->IsLeaf() && b->IsLeaf() && (b->GetWeight() == wt + 1)) ) {
        std::shared_ptr<Node> pre_node = p->GetPreNode();
        former_parent_of_p = p->GetParentNode();
        while (pre_node != b) {
            Tree::SwapCurrentAndPreNode(p, pre_node);
            pre_node = p->GetPreNode();
        }
        Tree::SwapCurrentAndPreNode(p, pre_node);
        p->SetWeight(wt + 1);
        if (p->IsLeaf()) {          // if 1st, then p points to its new parent
            p = p->GetParentNode();
        }
        else {              // if 2nd, then p points to its former parent
            p = former_parent_of_p;
        }
    }
    else {
        p->SetWeight(wt + 1);           // increase the weight of p by 1
        p = p->GetParentNode();         // p points to its parent
    }
    return p;
}

// return the character that the 8 bits represent
char BinaryToChar(std::string str) {
    std::bitset<8> binary_to_char(str);
    return static_cast<char>(binary_to_char.to_ulong());
}

// update the binary three and the doubly linked list by the input symbol
void Tree::Update(std::shared_ptr<Node> root, char symbol, std::string& output, int argc) {
    output = output + symbol;
    std::shared_ptr<Node> leaf_to_increment = nullptr;
    std::shared_ptr<Node> q = Tree::FindSymbolNode(root, symbol, output);
    // if q is NYT
    if (q->GetWeight() == 0) {
        std::shared_ptr<Node> right_node = std::make_shared<Node>(symbol, '1');
        std::shared_ptr<Node> left_node = std::make_shared<Node>('0');
        
        q->SetRightNode(right_node);    // create p's right node as new symbol node
        right_node->SetParentNode(q);    // set p as its right node's parent
        q->SetNextNode(right_node);
        right_node->SetPreNode(q);
        
        q->SetLeftNode(left_node);       // create p's left node as NYT
        left_node->SetParentNode(q);     // set p as its left node's parent
        right_node->SetNextNode(left_node);
        left_node->SetPreNode(right_node);
        
        q->SetIsLeaf(false);
        leaf_to_increment = right_node;
    }
    else {
        std::shared_ptr<Node> pre_node = q->GetPreNode();
        std::shared_ptr<Node> tmp;
        // interchange q in the tree with the leader of its block
        if ((q->GetWeight() == pre_node->GetWeight()) &&
            ((q->IsLeaf() && pre_node->IsLeaf()) ||
             (!q->IsLeaf() && !pre_node->IsLeaf()))) {
                while ((q->GetWeight() == pre_node->GetWeight()) &&
                       ((q->IsLeaf() && pre_node->IsLeaf()) ||
                        (!q->IsLeaf() && !pre_node->IsLeaf()))) {
                           tmp = pre_node;
                           pre_node = pre_node->GetPreNode();
                       }
                if (tmp == q->GetPreNode()) {
                    Tree::SwapCurrentAndPreNode(q, tmp);
                }
                else {
                    Tree::InterchangeTwoNode(q, tmp);
                }
                
            }
        // q is the sibling of NYT
        if (q->GetNextNode()->GetWeight() == 0) {
            leaf_to_increment = q;
            q = q->GetParentNode();
        }
    }
    while (q != root) {
        q = Tree::SlideAndIncrement(q);
    }
    root->SetWeight(root->GetWeight() + 1);     // increase the weight of the root by 1
    if (leaf_to_increment != nullptr) {
        Tree::SlideAndIncrement(leaf_to_increment);
    }
}

// build a binary three and its doubly linked list by its input string
void Tree::Build(int argc) {
    root_ = std::make_shared<Node>(0, 256, true);
    std::string output_str;
    std::string sub_str;
    char ch;
    char symbol;
    std::shared_ptr<Node> p = root_;        // p points to searched node
    for (int i = 0; str[i] != '\0'; ++i) {
        ch = str.at(i);
        if (ch == '0') {
            if (p->hasLeft()) {
                if (p->GetLeftNode()->GetWeight() == 0) {       // if p'left child node is NYT node at this time
                    ++i;          
                    for (int j = i + 8; i < j; ++i) {       // read the next 8 bits immediately
                        sub_str = sub_str + str.at(i);
                    }
                    --i;
                    symbol = BinaryToChar(sub_str);     // get the character of its 8 bits representation
                    sub_str.clear();
                    Tree::Update(root_, symbol, output_str, argc);      // put the character into the tree
                    p = root_;      // restore p by pointing it to root
                }
                else {      // if p'left child node is not NYT node
                    if (p->GetLeftNode()->IsLeaf()) {       // but it is still a leaf node
                        symbol = p->GetLeftNode()->GetSymbol();
                        Tree::Update(root_, symbol, output_str, argc);      // increase the number of the symbol by 1
                        p = root_;
                    }
                    else {      // if it is an internal node
                        p = p->GetLeftNode();       // continue on the path
                        continue;
                    }
                }
            }
            else {
                if (p->GetWeight() == 0) {      // if p itself is a NYT node
                    for (int j = i + 8; i < j; ++i) {       // read the 8 bits immediately
                        sub_str = sub_str + str.at(i);
                    }
                    --i;
                    symbol = BinaryToChar(sub_str);         // get the character of its 8 bits representation
                    sub_str.clear();
                    Tree::Update(root_, symbol, output_str, argc);      // put the character into the tree
                    p = root_;
                }
                else {          // the symbol has already existed
                    symbol = p->GetSymbol();
                    Tree::Update(root_, symbol, output_str, argc);
                    p = root_;
                }
            }
        }
        else if (ch == '1') {
            if (p->hasRight()) {
                    if (p->GetRightNode()->IsLeaf()) {      // if p's right child node is a leaf node
                        symbol = p->GetRightNode()->GetSymbol(); 
                        Tree::Update(root_, symbol, output_str, argc);      // increase the number of symbol by 1
                        p = root_;
                    }
                    else {
                        p = p->GetRightNode();
                        continue;
                    }
            }
            else {
                if (p->GetWeight() == 0) {      // if p itselt if a NYT node
                    for (int j = i + 8; i < j; ++i) {       // get the 8 bits immediately
                        sub_str = sub_str + str.at(i);
                    }
                    --i;
                    symbol = BinaryToChar(sub_str);     // get the character from its 8 bits representation
                    sub_str.clear();
                    Tree::Update(root_, symbol, output_str, argc);      // put the character into the tree
                    p = root_;
                }
                else {      // the symbol has already existed
                    symbol = p->GetSymbol();
                    Tree::Update(root_, symbol, output_str, argc);      // increase the number of symbol by 1
                    p = root_;
                }
            }
        }
        else if (ch == ' ') {
            continue;
        }
    }

    std::cout << output_str << std::endl;       // print the output string to console
}

