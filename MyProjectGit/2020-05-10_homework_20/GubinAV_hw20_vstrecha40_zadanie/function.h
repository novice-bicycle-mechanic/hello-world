// ���� function.h
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
#pragma once


#ifdef INTEGER

#define random(arr, length) randomInt(arr, length)
// ������� ���������� ������� ���� int
//         ���������� ���������� 0...UINT_MAX
// UINT_MAX == 0xffffffff == 4'294'967'295
// INT_MAX ==  2'147'483'647
// INT_MIN == -2'147'483'648
void random(
    int* arr,        // ��������� �� ������
    size_t length    // ����� �������
);

#define print(arr, length, lengthRow) printInt(arr, length, lengthRow)
// ������� ��� ������ ������� ���� int �� �����
void print(
    int* arr,                       // ��������� �� ������
    size_t length,                  // ����� �������
    size_t lengthRow                // ����� ������ ������ � ��������� �������
);

#define min(arr, length) minInt(arr, length)
// ������� ������ � ������� ���� int ������������ ��������
int min(
    int* arr,           // ��������� �� ������
    size_t length       // ����� �������
);

#define max(arr, length) maxInt(arr, length)
// ������� ������ � ������� ���� int ������������� ��������
int max(
    int* arr,           // ��������� �� ������
    size_t length       // ����� �������
);

#define sortAscend(arr, length) sortAscendInt(arr, length)
// ������� ���������� ������� ���� int �� �����������
void sortAscend(
    int* arr,           // ��������� �� ������
    size_t length       // ����� �������
);

#define sortDescend(arr, length) sortDescendInt(arr, length)
// ������� ���������� ������� ���� int �� ��������
void sortDescend(
    int* arr,           // ��������� �� ������
    size_t length       // ����� �������
);

#define edit(newValueItem, indexEditItem, arr, length)\
 editInt(newValueItem, indexEditItem, arr, length)
// ������� �������������� �������� ��������� ������� ���� int
bool edit(
    int newValueItem,           // ����� �������� ��������
    size_t indexEditItem,       // ������ �������������� ��������
    int* arr,                   // ��������� �� ������
    size_t length               // ����� �������
);

#endif


#ifdef DOUBLE

#define random(arr, length) randomDouble(arr, length)
// ������� ���������� ������� ���� doble
//         ���������� ���������� 0...UINT_MAX
// UINT_MAX == 0xffffffff == 4'294'967'295
void random(
    double* arr,     // ��������� �� ������
    size_t length    // ����� �������
);

#define print(arr, length, lengthRow) printDouble(arr, length, lengthRow)
// ������� ��� ������ ������� ���� double �� �����
void print(
    double* arr,                    // ��������� �� ������
    size_t length,                  // ����� �������
    size_t lengthRow                // ����� ������ ������ � ��������� �������
);

#define min(arr, length) minDouble(arr, length)
// ������� ������ � ������� ���� double ������������ ��������
double min(
    double* arr,        // ��������� �� ������
    size_t length       // ����� �������
);

#define max(arr, length) maxDouble(arr, length)
// ������� ������ � ������� ���� double ������������� ��������
double max(
    double* arr,        // ��������� �� ������
    size_t length       // ����� �������
);

#define sortAscend(arr, length) sortAscendDouble(arr, length)
// ������� ���������� ������� ���� double �� �����������
void sortAscend(
    double* arr,        // ��������� �� ������
    size_t length       // ����� �������
);

#define sortDescend(arr, length) sortDescendDouble(arr, length)
// ������� ���������� ������� ���� double �� ��������
void sortDescend(
    double* arr,        // ��������� �� ������
    size_t length       // ����� �������
);

#define edit(newValueItem, indexEditItem, arr, length) editDouble(newValueItem, indexEditItem, arr, length)
// ������� �������������� �������� ��������� ������� ���� double
bool edit(
    double newValueItem,        // ����� �������� ��������
    size_t indexEditItem,       // ������ �������������� ��������
    double* arr,                // ��������� �� ������
    size_t length               // ����� �������
);

#endif


#ifdef CHAR

#define random(arr, length) randomChar(arr, length)
// ������� ���������� ������� ���� char
//         ���������� ���������� 0...UINT_MAX
// UINT_MAX == 0xffffffff == 4'294'967'295
// � ����� � ��������� ������ �� ����� ��������� �������� char
// ��������� �������� char == 33...126 -> 94 ��������
void random(
    char* arr,       // ��������� �� ������
    size_t length    // ����� �������
);

#define print(arr, length, lengthRow) printChar(arr, length, lengthRow)
// ������� ��� ������ ������� ���� char �� �����
void print(
    char* arr,                      // ��������� �� ������
    size_t length,                  // ����� �������
    size_t lengthRow                // ����� ������ ������ � ��������� �������
);

#define min(arr, length) minChar(arr, length)
// ������� ������ � ������� ���� char ������������ ��������
char min(
    char* arr,          // ��������� �� ������
    size_t length       // ����� �������
);

#define max(arr, length) maxChar(arr, length)
// ������� ������ � ������� ���� char ������������� ��������
char max(
    char* arr,          // ��������� �� ������
    size_t length       // ����� �������
);

#define sortAscend(arr, length) sortAscendChar(arr, length)
// ������� ���������� ������� ���� char �� �����������
void sortAscend(
    char* arr,          // ��������� �� ������
    size_t length       // ����� �������
);

#define sortDescend(arr, length) sortDescendChar(arr, length)
// ������� ���������� ������� ���� char �� ��������
void sortDescend(
    char* arr,          // ��������� �� ������
    size_t length       // ����� �������
);

#define edit(newValueItem, indexEditItem, arr, length) editChar(newValueItem, indexEditItem, arr, length)
// ������� �������������� �������� ��������� ������� ���� char
bool edit(
    char newValueItem,          // ����� �������� ��������
    size_t indexEditItem,       // ������ �������������� ��������
    char* arr,                  // ��������� �� ������
    size_t length               // ����� �������
);

#endif
