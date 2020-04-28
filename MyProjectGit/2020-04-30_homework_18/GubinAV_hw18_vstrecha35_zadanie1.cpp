// задание из файла "homework 18.pdf"
	//-----------------------------------------------

	//                          Домашнее задание №18

	// Тема: Многомерные динамические массивы

	//                         Встреча №35. Задание 1

	//     Написать программу, которая дает пользователю ввести 5 фамилий
	// студентов, а затем сортирует их по возрастанию.

#include <iostream>
#include <Windows.h>
#include <conio.h>

#define N "\n"

using namespace std;


//--------------------------------------------------------------------------------------


void delArrays						// ФУНКЦИЯ удаления массивов
(
	char* buffer,							// массив для ввода фамилии

	char** surnames,						// массив-каталог фамилий

	size_t numNames							// количество фамилий в каталоге
)
{
	delete[] buffer;						// удаляем массив ввода фамилии

	for (size_t i = 0; i < numNames; i++)
	{
		delete[] surnames[i];				// удаляем массивы фамилий из массива-каталога
	}

	delete[] surnames;						// удаляем массив-каталог фамилий
}


//--------------------------------------------------------------------------------------


char* saveSurname				// ФУНКЦИЯ сохранения фамилии в каталоге
(
	char* buffer							// массив для ввода фамилии
)
{
	size_t length = 0;						// длина массива под фамилию

	while (true)							// подсчет длины фамилии
	{
		if (buffer[length])					// если текущий символ не равен 0
		{
			length++;						// увеличить длину фамилии на 1
		}
		else								// иначе, если текущий символ равен 0
		{
			break;							// выход из подсчета фамилии
		}
	}

	char* newArray = new char[(length + 1)]{ '\0' };	// создали новый массив под фамилию

	for (size_t i = 0; i < length; i++)
	{
		newArray[i] = buffer[i];

		buffer[i] = '\0';
	}

	return newArray;
}


//--------------------------------------------------------------------------------------


bool enterSurname					// ФУНКЦИЯ ввода фамилии
(
	char* buffer,							// массив для ввода фамилии

	size_t lenBuf,							// длина массива для ввода фамилии

	int number = 0							// номер создаваемой фамилии
)
{
	size_t index = 0;						// индекс массива фамилии

	bool mode = false;						// следующий после ввода фамилии режим работы

	size_t byte1code = 0;					// первый байт кода символа / нажатия клавиши

	enum key{BackSpace = 8, Enter = 13, ESC = 27};		// коды клавиш

	//------------------------------------------------

	// инициализируем функции работы с информацией о текущем буфере экрана консоли

	// для реализации BackSpace

	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);	// Дескриптор буфера экрана консоли

	CONSOLE_SCREEN_BUFFER_INFO conScreenBuf;		// структура с информацией о буфере экрана консоли

	PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo = &conScreenBuf;	// указатель на ...

	COORD dwCursorPosition;						// структура позиции курсора в буфере экрана консоли

	dwCursorPosition.X = 0;						// X - Горизонтальная координата или значение столбца (с 0)

	dwCursorPosition.Y = 0;						// Y - Вертикальная координата или значение строки (с 0)

	SHORT x = 0;								// координата x

	SHORT y = 0;								// координата y

	//------------------------------------------------

	cout << " Введите фамилию";
		
	if (number) { cout << " №" << number; }
	
	cout << " > ";

	while (true)
	{
		byte1code = _getch();

		if (_kbhit()) { (void)_getch(); }

		if (byte1code == ESC)
		{
			mode = false;

			break;
		}
		else if (

			((64 < byte1code) && (byte1code < 91))

			|| ((96 < byte1code) && (byte1code < 123))

			|| ((191 < byte1code) && (byte1code < 256))

			|| (byte1code == 168) || (byte1code == 184))
		{
			buffer[index++] = (char)byte1code;

			cout << (char)byte1code;

			if (index > (lenBuf - 2))
			{
				byte1code = Enter;
			}
			else
			{
				byte1code = 0;
			}
		}

		if (byte1code == Enter)
		{
			mode = true;

			break;
		}
		else if (byte1code == BackSpace)
		{
			if (index)
			{
				buffer[--index] = '\0';

				for (size_t i = 0; i < 2; i++)
				{
					GetConsoleScreenBufferInfo(hConsoleOutput, lpConsoleScreenBufferInfo);	// узнаем координаты

					x = lpConsoleScreenBufferInfo->dwCursorPosition.X;	// считаем координату X

					y = lpConsoleScreenBufferInfo->dwCursorPosition.Y;	// считаем координату Y

					dwCursorPosition.X = --x;		// X - Горизонтальная координата или номер столбца (с 0 вправо)

					dwCursorPosition.Y = y;			// Y - Вертикальная координата или номер строки (с 0 вниз)

					SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition); // перейдем по координатам

					// dwCursorPosition.X и lpConsoleScreenBufferInfo->dwCursorPosition.X
					
					// - dwCursorPosition разные структуры с одинаковыми именами !!! Так получилось.

					if (!i) { cout << " "; }
				}
			}
		}
	}

	buffer[index] = '\0';

	cout << N << endl;

	return mode;
}


//--------------------------------------------------------------------------------------


size_t  rankSymbol			// ФУНКЦИЯ оценки символа для целей сортировки

							// латинские: A-Z, a-z - 1-26 ; русские: А-Я, а-я - 101-133
(
	unsigned char symbol							// оцениваемый символ
)
{
	if ((64 < symbol) && (symbol < 91))				// прописные латинские символы A-Z
	{
		return (symbol - (unsigned char)64);
	}
	else if ((96 < symbol) && (symbol < 123))		// строчные латинские символы a-z
	{
		return (symbol - (unsigned char)96);
	}
	else if ((191 < symbol) && (symbol < 198))		// прописные русские символы А-Е
	{
		return (symbol - (unsigned char)91);
	}
	else if (symbol == 168)							// прописной русский символ Ё
	{
		return (symbol - (unsigned char)61);
	}
	else if ((197 < symbol) && (symbol < 224))		// прописные русские символы Ж-Я
	{
		return (symbol - (unsigned char)90);
	}
	else if ((223 < symbol) && (symbol < 230))		// строчные русские символы а-е
	{
		return (symbol - (unsigned char)123);
	}
	else if (symbol == 184)							// строчный русский символ ё
	{
		return (symbol - (unsigned char)77);
	}
	else if ((229 < symbol) && (symbol < 256))		// строчные русские символы ж-я
	{
		return (symbol - (unsigned char)122);
	}
	else 
	{
		return 0;									// прочие значения
	}
}


//--------------------------------------------------------------------------------------


void printArrays			// ФУНКЦИЯ печати массивов фамилий
(
	char** surnames,				// массив-каталог фамилий

	size_t numNames					// количество фамилий в каталоге
)
{
	for (size_t i = 0; i < numNames; i++)
	{
		cout << " " << (i + 1) << "." << surnames[i] << N << endl;
	}
}


//--------------------------------------------------------------------------------------


void minArray				// ФУНКЦИЯ сравнения и перестановки элементов на минимум
(
	char*& one,						// элемент 1 (должен быть меньше)

	char*& two,						// элемент 2 (должен быть больше)

	size_t index					// индекс char-массива элемента
)
{
	char* buf = nullptr;			// вспомогательный указатель на элемент

	if (rankSymbol(one[index]) > rankSymbol(two[index]))	// если 1 > 2
	{
		buf = one;											// переставить элементы местами

		one = two;

		two = buf;
	}

	// иначе, если элементы равны, и не равны '\0'

	else if ((rankSymbol(one[index]) == rankSymbol(two[index]))
		
		&& (rankSymbol(one[index]) != '\0') && (rankSymbol(two[index]) != '\0'))
	{
		// - вызвать настоящую функцию рекурсивно для сравнения
		//   следующих по порядку символов элементов

		minArray(one, two, ++index);	
	}

	// если 1 < 2 или хоть один равен '\0' - ничего не делать и выйти из функции
}


//--------------------------------------------------------------------------------------


void sortSurnames			// ФУНКЦИЯ сортировки массивов с фамилиями
(
	char** surnames,				// массив-каталог фамилий

	size_t numNames					// количество фамилий в каталоге
)
{
	for (size_t i = 1; i < numNames; i++)
	{
		for (size_t j = 1; j < numNames; j++)
		{
			minArray(surnames[j - 1], surnames[j], 0);
		}
	}
}


//--------------------------------------------------------------------------------------


int main()
{
	SetConsoleCP(1251);

	SetConsoleOutputCP(1251);

	//-----------------------------------------------

	//                          Домашнее задание №18

	// Тема: Многомерные динамические массивы

	//                         Встреча №35. Задание 1

	//     Написать программу, которая дает пользователю ввести 5 фамилий
	// студентов, а затем сортирует их по возрастанию.

	cout
		<< "                         Домашнее задание №18"

		N N" Тема: Многомерные динамические массивы"

		N N"                        Встреча №35. Задание 1"

		N N"     Написать программу, которая дает пользователю ввести 5 фамилий"

		N N" студентов, а затем сортирует их по возрастанию."

		N N" ------------------------------------------------------------------"

		<< N << endl;

	cout
		<< " [ESC]-выход из программы"

		N N" [Enter]-ввод фамилии, [BackSpace]-удалить символ слева"

		<< N << endl;

	size_t lenBuf = 64;								// длина массива для ввода фамилии

	char* buffer = new char[lenBuf]{};				// массив для ввода фамилии

	size_t numNames = 5;							// количество фамилий в каталоге

	char** surnames = new char* [numNames]{};		// массив-каталог фамилий

	for (size_t i = 0; i < numNames; i++)
	{
		if (enterSurname(buffer, lenBuf, (i + 1)))	// если функция ввода фамилии возвратила true
		{
			surnames[i] = saveSurname(buffer);		// переписываем фамилию из массива ввода в подмассив каталога	
		}
		else										// иначе, если функция ввода фамилии возвратила false
		{
			delArrays(buffer, surnames, numNames);	// удаляем созданные ранее массивы

			return 0;								// и выходим из программы
		}
	}

	cout << " Список фамилий до сортировки" << N << endl;

	printArrays(surnames, numNames);				// печатаем список фамилий
	
	sortSurnames(surnames, numNames);				// сортируем массивы

	cout << " Список фамилий после сортировки" << N << endl;

	printArrays(surnames, numNames);				// печатаем список фамилий

	delArrays(buffer, surnames, numNames);			// удаляем созданные массивы перед выходом из программы

	//-----------------------------------------------

	return 0;
}
