// DZ_ST_C++_07_dz23_vstrecha23_zadanie_DynamicArray.h
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

namespace programming
{
	// ����� ������������ ������
	class DynamicArray {
	private:
		int* dynarr{ nullptr };
		size_t length{ 0 };

	public:
		// ����������� �� ���������
		DynamicArray() {
			//	std::cout << " ����������� DynamicArray() �� ���������" << std::endl;
		}

		// ����������� � ���������� - ������ �������
		DynamicArray(size_t length_) : length(length_) {
			//	std::cout << " ����������� DynamicArray() � ���������� - ������ �������: " << length << std::endl;
			dynarr = new int[length] {0};
			if (!dynarr) std::cout << " ������ ������ " << length << " ��������� �� ������!" << std::endl;
		}

		// ����������� �����������
		DynamicArray(const DynamicArray& arr) {
			//	std::cout << " ����������� DynamicArray() �����������" << std::endl;
			*this = arr;
		}

		// ����������� �������� (�����������)
		DynamicArray(DynamicArray&& arr) noexcept :dynarr(nullptr), length(0) {
			//	std::cout << " ����������� DynamicArray() ��������" << std::endl;
			dynarr = arr.dynarr;
			arr.dynarr = nullptr;
			length = arr.length;
			arr.length = 0;
		}

		// ����������
		~DynamicArray() {
			//	std::cout << " ���������� ~DynamicArray()" << std::endl;
			if (dynarr) {
				delete[] dynarr;
				dynarr = nullptr;
				length = 0;
			}
		}

		// ����� ���������� ��������� ������� �������� �� ��������
		void rang() {
			if (dynarr) {
				for (size_t i = 0; i < length; i++) {
					dynarr[i] = i;
				}
			}
		}

		// ����� ���������� ��������� [] - ���������� �������
		int& operator[](const size_t index) {
			//	std::cout << " ���������� ��������� [] - ���������� �������" << std::endl;
			if (dynarr) {
				if ((0 <= index) && (index < length)) {
					return dynarr[index];
				}
				else {
					std::cout << " ������ �� ������ � ����������� ��������" << std::endl;
					exit(5);
				}
			}
			else {
				std::cout << " ������ �� ����������" << std::endl;
				exit(5);
			}
		}

		// ����� ���������� ��������� = - ����������� �������� �������
		DynamicArray& operator=(const DynamicArray& arr) {
			//	std::cout << " ���������� ��������� = - ���������� �������� �������" << std::endl;
				// �������� �� ����������������
			if (&arr == this) return *this;

			length = arr.length;
			if (dynarr) delete[] dynarr;
			dynarr = new int[length] {0};
			for (size_t i = 0; i < length; i++) {
				dynarr[i] = arr.dynarr[i];
			}

			return *this;
		}

		// ����� ���������� ��������� ++C - ���������� � ����� ������� ������ ��������
		DynamicArray& operator++() {
			DynamicArray arr(this->length + 1);

			for (size_t i = 0; i < this->length; i++) {
				arr.dynarr[i] = this->dynarr[i];
			}

			if (dynarr) delete[] dynarr;
			dynarr = arr.dynarr;
			arr.dynarr = nullptr;
			length = arr.length;
			arr.length = 0;

			return *this;
		}

		// ����� ���������� ��������� C++ - ���������� � ����� ������� ������ ��������
		DynamicArray operator++(int) {
			DynamicArray temp = *this;
			DynamicArray arr(this->length + 1);

			for (size_t i = 0; i < this->length; i++) {
				arr.dynarr[i] = this->dynarr[i];
			}

			if (dynarr) delete[] dynarr;
			dynarr = arr.dynarr;
			arr.dynarr = nullptr;
			length = arr.length;
			arr.length = 0;

			return temp;
		}

		// ����� ���������� ��������� --C - �������� ���������� �������� �������
		DynamicArray& operator--() {
			--length;
			DynamicArray arr(length);

			for (size_t i = 0; i < length; i++) {
				arr.dynarr[i] = this->dynarr[i];
			}

			if (dynarr) delete[] dynarr;
			dynarr = arr.dynarr;
			arr.dynarr = nullptr;
			arr.length = 0;

			return *this;
		}

		// ����� ���������� ��������� C-- - �������� ���������� �������� �������
		DynamicArray operator--(int) {
			DynamicArray temp = *this;
			--length;
			DynamicArray arr(length);

			for (size_t i = 0; i < length; i++) {
				arr.dynarr[i] = this->dynarr[i];
			}

			if (dynarr) delete[] dynarr;
			dynarr = arr.dynarr;
			arr.dynarr = nullptr;
			arr.length = 0;

			return temp;
		}

		// �������� ������������� ������� ������ ������� �� �������
		friend std::ostream& operator<<(std::ostream& out, const DynamicArray& arr);

		// �������� ������������� ������� ���������� ��������� + - ����������� ��������
		friend DynamicArray operator+(const DynamicArray& arr1, const DynamicArray& arr2);

		// �������� ������������� ������� ���������� ��������� - - ��������� �������
		friend DynamicArray operator-(const DynamicArray& arr1, const DynamicArray& arr2);
	};
	// ����� ������ ������������ ������

}