// DZ_ST_C++_07_dz22_vstrecha22_zadanie2_MainParentException.h
#pragma once
#include <iostream>


// Главный Родительский КЛАСС-ШАБЛОН Исключений
template <typename T>
class MainParentException {
private:
	T exception;                      // исключение
	int lineNumber{ 0 };              // номер строки генерации исключения
	const char* nameFile;             // имя файла генерации исключения
public:
	// КОНСТРУКТОР с параметрами
	MainParentException(T exception_, int lineNumber_, const char* nameFile_) :
		exception(exception_), lineNumber(lineNumber_), nameFile(nameFile_)
	{}

	// МЕТОД перегрузки оператора << для вывода на экран
	// сообщения исключения с дополнительной информацией
	friend std::ostream& operator<<(std::ostream& out, const MainParentException<T>& except) {
		out << " Ошибка!\n"
			<< " Файл " << except.nameFile << "\n"
			<< " Строка " << except.lineNumber << ": "
			<< except.exception
			;
		return out;
	}

};

