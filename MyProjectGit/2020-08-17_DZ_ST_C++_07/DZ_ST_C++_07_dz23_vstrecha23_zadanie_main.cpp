// DZ_ST_C++_07_dz23_vstrecha23_zadanie_main.cpp
//
// Задание из файла DZ_ST_C++_07.pdf
// Домашнее задание №23
// Встреча №23, задание
// Тема: Пространства имен
/*
В рамках предыдущих самостоятельных и домашних заданий
вы создали набор классов по работе с различными
примитивными математическими операциями (дробь,
точка в двумерном пространстве, точка в трехмерном
пространстве и т.д.). Разместите уже созданные классы
в пространствах имен. Продумайте правильную структуру
созданных пространств. Используя механизм пространств
напишите код по тестированию полученного решения.
*/

 /*
Создадим пространства имен с дочерними классами Test:
  1) spaceComplex;
  2) spaceFraction;
  3) spaceMatrix;
  4) spaceDate;
  5) spaceTime;
  6) spaceDynamicArray
*/

#include <iostream>
#include <clocale>
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_Complex.h"
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_Fraction.h"
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_Matrix.h"
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_Date.h"
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_Time.h"
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_DynamicArray.h"
using namespace std;


class Test {
public:
	const char* str{ " Это строка из класса std::Test" };
};


int main() {
	setlocale(LC_ALL, "ru");

	cout << " Демонстрация работы кода из пространств имен"	<< endl;
	cout << "---------------------------------------------------------------------------" << endl;

	// -------------- класс Test пространства имен std -----------------------

	//                            !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// здесь идентификатор типа Test применяется
	// без указания пространства имен std,
	// так как глобально применена директива: using namespace std;
	Test testStr;
	cout << testStr.str << endl;

	cout << "---------------------------------------------------------------------------" << endl;

	// -------------- класс Test пространства имен spaceComplex -----------------------

	// Создадим три объекта-комплексных числа
	spaceComplex::Test a(-129, 31);
	spaceComplex::Test b(1, 12);

	//                            !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// Здесь идентификатор типа Test из std::Test,
	// применяемый без указания идентификатора пространства имен std
	// замещается идентификатором типа Test из spaceComplex::Test
	// и применяется далее также без указания идентификатора пространства имен spaceComplex
	using spaceComplex::Test;
	Test c;

	cout
		<< " Создадим два комплексных числа: "
		<< a << " и " << b
		<< endl;

	// сложим два комплексных числа оператором +
	c = a + b;
	cout
		<< " Сложим два комплексных числа: "
		<< a << " + " << b << " = " << c
		<< endl;

	cout << "---------------------------------------------------------------------------" << endl;

	// -------------- класс Test пространства имен spaceFraction -----------------------

	// Создадим объекты Дробь 1, Дробь 2, Дробь 3 - для результата
	spaceFraction::Test f1(1, 3);
	spaceFraction::Test f2(1, 2);

	//                            !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// здесь для идентификатора пространства имен spaceFraction
	// вводится и применяется псевдоним NicknameFraction
	namespace NicknameFraction = spaceFraction;
	NicknameFraction::Test f3;

	// Покажем созданные Дробь 1 и Дробь 2
	cout << " Создадим дроби:" << endl;
	showCreatedFraction(f1, f2);
	cout << endl;

	// Сложим дроби
	cout << " Сложим дроби:" << endl;
	f3.copy(f1);
	f3.sum(f2);
	showFraction('+', f1, f2, f3);
	cout << endl;

	cout << "---------------------------------------------------------------------------" << endl;

	// -------------- класс Test пространства имен spaceMatrix -----------------------

	size_t m = 3;
	size_t n = 5;
	spaceMatrix::Test m2(m, n);
	cout << " Матрица m2:" << endl;
	cout << m2 << endl;
	cout << endl;

	cout << " Транспонируем матрицу m2" << endl;
	m2.transpose();
	cout << " Матрица m2:" << endl;
	cout << m2 << endl;
	cout << endl;

	cout << "---------------------------------------------------------------------------" << endl;

	// -------------- класс Test пространства имен spaceDate -----------------------

		// создание объекта конструктором с параметрами
	cout << " Создадим объект Дата: ";
	spaceDate::Test date1(29, 02, 2000);
	cout << "Дата == " << date1 << endl;
	cout << endl;

	// изменение значения объекта перегруженным оператором ++C
	cout << " Изменим значение объекта Дата == " << date1 << " оператором ++С >>> " << endl;
	cout << " Дата == " << ++date1 << endl;
	cout << endl;

	cout << "---------------------------------------------------------------------------" << endl;

	// -------------- класс Test пространства имен spaceTime -----------------------

	cout << " Работа со временем" << endl << endl;

	spaceTime::Test time1(13, 34, 35);
	cout << " time1: " << time1 << endl;
	cout << endl;

	spaceTime::Test time2(19, 04, 55);
	cout << " time2: " << time2 << endl;
	cout << endl;

	spaceTime::Test time3 = time1 + time2;
	cout << " time3 = time1 + time2 == " << time3 << endl;
	cout << endl;

	cout << "---------------------------------------------------------------------------" << endl;

	// -------------- класс Test пространства имен spaceDynamicArray -----------------------

	cout << " Работа с динамическими массивами" << endl << endl;

	spaceDynamicArray::Test arr1(5);
	arr1.rang();
	cout << " arr1: " << arr1 << endl;
	cout << endl;

	spaceDynamicArray::Test arr2(3);
	arr2.rang();
	cout << " arr2: " << arr2 << endl;
	cout << endl;

	spaceDynamicArray::Test arr3 = arr1 + arr2;
	cout << " arr3 = arr1 + arr2 >>> " << arr3 << endl;
	cout << endl;

	cout << "---------------------------------------------------------------------------" << endl;

	// --------------------------------------------------------------------------------

	return 0;
}
