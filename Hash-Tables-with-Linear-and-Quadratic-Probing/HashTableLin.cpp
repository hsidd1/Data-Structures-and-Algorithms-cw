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
    // find the nearest prime number -- increment until prime
    while (!isPrime(temp_size)) {
        temp_size++;
    }
    // temp size is prime after iteration
    size = temp_size;
    // fill table
    /*for (int i = 0; i < size; i++)
    {
        table.push_back(0);
    }*/
    table.resize(size);
}
 // self explanatory - checks if input int is prime 
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

//an O(n) only implementation (cringe) for fun:
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
int HashTableLin::linProbeInterations(int n) {
    // hash function n % M
    int probe = n % size;
    int i = 1;
    // linear probe until an empty position or key that is being searched is found
    while (table[probe] != 0 && table[probe] != n) {
        probe = (probe + 1) % size;
        i++;
    }
    // flag -1 if already in table, else return index
    //if (table[probe] == n) return -1;
    return i;
}

//std::vector<double> HashTableLin::simProbeSuccess()
//{
//    // TODO, change following code after completing this function
//    int NUM_RUNS = 1;
//    int NUM_KEYS = 10;
//    vector<double> result;
//    //vector<double> load_factors{0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
//    for (int i = 1; i <= 9; i+=1)
//    {
//
//        double b = (double) i/10.0;
//        for (int j = 0; j < NUM_RUNS; j++)
//        {
//        int num_probes = 0;
//            HashTableLin new_table(NUM_KEYS, b);
//            while(new_table.max_lf<b)
//            {
//                int rand_num = rand() * rand();
//                 num_probes +=  new_table.insertCount(rand_num);
//                // std::cout << num_probes << endl;
//            }
//        }
//        float avg = (float)num_probes / (float)(NUM_KEYS * NUM_RUNS);
//        std::cout << "average: " << endl;
//        result.push_back(avg);
//    }
//    return result;
//}

int HashTableLin::insertCount(int n) {
    // counts inserts 
    int index = linProbeIndex(n);
    int count = linProbeInterations(n);
    int num_probes = 1;
    if (index != -1) // -1 index indicates value is already in hash table
    {
        // check if adding a key will exceed max load factor 
        if (double(num_keys + 1) / double(size) > max_lf)
        {
            //rehash and recompute index with linear probing
          rehash();
            index = linProbeIndex(n);
            count = linProbeInterations(n);
        }
        // insertion index found - insert in table
        table[index] = n;
        //num_probes++;
        num_keys++;
    }
    return count;
}
// for bonus
std::vector<double> HashTableLin::simProbeUnsuccess()
{
    std::vector<double> testLambdas{ 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9 }, results(9);
    HashTableLin* test;
    std::vector<int> usedTests;
    int runRepitition = 100;
    int testNum = 100000;

    int i, j, k, l, x;
    double lambda, allRunsSum, allStepsSum;

   // cout << "Test Started for Probe Success" << endl;

    // This for loop tests each lambda defined above (ensure results and testLambdas are equal in size
    for (i = 0; i < testLambdas.size(); i++) {
        lambda = testLambdas[i];
        allRunsSum = 0;
        // Handles the number of tests that are to be averaged
        for (j = 0; j < runRepitition; j++) {
            allStepsSum = 0;
            test = new HashTableLin(testNum, lambda);
            // Adding fluff to the list
            for (k = 0; k < testNum; k++) {
                x = rand() * rand();
                while (test->isIn(x)) {
                    x = (rand()+1) * (rand()+1);
                }
                test->insert(x);
            }
            // Now testing isIn function for testNum times
            for (l = 0; l < testNum; l++) {
                x = rand() * rand();
                while (test->isIn(x)) {
                    x = (rand()+1) * (rand()+1);
                }
                allStepsSum += test->isInFalseCount(x);
            }
            allRunsSum = (double)allStepsSum / (double)testNum;
           // cout << "Unsuccessful Test for Lambda " << lambda << ": " << (double)allStepsSum / (double)testNum << std::endl;
            delete test;
        }
        results.at(i) = allRunsSum;
    }

    return results;
}
int HashTableLin::isInFalseCount(int n) { // -1 if the value exists
    int count = 0;

    int defaultHashValue = n % size; int newHash;

    for (int i = defaultHashValue; i < defaultHashValue + size; i++) {
        newHash = i % size;
        count++;
        if (table[newHash] == n)
            return -1;
        if (table[newHash] == 0)
            return count;
    }

    return count;
}

// getter methods for priv fields 
int HashTableLin::getNumKeys() {return num_keys;}
int HashTableLin::getTableSize() {return size;}
double HashTableLin::getMaxLoadFactor() {return max_lf;}