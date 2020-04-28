// задание из файла "homework 16.pdf"
//----------------------------------------------------------------------------------
	//                        Домашнее задание №16
	// Тема: Строки
	//                        Встреча №31. Задание

	//     Дополните свою библиотеку функций реализациями нижеследующих функций:

	// int mystrcmp(const char* str1, const char* str2); - функция сравнивает две строки, и, если
	// строки равны возвращает 0, если первая строка больше второй, то возвращает 1, иначе - 1.

	// int StringToNumber(char* str); - функция конвертирует строку в число и возвращает это число.

	// char* NumberToString(int  number); - функция конвертирует число в строку и возвращает
	// указатель на эту строку.

	// char* Uppercase(char* str); - функция преобразует строку в верхний регистр.

	// char* Lowercase(char* str); - функция преобразует строку в нижний регистр.

	// char* mystrrev(char* str); - функция реверсирует строку и возвращает указатель на новую строку.
//----------------------------------------------------------------------------------

#include <iostream>
#include <Windows.h>

#define N "\n"
#define NN "\n\n"
#define nel "\n" << endl

using namespace std;


//--------------------------------------------------------------------------------


size_t lenStr						// ФУНКЦИЯ измерения длины строки
(
	const char* str							// измеряемая строка
)
{
	size_t len = 0;							// длина строки

	while (true) if (!str[len++]) return --len;
}


//--------------------------------------------------------------------------------


int mystrcmp						// ФУНКЦИЯ сравнения длин строк
(
	const char* str1,						// строка 1

	const char* str2						// строка 2
)
{
	if (lenStr(str1) > lenStr(str2)) return 1;

	else if (lenStr(str1) < lenStr(str2)) return -1;

	else return 0;
}


//--------------------------------------------------------------------------------


void visualMyStringCompare			// ФУНКЦИЯ визуализации работы функции mystrcmp()
(
	const char* str1,						// строка 1

	const char* str2						// строка 2
)
{
	int estimation = mystrcmp(str1, str2);

	cout
		<< " Заданы две строки:"
		
		N " \"" << str1 << "\"" " и \"" << str2 << "\"" << endl;

	cout
		<< " Длина строки \"" << str1 << "\""

		N << ((estimation)
			
			? ((estimation == 1)?(" больше длины"):(" меньше длины"))
			
			: (" равна длине"))

		<< " строки \""	<< str2 << "\""

		<< nel;
}


//--------------------------------------------------------------------------------


int StringToNumber					// ФУНКЦИЯ конвертации строки в число
(
	char* str								// конвертируемая строка
)
{
	int number = 0;							// число конвертированное из строки

	size_t len = 0;							// индекс массива строки

	while (true)
	{
		if (str[len])
		{
			number = number * 10 + (str[len] - '0');
		}
		else 
		{
			return number;
		}

		len++;
	}
}


//--------------------------------------------------------------------------------


char* mystrrev						// ФУНКЦИЯ реверсирования строки
(
	char* str								// реверсируемая строка
)
{
	size_t length = lenStr(str);					// длина строки str

	char* rts = new char[(length + 1)]{ '\0' };		// создадим массив под реверсированную строку

	// перепишем в обратном порядке строку str в строку rts

	for (size_t i = 0; i < length; i++)	rts[i] = str[(length - 1 - i)];

	return rts;										// возврат указателя на реверсированную строку
}


//--------------------------------------------------------------------------------


char* NumberToString				// ФУНКЦИЯ конвертации числа в строку
(
	int  number								// конвертируемое число
)
{
	char* digits = new char[12]{};

	size_t len = 0;

	while (number)
	{
		digits[len++] = (number % 10) + '0';

		number /= 10;
	}

	char* stigid = mystrrev(digits);

	delete[] digits;

	return stigid;
}


//--------------------------------------------------------------------------------


char charCaseLowerToUpperAndBackRu	// ФУНКЦИЯ перевода символа из нижнего регистра в верхний и наоборот
(
	char symbol,						// конвертируемый символ

	bool trend,							// направление конвертации: true/false - нижний->верхний / верхний->нижний

	unsigned int numCP					// номер кодовой страницы для символов русского языка
)
{
	if ((!trend) && (64 < symbol) && (symbol < 91))  return (symbol + 32);

	else if ((trend) && (96 < symbol) && (symbol < 123)) return (symbol - 32);

	else if ((!trend) && (numCP == 1251) && ((191 - 256) < symbol) && (symbol < (224 - 256))) return (symbol + 32);

	else if ((trend) && (numCP == 1251) && ((223 - 256) < symbol) && (symbol < (256 - 256))) return (symbol - 32);

	else if ((!trend) && (numCP == 1251) && (symbol == (168 - 256))) return (symbol + 16);

	else if ((trend) && (numCP == 1251) && (symbol == (184 - 256))) return (symbol - 16);

	else if ((!trend) && (numCP == 866) && ((127 - 256) < symbol) && (symbol < (160 - 256))) return (symbol + 32);

	else if ((trend) && (numCP == 866) && ((159 - 256) < symbol) && (symbol < (176 - 256))) return (symbol - 32);

	else if ((trend) && (numCP == 866) && ((223 - 256) < symbol) && (symbol < (240 - 256))) return (symbol - 80);

	else if ((!trend) && (numCP == 866) && (symbol == (240 - 256))) return (symbol + 1);

	else if ((trend) && (numCP == 866) && (symbol == (241 - 256))) return (symbol - 1);

	else return symbol;
}


//--------------------------------------------------------------------------------


char* UpperCase						// ФУНКЦИЯ для преобразования строки в верхний регистр
(
	char* str								// преобразуемая строка
)
{
	size_t length = lenStr(str);

	char* STR = new char[(length + 1)]{ '\0' };

	for (size_t i = 0; i < length; i++)
	{
		STR[i] = charCaseLowerToUpperAndBackRu(str[i], true, GetConsoleOutputCP());
	}

	return STR;
}


//--------------------------------------------------------------------------------


char* LowerCase						// ФУНКЦИЯ для преобразования строки в нижний регистр
(
	char* STR								// преобразуемая строка
)
{
	size_t length = lenStr(STR);

	char* str = new char[(length + 1)]{ '\0' };

	for (size_t i = 0; i < length; i++)
	{
		str[i] = charCaseLowerToUpperAndBackRu(STR[i], false, GetConsoleOutputCP());
	}

	return str;
}


//--------------------------------------------------------------------------------


int main()
{
	SetConsoleOutputCP(1251);

	//----------------------------------

	cout
		<< "                       Домашнее задание №16"

		NN " Тема: Строки"

		NN "                       Встреча №31. Задание"

		NN "     Дополните свою библиотеку функций реализациями нижеследующих функций:"

		NN " int mystrcmp(const  char*  str1,  const  char*  str2); - функция сравнивает две"

		N  " строки, и, если  строки  равны  возвращает 0, если первая строка больше второй,"

		N  " то возвращает 1, иначе - 1."

		NN " int StringToNumber(char* str);-функция конвертирует строку в число и возвращает"

		N  " это число."

		NN " char* NumberToString(int  number); - функция  конвертирует  число  в  строку  и"

		N  " возвращает указатель на эту строку."

		NN " char* UpperCase(char* str); - функция  преобразует  строку  в  верхний регистр."

		NN " char* LowerCase(char* str); - функция  преобразует  строку  в  нижний  регистр."

		NN " char* mystrrev(char* str); - функция реверсирует строку и возвращает  указатель"

		N  " на новую строку."

		N  " -------------------------------------------------------------------------------"

		<< endl;

	cout << " Применение функции { int mystrcmp(const char* str1, const char* str2); }" << nel;

	const char* str1 = "Казнить, нельзя помиловать";

	const char* str2 = "Казнить нельзя, помиловать";

	visualMyStringCompare(str1, str2);

	const char* str3 = "Счастье есть";

	const char* str4 = "Оно не может не есть";

	visualMyStringCompare(str3, str4);

	const char* str5 = "Мы живем в мире, которым управляет вера";

	const char* str6 = "Во что поверите, то и сработает";

	visualMyStringCompare(str5, str6);

	cout << " -------------------------------------------------------------------------------" << endl;

	cout << " Применение функции { int StringToNumber(char* str); }" << nel;

	char digits1[] =  "1234567890";					// строка "число"

	int number1 = StringToNumber(digits1);			// число конвертированное из строки

	cout << " Задана строка \"" << digits1 << "\"" << endl;

	cout
		<< " Конвертируем строку " << "(" << typeid(digits1).name() << ")\"" << digits1 << "\""
		
		<< " в число " << "(" << typeid(number1).name() << ")" << number1
		
		<< endl;

	cout << " -------------------------------------------------------------------------------" << endl;

	cout << " Применение функции { char* NumberToString(int  number); }" << nel;

	int number2 = 1234567890;						// число

	char* digits2 = NumberToString(number2);		// строка конвертированная из числа

	cout << " Задано число " << number2 << endl;

	cout
		<< " Конвертируем число " << "(" << typeid(number2).name() << ")" << number2

		<< " в строку " << "(" << typeid(digits2).name() << ")\"" << digits2 << "\""

		<< endl;

	cout << " -------------------------------------------------------------------------------" << endl;

	cout << " Применение функции { char* UpperCase(char* str); }" << nel;

	// создадим строку для преобразования в верхний регистр

	char strLower1[] = "\"abcdefghijkimnopqrstuvwxyz абвгдеёжзийклмнопрстуфхцчшщъыьэюя\"";

	// создадим преобразованную в верхний регистр строку

	char* strUpper1 = UpperCase(strLower1);

	cout << " Задана строка: " N " " << strLower1 << nel;

	cout << " Преобразуем её в верхний регистр: " N " " << strUpper1 << endl;

	cout << " -------------------------------------------------------------------------------" << endl;

	cout << " Применение функции { char* LowerCase(char* str); }" << nel;

	// создадим строку для преобразования в нижний регистр

	char strUpper2[] = "\"ABCDEFGHIJKLMNOPQRSTUVWXYZ АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ\"";

	// создадим преобразованную в нижний регистр строку

	char* strLower2 = LowerCase(strUpper2);

	cout << " Задана строка: " N " " << strUpper2 << nel;

	cout << " Преобразуем её в нижний регистр: " N " " << strLower2 << endl;

	cout << " -------------------------------------------------------------------------------" << endl;

	cout << " Применение функции { char* mystrrev(char* str); }" << nel;

	// создадим строку, которую будем реверсировать

	char str[] = "0123456789 abcdefghijkimnopqrstuvwxyz абвгдеёжзийклмнопрстуфхцчшщъыьэюя";

	// реверсируем строку

	char* rts = mystrrev(str);

	cout << " Задана строка: " N " " << str << nel;

	cout << " Реверсируем её: " N " " << rts << endl;

	cout << " -------------------------------------------------------------------------------" << endl;

	//----------------------------------

	return 0;
}
