#include <string>

using namespace std;

typedef struct node {
  string value;
  node *left = NULL;
  node *right = NULL;
} node;

typedef struct scatter_node {
  node *root = NULL;
} scatter_node;

// auxiliary functions

// use preorder path
void print(node *node) {
  if(node == NULL){
    return;
  }

  cout << "\t" << node->value;
  print(node->left);
  print(node->right);
}
bool do_insert_item(node* actual_node, node* new_node) {
  if(new_node->value.compare(actual_node->value) < 0){
    if(actual_node->left == NULL){
      actual_node->left = new_node;
      return true;
    }

    return do_insert_item(actual_node->left, new_node);

  } else {
    if(actual_node->right == NULL){
      actual_node->right = new_node;
      return true;
    }

    return do_insert_item(actual_node->right, new_node);
  }
}

bool do_item_exist(node *node, string value){
  if(node == NULL) {
    return false;
  }

  if(value.compare(node->value) == 0){
    return true;
  }

  if(value.compare(node->value) < 0){
    return do_item_exist(node->left, value);
  } else {
    return do_item_exist(node->right, value);
  }
}

// exported functions
bool item_exist(scatter_node *scatter_table, unsigned index, string value){
  node *root = scatter_table[index].root;
  if(root == NULL){
    return false;
  }

  return do_item_exist(root, value);
}

bool insert_item(scatter_node *scatter_table, unsigned index, string value) {
  if(item_exist(scatter_table, index, value))
    return true;

  node *new_node = (node *) malloc(sizeof(node));
  new_node->value = value;

  if(new_node == NULL){
    return false;
  }

  if(scatter_table[index].root == NULL){
    scatter_table[index].root = new_node;
    return true;
  } else {
    return do_insert_item(scatter_table[index].root, new_node);
  }
}
