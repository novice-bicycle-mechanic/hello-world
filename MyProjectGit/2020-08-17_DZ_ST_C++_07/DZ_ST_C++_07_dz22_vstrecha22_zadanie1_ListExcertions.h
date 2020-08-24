// DZ_ST_C++_07_dz22_vstrecha22_zadanie1_ListExcertions.h
//
// Задание из файла DZ_ST_C++_07.pdf
// Домашнее задание №22
// Встреча №22, задание 1
// Тема: Исключения
/*
Добавьте в класс двусвязного списка механизм обработки исключений.
На ваш выбор генерируйте исключения в случае ошибок.
Например, нехватка памяти, попытка удаления из пустого списка и т.д.
*/

#pragma once
#include <iostream>


// КЛАСС-ПЕРЕЧИСЛЕНИЕ исключений
enum class EXCEPTIONS {
    NO_EXCEPTIONS,                                          // нет исключений (значение инициализации)
    NULL_POINTER_TO_THE_HEAD_OF_THE_LIST,                   // нулевой указатель на голову списка
    NULL_POINTER_TO_THE_TAIL_OF_THE_LIST,                   // нулевой указатель на хвост списка
    NULL_POINTER_TO_A_LIST_ITEM,                            // нулевой указатель на элемент списка
    THE_POSITION_NUMBER_IN_THE_LIST_IS_ZERO,                // номер позиции в списке равен нулю
    THE_POSITION_NUMBER_IN_THE_LIST_IS_NEGATIVE,            // номер позиции в списке отрицательный
    THE_POSITION_NUMBER_IN_THE_LIST_IS_GREATER_THAN_THE_MAXIMUM,   // номер позиции в списке больше максимального
    THE_CURRENT_POSITION_IN_THE_LIST_IS_GREATER_THAN_THE_SPECIFIED_ONE, // текущая позиция в списке больше заданной
    INVALID_CLASS_INSTANCE_TYPE                             // недопустимый тип экземпляра класса
};


// КЛАСС исключений для класса Список
class ListExceptions {
private:
    EXCEPTIONS exception{ EXCEPTIONS::NO_EXCEPTIONS };  // значение исключения
    int lineNumber{ 0 };                                // номер строки генерации исключения
    const char* nameFile;                               // имя файла генерации исключения
public:
    ListExceptions(EXCEPTIONS exception_, int lineNumber_, const char* nameFile_) :
        exception(exception_), lineNumber(lineNumber_), nameFile(nameFile_)
    {}

    friend std::ostream& operator<<(std::ostream& out, const ListExceptions& except);
};


