// DZ_ST_C++_07_dz23_vstrecha23_zadanie_main.cpp
//
// ������� �� ����� DZ_ST_C++_07.pdf
// �������� ������� �23
// ������� �23, �������
// ����: ������������ ����
/*
� ������ ���������� ��������������� � �������� �������
�� ������� ����� ������� �� ������ � ����������
������������ ��������������� ���������� (�����,
����� � ��������� ������������, ����� � ����������
������������ � �.�.). ���������� ��� ��������� ������
� ������������� ����. ���������� ���������� ���������
��������� �����������. ��������� �������� �����������
�������� ��� �� ������������ ����������� �������.
*/

 /*
�������� ������������ � ���������� ��������:
1) math (����������):
  �) Complex;
  �) Fraction;
  �) Matrix;
2) datetime (���� � �����):
  �) Date;
  �) Time;
3) programming (����������������):
  �) DynamicArray
*/

#include <iostream>
#include <clocale>
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_Complex.h"
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_Fraction.h"
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_Matrix.h"
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_Date.h"
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_Time.h"
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_DynamicArray.h"


int main() {
	setlocale(LC_ALL, "ru");

	std::cout
		<< " ������������ ������ ���� �� �����������: std, math, datetime, programming"
		<< std::endl;
	std::cout
		<< "---------------------------------------------------------------------------"
		<< std::endl;

	// -------------- ����� Complex ������������ math -----------------------

	// �������� ��� �������-����������� �����
	math::Complex a(-129, 31);
	math::Complex b(1, 12);
	math::Complex c;
	std::cout
		<< " �������� ��� ����������� �����: "
		<< a << " � " << b
		<< std::endl;

	// ������ ��� ����������� ����� ���������� +
	c = a + b;
	std::cout
		<< " ������ ��� ����������� �����: "
		<< a << " + " << b << " = " << c
		<< std::endl;

	std::cout
		<< "---------------------------------------------------------------------------"
		<< std::endl;

	// -------------- ����� Fraction ������������ math -----------------------

	// �������� ������� ����� 1, ����� 2, ����� 3 - ��� ����������
	math::Fraction f1(1, 3);
	math::Fraction f2(1, 2);
	math::Fraction f3;

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

	std::cout
		<< "---------------------------------------------------------------------------"
		<< std::endl;

	// -------------- ����� Matrix ������������ math -----------------------

	size_t m = 3;
	size_t n = 5;
	math::Matrix m2(m, n);
	std::cout << " ������� m2:" << std::endl;
	std::cout << m2 << std::endl;
	std::cout << std::endl;

	std::cout << " ������������� ������� m2" << std::endl;
	m2.transpose();
	std::cout << " ������� m2:" << std::endl;
	std::cout << m2 << std::endl;
	std::cout << std::endl;

	std::cout
		<< "---------------------------------------------------------------------------"
		<< std::endl;

	// -------------- ����� Date ������������ datetime -----------------------

		// �������� ������� ������������� � �����������
	std::cout << " �������� ������ ����: ";
	datetime::Date date1(29, 02, 2000);
	std::cout << "���� " << date1() << " == " << date1 << std::endl;
	std::cout << std::endl;

	// ��������� �������� ������� ������������� ���������� ++C
	std::cout << " ������� �������� ������� ���� " << date1() << " == " << date1 << " ���������� ++� >>> " << std::endl;
	std::cout << " ���� " << date1() << " == " << ++date1 << std::endl;
	std::cout << std::endl;

	std::cout
		<< "---------------------------------------------------------------------------"
		<< std::endl;

	// -------------- ����� Time ������������ datetime -----------------------

	std::cout << " ������ �� ��������" << std::endl << std::endl;

	datetime::Time time1(13, 34, 35);
	std::cout << " time1: " << time1 << std::endl;
	std::cout << std::endl;

	datetime::Time time2(19, 04, 55);
	std::cout << " time2: " << time2 << std::endl;
	std::cout << std::endl;

	datetime::Time time3 = time1 + time2;
	std::cout << " time3 = time1 + time2 == " << time3 << std::endl;
	std::cout << std::endl;

	std::cout
		<< "---------------------------------------------------------------------------"
		<< std::endl;

	// -------------- ����� DynamicArray ������������ programming -----------------------

	std::cout << " ������ � ������������� ���������" << std::endl << std::endl;

	programming::DynamicArray arr1(5);
	arr1.rang();
	std::cout << " arr1: " << arr1 << std::endl;
	std::cout << std::endl;

	programming::DynamicArray arr2(3);
	arr2.rang();
	std::cout << " arr2: " << arr2 << std::endl;
	std::cout << std::endl;

	programming::DynamicArray arr3 = arr1 + arr2;
	std::cout << " arr3 = arr1 + arr2 >>> " << arr3 << std::endl;
	std::cout << std::endl;

	std::cout
		<< "---------------------------------------------------------------------------"
		<< std::endl;

	// --------------------------------------------------------------------------------

	return 0;
}
