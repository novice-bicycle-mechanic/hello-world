// DZ_ST_C++_07_dz22_vstrecha22_zadanie1_ListExcertions.cpp

#include "DZ_ST_C++_07_dz22_vstrecha22_zadanie1_ListExcertions.h"


// ������������� ������� ���������� ��������� << ��� ������ ��������� ����������
std::ostream& operator<<(std::ostream& out, const ListExceptions& except) {
    switch (except.exception)
    {
    case EXCEPTIONS::NO_EXCEPTIONS: {
        break;
    }
    case EXCEPTIONS::NULL_POINTER_TO_THE_HEAD_OF_THE_LIST: {
        out << " ������!\n"
            << " ���� " << except.nameFile << "\n"
            << " ������ " << except.lineNumber << ":"
            << " ������� ��������� �� ������ ������";
        break;
    }
    case EXCEPTIONS::NULL_POINTER_TO_THE_TAIL_OF_THE_LIST: {
        out << " ������!\n"
            << " ���� " << except.nameFile << "\n"
            << " ������ " << except.lineNumber << ":"
            << " ������� ��������� �� ����� ������";
        break;
    }
    case EXCEPTIONS::NULL_POINTER_TO_A_LIST_ITEM: {
        out << " ������!\n"
            << " ���� " << except.nameFile << "\n"
            << " ������ " << except.lineNumber << ":"
            << " ������� ��������� �� ������� ������";
        break;
    }
    case EXCEPTIONS::THE_POSITION_NUMBER_IN_THE_LIST_IS_ZERO: {
        out << " ������!\n"
            << " ���� " << except.nameFile << "\n"
            << " ������ " << except.lineNumber << ":"
            << " ����� ������� � ������ ����� ����";
        break;
    }
    case EXCEPTIONS::THE_POSITION_NUMBER_IN_THE_LIST_IS_NEGATIVE: {
        out << " ������!\n"
            << " ���� " << except.nameFile << "\n"
            << " ������ " << except.lineNumber << ":"
            << " ����� ������� � ������ ������ ����";
        break;
    }
    case EXCEPTIONS::THE_POSITION_NUMBER_IN_THE_LIST_IS_GREATER_THAN_THE_MAXIMUM: {
        out << " ������!\n"
            << " ���� " << except.nameFile << "\n"
            << " ������ " << except.lineNumber << ":"
            << " ����� ������� � ������ ������ �������������";
        break;
    }
    case EXCEPTIONS::THE_CURRENT_POSITION_IN_THE_LIST_IS_GREATER_THAN_THE_SPECIFIED_ONE: {
        out << " ������!\n"
            << " ���� " << except.nameFile << "\n"
            << " ������ " << except.lineNumber << ":"
            << " ������� ������� � ������ ������ ��������";
        break;
    }
    case EXCEPTIONS::INVALID_CLASS_INSTANCE_TYPE: {
        out << " ������!\n"
            << " ���� " << except.nameFile << "\n"
            << " ������ " << except.lineNumber << ":"
            << " ������������ ��� ���������� ������.\n"
            << " ���������: short, unsigned short, int, unsigned int,\n"
            << " long, unsigned long, long long, unsigned long long";
        break;
    }
    }
    return out;
}
