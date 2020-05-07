// Реализовать клавиатуру кнопочного телефона для текстового сообщения.
// Для получения на GitHube русского текста в программе
// файл <2020-05-06 lesson-phone-keypad_3.cpp>
// сохранен в блокноте в "UTF-8 со спецификацией"
// 1 - .,!? 1
// 2 - АБВГ ABC 2
// 3 - ДЕЖЗ DEF 3
// 4 - ИЙКЛ GHI 4
// 5 - МНОП JKL 5
// 6 - РСТУ MNO 6
// 7 - ФХЦЧ PQRS 7
// 8 - ШЩЪЫ TUV 8
// 9 - ЬЭЮЯ WXYZ 9
// 0 - ' ' 0
// *
// #

#include <iostream>
#include <clocale>
#include <Windows.h>
#include <conio.h>
#define N "\n"
using namespace std;

// функция вывода заголовка экрана - вида клавиатуры телефона
void header(void)
{
	system("cls");

	cout <<
		N "\t" "ВЫХОД   ВВОД  ОТМЕНА"
		N "\t" " ESC   Enter    BS"
		N
		N "\t" "  1      2      3"
		N "\t" " .,!?   АБВГ   ДЕЖЗ"
		N "\t" "        ABC    DEF"
		N
		N "\t" "  4      5      6"
		N "\t" " ИЙКЛ   МНОП   РСТУ"
		N "\t" " GHI    JKL    MNO"
		N
		N "\t" "  7      8      9"
		N "\t" " ФХЦЧ   ШЩЪЫ   ЬЭЮЯ"
		N "\t" " PQRS   TUV    WXYZ"
		N
		N "\t" "  *      0      #"
		N "\t" "        '_'"
		<< N << endl;
}

int main()
{
	setlocale(LC_ALL, "");

	unsigned char byte1char = '\0';					// код символа первоначальный
	unsigned char byte2char = '\0';					// код символа следующего
	enum keys { BS = 8, Enter = 13, ESC = 27 };		// коды нажатий клавиш
	unsigned int timeCode = 0;						// текущее количество временной задержки
	unsigned int delay = 8;							// общее количество задержки времени
	char str[256]{ '\0' };							// строка сообщения
	size_t idx = 0;									// индекс строки сообщения
	size_t indexS = 0;								// индекс набора символов у клавиши
	size_t indexMax = 0;							// максимальный индекс в наборе символов у клавиши
	size_t numKey = 0;								// номер клавиши
	char key[12][10]{								// наборы символов у клавиш
		{' ','0','\0','\0','\0','\0','\0','\0','\0','\0'},		// 0
		{'.',',','!','?','1','\0','\0','\0','\0','\0'},			// 1
		{'А','Б','В','Г','A','B','C','2','\0','\0'},			// 2
		{'Д','Е','Ж','З','D','E','F','3','\0','\0'},			// 3
		{'И','Й','К','Л','G','H','I','4','\0','\0'},			// 4
		{'М','Н','О','П','J','K','L','5','\0','\0'},			// 5
		{'Р','С','Т','У','M','N','O','6','\0','\0'},			// 6
		{'Ф','Х','Ц','Ч','P','Q','R','S','7','\0'},				// 7
		{'Ш','Щ','Ъ','Ы','T','U','V','8','\0','\0'},			// 8
		{'Ь','Э','Ю','Я','W','X','Y','Z','9','\0'},				// 9
		{'*','\0','\0','\0','\0','\0','\0','\0','\0','\0'},		// * (10)
		{'#','\0','\0','\0','\0','\0','\0','\0','\0','\0'}		// # (11)
	};

	header();

	do
	{
		byte1char = _getch();
		if (_kbhit()) (void)_getch();

		if (byte1char == ESC) break;						// если нажато ESC - выход из программы

		if ((('0' <= byte1char) && (byte1char <= '9'))		// если нажата клавиша клавиатуры телефона
			|| (byte1char == '*') || (byte1char == '#'))
		{
			if (byte1char != byte2char)						// если это нажатие для следующего символа
			{
				indexS = 0;

				switch (byte1char)							// задаем параметры нажатия
				{
				case '0': numKey = 0; indexMax = 1; break;
				case '1': numKey = 1; indexMax = 4; break;
				case '2': numKey = 2; indexMax = 7; break;
				case '3': numKey = 3; indexMax = 7; break;
				case '4': numKey = 4; indexMax = 7; break;
				case '5': numKey = 5; indexMax = 7; break;
				case '6': numKey = 6; indexMax = 7; break;
				case '7': numKey = 7; indexMax = 8; break;
				case '8': numKey = 8; indexMax = 7; break;
				case '9': numKey = 9; indexMax = 8; break;
				case '*': numKey = 10; indexMax = 0; break;
				case '#': numKey = 11; indexMax = 0; break;
				}
				byte2char = byte1char;
			}

			cout << key[numKey][indexS];	// вывод первого символа из набора для нажатой клавиши
			cout << "\x1b[D";				// смещаем курсор под последний введенный символ

			while (true)
			{
				if (_kbhit() && (timeCode <= delay))		// если есть быстрое нажатие
				{
					indexS++;		// задаем индекс следующего символа из набора у клавиши
					if (indexS > indexMax) indexS = 0;

					cout << key[numKey][indexS];	// выводим заданный следующий символ
					cout << "\x1b[D";				// смещаем курсор под последний введенный символ

					timeCode = 0;
					break;
				}
				else if (timeCode > delay)					// если нажатия долго не было
				{
					str[idx++] = key[numKey][indexS];		// вводим последний заданный символ в строку сообщения
					cout << key[numKey][indexS];			// выводим / обновляем последний заданный символ

					byte2char = '\0';
					indexS = 0;
					timeCode = 0;
					break;
				}
				else if (!_kbhit())		// если быстрого нажатия не было
				{
					timeCode++;			// увеличиваем код задержки
				}

				Sleep(100);				// задержка времени 0,1 сек.
			}
		}

		if (byte1char == Enter)			// если нажато Enter - ввод и отправка сообщения
		{
			header();										// обновляем экран
			cout << " ОТПРАВЛЕНО: " << str << N << endl;	// вывод отправленного сообщения

			byte2char = '\0';
			indexS = 0;
			timeCode = 0;
			idx = 0;
			for (size_t i = 0; i < 256; i++) str[i] = '\0';		// очищаем строку сообщения
		}

		if (byte1char == BS)				// если нажато BackSpace - отмена последнего символа
		{
			if (idx) str[--idx] = '\0';		// вводим "пусто" в позицию последнего символа строки
			header();						// обновляем экран
			cout << str;					// выводим укороченную на 1 символ строку
		}
		
	} while (true);

	return 0;
}

