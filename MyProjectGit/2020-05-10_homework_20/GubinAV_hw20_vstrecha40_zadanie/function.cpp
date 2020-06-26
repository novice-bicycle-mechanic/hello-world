// ���� function.cpp
// ������� �� ����� homework 20.pdf
// ����: ������������
// ������� �40.
// �������:
/*
    ������� ������ � �������:
    1. ������� ��� �����: function.h, function.cpp, prog.cpp.
    2. � ����� function.cpp ���������� �������� ��������� ������� ��� ������
� �������� ������:
�) ������� ��� ���������� ������� ���������� ����������;
�) ������� ��� ������ �������� ������� �� �������;
�) ������� ��� ������ ������������ ��������;
�) ������� ��� ������ ������������� ��������;
�) ������� ��� ����������;
�) ������� ��� �������������� �������� �������.
������ ������� ���������� �������� ��� ������ � �������� �����, ��������������
� ���������� ��������. ��� ������� ���� �������� ��������� �������.
    3. � ����� function.h �����:
�) ������� ��������� ���� �������;
�) ������� �������� ���������� �� ���������, ����������� �� ��� ������ ( #ifdef INTEGER )
�) ������� ���������� ����� �������, ������� ����� ���������� ������� ����������������
���� � ����������� �� ���������, ��������� � ����� prog.cpp (# define show ShowInt ).
    4. � ����� prog.cpp �����:
�) � ������� main ������� ��� ������� ����� ������������� (����������) ����� ��
����� function.h ( show ( ));
�) ���������� ���������, ������� ��������� ����� ��� ������ ����� ��������������.
�������� INTEGER - ����� ������, CHAR - ����������, DOUBLE - ��������������
(#define INTEGER ). ��� �������� ����� ������ ���, ����� ��� �������� ����� ����.
��������, ������� ��� ������ �������� ������� ����� ����� �� ������� - ShowArrayInt().
� ����� �������������� ������� � ������� #define, �� ����� ������ ����� ���.
��������, #define ShowArray ShowArrayInt
*/

#define _CRT_RAND_S
#include <stdlib.h>
#include <cstdio>


// ������� ���������� ������� ���� int
//         ���������� ���������� 0...UINT_MAX
// UINT_MAX == 0xffffffff == 4'294'967'295
// INT_MAX ==  2'147'483'647
// INT_MIN == -2'147'483'648
void randomInt(
    int* arr,        // ��������� �� ������
    size_t length    // ����� �������
) {
    unsigned int randomValue = 0;
    for (size_t i = 0; i < length; i++) {
        rand_s(&randomValue);
        arr[i] = (int)(randomValue - UINT_MAX / 2);
    }
}


// ������� ���������� ������� ���� doble
//         ���������� ���������� 0...UINT_MAX
// UINT_MAX == 0xffffffff == 4'294'967'295
void randomDouble(
    double* arr,        // ��������� �� ������
    size_t length    // ����� �������
) {
    unsigned int randomValue = 0;
    for (size_t i = 0; i < length; i++) {
        rand_s(&randomValue);
        arr[i] = (double)((int)(randomValue - UINT_MAX / 2)) / 1000;
    }
}


// ������� ���������� ������� ���� char
//         ���������� ���������� 0...UINT_MAX
// UINT_MAX == 0xffffffff == 4'294'967'295
// � ����� � ��������� ������ �� ����� ��������� �������� char
// ��������� �������� char == 33...126 -> 94 ��������
void randomChar(
    char* arr,        // ��������� �� ������
    size_t length    // ����� �������
) {
    unsigned int randomValue = 0;
    for (size_t i = 0; i < length; i++) {
        rand_s(&randomValue);
        arr[i] = (char)((unsigned int)(randomValue / 45691141.44) + 33);
    }
}


// ������� ��� ������ ������� ���� int �� �����
void printInt(
    int* arr,                       // ��������� �� ������
    size_t length,                  // ����� �������
    size_t lengthRow = 80 / 12      // ����� ������ ������ � ��������� �������
) {
    for (size_t i = 0; i < length; i++) {
        printf_s("%12d", arr[i]);
        if ((!((i + 1) % lengthRow)) && (i)) printf_s("\n");
    }
    printf_s("\n\n");
}


// ������� ��� ������ ������� ���� double �� �����
void printDouble(
    double* arr,                       // ��������� �� ������
    size_t length,                  // ����� �������
    size_t lengthRow = 80 / 16      // ����� ������ ������ � ��������� �������
) {
    for (size_t i = 0; i < length; i++) {
        printf_s("%14.3f", arr[i]);
        if ((!((i + 1) % lengthRow)) && (i)) printf_s("\n");
    }
    printf_s("\n\n");
}


// ������� ��� ������ ������� ���� char �� �����
void printChar(
    char* arr,                       // ��������� �� ������
    size_t length,                  // ����� �������
    size_t lengthRow = 80 / 2       // ����� ������ ������ � ��������� �������
) {
    for (size_t i = 0; i < length; i++) {
        printf_s("%2c", arr[i]);
        if ((!((i + 1) % lengthRow)) && (i)) printf_s("\n");
    }
    printf_s("\n\n");
}


// ������� ������ � ������� ���� int ������������ ��������
int minInt(
    int* arr,        // ��������� �� ������
    size_t length    // ����� �������
) {
    int min = INT_MAX;
    for (size_t i = 0; i < length; i++) {
        if (min > arr[i]) min = arr[i];
    }
    return min;
}


// ������� ������ � ������� ���� int ������������� ��������
int maxInt(
    int* arr,        // ��������� �� ������
    size_t length    // ����� �������
) {
    int max = INT_MIN;
    for (size_t i = 0; i < length; i++) {
        if (max < arr[i]) max = arr[i];
    }
    return max;
}


// ������� ������ � ������� ���� double ������������ ��������
double minDouble(
    double* arr,        // ��������� �� ������
    size_t length       // ����� �������
) {
    double min = (double)INT_MAX;
    for (size_t i = 0; i < length; i++) {
        if (min > arr[i]) min = arr[i];
    }
    return min;
}


// ������� ������ � ������� ���� double ������������� ��������
double maxDouble(
    double* arr,        // ��������� �� ������
    size_t length       // ����� �������
) {
    double max = (double)INT_MIN;
    for (size_t i = 0; i < length; i++) {
        if (max < arr[i]) max = arr[i];
    }
    return max;
}


// ������� ������ � ������� ���� char ������������ ��������
char minChar(
    char* arr,        // ��������� �� ������
    size_t length    // ����� �������
) {
    char min = SCHAR_MAX;
    for (size_t i = 0; i < length; i++) {
        if (min > arr[i]) min = arr[i];
    }
    return min;
}


// ������� ������ � ������� ���� char ������������� ��������
char maxChar(
    char* arr,        // ��������� �� ������
    size_t length    // ����� �������
) {
    char max = SCHAR_MIN;
    for (size_t i = 0; i < length; i++) {
        if (max < arr[i]) max = arr[i];
    }
    return max;
}


// ������� ���������� ������� ���� int �� �����������
void sortAscendInt(
    int* arr,        // ��������� �� ������
    size_t length    // ����� �������
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


// ������� ���������� ������� ���� int �� ��������
void sortDescendInt(
    int* arr,        // ��������� �� ������
    size_t length    // ����� �������
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


// ������� ���������� ������� ���� double �� �����������
void sortAscendDouble(
    double* arr,        // ��������� �� ������
    size_t length       // ����� �������
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


// ������� ���������� ������� ���� double �� ��������
void sortDescendDouble(
    double* arr,        // ��������� �� ������
    size_t length    // ����� �������
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


// ������� ���������� ������� ���� char �� �����������
void sortAscendChar(
    char* arr,          // ��������� �� ������
    size_t length       // ����� �������
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


// ������� ���������� ������� ���� char �� ��������
void sortDescendChar(
    char* arr,          // ��������� �� ������
    size_t length       // ����� �������
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


// ������� �������������� �������� ��������� ������� ���� int
bool editInt(
    int newValueItem,           // ����� �������� ��������
    size_t indexEditItem,       // ������ �������������� ��������
    int* arr,                   // ��������� �� ������
    size_t length               // ����� �������
) {
    if ((0 <= indexEditItem) && (indexEditItem < length)) {
        arr[indexEditItem] = newValueItem;
        return true;
    }
    else return false;
}


// ������� �������������� �������� ��������� ������� ���� double
bool editDouble(
    double newValueItem,        // ����� �������� ��������
    size_t indexEditItem,       // ������ �������������� ��������
    double* arr,                // ��������� �� ������
    size_t length               // ����� �������
) {
    if ((0 <= indexEditItem) && (indexEditItem < length)) {
        arr[indexEditItem] = newValueItem;
        return true;
    }
    else return false;
}


// ������� �������������� �������� ��������� ������� ���� char
bool editChar(
    char newValueItem,        // ����� �������� ��������
    size_t indexEditItem,       // ������ �������������� ��������
    char* arr,                // ��������� �� ������
    size_t length               // ����� �������
) {
    if ((0 <= indexEditItem) && (indexEditItem < length)) {
        arr[indexEditItem] = newValueItem;
        return true;
    }
    else return false;
}
