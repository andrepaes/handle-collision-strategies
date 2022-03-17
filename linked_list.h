#include <string>
#include <math.h>

using namespace std;

class Node {
   public:
      Node():next(nullptr){}
      string value;
      Node *next;
};

class scatter_node {
   public:
       scatter_node():head(nullptr){}
       Node *head;
};

bool item_exist(scatter_node *scatter_table, unsigned index, string& value){
   Node *finder = scatter_table[index].head;
   while(finder != NULL) {
      if(value.compare(finder->value) == 0){
         return true;
      }
      finder = finder->next;
   }

   return false;
}

// insert at first postion to not need to iterate over the whole list
bool insert_item(scatter_node *scatter_table, unsigned index, string& value){
   Node *new_node = new Node;

   if(new_node == nullptr){
      return false;
   } 

   new_node->value = value;
   new_node->next = scatter_table[index].head;
   scatter_table[index].head = new_node;
   return true;
}

void print(Node *chain_list){
   Node *reader = chain_list;
   while(reader !=  NULL){
      cout << "VALUE: " << reader->value << "\n";
      reader = reader->next;
   }
}

void free_all(Node *chain_list) {
   Node *first_ptr = chain_list, *second_ptr = chain_list;
   while(first_ptr !=  NULL){
      second_ptr = first_ptr->next;
      free(first_ptr);
      first_ptr = second_ptr;
   }
}
