#include <iostream>
using namespace std;
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
  return new_node;
}

int create_sorted_binary_tree_node(node *root, int value) {
  if (root == NULL) {
    return 0;
  }
  if (root->value == value) {
    return 0;
  }
  if (root->right == NULL) {
    if (root->value < value) {
      root->right = create_node(root->parent, value);
      return 1;
    }
    return 0;
  }
  if (root->left == NULL) {
    if (root->value > value) {
      root->left = create_node(root->parent, value);
      return 1;
    }
    return 0;
  }

  int check = create_sorted_binary_tree_node(root->right, value);
  if (check == 0) {
    create_sorted_binary_tree_node(root->left, value);
  }
  return 0;
}
node *create_sorted_binary_tree(int *ptr, int number) {
  int *ptr2 = ptr;
  ptr2++;
  node *binary_tree = create_node(NULL, *ptr);
  for (int i = 0; i < number - 1; i++) {
    create_sorted_binary_tree_node(binary_tree, *ptr2);
    ptr2++;
  }
  return binary_tree;
}
string json(node *tree) {
  if (tree == NULL) {
    return "{}";
  }
  return "{\"value\" : " + to_string(tree->value) +
         ", \"left\" : " + json(tree->left) +
         ", \"right\" : " + json(tree->right) + "}";
}
void serch_tree_ge(node *root, int number, int &answer, int &check) {
  if (root == NULL) {
    return;
  }
  if (root->value > number && check == 0 ||
      root->value > number && root->value < answer) {
    answer = root->value;
    check = 1;
  }
  serch_tree_ge(root->left, number, answer, check),
      serch_tree_ge(root->right, number, answer, check);
}
void serch_tree_le(node *root, int number, int &answer, int &check) {
  if (root == NULL) {
    return;
  }
  if (root->value < number && check == 0 || root->value < number && root->value > answer) {
    answer = root->value;
    check = 1;
  }
  serch_tree_le(root->left, number, answer, check),
      serch_tree_le(root->right, number, answer, check);
}

int main() {
  int array[] = {10, 11, 12, 1, 5, 9,20};
  int *ptr = array;
  node *binary_tree = create_sorted_binary_tree(ptr, sizeof(array) / 4);
  string json_string = json(binary_tree);
  printf("%s", json_string.c_str());
  int number;
  cout << "number is: ";
  cin >> number;
  int a = 0;
  int answer = 0;
  serch_tree_le(binary_tree, number, answer, a);
  if (answer != 0) {
    printf("answer is %d\n", answer);
  }
  if (answer == 0) {
    printf("answer is %d\n", -1);
  }
}
