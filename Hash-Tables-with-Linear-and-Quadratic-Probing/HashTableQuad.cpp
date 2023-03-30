#include "HashTableQuad.h"
using namespace std;

HashTableQuad::HashTableQuad(int maxNum, double load)
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
bool HashTableQuad::isPrime(int num) { // O(sqrt(n)) worst case
    if (num <= 1) return false;
    for (int i = 2; i <= std::sqrt(num); i++)
    {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

//void HashTableQuad::insert(int n)
//{
//    int index = quadProbeIndex(n);
//    if (index != -1) // -1 index indicates value is already in hash table
//    {
//        // check if adding a key will exceed max load factor 
//        if (double(num_keys + 1) / double(size) > max_lf)
//        {
//            // rehash and recompute index with linear probing
//            rehash();
//            index = quadProbeIndex(n);
//
//        }
//        // insertion index found - insert in table
//        table[index] = n;
//        num_keys++;
//    }
//}
//
///*
//* Returns index to insert using quadratic probing
//*/
//int HashTableQuad::quadProbeIndex(int n) {
//    // hash function n % M
//    int probe = n % size;
//    int i = 0;
//    // quadratic probe until an empty position or key that is being searched is found
//    while (table[probe] != 0 && table[probe] != n && i < size) {
//        probe = (probe + i * i) % size;
//        i++;
//    }
//    // flag -1 if already in table, else return index
//    return (table[probe] == n) ? -1 : ((i == size) ? -1 : probe);
//}
//
//
void HashTableQuad::rehash()
{
    std::vector<int> oldTable = table;
    int oldSize = size;

    // resize table to closest prime number after doubling old table size
    size *= 2;
    while (!isPrime(size)) { size++; }
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
//
//bool HashTableQuad::isIn(int n) {
//    int probe = n % size;
//    int i = 0;
//    while (i < size) {
//        if (table[probe] == n) {
//            return true;
//        }
//        if (!table[probe]) {
//            return false;
//        }
//        // probe next
//        probe = (probe + i * i) % size;
//        i++;
//    }
//    return false;
//}
void HashTableQuad::insert(int n)
{
    int index = quadProbeIndex(n);
    if (index != -1) // -1 index indicates value is already in hash table
    {
        // check if adding a key will exceed max load factor 
        if (double(num_keys + 1) / double(size) > max_lf)
        {
            // rehash and recompute index with quadratic probing
            rehash();
            index = quadProbeIndex(n);
        }
        // insertion index found - insert in table
        table[index] = n;
        num_keys++;
    }
}

/*
* Returns index to insert using quadratic probing
*/
int HashTableQuad::quadProbeIndex(int n) {
    // hash function n % M
    int probe = n % size;
    int i = 0;
    // quadratic probe until an empty position or key that is being searched is found
    while (table[probe] != 0 && table[probe] != n && i < size) {
        probe = (probe + i * i) % size;
        i++;
    }
    // flag -1 if already in table, else return index
    return (table[probe] == n) ? -1 : ((i == size) ? -1 : probe);
}

bool HashTableQuad::isIn(int n)
{
    int probe = n % size;
    int i = 0;
    while (table[probe] != 0 && i < size)
    {
        if (table[probe] == n)
        {
            return true;
        }
        else
        {
            probe = (probe + i * i) % size;
            i++;
        }
    }
    return false;
}


void HashTableQuad::printKeys()
{
    for (int i = 0; i < table.size(); i++)
    {
        std::cout << table[i] << std::endl;
    }
}

void HashTableQuad::printKeysAndIndexes()
{
    for (int i = 0; i < table.size(); i++)
    {
        std::cout << "Index: " << i << "key: " << table[i] << std::endl;
    }
}


std::vector<double> HashTableQuad::simProbeSuccess()
{
    // TODO, change following code after completing this function
    vector<double> result(9);
    return result;
}
// getter methods for priv fields 
int HashTableQuad::getNumKeys() { return num_keys; }
int HashTableQuad::getTableSize() { return size; }
double HashTableQuad::getMaxLoadFactor() { return max_lf; }