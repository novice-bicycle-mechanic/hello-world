// задание из файла DZ_ST_C++_03.pdf
// Встреча №6
// Тема: Перегрузка операторов
// Задание 1.
/*
Создайте класс Дробь (или используйте уже ранее создан-
ный вами). Используя перегрузку операторов реализуйте
для него арифметические операции для работы с дробями
(операции +, -, *, /).
*/

#include <iostream>
#include <clocale>
#include <iomanip>
#define pendl cout << endl
using namespace std;


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


// Дружественная ФУНКЦИЯ перегрузки оператора +
Fraction operator+(const Fraction& fraction1, const Fraction& fraction2) {
	Fraction fraction3;
	if (fraction1.denominator != fraction2.denominator) {
		int lcm = Fraction::lcm(fraction1, fraction2);
		if (lcm) {
			fraction3.denominator = lcm;
			fraction3.numerator =
				fraction1.numerator * lcm / fraction1.denominator +
				fraction2.numerator * lcm / fraction2.denominator;
		}
	}
	else {
		fraction3.denominator = fraction1.denominator;
		fraction3.numerator = fraction1.numerator + fraction2.numerator;
	}
	return fraction3;
}
// КОНЕЦ дружественной ФУНКЦИИ оператора +


// Дружественная ФУНКЦИЯ перегрузки оператора -
Fraction operator-(const Fraction& fraction1, const Fraction& fraction2) {
	Fraction fraction3;
	if (fraction1.denominator != fraction2.denominator) {
		int lcm = Fraction::lcm(fraction1, fraction2);
		if (lcm) {
			fraction3.denominator = lcm;
			fraction3.numerator =
				fraction1.numerator * lcm / fraction1.denominator -
				fraction2.numerator * lcm / fraction2.denominator;
		}
	}
	else {
		fraction3.denominator = fraction1.denominator;
		fraction3.numerator = fraction1.numerator - fraction2.numerator;
	}
	return fraction3;
}
// КОНЕЦ дружественной ФУНКЦИИ оператора -


// Дружественная ФУНКЦИЯ перегрузки оператора *
Fraction operator*(const Fraction& fraction1, const Fraction& fraction2) {
	Fraction fraction3;

	fraction3.denominator = fraction1.denominator * fraction2.denominator;
	fraction3.numerator = fraction1.numerator * fraction2.numerator;

	return fraction3;
}
// КОНЕЦ дружественной ФУНКЦИИ оператора *


// Дружественная ФУНКЦИЯ перегрузки оператора /
Fraction operator/(const Fraction& fraction1, const Fraction& fraction2) {
	Fraction fraction3;

	fraction3.denominator = fraction1.denominator * fraction2.numerator;
	fraction3.numerator = fraction1.numerator * fraction2.denominator;

	return fraction3;
}
// КОНЕЦ дружественной ФУНКЦИИ оператора /


// ФУНКЦИЯ определения ширины черты дроби от ширины чисел дроби
std::streamsize widthLine_From_widthNumber(std::streamsize widthNumber) {
	return widthNumber + 2;
}
// КОНЕЦ ФУНКЦИИ


// ФУНКЦИЯ определения ширины чисел дроби
int widthNumber_From_fraction(const Fraction& fraction) {
	int max = 0;
	if (fraction.getDenominator() > fraction.getNumerator()) {
		max = fraction.getDenominator();
	}
	else {
		max = fraction.getNumerator();
	}

	int limit = 1;
	int width = 0;

	while (width < 9) {
		limit *= 10;
		++width;
		if (max < limit) return width;
	}

	return 0;
}
// КОНЕЦ ФУНКЦИИ


// ФУНКЦИЯ демонстрации арифметических действий с дробями
void showFraction(
	const char& sign,             // знак действия
	const Fraction& fraction1,    // дробь 1
	const Fraction& fraction2,    // дробь 2
	const Fraction& fraction3     // дробь 3
) {
	std::streamsize indent = 13;   // общий отступ

	std::streamsize widthNumber1 = widthNumber_From_fraction(fraction1);
	std::streamsize widthLine1 = widthLine_From_widthNumber(widthNumber1);

	std::streamsize widthNumber2 = widthNumber_From_fraction(fraction2);
	std::streamsize widthLine2 = widthLine_From_widthNumber(widthNumber2);

	std::streamsize widthNumber3 = widthNumber_From_fraction(fraction3);
	std::streamsize widthLine3 = widthLine_From_widthNumber(widthNumber3);

	// Линия числителей
	cout
		<< setw(indent) << ""
		<< setw(1) << left << ""
		<< setw(widthNumber1) << left << fraction1.getNumerator()
		<< setw(1) << left << ""
		<< setw(3) << left << ""
		<< setw(1) << left << ""
		<< setw(widthNumber2) << left << fraction2.getNumerator()
		<< setw(1) << left << ""
		<< setw(3) << left << ""
		<< setw(1) << left << ""
		<< setw(widthNumber3) << left << fraction3.getNumerator()
		<< setw(1) << left << ""
		<< endl;

	// Средняя линия
	cout
		<< setw(indent) << ""
		<< setw(0) << left << ""
		<< setw(widthLine1) << left << setfill('-') << "-" << setfill(' ')
		<< setw(0) << left << ""
		<< setw(1) << left << " " << setw(1) << left << sign << setw(1) << left << " "
		<< setw(0) << left << ""
		<< setw(widthLine2) << left << setfill('-') << "-" << setfill(' ')
		<< setw(0) << left << ""
		<< setw(3) << left << " = "
		<< setw(0) << left << ""
		<< setw(widthLine3) << left << setfill('-') << "-" << setfill(' ')
		<< setw(0) << left << ""
		<< endl;

	// Линия знаменателей
	cout
		<< setw(indent) << ""
		<< setw(1) << left << ""
		<< setw(widthNumber1) << left << fraction1.getDenominator()
		<< setw(1) << left << ""
		<< setw(3) << left << ""
		<< setw(1) << left << ""
		<< setw(widthNumber2) << left << fraction2.getDenominator()
		<< setw(1) << left << ""
		<< setw(3) << left << ""
		<< setw(1) << left << ""
		<< setw(widthNumber3) << left << fraction3.getDenominator()
		<< setw(1) << left << ""
		<< endl;
}
// КОНЕЦ ФУНКЦИИ


// ФУНКЦИЯ демонстрации созданных дробей
void showCreatedFraction(
	const Fraction& fraction1,    // дробь 1
	const Fraction& fraction2     // дробь 2
) {
	std::streamsize indent = 3;   // общий отступ

	std::streamsize widthNumber1 = widthNumber_From_fraction(fraction1);
	std::streamsize widthLine1 = widthLine_From_widthNumber(widthNumber1);

	std::streamsize widthNumber2 = widthNumber_From_fraction(fraction2);
	std::streamsize widthLine2 = widthLine_From_widthNumber(widthNumber2);

	// Линия числителей
	cout
		<< setw(indent) << ""
		<< setw(10) << left << ""
		<< setw(1) << left << ""
		<< setw(widthNumber1) << left << fraction1.getNumerator()
		<< setw(1) << left << ""
		<< setw(3) << left << ""
		<< setw(10) << left << ""
		<< setw(1) << left << ""
		<< setw(widthNumber2) << left << fraction2.getNumerator()
		<< setw(1) << left << ""
		<< endl;

	// Средняя линия
	cout
		<< setw(indent) << ""
		<< setw(10) << left << "Дробь 1 = "
		<< setw(widthLine1) << left << setfill('-') << "-" << setfill(' ')
		<< setw(3) << left << " ; "
		<< setw(10) << left << "Дробь 2 = "
		<< setw(widthLine2) << left << setfill('-') << "-" << setfill(' ')
		<< endl;

	// Линия знаменателей
	cout
		<< setw(indent) << ""
		<< setw(10) << left << ""
		<< setw(1) << left << ""
		<< setw(widthNumber1) << left << fraction1.getDenominator()
		<< setw(1) << left << ""
		<< setw(3) << left << ""
		<< setw(10) << left << ""
		<< setw(1) << left << ""
		<< setw(widthNumber2) << left << fraction2.getDenominator()
		<< setw(1) << left << ""
		<< endl;
}
// КОНЕЦ ФУНКЦИИ


// ГЛАВНАЯ ФУНКЦИЯ
int main() {
	setlocale(LC_ALL, "ru");

	// Создадим объекты Дробь 1, Дробь 2, Дробь 3 - для результата
	Fraction f1(1, 3);
	Fraction f2(1, 2);
	Fraction f3;

	// Покажем созданные Дробь 1 и Дробь 2
	cout << " Создадим дроби:" << endl;
	showCreatedFraction(f1, f2);
	pendl;

	// Сложим дроби
	cout << " Сложим дроби:" << endl;
	f3.copy(f1);
	f3.sum(f2);
	showFraction('+', f1, f2, f3);
	pendl;

	// Вычтем дроби
	cout << " Вычтем дроби:" << endl;
	f3.copy(f2);
	f3.sub(f1);
	showFraction('-', f2, f1, f3);
	pendl;

	// Умножим дроби
	cout << " Умножим дроби:" << endl;
	f3.copy(f1);
	f3.mul(f2);
	showFraction('*', f1, f2, f3);
	pendl;

	// Разделим дроби
	cout << " Разделим дроби:" << endl;
	f3.copy(f2);
	f3.div(f1);
	showFraction(':', f2, f1, f3);
	pendl;

	// Сложим дроби оператором +
	cout << " Сложим дроби оператором + :" << endl;
	f3 = f1 + f2;
	showFraction('+', f1, f2, f3);
	pendl;

	// Вычтем дроби оператором -
	cout << " Вычтем дроби оператором - :" << endl;
	f3 = f2 - f1;
	showFraction('-', f2, f1, f3);
	pendl;

	// Умножим дроби оператором *
	cout << " Умножим дроби оператором * :" << endl;
	f3 = f1 * f2;
	showFraction('*', f1, f2, f3);
	pendl;

	// Разделим дроби оператором /
	cout << " Разделим дроби оператором / :" << endl;
	f3 = f2 / f1;
	showFraction('/', f2, f1, f3);
	pendl;

	// Конец
	return 0;
}
// КОНЕЦ ГЛАВНОЙ ФУНКЦИИ

