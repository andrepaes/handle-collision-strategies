#include <string>

using namespace std;

typedef struct node {
  string value;
  node *left = NULL;
  node *right = NULL;
  unsigned height = 0;
} node;

typedef struct scatter_node {
  node *root = NULL;
} scatter_node;

// auxiliary functions
 
// A utility function to get the height of the tree
int height(node *node)
{
  if (node == NULL)
    return -1;

  return node->height;
}
 
// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}

int balance_factor(node *node)
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

node *right_rotate(node *actual_node)
{
    node *left_child = actual_node->left;
    node *left_right_child = left_child->right;
 
    // Perform rotation
    left_child->right = actual_node;
    actual_node->left = left_right_child;
 
    // Update heights
    actual_node->height = 1 + max(height(actual_node->left), height(actual_node->right));
    left_child->height = 1 + max(height(left_child->left), height(left_child->right));
 
    // Return new root
    return left_child;
}
 
node *left_rotate(node *actual_node)
{
    node *right_child = actual_node->right;
    node *right_left_child = right_child->left;
 
    // Perform rotation
    right_child->left = actual_node;
    actual_node->right = right_left_child;
 
    //  Update heights
    actual_node->height = 1 + max(height(actual_node->left), height(actual_node->right));
    right_child->height = 1 + max(height(right_child->left), height(right_child->right));
 
    // Return new root
    return right_child;
}

// use preorder path
void print(node *node) {
  if(node == NULL){
    return;
  }

  cout << "\n\t" << node->value << "(" << node->height << ") \n";
  print(node->left);
  print(node->right);
}

node *do_insert_item(node* actual_node, node* new_node) {
  string value = new_node->value;

  if (actual_node == NULL) {
    return new_node;
  }
  if (value.compare(actual_node->value) < 0) {
    actual_node->left = do_insert_item(actual_node->left, new_node);
  } else if (value.compare(actual_node->value) > 0) {
    actual_node->right = do_insert_item(actual_node->right, new_node);
  } else {
    return actual_node;
  }

    // As we'll return back into the stack we take the opportunity to update the nodes heights
    actual_node->height = 1 + max(height(actual_node->left), height(actual_node->right));
 
    // Get the balance factor to check if there is some need of rebalancing
    int balance = balance_factor(actual_node);
 
    // Left Left Case
    if (balance > 1 && value.compare(actual_node->left->value) < 0)
        return right_rotate(actual_node);
 
    // Right Right Case
    if (balance < -1 && value.compare(actual_node->right->value) > 0)
        return left_rotate(actual_node);
 
    // Left Right Case
    if (balance > 1 && value.compare(actual_node->left->value) > 0)
    {
        actual_node->left = left_rotate(actual_node->left);
        return right_rotate(actual_node);
    }
 
    // Right Left Case
    if (balance < -1 && value.compare(actual_node->right->value) < 0)
    {
        actual_node->right = right_rotate(actual_node->right);
        return left_rotate(actual_node);
    }
 
    return actual_node;
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
  node *new_node = (node *) malloc(sizeof(node));
  new_node->value = value;

  if(new_node == NULL){
    return false;
  }

  if(scatter_table[index].root == NULL){
    scatter_table[index].root = new_node;
    return true;
  } else {
    scatter_table[index].root = do_insert_item(scatter_table[index].root, new_node);
    return true;
  }
}
