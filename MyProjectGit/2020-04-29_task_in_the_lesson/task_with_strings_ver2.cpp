// урок по программированию —++ 2020-04-29 - верси€ 2
// без пустых строк и с уменьшением строк кода (54 строк)
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
#include <string.h>

char* RecursiveHandlerForTheLine(char* str) {
	char* text = new char[strlen(str) + 1]{ '\0' };  // возвращаема€ строка
	char* firstWord = new char[strlen(str) + 1]{ '\0' }; // буфер первого слова
	firstWord = strncat(firstWord, str, strcspn(str, " "));  // копируем слово
	if (strlen(firstWord) > 5) firstWord = _strrev(firstWord);  // реверс слова
	text = strcat(text, firstWord);  // копируем результат
	delete[] firstWord;  // удал€ем буфер первого слова
	char* nextWords = strchr(str, ' '); // буфер продолжени€ строки
	// продолжение строки после слова: >0-пробел в начале или 0-нет пробелов
	if (nextWords) {
		nextWords = _strrev(nextWords); // реверсируем строку, пробел -> в конец
		// буфер под продолжение строки без пробела
		char* buffer = new char[strlen(str) + 1]{ '\0' };
		// копируем в новый буфер продолжение строки без пробела в конце
		buffer = strncat(buffer, nextWords, (strlen(nextWords) - 1));
		buffer = _strrev(buffer);  // реверсируем строку обратно
		buffer = RecursiveHandlerForTheLine(buffer);  // обработка дальше...
		text = strcat(text, " ");  // добавл€ем в строку пробел после слова
		text = strcat(text, buffer); // добавл€ем полученный результат
		delete[] buffer;  // удал€ем последний буфер
		delete[] str;  // удал€ем исходную дл€ этой функции строку
		return text;  // возврат строки-результата
	}
	else {
		delete[] str;  // удал€ем исходную дл€ этой функции строку
		return text;  // возврат строки-результата
	}
}

char* twistWords(const char* str) {  // конвертаци€ const char* в char*
	char* Str = new char[strlen(str) + 1]{ '\0' };
	return RecursiveHandlerForTheLine(strcat(Str, str));
}

int main() {
	setlocale(LC_ALL, "");
	char* newText = nullptr;
	const char* textA = "Ѕелеет парус одинокий в тумане мор€ голубом";
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
