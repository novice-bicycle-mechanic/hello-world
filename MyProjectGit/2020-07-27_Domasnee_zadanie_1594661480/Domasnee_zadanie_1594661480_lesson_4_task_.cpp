// задание 1 из файла Domasnee_zadanie_1594661480.txt
// Выполните домашние задания после уроков 3, 4, 5
// Урок 4. Задание 1
/*
Создайте класс динамического массива, в котором
реализована проверка выхода за границы массива.
Перегрузите операторы: [ ], =, +, -, ++ (добавление
элемента в конец массива), –– (удаление элемента
из конца массива).
*/
#include <iostream>
#include <clocale>
using namespace std;


// КЛАСС Динамический массив
class DynamicArray {
private:
	int* dynarr{ nullptr };
	size_t length{ 0 };

public:
	// КОНСТРУКТОР по умолчанию
	DynamicArray() {
		cout << " Конструктор DynamicArray() по умолчанию" << endl;
	}

	// КОНСТРУКТОР с параметром - длиной массива
	DynamicArray(size_t length_) : length(length_) {
		cout << " Конструктор DynamicArray() с параметром - длиной массива: " << length << endl;
		dynarr = new int[length] {0};
		if (!dynarr) cout << " Массив длиной " << length << " элементов не создан!" << endl;
	}

	// КОНСТРУКТОР копирования
	DynamicArray(const DynamicArray& arr) {
		cout << " Конструктор DynamicArray() копирования" << endl;
		*this = arr;
	}

	// КОНСТРУКТОР переноса (перемещения)
	DynamicArray(DynamicArray&& arr) noexcept :dynarr(nullptr), length(0) {
		cout << " Конструктор DynamicArray() переноса" << endl;
		dynarr = arr.dynarr;
		arr.dynarr = nullptr;
		length = arr.length;
		arr.length = 0;
	}

	// ДЕСТРУКТОР
	~DynamicArray() {
		cout << " Деструктор ~DynamicArray()" << endl;
		if (dynarr) {
			delete[] dynarr;
			dynarr = nullptr;
			length = 0;
		}
	}

	// МЕТОД присвоения элементам массива значений их индексов
	void rang() {
		if (dynarr) {
			for (size_t i = 0; i < length; i++)	{
				dynarr[i] = i;
			}
		}
	}

	// МЕТОД перегрузки оператора [] - индексация массива
	int& operator[](const size_t index) {
		cout << " Перегрузка оператора [] - индексация массива" << endl;
		if (dynarr) {
			if ((0 <= index) && (index < length)) {
				return dynarr[index];
			}
			else {
				cout << " Индекс не входит в разрешенный диапазон" << endl;
				exit(5);
			}
		}
		else {
			cout << " Массив не существует" << endl;
			exit(5);
		}			
	}

	// МЕТОД перегрузки оператора = - копирования значений массива
	DynamicArray& operator=(const DynamicArray& arr) {
		cout << " Перегрузка оператора = - присвоение значений массива" << endl;
		// Проверка на самоприсваивание
		if (&arr == this) return *this;

		length = arr.length;
		if (dynarr) delete[] dynarr;
		dynarr = new int[length] {0};
		for (size_t i = 0; i < length; i++)	{
			dynarr[i] = arr.dynarr[i];
		}

		return *this;
	}

	// метод перегрузки оператора ++C - добавление в конец массива одного элемента
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

	// метод перегрузки оператора C++ - добавление в конец массива одного элемента
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

	// метод перегрузки оператора --C - удаления последнего элемента массива
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

	// метод перегрузки оператора C-- - удаления последнего элемента массива
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

	// прототип дружественной функции вывода объекта на консоль
	friend std::ostream& operator<<(std::ostream& out, const DynamicArray& arr);

	// прототип дружественной функции перегрузки оператора + - объединения массивов
	friend DynamicArray operator+(const DynamicArray& arr1, const DynamicArray& arr2);

	// прототип дружественной функции перегрузки оператора - - вычитания массива
	friend DynamicArray operator-(const DynamicArray& arr1, const DynamicArray& arr2);
};
// Конец КЛАССА Динамический массив


// Дружественная ФУНКЦИЯ вывода объекта на консоль
std::ostream& operator<<(std::ostream& out, const DynamicArray& arr) {
	if (arr.dynarr) {
		for (size_t i = 0; i < arr.length; i++) {
			out << " " << arr.dynarr[i];
		}
	}
	else {
		out << " Массив нельзя вывести на экран - массив не существует";
	}
	return out;
}


// Дружественная функция перегрузки оператора + - объединения массивов
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


// Дружественная функция перегрузки оператора - - вычитания массива
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


// ГЛАВНАЯ ФУНКЦИЯ
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
// Конец ГЛАВНОЙ ФУНКЦИИ
