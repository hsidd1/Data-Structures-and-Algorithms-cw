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
    table.resize(size);
    /*for (int i = 0; i < size; i++)
    {
        table.push_back(0);
    }*/
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
        // insertion index found - insert in table
        if (((double)(num_keys+1) / (double)(size)) > max_lf)
        {
                //cout << "pre-rehash" << endl;
                //printKeysAndIndexes();
                // rehash and recompute index with quadratic probing
                rehash();
                index = quadProbeIndex(n);
            if (index == -1) {
                return;
            }
        }
        num_keys++;
        table[index] = n;
        //cout << "after rehash" << endl;
        //printKeysAndIndexes();
    }
}

/*
* Returns index to insert using quadratic probing
*/
int HashTableQuad::quadProbeIndex(int n) {
    // hash function n % M
    int probe = n%size;
    int i = 0;
    // quadratic probe until an empty position or key that is being searched is found
    while (table[probe] != 0 && table[probe] != n && i < size) {
        i++;
        probe = (n%size + i * i) % size;
    }
    // flag -1 if already in table, else return index
    return (table[probe] == n) ? -1 : ((i == size) ? -1 : probe);
}

bool HashTableQuad::isIn(int n)
{
    int probe = n % size;
    int i = 1;
    while (table[probe] != 0 && i < size)
    {
        if (table[probe] == n)
        {
            return true;
        }
        else
        {
            probe = (n%size + i * i) % size;
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
        std::cout << "Index: " << i << "\tkey: " << table[i] << std::endl;
    }
}


std::vector<double> HashTableQuad::simProbeSuccess()
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
            HashTableQuad new_table(NUM_KEYS, b);
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

int HashTableQuad::insertCount(int n) {
    // counts inserts 
    int index = quadProbeIndex(n);
    int count = quadProbeInterations(n);
    int num_probes = 1;
    if (index != -1) // -1 index indicates value is already in hash table
    {
        // check if adding a key will exceed max load factor 
        if (double(num_keys + 1) / double(size) > max_lf)
        {
            //rehash and recompute index with linear probing
            rehash();
            index = quadProbeIndex(n);
            count = quadProbeInterations(n);
        }
        // insertion index found - insert in table
        table[index] = n;
        //num_probes++;
        num_keys++;
    }
    return count;
}

int HashTableQuad::quadProbeInterations(int n) {
    // hash function n % M
    int probe = n % size;
    int i = 0;
    int j = 1;
    // quadratic probe until an empty position or key that is being searched is found
    while (table[probe] != 0 && table[probe] != n && i < size) {
        i++;
        j++;
        probe = (n % size + i * i) % size;
    }
    // flag -1 if already in table, else return index
    return j;
}

// getter methods for priv fields 
int HashTableQuad::getNumKeys() { return num_keys; }
int HashTableQuad::getTableSize() { return size; }
double HashTableQuad::getMaxLoadFactor() { return max_lf; }