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
	HugeInteger b = h;

	HugeInteger temp_h = h;
	if (this->toString() == "0") { return HugeInteger(h); }
	if (temp_h.toString() == "0") {return HugeInteger(*this); }

	if (this->compareTo(h) == 0) {
		if (aNeg && bNeg) { // both negative
			std::string sum = "-" + Positiveadd(h).toString();
			return HugeInteger(sum);
		}
		
		if (!aNeg && !bNeg) { // both positive
			return Positiveadd(h);
		}
	}
	if (this->compareTo(h) == 1) {
		if (aNeg && bNeg) { // both negative
			std::string sum = "-" + Positiveadd(h).toString();
			return HugeInteger(sum);
		}
		if (!aNeg && bNeg) { // pos and neg
			b.sign = false;
			return subtract(b);
		}
		if (!aNeg && !bNeg) { // both positive
			return Positiveadd(h);
		}
	}
	if (this->compareTo(h) == -1) {
		if (aNeg && bNeg) { // both negative
			std::string sum = "-" + Positiveadd(h).toString();
			return HugeInteger(sum);
		}
		if (!aNeg && !bNeg) { // both positive
			return Positiveadd(h);
		}
		if (aNeg && !bNeg) { // neg and pos
			this->sign = false;
			return b.subtract(*this); // returns b - a 
		}
	}
	/*
	if (aNeg && bNeg) {
		// both are negative --> add them as positives and add a minus sign

		std::string output = Positiveadd(HugeInteger(h)).toString();
		output.std::string::insert(0, "-");
		return HugeInteger(output);
	}
	
	else if (!aNeg && bNeg) {
		// a is positive and b is negative
		// return a subtract b
		return stdsub(HugeInteger(h));
	}
	else if (aNeg && !bNeg) {
		// a is negative and b is positive 
		// return b subtact a 
		HugeInteger b = h;
		return b.subtract(HugeInteger(*this));
	}
	else {
		// a and b are positive
		return Positiveadd(HugeInteger(h));
	}
	*/
}

HugeInteger HugeInteger::Positiveadd(const HugeInteger& h) {
	std::string sum;
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
	std::string sub = "";
	std::vector<int> temp_h = h.number;
	HugeInteger another_h = h;

	// ----------- checking zeros ------------------------------------------------------//
	//if (this->toString() == another_h.toString()) { return HugeInteger("0"); }
	if (this->toString() == "0") {
		if (!another_h.sign) // 0 - a positive number
		{
			if (another_h.toString() == "0") return HugeInteger(*this);
			sub += "-" + another_h.toString();
			return HugeInteger(sub);
		}
		else { // 0 - negative number 
			sub = another_h.toString();
			sub.erase(0, 1); // remove the - 
			return HugeInteger(sub);
		}
	}
	if (another_h.toString() == "0") { return HugeInteger(*this); } // any number - 0 
// -----------------------------------------------------------------------------------//

	// sign trackers 
	bool aNeg = this->sign;
	bool bNeg = h.sign;

	// ---------------- checking compareTo conditions -------------------------------//
	if (this->compareTo(h) == 1) { // this is larger than h 
		if (!aNeg && !bNeg) { // both pos
			return stdsub(HugeInteger(h)); // standard subtraction
		}
		if (aNeg && bNeg) { // both neg
			return another_h.stdsub(*this); // wanna make both pos and do h - this 
		}
		if (!aNeg && bNeg) { // +ve - a positive
			return Positiveadd(HugeInteger(h));
		}
		// not even possible for a -ve to be bigger than a pos
		if (aNeg && !bNeg) {
			sub += "-" + Positiveadd(HugeInteger(h)).toString();// wanna add them and add a - sign
			return HugeInteger(sub);
		}
	}

	if (this->compareTo(h) == 0) { // same 
		//if (aNeg && bNeg) { // neg - neg
		//	sub += "-" + Positiveadd(h).toString();
		//	return HugeInteger(sub);
		//}
		//else if (!aNeg && !bNeg) { // same and both pos 
			return HugeInteger("0");
		}
	
	if(this->compareTo(h) == -1) { // this smaller than h
		if (!aNeg && !bNeg) { // both pos
			sub += "-" + another_h.stdsub(*this).toString();
			return HugeInteger(sub);
		}
		if (aNeg && bNeg) { // both neg
			sub += "-" + stdsub(HugeInteger(h)).toString();
			return HugeInteger(sub);
		}
		if (aNeg && !bNeg) {
			sub += "-" + Positiveadd(HugeInteger(h)).toString();
			return HugeInteger(sub);
		}
	}
//------------------------------------------------------------------------------//


	// making them the same size by adding leading 0s to the smaller one
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

	if (!aNeg && bNeg) { return Positiveadd(HugeInteger(h)); }

	if (!aNeg && bNeg || aNeg && !bNeg) {
		std::string output = Positiveadd(HugeInteger(h)).toString();
		output.std::string::insert(0, "-");
		return HugeInteger(output);
	}
	
}

HugeInteger HugeInteger::stdsub(const HugeInteger& h) {
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
	// remove leading zeros
	int start = 0;
	for (int i = 0; i < sub.size(); i++) {
		if (sub[i] != '0') {
			start = i;
			break;
		}
	}
	return HugeInteger(sub.substr(start));
}
HugeInteger HugeInteger::multiply(const HugeInteger& h) {
	HugeInteger result, a = *this, b = h;
	
	if ((this->number[0] == 0 && this->number.size() == 1) || (b.number[0] == 0 && b.number.size() == 1)) {
		return HugeInteger("0");
	}
	
	result.number.resize(a.number.size() + b.number.size(), 0);
	result.sign = a.sign ^ b.sign;

	for (int i = a.number.size() - 1; i >= 0; i--) {
		for (int j = b.number.size() - 1; j >= 0; j--) {
			result.number[i + j + 1] += a.number[i] * b.number[j];
			result.number[i + j] += result.number[i + j + 1] / 10;
			result.number[i + j + 1] %= 10;
		}
	}
	while (result.number[0] == 0){result.number.erase(result.number.begin());}
	return result;
}
//HugeInteger HugeInteger::multiply(const HugeInteger& h) {
//	HugeInteger result;
//	HugeInteger a = *this;
//	HugeInteger b = h;
//	if (this->toString() == "0" || b.toString() == "0") {
//		return HugeInteger("0");
//	}
//	if (this->toString() == "1" && number.size() == 1) {
//		return HugeInteger(h);
//	}
//	if (b.toString() == "1" && h.number.size() == 1) {
//		return HugeInteger(*this);
//	}
//	if (a.number.size() < b.number.size()) {
//		std::swap(a, b);
//	}
//	result.number.resize(a.number.size() + b.number.size(), 0);
//	result.sign = a.sign ^ b.sign;
//
//	for (int i = a.number.size() - 1; i >= 0; i--) {
//		for (int j = b.number.size() - 1; j >= 0; j--) {
//			result.number[i + j + 1] += a.number[i] * b.number[j];
//			result.number[i + j] += result.number[i + j + 1] / 10;
//			result.number[i + j + 1] %= 10;
//		}
//	}
//	//hile (result.number.size() > 1 && result.number.back() == 0) {
//	//	result.number.pop_back();
//	
//
//	while (result.number[0] == 0)
//	{
//		result.number.erase(result.number.begin());
//	}
//	return result;
//}

/*
HugeInteger HugeInteger::multiply(const HugeInteger& h) {
	HugeInteger b = h;
	if (this->toString() == "0" || b.toString() == "0") { 
		return HugeInteger("0"); 
	}
	HugeInteger a = *this;
	HugeInteger result = HugeInteger();
	result.number.resize(a.number.size() + b.number.size() - 1, 0);

	int sign = 1;
	if (a.sign != b.sign) {
		sign = -1;
	}

	for (int i = 0; i < a.number.size(); i++) {
		for (int j = 0; j < b.number.size(); j++) {
			result.number[i + j] += a.number[i] * b.number[j];
			result.number[i + j + 1] += result.number[i + j] / 10;
			result.number[i + j] %= 10;
		}
	}

	result.sign = (sign == 1) ? false : true;
	// remove leading zeros
	std::string res = result.toString();
	int start = 0;
	for (int i = 0; i < result.number.size(); i++) {
		if (res[i] != '0') {
			start = i;
			break;
		}
	}	return HugeInteger(res.substr(start));
}
*/



int HugeInteger::compareTo(const HugeInteger& h) {
	/*Returns -1 if this HugeInteger is less
than h, 1 if this HugeInteger is larger than h, and 0 if this HugeInteger is equal
to h.*/

	if (!h.sign && this->sign) { // h positive and this negative - h is bigger
		return -1;
	}
	else if ((h.sign && !this->sign)) { // h negative and this positive - this is bigger 
		return 1;
	}

	// if this has more digits than h
	if (this->number.size() > h.number.size()) {
		if (!this->sign && !h.sign)
			return 1;
		else return -1;
	}
	// if h has more digits than this
	else if (h.number.size() > this->number.size()) {
		if (!h.sign && !this->sign)
			return -1;
		else return 1;
	}


	else { // same length
		// compare most significant bits
		for (int i = 0; i < this->number.size(); i++) {
			if (this->number[i] > h.number[i]) {
				if (!this->sign && !h.sign)
					return 1;
				else return -1;
			}
			else if (h.number[i] > this->number[i]) {
				if (!this->sign && !h.sign)
					return -1;
				else return 1;
			}
			else if (h.number[i] < this->number[i]) return 1;
		}
		return 0;

	}
}

std::string HugeInteger::toString() {

/* Returns a string representing the sequence of digits
corresponding to the decimal representation of this HugeInteger */

	std::string output;
	if (sign) {output += "-";}
	for (int i = 0; i < this->number.size(); i++) {
		output += std::to_string(this->number[i]);
	}
	return output;
}
