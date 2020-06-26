// файл function.cpp
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

#define _CRT_RAND_S
#include <stdlib.h>
#include <cstdio>


// ‘”Ќ ÷»я заполнени€ массива типа int
//         случайными значени€ми 0...UINT_MAX
// UINT_MAX == 0xffffffff == 4'294'967'295
// INT_MAX ==  2'147'483'647
// INT_MIN == -2'147'483'648
void randomInt(
    int* arr,        // указатель на массив
    size_t length    // длина массива
) {
    unsigned int randomValue = 0;
    for (size_t i = 0; i < length; i++) {
        rand_s(&randomValue);
        arr[i] = (int)(randomValue - UINT_MAX / 2);
    }
}


// ‘”Ќ ÷»я заполнени€ массива типа doble
//         случайными значени€ми 0...UINT_MAX
// UINT_MAX == 0xffffffff == 4'294'967'295
void randomDouble(
    double* arr,        // указатель на массив
    size_t length    // длина массива
) {
    unsigned int randomValue = 0;
    for (size_t i = 0; i < length; i++) {
        rand_s(&randomValue);
        arr[i] = (double)((int)(randomValue - UINT_MAX / 2)) / 1000;
    }
}


// ‘”Ќ ÷»я заполнени€ массива типа char
//         случайными значени€ми 0...UINT_MAX
// UINT_MAX == 0xffffffff == 4'294'967'295
// в св€зи с проблемой вывода на экран отдельных значений char
// принимаем диапазон char == 33...126 -> 94 значени€
void randomChar(
    char* arr,        // указатель на массив
    size_t length    // длина массива
) {
    unsigned int randomValue = 0;
    for (size_t i = 0; i < length; i++) {
        rand_s(&randomValue);
        arr[i] = (char)((unsigned int)(randomValue / 45691141.44) + 33);
    }
}


// ‘”Ќ ÷»я дл€ вывода массива типа int на экран
void printInt(
    int* arr,                       // указатель на массив
    size_t length,                  // длина массива
    size_t lengthRow = 80 / 12      // длина строки вывода в элементах массива
) {
    for (size_t i = 0; i < length; i++) {
        printf_s("%12d", arr[i]);
        if ((!((i + 1) % lengthRow)) && (i)) printf_s("\n");
    }
    printf_s("\n\n");
}


// ‘”Ќ ÷»я дл€ вывода массива типа double на экран
void printDouble(
    double* arr,                       // указатель на массив
    size_t length,                  // длина массива
    size_t lengthRow = 80 / 16      // длина строки вывода в элементах массива
) {
    for (size_t i = 0; i < length; i++) {
        printf_s("%14.3f", arr[i]);
        if ((!((i + 1) % lengthRow)) && (i)) printf_s("\n");
    }
    printf_s("\n\n");
}


// ‘”Ќ ÷»я дл€ вывода массива типа char на экран
void printChar(
    char* arr,                       // указатель на массив
    size_t length,                  // длина массива
    size_t lengthRow = 80 / 2       // длина строки вывода в элементах массива
) {
    for (size_t i = 0; i < length; i++) {
        printf_s("%2c", arr[i]);
        if ((!((i + 1) % lengthRow)) && (i)) printf_s("\n");
    }
    printf_s("\n\n");
}


// ‘”Ќ ÷»я поиска в массиве типа int минимального значени€
int minInt(
    int* arr,        // указатель на массив
    size_t length    // длина массива
) {
    int min = INT_MAX;
    for (size_t i = 0; i < length; i++) {
        if (min > arr[i]) min = arr[i];
    }
    return min;
}


// ‘”Ќ ÷»я поиска в массиве типа int максимального значени€
int maxInt(
    int* arr,        // указатель на массив
    size_t length    // длина массива
) {
    int max = INT_MIN;
    for (size_t i = 0; i < length; i++) {
        if (max < arr[i]) max = arr[i];
    }
    return max;
}


// ‘”Ќ ÷»я поиска в массиве типа double минимального значени€
double minDouble(
    double* arr,        // указатель на массив
    size_t length       // длина массива
) {
    double min = (double)INT_MAX;
    for (size_t i = 0; i < length; i++) {
        if (min > arr[i]) min = arr[i];
    }
    return min;
}


// ‘”Ќ ÷»я поиска в массиве типа double максимального значени€
double maxDouble(
    double* arr,        // указатель на массив
    size_t length       // длина массива
) {
    double max = (double)INT_MIN;
    for (size_t i = 0; i < length; i++) {
        if (max < arr[i]) max = arr[i];
    }
    return max;
}


// ‘”Ќ ÷»я поиска в массиве типа char минимального значени€
char minChar(
    char* arr,        // указатель на массив
    size_t length    // длина массива
) {
    char min = SCHAR_MAX;
    for (size_t i = 0; i < length; i++) {
        if (min > arr[i]) min = arr[i];
    }
    return min;
}


// ‘”Ќ ÷»я поиска в массиве типа char максимального значени€
char maxChar(
    char* arr,        // указатель на массив
    size_t length    // длина массива
) {
    char max = SCHAR_MIN;
    for (size_t i = 0; i < length; i++) {
        if (max < arr[i]) max = arr[i];
    }
    return max;
}


// ‘”Ќ ÷»я сортировки массива типа int по возрастанию
void sortAscendInt(
    int* arr,        // указатель на массив
    size_t length    // длина массива
) {
    int buffer = 0;
    for (size_t i = 0; i < length; i++) {
        for (size_t j = 1; j < length; j++) {
            if (arr[j - 1] > arr[j]) {
                buffer = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = buffer;
            }
        }
    }
}


// ‘”Ќ ÷»я сортировки массива типа int по убыванию
void sortDescendInt(
    int* arr,        // указатель на массив
    size_t length    // длина массива
) {
    int buffer = 0;
    for (size_t i = 0; i < length; i++) {
        for (size_t j = 1; j < length; j++) {
            if (arr[j - 1] < arr[j]) {
                buffer = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = buffer;
            }
        }
    }
}


// ‘”Ќ ÷»я сортировки массива типа double по возрастанию
void sortAscendDouble(
    double* arr,        // указатель на массив
    size_t length       // длина массива
) {
    double buffer = 0;
    for (size_t i = 0; i < length; i++) {
        for (size_t j = 1; j < length; j++) {
            if (arr[j - 1] > arr[j]) {
                buffer = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = buffer;
            }
        }
    }
}


// ‘”Ќ ÷»я сортировки массива типа double по убыванию
void sortDescendDouble(
    double* arr,        // указатель на массив
    size_t length    // длина массива
) {
    double buffer = 0;
    for (size_t i = 0; i < length; i++) {
        for (size_t j = 1; j < length; j++) {
            if (arr[j - 1] < arr[j]) {
                buffer = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = buffer;
            }
        }
    }
}


// ‘”Ќ ÷»я сортировки массива типа char по возрастанию
void sortAscendChar(
    char* arr,          // указатель на массив
    size_t length       // длина массива
) {
    char buffer = 0;
    for (size_t i = 0; i < length; i++) {
        for (size_t j = 1; j < length; j++) {
            if (arr[j - 1] > arr[j]) {
                buffer = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = buffer;
            }
        }
    }
}


// ‘”Ќ ÷»я сортировки массива типа char по убыванию
void sortDescendChar(
    char* arr,          // указатель на массив
    size_t length       // длина массива
) {
    char buffer = 0;
    for (size_t i = 0; i < length; i++) {
        for (size_t j = 1; j < length; j++) {
            if (arr[j - 1] < arr[j]) {
                buffer = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = buffer;
            }
        }
    }
}


// ‘”Ќ ÷»я редактировани€ значений элементов массива типа int
bool editInt(
    int newValueItem,           // новое значение элемента
    size_t indexEditItem,       // индекс редактируемого элемента
    int* arr,                   // указатель на массив
    size_t length               // длина массива
) {
    if ((0 <= indexEditItem) && (indexEditItem < length)) {
        arr[indexEditItem] = newValueItem;
        return true;
    }
    else return false;
}


// ‘”Ќ ÷»я редактировани€ значений элементов массива типа double
bool editDouble(
    double newValueItem,        // новое значение элемента
    size_t indexEditItem,       // индекс редактируемого элемента
    double* arr,                // указатель на массив
    size_t length               // длина массива
) {
    if ((0 <= indexEditItem) && (indexEditItem < length)) {
        arr[indexEditItem] = newValueItem;
        return true;
    }
    else return false;
}


// ‘”Ќ ÷»я редактировани€ значений элементов массива типа char
bool editChar(
    char newValueItem,        // новое значение элемента
    size_t indexEditItem,       // индекс редактируемого элемента
    char* arr,                // указатель на массив
    size_t length               // длина массива
) {
    if ((0 <= indexEditItem) && (indexEditItem < length)) {
        arr[indexEditItem] = newValueItem;
        return true;
    }
    else return false;
}
