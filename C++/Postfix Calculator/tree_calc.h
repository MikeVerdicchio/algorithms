#ifndef TREE_CALC_H
#define TREE_CALC_H

#include "tree_node.h"
#include <stack> // Uses standard stack implementation

class TreeCalc
{
  public:
    TreeCalc();  //Constructor
    ~TreeCalc(); //Destructor

    void cleanTree(TreeNode *ptr);       //Deletes tree/frees memory
    void readInput();                    //gets data from user
    void insert(const std::string &val); //puts value in tree

    // print methods
    void printPrefix(TreeNode *curNode) const;  //prints data in prefix form
    void printInfix(TreeNode *curNode) const;   //prints data in infix form
    void printPostfix(TreeNode *curNode) const; //prints data in postfix form
    void printOutput() const;                   //prints in pre,in,post form
    int calculate();                            //calls private calculate method

  private:
    // declare a stack to hold your expression tree
    std::stack<TreeNode *> mystack;
    int calculate(TreeNode *ptr) const; //Evaluates tree, returns value
};

#endif
