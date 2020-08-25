// DZ_ST_C++_07_dz22_vstrecha22_zadanie1_ListExcertions.cpp
#pragma once
#include "DZ_ST_C++_07_dz22_vstrecha22_zadanie1_ListExcertions.h"


// Дружественная ФУНКЦИЯ перегрузки оператора << для вывода сообщения исключения
std::ostream& operator<<(std::ostream& out, const ListExceptions& except) {
    switch (except.exception)
    {
    case EXCEPTIONS::NO_EXCEPTIONS: {
        break;
    }
    case EXCEPTIONS::NULL_POINTER_TO_THE_HEAD_OF_THE_LIST: {
        out << " Ошибка!\n"
            << " Файл " << except.nameFile << "\n"
            << " Строка " << except.lineNumber << ":"
            << " нулевой указатель на голову списка";
        break;
    }
    case EXCEPTIONS::NULL_POINTER_TO_THE_TAIL_OF_THE_LIST: {
        out << " Ошибка!\n"
            << " Файл " << except.nameFile << "\n"
            << " Строка " << except.lineNumber << ":"
            << " нулевой указатель на хвост списка";
        break;
    }
    case EXCEPTIONS::NULL_POINTER_TO_A_LIST_ITEM: {
        out << " Ошибка!\n"
            << " Файл " << except.nameFile << "\n"
            << " Строка " << except.lineNumber << ":"
            << " нулевой указатель на элемент списка";
        break;
    }
    case EXCEPTIONS::THE_POSITION_NUMBER_IN_THE_LIST_IS_ZERO: {
        out << " Ошибка!\n"
            << " Файл " << except.nameFile << "\n"
            << " Строка " << except.lineNumber << ":"
            << " номер позиции в списке равен нулю";
        break;
    }
    case EXCEPTIONS::THE_POSITION_NUMBER_IN_THE_LIST_IS_NEGATIVE: {
        out << " Ошибка!\n"
            << " Файл " << except.nameFile << "\n"
            << " Строка " << except.lineNumber << ":"
            << " номер позиции в списке меньше нуля";
        break;
    }
    case EXCEPTIONS::THE_POSITION_NUMBER_IN_THE_LIST_IS_GREATER_THAN_THE_MAXIMUM: {
        out << " Ошибка!\n"
            << " Файл " << except.nameFile << "\n"
            << " Строка " << except.lineNumber << ":"
            << " номер позиции в списке больше максимального";
        break;
    }
    case EXCEPTIONS::THE_CURRENT_POSITION_IN_THE_LIST_IS_GREATER_THAN_THE_SPECIFIED_ONE: {
        out << " Ошибка!\n"
            << " Файл " << except.nameFile << "\n"
            << " Строка " << except.lineNumber << ":"
            << " текущая позиция в списке больше заданной";
        break;
    }
    case EXCEPTIONS::INVALID_CLASS_INSTANCE_TYPE: {
        out << " Ошибка!\n"
            << " Файл " << except.nameFile << "\n"
            << " Строка " << except.lineNumber << ":"
            << " недопустимый тип экземпляра класса.\n"
            << " Разрешены: short, unsigned short, int, unsigned int,\n"
            << " long, unsigned long, long long, unsigned long long";
        break;
    }
    }
    return out;
}
