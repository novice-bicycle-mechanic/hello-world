// урок по программированию —++ 2020-04-29 - верси€ 3
// c циклами, без пустых строк и с уменьшением строк кода (36 строк)
/*
«адача!!!(тема "строки")

написать функцию, аргументом которой будет строка::

—трока содержит только буквы и пробелы,
в начале и конце строки пробелов нет,
пробелы раздел€ют слова,
между словами может быть только один пробел

char* twistWords(const char* str) {}

функци€ должна возвращать первоначальную строку,
в которой все слова длиной большей или равной 6-и
буквам должны быть перевЄрнуты:

I - "Ѕелеет парус одинокий в тумане мор€ голубом"
O - "теелеЅ парус йиконидо в унамут мор€ мобулог"

I - "To be or not to be that is the question"
O - "To be or not to be that is the noitseuq"

I - "HelloWorld"
O - "dlroWolleH"

«адача должна быть загружена в ¬аш репозиторий на гитхаб.
«аодно и проверим, кто как владеет искусством запушивани€ репозиториев.
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
			if (strlen(buffer) > 5) buffer = _strrev(buffer);  // реверс слова
			text = strcat(text, buffer);  // копируем слово-результат и
			text = strcat(text, ((str[i] != '\0') ? (" ") : ("\0"))); // пробел
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
	const char* text[3] = { "Ѕелеет парус одинокий в тумане мор€ голубом",
		"To be or not to be that is the question","HelloWorld" };
	char* newText = nullptr;
	for (size_t i = 0; i < 3; i++) {
		newText = twistWords(text[i]);
		std::cout << " " << text[i] << "\n\n" << " " << newText << "\n" << std::endl;
		delete[] newText;
	}
	return 0;
}
