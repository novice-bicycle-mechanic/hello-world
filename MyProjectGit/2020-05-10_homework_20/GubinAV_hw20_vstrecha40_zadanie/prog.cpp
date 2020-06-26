// файл prog.cpp
// задание из файла homework 20.pdf
// Тема: Препроцессор
// Встреча №40.
// Задание:
/*
    Создать проект в котором:
    1. Создать три файла: function.h, function.cpp, prog.cpp.
    2. В файле function.cpp необходимо написать следующие функции для работы
с массивом данных:
а) функцию для заполнения массива случайными значениями;
б) функцию для вывода значений массива на консоль;
в) функцию для поиска минимального элемента;
г) функцию для поиска максимального элемента;
д) функцию для сортировки;
е) функцию для редактирования значения массива.
Данные функции необходимо написать для работы с массивом целых, действительных
и символьных значений. Для каждого типа написать отдельную функцию.
    3. В файле function.h нужно:
а) описать прототипы всех функций;
б) сделать проверку определена ли константа, указывающая на тип данных ( #ifdef INTEGER )
в) создать обобщающие имена функции, которым будет определена функция соответствующего
типа в зависимости от константы, указанной в файле prog.cpp (# define show ShowInt ).
    4. В файле prog.cpp нужно:
а) в функции main вызвать все функции через переозначеные (обобщенные) имена из
файла function.h ( show ( ));
б) определить константу, которая указывает какой тип данных будет использоваться.
Например INTEGER - целые данные, CHAR - символьные, DOUBLE - действительные
(#define INTEGER ). Имя функциям нужно давать так, чтобы они отвечали своей сути.
Например, функция для вывода значений массива целых чисел на консоль - ShowArrayInt().
А когда переопределяем функцию с помощью #define, то нужно давать общее имя.
Например, #define ShowArray ShowArrayInt
*/

#include <cstdio>
#include <clocale>

// INTEGER DOUBLE CHAR - константы типов данных для компиляции программы под работу с определенным типом
#define INTEGER
//#define DOUBLE
//#define CHAR

#include "function.h"


// ГЛАВНАЯ ФУНКЦИЯ
int main() {
    setlocale(LC_ALL, "ru");

    size_t length = 30;                             // длина массива

#ifdef INTEGER
#define ARRAY arrayInt
#define LENGT_ROW lengthRowInt
#define TYPE_VALUE "%d"
    int* ARRAY = new int[length] {};                // массив типа int
    size_t LENGT_ROW = 80 / 12;                     // длина строки массива на экране
    const char* typeArray = "int";                  // наименование типа массива
    int editValue = 999'999;                        // новое значение в редактируемом элементе
#endif

#ifdef DOUBLE
#define ARRAY arrayDouble
#define LENGT_ROW lengthRowDouble
#define TYPE_VALUE "%.3f"
    double* ARRAY = new double[length] {};          // массив типа double
    size_t LENGT_ROW = 80 / 16;                     // длина строки массива на экране
    const char* typeArray = "double";               // наименование типа массива
    double editValue = 666.666;                     // новое значение в редактируемом элементе
#endif

#ifdef CHAR
#define ARRAY arrayChar
#define LENGT_ROW lengthRowChar
#define TYPE_VALUE "%c"
    char* ARRAY = new char[length] {};              // массив типа char
    size_t LENGT_ROW = 80 / 2;                      // длина строки массива на экране
    const char* typeArray = "char";                 // наименование типа массива
    char editValue = '#';                           // новое значение в редактируемом элементе
#endif

    printf_s("            Заполнение массива типа %s случайными значениями\n\n", typeArray);
    random(ARRAY, length);
    print(ARRAY, length, LENGT_ROW);

    printf_s(" Минимальное значение в массиве типа %s равно " TYPE_VALUE "\n\n", typeArray, min(ARRAY, length));
    printf_s(" Максимальное значение в массиве типа %s равно " TYPE_VALUE "\n\n", typeArray, max(ARRAY, length));

    printf_s("               Сортировка массива типа %s по возрастанию\n\n", typeArray);
    sortAscend(ARRAY, length);
    print(ARRAY, length, LENGT_ROW);

    printf_s("               Сортировка массива типа %s по убыванию\n\n", typeArray);
    sortDescend(ARRAY, length);
    print(ARRAY, length, LENGT_ROW);

    printf_s("                  Редактирование массива типа %s\n", typeArray);
    printf_s(" (отредактированное значение <" TYPE_VALUE "> в начале, середине и конце массива)\n\n", editValue);
    edit(editValue, 0, ARRAY, length);
    edit(editValue, 15, ARRAY, length);
    edit(editValue, 29, ARRAY, length);
    print(ARRAY, length, LENGT_ROW);

    return 0;
}
