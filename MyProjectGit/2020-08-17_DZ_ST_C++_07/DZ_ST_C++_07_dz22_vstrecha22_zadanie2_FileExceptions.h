// DZ_ST_C++_07_dz22_vstrecha22_zadanie2_FileExceptions.h
#pragma once
#include <iostream>
#include "DZ_ST_C++_07_dz22_vstrecha22_zadanie2_MainParentException.h"


// КЛАСС-ПЕРЕЧИСЛЕНИЕ кодов исключений файлов
enum class FILE_EXCEPT {
	NONE,										// ничто - значение для инициализации
	THE_FILE_IS_NOT_CREATED,					// файл не создан
	THE_FILE_IS_NOT_OPEN,						// файл не открыт
	THE_FILE_IS_NOT_CLOSED,						// файл не закрыт
	THE_FILE_IS_NOT_AVAILABLE,					// файл не доступен
	THE_FILE_IS_NOT_READABLE,					// файл не доступен для чтения
	THE_FILE_IS_NOT_WRITABLE,					// файл не доступен для записи
};

// КЛАСС собственно исключений файлов
class FileExcept {
private:
	FILE_EXCEPT exception{ FILE_EXCEPT::NONE };         // исключение
public:
	// КОНСТРУКТОР с параметрами
	FileExcept(FILE_EXCEPT exception_) : exception(exception_) {}

	// ОБЪЯВЛЕНИЕ дружественной ФУНКЦИИ перегрузки оператора <<
	// для вывода сообщения исключения на экран
	friend std::ostream& operator<<(std::ostream& out, const FileExcept& fileExcept);
};

// Дружественная ФУНКЦИЯ перегрузки оператора << для вывода сообщения исключения на экран
std::ostream& operator<<(std::ostream& out, const FileExcept& fileExcept) {
	switch (fileExcept.exception)
	{
	case FILE_EXCEPT::NONE: {
		out << " Ничто";
		break;
	}
	case FILE_EXCEPT::THE_FILE_IS_NOT_CREATED: {
		out << " Файл не создан";
		break;
	}
	case FILE_EXCEPT::THE_FILE_IS_NOT_OPEN: {
		out << " Файл не открыт";
		break;
	}
	case FILE_EXCEPT::THE_FILE_IS_NOT_CLOSED: {
		out << " Файл не закрыт";
		break;
	}
	case FILE_EXCEPT::THE_FILE_IS_NOT_AVAILABLE: {
		out << " Файл не доступен";
		break;
	}
	case FILE_EXCEPT::THE_FILE_IS_NOT_READABLE: {
		out << " Файл не доступен для чтения";
		break;
	}
	case FILE_EXCEPT::THE_FILE_IS_NOT_WRITABLE: {
		out << " Файл не доступен для записи";
		break;
	}
	}
	return out;
}

// ДОЧЕРНИЙ КЛАСС исключений файлов с дополнительной информацией
class FileExceptions : public MainParentException<FileExcept> {
public:
	// КОНСТРУКТОР дочернего класса с параметрами,
	// вызывает конструктор родительского класса
	FileExceptions(FileExcept exception_, int lineNumber_, const char* nameFile_) :
		MainParentException(exception_, lineNumber_, nameFile_)
	{}
};

