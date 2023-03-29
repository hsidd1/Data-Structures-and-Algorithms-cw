#include "Poly.h"

Poly::Poly() // Complexity O(1) space O(1)
{
	head = new PolyNode(-1, 0, NULL);
}

Poly::Poly(const std::vector<int>& deg, const std::vector<double>& coeff)  // Complexity O(n) space O(n)
{
	PolyNode* readerHead;
	head = new PolyNode(-1, 0, NULL);
	readerHead = head;

	for (int i = 0; i < deg.size(); i++) {
		readerHead->next = new PolyNode(deg[i], coeff[i], NULL);
		readerHead = readerHead->next;
		size++;
	}
}

Poly::~Poly() // Complexity O(n) space O(1)
{
	PolyNode* readerHead = head;
	PolyNode* prevHead = NULL;
		
	while (readerHead) {
		prevHead = readerHead;
		readerHead = readerHead->next;
		delete prevHead;
	}

	size = 0;
}

void Poly::addMono(int i, double c)  // Complexity O(n) space O(1)
{

	PolyNode* temp;

	PolyNode* readerHead = head->next;
	PolyNode* prevHead = head;

	while (readerHead) {
		if (i < readerHead->deg) {
			if (!readerHead->next) {
				readerHead->next = new PolyNode(i, c, NULL);
				size++;
				return;
			}
			prevHead = readerHead;
			readerHead = readerHead->next;
			continue;
		}
		if (i == readerHead->deg) {
			readerHead->coeff += c;
			if (readerHead->coeff == 0) {
				prevHead->next = readerHead->next;
				delete readerHead;
				size--;
			}
			return;
		}
		if (i > readerHead->deg) {
			temp = new PolyNode(i, c, readerHead);
			prevHead->next = temp;
			size++;
			return;
		}
	}

	head->next = new PolyNode(i, c, NULL);
	size++;

}

void Poly::addPoly(const Poly& p)  // Complexity O(n^2) :( space O(n)
{
	PolyNode* readerHead = p.head->next;

	if (!readerHead) {
		return;
	}

	while (readerHead) {
		this->addMono(readerHead->deg, readerHead->coeff);
		readerHead = readerHead->next;
	}

}

void Poly::multiplyMono(int i, double c)  // Complexity O(n) space O(1)
{
	if (!c || !head->next) {
		this->~Poly(); 
		head = new PolyNode(-1, 0, NULL);
		return;
	}

	PolyNode* readerHead = this->head->next;
	
	while (readerHead) {
		readerHead->deg += i;
		readerHead->coeff *= c;
		readerHead = readerHead->next;
	}

}

void Poly::multiplyPoly(const Poly& p)  // Complexity O(n^3) space O(n)
{
	PolyNode* readerHead = p.head->next;
	Poly thisCopy;
	Poly tempPoly = Poly();

	if (!readerHead) {
		this->~Poly();
		head = new PolyNode(-1, 0, NULL);
	}

	while (readerHead) {
		this->duplicate(thisCopy);
		thisCopy.multiplyMono(readerHead->deg, readerHead->coeff);
		tempPoly.addPoly(thisCopy);
		readerHead = readerHead->next;
	}
	tempPoly.duplicate(*this);
}

void Poly::duplicate(Poly& outputPoly)  // Complexity O(n) space O(n)
{
	std::vector<int> deg;
	std::vector<double> coeff;
	outputPoly.~Poly();
	outputPoly.head = new PolyNode(-1, 0, NULL);
	PolyNode* thisReaderHead = head->next;
	PolyNode* outputReaderHead = outputPoly.head;

	while (thisReaderHead) {
		outputReaderHead->next = new PolyNode(thisReaderHead->deg, thisReaderHead->coeff, NULL);
		outputReaderHead = outputReaderHead->next;
		thisReaderHead = thisReaderHead->next;
	}

	outputPoly.size = size;

}

int Poly::getDegree()  // Complexity O(1) space O(1)
{
	int deg;
	head->next ? deg = head->next->deg : deg = head->deg;
	return deg;
}

int Poly::getTermsNo()  // Complexity O(1) space O(1)
{
	return size;
}

double Poly::evaluate(double x)  // Complexity O(n) space O(1)
{
	double result = 0;
	PolyNode* readerHead = head->next;

	while (readerHead) {
		result += readerHead->coeff * (pow(x, readerHead->deg));
		readerHead = readerHead->next;
	}

	return result;
}

std::string Poly::toString()  // Complexity O(n) space O(1)
{
	
	std::string polyString = "";

	if (size) {
		PolyNode* readerHead = head->next;
		std::string polyString = "degree=" + std::to_string(readerHead->deg) + ';';

		while (readerHead) {
			polyString += (' ' + "a(" + std::to_string(readerHead->deg) + ")=" + std::to_string(readerHead->coeff) + ';');
			readerHead = readerHead->next;
		}
	}
	else {
		polyString = "degree=-1; a(-1)=0;";
	}
	return polyString;
}
