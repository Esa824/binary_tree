#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;
struct node {
  int value;
  node *left;
  node *right;
  node *parent;
};

node *create_node(node *parent, int value) {
  node *new_node = (node *)malloc(sizeof(node));
  new_node->value = value;
  new_node->parent = parent;
  return new_node;
}

string print_binary(node *tree) {
  if (tree == NULL) {
    return "{}";
  }
  return "{ \"value\": " + to_string(tree->value) + ", \"left\": " + print_binary(tree->left) + ", \"right\": " + print_binary(tree->right) + "}";
}
