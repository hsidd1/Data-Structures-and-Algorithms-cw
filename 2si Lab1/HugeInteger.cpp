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
	sign = false;
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

/* Copy Constructor */
HugeInteger::HugeInteger(const HugeInteger& k) {
	this->sign = k.sign;
	for (int i = 0; i < k.number.size(); i++) {
		this->number.push_back(k.number[i]);
	}
}

/* Default constructor */
HugeInteger::HugeInteger() {
	number = std::vector<int>();
	sign = false;
}

HugeInteger HugeInteger::add(const HugeInteger& h) {
	HugeInteger sum;
	std::vector<int> temp_h = h.number;

	// adding leading 0's to fill up smaller vector to force same size 
	if (this->number.size() < temp_h.size()) {
		int diff = temp_h.size() - this->number.size();
		for (int i = 0; i < diff; i++) {
			this->number.insert(this->number.begin(), 0);
		}
	}
	else {
		int diff = this->number.size() - temp_h.size();
		for (int i = 0; i < diff; i++) {
			temp_h.insert(temp_h.begin(), 0);
		}
	}

	int carry = 0;
	for (int i = 0; i < this->number.size(); i++) {
		int digit1 = this->number[i];
		int digit2 = temp_h[i];
		digit1 = digit1 % 10 + digit2 + carry;
		carry = digit1 / 10;
		sum.number.push_back(digit1);
	}

	if (carry > 0) {
		sum.number[0]+=(carry);
	}
	return sum;
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
