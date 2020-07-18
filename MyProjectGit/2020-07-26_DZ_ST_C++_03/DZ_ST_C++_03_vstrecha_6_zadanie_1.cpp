// ������� �� ����� DZ_ST_C++_03.pdf
// ������� �6
// ����: ���������� ����������
// ������� 1.
/*
�������� ����� ����� (��� ����������� ��� ����� ������-
��� ����). ��������� ���������� ���������� ����������
��� ���� �������������� �������� ��� ������ � �������
(�������� +, -, *, /).
*/

#include <iostream>
#include <clocale>
#include <iomanip>
#define pendl cout << endl
using namespace std;


// ����� �����
class Fraction {
private:
	int numerator{ 0 };    // ���������
	int denominator{ 1 };  // �����������
public:
	// ����������� �� ���������
	Fraction() {}

	// ����������� � �����������
	Fraction(int numerator, int denominator) 
		: numerator(numerator), denominator(denominator)
	{}

	// ����������� �����������
	Fraction(const Fraction& fraction2) {
		*this = fraction2;
	}

	// SETTER-�
	void setNumerator(int numerator) { this->numerator = numerator; }
	void setDenominator(int denominator) { this->denominator = denominator; }

	// GETTER-�
	int getNumerator() const { return numerator; }
	int getDenominator() const { return denominator; }

	// ����� ����������� �������� �����
	//       �� �����-��������� � �����-��������� ������
	void copy(const Fraction& fraction2) {
		numerator = fraction2.numerator;
		denominator = fraction2.denominator;
	}

	// ����� �������� ������
	bool sum(const Fraction& fraction2) {
		if (denominator != fraction2.denominator) {
			int lcm = Fraction::lcm(*this, fraction2);
			if (lcm) {
				numerator *= lcm / denominator;
				denominator = lcm;
				numerator += fraction2.numerator * lcm / fraction2.denominator;
			}
			else return false;
		}
		else {
			numerator += fraction2.numerator;
		}
		return true;
	}

	// ����� ��������� ������
	bool sub(const Fraction& fraction2) {
		if (denominator != fraction2.denominator) {
			int lcm = Fraction::lcm(*this, fraction2);
			if (lcm) {
				numerator *= lcm / denominator;
				denominator = lcm;
				numerator -= fraction2.numerator * lcm / fraction2.denominator;
			}
			else return false;
		}
		else {
			numerator -= fraction2.numerator;
		}
		return true;
	}

	// ����� ��������� ������
	bool mul(const Fraction& fraction2) {
		int _denominator = denominator;
		_denominator *= fraction2.denominator;
		if (_denominator) {
			denominator = _denominator;
			numerator *= fraction2.numerator;
			return true;
		}
		else return false;
	}

	// ����� ������� ������
	bool div(const Fraction& fraction2) {
		int _denominator = denominator;
		_denominator *= fraction2.numerator;
		if (_denominator) {
			denominator = _denominator;
			numerator *= fraction2.denominator;
			return true;
		}
		else return false;
	}

private:
	// ����� ���������� ����������� ������ �������� (���)
	//       ��� �� ���������� Least Common Multiple (LCM)
	// !!! - ������� 0 - ��� ������:
	// 1) �����-�� �������� �������� ����� 0;
	// 2) ��������� �������� ��� ��������� ������������ int
	// !!! ����� ��������
	static int lcm(const Fraction& fraction1, const Fraction& fraction2) {

		// �������� ����������
		long long int min = 0;             // ������� ����� �� ����
		long long int max = 0;             // ������� ����� �� ����
		long long int multiplier = 0;      // ��������� �������� �����
		long long int lcm = 0;             // LCM - ���

		// !!! ����� � �����, �� ������� ��������������:
		// min � max - ������ �����,
		// multiplier - ����� ��� ������ ����������

		// ��������� �������� ������������ ������ � ����������
		// ���� ������ ��� �� ����� 0, ����� - ������ - ������� 0
		if (fraction1.denominator) min = fraction1.denominator;
		else return 0;
		if (fraction2.denominator) max = fraction2.denominator;
		else return 0;

		// ������ ������ ����� (�������� ��� �����, �������������)
		min = min < 0 ? -min : min;
		max = max < 0 ? -max : max;

		// !!! ����� min � max ������ ���� �����
		// ������� ����� � �������� �� ��������
		// �������� � �������� ������
		if (min > max) {
			multiplier = max;
			max = min;
			min = multiplier;
		}

		// !!! ����� multiplier ������ ��� �����
		// �������� multiplier ��������� ��������
		multiplier = 1;

		// ���� ���������� ���
		while (lcm < INT_MAX) {

			// ������ ��������� � ���
			// - ������� ������� ����� �� ���������
			lcm = max * multiplier;

			// ���� ������� �� ������� ��� �� ������� ����� ����� 0
			// - ���� ��� - ������� ���
			if (lcm % min == 0) return (int)lcm;

			// ����� - ����������� ��������� �� 1
			else ++multiplier;

			//  � ������ �� ��������� �������� �����
		}

		// ���� lcm �� ������ INT_MAX - ������ - ������� 0
		return 0;
	}

public:
	// �������� ������������� ������� ���������� ��������� +
	friend Fraction operator+(const Fraction& fraction1, const Fraction& fraction2);

	// �������� ������������� ������� ���������� ��������� -
	friend Fraction operator-(const Fraction& fraction1, const Fraction& fraction2);

	// �������� ������������� ������� ���������� ��������� *
	friend Fraction operator*(const Fraction& fraction1, const Fraction& fraction2);

	// �������� ������������� ������� ���������� ��������� /
	friend Fraction operator/(const Fraction& fraction1, const Fraction& fraction2);
};
// ����� ������


// ������������� ������� ���������� ��������� +
Fraction operator+(const Fraction& fraction1, const Fraction& fraction2) {
	Fraction fraction3;
	if (fraction1.denominator != fraction2.denominator) {
		int lcm = Fraction::lcm(fraction1, fraction2);
		if (lcm) {
			fraction3.denominator = lcm;
			fraction3.numerator =
				fraction1.numerator * lcm / fraction1.denominator +
				fraction2.numerator * lcm / fraction2.denominator;
		}
	}
	else {
		fraction3.denominator = fraction1.denominator;
		fraction3.numerator = fraction1.numerator + fraction2.numerator;
	}
	return fraction3;
}
// ����� ������������� ������� ��������� +


// ������������� ������� ���������� ��������� -
Fraction operator-(const Fraction& fraction1, const Fraction& fraction2) {
	Fraction fraction3;
	if (fraction1.denominator != fraction2.denominator) {
		int lcm = Fraction::lcm(fraction1, fraction2);
		if (lcm) {
			fraction3.denominator = lcm;
			fraction3.numerator =
				fraction1.numerator * lcm / fraction1.denominator -
				fraction2.numerator * lcm / fraction2.denominator;
		}
	}
	else {
		fraction3.denominator = fraction1.denominator;
		fraction3.numerator = fraction1.numerator - fraction2.numerator;
	}
	return fraction3;
}
// ����� ������������� ������� ��������� -


// ������������� ������� ���������� ��������� *
Fraction operator*(const Fraction& fraction1, const Fraction& fraction2) {
	Fraction fraction3;

	fraction3.denominator = fraction1.denominator * fraction2.denominator;
	fraction3.numerator = fraction1.numerator * fraction2.numerator;

	return fraction3;
}
// ����� ������������� ������� ��������� *


// ������������� ������� ���������� ��������� /
Fraction operator/(const Fraction& fraction1, const Fraction& fraction2) {
	Fraction fraction3;

	fraction3.denominator = fraction1.denominator * fraction2.numerator;
	fraction3.numerator = fraction1.numerator * fraction2.denominator;

	return fraction3;
}
// ����� ������������� ������� ��������� /


// ������� ����������� ������ ����� ����� �� ������ ����� �����
std::streamsize widthLine_From_widthNumber(std::streamsize widthNumber) {
	return widthNumber + 2;
}
// ����� �������


// ������� ����������� ������ ����� �����
int widthNumber_From_fraction(const Fraction& fraction) {
	int max = 0;
	if (fraction.getDenominator() > fraction.getNumerator()) {
		max = fraction.getDenominator();
	}
	else {
		max = fraction.getNumerator();
	}

	int limit = 1;
	int width = 0;

	while (width < 9) {
		limit *= 10;
		++width;
		if (max < limit) return width;
	}

	return 0;
}
// ����� �������


// ������� ������������ �������������� �������� � �������
void showFraction(
	const char& sign,             // ���� ��������
	const Fraction& fraction1,    // ����� 1
	const Fraction& fraction2,    // ����� 2
	const Fraction& fraction3     // ����� 3
) {
	std::streamsize indent = 13;   // ����� ������

	std::streamsize widthNumber1 = widthNumber_From_fraction(fraction1);
	std::streamsize widthLine1 = widthLine_From_widthNumber(widthNumber1);

	std::streamsize widthNumber2 = widthNumber_From_fraction(fraction2);
	std::streamsize widthLine2 = widthLine_From_widthNumber(widthNumber2);

	std::streamsize widthNumber3 = widthNumber_From_fraction(fraction3);
	std::streamsize widthLine3 = widthLine_From_widthNumber(widthNumber3);

	// ����� ����������
	cout
		<< setw(indent) << ""
		<< setw(1) << left << ""
		<< setw(widthNumber1) << left << fraction1.getNumerator()
		<< setw(1) << left << ""
		<< setw(3) << left << ""
		<< setw(1) << left << ""
		<< setw(widthNumber2) << left << fraction2.getNumerator()
		<< setw(1) << left << ""
		<< setw(3) << left << ""
		<< setw(1) << left << ""
		<< setw(widthNumber3) << left << fraction3.getNumerator()
		<< setw(1) << left << ""
		<< endl;

	// ������� �����
	cout
		<< setw(indent) << ""
		<< setw(0) << left << ""
		<< setw(widthLine1) << left << setfill('-') << "-" << setfill(' ')
		<< setw(0) << left << ""
		<< setw(1) << left << " " << setw(1) << left << sign << setw(1) << left << " "
		<< setw(0) << left << ""
		<< setw(widthLine2) << left << setfill('-') << "-" << setfill(' ')
		<< setw(0) << left << ""
		<< setw(3) << left << " = "
		<< setw(0) << left << ""
		<< setw(widthLine3) << left << setfill('-') << "-" << setfill(' ')
		<< setw(0) << left << ""
		<< endl;

	// ����� ������������
	cout
		<< setw(indent) << ""
		<< setw(1) << left << ""
		<< setw(widthNumber1) << left << fraction1.getDenominator()
		<< setw(1) << left << ""
		<< setw(3) << left << ""
		<< setw(1) << left << ""
		<< setw(widthNumber2) << left << fraction2.getDenominator()
		<< setw(1) << left << ""
		<< setw(3) << left << ""
		<< setw(1) << left << ""
		<< setw(widthNumber3) << left << fraction3.getDenominator()
		<< setw(1) << left << ""
		<< endl;
}
// ����� �������


// ������� ������������ ��������� ������
void showCreatedFraction(
	const Fraction& fraction1,    // ����� 1
	const Fraction& fraction2     // ����� 2
) {
	std::streamsize indent = 3;   // ����� ������

	std::streamsize widthNumber1 = widthNumber_From_fraction(fraction1);
	std::streamsize widthLine1 = widthLine_From_widthNumber(widthNumber1);

	std::streamsize widthNumber2 = widthNumber_From_fraction(fraction2);
	std::streamsize widthLine2 = widthLine_From_widthNumber(widthNumber2);

	// ����� ����������
	cout
		<< setw(indent) << ""
		<< setw(10) << left << ""
		<< setw(1) << left << ""
		<< setw(widthNumber1) << left << fraction1.getNumerator()
		<< setw(1) << left << ""
		<< setw(3) << left << ""
		<< setw(10) << left << ""
		<< setw(1) << left << ""
		<< setw(widthNumber2) << left << fraction2.getNumerator()
		<< setw(1) << left << ""
		<< endl;

	// ������� �����
	cout
		<< setw(indent) << ""
		<< setw(10) << left << "����� 1 = "
		<< setw(widthLine1) << left << setfill('-') << "-" << setfill(' ')
		<< setw(3) << left << " ; "
		<< setw(10) << left << "����� 2 = "
		<< setw(widthLine2) << left << setfill('-') << "-" << setfill(' ')
		<< endl;

	// ����� ������������
	cout
		<< setw(indent) << ""
		<< setw(10) << left << ""
		<< setw(1) << left << ""
		<< setw(widthNumber1) << left << fraction1.getDenominator()
		<< setw(1) << left << ""
		<< setw(3) << left << ""
		<< setw(10) << left << ""
		<< setw(1) << left << ""
		<< setw(widthNumber2) << left << fraction2.getDenominator()
		<< setw(1) << left << ""
		<< endl;
}
// ����� �������


// ������� �������
int main() {
	setlocale(LC_ALL, "ru");

	// �������� ������� ����� 1, ����� 2, ����� 3 - ��� ����������
	Fraction f1(1, 3);
	Fraction f2(1, 2);
	Fraction f3;

	// ������� ��������� ����� 1 � ����� 2
	cout << " �������� �����:" << endl;
	showCreatedFraction(f1, f2);
	pendl;

	// ������ �����
	cout << " ������ �����:" << endl;
	f3.copy(f1);
	f3.sum(f2);
	showFraction('+', f1, f2, f3);
	pendl;

	// ������ �����
	cout << " ������ �����:" << endl;
	f3.copy(f2);
	f3.sub(f1);
	showFraction('-', f2, f1, f3);
	pendl;

	// ������� �����
	cout << " ������� �����:" << endl;
	f3.copy(f1);
	f3.mul(f2);
	showFraction('*', f1, f2, f3);
	pendl;

	// �������� �����
	cout << " �������� �����:" << endl;
	f3.copy(f2);
	f3.div(f1);
	showFraction(':', f2, f1, f3);
	pendl;

	// ������ ����� ���������� +
	cout << " ������ ����� ���������� + :" << endl;
	f3 = f1 + f2;
	showFraction('+', f1, f2, f3);
	pendl;

	// ������ ����� ���������� -
	cout << " ������ ����� ���������� - :" << endl;
	f3 = f2 - f1;
	showFraction('-', f2, f1, f3);
	pendl;

	// ������� ����� ���������� *
	cout << " ������� ����� ���������� * :" << endl;
	f3 = f1 * f2;
	showFraction('*', f1, f2, f3);
	pendl;

	// �������� ����� ���������� /
	cout << " �������� ����� ���������� / :" << endl;
	f3 = f2 / f1;
	showFraction('/', f2, f1, f3);
	pendl;

	// �����
	return 0;
}
// ����� ������� �������

