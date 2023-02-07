#ifndef HUGEINTEGER_H_
#define HUGEINTEGER_H_
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <random>

class HugeInteger
{
private:
	std::vector<int> number;
	bool sign = false;
public:
	// Required methods
	HugeInteger(const std::string& val);
	HugeInteger(int n);

	HugeInteger stdsub(const HugeInteger& h);
	HugeInteger(const HugeInteger& h);
	HugeInteger();
	std::string karatsuba(std::string lhs, std::string rhs);
	HugeInteger getHigh(int k) const;
	HugeInteger getLow(int k) const;
	HugeInteger add(const HugeInteger& h);
	HugeInteger Positiveadd(const HugeInteger& h);
	HugeInteger subtract(const HugeInteger& h);
	HugeInteger multiply(const HugeInteger& h);
	int compareTo(const HugeInteger& h);
	std::string toString();
};

#endif /* HUGEINTEGER_H_ */
