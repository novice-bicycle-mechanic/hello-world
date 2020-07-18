// задание из файла DZ_ST_C++_03.pdf
// Встреча №8
// Тема: Конструктор переноса
// Задание 2.
// Добавить в уже существующий класс Array конструктор переноса.

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
		cout << " Вызван конструктор по умолчанию Array() для № " << num << endl;
	}
	Array(size_t size) : size(size) {
		cout << " Вызван конструктор с параметрами Array() для № " << num << endl;
		arr = new int[size]{};
	}

//---------------------------------------------------------

	// КОНСТРУКТОР переноса (перемещения)
	Array(Array&& array) noexcept :arr(nullptr), size(0) {               // <--- конструктор переноса !!!
		cout << " Вызван конструктор переноса Array() для № " << num << endl;

		arr = array.arr;
		size = array.size;

		array.arr = nullptr;
		array.size = 0;
	}

/*
	// оператор присваивания переносом
	Array& operator=(Array&& array) noexcept {
		cout << " Вызван оператор присваивания с переносом" << endl;

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

	// деструктор
	~Array() {
		
		cout << " Вызван деструктор ~Array для № " << num << endl;
		if (arr) delete[] arr;
	}

	static int counter() {
		static int count{ 0 };
		return ++count;
	}

	// функция возвращающая массив
	static Array genArray(size_t size) {
		Array a(size);
		a.random();
		cout << "a:" << a << endl;
		return a;
	}

	// функция заполнения массива случайными значениями
	void random() {
		if (arr) {
			srand((unsigned int)time(0));
			rand(); rand(); rand(); rand();
			for (size_t i = 0; i < size; i++) {
				arr[i] = rand();
			}
		}
	}

	// прототип дружественной функции вывода объекта на консоль оператором <<
	friend std::ostream& operator<<(std::ostream& out, const Array& array);
};


// Дружественная ФУНКЦИЯ вывода объекта на консоль оператором <<
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
// КОНЕЦ дружественной ФУНКЦИИ оператора <<


int main() {
	setlocale(LC_ALL, "ru");

	// создадим массив b из массива a из функции genArray,
	// и выведем его на экран
	Array b = Array::genArray(10);
	cout << "b:" << b << endl;

	return 0;
}


