// DZ_ST_C++_07_dz23_vstrecha23_zadanie_Matrix_main.cpp


// ������� 1 �� ����� Domasnee_zadanie_1594661480.txt
// ��������� �������� ������� ����� ������ 3, 4, 5
// ���� 5. ������� 2
/*
2.	������� ����� ��� ������ � ���������.
�������������, ��� �������, ������� ��� �������� ������,
��������� ������, ���������������� ������, ������������
������ ���� �����, ��������� � ��������� �������������
�������� �������. ���������� ����������� ���������������
���������.
*/
#include <iostream>
#include <clocale>
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_Matrix.h"
using namespace math;


// ������� �������
int main() {
	setlocale(LC_ALL, "ru");

	Matrix m1;
	std::cout << " ������� m1:" << std::endl;
	std::cout << m1 << std::endl;
	std::cout << std::endl;

	size_t m = 3;
	size_t n = 5;
	Matrix m2(m, n);
	std::cout << " ������� m2:" << std::endl;
	std::cout << m2 << std::endl;
	std::cout << std::endl;

	std::cout << " �������� ������ ���������� ���������� �������" << std::endl;
	std::cout << " ���������: m2[1][1] == " << m2[1][1] << std::endl;
	std::cout << " �������� ��������: m2[1][1] = 11" << std::endl;
	m2[1][1] = 11;
	std::cout << " ���������: m2[1][1] == " << m2[1][1] << std::endl;
	std::cout << " ������� m2:" << std::endl;
	std::cout << m2 << std::endl;
	std::cout << std::endl;

	m1 = m2;
	std::cout << " ������� m1 = m2:" << std::endl;
	std::cout << m1 << std::endl;
	std::cout << std::endl;

	Matrix m3 = m2;
	std::cout << " ������� m3 = m2:" << std::endl;
	std::cout << m3 << std::endl;
	std::cout << std::endl;

	m1 = m2 + m3;
	std::cout << " ������� m1 = m2 + m3:" << std::endl;
	std::cout << m1 << std::endl;
	std::cout << std::endl;

	m3 = m2 - m1;
	std::cout << " ������� m3 = m2 - m1:" << std::endl;
	std::cout << m3 << std::endl;
	std::cout << std::endl;

	std::cout << " ������������� ������� m3" << std::endl;
	m3.transpose();
	std::cout << " ������� m3:" << std::endl;
	std::cout << m3 << std::endl;
	std::cout << std::endl;

	std::cout << " ������� m2:" << std::endl;
	std::cout << m2 << std::endl;
	std::cout << std::endl;

	m1 = m2 * m3;
	std::cout << " ������� m1 = m2 * m3:" << std::endl;
	std::cout << m1 << std::endl;
	std::cout << std::endl;

	//	std::cout << " ����� main()" << std::endl;
	return 0;
}
// ����� ������� �������
