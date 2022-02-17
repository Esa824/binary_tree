#include <iostream>
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
int count_number_of_nodes_that_are_odd(node *binary_tree) {
  node *ptr = binary_tree;
  if (ptr == NULL) {
    return 0;
  }
  if (ptr->left == NULL && ptr->right == NULL && ptr->value % 2 == 1) {
    return 1;
  }
  int plus = 0;
  if(ptr->value % 2 == 1){
    plus++;
  }
  return count_number_of_nodes_that_are_odd(ptr->left) + count_number_of_nodes_that_are_odd(ptr->right) + plus;
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
  int count_three = 1431;
  node *binary_tree = binary_tree = create_binary_tree(count_three);
  int a = count_number_of_nodes_that_are_odd(binary_tree);
  printf("Value is %d\n", a);
}
