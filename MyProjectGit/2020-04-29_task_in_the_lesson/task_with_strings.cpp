// урок по программированию С++ 2020-04-29
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <clocale>
#include <string.h>

#define N "\n"

using namespace std;


//----------------------------------------------------------------


char* twistWords
(
	const char* str
)
{
	size_t length = strlen(str);					// найдем длину полученной строки

	char* text = new char[(length + 2)]{ '\0' };	// выделим память под новую строку

	char* buf = new char[(length + 2)]{ '\0' };		// выделим память под буферную строку

	size_t prev = 0;

	size_t newI = length;

	size_t counter = 1;

	for (size_t i = 0; i < length; i++)
	{
		if ((str[i] == ' ') || ((i + 1) == length))
		{
			newI = ((i + 1) == length) ? (i + 1) : (i);

			delete[] buf;

			buf = new char[(length + 2)];

			size_t y = 0;

			size_t x = 0;

			counter = 0;

			for (y = prev, x = 0; y < newI; y++, x++)
			{
				counter++;

				buf[x] = str[y];
			}

			buf[x] = '\0';

			if (counter > 5) buf = _strrev(buf);

			text = strcat(text, buf);

			text = strcat(text, " ");

			prev = i + 1;
		}
	}

	delete[] buf;

	return text;
}


//----------------------------------------------------------------


int main()
{
	setlocale(LC_ALL, "ru");

	//--------------------------------

/*
Задача!!!(тема "строки")

написать функцию, аргументом которой будет строка::

Строка содержит только буквы и пробелы,
в начале и конце строки пробелов нет,
пробелы разделяют слова,
между словами может быть только один пробел

char* twistWords(const char* str) {}

функция должна возвращать первоначальную строку,
в которой все слова длиной большей или равной 6-и
буквам должны быть перевёрнуты:

I - "Белеет парус одинокий в тумане моря голубом"
O - "теелеБ парус йиконидо в унамут моря мобулог"

I - "To be or not to be that is the question"
O - "To be or not to be that is the noitseuq"

I - "HelloWorld"
O - "dlroWolleH"

Задача должна быть загружена в Ваш репозиторий на гитхаб.
Заодно и проверим, кто как владеет искусством запушивания репозиториев.

*/

	char textA[] = "Белеет парус одинокий в тумане моря голубом";

	const char* textB = "To be or not to be that is the question";

	const char* textC = "HelloWorld";

	char* textNew = nullptr;

	textNew = twistWords(textA);

	cout << " " << textA << N N << " " << textNew << N << endl;

	delete[] textNew;

	textNew = twistWords(textB);

	cout << " " << textB << N N << " " << textNew << N << endl;

	delete[] textNew;

	textNew = twistWords(textC);

	cout << " " << textC << N N << " " << textNew << N << endl;

	delete[] textNew;

	//--------------------------------

	cout << endl;

	return 0;
}


