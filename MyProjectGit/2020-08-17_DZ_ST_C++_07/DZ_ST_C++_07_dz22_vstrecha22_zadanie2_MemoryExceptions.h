// DZ_ST_C++_07_dz22_vstrecha22_zadanie2_MemoryExceptions.h
#pragma once
#include <iostream>
#include "DZ_ST_C++_07_dz22_vstrecha22_zadanie2_MainParentException.h"


// �����-������������ ����� ���������� ������
enum class MEMORY_EXCEPT {
	NONE,													// ����� - �������� ��� �������������
	NOT_ENOUGH_STACK_MEMORY,								// ������������ �������� ������
	NOT_ENOUGH_DYNAMIC_MEMORY,								// ������������ ������������ ������
	DYNAMIC_MEMORY_IS_NOT_ALLOCATED,						// ������������ ������ �� ��������
	THE_ALLOCATED_DYNAMIC_MEMORY_WAS_NOT_DELETED,			// ���������� ������������ ������ �� �������
};

// ����� ���������� ���������� ������
class MemoryExcept {
private:
	MEMORY_EXCEPT exception{ MEMORY_EXCEPT::NONE };         // ����������
public:
	// ����������� � �����������
	MemoryExcept(MEMORY_EXCEPT exception_) : exception(exception_) {}

	// ���������� ������������� ������� ���������� ��������� <<
	// ��� ������ ��������� ���������� �� �����
	friend std::ostream& operator<<(std::ostream& out, const MemoryExcept& memoryExcept);
};

// ������������� ������� ���������� ��������� << ��� ������ ��������� ���������� �� �����
std::ostream& operator<<(std::ostream& out, const MemoryExcept& memoryExcept) {
	switch (memoryExcept.exception)
	{
	case MEMORY_EXCEPT::NONE: {
		out << " �����";
		break;
	}
	case MEMORY_EXCEPT::NOT_ENOUGH_STACK_MEMORY: {
		out << " ������������ �������� ������";
		break;
	}
	case MEMORY_EXCEPT::NOT_ENOUGH_DYNAMIC_MEMORY: {
		out << " ������������ ������������ ������";
		break;
	}
	case MEMORY_EXCEPT::DYNAMIC_MEMORY_IS_NOT_ALLOCATED: {
		out << " ������������ ������ �� ��������";
		break;
	}
	case MEMORY_EXCEPT::THE_ALLOCATED_DYNAMIC_MEMORY_WAS_NOT_DELETED: {
		out << " ���������� ������������ ������ �� �������";
		break;
	}
	}
	return out;
}

// �������� ����� ���������� ������ � �������������� �����������
class MemoryExceptions : public MainParentException<MemoryExcept> {
public:
	// ����������� ��������� ������ � �����������,
	// �������� ����������� ������������� ������
	MemoryExceptions(MemoryExcept exception_, int lineNumber_, const char* nameFile_) :
		MainParentException(exception_, lineNumber_, nameFile_)
	{}
};

