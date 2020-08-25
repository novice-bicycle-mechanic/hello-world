// DZ_ST_C++_07_dz22_vstrecha22_zadanie2_IndexExceptions.h
#pragma once
#include <iostream>
#include "DZ_ST_C++_07_dz22_vstrecha22_zadanie2_MainParentException.h"


// КЛАСС-ПЕРЕЧИСЛЕНИЕ кодов исключений индексов
enum class INDEX_EXCEPT {
	NONE,													// ничто - значение для инициализации
	THE_INDEX_VALUE_IS_LESS_THAN_ZERO,						// значение индекса меньше нуля
	THE_INDEX_VALUE_IS_LESS_THAN_THE_SPECIFIED_VALUE,		// значение индекса меньше заданного
	THE_INDEX_VALUE_IS_GREATER_THAN_THE_MAXIMUM,			// значение индекса больше максимального
	THE_INDEX_VALUE_IS_GREATER_THAN_THE_SPECIFIED_VALUE,	// значение индекса больше заданного
};

// КЛАСС собственно исключений индексов
class IndexExcept {
private:
	INDEX_EXCEPT exception{ INDEX_EXCEPT::NONE };         // исключение
public:
	// КОНСТРУКТОР с параметрами
	IndexExcept(INDEX_EXCEPT exception_) : exception(exception_) {}

	// ОБЪЯВЛЕНИЕ дружественной ФУНКЦИИ перегрузки оператора <<
	// для вывода сообщения исключения на экран
	friend std::ostream& operator<<(std::ostream& out, const IndexExcept& indexExcept);
};

// Дружественная ФУНКЦИЯ перегрузки оператора << для вывода сообщения исключения на экран
std::ostream& operator<<(std::ostream& out, const IndexExcept& indexExcept) {
	switch (indexExcept.exception)
	{
	case INDEX_EXCEPT::NONE: {
		out << " Ничто";
		break;
	}
	case INDEX_EXCEPT::THE_INDEX_VALUE_IS_LESS_THAN_ZERO: {
		out << " Значение индекса меньше нуля";
		break;
	}
	case INDEX_EXCEPT::THE_INDEX_VALUE_IS_LESS_THAN_THE_SPECIFIED_VALUE: {
		out << " Значение индекса меньше заданного";
		break;
	}
	case INDEX_EXCEPT::THE_INDEX_VALUE_IS_GREATER_THAN_THE_MAXIMUM: {
		out << " Значение индекса больше максимального";
		break;
	}
	case INDEX_EXCEPT::THE_INDEX_VALUE_IS_GREATER_THAN_THE_SPECIFIED_VALUE: {
		out << " Значение индекса больше заданного";
		break;
	}
	}
	return out;
}

// ДОЧЕРНИЙ КЛАСС исключений индексов с дополнительной информацией
class IndexExceptions : public MainParentException<IndexExcept> {
public:
	// КОНСТРУКТОР дочернего класса с параметрами,
	// вызывает конструктор родительского класса
	IndexExceptions(IndexExcept exception_, int lineNumber_, const char* nameFile_) :
		MainParentException(exception_, lineNumber_, nameFile_)
	{}
};

