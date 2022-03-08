#include <string>

using namespace std;

typedef struct node {
  string value;
  node *next = NULL;
} node;

typedef struct scatter_node {
  node *head = NULL;
} scatter_node;

bool item_exist(scatter_node *scatter_table, unsigned index, string value){
   node *finder = scatter_table[index].head;
   while(finder != NULL) {
      if(value.compare(finder->value) == 0){
         return true;
      }
      finder = finder->next;
   }

   return false;
}

// insert at first postion to not need to iterate over the whole list
bool insert_item(scatter_node *scatter_table, unsigned index, string value){
   node *new_node = (node *) malloc(sizeof(node));

   if(new_node == NULL){
      return false;
   } 

   if(item_exist(scatter_table, index, value)) {
      free(new_node);
      return true;
   } else {
      new_node->value = value;
      new_node->next = scatter_table[index].head;
      scatter_table[index].head = new_node;
      return true;
   }
}

void print(node *chain_list){
   node *reader = chain_list;
   while(reader !=  NULL){
      cout << "VALUE: " << reader->value << "\n";
      reader = reader->next;
   }
}
