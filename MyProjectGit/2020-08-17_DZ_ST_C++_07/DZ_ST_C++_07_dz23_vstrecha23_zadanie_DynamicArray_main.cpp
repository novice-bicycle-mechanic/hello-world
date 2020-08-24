// DZ_ST_C++_07_dz23_vstrecha23_zadanie_DynamicArray_main.cpp
//
// ������� 1 �� ����� Domasnee_zadanie_1594661480.txt
// ��������� �������� ������� ����� ������ 3, 4, 5
// ���� 4. ������� 1
/*
�������� ����� ������������� �������, � �������
����������� �������� ������ �� ������� �������.
����������� ���������: [ ], =, +, -, ++ (����������
�������� � ����� �������), �� (�������� ��������
�� ����� �������).
*/
#include <iostream>
#include <clocale>
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_DynamicArray.h"
using namespace programming;


// ������� �������
int main() {
	setlocale(LC_ALL, "ru");

	DynamicArray arr1(5);
	arr1.rang();
	std::cout << "arr1: " << arr1 << std::endl;
	std::cout << "arr1[1]: " << arr1[1] << std::endl;
	std::cout << std::endl;

	DynamicArray arr2;
	std::cout << "arr2: " << arr2 << std::endl;
	arr2 = arr1;
	std::cout << "arr2: " << arr2 << std::endl;
	std::cout << std::endl;

	DynamicArray arr3 = arr1 + arr2;
	std::cout << "arr3 = arr1 + arr2 >>> " << arr3 << std::endl;
	std::cout << std::endl;

	DynamicArray arr4;
	arr4 = arr3 + arr2;
	std::cout << "arr4 = arr3 + arr2 >>> " << arr4 << std::endl;
	std::cout << std::endl;

	std::cout << "       ++arr4: " << ++arr4 << std::endl;
	std::cout << std::endl;

	DynamicArray arr5 = arr4++;
	std::cout << "arr5 = arr4++: " << arr5 << std::endl;
	std::cout << "         arr4: " << arr4 << std::endl;
	std::cout << std::endl;

	std::cout << "       --arr4: " << --arr4 << std::endl;
	std::cout << std::endl;

	DynamicArray arr6 = arr4--;
	std::cout << "arr6 = arr4--: " << arr6 << std::endl;
	std::cout << "         arr4: " << arr4 << std::endl;
	std::cout << std::endl;

	DynamicArray arr7 = arr4 - arr2;
	std::cout << "  arr7 = arr4 - arr2 >>> " << arr7 << std::endl;
	std::cout << std::endl;

	return 0;
}
// ����� ������� �������
