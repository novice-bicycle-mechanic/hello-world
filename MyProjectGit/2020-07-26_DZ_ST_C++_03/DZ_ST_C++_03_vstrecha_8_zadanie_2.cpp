// ������� �� ����� DZ_ST_C++_03.pdf
// ������� �8
// ����: ����������� ��������
// ������� 2.
// �������� � ��� ������������ ����� Array ����������� ��������.

#include <iostream>
#include <clocale>
#include <ctime>
using namespace std;

class Array {
private:
	int* arr{ nullptr };
	size_t size{ 0 };
	int num = counter();
public:
	Array(){
		cout << " ������ ����������� �� ��������� Array() ��� � " << num << endl;
	}
	Array(size_t size) : size(size) {
		cout << " ������ ����������� � ����������� Array() ��� � " << num << endl;
		arr = new int[size]{};
	}

//---------------------------------------------------------

	// ����������� �������� (�����������)
	Array(Array&& array) noexcept :arr(nullptr), size(0) {               // <--- ����������� �������� !!!
		cout << " ������ ����������� �������� Array() ��� � " << num << endl;

		arr = array.arr;
		size = array.size;

		array.arr = nullptr;
		array.size = 0;
	}

/*
	// �������� ������������ ���������
	Array& operator=(Array&& array) noexcept {
		cout << " ������ �������� ������������ � ���������" << endl;

		if (this != &array) {
			delete[] arr;
		}

		arr = array.arr;
		size = array.size;

		array.arr = nullptr;
		array.size = 0;

		return *this;
	}
*/

//---------------------------------------------------------

	// ����������
	~Array() {
		
		cout << " ������ ���������� ~Array ��� � " << num << endl;
		if (arr) delete[] arr;
	}

	static int counter() {
		static int count{ 0 };
		return ++count;
	}

	// ������� ������������ ������
	static Array genArray(size_t size) {
		Array a(size);
		a.random();
		cout << "a:" << a << endl;
		return a;
	}

	// ������� ���������� ������� ���������� ����������
	void random() {
		if (arr) {
			srand((unsigned int)time(0));
			rand(); rand(); rand(); rand();
			for (size_t i = 0; i < size; i++) {
				arr[i] = rand();
			}
		}
	}

	// �������� ������������� ������� ������ ������� �� ������� ���������� <<
	friend std::ostream& operator<<(std::ostream& out, const Array& array);
};


// ������������� ������� ������ ������� �� ������� ���������� <<
std::ostream& operator<<(std::ostream& out, const Array& array) {
	if (array.arr) {
		for (size_t i = 0; i < array.size; i++) {
			out << " " << array.arr[i];
		}
	}
	else {
		out << "";
	}
	return out;
}
// ����� ������������� ������� ��������� <<


int main() {
	setlocale(LC_ALL, "ru");

	// �������� ������ b �� ������� a �� ������� genArray,
	// � ������� ��� �� �����
	Array b = Array::genArray(10);
	cout << "b:" << b << endl;

	return 0;
}


