// DZ_ST_C++_07_dz23_vstrecha23_zadanie_Complex.cpp
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
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_Complex.h"

namespace math
{

	// ������������� ������� ������ ������������ ����� �� ������� ���������� <<
	std::ostream& operator<<(std::ostream& out, const Complex& complex) {
		out << complex.real << (complex.image < 0 ? "" : "+") << complex.image << "i";
		return out;
	}
	// ����� ������������� ������� ��������� <<


	// ������������� ������� ���������� ��������� +
	Complex operator+(const Complex& complex1, const Complex& complex2) {
		Complex complex3;

		complex3.real = complex1.real + complex2.real;
		complex3.image = complex1.image + complex2.image;

		return complex3;
	}
	// ����� ������������� ������� ��������� +


	// ������������� ������� ���������� ��������� -
	Complex operator-(const Complex& complex1, const Complex& complex2) {
		Complex complex3;

		complex3.real = complex1.real - complex2.real;
		complex3.image = complex1.image - complex2.image;

		return complex3;
	}
	// ����� ������������� ������� ��������� -


	// ������������� ������� ���������� ��������� *
	Complex operator*(const Complex& complex1, const Complex& complex2) {
		Complex complex3;

		complex3.real = complex1.real * complex2.real - complex1.image * complex2.image;
		complex3.image = complex1.image * complex2.real + complex1.real * complex2.image;

		return complex3;
	}
	// ����� ������������� ������� ��������� *


	// ������������� ������� ���������� ��������� /
	Complex operator/(const Complex& complex1, const Complex& complex2) {
		Complex complex3;

		complex3.real =
			(complex1.real * complex2.real + complex1.image * complex2.image) /
			(complex2.real * complex2.real + complex2.image * complex2.image);

		complex3.image =
			(complex1.image * complex2.real - complex1.real * complex2.image) /
			(complex2.real * complex2.real + complex2.image * complex2.image);

		return complex3;
	}
	// ����� ������������� ������� ��������� /
}
