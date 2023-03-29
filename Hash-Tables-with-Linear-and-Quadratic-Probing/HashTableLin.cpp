#include "HashTableLin.h"
#include <cmath>
using namespace std;

/*
creates a HashTableLin object representing an empty hash table with maximum 
allowed load factor equal to load
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

void HashTableLin::insert(int n)
{
    // TODO
}

void HashTableLin::rehash()
{
    // TODO
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

int HashTableLin::getNumKeys() {
    return num_keys;
}

int HashTableLin::getTableSize() {
    return size;
}

double HashTableLin::getMaxLoadFactor() {
    return max_lf;
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
