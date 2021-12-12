#include <iostream>
#include <string>
#include "linked_list.h"

using namespace std;

// functions definitions
bool insert_item(node* chain_list, unsigned index, string value);
bool delete_item(node* chain_list, unsigned index, string value);
bool item_exist(node* chain_list, unsigned index, string value);
void print(node *chain_list);

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
    print(scatter_table[i].head);
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

    delete_item(scatter_table, position, value);

    for(int i = 0; i < TABLE_SIZE; i++){
      cout << "index: " << i << "\n";
      print(scatter_table[i].head);
      cout << "\n";
    }
  }

  return 0;
}
