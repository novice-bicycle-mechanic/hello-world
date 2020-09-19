// GameDigits_Table_Massif.h
/*
Здесь определены вложенные друг в друга
   классы для класса Table (Таблица):

1. Digit (Цифра)
   Вложен в класс Element (Элемент).
   Содержит:
   1) перечисление enum class D содержащее значения цифр;
   2) выражение typedef для задания типа
   значений перечисления;
   3) член-переменную digit типа enum class D;
   4) методы переопределения операторов для работы
   с "цифрами": bool(), ==, << .
   5) отдельные методы для возврата каждого
   отдельного значения перечисления.

   Реализация класса Цифра для игры "Цифры":
   Тип Цифр - любой целочисленный, как символьный,
              так и числовой. Тип влияет на объем
              памяти занимаемый игрой.
              Конкретный тип подставить в typedef.
   Сочетание Цифр - в игре сочетаются те пары Цифр,
                    в которых Цифры равны или,
                    у которых в числовом виде
                    сумма Цифр равна 10.
                    Перегрузкой оператора == реализована
                    проверка сочетаемости пар Цифр.
   Стертая Цифра - в программе отображается как d0,
                   на экране - как ' ' (пробел),
                   в операциях сравнения - как (bool)false
                   (реализовано перегрузкой оператора bool() ).

2. Element (Элемент)
   Вложен в класс MassifRow (Строка массива).
   Содержит вложенный класс Digit (Цифра).
   Содержит:
   1) член-переменную digit класса Digit (Цифра).
   2) транзитные методы, передающие функционал
   класса Digit "наверх".
   3) член-переменную allotted типа bool,
   для задания подсветки позиции элемента в таблице.

3. MassifRow (Строка массива)
   Вложен в класс Massif (Массив).
   Содержит вложенный класс Element (Элемент).
   Является динамическим массивом типа Element.
   Выполняет функцию строки двумерного массива типа Digit.

4. Massif (Массив)
   Содержит вложенный класс MassifRow (Строка массива).
   Является динамическим массивом типа MassifRow.
   Выполняет функцию двумерного массива типа Digit
   с опцией подсветки позиций.
   Совместно с классом MassifRow (Строка массива)
   имеет перегруженные операторы индексации [],
   обеспечивающие доступ "сверху" до функционала
   класса Element (Элемент), и через последний,
   до функционала класса Digit (Цифра).
*/
#pragma once
#include <iostream>

// КЛАСС Массив
class Massif {
private:

	// КЛАСС Строка массива
	class MassifRow {
	private:

		// КЛАСС Элемент
		class Element {
		private:

			// КЛАСС Цифра
			class Digit {
			private:
				// Указание типа цифр
				typedef char TypeDigit;

				// ПЕРЕЧИСЛЕНИЕ цифр
				enum class D : TypeDigit {
					d0 = '0',     // стертая цифра
					d1, d2, d3, d4, d5, d6, d7, d8, d9
				};

				// цифра - член класса 
				D digit{ D::d0 };

			public:
				// КОНСТРУКТОР по умолчанию
				Digit() {}

				// МЕТОД перегрузки оператора ()
				// - приведение типа объекта к bool
				operator bool() const {
					if (digit == D::d0) return false;
					else return true;
				}

				// МЕТОД перегрузки оператора ==
				// - равенство заменяется на сочетаемость
				bool operator==(const Digit& object) {
					if (this->digit == D::d0) return false;
					if (this->digit == object.digit) return true;
					if (
						((this->digit == D::d1) && (object.digit == D::d9)) ||
						((this->digit == D::d2) && (object.digit == D::d8)) ||
						((this->digit == D::d3) && (object.digit == D::d7)) ||
						((this->digit == D::d4) && (object.digit == D::d6)) ||
						((this->digit == D::d6) && (object.digit == D::d4)) ||
						((this->digit == D::d7) && (object.digit == D::d3)) ||
						((this->digit == D::d8) && (object.digit == D::d2)) ||
						((this->digit == D::d9) && (object.digit == D::d1))
						) return true;
					else return false;
				}

				// Встроенная дружественная ФУНКЦИЯ перегрузки оператора <<
				// - вывод на экран объекта
				friend std::ostream& operator<<(std::ostream& out, const Digit& object) {
					if (object) out << (TypeDigit)object.digit;
					else out << " ";
					return out;
				}

				// МЕТОДЫ задания значения цифры
				void setD0() { digit = D::d0; }
				void setD1() { digit = D::d1; }
				void setD2() { digit = D::d2; }
				void setD3() { digit = D::d3; }
				void setD4() { digit = D::d4; }
				void setD5() { digit = D::d5; }
				void setD6() { digit = D::d6; }
				void setD7() { digit = D::d7; }
				void setD8() { digit = D::d8; }
				void setD9() { digit = D::d9; }
			};
			// Конец КЛАССА Цифра

		// Определение класса Element
		private:

			Digit value;			// значение цифры
			bool allotted{ false };	// ключ выделения цифры

		public:
			// КОНСТРУКТОР по умолчанию
			Element() {}

			// МЕТОД возврата цифры
			Digit& getDigit() { return value; }

			// МЕТОД перегрузки оператора =
			// - присваивание значения bool ключу выделения цифры
			Element& operator=(const bool allot) {
				this->allotted = allot;
				return *this;
			}

			// МЕТОД перегрузки оператора ()
			// - приведение типа объекта к bool
			operator bool() const {
				if (this->value) return true;
				else return false;
			}

			// МЕТОД перегрузки оператора ==
			// - равенство заменяется на сочетаемость
			bool operator==(const Element& element) {
				if (this->value == element.value) return true;
				else return false;
			}

			// Встроенная дружественная ФУНКЦИЯ перегрузки оператора <<
			// - вывод элемента на экран
			friend std::ostream& operator<<(
				std::ostream& out, const Element& element
				) {
				out
					// Если элемент выделен (allotted == true)
					// - включить выделение элемента негативным цветом,
					// иначе - цвет по умолчанию
					<< (element.allotted ? "\x1b[7m" : "\x1b[m")
					<< element.value
					<< "\x1b[m";	// отмена выделения цветом
				return out;
			}
		};
		// Конец КЛАССА Элемент

	// Определение класса MassifRow
	private:
		Element* row{ nullptr }; // строка массива

	public:
		// длина строки массива
		static const size_t length{ 9 };

		// КОНСТРУКТОР по умолчанию
		MassifRow() {
			if (!row) row = new Element[length];
		}

		// ДЕСТРУКТОР
		~MassifRow() {
			if (row) delete[] row;
			row = nullptr;
		}

		// МЕТОД перегрузки оператора []
		// - индексация массива
		Element& operator[](const size_t index) const {
			return row[index];
		}

		// Встроенная дружественная ФУНКЦИЯ перегрузки оператора <<
		// - вывод строки массива на экран
		friend std::ostream& operator<<(
			std::ostream& out, const MassifRow& massifRow
			) {
			for (size_t i = 0; i < massifRow.length; i++) {
				out << massifRow.row[i];
			}
			return out;
		}
	};
	// Конец КЛАССА Строка массива

// Определение класса Massif
private:
	size_t size{ 0 };				// длина массива
	MassifRow* massif{ nullptr };	// массив для цифр

public:
	// максимальный индекс строки
	// значение задается в конструкторах
	// и в методе перегрузки оператора =
	// - присвоение перемещением
	volatile const size_t maxIndexRow; // = size - 1;

	// максимальный индекс столбцов
	const size_t maxIndexCol = MassifRow::length - 1;

	// КОНСТРУКТОР по умолчанию
	Massif() : maxIndexRow(0) {}

	// КОНСТРУКТОР с параметром
	Massif(size_t size_) :
		size(size_), maxIndexRow(size - 1)
	{
		if (!massif) massif = new MassifRow[size];
	}

	// КОНСТРУКТОР перемещения
	Massif(Massif&& object) noexcept
		: massif(object.massif)
		, size(object.size)
		, maxIndexRow(size - 1)
	{
		object.massif = nullptr;
		object.size = 0;
	}

	// ДЕСТРУКТОР
	~Massif() {
		if (massif) delete[] massif;
		massif = nullptr;
		size = 0;
	}

	// МЕТОД вывода значения длины таблицы
	size_t getSize() const { return size; }

	// МЕТОД вывода длины строки массива
	size_t getRowLength() const {
		return MassifRow::length;
	}

	// МЕТОД перегрузки оператора =
	// - присвоение перемещением
	Massif& operator=(Massif&& object) noexcept {
		if (this != &object) {
			delete[] massif;
			size = 0;
			massif = object.massif;
			object.massif = nullptr;
			size = object.size;
			object.size = 0;
			// задание значения константе maxIndexRow
			size_t* ptr_maxIR =
				const_cast<size_t*>(&maxIndexRow);
			*ptr_maxIR = object.maxIndexRow;
		}
		return *this;
	}

	// МЕТОД перегрузки оператора []
	// - индексация массива
	MassifRow& operator[](const size_t index) {
		return massif[index];
	}

	// Встроенная дружественная ФУНКЦИЯ перегрузки оператора <<
	// - вывод массива на экран
	friend std::ostream& operator<<(
		std::ostream& out, const Massif& massif
		) {
		for (size_t i = 0; i < massif.size; i++) {
			out
				<< "                             "
				<< massif.massif[i]
				<< "-"
				<< std::endl;
		}
		return out;
	}
};
// Конец КЛАССА Массив

