// DZ_ST_C++_07_dz22_vstrecha22_zadanie1_ListExcertions.h
//
// ������� �� ����� DZ_ST_C++_07.pdf
// �������� ������� �22
// ������� �22, ������� 1
// ����: ����������
/*
�������� � ����� ����������� ������ �������� ��������� ����������.
�� ��� ����� ����������� ���������� � ������ ������.
��������, �������� ������, ������� �������� �� ������� ������ � �.�.
*/

#pragma once
#include <iostream>


// �����-������������ ����������
enum class EXCEPTIONS {
    NO_EXCEPTIONS,                                          // ��� ���������� (�������� �������������)
    NULL_POINTER_TO_THE_HEAD_OF_THE_LIST,                   // ������� ��������� �� ������ ������
    NULL_POINTER_TO_THE_TAIL_OF_THE_LIST,                   // ������� ��������� �� ����� ������
    NULL_POINTER_TO_A_LIST_ITEM,                            // ������� ��������� �� ������� ������
    THE_POSITION_NUMBER_IN_THE_LIST_IS_ZERO,                // ����� ������� � ������ ����� ����
    THE_POSITION_NUMBER_IN_THE_LIST_IS_NEGATIVE,            // ����� ������� � ������ �������������
    THE_POSITION_NUMBER_IN_THE_LIST_IS_GREATER_THAN_THE_MAXIMUM,   // ����� ������� � ������ ������ �������������
    THE_CURRENT_POSITION_IN_THE_LIST_IS_GREATER_THAN_THE_SPECIFIED_ONE, // ������� ������� � ������ ������ ��������
    INVALID_CLASS_INSTANCE_TYPE                             // ������������ ��� ���������� ������
};


// ����� ���������� ��� ������ ������
class ListExceptions {
private:
    EXCEPTIONS exception{ EXCEPTIONS::NO_EXCEPTIONS };  // �������� ����������
    int lineNumber{ 0 };                                // ����� ������ ��������� ����������
    const char* nameFile;                               // ��� ����� ��������� ����������
public:
    ListExceptions(EXCEPTIONS exception_, int lineNumber_, const char* nameFile_) :
        exception(exception_), lineNumber(lineNumber_), nameFile(nameFile_)
    {}

    friend std::ostream& operator<<(std::ostream& out, const ListExceptions& except);
};


