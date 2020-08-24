// DZ_ST_C++_07_dz23_vstrecha23_zadanie_Fraction.cpp
//
// ������� �6
// ����: ���������� ����������
// ������� 1.
/*
�������� ����� ����� (��� ����������� ��� ����� ������-
��� ����). ��������� ���������� ���������� ����������
��� ���� �������������� �������� ��� ������ � �������
(�������� +, -, *, /).
*/
#pragma once
#include <iostream>
#include <iomanip>
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_Fraction.h"

namespace math
{
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
		std::cout
			<< std::setw(indent) << ""
			<< std::setw(1) << std::left << ""
			<< std::setw(widthNumber1) << std::left << fraction1.getNumerator()
			<< std::setw(1) << std::left << ""
			<< std::setw(3) << std::left << ""
			<< std::setw(1) << std::left << ""
			<< std::setw(widthNumber2) << std::left << fraction2.getNumerator()
			<< std::setw(1) << std::left << ""
			<< std::setw(3) << std::left << ""
			<< std::setw(1) << std::left << ""
			<< std::setw(widthNumber3) << std::left << fraction3.getNumerator()
			<< std::setw(1) << std::left << ""
			<< std::endl;

		// ������� �����
		std::cout
			<< std::setw(indent) << ""
			<< std::setw(0) << std::left << ""
			<< std::setw(widthLine1) << std::left << std::setfill('-') << "-" << std::setfill(' ')
			<< std::setw(0) << std::left << ""
			<< std::setw(1) << std::left << " "
			<< std::setw(1) << std::left << sign << std::setw(1) << std::left << " "
			<< std::setw(0) << std::left << ""
			<< std::setw(widthLine2) << std::left << std::setfill('-') << "-" << std::setfill(' ')
			<< std::setw(0) << std::left << ""
			<< std::setw(3) << std::left << " = "
			<< std::setw(0) << std::left << ""
			<< std::setw(widthLine3) << std::left << std::setfill('-') << "-" << std::setfill(' ')
			<< std::setw(0) << std::left << ""
			<< std::endl;

		// ����� ������������
		std::cout
			<< std::setw(indent) << ""
			<< std::setw(1) << std::left << ""
			<< std::setw(widthNumber1) << std::left << fraction1.getDenominator()
			<< std::setw(1) << std::left << ""
			<< std::setw(3) << std::left << ""
			<< std::setw(1) << std::left << ""
			<< std::setw(widthNumber2) << std::left << fraction2.getDenominator()
			<< std::setw(1) << std::left << ""
			<< std::setw(3) << std::left << ""
			<< std::setw(1) << std::left << ""
			<< std::setw(widthNumber3) << std::left << fraction3.getDenominator()
			<< std::setw(1) << std::left << ""
			<< std::endl;
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
		std::cout
			<< std::setw(indent) << ""
			<< std::setw(10) << std::left << ""
			<< std::setw(1) << std::left << ""
			<< std::setw(widthNumber1) << std::left << fraction1.getNumerator()
			<< std::setw(1) << std::left << ""
			<< std::setw(3) << std::left << ""
			<< std::setw(10) << std::left << ""
			<< std::setw(1) << std::left << ""
			<< std::setw(widthNumber2) << std::left << fraction2.getNumerator()
			<< std::setw(1) << std::left << ""
			<< std::endl;

		// ������� �����
		std::cout
			<< std::setw(indent) << ""
			<< std::setw(10) << std::left << "����� 1 = "
			<< std::setw(widthLine1) << std::left << std::setfill('-') << "-" << std::setfill(' ')
			<< std::setw(3) << std::left << " ; "
			<< std::setw(10) << std::left << "����� 2 = "
			<< std::setw(widthLine2) << std::left << std::setfill('-') << "-" << std::setfill(' ')
			<< std::endl;

		// ����� ������������
		std::cout
			<< std::setw(indent) << ""
			<< std::setw(10) << std::left << ""
			<< std::setw(1) << std::left << ""
			<< std::setw(widthNumber1) << std::left << fraction1.getDenominator()
			<< std::setw(1) << std::left << ""
			<< std::setw(3) << std::left << ""
			<< std::setw(10) << std::left << ""
			<< std::setw(1) << std::left << ""
			<< std::setw(widthNumber2) << std::left << fraction2.getDenominator()
			<< std::setw(1) << std::left << ""
			<< std::endl;
	}
	// ����� �������
}
