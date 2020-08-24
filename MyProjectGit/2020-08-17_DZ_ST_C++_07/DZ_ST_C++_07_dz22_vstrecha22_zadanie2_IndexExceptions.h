// DZ_ST_C++_07_dz22_vstrecha22_zadanie2_IndexExceptions.h
#pragma once
#include <iostream>
#include "DZ_ST_C++_07_dz22_vstrecha22_zadanie2_MainParentException.h"


// �����-������������ ����� ���������� ��������
enum class INDEX_EXCEPT {
	NONE,													// ����� - �������� ��� �������������
	THE_INDEX_VALUE_IS_LESS_THAN_ZERO,						// �������� ������� ������ ����
	THE_INDEX_VALUE_IS_LESS_THAN_THE_SPECIFIED_VALUE,		// �������� ������� ������ ���������
	THE_INDEX_VALUE_IS_GREATER_THAN_THE_MAXIMUM,			// �������� ������� ������ �������������
	THE_INDEX_VALUE_IS_GREATER_THAN_THE_SPECIFIED_VALUE,	// �������� ������� ������ ���������
};

// ����� ���������� ���������� ��������
class IndexExcept {
private:
	INDEX_EXCEPT exception{ INDEX_EXCEPT::NONE };         // ����������
public:
	// ����������� � �����������
	IndexExcept(INDEX_EXCEPT exception_) : exception(exception_) {}

	// ���������� ������������� ������� ���������� ��������� <<
	// ��� ������ ��������� ���������� �� �����
	friend std::ostream& operator<<(std::ostream& out, const IndexExcept& indexExcept);
};

// ������������� ������� ���������� ��������� << ��� ������ ��������� ���������� �� �����
std::ostream& operator<<(std::ostream& out, const IndexExcept& indexExcept) {
	switch (indexExcept.exception)
	{
	case INDEX_EXCEPT::NONE: {
		out << " �����";
		break;
	}
	case INDEX_EXCEPT::THE_INDEX_VALUE_IS_LESS_THAN_ZERO: {
		out << " �������� ������� ������ ����";
		break;
	}
	case INDEX_EXCEPT::THE_INDEX_VALUE_IS_LESS_THAN_THE_SPECIFIED_VALUE: {
		out << " �������� ������� ������ ���������";
		break;
	}
	case INDEX_EXCEPT::THE_INDEX_VALUE_IS_GREATER_THAN_THE_MAXIMUM: {
		out << " �������� ������� ������ �������������";
		break;
	}
	case INDEX_EXCEPT::THE_INDEX_VALUE_IS_GREATER_THAN_THE_SPECIFIED_VALUE: {
		out << " �������� ������� ������ ���������";
		break;
	}
	}
	return out;
}

// �������� ����� ���������� �������� � �������������� �����������
class IndexExceptions : public MainParentException<IndexExcept> {
public:
	// ����������� ��������� ������ � �����������,
	// �������� ����������� ������������� ������
	IndexExceptions(IndexExcept exception_, int lineNumber_, const char* nameFile_) :
		MainParentException(exception_, lineNumber_, nameFile_)
	{}
};

