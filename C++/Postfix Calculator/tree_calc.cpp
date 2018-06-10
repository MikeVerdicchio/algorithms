#include <iostream>
#include <stdio.h>
#include <stack>
#include <string>
#include <cstring>
#include <stdlib.h>
#include "tree_calc.h"

// Constructor
TreeCalc::TreeCalc()
{
    mystack = std::stack<TreeNode *>();
}

// Destructor- frees memory
TreeCalc::~TreeCalc()
{
    while (mystack.size() != 0)
    {
        cleanTree(mystack.top());
        mystack.pop();
    }
}

// Deletes tree/frees memory
void TreeCalc::cleanTree(TreeNode *ptr)
{
    if (ptr->left != NULL)
    {
        cleanTree(ptr->left);
        cleanTree(ptr->right);
    }
    else
    {
        delete ptr;
    }
}

// Gets data from user
void TreeCalc::readInput()
{
    std::string response;
    std::cout << "Enter elements one by one in postfix notation" << std::endl
              << "Any non-numeric or non-operator character,"
              << " e.g. #, will terminate input" << std::endl;
    std::cout << "Enter first element: ";
    std::cin >> response;
    // while input is legal
    while (isdigit(response[0]) || response[0] == '/' || response[0] == '*' || response[0] == '-' || response[0] == '+')
    {
        insert(response);
        std::cout << "Enter next element: ";
        std::cin >> response;
    }
}

// Puts value in tree stack
void TreeCalc::insert(const std::string &val)
{
    // insert a value into the tree
    if (val == "+" || val == "-" || val == "*" || val == "/")
    {
        TreeNode *node = new TreeNode(val);
        node->left = mystack.top();
        mystack.pop();
        node->right = mystack.top();
        mystack.pop();
        mystack.push(node);
    }
    else
    {
        TreeNode *node = new TreeNode(val);
        mystack.push(node);
    }
}

// Prints data in prefix form
void TreeCalc::printPrefix(TreeNode *ptr) const
{
    if (ptr->left != NULL || ptr->right != NULL)
    {
        std::cout << ptr->value << " ";
        printPrefix(ptr->right);
        std::cout << " ";
        printPrefix(ptr->left);
    }
    else
    {
        std::cout << ptr->value;
    }
}

// Prints data in infix form
void TreeCalc::printInfix(TreeNode *ptr) const
{
    if (ptr->left != NULL)
    {
        if (ptr->value == "+" || ptr->value == "-" || ptr->value == "*" || ptr->value == "/")
        {
            std::cout << "(";
            printInfix(ptr->right);
            std::cout << " " << ptr->value << " ";
            printInfix(ptr->left);
            std::cout << ")";
        }
        else
        {
            std::cout << ptr->value;
        }
    }
    else
    {
        std::cout << ptr->value;
    }
}

// Prints data in postfix form
void TreeCalc::printPostfix(TreeNode *ptr) const
{
    if (ptr->left != NULL || ptr->right != NULL)
    {
        printPostfix(ptr->right);
        std::cout << " ";
        printPostfix(ptr->left);
        std::cout << " " << ptr->value;
    }
    else
    {
        std::cout << ptr->value;
    }
}

// Prints tree in all 3 (pre,in,post) forms
void TreeCalc::printOutput() const
{
    if (mystack.size() != 0 && mystack.top() != NULL)
    {
        std::cout << "Expression tree in postfix expression: ";
        printPostfix(mystack.top());
        std::cout << std::endl;
        std::cout << "Expression tree in infix expression: ";
        printInfix(mystack.top());
        std::cout << std::endl;
        std::cout << "Expression tree in prefix expression: ";
        printPrefix(mystack.top());
        std::cout << std::endl;
    }
    else
        std::cout << "Size is 0." << std::endl;
}

// Evaluates tree, returns value
// private calculate() method
int TreeCalc::calculate(TreeNode *ptr) const
{
    // Traverse the tree and calculates the result
    int answer = 0;
    int left;
    int right;
    if (ptr->left == NULL)
    {
        return atoi((ptr->value).c_str());
    }
    else if (ptr->value == "+")
    {
        left = calculate(ptr->left);
        right = calculate(ptr->right);
        answer += (left + right);
    }
    else if (ptr->value == "-")
    {
        left = calculate(ptr->left);
        right = calculate(ptr->right);
        answer += (right - left);
    }
    else if (ptr->value == "*")
    {
        left = calculate(ptr->left);
        right = calculate(ptr->right);
        answer += (left * right);
    }
    else if (ptr->value == "/")
    {
        left = calculate(ptr->left);
        right = calculate(ptr->right);
        answer += (right / left);
    }
    return answer;
}

// Calls calculate, sets the stack back to a blank stack
// public calculate() method. Hides private data from user
int TreeCalc::calculate()
{
    int i = 0;
    while (mystack.size() != 0)
    {
        i += calculate(mystack.top());
        mystack.pop();
    }
    return i;
}