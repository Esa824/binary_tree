#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <istream>
#include <iterator>
#include <stdio.h>

#include <string.h>
struct node {
  int value;
  node *left;
  node *right;
  node *parent;
};
node *create_node(node *parent, int value) {
  node *new_node = (node *)malloc(sizeof(node));
  new_node->parent = parent;
  new_node->value = value;
  new_node->left = new_node->right = NULL;
  return new_node;
}
int find_depth(node *binary_tree) {
  int depth = 0;
  while (binary_tree->parent != NULL) {
    binary_tree = binary_tree->parent;
  }
  node *ptr1 = binary_tree;
  while (ptr1->left != 0) {
    ptr1 = ptr1->left;
    depth++;
  }
  depth++;
  int depth_two = 0;
  node *ptr2 = binary_tree;
  while (ptr2->left != 0) {
    ptr2 = ptr2->left;
    depth_two++;
  }
  depth_two++;
  return depth >= depth_two ? depth : depth_two;
}
bool last_node(node *binary_tree) {
  node *ptr = binary_tree;
  node *ptr2 = binary_tree;
  ptr2 = ptr2->parent;
  while (ptr2->parent == ptr) {
    ptr = ptr->parent;
    ptr2 = ptr2->parent;
    if (ptr2->parent == NULL) {
      return true;
    }
  }
  return false;
}
node *next_available_node(node *current_node, int i) {
  node *parent = current_node->parent;
  int opsite_right = 0;
  int opsite_left = 0;
  node *parent_ptr = current_node;
  if (i > 4 && i % 2 == 1) {
    while (parent_ptr == parent->right) {
      opsite_right++;
      parent_ptr = parent_ptr->parent;
      if (parent->parent == NULL) {
        node *ptr = parent;
        while (ptr->left != 0) {
          ptr = ptr->left;
        }
        return ptr;
      }
      parent = parent->parent;
    }
    node *ptr = parent;
    ptr = ptr->right;
    for (int i = 0; i < opsite_right; i++) {
      ptr = ptr->left;
    }
    return ptr;
  }
  if (parent == NULL) {
    return current_node->left;
  }

  if (current_node == parent->left) {
    return parent->right;
  }
  return NULL;
}
node *create_binary_tree_node(node *current_node, int value) {
  if (current_node->left == NULL) {
    current_node->left = create_node(current_node, value);
    return current_node;
  }

  if (current_node->right == NULL) {
    current_node->right = create_node(current_node, value);
    return current_node;
  }

  node *next = next_available_node(current_node, value);
  return create_binary_tree_node(next, value);
}

node *create_binary_tree(int number_of_nodes) {
  node *root = create_node(NULL, 0);
  node *current_node = root;

  for (int i = 1; i < number_of_nodes; ++i) {
    current_node = create_binary_tree_node(current_node, i);
  }

  return root;
}
int main() {
  int count_three = 20;
  node *binary_tree = binary_tree = create_binary_tree(count_three);
  int depth_of_binary_tree = 0;
  printf("Value is %d\n", depth_of_binary_tree = find_depth(binary_tree));
}
