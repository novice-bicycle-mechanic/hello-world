// задание из файла "homework 18.pdf"
	//--------------------------------------------

	//                          Домашнее задание №18

	// Тема: Многомерные динамические массивы

	//                         Встреча №35. Задание 2

	//     Есть 3 двумерных массива A, B, C. Количество строк и столбцов для них
	// вводит пользователь с клавиатуры для каждого из них.
	//     Задание:
	// • Создать одномерный массив, который содержит общие значения для A, B, C.
	// • Создать одномерный массив, который содержит уникальные значения для A, B, C.
	// • Создать одномерный массив, который содержит общие значения для A и C.
	// • Создать одномерный массив, который содержит отрицательные значения для
	//   A, B, C без повторений.

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include <iomanip>

#define N "\n"

using namespace std;


//--------------------------------------------------------------------


bool compareToMatchPreviousOnes			// ФУНКЦИЯ проверки в указанном двумерном массиве элемента
										//         value на сходство с предшевствующими элементами
(
	int value,								// проверяемое на совпадение значение

	int** twoDimArr,						// указатель на двумерный массив

	size_t row,								// номер строки массива, где находится value

	size_t col,								// номер колонки массива, где находится value

	size_t colMax							// номер колонки массива, где находится value
)
{
	for (size_t i = 0; i <= row; i++)
	{
		for (size_t j = 0; j < ((i != row) ? (colMax) : (col)); j++)
		{
			if (twoDimArr[i][j] == value)
			{
				return true;
			}
		}
	}

	return false;
}


//--------------------------------------------------------------------


bool compareToMatchPreviousOnes			// ФУНКЦИЯ проверки в указанном одномерном массиве элемента
										//         value на сходство с предшевствующими элементами
(
	int value,								// проверяемое на совпадение значение

	int* oneDimArr,							// указатель на одномерный массив

	size_t numItem							// номер элемента массива, где находится value
)
{
	for (size_t i = 0; i < numItem; i++)
	{
		if (oneDimArr[i] == value)
		{
			return true;
		}
	}

	return false;
}


//--------------------------------------------------------------------


bool uniqueElementInTwoDimArray			// ФУНКЦИЯ проверки в указанном двумерном массиве
										//         значения value на не сходство с элементами
(
	int value,								// проверяемое на совпадение значение

	int** twoDimArr,						// указатель на двумерный массив

	size_t row,								// количество строк массива

	size_t col								// количество колонок массива
)
{
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{
			if (twoDimArr[i][j] == value)
			{
				return false;
			}
		}
	}

	return true;
}


//--------------------------------------------------------------------


int* unique							// ФУНКЦИЯ поиска уникальных значений в трех двумерных массивах
									//         и создания одномерного массива с найденными значениями
(
	size_t& sizeNewArr,						// ссылка на размер массива уникальных элементов

	int** first,							// первый массив

	size_t* sizesFirst,						// размеры первого массива

	int** second,							// второй массив

	size_t* sizesSecond,					// размеры второго массива

	int** third,							// третий массив

	size_t* sizesThird						// размеры третьего массива
)
{
	int* arrUnique = nullptr;				// указатель на массив уникальных элементов

	size_t sizeUnique = 0;					// размер массива уникальных элементов

	for (size_t k = 0; k < 2; k++)			// цикл режимов работы: 0 - подсчет и создание; 1 - заполнение
	{
		sizeUnique = 0;

		// проверим на уникальность элементы первого массива

		for (size_t i = 0; i < sizesFirst[0]; i++)
		{
			for (size_t j = 0; j < sizesFirst[1]; j++)
			{
				if ((!compareToMatchPreviousOnes(first[i][j], first, i, j, sizesFirst[1]))

					&& (uniqueElementInTwoDimArray(first[i][j], second, sizesSecond[0], sizesSecond[1]))

					&& (uniqueElementInTwoDimArray(first[i][j], third, sizesThird[0], sizesThird[1])))
				{
					// если элемент уникальный

					if (arrUnique)								// если здесь не nullptr
					{
						arrUnique[sizeUnique] = first[i][j];	// задать значение
					}

					sizeUnique++;								// увеличиваем индекс для следующей итерации
				}
			}
		}

		// проверим на уникальность элементы второго массива

		for (size_t i = 0; i < sizesSecond[0]; i++)
		{
			for (size_t j = 0; j < sizesSecond[1]; j++)
			{
				if ((!compareToMatchPreviousOnes(second[i][j], second, i, j, sizesSecond[1]))

					&& (uniqueElementInTwoDimArray(second[i][j], first, sizesFirst[0], sizesFirst[1]))

					&& (uniqueElementInTwoDimArray(second[i][j], third, sizesThird[0], sizesThird[1])))
				{
					// если элемент уникальный

					if (arrUnique)								// если здесь не nullptr
					{
						arrUnique[sizeUnique] = second[i][j];	// задать значение
					}

					sizeUnique++;								// увеличиваем индекс для следующей итерации
				}
			}
		}

		// проверим на уникальность элементы третьего массива

		for (size_t i = 0; i < sizesThird[0]; i++)
		{
			for (size_t j = 0; j < sizesThird[1]; j++)
			{
				if ((!compareToMatchPreviousOnes(third[i][j], third, i, j, sizesThird[1]))

					&& (uniqueElementInTwoDimArray(third[i][j], first, sizesFirst[0], sizesFirst[1]))

					&& (uniqueElementInTwoDimArray(third[i][j], second, sizesSecond[0], sizesSecond[1])))
				{
					// если элемент уникальный

					if (arrUnique)								// если здесь не nullptr
					{
						arrUnique[sizeUnique] = third[i][j];	// задать значение
					}

					sizeUnique++;								// увеличиваем индекс для следующей итерации
				}
			}
		}

		if (!arrUnique)								// если здесь nullptr
		{
			sizeNewArr = sizeUnique;				// записать подсчитанную длину массива

			arrUnique = new int[sizeUnique] {0};	// создать массив подсчитанной длины
		}
	}

	return arrUnique;
}


//--------------------------------------------------------------------


int* negative						// ФУНКЦИЯ поиска отрицательных значений без повторений в трех двумерных
									//         массивах и создания одномерного массива с найденными значениями
(
	size_t& sizeNewArr,						// ссылка на размер массива отрицательных элементов

	int** first,							// первый массив

	size_t* sizesFirst,						// размеры первого массива

	int** second,							// второй массив

	size_t* sizesSecond,					// размеры второго массива

	int** third,							// третий массив

	size_t* sizesThird						// размеры третьего массива
)
{
	int* arrNegative = nullptr;				// указатель на массив отрицательных элементов

	size_t sizeNegative = 0;				// размер массива отрицательных элементов

	for (size_t k = 0; k < 2; k++)			// цикл режимов работы: 0 - подсчет и создание; 1 - заполнение
	{
		sizeNegative = 0;

		// проверим на отрицательность элементы первого массива

		for (size_t i = 0; i < sizesFirst[0]; i++)
		{
			for (size_t j = 0; j < sizesFirst[1]; j++)
			{
				if ((first[i][j] < 0)
					
					&& (!compareToMatchPreviousOnes(first[i][j], first, i, j, sizesFirst[1])))
				{
					// если элемент отрицательный и уникальный в настоящем массиве

					if (arrNegative)								// если здесь не nullptr
					{
						arrNegative[sizeNegative] = first[i][j];	// задать значение
					}

					sizeNegative++;									// увеличиваем индекс для следующей итерации
				}
			}
		}

		// проверим на отрицательность элементы второго массива

		for (size_t i = 0; i < sizesSecond[0]; i++)
		{
			for (size_t j = 0; j < sizesSecond[1]; j++)
			{
				if ((second[i][j] < 0)

					&& (!compareToMatchPreviousOnes(second[i][j], second, i, j, sizesSecond[1]))
					
					&& (uniqueElementInTwoDimArray(second[i][j], first, sizesFirst[0], sizesFirst[1]))
				)
				{
					// если элемент отрицательный и уникальный в настоящем массиве
					// и не встречается в первом массиве

					if (arrNegative)								// если здесь не nullptr
					{
						arrNegative[sizeNegative] = second[i][j];	// задать значение
					}

					sizeNegative++;									// увеличиваем индекс для следующей итерации
				}
			}
		}

		// проверим на отрицательность элементы третьего массива

		for (size_t i = 0; i < sizesThird[0]; i++)
		{
			for (size_t j = 0; j < sizesThird[1]; j++)
			{
				if ((third[i][j] < 0)

					&& (!compareToMatchPreviousOnes(third[i][j], third, i, j, sizesThird[1]))

					&& (uniqueElementInTwoDimArray(third[i][j], first, sizesFirst[0], sizesFirst[1]))

					&& (uniqueElementInTwoDimArray(third[i][j], second, sizesSecond[0], sizesSecond[1]))
					)
				{
					// если элемент отрицательный и уникальный в настоящем массиве
					// и не встречается в первом массиве
					// и не встречается во втором массиве

					if (arrNegative)								// если здесь не nullptr
					{
						arrNegative[sizeNegative] = third[i][j];	// задать значение
					}

					sizeNegative++;									// увеличиваем индекс для следующей итерации
				}
			}
		}

		if (!arrNegative)								// если здесь nullptr
		{
			sizeNewArr = sizeNegative;					// записать подсчитанную длину массива

			arrNegative = new int[sizeNegative] {0};	// создать массив подсчитанной длины
		}
	}

	return arrNegative;
}


//--------------------------------------------------------------------


int* general					// ФУНКЦИЯ нахождения общих элементов в двух двумерных массивах
(
	size_t& sizeNewArr,						// ссылка на размер массива общих элементов

	int** first,							// первый массив

	size_t* sizesFirst,						// размеры первого массива

	int** second,							// второй массив

	size_t* sizesSecond						// размеры второго массива
)
{
	// Количество общих элементов для нескольких массивов
	// не превышает количества элементов в наименьшем из них.
	// Примем стратегию экономии памяти: сначала посчитаем
	// количество общих элементов и создадим массив общих элементов,
	// а за тем пройдем второй раз и заполним новый массив общими элементами.
	// Отброшенная стратегия - объединить два массива в один, отсортировать,
	// и выбрать те элементы, что будут в двух экземплярах - общие.

	int** min = nullptr;					// указатель на наименьший массив

	size_t* sizesMin = nullptr;				// указатель на массив размеров наименьшего массива

	int** two = nullptr;					// указатель на массив №2

	size_t* sizesTwo = nullptr;				// указатель на массив размеров массива №2

	int* arrGeneral = nullptr;				// указатель на массив общих элементов

	size_t sizeGeneral = 0;					// размер массива общих элементов

	// найдем наименьший массив из заданных

	if (sizesFirst[0] * sizesFirst[1] <= sizesSecond[0] * sizesSecond[1])
	{
		min = first;

		sizesMin = sizesFirst;

		two = second;

		sizesTwo = sizesSecond;
	}
	else
	{
		min = second;

		sizesMin = sizesSecond;

		two = first;

		sizesTwo = sizesFirst;
	}

	// посчитаем количество общих элементов в массивах,
	// создадим одномерный массив общих элементов двух двумерных массивов,
	// заполним созданный массив общими значениями

	for (size_t k = 0; k < 2; k++)			// цикл режимов работы: 0 - подсчет и создание; 1 - заполнение
	{
		sizeGeneral = 0;

		for (size_t i = 0; i < sizesMin[0]; i++)		// два цикла выбора сравниваемого элемента
		{
			for (size_t j = 0; j < sizesMin[1]; j++)
			{
				// проверим новый сравниваемый на общность элемент
				// из массива min на отсутствие совпадений с ранее
				// проверенными в этом же массиве

				if (compareToMatchPreviousOnes(min[i][j], min, i, j, sizesMin[1]))
				{
					continue;	// выход в следующую итерацию если есть совпадение
				}

				for (size_t x = 0; x < sizesTwo[0]; x++)	// два цикла сравнения элементов на общность
				{
					for (size_t y = 0; y < sizesTwo[1]; y++)
					{
						if (two[x][y] == min[i][j])
						{
							// проверим новый сравниваемый на общность элемент
							// из массива two на отсутствие совпадений с ранее
							// проверенными в этом же массиве

							if (compareToMatchPreviousOnes(two[x][y], two, x, y, sizesTwo[1]))
							{
								continue;	// выход в следующую итерацию если есть совпадение
							}

							if (arrGeneral)	// если здесь не nullptr
							{
								arrGeneral[sizeGeneral] = min[i][j];	// задать значение
							}

							sizeGeneral++;	// увеличиваем индекс для следующей итерации
						}
					}
				}
			}
		}

		if (!arrGeneral)							// если здесь nullptr
		{
			sizeNewArr = sizeGeneral;					// записать подсчитанную длину массива

			arrGeneral = new int[sizeGeneral] {0};	// создать массив подсчитанной длины
		}
	}

	return arrGeneral;
}


//--------------------------------------------------------------------


int* general					// ФУНКЦИЯ нахождения общих элементов в одномерном
								//         и двумерном массивах
(
	size_t& sizeNewArr,						// ссылка на размер массива общих элементов

	int* min,								// минимальный одномерный массив

	size_t sizesMin,						// размеры первого массива

	int** two,								// второй двумерный массив

	size_t* sizesTwo						// размеры второго массива
)
{
	// Количество общих элементов для нескольких массивов
	// не превышает количества элементов в наименьшем из них.
	// Примем стратегию экономии памяти: сначала посчитаем
	// количество общих элементов и создадим массив общих элементов,
	// а за тем пройдем второй раз и заполним новый массив общими элементами.
	// Отброшенная стратегия - объединить два массива в один, отсортировать,
	// и выбрать те элементы, что будут в двух экземплярах - общие.

	int* arrGeneral = nullptr;				// указатель на массив общих элементов

	size_t sizeGeneral = 0;					// размер массива общих элементов

	// посчитаем количество общих элементов в массивах,
	// создадим одномерный массив общих элементов двух двумерных массивов,
	// заполним созданный массив общими значениями

	bool outIter = false;					// выход из итерации

	for (size_t k = 0; k < 2; k++)			// цикл режимов работы: 0 - подсчет и создание; 1 - заполнение
	{
		sizeGeneral = 0;

		for (size_t i = 0; i < sizesMin; i++)		// цикл выбора сравниваемого элемента
		{
			// проверим новый сравниваемый на общность элемент
			// из массива min на отсутствие совпадений с ранее
			// проверенными в этом же массиве

			if (compareToMatchPreviousOnes(min[i], min, i))
			{
				continue;	// выход в следующую итерацию если есть совпадение
			}

			for (size_t x = 0; x < sizesTwo[0]; x++)	// два цикла сравнения элементов на общность
			{
				for (size_t y = 0; y < sizesTwo[1]; y++)
				{
					if (two[x][y] == min[i])
					{
						// проверим новый сравниваемый на общность элемент
						// из массива two на отсутствие совпадений с ранее
						// проверенными в этом же массиве

						if (compareToMatchPreviousOnes(two[x][y], two, x, y, sizesTwo[1]))
						{
							continue;	// выход в следующую итерацию если есть совпадение
						}

						if (arrGeneral)	// если здесь не nullptr
						{
							arrGeneral[sizeGeneral] = min[i];	// задать значение
						}

						sizeGeneral++;	// увеличиваем индекс для следующей итерации
					}
				}
			}
		}

		if (!arrGeneral)							// если здесь nullptr
		{
			sizeNewArr = sizeGeneral;				// записать подсчитанную длину массива

			arrGeneral = new int[sizeGeneral] {0};	// создать массив подсчитанной длины
		}
	}

	return arrGeneral;
}


//--------------------------------------------------------------------


bool createAnArray					// ФУНКЦИЯ создания двумерного массива (true-выход из программы)
(
	char name,								// однобуквенное имя массива для сообщения

	int**& twoDimArr,						// указатель на создаваемый двумерный массив

	size_t& row,							// количество строк в создаваемом массиве

	size_t& col								// количество колонок в создаваемом массиве
)
{
	unsigned char byte1char = 0;			// первый байт кода символа / нажатия клавиши

	enum key { BackSpace = 8, Enter = 13, ESC = 27 };		// коды клавиш

	bool firstSymbol = false;				// ввод первого символа

	size_t num = 0;							// вспомогательная переменная

	for (size_t i = 0; i < 2; i++)			// цикл режимов ввода: количество строк или колонок
	{
		firstSymbol = false;

		cout
			<< " Введите количество "
			
			<< (i ? "колонок (4-10)" : "строк (1-3)")
			
			<< " в массиве " << name << ": > ";

		while (true)						// цикл ввода значений
		{
			byte1char = _getch();

			if (_kbhit()) { (void)_getch(); }

			if (byte1char == ESC)
			{
				return true;			
			}

			if ((('0' < byte1char) && (byte1char <= '9'))
				
				|| ((firstSymbol) && (byte1char == '0')))
			{
				firstSymbol = true;

				cout << byte1char;

				if (i)
				{
					col = col * 10 + (byte1char - 48);

					num = col;

					if (col > 10)
					{
						col = 10;

						num = col;

						byte1char = Enter;
					}
				}
				else 
				{
					row = row * 10 + (byte1char - 48);

					num = row;

					if (row > 3)
					{
						row = 3;

						num = row;

						byte1char = Enter;
					}
				}
			}

			if (byte1char == Enter)
			{
				if ((i) && (col < 4))
				{
					col = 4;

					num = col;
				}

				byte1char = 0;

				break;
			}
		}

		cout << "\t" "Принимаем равным " << num << N << endl;
	}

	twoDimArr = new int* [row];					// создали двумерный массив (только уровень строк)

	for (size_t i = 0; i < row; i++)			// окончательное создание двумерного массива
	{
		twoDimArr[i] = new int[col];			// - добавили уровень колонок
	}

	for (size_t i = 0; i < row; i++)			// инициализация массива
	{
		for (size_t j = 0; j < col; j++)
		{
			// - заполнение случайными +/- значениями

			twoDimArr[i][j] = rand() * row * col * 2 / RAND_MAX - (row * col);
		}
	}

	return false;
}


//--------------------------------------------------------------------


void printArray				// ФУНКЦИЯ вывода на экран двумерного массива
(
	int** twoDimArr,						// выводимый на экран двумерный массив

	size_t row,								// количество строк в создаваемом массиве

	size_t col								// количество колонок в создаваемом массиве
)
{
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{
			cout << setw(7) << twoDimArr[i][j];
		}

		cout << N << endl;
	}
}


//--------------------------------------------------------------------


void printArray				// ФУНКЦИЯ вывода на экран одномерного массива
(
	int* oneDimArr,						// выводимый на экран одномерный массив

	size_t sizeArr						// размер одномерного массива
)
{
	for (size_t i = 0; i < sizeArr; i++)
	{
		cout
			<< setw(7) << oneDimArr[i]

			<< (((  (!((i + 1) % 10)) && (i != 0)) || ((i + 1) == sizeArr)) ? (N N) : (""));
	}
}


//--------------------------------------------------------------------


template <typename T>

T** delArray						// ФУНКЦИЯ удаления двумерного массива
(
	T** twoDimArr,							// удаляемый двумерный массив

	size_t row								// количество строк в создаваемом массиве
)
{
	for (size_t i = 0; i < row; i++)
	{
		delete[] twoDimArr[i];				// удаление строк двумерного массива
	}

	delete[] twoDimArr;						// окончательное удаление двумерного массива

	return nullptr;							// возврат нулевого указателя
}


//--------------------------------------------------------------------


template <typename T>

T* delArray							// ФУНКЦИЯ удаления одномерного массива
(
	T* oneDimArr							// удаляемый одномерный массив
)
{
	delete[] oneDimArr;						// удаление одномерного массива

	return nullptr;							// возврат нулевого указателя
}


//--------------------------------------------------------------------


int main()
{
	SetConsoleOutputCP(1251);

	//--------------------------------------------

	//                          Домашнее задание №18

	// Тема: Многомерные динамические массивы

	//                         Встреча №35. Задание 2

	//     Есть 3 двумерных массива A, B, C. Количество строк и столбцов для них
	// вводит пользователь с клавиатуры для каждого из них.
	//     Задание:
	// • Создать одномерный массив, который содержит общие значения для A, B, C.
	// • Создать одномерный массив, который содержит уникальные значения для A, B, C.
	// • Создать одномерный массив, который содержит общие значения для A и C.
	// • Создать одномерный массив, который содержит отрицательные значения для
	//   A, B, C без повторений.

	cout
		<< "                              Домашнее задание №18"

		N N" Тема: Многомерные динамические массивы"

		N N"                             Встреча №35. Задание 2"

		N N"     Есть 3 двумерных массива A, B, C. Количество строк и столбцов для них"
		
		N N" вводит пользователь с клавиатуры для каждого из них."
		
		N N"     Задание:"

		N N" • Создать одномерный массив, который содержит общие значения для A, B, C."
		
		N N" • Создать одномерный массив, который содержит уникальные значения для A, B, C."
		
		N N" • Создать одномерный массив, который содержит общие значения для A и C."
		
		N N" • Создать одномерный массив, который содержит отрицательные значения для"
		
		N N"   A, B, C без повторений."

		N N" ------------------------------------------------------------------------------"

		<< N << endl;

	cout << " [ESC]-выход из программы, [Enter]-ввод числа" << N << endl;

	int** arrayA = nullptr;							// №0 двумерный массив A

	int** arrayB = nullptr;							// №1 двумерный массив B

	int** arrayC = nullptr;							// №2 двумерный массив C

	int* generalABC = nullptr;						// №0 одномерный массив с элементами общими для A, B, C

	int* uniqueABC = nullptr;						// №1 одномерный массив с элементами уникальными для A, B, C

	int* generalAC = nullptr;						// №2 одномерный массив с элементами общими для A и C

	int* negativeABC = nullptr;						// №3 одномерный массив с отрицательными элементами
													// для A, B, C без повторений

	srand((unsigned int)time(0));					// настройка начальных значений для rand()

	(void)rand();									// холостой прогон для получения случайных значений

	(void)rand();									// холостой прогон для получения случайных значений

	// создадим массив значений количества строк и колонок двумерных массивов

	size_t** rowCol = new size_t * [3]{ nullptr };
	
	for (size_t i = 0; i < 3; i++)
	{
		rowCol[i] = new size_t[2]{0};
	}

	// создадим массив значений количества элементов одномерных массивов

	size_t* arrSize = new size_t[4]{};

	// создание и инициализация двумерных массивов A, B, C

	if      (createAnArray('A', arrayA, rowCol[0][0], rowCol[0][1]))
	{
		return 0;													// выход из программы
	}
	else if (createAnArray('B', arrayB, rowCol[1][0], rowCol[1][1]))
	{
		delArray(arrayA, rowCol[0][0]);								// удаление двумерного массива A

		return 0;													// выход из программы
	}
	else if (createAnArray('C', arrayC, rowCol[2][0], rowCol[2][1]))
	{
		delArray(arrayA, rowCol[0][0]);								// удаление двумерного массива A

		delArray(arrayB, rowCol[1][0]);								// удаление двумерного массива B

		return 0;													// выход из программы
	}

	cout << " Создан массив A:" << N << endl;

	printArray(arrayA, rowCol[0][0], rowCol[0][1]);		// вывод на экран двумерного массива A

	cout << " Создан массив B:" << N << endl;

	printArray(arrayB, rowCol[1][0], rowCol[1][1]);		// вывод на экран двумерного массива B

	cout << " Создан массив C:" << N << endl;

	printArray(arrayC, rowCol[2][0], rowCol[2][1]);		// вывод на экран двумерного массива C

	// создадим одномерный массив общих значений для массивов A и C.

	generalAC = general(arrSize[2], arrayA, rowCol[0], arrayC, rowCol[2]);

	// создадим одномерный массив общих значений для массивов A, B, C (для AC и B)

	generalABC = general(arrSize[0], generalAC, arrSize[2], arrayB, rowCol[1]);

	// создадим одномерный массив общих значений для массивов A, B, C (для AC и B)

	uniqueABC = unique(arrSize[1], arrayA, rowCol[0], arrayB, rowCol[1], arrayC, rowCol[2]);

	// создадим одномерный массив отрицательных значений без повторений для массивов A, B, C

	negativeABC = negative(arrSize[3], arrayA, rowCol[0], arrayB, rowCol[1], arrayC, rowCol[2]);

	// вывод на экран одномерного массива общих элементов для массивов A, B, C

	cout
		<< " Создан массив общих для массивов A, B, C элементов длиной "

		<< arrSize[0] << " :" << N << endl;

	printArray(generalABC, arrSize[0]);

	// вывод на экран одномерного массива общих элементов для массивов A и C

	cout
		<< " Создан массив общих для массивов A и C элементов длиной "

		<< arrSize[2] << " :" << N << endl;

	printArray(generalAC, arrSize[2]);

	// вывод на экран одномерного массива уникальных элементов для массивов A, B, C

	cout
		<< " Создан массив уникальных для массивов A, B, C элементов длиной "

		<< arrSize[1] << " :" << N << endl;

	printArray(uniqueABC, arrSize[1]);

	// вывод на экран одномерного массива отрицательных элементов для массивов A, B, C

	cout
		<< " Создан массив отрицательных элементов для массивов A, B, C длиной "

		<< arrSize[3] << " :" << N << endl;

	printArray(negativeABC, arrSize[3]);

	// удаление массивов перед окончанием программы

	arrayA = delArray(arrayA, rowCol[0][0]);	// удаление двумерного массива A

	arrayB = delArray(arrayB, rowCol[1][0]);	// удаление двумерного массива B

	arrayC = delArray(arrayC, rowCol[2][0]);	// удаление двумерного массива C

	rowCol = delArray(rowCol, 3);				// удаление двумерного массива строк и колонок

	generalABC = delArray(generalABC);		// удаление одномерного массива общих элементов массивов A, B, C

	uniqueABC = delArray(uniqueABC);		// удаление одномерного массива уникальных элементов массивов A, B, C

	generalAC = delArray(generalAC);		// удаление одномерного массива общих элементов массивов A, C

	negativeABC = delArray(negativeABC);	// удаление одномерного массива отрицательных элементов массивов A, B, C

	arrSize = delArray(arrSize);			// удаление одномерного массива длин массивов

	//--------------------------------------------

	return 0;
}