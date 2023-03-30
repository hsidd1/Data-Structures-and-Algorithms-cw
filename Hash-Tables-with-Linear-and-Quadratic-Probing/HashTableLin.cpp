#include "HashTableLin.h"
#include <cmath>
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
    // find the nearest prime number -- increment until prime
    while (!isPrime(temp_size)) {
        temp_size++;
    }
    // temp size is prime after iteration
    size = temp_size;
    // fill table
    for (int i = 0; i < size; i++)
    {
        table.push_back(0);
    }
}
 // self explanatory - checks if input int is prime 
bool HashTableLin::isPrime(int num){
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
        // insertion index found - insert in table
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


bool HashTableLin::isIn(int n)
{
    // TODO, change following code after completing this function
    return true;
}

void HashTableLin::printKeys()
{
    // TODO
}

void HashTableLin::printKeysAndIndexes()
{
    // TODO
}


std::vector<double> HashTableLin::simProbeSuccess()
{
    // TODO, change following code after completing this function
    vector<double> result(9);
    return result;
}

// for bonus
std::vector<double> HashTableLin::simProbeUnsuccess()
{
    // TODO, change following code after completing this function
    vector<double> result(9);
    return result;
}

// getter methods for priv fields 

int HashTableLin::getNumKeys() {
    return num_keys;
}

int HashTableLin::getTableSize() {
    return size;
}

double HashTableLin::getMaxLoadFactor() {
    return max_lf;
}