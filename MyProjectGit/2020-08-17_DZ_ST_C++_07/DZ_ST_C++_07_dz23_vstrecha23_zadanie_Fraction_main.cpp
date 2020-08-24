// DZ_ST_C++_07_dz23_vstrecha23_zadanie_Fraction_main.cpp
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

#include <iostream>
#include <clocale>
#include <iomanip>
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_Fraction.h"
using namespace math;

// ������� �������
int main() {
	setlocale(LC_ALL, "ru");

	// �������� ������� ����� 1, ����� 2, ����� 3 - ��� ����������
	Fraction f1(1, 3);
	Fraction f2(1, 2);
	Fraction f3;

	// ������� ��������� ����� 1 � ����� 2
	std::cout << " �������� �����:" << std::endl;
	showCreatedFraction(f1, f2);
	std::cout << std::endl;

	// ������ �����
	std::cout << " ������ �����:" << std::endl;
	f3.copy(f1);
	f3.sum(f2);
	showFraction('+', f1, f2, f3);
	std::cout << std::endl;

	// ������ �����
	std::cout << " ������ �����:" << std::endl;
	f3.copy(f2);
	f3.sub(f1);
	showFraction('-', f2, f1, f3);
	std::cout << std::endl;

	// ������� �����
	std::cout << " ������� �����:" << std::endl;
	f3.copy(f1);
	f3.mul(f2);
	showFraction('*', f1, f2, f3);
	std::cout << std::endl;

	// �������� �����
	std::cout << " �������� �����:" << std::endl;
	f3.copy(f2);
	f3.div(f1);
	showFraction(':', f2, f1, f3);
	std::cout << std::endl;

	// ������ ����� ���������� +
	std::cout << " ������ ����� ���������� + :" << std::endl;
	f3 = f1 + f2;
	showFraction('+', f1, f2, f3);
	std::cout << std::endl;

	// ������ ����� ���������� -
	std::cout << " ������ ����� ���������� - :" << std::endl;
	f3 = f2 - f1;
	showFraction('-', f2, f1, f3);
	std::cout << std::endl;

	// ������� ����� ���������� *
	std::cout << " ������� ����� ���������� * :" << std::endl;
	f3 = f1 * f2;
	showFraction('*', f1, f2, f3);
	std::cout << std::endl;

	// �������� ����� ���������� /
	std::cout << " �������� ����� ���������� / :" << std::endl;
	f3 = f2 / f1;
	showFraction('/', f2, f1, f3);
	std::cout << std::endl;

	// �����
	return 0;
}
// ����� ������� �������

