// задание из файла "homework 14.pdf"

#include <iostream>
#include <clocale>
#include <ctime>

#define N "\n"

using namespace std;


//--------------------------------------------------------------------------------------


void printingAnArray					// ФУНКЦИЯ печати динамического массива
(
	int staticArray[],							// указатель на динамический массив

	size_t length								// длина динамического массива
)
{
	for (size_t i = 0; i < length; i++)
	{
		cout << " " << staticArray[i];
	}

	cout << N << endl;
}


//--------------------------------------------------------------------------------------

void distributionValues					// ФУНКЦИЯ распределения значений по разным массивам
(
	int staticArray[],							// указатель на динамический массив

	size_t length,								// длина динамического массива

	int*& arrayPositiv,							// указатель на массив положительных значений

	int*& arrayNegativ,							// указатель на массив отрицательных значений

	int*& arrayZero,							// указатель на массив нулевых значений

	size_t& numPositiv,							// количество положительных значений в массиве

	size_t& numNegativ,							// количество отрицательных значений в массиве

	size_t& numZero								// количество нулевых значений в массиве
)
{

	for (size_t i = 0; i < length; i++)			// подсчет значений по знакам
	{
		if(staticArray[i] > 0)
		{
			numPositiv++;
		}
		else if (staticArray[i] < 0)
		{
			numNegativ++;
		}
		else 
		{
			numZero++;
		}
	}

	arrayPositiv = new int[numPositiv] {};		// создание массива положительных значений

	arrayNegativ = new int[numNegativ] {};		// создание массива отрицательных значений

	arrayZero = new int[numZero] {};			// создание массива нулевых значений

	// обнулим счетчики длин массивов для последующего отсчета номеров элементов

	numPositiv = 0;

	numNegativ = 0;

	numZero = 0;

	// заполним массивы соответствующими значениями из изначального массива

	for (size_t i = 0; i < length; i++)
	{
		if (staticArray[i] > 0)
		{
			arrayPositiv[numPositiv++] = staticArray[i];
		}
		else if (staticArray[i] < 0)
		{
			arrayNegativ[numNegativ++] = staticArray[i];
		}
		else
		{
			arrayZero[numZero++] = staticArray[i];
		}
	}
}


//--------------------------------------------------------------------------------------


int main()
{
	setlocale(LC_ALL, "ru");

	//-----------------------------------------------

	//                          Домашнее задание №14

	// Тема: Указатели. Передача параметров.

	//                         Встреча №28. Задание 2

	//     Написать  функцию, которая  получает  указатель на статический массив
	// и его размер. Функция распределяет положительные, отрицательные и нулевые
	// элементы в отдельные динамические массивы.

	cout
		<< "                            Домашнее задание №14"

		N N" Тема: Указатели. Передача параметров."

		N N"                           Встреча №28. Задание 2"

		N N"     Написать  функцию, которая  получает  указатель на статический массив"

		N N" и его размер. Функция распределяет положительные, отрицательные и нулевые"

		N N" элементы в отдельные динамические массивы."

		<< N << endl;

	const size_t length = 20;					// длина статического массива

	int staticArray[length];					// статический массив

	int* arrayPositiv = nullptr;				// указатель на массив положительных значений

	int* arrayNegativ = nullptr;				// указатель на массив отрицательных значений

	int* arrayZero = nullptr;					// указатель на массив нулевых значений

	size_t numPositiv = 0;						// количество положительных значений в массиве

	size_t numNegativ = 0;						// количество отрицательных значений в массиве

	size_t numZero = 0;							// количество нулевых значений в массиве

	srand((unsigned int)time(0));				// настроим генератор случайных чисел

	(void)rand();

	(void)rand();

	// заполним массив случайными значениями от -10 до +9

	for (size_t i = 0; i < length; i++)			
	{
		staticArray[i] = rand() * length / RAND_MAX - length / 2;
	}

	size_t nunZero = rand() * length / 3 / RAND_MAX;		// добавляемое количество нулевых значений в массиве

	for (size_t i = 0, k = 0; k < nunZero; k++)
	{
		i = rand() * length / RAND_MAX;						// случайный номер элемента с нулевым значением

		if (i < length)										// проверка индекса на вхождение в диапазон
		{
			staticArray[i] = 0;								// присвоение 0 случайно выбранному элементу
		}
	}

	// печать массива

	cout << " Создан статический массив:" << N << endl;

	printingAnArray(staticArray, length);

	// Заполним массивы соответствующими значениями

	distributionValues									// функция распределения значений по знаку
	(
		staticArray, length,							// указатель и длина массива исходных значений

		arrayPositiv, arrayNegativ, arrayZero,			// указатели массивов распределенных значений

		numPositiv, numNegativ, numZero					// длины массивов распределенных значений
	);

	// распечатаем массивы распределенных значений

	cout << " Сформирован массив положительных значений:" << N << endl;

	printingAnArray(arrayPositiv, numPositiv);

	cout << " Сформирован массив отрицательных значений:" << N << endl;

	printingAnArray(arrayNegativ, numNegativ);

	cout << " Сформирован массив нулевых значений:" << N << endl;

	printingAnArray(arrayZero, numZero);

	//-----------------------------------------------

	return 0;
}
