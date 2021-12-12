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
   } else if(item_exist(scatter_table, index, value)) {
      return true;
   } else {
      new_node->value = value;
      new_node->next = scatter_table[index].head;
      scatter_table[index].head = new_node;
      return true;
   }
}

bool delete_item(scatter_node *scatter_table, unsigned index, string value) {
   if(scatter_table[index].head == NULL){
      return false;
   }

   node *finder = scatter_table[index].head;
   node *finder_aux = finder->next;

   // in case list have only 1 element
   if(value.compare(finder->value) == 0){
      free(finder);
      scatter_table[index].head = finder_aux;
      return true;
   }

   while(finder_aux != NULL){
      if(value.compare(finder_aux->value) == 0) {
         finder->next = finder_aux->next;
         free(finder_aux);
         return true;
      }

      finder = finder_aux;
      finder_aux = finder_aux->next;
   }

   return false;
}

void print(node *chain_list){
   node *reader = chain_list;
   while(reader !=  NULL){
      cout << "VALUE: " << reader->value << "\n";
      reader = reader->next;
   }
}
