// задание из файла problemy_1592453914.txt
// файл Lab_C++_week_1.pdf, Встреча 2, задание 3
/*
	К уже реализованному классу Дробь добавьте необходимые
конструкторы, сделайте ряд функций inline, используйте
инициализаторы.
(Файл DZ_ST_C++_01.pdf, Встреча 1, задание:
Реализуйте класс Дробь. Необходимо хранить числитель
и знаменатель в качестве переменных-членов.
Реализуйте функции-члены для ввода данных в переменные-члены,
для выполнения арифметических операций (сложение,
вычитание, умножение, деление, и т.д.)).
*/
#include <iostream>
#include <clocale>
#include <iomanip>
#define pendl cout << endl
using namespace std;


// КЛАСС Дробь
class Fraction {
private:
	int numerator  { 0 };    // числитель
	int denominator{ 1 };    // знаменатель
public:
	// КОНСТРУКТОР по умолчанию
	Fraction(){}

	// КОНСТРУКТОР с параметрами
	Fraction(
		int numerator,
		int denominator
	) {
		setNumerator  (numerator  );
		setDenominator(denominator);
	}

	// КОНСТРУКТОР копирования
	Fraction(Fraction& object) { *this = object; }

	// SETTER-ы
	inline void setNumerator  (int numerator  ) { this->numerator   = numerator  ; }
	inline void setDenominator(int denominator) { this->denominator = denominator; }

	// GETTER-ы
	inline int getNumerator  () { return numerator  ; }
	inline int getDenominator() { return denominator; }

	// МЕТОД копирования значений дроби
	//       от Дроби-аргумента к Дроби-владельцу метода
	inline void copy(Fraction fraction2) {
		this->numerator   = fraction2.getNumerator  ();
		this->denominator = fraction2.getDenominator();
	}

	// МЕТОД сложения дробей
	bool sum(Fraction fraction2) {
		if (this->denominator != fraction2.getDenominator()) {
			int lcm = this->lcm(fraction2);
			if (lcm) {
				this->numerator *= lcm / this->denominator;
				this->denominator = lcm;
				this->numerator += fraction2.getNumerator() * lcm / fraction2.getDenominator();
			}
			else return false;
		}
		else {
			this->numerator += fraction2.getNumerator();
		}
		return true;
	}

	// МЕТОД вычитания дробей с одинаковыми знаменателями
	bool sub(Fraction fraction2) {
		if (this->denominator != fraction2.getDenominator()) {
			int lcm = this->lcm(fraction2);
			if (lcm) {
				this->numerator *= lcm / this->denominator;
				this->denominator = lcm;
				this->numerator -= fraction2.getNumerator() * lcm / fraction2.getDenominator();
			}
			else return false;
		}
		else {
			this->numerator -= fraction2.getNumerator();
		}
		return true;
	}

	// МЕТОД умножения дробей
	bool mul(Fraction fraction2) {
		int denominator = this->denominator;
		denominator *= fraction2.getDenominator();
		if (denominator) {
			this->denominator = denominator;
			this->numerator *= fraction2.getNumerator();
			return true;
		}
		else return false;
	}

	// МЕТОД деления дробей
	bool div(Fraction fraction2) {
		int denominator = this->denominator;
		denominator *= fraction2.getNumerator();
		if (denominator) {
			this->denominator = denominator;
			this->numerator *= fraction2.getDenominator();
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
	int lcm(Fraction fraction2) {

		// создадим переменные
		long long int min{ 0 };             // меньшее число из двух
		long long int max{ 0 };             // большее число из двух
		long long int multiplier{ 0 };      // множитель большего числа
		long long int lcm{ 0 };             // LCM - НОК

		// !!! здесь и далее, до особого предупреждения:
		// min и max - просто числа,
		// multiplier - буфер для обмена значениями

		// скопируем значения знаменателей дробей в переменные
		// если только они не равны 0, иначе - ошибка - возврат 0
		if (this->denominator) min = this->denominator;
		else return 0;
		if (fraction2.getDenominator()) max = fraction2.getDenominator();
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
};
// КОНЕЦ КЛАССА


// ФУНКЦИЯ определения ширины черты дроби от ширины чисел дроби
std::streamsize widthLine_From_widthNumber(std::streamsize widthNumber) {
	return widthNumber + 2;
}
// КОНЕЦ ФУНКЦИИ


// ФУНКЦИЯ определения ширины чисел дроби
int widthNumber_From_fraction(Fraction fraction) {
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
	char sign,             // знак действия
	Fraction fraction1,    // дробь 1
	Fraction fraction2,    // дробь 2
	Fraction fraction3     // дробь 3
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
	Fraction fraction1,    // дробь 1
	Fraction fraction2     // дробь 2
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
	Fraction f1{ 1, 3 };
	Fraction f2{ 1, 2 };
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

	// Конец
	return 0;
}
// КОНЕЦ ГЛАВНОЙ ФУНКЦИИ










































































