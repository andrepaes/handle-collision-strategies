#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
//#include "linked_list.h"
#include "bst.h"
//#include "avl.h"
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <set>

using namespace std::chrono;

unsigned M = 31;
unsigned FILE_SIZE = 4000000;
unsigned RANDOM_INDEX_QUANTITY = 30;

// Kernighan and Ritchie's function
unsigned hash_key(string& key, unsigned len, unsigned table_size) {
    unsigned hash = 0;
    for(unsigned i = 0; i < len; ++i)
        hash = M * hash + key[i];
    return hash % table_size;
}

// scatter table mean table of references
int main()
{
    string row, word, value;
    vector<string> proof_values, non_existent_emails;
    unsigned counter = 0, random_value, insert_time_counter = 0, read_time_counter = 0, cycle_counter = 0;
    set<unsigned> random_values;
    unsigned table_size = 10;
    srand((unsigned) time(0));


    while(cycle_counter < 3) {
        scatter_node *scatter_table = new scatter_node[table_size];
        random_values.clear();
        proof_values.clear();
        counter = 0;
        ifstream not_found_emails("non_existent_emails.txt");

        while(getline(not_found_emails, row)){
            non_existent_emails.push_back(row);
        }

        while(random_values.size() < RANDOM_INDEX_QUANTITY) 
            random_values.insert(rand() % FILE_SIZE);

        auto start = high_resolution_clock::now();

        ifstream file("Dubsmash_22m_mail_pass.txt");

        if(file){
            while(getline(file, row)){
                std::size_t pos = row.find(":");
                string email = row.substr(0, pos);

                insert_item(scatter_table, hash_key(email, email.length(), table_size), email);
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
        insert_time_counter += duration.count();

        auto start_query = high_resolution_clock::now();

        while(!proof_values.empty()) {
            value = proof_values.back();
            proof_values.pop_back();
          if(item_exist(scatter_table, hash_key(value, value.length(), table_size), value))
              cout << value << " found" << endl;
          else
              cout << value << " not found" << endl;
        }

        cout << "--------------------------------" << endl;

        while(!non_existent_emails.empty()){
            value = non_existent_emails.back();
          non_existent_emails.pop_back();
          if(item_exist(scatter_table, hash_key(value, value.length(), table_size), value))
              cout << value << " found" << endl;
          else
              cout << value << " not found" << endl;
        }

        auto stop_query = high_resolution_clock::now();

        auto duration_query = duration_cast<microseconds>(stop_query - start_query);

        cout << "\n\nREAD TIME: " << duration_query.count() << " microseconds " << endl;
        read_time_counter += duration_query.count();

        for(int i = 0; i < table_size; i++) {
            free_all(scatter_table[i].root);
            scatter_table[i].root = nullptr;
        }
        delete scatter_table;
        cycle_counter++;
    }

    cout << "\n mean insertion time: " << insert_time_counter/cycle_counter << endl;
    cout << "\n mean reading time: " << read_time_counter/cycle_counter << endl;

    return 0;
}
