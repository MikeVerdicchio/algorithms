#include "tree_node.h"

// Default Constructor - left and right are NULL, value '?'
TreeNode::TreeNode()
{
    value = "?";
    left = NULL;
    right = NULL;
}

// Constructor - sets value to val
TreeNode::TreeNode(const std::string &val)
{
    value = val;
    left = NULL;
    right = NULL;
}
