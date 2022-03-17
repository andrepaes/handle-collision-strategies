#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "linked_list.h"
//#include "bst.h"
//#include "avl.h"
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <set>

using namespace std::chrono;

unsigned TABLE_SIZE = 1000;
unsigned M = 31;
unsigned FILE_SIZE = 4000000;
//unsigned FILE_SIZE = 1000;
unsigned RANDOM_INDEX_QUANTITY = 30;

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
    vector<string> proof_values;
    unsigned counter = 0, random_value;
    set<unsigned> random_values;
    scatter_node *scatter_table = new scatter_node[TABLE_SIZE];
    srand((unsigned) time(0));


    while(random_values.size() < RANDOM_INDEX_QUANTITY)
        random_values.insert(rand() % FILE_SIZE);

    auto start = high_resolution_clock::now();

    ifstream file("Dubsmash_22m_mail_pass.txt");

    if(file){
        while(getline(file, row)){
            std::size_t pos = row.find(":");
            string email = row.substr(0, pos);

            insert_item(scatter_table, hash_key(email, email.length()), email);
            if(std::find(random_values.begin(), random_values.end(), counter) != random_values.end()) {
                proof_values.push_back(email);
            }
            counter++;
        }
    } else {
        cout << "Couldn't open file";
        return 0;
    }

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    cout << "\n\n" << "INSERTION TIME: " << duration.count() << " microseconds \n\n";

    auto start_query = high_resolution_clock::now();

    while(!proof_values.empty()) {
        value = proof_values.back();
        proof_values.pop_back();
        if(item_exist(scatter_table, hash_key(value, value.length()), value))
            cout << value << " found" << endl;
        else
            cout << value << " not found" << endl;
    }

    auto stop_query = high_resolution_clock::now();

    auto duration_query = duration_cast<microseconds>(stop_query - start_query);

    cout << "\n\nREAD TIME: " << duration_query.count() << " microseconds " << endl;

    for(int i = 0; i < TABLE_SIZE; i++) {
        free_all(scatter_table[i].head);
        scatter_table[i].head = nullptr;
    }
    return 0;
}
