// DZ_ST_C++_07_dz23_vstrecha23_zadanie_Complex.cpp
//
// задание из файла DZ_ST_C++_03.pdf
// Встреча №6
// Тема: Перегрузка операторов
// Задание 2.
/*
Создайте класс Complex (комплексное число) или исполь-
зуйте уже созданный вами класс. Создайте перегруженные
операторы для реализации арифметических операций для
по работе с комплексными числами (операции +, -, *, /).
*/
#pragma once
#include <iostream>
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_Complex.h"

namespace spaceComplex
{

	// Дружественная ФУНКЦИЯ вывода комплексного числа на консоль оператором <<
	std::ostream& operator<<(std::ostream& out, const Complex& complex) {
		out << complex.real << (complex.image < 0 ? "" : "+") << complex.image << "i";
		return out;
	}
	// КОНЕЦ дружественной ФУНКЦИИ оператора <<


	// Дружественная ФУНКЦИЯ перегрузки оператора +
	Complex operator+(const Complex& complex1, const Complex& complex2) {
		Complex complex3;

		complex3.real = complex1.real + complex2.real;
		complex3.image = complex1.image + complex2.image;

		return complex3;
	}
	// КОНЕЦ дружественной ФУНКЦИИ оператора +


	// Дружественная ФУНКЦИЯ перегрузки оператора -
	Complex operator-(const Complex& complex1, const Complex& complex2) {
		Complex complex3;

		complex3.real = complex1.real - complex2.real;
		complex3.image = complex1.image - complex2.image;

		return complex3;
	}
	// КОНЕЦ дружественной ФУНКЦИИ оператора -


	// Дружественная ФУНКЦИЯ перегрузки оператора *
	Complex operator*(const Complex& complex1, const Complex& complex2) {
		Complex complex3;

		complex3.real = complex1.real * complex2.real - complex1.image * complex2.image;
		complex3.image = complex1.image * complex2.real + complex1.real * complex2.image;

		return complex3;
	}
	// КОНЕЦ дружественной ФУНКЦИИ оператора *


	// Дружественная ФУНКЦИЯ перегрузки оператора /
	Complex operator/(const Complex& complex1, const Complex& complex2) {
		Complex complex3;

		complex3.real =
			(complex1.real * complex2.real + complex1.image * complex2.image) /
			(complex2.real * complex2.real + complex2.image * complex2.image);

		complex3.image =
			(complex1.image * complex2.real - complex1.real * complex2.image) /
			(complex2.real * complex2.real + complex2.image * complex2.image);

		return complex3;
	}
	// КОНЕЦ дружественной ФУНКЦИИ оператора /


	// Дружественная ФУНКЦИЯ перегрузки оператора +
	Test operator+(const Test& complex1, const Test& complex2) {
		Test complex3;

		complex3.real = complex1.real + complex2.real;
		complex3.image = complex1.image + complex2.image;

		return complex3;
	}
	// КОНЕЦ дружественной ФУНКЦИИ оператора +


}
