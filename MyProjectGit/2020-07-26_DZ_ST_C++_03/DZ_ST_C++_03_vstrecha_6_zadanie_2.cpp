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

#include <iostream>
#include <clocale>
#include <iomanip>
#define pendl cout << endl
using namespace std;



class Complex {
private:
	int real{ 0 };					// вещественная часть комплексного числа
	int image{ 0 };					// мнимая часть комплексного числа
public:
	Complex(){}
	Complex(int real, int image) :real(real), image(image){}
	Complex(const Complex& complex) { *this = complex; }

	// прототип дружественной функции вывода комплексного числа на консоль оператором <<
	friend std::ostream& operator<<(std::ostream & out, const Complex & complex);

	// прототип дружественной функции перегрузки оператора +
	friend Complex operator+(const Complex& complex1, const Complex& complex2);

	// прототип дружественной функции перегрузки оператора -
	friend Complex operator-(const Complex& complex1, const Complex& complex2);

	// прототип дружественной функции перегрузки оператора *
	friend Complex operator*(const Complex& complex1, const Complex& complex2);

	// прототип дружественной функции перегрузки оператора /
	friend Complex operator/(const Complex& complex1, const Complex& complex2);
};


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


int main() {
	setlocale(LC_ALL, "ru");

	Complex a(-129, 31);
	Complex b(1, 12);
	Complex c;
	cout << " Создадим два комплексных числа: " << a << " и " << b << endl;

	// сложим два комплексных числа оператором +
	c = a + b;
	cout << " Сложим два комплексных числа оператором + : " << a << " + " << b << " = " << c << endl;

	// вычтем два комплексных числа оператором -
	c = a - b;
	cout << " Вычтем два комплексных числа оператором - : " << a << " - " << b << " = " << c << endl;

	// умножим два комплексных числа оператором *
	c = a * b;
	cout << " Умножим два комплексных числа оператором * : " << a << " * " << b << " = " << c << endl;

	// разделим два комплексных числа оператором /
	c = a / b;
	cout << " Разделим два комплексных числа оператором / : " << a << " / " << b << " = " << c << endl;

	return 0;
}
