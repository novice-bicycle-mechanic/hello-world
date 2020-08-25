// DZ_ST_C++_07_dz23_vstrecha23_zadanie_DynamicArray.h
//
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
#pragma once
#include <iostream>

namespace spaceDynamicArray
{
	// КЛАСС Динамический массив
	class DynamicArray {
	protected:
		int* dynarr{ nullptr };
		size_t length{ 0 };

	public:
		// КОНСТРУКТОР по умолчанию
		DynamicArray() {
			//	std::cout << " Конструктор DynamicArray() по умолчанию" << std::endl;
		}

		// КОНСТРУКТОР с параметром - длиной массива
		DynamicArray(size_t length_) : length(length_) {
			//	std::cout << " Конструктор DynamicArray() с параметром - длиной массива: " << length << std::endl;
			dynarr = new int[length] {0};
			if (!dynarr) std::cout << " Массив длиной " << length << " элементов не создан!" << std::endl;
		}

		// КОНСТРУКТОР копирования
		DynamicArray(const DynamicArray& arr) {
			//	std::cout << " Конструктор DynamicArray() копирования" << std::endl;
			*this = arr;
		}

		// КОНСТРУКТОР переноса (перемещения)
		DynamicArray(DynamicArray&& arr) noexcept :dynarr(nullptr), length(0) {
			//	std::cout << " Конструктор DynamicArray() переноса" << std::endl;
			dynarr = arr.dynarr;
			arr.dynarr = nullptr;
			length = arr.length;
			arr.length = 0;
		}

		// ДЕСТРУКТОР
		~DynamicArray() {
			//	std::cout << " Деструктор ~DynamicArray()" << std::endl;
			if (dynarr) {
				delete[] dynarr;
				dynarr = nullptr;
				length = 0;
			}
		}

		// МЕТОД присвоения элементам массива значений их индексов
		void rang() {
			if (dynarr) {
				for (size_t i = 0; i < length; i++) {
					dynarr[i] = i;
				}
			}
		}

		// МЕТОД перегрузки оператора [] - индексация массива
		int& operator[](const size_t index) {
			//	std::cout << " Перегрузка оператора [] - индексация массива" << std::endl;
			if (dynarr) {
				if ((0 <= index) && (index < length)) {
					return dynarr[index];
				}
				else {
					std::cout << " Индекс не входит в разрешенный диапазон" << std::endl;
					exit(5);
				}
			}
			else {
				std::cout << " Массив не существует" << std::endl;
				exit(5);
			}
		}

		// МЕТОД перегрузки оператора = - копирования значений массива
		DynamicArray& operator=(const DynamicArray& arr) {
			//	std::cout << " Перегрузка оператора = - присвоение значений массива" << std::endl;
				// Проверка на самоприсваивание
			if (&arr == this) return *this;

			length = arr.length;
			if (dynarr) delete[] dynarr;
			dynarr = new int[length] {0};
			for (size_t i = 0; i < length; i++) {
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

		// прототип дружественной функции перегрузки оператора - - вычитания массива
		friend DynamicArray operator-(const DynamicArray& arr1, const DynamicArray& arr2);

		// прототип дружественной функции перегрузки оператора + - объединения массивов
		friend DynamicArray operator+(const DynamicArray& arr1, const DynamicArray& arr2);
	};
	// Конец КЛАССА Динамический массив


	// КЛАСС Test для проверки работы namespace при совпадении идентификаторов типа
	class Test : public DynamicArray {
	public:
		Test(size_t length_) : DynamicArray(length_) {}

		// МЕТОД перегрузки оператора = - копирования значений массива
		Test& operator=(const Test& arr) {
			//	std::cout << " Перегрузка оператора = - присвоение значений массива" << std::endl;
				// Проверка на самоприсваивание
			if (&arr == this) return *this;

			length = arr.length;
			if (dynarr) delete[] dynarr;
			dynarr = new int[length] {0};
			for (size_t i = 0; i < length; i++) {
				dynarr[i] = arr.dynarr[i];
			}

			return *this;
		}

		// прототип дружественной функции перегрузки оператора + - объединения массивов
		friend Test operator+(const Test& arr1, const Test& arr2);
	};






}