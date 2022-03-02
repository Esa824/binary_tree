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
  node *root = create_node(NULL, 9);
  node *current_node = root;

  for (int i = 1; i < number_of_nodes; ++i) {
    current_node = create_binary_tree_node(current_node, i);
  }

  return root;
}
node *next_sibbling(node *binary_tree) {
  node *ptr = binary_tree;
  if (ptr->parent == NULL) {
    return ptr->left;
  }
  if (ptr->parent->left == ptr) {
    return ptr->parent->right;
  } else {
    int opsit_right = 0;
    node *ptr = binary_tree->parent;
    node *ptr2 = binary_tree;
    while (ptr2 == ptr->right) {
      opsit_right++;
      ptr2 = ptr2->parent;
      if (ptr->parent == NULL) {
        node *ptr3 = ptr;
        for (int i = 0; i < opsit_right; i++) {
          ptr3 = ptr3->left;
        }
        return ptr3->left;
      }
      ptr = ptr->parent;
    }
    node *ptr3 = ptr;
    ptr3 = ptr3->right;
    for (int i = 0; i < opsit_right; i++) {
      ptr3 = ptr3->left;
    }
    return ptr3;
  }
}
string print_binary_tree(node *tree) {
  string out_put;
  if (tree == NULL) {
    return "";
  }
  if (tree->value <= 9) {
    out_put += tree->value + 48;
    out_put += ",";
  }
  if (tree->value > 9) {
    int c = tree->value;
    int b = tree->value;
    int count = 0;
    ;
    while (c != 0) {
      c %= 10;
      count++;
      b /= 10;
      c = b;
    }
    c = tree->value;
    b = c;
    for (int i = 0; i < count; i++) {
      c %= 10;
      b /= 10;
      c = b;
      if (i == count - 1) {
        out_put += c + 48;
        c = tree->value;
        b = c;
      }
      c = tree->value;
      out_put += c % 10 + 48;
      out_put += ",";
    }
  }
  if (tree->left == NULL && tree->right == NULL) {
    return out_put;
  }
  return print_binary_tree(tree->left) + print_binary_tree(tree->right) +
         out_put;
}
string print_binary(node *tree) {
  if (tree == NULL) {
    return "{}";
  }
  return "{ \"value\": " + to_string(tree->value) + ", \"left\": " + print_binary(tree->left) + ", \"right\": " + print_binary(tree->right) + "}";
}
int main() {
  node *a = create_binary_tree(5);
  node *ptr = a;
  string k = print_binary(a);
  
  printf("%s", k.c_str());
}
