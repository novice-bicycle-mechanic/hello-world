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
Создадим пространства с вложенными классами:
1) math (математика):
  а) Complex;
  б) Fraction;
  в) Matrix;
2) datetime (дата и время):
  а) Date;
  б) Time;
3) programming (программирование):
  а) DynamicArray
*/

#include <iostream>
#include <clocale>
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_Complex.h"
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_Fraction.h"
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_Matrix.h"
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_Date.h"
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_Time.h"
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_DynamicArray.h"


int main() {
	setlocale(LC_ALL, "ru");

	std::cout
		<< " Демонстрация работы кода из пространств: std, math, datetime, programming"
		<< std::endl;
	std::cout
		<< "---------------------------------------------------------------------------"
		<< std::endl;

	// -------------- класс Complex пространства math -----------------------

	// Создадим три объекта-комплексных числа
	math::Complex a(-129, 31);
	math::Complex b(1, 12);
	math::Complex c;
	std::cout
		<< " Создадим два комплексных числа: "
		<< a << " и " << b
		<< std::endl;

	// сложим два комплексных числа оператором +
	c = a + b;
	std::cout
		<< " Сложим два комплексных числа: "
		<< a << " + " << b << " = " << c
		<< std::endl;

	std::cout
		<< "---------------------------------------------------------------------------"
		<< std::endl;

	// -------------- класс Fraction пространства math -----------------------

	// Создадим объекты Дробь 1, Дробь 2, Дробь 3 - для результата
	math::Fraction f1(1, 3);
	math::Fraction f2(1, 2);
	math::Fraction f3;

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

	std::cout
		<< "---------------------------------------------------------------------------"
		<< std::endl;

	// -------------- класс Matrix пространства math -----------------------

	size_t m = 3;
	size_t n = 5;
	math::Matrix m2(m, n);
	std::cout << " Матрица m2:" << std::endl;
	std::cout << m2 << std::endl;
	std::cout << std::endl;

	std::cout << " Транспонируем матрицу m2" << std::endl;
	m2.transpose();
	std::cout << " Матрица m2:" << std::endl;
	std::cout << m2 << std::endl;
	std::cout << std::endl;

	std::cout
		<< "---------------------------------------------------------------------------"
		<< std::endl;

	// -------------- класс Date пространства datetime -----------------------

		// создание объекта конструктором с параметрами
	std::cout << " Создадим объект Дата: ";
	datetime::Date date1(29, 02, 2000);
	std::cout << "Дата " << date1() << " == " << date1 << std::endl;
	std::cout << std::endl;

	// изменение значения объекта перегруженным оператором ++C
	std::cout << " Изменим значение объекта Дата " << date1() << " == " << date1 << " оператором ++С >>> " << std::endl;
	std::cout << " Дата " << date1() << " == " << ++date1 << std::endl;
	std::cout << std::endl;

	std::cout
		<< "---------------------------------------------------------------------------"
		<< std::endl;

	// -------------- класс Time пространства datetime -----------------------

	std::cout << " Работа со временем" << std::endl << std::endl;

	datetime::Time time1(13, 34, 35);
	std::cout << " time1: " << time1 << std::endl;
	std::cout << std::endl;

	datetime::Time time2(19, 04, 55);
	std::cout << " time2: " << time2 << std::endl;
	std::cout << std::endl;

	datetime::Time time3 = time1 + time2;
	std::cout << " time3 = time1 + time2 == " << time3 << std::endl;
	std::cout << std::endl;

	std::cout
		<< "---------------------------------------------------------------------------"
		<< std::endl;

	// -------------- класс DynamicArray пространства programming -----------------------

	std::cout << " Работа с динамическими массивами" << std::endl << std::endl;

	programming::DynamicArray arr1(5);
	arr1.rang();
	std::cout << " arr1: " << arr1 << std::endl;
	std::cout << std::endl;

	programming::DynamicArray arr2(3);
	arr2.rang();
	std::cout << " arr2: " << arr2 << std::endl;
	std::cout << std::endl;

	programming::DynamicArray arr3 = arr1 + arr2;
	std::cout << " arr3 = arr1 + arr2 >>> " << arr3 << std::endl;
	std::cout << std::endl;

	std::cout
		<< "---------------------------------------------------------------------------"
		<< std::endl;

	// --------------------------------------------------------------------------------

	return 0;
}
