// DZ_ST_C++_07_dz22_vstrecha22_zadanie2_MemoryExceptions.h
#pragma once
#include <iostream>
#include "DZ_ST_C++_07_dz22_vstrecha22_zadanie2_MainParentException.h"


// КЛАСС-ПЕРЕЧИСЛЕНИЕ кодов исключений памяти
enum class MEMORY_EXCEPT {
	NONE,													// ничто - значение для инициализации
	NOT_ENOUGH_STACK_MEMORY,								// недостаточно стековой памяти
	NOT_ENOUGH_DYNAMIC_MEMORY,								// недостаточно динамической памяти
	DYNAMIC_MEMORY_IS_NOT_ALLOCATED,						// динамическая память не выделена
	THE_ALLOCATED_DYNAMIC_MEMORY_WAS_NOT_DELETED,			// выделенная динамическая память не удалена
};

// КЛАСС собственно исключений памяти
class MemoryExcept {
private:
	MEMORY_EXCEPT exception{ MEMORY_EXCEPT::NONE };         // исключение
public:
	// КОНСТРУКТОР с параметрами
	MemoryExcept(MEMORY_EXCEPT exception_) : exception(exception_) {}

	// ОБЪЯВЛЕНИЕ дружественной ФУНКЦИИ перегрузки оператора <<
	// для вывода сообщения исключения на экран
	friend std::ostream& operator<<(std::ostream& out, const MemoryExcept& memoryExcept);
};

// Дружественная ФУНКЦИЯ перегрузки оператора << для вывода сообщения исключения на экран
std::ostream& operator<<(std::ostream& out, const MemoryExcept& memoryExcept) {
	switch (memoryExcept.exception)
	{
	case MEMORY_EXCEPT::NONE: {
		out << " Ничто";
		break;
	}
	case MEMORY_EXCEPT::NOT_ENOUGH_STACK_MEMORY: {
		out << " Недостаточно стековой памяти";
		break;
	}
	case MEMORY_EXCEPT::NOT_ENOUGH_DYNAMIC_MEMORY: {
		out << " Недостаточно динамической памяти";
		break;
	}
	case MEMORY_EXCEPT::DYNAMIC_MEMORY_IS_NOT_ALLOCATED: {
		out << " Динамическая память не выделена";
		break;
	}
	case MEMORY_EXCEPT::THE_ALLOCATED_DYNAMIC_MEMORY_WAS_NOT_DELETED: {
		out << " Выделенная динамическая память не удалена";
		break;
	}
	}
	return out;
}

// ДОЧЕРНИЙ КЛАСС исключений памяти с дополнительной информацией
class MemoryExceptions : public MainParentException<MemoryExcept> {
public:
	// КОНСТРУКТОР дочернего класса с параметрами,
	// вызывает конструктор родительского класса
	MemoryExceptions(MemoryExcept exception_, int lineNumber_, const char* nameFile_) :
		MainParentException(exception_, lineNumber_, nameFile_)
	{}
};

