// ���� �� ���������������� �++ 2020-04-29
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
	size_t length = strlen(str);					// ������ ����� ���������� ������

	char* text = new char[(length + 2)]{ '\0' };	// ������� ������ ��� ����� ������

	char* buf = new char[(length + 2)]{ '\0' };		// ������� ������ ��� �������� ������

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
������!!!(���� "������")

�������� �������, ���������� ������� ����� ������::

������ �������� ������ ����� � �������,
� ������ � ����� ������ �������� ���,
������� ��������� �����,
����� ������� ����� ���� ������ ���� ������

char* twistWords(const char* str) {}

������� ������ ���������� �������������� ������,
� ������� ��� ����� ������ ������� ��� ������ 6-�
������ ������ ���� ����������:

I - "������ ����� �������� � ������ ���� �������"
O - "������ ����� �������� � ������ ���� �������"

I - "To be or not to be that is the question"
O - "To be or not to be that is the noitseuq"

I - "HelloWorld"
O - "dlroWolleH"

������ ������ ���� ��������� � ��� ����������� �� ������.
������ � ��������, ��� ��� ������� ���������� ����������� ������������.

*/

	char textA[] = "������ ����� �������� � ������ ���� �������";

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


