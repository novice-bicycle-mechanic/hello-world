// ������� �� ����� DZ_ST_C++_03.pdf
// ������� �6
// ����: ���������� ����������
// ������� 2.
/*
�������� ����� Complex (����������� �����) ��� ������-
����� ��� ��������� ���� �����. �������� �������������
��������� ��� ���������� �������������� �������� ���
�� ������ � ������������ ������� (�������� +, -, *, /).
*/

#include <iostream>
#include <clocale>
#include <iomanip>
#define pendl cout << endl
using namespace std;



class Complex {
private:
	int real{ 0 };					// ������������ ����� ������������ �����
	int image{ 0 };					// ������ ����� ������������ �����
public:
	Complex(){}
	Complex(int real, int image) :real(real), image(image){}
	Complex(const Complex& complex) { *this = complex; }

	// �������� ������������� ������� ������ ������������ ����� �� ������� ���������� <<
	friend std::ostream& operator<<(std::ostream & out, const Complex & complex);

	// �������� ������������� ������� ���������� ��������� +
	friend Complex operator+(const Complex& complex1, const Complex& complex2);

	// �������� ������������� ������� ���������� ��������� -
	friend Complex operator-(const Complex& complex1, const Complex& complex2);

	// �������� ������������� ������� ���������� ��������� *
	friend Complex operator*(const Complex& complex1, const Complex& complex2);

	// �������� ������������� ������� ���������� ��������� /
	friend Complex operator/(const Complex& complex1, const Complex& complex2);
};


// ������������� ������� ������ ������������ ����� �� ������� ���������� <<
std::ostream& operator<<(std::ostream& out, const Complex& complex) {
	out << complex.real << (complex.image < 0 ? "" : "+") << complex.image << "i";
	return out;
}
// ����� ������������� ������� ��������� <<


// ������������� ������� ���������� ��������� +
Complex operator+(const Complex& complex1, const Complex& complex2) {
	Complex complex3;

	complex3.real = complex1.real + complex2.real;
	complex3.image = complex1.image + complex2.image;

	return complex3;
}
// ����� ������������� ������� ��������� +


// ������������� ������� ���������� ��������� -
Complex operator-(const Complex& complex1, const Complex& complex2) {
	Complex complex3;

	complex3.real = complex1.real - complex2.real;
	complex3.image = complex1.image - complex2.image;

	return complex3;
}
// ����� ������������� ������� ��������� -


// ������������� ������� ���������� ��������� *
Complex operator*(const Complex& complex1, const Complex& complex2) {
	Complex complex3;

	complex3.real = complex1.real * complex2.real - complex1.image * complex2.image;
	complex3.image = complex1.image * complex2.real + complex1.real * complex2.image;

	return complex3;
}
// ����� ������������� ������� ��������� *


// ������������� ������� ���������� ��������� /
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
// ����� ������������� ������� ��������� /


int main() {
	setlocale(LC_ALL, "ru");

	Complex a(-129, 31);
	Complex b(1, 12);
	Complex c;
	cout << " �������� ��� ����������� �����: " << a << " � " << b << endl;

	// ������ ��� ����������� ����� ���������� +
	c = a + b;
	cout << " ������ ��� ����������� ����� ���������� + : " << a << " + " << b << " = " << c << endl;

	// ������ ��� ����������� ����� ���������� -
	c = a - b;
	cout << " ������ ��� ����������� ����� ���������� - : " << a << " - " << b << " = " << c << endl;

	// ������� ��� ����������� ����� ���������� *
	c = a * b;
	cout << " ������� ��� ����������� ����� ���������� * : " << a << " * " << b << " = " << c << endl;

	// �������� ��� ����������� ����� ���������� /
	c = a / b;
	cout << " �������� ��� ����������� ����� ���������� / : " << a << " / " << b << " = " << c << endl;

	return 0;
}
