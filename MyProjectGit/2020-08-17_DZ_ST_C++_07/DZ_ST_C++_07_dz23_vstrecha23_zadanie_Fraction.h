// DZ_ST_C++_07_dz23_vstrecha23_zadanie_Fraction.h
//
// Встреча №6
// Тема: Перегрузка операторов
// Задание 1.
/*
Создайте класс Дробь (или используйте уже ранее создан-
ный вами). Используя перегрузку операторов реализуйте
для него арифметические операции для работы с дробями
(операции +, -, *, /).
*/
#pragma once
#include <iostream>
#include <iomanip>

namespace math
{


	// КЛАСС Дробь
	class Fraction {
	private:
		int numerator{ 0 };    // числитель
		int denominator{ 1 };  // знаменатель
	public:
		// КОНСТРУКТОР по умолчанию
		Fraction() {}

		// КОНСТРУКТОР с параметрами
		Fraction(int numerator, int denominator)
			: numerator(numerator), denominator(denominator)
		{}

		// конструктор копирования
		Fraction(const Fraction& fraction2) {
			*this = fraction2;
		}

		// SETTER-ы
		void setNumerator(int numerator) { this->numerator = numerator; }
		void setDenominator(int denominator) { this->denominator = denominator; }

		// GETTER-ы
		int getNumerator() const { return numerator; }
		int getDenominator() const { return denominator; }

		// МЕТОД копирования значений дроби
		//       от Дроби-аргумента к Дроби-владельцу метода
		void copy(const Fraction& fraction2) {
			numerator = fraction2.numerator;
			denominator = fraction2.denominator;
		}

		// МЕТОД сложения дробей
		bool sum(const Fraction& fraction2) {
			if (denominator != fraction2.denominator) {
				int lcm = Fraction::lcm(*this, fraction2);
				if (lcm) {
					numerator *= lcm / denominator;
					denominator = lcm;
					numerator += fraction2.numerator * lcm / fraction2.denominator;
				}
				else return false;
			}
			else {
				numerator += fraction2.numerator;
			}
			return true;
		}

		// МЕТОД вычитания дробей
		bool sub(const Fraction& fraction2) {
			if (denominator != fraction2.denominator) {
				int lcm = Fraction::lcm(*this, fraction2);
				if (lcm) {
					numerator *= lcm / denominator;
					denominator = lcm;
					numerator -= fraction2.numerator * lcm / fraction2.denominator;
				}
				else return false;
			}
			else {
				numerator -= fraction2.numerator;
			}
			return true;
		}

		// МЕТОД умножения дробей
		bool mul(const Fraction& fraction2) {
			int _denominator = denominator;
			_denominator *= fraction2.denominator;
			if (_denominator) {
				denominator = _denominator;
				numerator *= fraction2.numerator;
				return true;
			}
			else return false;
		}

		// МЕТОД деления дробей
		bool div(const Fraction& fraction2) {
			int _denominator = denominator;
			_denominator *= fraction2.numerator;
			if (_denominator) {
				denominator = _denominator;
				numerator *= fraction2.denominator;
				return true;
			}
			else return false;
		}

	private:
		// МЕТОД нахождения Наименьшего Общего Кратного (НОК)
		//       или на английском Least Common Multiple (LCM)
		// !!! - возврат 0 - это ошибка:
		// 1) какое-то исходное значение равно 0;
		// 2) возможное значение НОК превышает максимальное int
		// !!! метод закрытый
		static int lcm(const Fraction& fraction1, const Fraction& fraction2) {

			// создадим переменные
			long long int min = 0;             // меньшее число из двух
			long long int max = 0;             // большее число из двух
			long long int multiplier = 0;      // множитель большего числа
			long long int lcm = 0;             // LCM - НОК

			// !!! здесь и далее, до особого предупреждения:
			// min и max - просто числа,
			// multiplier - буфер для обмена значениями

			// скопируем значения знаменателей дробей в переменные
			// если только они не равны 0, иначе - ошибка - возврат 0
			if (fraction1.denominator) min = fraction1.denominator;
			else return 0;
			if (fraction2.denominator) max = fraction2.denominator;
			else return 0;

			// найдем модули чисел (значения без знака, положительные)
			min = min < 0 ? -min : min;
			max = max < 0 ? -max : max;

			// !!! здесь min и max станут сами собой
			// сравним числа и присвоим их значения
			// меньшему и большему числам
			if (min > max) {
				multiplier = max;
				max = min;
				min = multiplier;
			}

			// !!! здесь multiplier станет сам собой
			// присвоим multiplier начальное значение
			multiplier = 1;

			// цикл нахождения НОК
			while (lcm < INT_MAX) {

				// найдем кандидата в НОК
				// - умножим большее число на множитель
				lcm = max * multiplier;

				// если остаток от деления НОК на меньшее число равен 0
				// - есть НОК - возврат НОК
				if (lcm % min == 0) return (int)lcm;

				// иначе - увеличиваем множитель на 1
				else ++multiplier;

				//  и уходим на следующую итерацию цикла
			}

			// если lcm не меньше INT_MAX - ошибка - возврат 0
			return 0;
		}

	public:
		// прототип дружественной функции перегрузки оператора +
		friend Fraction operator+(const Fraction& fraction1, const Fraction& fraction2);

		// прототип дружественной функции перегрузки оператора -
		friend Fraction operator-(const Fraction& fraction1, const Fraction& fraction2);

		// прототип дружественной функции перегрузки оператора *
		friend Fraction operator*(const Fraction& fraction1, const Fraction& fraction2);

		// прототип дружественной функции перегрузки оператора /
		friend Fraction operator/(const Fraction& fraction1, const Fraction& fraction2);
	};
	// КОНЕЦ КЛАССА


	// Прототип ФУНКЦИИ демонстрации арифметических действий с дробями
	void showFraction(
		const char& sign,             // знак действия
		const Fraction& fraction1,    // дробь 1
		const Fraction& fraction2,    // дробь 2
		const Fraction& fraction3     // дробь 3
	);


	// Прототип ФУНКЦИИ демонстрации созданных дробей
	void showCreatedFraction(
		const Fraction& fraction1,    // дробь 1
		const Fraction& fraction2     // дробь 2
	);

}

