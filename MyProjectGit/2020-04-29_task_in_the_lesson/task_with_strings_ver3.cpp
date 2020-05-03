// ���� �� ���������������� �++ 2020-04-29 - ������ 3
// c �������, ��� ������ ����� � � ����������� ����� ���� (36 �����)
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
#include <cstring>

char* twistWords(const char* str) {
	size_t length = strlen(str);
	char* text = new char[length + 1]{ '\0' };
	char* buffer = new char[length + 1]{ '\0' };
	for (size_t i = 0, j = 0; i <= length; i++)	{
		if ((str[i] == ' ') || (str[i] == '\0')) {
			buffer[j] = '\0';
			if (strlen(buffer) > 5) buffer = _strrev(buffer);  // ������ �����
			text = strcat(text, buffer);  // �������� �����-��������� �
			text = strcat(text, ((str[i] != '\0') ? (" ") : ("\0"))); // ������
			if (str[i] == '\0') { 
				delete[] buffer;				
				return text;
			}
			j = 0;
		}
		else buffer[j++] = str[i];
	}
	return nullptr;
}

int main() {
	setlocale(LC_ALL, "");
	const char* text[3] = { "������ ����� �������� � ������ ���� �������",
		"To be or not to be that is the question","HelloWorld" };
	char* newText = nullptr;
	for (size_t i = 0; i < 3; i++) {
		newText = twistWords(text[i]);
		std::cout << " " << text[i] << "\n\n" << " " << newText << "\n" << std::endl;
		delete[] newText;
	}
	return 0;
}
