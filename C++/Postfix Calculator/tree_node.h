#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <string>

class TreeNode
{
  public:
    TreeNode();                       //Default Constructor
    TreeNode(const std::string &val); //Constructor

  private:
    std::string value;
    TreeNode *left, *right; // for trees
    friend class TreeCalc;  // gives TreeCalc access to private data
};

#endif