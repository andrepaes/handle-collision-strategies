#include <string>

using namespace std;

class Node {
  public:
    Node():left(nullptr), right(nullptr), height(0){}
    string value;
    Node *left;
    Node *right;
    unsigned height;
};

class scatter_node {
  public:
    scatter_node():root(nullptr),numberNode(0){}
    Node *root;
    unsigned numberNode;
};

// auxiliary functions

// A utility function to get the height of the tree
int height(Node *node)
{
    if (node == nullptr)
        return -1;

    return node->height;
}

// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}

int balance_factor(Node *node)
{
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}

Node *right_rotate(Node *actual_node)
{
    Node *left_child = actual_node->left;
    Node *left_right_child = left_child->right;

    // Perform rotation
    left_child->right = actual_node;
    actual_node->left = left_right_child;

    // Update heights
    actual_node->height = 1 + max(height(actual_node->left), height(actual_node->right));
    left_child->height = 1 + max(height(left_child->left), height(left_child->right));

    // Return new root
    return left_child;
}

Node *left_rotate(Node *actual_node)
{
    Node *right_child = actual_node->right;
    Node *right_left_child = right_child->left;

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
void print(Node *node) {
    if(node == nullptr){
        return;
    }

    cout << "\n\t" << node->value << "(" << node->height << ") \n";
    print(node->left);
    print(node->right);
}

Node *do_insert_item(Node* actual_node, Node* new_node) {
    string value = new_node->value;

    if (actual_node == nullptr) {
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

bool do_item_exist(Node *node, string value){
    if(node == nullptr) {
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
bool item_exist(scatter_node *scatter_table, unsigned index, string& value){
    Node *root = scatter_table[index].root;
    if(root == nullptr){
        return false;
    }

    return do_item_exist(root, value);
}

bool insert_item(scatter_node *scatter_table, unsigned index, string& value) {
    Node *new_node = new Node;
    new_node->value = value;

    if(new_node == nullptr){
        return false;
    }

    scatter_table[index].root = do_insert_item(scatter_table[index].root, new_node);
    scatter_table[index].numberNode++;
    return true;
}
