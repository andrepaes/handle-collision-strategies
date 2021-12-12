#include <iostream>
#include <string>
#include "linked_list.h"

using namespace std;

// functions definitions
bool insert(node* chain_list, string value);
bool item_exist()
void print(node *chain_list);

unsigned TABLE_SIZE = 5;
unsigned M = 31;

// Kernighan and Ritchie's function
unsigned hash_key(string key, size_t len) {
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
  cin >> value;
  position = hash_key(value, sizeof(value));
  cout << position;
  insert(scatter_table, position, value);
  print(scatter_table[position].head);
  
  if(item_exist(scatter_table, position, value)){
     cout << "ITEM EXIST";
  } else{
     cout << "NAO EXISTE";
  }

  return 0;
}
