// DZ_ST_C++_07_dz22_vstrecha22_zadanie2_MathExceptions.h
#pragma once
#include <iostream>
#include "DZ_ST_C++_07_dz22_vstrecha22_zadanie2_MainParentException.h"


// КЛАСС-ПЕРЕЧИСЛЕНИЕ кодов математических исключений
enum class MATH_EXCEPT {
	NONE,										// ничто - значение для инициализации
	INVALID_ARGUMENT_TYPE,						// несоответствующий тип аргумента
	DIVISION_BY_ZERO,							// деление на ноль
	THE_SQUARE_ROOT_OF_A_NEGATIVE_NUMBER,		// квадратный корень из отрицательного числа
};

// КЛАСС собственно математических исключений
class MathExcept {
private:
	MATH_EXCEPT exception{ MATH_EXCEPT::NONE };         // исключение
public:
	// КОНСТРУКТОР с параметрами
	MathExcept(MATH_EXCEPT exception_) : exception(exception_) {}

	// ОБЪЯВЛЕНИЕ дружественной ФУНКЦИИ перегрузки оператора <<
	// для вывода сообщения исключения на экран
	friend std::ostream& operator<<(std::ostream& out, const MathExcept& mathExcept);
};

// Дружественная ФУНКЦИЯ перегрузки оператора << для вывода сообщения исключения на экран
std::ostream& operator<<(std::ostream& out, const MathExcept& mathExcept) {
	switch (mathExcept.exception)
	{
	case MATH_EXCEPT::NONE:	{
		out << " Ничто";
		break;
	}
	case MATH_EXCEPT::INVALID_ARGUMENT_TYPE: {
		out << " Несоответствующий тип аргумента";
		break;
	}
	case MATH_EXCEPT::DIVISION_BY_ZERO:	{
		out << " Деление на ноль";
		break;
	}
	case MATH_EXCEPT::THE_SQUARE_ROOT_OF_A_NEGATIVE_NUMBER:	{
		out << " Квадратный корень из отрицательного числа";
		break;
	}
	}
	return out;
}

// ДОЧЕРНИЙ КЛАСС математических исключений с дополнительной информацией
class MathExceptions : public MainParentException<MathExcept> {
public:
	// КОНСТРУКТОР дочернего класса с параметрами,
	// вызывает конструктор родительского класса
	MathExceptions(MathExcept exception_, int lineNumber_, const char* nameFile_) :
		MainParentException(exception_, lineNumber_, nameFile_)
	{}
};

