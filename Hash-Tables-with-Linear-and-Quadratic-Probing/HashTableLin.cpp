#include "HashTableLin.h"
#include <cmath>
#include <iostream>
#include <random>
using namespace std;

/*
* creates a HashTableLin object representing an empty hash table with maximum 
* allowed load factor equal to load
*/
HashTableLin::HashTableLin(int maxNum, double load)
{
    max_lf = load;
    num_keys = 0;
    int temp_size = std::ceil(maxNum / load); // size before checking prime
    // find the nearest prime number 
    while (!isPrime(temp_size)) {
        temp_size++;
    }
    size = temp_size;
  
    table.resize(size);
}
bool HashTableLin::isPrime(int num){ // O(sqrt(n)) worst case
    if (num <= 1) return false;
    for (int i = 2; i <= std::sqrt(num); i++)
    {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

/*
* Inserts the key n into this hash table.
* resolves collisions using linear probing
*/
void HashTableLin::insert(int n)
{
    int index = linProbeIndex(n);
    if (index != -1) // -1 index indicates value is already in hash table
    {
    // check if adding a key will exceed max load factor 
        if (double(num_keys + 1) / double(size) > max_lf)
        {
            // rehash and recompute index with linear probing
            rehash();
            index = linProbeIndex(n);
           
        }
        // insertion index found - insert in table at index
        table[index] = n;
        num_keys++;
    }
}

/*
* Returns index to insert using linear probing
*/
int HashTableLin::linProbeIndex(int n) {
    // hash function n % M
    int probe = n % size;
    // linear probe until an empty position or key that is being searched is found
    while (table[probe] != 0 && table[probe] != n) {
        probe = (probe + 1) % size;
    }
    // flag -1 if already in table, else return index
    return table[probe] == n ? -1 : probe;
}

/*
* rehash function incase collisions cannot be resolved
*/
void HashTableLin::rehash()
{
    std::vector<int> oldTable = table;
    int oldSize = size;

    // resize table to closest prime number after doubling old table size
    size *= 2;
    while (!isPrime(size)) { size++;}
    table.clear();
    table.resize(size);

    num_keys = 0;

    // insert all valid values from old table into resized table
    for (int i = 0; i < oldSize; i++) {
        if (oldTable[i] != 0) {
           insert(oldTable[i]);
        }
    }
}

/*
* returns true if key n is in this hash table. It returns
false otherwise
*/
bool HashTableLin::isIn(int n) // runs O(1) on avg unless high load factor - O(n) worst case
{
    int index = n % size; 
    while (table[index]) {
        if (table[index] == n) {
            return true;
        }
        // probe next
        index = (index + 1) % size;
    }
    return false;
}

//an O(n) only implementation for fun:
//bool HashTableLin::isIn(int n)
//{
//    for (int i = 0; i < table.size(); i++) {
//        if (table[i] == n) {
//            return true;
//        }
//    }
//    return false;
//}

void HashTableLin::printKeys()
{
    for (int i = 0; i < table.size(); i++)
    {
        std::cout << table[i] << std::endl;
    }
}

void HashTableLin::printKeysAndIndexes()
{
    for (int i = 0; i < table.size(); i++)
    {
        std::cout << "Index: " << i << "key: " << table[i] << std::endl;
    }
}
std::vector<double> HashTableLin::simProbeSuccess()
{
    int NUM_RUNS = 100;
    int NUM_KEYS = 1000;
    vector<double> result(9);
    for (int i = 1; i <= 9; i++)
    {
        double b = (double)i / 10.0;
        double total_probes = 0;
        for (int j = 0; j < NUM_RUNS; j++)
        {
            HashTableLin new_table(NUM_KEYS, b);
            int num_probes = 0;
            while (new_table.num_keys < NUM_KEYS)
            {
                int rand_num = (rand() + 1) * (rand() + 1);
                num_probes += new_table.insertCount(rand_num);
            }
            total_probes += num_probes;
        }
        double avg_probes = total_probes / (double)(NUM_RUNS * NUM_KEYS);
        result[i - 1] = avg_probes;
    }
    return result;
}
int HashTableLin::linProbeIterations(int n) { // linear probe but returns iterations 
    // hash function n % M
    int probe = n % size;
    int i = 1;
    // linear probe until an empty position or key that is being searched is found
    while (table[probe] != 0 && table[probe] != n) {
        probe = (probe + 1) % size;
        i++;
    }
    return i;
}

int HashTableLin::insertCount(int n) { // insert but returns insert count 
    // counts inserts 
    int index = linProbeIndex(n);
    int count = linProbeIterations(n);
    if (index != -1) // -1 index indicates value is already in hash table
    {
        // check if adding a key will exceed max load factor 
        if (double(num_keys + 1) / double(size) > max_lf)
        {
            //rehash and recompute index with linear probing
          rehash();
            index = linProbeIndex(n);
            count = linProbeIterations(n);
        }
        // insertion index found - insert in table
        table[index] = n;
        num_keys++;
    }
    return count;
}
// for bonus
std::vector<double> HashTableLin::simProbeUnsuccess()
{
    HashTableLin* hash_table;
    std::vector<int> used_lambdas;
    const int num_repetitions = 100;
    const int num_tests = 100000; // required to run with high tests since psedurandomness ruins results with smaller samples
    std::vector<double> lambdas{ 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9 }, results(lambdas.size());

    // This for loop tests each lambda defined above
    for (int i = 0; i < lambdas.size(); i++) {
        double lambda = lambdas[i];
        double runs_sum = 0;
        // Handles the number of tests that are to be averaged
        for (int j = 0; j < num_repetitions; j++) {
            double steps_sum = 0;
            hash_table = new HashTableLin(num_tests, lambda);
            // Adding fluff to the list
            for (int k = 0; k < num_tests; k++) {
                int x = rand() * rand();
                while (hash_table->isIn(x)) {
                    x = (rand() + 1) * (rand() + 1);
                }
                hash_table->insert(x);
            }
            // Now testing isIn function for testNum times
            for (int l = 0; l < num_tests; l++) {
                int x = rand() * rand();
                while (hash_table->isIn(x)) {
                    x = (rand() + 1) * (rand() + 1);
                }
                steps_sum += hash_table->unsuccessIsIn(x);
            }
            runs_sum += (double)steps_sum / (double)num_tests;
            delete hash_table;
        }
        results.at(i) = runs_sum / num_repetitions;
    }
    return results;
}

int HashTableLin::unsuccessIsIn(int n) { 
    int count = 0;

    int default_hash_value = n % size; int new_hash;

    for (int i = default_hash_value; i < default_hash_value + size; i++) {
        new_hash = i % size;
        count++;
        if (table[new_hash] == n)
            return -1;
        if (table[new_hash] == 0)
            return count;
    }
    return count;
}

// getter methods for priv fields 
int HashTableLin::getNumKeys() {return num_keys;}
int HashTableLin::getTableSize() {return size;}
double HashTableLin::getMaxLoadFactor() {return max_lf;}