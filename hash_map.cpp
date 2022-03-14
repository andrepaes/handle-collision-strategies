#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
//#include "linked_list.h"
//#include "bst.h"
#include "avl.h"
#include <unistd.h>
#include <cstdlib>

#include <chrono>
using namespace std::chrono;

unsigned TABLE_SIZE = 10;
unsigned M = 31;

// Kernighan and Ritchie's function
unsigned hash_key(string& key, unsigned len) {
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
    //scatter_node *scatter_table = (scatter_node *) malloc(sizeof(scatter_node) * TABLE_SIZE);
    scatter_node *scatter_table = new scatter_node[TABLE_SIZE];
    //vector<Node *> scatter_table(TABLE_SIZE, nullptr);

    auto start = high_resolution_clock::now();

    ifstream file("1000_entries.txt");

    if(file){
        while(getline(file, row)){
            std::size_t pos = row.find(":");
            string email = row.substr(0, pos);
            string senha = row.substr(pos+1);
            cout << email << '\t' << senha << endl;
            insert_item(scatter_table, hash_key(email, email.length()), email);
        }
    } else {
        cout << "Couldn't open file";
        return 0;
    }

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    cout << duration.count() << endl;

    print(scatter_table[0].root);
    cout << height(scatter_table[0].root) << " " << scatter_table[0].numberNode << endl;
    return 0;
}
