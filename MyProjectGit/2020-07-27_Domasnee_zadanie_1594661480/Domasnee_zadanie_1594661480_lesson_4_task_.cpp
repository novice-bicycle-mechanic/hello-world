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
using namespace std;


// ����� ������������ ������
class DynamicArray {
private:
	int* dynarr{ nullptr };
	size_t length{ 0 };

public:
	// ����������� �� ���������
	DynamicArray() {
		cout << " ����������� DynamicArray() �� ���������" << endl;
	}

	// ����������� � ���������� - ������ �������
	DynamicArray(size_t length_) : length(length_) {
		cout << " ����������� DynamicArray() � ���������� - ������ �������: " << length << endl;
		dynarr = new int[length] {0};
		if (!dynarr) cout << " ������ ������ " << length << " ��������� �� ������!" << endl;
	}

	// ����������� �����������
	DynamicArray(const DynamicArray& arr) {
		cout << " ����������� DynamicArray() �����������" << endl;
		*this = arr;
	}

	// ����������� �������� (�����������)
	DynamicArray(DynamicArray&& arr) noexcept :dynarr(nullptr), length(0) {
		cout << " ����������� DynamicArray() ��������" << endl;
		dynarr = arr.dynarr;
		arr.dynarr = nullptr;
		length = arr.length;
		arr.length = 0;
	}

	// ����������
	~DynamicArray() {
		cout << " ���������� ~DynamicArray()" << endl;
		if (dynarr) {
			delete[] dynarr;
			dynarr = nullptr;
			length = 0;
		}
	}

	// ����� ���������� ��������� ������� �������� �� ��������
	void rang() {
		if (dynarr) {
			for (size_t i = 0; i < length; i++)	{
				dynarr[i] = i;
			}
		}
	}

	// ����� ���������� ��������� [] - ���������� �������
	int& operator[](const size_t index) {
		cout << " ���������� ��������� [] - ���������� �������" << endl;
		if (dynarr) {
			if ((0 <= index) && (index < length)) {
				return dynarr[index];
			}
			else {
				cout << " ������ �� ������ � ����������� ��������" << endl;
				exit(5);
			}
		}
		else {
			cout << " ������ �� ����������" << endl;
			exit(5);
		}			
	}

	// ����� ���������� ��������� = - ����������� �������� �������
	DynamicArray& operator=(const DynamicArray& arr) {
		cout << " ���������� ��������� = - ���������� �������� �������" << endl;
		// �������� �� ����������������
		if (&arr == this) return *this;

		length = arr.length;
		if (dynarr) delete[] dynarr;
		dynarr = new int[length] {0};
		for (size_t i = 0; i < length; i++)	{
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

	for (size_t i = arr1.length, j=0; j < arr2.length; i++, j++) {
		arr3.dynarr[i] = arr2.dynarr[j];
	}

	return arr3;
}


// ������������� ������� ���������� ��������� - - ��������� �������
DynamicArray operator-(const DynamicArray& arr1, const DynamicArray& arr2) {
	DynamicArray arr3{ arr1 };
	size_t length{ arr3.length };

	for (size_t i = 0; i < arr2.length; i++) {
		for (size_t j = 0; j < arr3.length; j++)	{
			if (arr2.dynarr[i] == arr3.dynarr[j]) {
				for (size_t k = j + 1; k < arr3.length; k++)	{
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


// ������� �������
int main() {
	setlocale(LC_ALL, "ru");

	DynamicArray arr1(5);
	arr1.rang();
	cout << "arr1: " << arr1 << endl;
	cout << "arr1[1]: " << arr1[1] << endl;
	cout << endl;

	DynamicArray arr2;
	cout << "arr2: " << arr2 << endl;
	arr2 = arr1;
	cout << "arr2: " << arr2 << endl;
	cout << endl;

	DynamicArray arr3 = arr1 + arr2;
	cout << "arr3 = arr1 + arr2 >>> " << arr3 << endl;
	cout << endl;

	DynamicArray arr4;
	arr4 = arr3 + arr2;
	cout << "arr4 = arr3 + arr2 >>> " << arr4 << endl;
	cout << endl;

	cout << "       ++arr4: " << ++arr4 << endl;
	cout << endl;

	DynamicArray arr5 = arr4++;
	cout << "arr5 = arr4++: " << arr5 << endl;
	cout << "         arr4: " << arr4 << endl;
	cout << endl;

	cout << "       --arr4: " << --arr4 << endl;
	cout << endl;

	DynamicArray arr6 = arr4--;
	cout << "arr6 = arr4--: " << arr6 << endl;
	cout << "         arr4: " << arr4 << endl;
	cout << endl;

	DynamicArray arr7 = arr4 - arr2;
	cout << "  arr7 = arr4 - arr2 >>> " << arr7 << endl;
	cout << endl;

	return 0;
}
// ����� ������� �������
