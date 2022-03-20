#include <string>

using namespace std;

typedef struct node {
  string value;
  node *left = NULL;
  node *right = NULL;
} node;

class Node {
  public:
    Node():left(nullptr), right(nullptr){}
    string value;
    Node *left;
    Node *right;
};

class scatter_node {
  public:
    scatter_node():root(nullptr),numberNode(0){}
    Node *root;
    unsigned numberNode;
};

// auxiliary functions

// use preorder path
void print(Node *actual_node) {
  if(actual_node == NULL){
    return;
  }

  cout << "\t" << actual_node->value;
  print(actual_node->left);
  print(actual_node->right);
}

bool do_insert_item(Node* actual_node, Node* new_node) {
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

bool do_item_exist(Node *actual_node, string& value){
  if(actual_node == NULL) {
    return false;
  }

  if(value.compare(actual_node->value) == 0){
    return true;
  }

  if(value.compare(actual_node->value) < 0){
    return do_item_exist(actual_node->left, value);
  } else {
    return do_item_exist(actual_node->right, value);
  }
}

// exported functions
bool item_exist(scatter_node *scatter_table, unsigned index, string value){
  Node *root = scatter_table[index].root;
  if(root == NULL){
    return false;
  }

  return do_item_exist(root, value);
}

bool insert_item(scatter_node *scatter_table, unsigned index, string&  value) {
  Node *new_node = (Node *) malloc(10 * sizeof(Node));
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

void free_all(Node *actual_node) {

    if(actual_node == nullptr){
        return;
    }

    free_all(actual_node->left);
    free_all(actual_node->right);
    free(actual_node);
}
