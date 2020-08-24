// DZ_ST_C++_07_dz22_vstrecha22_zadanie2_MathExceptions.h
#pragma once
#include <iostream>
#include "DZ_ST_C++_07_dz22_vstrecha22_zadanie2_MainParentException.h"


// �����-������������ ����� �������������� ����������
enum class MATH_EXCEPT {
	NONE,										// ����� - �������� ��� �������������
	INVALID_ARGUMENT_TYPE,						// ����������������� ��� ���������
	DIVISION_BY_ZERO,							// ������� �� ����
	THE_SQUARE_ROOT_OF_A_NEGATIVE_NUMBER,		// ���������� ������ �� �������������� �����
};

// ����� ���������� �������������� ����������
class MathExcept {
private:
	MATH_EXCEPT exception{ MATH_EXCEPT::NONE };         // ����������
public:
	// ����������� � �����������
	MathExcept(MATH_EXCEPT exception_) : exception(exception_) {}

	// ���������� ������������� ������� ���������� ��������� <<
	// ��� ������ ��������� ���������� �� �����
	friend std::ostream& operator<<(std::ostream& out, const MathExcept& mathExcept);
};

// ������������� ������� ���������� ��������� << ��� ������ ��������� ���������� �� �����
std::ostream& operator<<(std::ostream& out, const MathExcept& mathExcept) {
	switch (mathExcept.exception)
	{
	case MATH_EXCEPT::NONE:	{
		out << " �����";
		break;
	}
	case MATH_EXCEPT::INVALID_ARGUMENT_TYPE: {
		out << " ����������������� ��� ���������";
		break;
	}
	case MATH_EXCEPT::DIVISION_BY_ZERO:	{
		out << " ������� �� ����";
		break;
	}
	case MATH_EXCEPT::THE_SQUARE_ROOT_OF_A_NEGATIVE_NUMBER:	{
		out << " ���������� ������ �� �������������� �����";
		break;
	}
	}
	return out;
}

// �������� ����� �������������� ���������� � �������������� �����������
class MathExceptions : public MainParentException<MathExcept> {
public:
	// ����������� ��������� ������ � �����������,
	// �������� ����������� ������������� ������
	MathExceptions(MathExcept exception_, int lineNumber_, const char* nameFile_) :
		MainParentException(exception_, lineNumber_, nameFile_)
	{}
};

