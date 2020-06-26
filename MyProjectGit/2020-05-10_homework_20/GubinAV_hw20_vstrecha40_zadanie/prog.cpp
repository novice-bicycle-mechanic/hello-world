// ���� prog.cpp
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

#include <cstdio>
#include <clocale>

// INTEGER DOUBLE CHAR - ��������� ����� ������ ��� ���������� ��������� ��� ������ � ������������ �����
#define INTEGER
//#define DOUBLE
//#define CHAR

#include "function.h"


// ������� �������
int main() {
    setlocale(LC_ALL, "ru");

    size_t length = 30;                             // ����� �������

#ifdef INTEGER
#define ARRAY arrayInt
#define LENGT_ROW lengthRowInt
#define TYPE_VALUE "%d"
    int* ARRAY = new int[length] {};                // ������ ���� int
    size_t LENGT_ROW = 80 / 12;                     // ����� ������ ������� �� ������
    const char* typeArray = "int";                  // ������������ ���� �������
    int editValue = 999'999;                        // ����� �������� � ������������� ��������
#endif

#ifdef DOUBLE
#define ARRAY arrayDouble
#define LENGT_ROW lengthRowDouble
#define TYPE_VALUE "%.3f"
    double* ARRAY = new double[length] {};          // ������ ���� double
    size_t LENGT_ROW = 80 / 16;                     // ����� ������ ������� �� ������
    const char* typeArray = "double";               // ������������ ���� �������
    double editValue = 666.666;                     // ����� �������� � ������������� ��������
#endif

#ifdef CHAR
#define ARRAY arrayChar
#define LENGT_ROW lengthRowChar
#define TYPE_VALUE "%c"
    char* ARRAY = new char[length] {};              // ������ ���� char
    size_t LENGT_ROW = 80 / 2;                      // ����� ������ ������� �� ������
    const char* typeArray = "char";                 // ������������ ���� �������
    char editValue = '#';                           // ����� �������� � ������������� ��������
#endif

    printf_s("            ���������� ������� ���� %s ���������� ����������\n\n", typeArray);
    random(ARRAY, length);
    print(ARRAY, length, LENGT_ROW);

    printf_s(" ����������� �������� � ������� ���� %s ����� " TYPE_VALUE "\n\n", typeArray, min(ARRAY, length));
    printf_s(" ������������ �������� � ������� ���� %s ����� " TYPE_VALUE "\n\n", typeArray, max(ARRAY, length));

    printf_s("               ���������� ������� ���� %s �� �����������\n\n", typeArray);
    sortAscend(ARRAY, length);
    print(ARRAY, length, LENGT_ROW);

    printf_s("               ���������� ������� ���� %s �� ��������\n\n", typeArray);
    sortDescend(ARRAY, length);
    print(ARRAY, length, LENGT_ROW);

    printf_s("                  �������������� ������� ���� %s\n", typeArray);
    printf_s(" (����������������� �������� <" TYPE_VALUE "> � ������, �������� � ����� �������)\n\n", editValue);
    edit(editValue, 0, ARRAY, length);
    edit(editValue, 15, ARRAY, length);
    edit(editValue, 29, ARRAY, length);
    print(ARRAY, length, LENGT_ROW);

    return 0;
}
