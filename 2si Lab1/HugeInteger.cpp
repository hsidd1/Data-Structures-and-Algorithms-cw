#include "HugeInteger.h"

HugeInteger::HugeInteger(const std::string& val) {
	std::vector<int> number;
	for (int i = 0; i < val.length(); i++) {
		// add to vector if valid ascii character 
		if (val[i] >= 48 && val[i] <= 57) {
			number.push_back(val[i] - 48);
		}
		else {
			throw std::invalid_argument("Error: received invalid ascii input");
		}
	}
}

HugeInteger::HugeInteger(int n) {
	if (n < 1) {
		throw std::invalid_argument("Error: n must be larger than or equal to 1");
	}
	srand(time(NULL));
	unsigned int digit = 0;
	std::vector<int> number;
	// add random digits based on input total digit amount
	for (int i = 0; i < n; i++) {
		digit = rand() % 10; // random num 0 - 9
		// if starting with leading 0 change to random num 1 - 9
		if (i == 0 && digit == 0) {
			digit = rand() % 9 + 1;
		}
		number.push_back(digit);
	}
}

/* Returns a new HugeInteger representing the sum of this HugeInteger and h.*/
HugeInteger HugeInteger::add(const HugeInteger& h) {

	return HugeInteger("");
}

HugeInteger HugeInteger::subtract(const HugeInteger& h) {
	// TODO
	return HugeInteger("");
}

HugeInteger HugeInteger::multiply(const HugeInteger& h) {
	// TODO
	return HugeInteger("");
}

int HugeInteger::compareTo(const HugeInteger& h) {
	// TODO
	return 0;
}

std::string HugeInteger::toString() {
	std::string output = "";
	for (int i = 0; i < this->HugeInteger.length(); )
	return output;
}
