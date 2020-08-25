// DZ_ST_C++_07_dz23_vstrecha23_zadanie_Complex.h
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

namespace spaceComplex
{
	class Complex {
	protected:
		int real{ 0 };					// вещественная часть комплексного числа
		int image{ 0 };					// мнимая часть комплексного числа
	public:
		Complex() {}
		Complex(int real, int image) :real(real), image(image) {}
		Complex(const Complex& complex) { *this = complex; }

		// прототип дружественной функции вывода комплексного числа на консоль оператором <<
		friend std::ostream& operator<<(std::ostream& out, const Complex& complex);

		// прототип дружественной функции перегрузки оператора +
		friend Complex operator+(const Complex& complex1, const Complex& complex2);

		// прототип дружественной функции перегрузки оператора -
		friend Complex operator-(const Complex& complex1, const Complex& complex2);

		// прототип дружественной функции перегрузки оператора *
		friend Complex operator*(const Complex& complex1, const Complex& complex2);

		// прототип дружественной функции перегрузки оператора /
		friend Complex operator/(const Complex& complex1, const Complex& complex2);
	};


	// КЛАСС Test для проверки работы namespace при совпадении идентификаторов типа
	class Test : public Complex {
	public:
		Test() : Complex() {}

		Test(int real_, int image_) : Complex(real_, image_) {}

	// прототип дружественной функции перегрузки оператора +
	friend Test operator+(const Test& complex1, const Test& complex2);

	};

}
