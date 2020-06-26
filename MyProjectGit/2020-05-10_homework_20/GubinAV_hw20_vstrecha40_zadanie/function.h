// файл function.h
// задание из файла homework 20.pdf
// “ема: ѕрепроцессор
// ¬стреча є40.
// «адание:
/*
    —оздать проект в котором:
    1. —оздать три файла: function.h, function.cpp, prog.cpp.
    2. ¬ файле function.cpp необходимо написать следующие функции дл€ работы
с массивом данных:
а) функцию дл€ заполнени€ массива случайными значени€ми;
б) функцию дл€ вывода значений массива на консоль;
в) функцию дл€ поиска минимального элемента;
г) функцию дл€ поиска максимального элемента;
д) функцию дл€ сортировки;
е) функцию дл€ редактировани€ значени€ массива.
ƒанные функции необходимо написать дл€ работы с массивом целых, действительных
и символьных значений. ƒл€ каждого типа написать отдельную функцию.
    3. ¬ файле function.h нужно:
а) описать прототипы всех функций;
б) сделать проверку определена ли константа, указывающа€ на тип данных ( #ifdef INTEGER )
в) создать обобщающие имена функции, которым будет определена функци€ соответствующего
типа в зависимости от константы, указанной в файле prog.cpp (# define show ShowInt ).
    4. ¬ файле prog.cpp нужно:
а) в функции main вызвать все функции через переозначеные (обобщенные) имена из
файла function.h ( show ( ));
б) определить константу, котора€ указывает какой тип данных будет использоватьс€.
Ќапример INTEGER - целые данные, CHAR - символьные, DOUBLE - действительные
(#define INTEGER ). »м€ функци€м нужно давать так, чтобы они отвечали своей сути.
Ќапример, функци€ дл€ вывода значений массива целых чисел на консоль - ShowArrayInt().
ј когда переопредел€ем функцию с помощью #define, то нужно давать общее им€.
Ќапример, #define ShowArray ShowArrayInt
*/
#pragma once


#ifdef INTEGER

#define random(arr, length) randomInt(arr, length)
// ‘”Ќ ÷»я заполнени€ массива типа int
//         случайными значени€ми 0...UINT_MAX
// UINT_MAX == 0xffffffff == 4'294'967'295
// INT_MAX ==  2'147'483'647
// INT_MIN == -2'147'483'648
void random(
    int* arr,        // указатель на массив
    size_t length    // длина массива
);

#define print(arr, length, lengthRow) printInt(arr, length, lengthRow)
// ‘”Ќ ÷»я дл€ вывода массива типа int на экран
void print(
    int* arr,                       // указатель на массив
    size_t length,                  // длина массива
    size_t lengthRow                // длина строки вывода в элементах массива
);

#define min(arr, length) minInt(arr, length)
// ‘”Ќ ÷»я поиска в массиве типа int минимального значени€
int min(
    int* arr,           // указатель на массив
    size_t length       // длина массива
);

#define max(arr, length) maxInt(arr, length)
// ‘”Ќ ÷»я поиска в массиве типа int максимального значени€
int max(
    int* arr,           // указатель на массив
    size_t length       // длина массива
);

#define sortAscend(arr, length) sortAscendInt(arr, length)
// ‘”Ќ ÷»я сортировки массива типа int по возрастанию
void sortAscend(
    int* arr,           // указатель на массив
    size_t length       // длина массива
);

#define sortDescend(arr, length) sortDescendInt(arr, length)
// ‘”Ќ ÷»я сортировки массива типа int по убыванию
void sortDescend(
    int* arr,           // указатель на массив
    size_t length       // длина массива
);

#define edit(newValueItem, indexEditItem, arr, length)\
 editInt(newValueItem, indexEditItem, arr, length)
// ‘”Ќ ÷»я редактировани€ значений элементов массива типа int
bool edit(
    int newValueItem,           // новое значение элемента
    size_t indexEditItem,       // индекс редактируемого элемента
    int* arr,                   // указатель на массив
    size_t length               // длина массива
);

#endif


#ifdef DOUBLE

#define random(arr, length) randomDouble(arr, length)
// ‘”Ќ ÷»я заполнени€ массива типа doble
//         случайными значени€ми 0...UINT_MAX
// UINT_MAX == 0xffffffff == 4'294'967'295
void random(
    double* arr,     // указатель на массив
    size_t length    // длина массива
);

#define print(arr, length, lengthRow) printDouble(arr, length, lengthRow)
// ‘”Ќ ÷»я дл€ вывода массива типа double на экран
void print(
    double* arr,                    // указатель на массив
    size_t length,                  // длина массива
    size_t lengthRow                // длина строки вывода в элементах массива
);

#define min(arr, length) minDouble(arr, length)
// ‘”Ќ ÷»я поиска в массиве типа double минимального значени€
double min(
    double* arr,        // указатель на массив
    size_t length       // длина массива
);

#define max(arr, length) maxDouble(arr, length)
// ‘”Ќ ÷»я поиска в массиве типа double максимального значени€
double max(
    double* arr,        // указатель на массив
    size_t length       // длина массива
);

#define sortAscend(arr, length) sortAscendDouble(arr, length)
// ‘”Ќ ÷»я сортировки массива типа double по возрастанию
void sortAscend(
    double* arr,        // указатель на массив
    size_t length       // длина массива
);

#define sortDescend(arr, length) sortDescendDouble(arr, length)
// ‘”Ќ ÷»я сортировки массива типа double по убыванию
void sortDescend(
    double* arr,        // указатель на массив
    size_t length       // длина массива
);

#define edit(newValueItem, indexEditItem, arr, length) editDouble(newValueItem, indexEditItem, arr, length)
// ‘”Ќ ÷»я редактировани€ значений элементов массива типа double
bool edit(
    double newValueItem,        // новое значение элемента
    size_t indexEditItem,       // индекс редактируемого элемента
    double* arr,                // указатель на массив
    size_t length               // длина массива
);

#endif


#ifdef CHAR

#define random(arr, length) randomChar(arr, length)
// ‘”Ќ ÷»я заполнени€ массива типа char
//         случайными значени€ми 0...UINT_MAX
// UINT_MAX == 0xffffffff == 4'294'967'295
// в св€зи с проблемой вывода на экран отдельных значений char
// принимаем диапазон char == 33...126 -> 94 значени€
void random(
    char* arr,       // указатель на массив
    size_t length    // длина массива
);

#define print(arr, length, lengthRow) printChar(arr, length, lengthRow)
// ‘”Ќ ÷»я дл€ вывода массива типа char на экран
void print(
    char* arr,                      // указатель на массив
    size_t length,                  // длина массива
    size_t lengthRow                // длина строки вывода в элементах массива
);

#define min(arr, length) minChar(arr, length)
// ‘”Ќ ÷»я поиска в массиве типа char минимального значени€
char min(
    char* arr,          // указатель на массив
    size_t length       // длина массива
);

#define max(arr, length) maxChar(arr, length)
// ‘”Ќ ÷»я поиска в массиве типа char максимального значени€
char max(
    char* arr,          // указатель на массив
    size_t length       // длина массива
);

#define sortAscend(arr, length) sortAscendChar(arr, length)
// ‘”Ќ ÷»я сортировки массива типа char по возрастанию
void sortAscend(
    char* arr,          // указатель на массив
    size_t length       // длина массива
);

#define sortDescend(arr, length) sortDescendChar(arr, length)
// ‘”Ќ ÷»я сортировки массива типа char по убыванию
void sortDescend(
    char* arr,          // указатель на массив
    size_t length       // длина массива
);

#define edit(newValueItem, indexEditItem, arr, length) editChar(newValueItem, indexEditItem, arr, length)
// ‘”Ќ ÷»я редактировани€ значений элементов массива типа char
bool edit(
    char newValueItem,          // новое значение элемента
    size_t indexEditItem,       // индекс редактируемого элемента
    char* arr,                  // указатель на массив
    size_t length               // длина массива
);

#endif
