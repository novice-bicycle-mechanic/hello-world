// ���� �� ���������������� �++ 2020-04-29 - ������ 2
// ��� ������ ����� � � ����������� ����� ���� (54 �����)
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
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>

char* RecursiveHandlerForTheLine(char* str) {
	char* text = new char[strlen(str) + 1]{ '\0' };  // ������������ ������
	char* firstWord = new char[strlen(str) + 1]{ '\0' }; // ����� ������� �����
	firstWord = strncat(firstWord, str, strcspn(str, " "));  // �������� �����
	if (strlen(firstWord) > 5) firstWord = _strrev(firstWord);  // ������ �����
	text = strcat(text, firstWord);  // �������� ���������
	delete[] firstWord;  // ������� ����� ������� �����
	char* nextWords = strchr(str, ' '); // ����� ����������� ������
	// ����������� ������ ����� �����: >0-������ � ������ ��� 0-��� ��������
	if (nextWords) {
		nextWords = _strrev(nextWords); // ����������� ������, ������ -> � �����
		// ����� ��� ����������� ������ ��� �������
		char* buffer = new char[strlen(str) + 1]{ '\0' };
		// �������� � ����� ����� ����������� ������ ��� ������� � �����
		buffer = strncat(buffer, nextWords, (strlen(nextWords) - 1));
		buffer = _strrev(buffer);  // ����������� ������ �������
		buffer = RecursiveHandlerForTheLine(buffer);  // ��������� ������...
		text = strcat(text, " ");  // ��������� � ������ ������ ����� �����
		text = strcat(text, buffer); // ��������� ���������� ���������
		delete[] buffer;  // ������� ��������� �����
		delete[] str;  // ������� �������� ��� ���� ������� ������
		return text;  // ������� ������-����������
	}
	else {
		delete[] str;  // ������� �������� ��� ���� ������� ������
		return text;  // ������� ������-����������
	}
}

char* twistWords(const char* str) {  // ����������� const char* � char*
	char* Str = new char[strlen(str) + 1]{ '\0' };
	return RecursiveHandlerForTheLine(strcat(Str, str));
}

int main() {
	setlocale(LC_ALL, "");
	char* newText = nullptr;
	const char* textA = "������ ����� �������� � ������ ���� �������";
	const char* textB = "To be or not to be that is the question";
	const char* textC = "HelloWorld";
	newText = twistWords(textA);
	std::cout << " " << textA << "\n\n" << " " << newText << "\n" << std::endl;
    delete[] newText;
	newText = twistWords(textB);
	std::cout << " " << textB << "\n\n" << " " << newText << "\n" << std::endl;
	delete[] newText;
	newText = twistWords(textC);
	std::cout << " " << textC << "\n\n" << " " << newText << "\n" << std::endl;
	delete[] newText;
	return 0;
}
