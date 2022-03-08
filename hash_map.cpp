#include <iostream>
#include "linked_list.h"
//#include "bst.h"

// functions definition
bool insert_item(node* scatter_table, unsigned index, string value);
bool item_exist(node* scatter_table, unsigned index, string value);
void print(node *node);

unsigned TABLE_SIZE = 1;
unsigned M = 31;

// Kernighan and Ritchie's function
unsigned hash_key(string key, unsigned len) {
   unsigned hash = 0;
   for(unsigned i = 0; i < len; ++i)
      hash = M * hash + key[i];
   return hash % TABLE_SIZE;
}

// scatter table mean table of references
int main()
{
  string value;
  unsigned position;
  scatter_node *scatter_table = (scatter_node *) malloc(sizeof(scatter_node) * TABLE_SIZE);

  while(value.compare("0") != 0) {
    cin.clear();
    fflush(stdin);
    cin >> value;
    position = hash_key(value, value.size());
    cout << "\nvalue: " << value << ", index: " << position << "\n";
    insert_item(scatter_table, position, value);
  }

  for(int i = 0; i < TABLE_SIZE; i++){
    print(scatter_table[i].root);
    cout << "\n";
  }

 while(true){
   cin.clear();
   fflush(stdin);
   cin >> value;
   position = hash_key(value, value.size());
   cout << position;

   if(item_exist(scatter_table, position, value)){
      cout << "\nITEM EXIST\n";
   } else{
      cout << "\nNAO EXISTE\n";
   }

   for(int i = 0; i < TABLE_SIZE; i++){
     print(scatter_table[i].root);
     cout << "\n";
   }
 }

  return 0;
}
