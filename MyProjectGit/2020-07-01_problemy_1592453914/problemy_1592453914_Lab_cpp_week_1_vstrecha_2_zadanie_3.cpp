// ������� �� ����� problemy_1592453914.txt
// ���� Lab_C++_week_1.pdf, ������� 2, ������� 3
/*
	� ��� �������������� ������ ����� �������� �����������
������������, �������� ��� ������� inline, �����������
��������������.
(���� DZ_ST_C++_01.pdf, ������� 1, �������:
���������� ����� �����. ���������� ������� ���������
� ����������� � �������� ����������-������.
���������� �������-����� ��� ����� ������ � ����������-�����,
��� ���������� �������������� �������� (��������,
���������, ���������, �������, � �.�.)).
*/
#include <iostream>
#include <clocale>
#include <iomanip>
#define pendl cout << endl
using namespace std;


// ����� �����
class Fraction {
private:
	int numerator  { 0 };    // ���������
	int denominator{ 1 };    // �����������
public:
	// ����������� �� ���������
	Fraction(){}

	// ����������� � �����������
	Fraction(
		int numerator,
		int denominator
	) {
		setNumerator  (numerator  );
		setDenominator(denominator);
	}

	// ����������� �����������
	Fraction(Fraction& object) { *this = object; }

	// SETTER-�
	inline void setNumerator  (int numerator  ) { this->numerator   = numerator  ; }
	inline void setDenominator(int denominator) { this->denominator = denominator; }

	// GETTER-�
	inline int getNumerator  () { return numerator  ; }
	inline int getDenominator() { return denominator; }

	// ����� ����������� �������� �����
	//       �� �����-��������� � �����-��������� ������
	inline void copy(Fraction fraction2) {
		this->numerator   = fraction2.getNumerator  ();
		this->denominator = fraction2.getDenominator();
	}

	// ����� �������� ������
	bool sum(Fraction fraction2) {
		if (this->denominator != fraction2.getDenominator()) {
			int lcm = this->lcm(fraction2);
			if (lcm) {
				this->numerator *= lcm / this->denominator;
				this->denominator = lcm;
				this->numerator += fraction2.getNumerator() * lcm / fraction2.getDenominator();
			}
			else return false;
		}
		else {
			this->numerator += fraction2.getNumerator();
		}
		return true;
	}

	// ����� ��������� ������ � ����������� �������������
	bool sub(Fraction fraction2) {
		if (this->denominator != fraction2.getDenominator()) {
			int lcm = this->lcm(fraction2);
			if (lcm) {
				this->numerator *= lcm / this->denominator;
				this->denominator = lcm;
				this->numerator -= fraction2.getNumerator() * lcm / fraction2.getDenominator();
			}
			else return false;
		}
		else {
			this->numerator -= fraction2.getNumerator();
		}
		return true;
	}

	// ����� ��������� ������
	bool mul(Fraction fraction2) {
		int denominator = this->denominator;
		denominator *= fraction2.getDenominator();
		if (denominator) {
			this->denominator = denominator;
			this->numerator *= fraction2.getNumerator();
			return true;
		}
		else return false;
	}

	// ����� ������� ������
	bool div(Fraction fraction2) {
		int denominator = this->denominator;
		denominator *= fraction2.getNumerator();
		if (denominator) {
			this->denominator = denominator;
			this->numerator *= fraction2.getDenominator();
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
	int lcm(Fraction fraction2) {

		// �������� ����������
		long long int min{ 0 };             // ������� ����� �� ����
		long long int max{ 0 };             // ������� ����� �� ����
		long long int multiplier{ 0 };      // ��������� �������� �����
		long long int lcm{ 0 };             // LCM - ���

		// !!! ����� � �����, �� ������� ��������������:
		// min � max - ������ �����,
		// multiplier - ����� ��� ������ ����������

		// ��������� �������� ������������ ������ � ����������
		// ���� ������ ��� �� ����� 0, ����� - ������ - ������� 0
		if (this->denominator) min = this->denominator;
		else return 0;
		if (fraction2.getDenominator()) max = fraction2.getDenominator();
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
};
// ����� ������


// ������� ����������� ������ ����� ����� �� ������ ����� �����
std::streamsize widthLine_From_widthNumber(std::streamsize widthNumber) {
	return widthNumber + 2;
}
// ����� �������


// ������� ����������� ������ ����� �����
int widthNumber_From_fraction(Fraction fraction) {
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
	char sign,             // ���� ��������
	Fraction fraction1,    // ����� 1
	Fraction fraction2,    // ����� 2
	Fraction fraction3     // ����� 3
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
	Fraction fraction1,    // ����� 1
	Fraction fraction2     // ����� 2
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
	Fraction f1{ 1, 3 };
	Fraction f2{ 1, 2 };
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

	// �����
	return 0;
}
// ����� ������� �������










































































