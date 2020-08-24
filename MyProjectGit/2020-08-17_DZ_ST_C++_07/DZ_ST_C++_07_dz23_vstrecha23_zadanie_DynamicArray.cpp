// DZ_ST_C++_07_dz23_vstrecha23_zadanie_DynamicArray.cpp
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
#pragma once
#include <iostream>
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_DynamicArray.h"

namespace programming
{

	// ������������� ������� ������ ������� �� �������
	std::ostream& operator<<(std::ostream& out, const DynamicArray& arr) {
		if (arr.dynarr) {
			for (size_t i = 0; i < arr.length; i++) {
				out << " " << arr.dynarr[i];
			}
		}
		else {
			out << " ������ ������ ������� �� ����� - ������ �� ����������";
		}
		return out;
	}


	// ������������� ������� ���������� ��������� + - ����������� ��������
	DynamicArray operator+(const DynamicArray& arr1, const DynamicArray& arr2) {
		DynamicArray arr3(arr1.length + arr2.length);

		for (size_t i = 0; i < arr1.length; i++) {
			arr3.dynarr[i] = arr1.dynarr[i];
		}

		for (size_t i = arr1.length, j = 0; j < arr2.length; i++, j++) {
			arr3.dynarr[i] = arr2.dynarr[j];
		}

		return arr3;
	}


	// ������������� ������� ���������� ��������� - - ��������� �������
	DynamicArray operator-(const DynamicArray& arr1, const DynamicArray& arr2) {
		DynamicArray arr3{ arr1 };
		size_t length{ arr3.length };

		for (size_t i = 0; i < arr2.length; i++) {
			for (size_t j = 0; j < arr3.length; j++) {
				if (arr2.dynarr[i] == arr3.dynarr[j]) {
					for (size_t k = j + 1; k < arr3.length; k++) {
						arr3.dynarr[k - 1] = arr3.dynarr[k];
					}
					--length;
					break;
				}
			}
		}

		DynamicArray arr4(length);
		for (size_t i = 0; i < arr4.length; i++) {
			arr4.dynarr[i] = arr3.dynarr[i];
		}

		return arr4;
	}

}