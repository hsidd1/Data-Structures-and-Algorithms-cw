#ifndef HASHTABLELIN_H_
#define HASHTABLELIN_H_

#include <vector>

class HashTableLin
{
private:
	// must contain this private field
	std::vector<int> table; // table storing keys
	// defining other private fields to store:
	// 1. the size of the table
	int size;
	// 2. the number of keys stored in the table
	int num_keys;
	// 3. the maximum load factor allowed
	double max_lf;

public:
	// required constructor
	HashTableLin(int maxNum, double load);

	// required methods
	void insert(int n);
	bool isIn(int n);
	void printKeys();
	void printKeysAndIndexes();
	int getNumKeys();
	int getTableSize();
	double getMaxLoadFactor();
	static std::vector<double> simProbeSuccess();
	static std::vector<double> simProbeUnsuccess(); // for bonus

	// additional methods
	bool isPrime(int num);
	int linProbeIndex(int n);

	// used for testing
	std::vector<int> getTable() {
		return table;
	};

private:
	// required methods
	void rehash();
};

#endif /* HASHTABLELIN_H_ */
