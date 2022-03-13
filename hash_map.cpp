#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "linked_list.h"
//#include "bst.h"
//#include "avl.h"
#include <unistd.h>
#include <cstdlib>

#include <chrono>
using namespace std::chrono;

// functions definition
bool insert_item(node* scatter_table, unsigned index, string value);
bool item_exist(node* scatter_table, unsigned index, string value);
void print(node *node);

unsigned TABLE_SIZE = 1000;
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
  string row, word, value;
  vector<string> row_array;
  unsigned i = 0;
  scatter_node *scatter_table = (scatter_node *) malloc(sizeof(scatter_node) * TABLE_SIZE);

  auto start = high_resolution_clock::now();

  std::ifstream file("Dubsmash_22m_mail_pass.txt");

  if(file.is_open()){
    while(getline(file, row)){
      stringstream row_stream(row);

      getline(row_stream, value, ':');
      string a = value;
      insert_item(scatter_table, hash_key(a, a.length()), a);
      i++;
      cout << i << endl;
    }
  } else 
    cout << "Couldn't open file";

  auto stop = high_resolution_clock::now();

  auto duration = duration_cast<microseconds>(stop - start);

  cout << "----------------------------------------------------------------------------";
  cout << duration.count()/1000 << endl;

  return 0;
}
