// DZ_ST_C++_07_dz23_vstrecha23_zadanie_Fraction_main.cpp
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

#include <iostream>
#include <clocale>
#include <iomanip>
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_Fraction.h"
using namespace math;

// ГЛАВНАЯ ФУНКЦИЯ
int main() {
	setlocale(LC_ALL, "ru");

	// Создадим объекты Дробь 1, Дробь 2, Дробь 3 - для результата
	Fraction f1(1, 3);
	Fraction f2(1, 2);
	Fraction f3;

	// Покажем созданные Дробь 1 и Дробь 2
	std::cout << " Создадим дроби:" << std::endl;
	showCreatedFraction(f1, f2);
	std::cout << std::endl;

	// Сложим дроби
	std::cout << " Сложим дроби:" << std::endl;
	f3.copy(f1);
	f3.sum(f2);
	showFraction('+', f1, f2, f3);
	std::cout << std::endl;

	// Вычтем дроби
	std::cout << " Вычтем дроби:" << std::endl;
	f3.copy(f2);
	f3.sub(f1);
	showFraction('-', f2, f1, f3);
	std::cout << std::endl;

	// Умножим дроби
	std::cout << " Умножим дроби:" << std::endl;
	f3.copy(f1);
	f3.mul(f2);
	showFraction('*', f1, f2, f3);
	std::cout << std::endl;

	// Разделим дроби
	std::cout << " Разделим дроби:" << std::endl;
	f3.copy(f2);
	f3.div(f1);
	showFraction(':', f2, f1, f3);
	std::cout << std::endl;

	// Сложим дроби оператором +
	std::cout << " Сложим дроби оператором + :" << std::endl;
	f3 = f1 + f2;
	showFraction('+', f1, f2, f3);
	std::cout << std::endl;

	// Вычтем дроби оператором -
	std::cout << " Вычтем дроби оператором - :" << std::endl;
	f3 = f2 - f1;
	showFraction('-', f2, f1, f3);
	std::cout << std::endl;

	// Умножим дроби оператором *
	std::cout << " Умножим дроби оператором * :" << std::endl;
	f3 = f1 * f2;
	showFraction('*', f1, f2, f3);
	std::cout << std::endl;

	// Разделим дроби оператором /
	std::cout << " Разделим дроби оператором / :" << std::endl;
	f3 = f2 / f1;
	showFraction('/', f2, f1, f3);
	std::cout << std::endl;

	// Конец
	return 0;
}
// КОНЕЦ ГЛАВНОЙ ФУНКЦИИ

