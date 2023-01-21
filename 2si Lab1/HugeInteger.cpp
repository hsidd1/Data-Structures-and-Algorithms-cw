#include "HugeInteger.h"


HugeInteger::HugeInteger(const std::string& val) {

/* creates a HugeInteger from the decimal string representation val.
The string contains an optional minus sign at the beginning followed by one or more decimal digits.
No other characters are allowed in the string. */

	int start = 0; // standard start for interating 'val'
	if (val.length() == 0) 
		throw std::invalid_argument("Error: Empty string!");
	if (val[0] == '-') {
		sign = true; 
		start = 1; // skip first character in iteration if its a '-'
	}
	for (int i = start; i < val.length(); i++) {
		// add to vector if valid ascii character 
		if (val[i] >= 48 && val[i] <= 57) {
			number.push_back(val[i] - 48);
		}
		else {
			throw std::invalid_argument("Error: Received invalid ASCII input");
		}
	}
}

HugeInteger::HugeInteger(int n) {

/* creates a random HugeInteger of n digits, the first digit
being different from 0; n must be larger or equal to 1.*/

	if (n < 1) {
		throw std::invalid_argument("Error: n must be larger than or equal to 1");
	}
	srand(time(NULL));
	unsigned int digit = 0;
	// add random digits based on input total digit amount
	for (int i = 0; i < n; i++) {
		digit = rand() % 10; // random num 0 - 9
		// ensure no leading 0's 
		if (i == 0 && digit == 0) {
			digit = rand() % 9 + 1;
		}
		number.push_back(digit);
	}
}

HugeInteger HugeInteger::add(const HugeInteger& h) {

/* Returns a new HugeInteger representing the sum of this HugeInteger and h.*/


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

/* Returns a string representing the sequence of digits
corresponding to the decimal representation of this HugeInteger */

	std::string output;
	if (sign) {
		output += "-";
	}
	for (int i = 0; i < this->number.size(); i++) {
		output += std::to_string(this->number[i]);
	}
	return output;
}
