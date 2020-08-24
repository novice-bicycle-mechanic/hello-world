// DZ_ST_C++_07_dz23_vstrecha23_zadanie_Matrix_main.cpp


// задание 1 из файла Domasnee_zadanie_1594661480.txt
// Выполните домашние задания после уроков 3, 4, 5
// Урок 5. Задание 2
/*
2.	Создать класс для работы с матрицами.
Предусмотреть, как минимум, функции для сложения матриц,
умножения матриц, транспонирования матриц, присваивания
матриц друг другу, установка и получение произвольного
элемента матрицы. Необходимо перегрузить соответствующие
операторы.
*/
#include <iostream>
#include <clocale>
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_Matrix.h"
using namespace math;


// ГЛАВНАЯ ФУНКЦИЯ
int main() {
	setlocale(LC_ALL, "ru");

	Matrix m1;
	std::cout << " Матрица m1:" << std::endl;
	std::cout << m1 << std::endl;
	std::cout << std::endl;

	size_t m = 3;
	size_t n = 5;
	Matrix m2(m, n);
	std::cout << " Матрица m2:" << std::endl;
	std::cout << m2 << std::endl;
	std::cout << std::endl;

	std::cout << " Проверка работы индексации двумерного массива" << std::endl;
	std::cout << " Результат: m2[1][1] == " << m2[1][1] << std::endl;
	std::cout << " Присвоим значение: m2[1][1] = 11" << std::endl;
	m2[1][1] = 11;
	std::cout << " Результат: m2[1][1] == " << m2[1][1] << std::endl;
	std::cout << " Матрица m2:" << std::endl;
	std::cout << m2 << std::endl;
	std::cout << std::endl;

	m1 = m2;
	std::cout << " Матрица m1 = m2:" << std::endl;
	std::cout << m1 << std::endl;
	std::cout << std::endl;

	Matrix m3 = m2;
	std::cout << " Матрица m3 = m2:" << std::endl;
	std::cout << m3 << std::endl;
	std::cout << std::endl;

	m1 = m2 + m3;
	std::cout << " Матрица m1 = m2 + m3:" << std::endl;
	std::cout << m1 << std::endl;
	std::cout << std::endl;

	m3 = m2 - m1;
	std::cout << " Матрица m3 = m2 - m1:" << std::endl;
	std::cout << m3 << std::endl;
	std::cout << std::endl;

	std::cout << " Транспонируем матрицу m3" << std::endl;
	m3.transpose();
	std::cout << " Матрица m3:" << std::endl;
	std::cout << m3 << std::endl;
	std::cout << std::endl;

	std::cout << " Матрица m2:" << std::endl;
	std::cout << m2 << std::endl;
	std::cout << std::endl;

	m1 = m2 * m3;
	std::cout << " Матрица m1 = m2 * m3:" << std::endl;
	std::cout << m1 << std::endl;
	std::cout << std::endl;

	//	std::cout << " Конец main()" << std::endl;
	return 0;
}
// Конец ГЛАВНОЙ ФУНКЦИИ
