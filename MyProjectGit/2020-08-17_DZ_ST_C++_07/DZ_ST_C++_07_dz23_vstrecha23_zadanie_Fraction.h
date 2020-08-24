// DZ_ST_C++_07_dz23_vstrecha23_zadanie_Fraction.h
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

namespace math
{


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


	// �������� ������� ������������ �������������� �������� � �������
	void showFraction(
		const char& sign,             // ���� ��������
		const Fraction& fraction1,    // ����� 1
		const Fraction& fraction2,    // ����� 2
		const Fraction& fraction3     // ����� 3
	);


	// �������� ������� ������������ ��������� ������
	void showCreatedFraction(
		const Fraction& fraction1,    // ����� 1
		const Fraction& fraction2     // ����� 2
	);

}

