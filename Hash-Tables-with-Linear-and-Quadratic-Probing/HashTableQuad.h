#ifndef HASHTABLEQUAD_H_
#define HASHTABLEQUAD_H_

#include <vector>
#include <cmath>
#include <iostream>
class HashTableQuad
{
private:
	// must contain this private field
	std::vector<int> table; // table storing keys
	// define other private fields to store:
	// 1. the size of the table
	int size;
	// 2. the number of keys stored in the table
	int num_keys;
	// 3. the maximum load factor allowed
	double max_lf;
public:
	// required constructor
	HashTableQuad(int maxNum, double load);

	// required methods
	void insert(int n);
	bool isIn(int n);
	void printKeys();
	void printKeysAndIndexes();
	int getNumKeys();
	int getTableSize();
	double getMaxLoadFactor();
	static std::vector<double> simProbeSuccess();
	
	// added stuff
	bool isPrime(int num);
	int quadProbeIndex(int n);
	int insertCount(int n);
	int quadProbeInterations(int n);
	// used for testing
	std::vector<int> getTable() {
		return table;
	};

private:
	// required methods
	void rehash();
};

#endif /* HASHTABLEQUAD_H_ */
