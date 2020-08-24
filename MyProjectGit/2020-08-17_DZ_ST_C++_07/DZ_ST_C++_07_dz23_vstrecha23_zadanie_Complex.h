// DZ_ST_C++_07_dz23_vstrecha23_zadanie_Complex.h
//
// ������� �� ����� DZ_ST_C++_03.pdf
// ������� �6
// ����: ���������� ����������
// ������� 2.
/*
�������� ����� Complex (����������� �����) ��� ������-
����� ��� ��������� ���� �����. �������� �������������
��������� ��� ���������� �������������� �������� ���
�� ������ � ������������ ������� (�������� +, -, *, /).
*/
#pragma once
#include <iostream>

namespace math
{
	class Complex {
	private:
		int real{ 0 };					// ������������ ����� ������������ �����
		int image{ 0 };					// ������ ����� ������������ �����
	public:
		Complex() {}
		Complex(int real, int image) :real(real), image(image) {}
		Complex(const Complex& complex) { *this = complex; }

		// �������� ������������� ������� ������ ������������ ����� �� ������� ���������� <<
		friend std::ostream& operator<<(std::ostream& out, const Complex& complex);

		// �������� ������������� ������� ���������� ��������� +
		friend Complex operator+(const Complex& complex1, const Complex& complex2);

		// �������� ������������� ������� ���������� ��������� -
		friend Complex operator-(const Complex& complex1, const Complex& complex2);

		// �������� ������������� ������� ���������� ��������� *
		friend Complex operator*(const Complex& complex1, const Complex& complex2);

		// �������� ������������� ������� ���������� ��������� /
		friend Complex operator/(const Complex& complex1, const Complex& complex2);
	};
}
