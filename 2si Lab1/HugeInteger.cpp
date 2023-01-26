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
	bool aNeg = this->sign;
	bool bNeg = h.sign;

	if (aNeg && bNeg) {
		// both are negative --> add them as positives and add a minus sign?
		
		std::string output =  Positiveadd(HugeInteger(h)).toString();
		output.std::string::insert(0, "-");
		return HugeInteger(output);
	}
	else if (!aNeg && bNeg) {

	}
}

HugeInteger HugeInteger::Positiveadd(const HugeInteger& h) {
	std::string sum = "";
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
	for (int i = this->number.size() - 1; i >= 0; i--) {
		int digit1 = this->number[i];
		int digit2 = temp_h[i];
		digit1 += digit2 + carry;
		carry = digit1 / 10;
		digit1 %= 10;
		sum.std::string::insert(0, 1, digit1 + 48);
	}

	if (carry > 0) {
		sum.std::string::insert(0, 1, carry + 48);
	}

	return HugeInteger(sum);
}

HugeInteger HugeInteger::subtract(const HugeInteger& h) {
	/*Returns a new HugeInteger
representing the difference between this HugeInteger and h.*/
	std::string sub;
	std::vector<int> temp_h = h.number;
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

	int borrow = 0;
	for (int i = this->number.size() - 1; i >= 0; i--) {
		int digit1 = this->number[i];
		int digit2 = temp_h[i];
		digit1 -= (digit2 + borrow);
		if (digit1 < 0) {
			digit1 += 10;
			borrow = 1;
		}
		else
			borrow = 0;
		sub.std::string::insert(0, 1, digit1 + 48);
	}
	return HugeInteger(sub);
}

HugeInteger HugeInteger::multiply(const HugeInteger& h) {
	// TODO
	return HugeInteger("");
}

int HugeInteger::compareTo(const HugeInteger& h) {
	// if this has more digits or if this is positive and h is negative
	if ((!this->sign && h.sign) || this->number.size() > h.number.size() ) {
		return 1;
	}
	// if h has more digits or if h is positive and this is negative
	else if ((!h.sign && this->sign) || h.number.size() > this->number.size() ) {
		return -1;
	}
	else { // same length
		//std::_Vector_iterator<std::_Vector_val<std::_Simple_types<int>>> it_this = this->number.begin();
		//auto it_h = h.number.begin();

		//auto MSB_this = this->number.front();
		//auto MSB_h = h.number.front();

		for (int i = 0; i < this->number.size(); i++) {
			if (this->number[i] > h.number[i]) {
				return 1;
			}
			else if (h.number[i] > this->number[i]) {
				return -1;
			}
			else return 0;
			/*
			if (MSB_this > MSB_h)
				return 1;
			else if (MSB_h > MSB_this) {
				return -1;
			}
			else return 0;

			it_this++;
			it_h++;
			*/
		}
	}
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
