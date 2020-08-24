// DZ_ST_C++_07_dz22_vstrecha22_zadanie2_FileExceptions.h
#pragma once
#include <iostream>
#include "DZ_ST_C++_07_dz22_vstrecha22_zadanie2_MainParentException.h"


// �����-������������ ����� ���������� ������
enum class FILE_EXCEPT {
	NONE,										// ����� - �������� ��� �������������
	THE_FILE_IS_NOT_CREATED,					// ���� �� ������
	THE_FILE_IS_NOT_OPEN,						// ���� �� ������
	THE_FILE_IS_NOT_CLOSED,						// ���� �� ������
	THE_FILE_IS_NOT_AVAILABLE,					// ���� �� ��������
	THE_FILE_IS_NOT_READABLE,					// ���� �� �������� ��� ������
	THE_FILE_IS_NOT_WRITABLE,					// ���� �� �������� ��� ������
};

// ����� ���������� ���������� ������
class FileExcept {
private:
	FILE_EXCEPT exception{ FILE_EXCEPT::NONE };         // ����������
public:
	// ����������� � �����������
	FileExcept(FILE_EXCEPT exception_) : exception(exception_) {}

	// ���������� ������������� ������� ���������� ��������� <<
	// ��� ������ ��������� ���������� �� �����
	friend std::ostream& operator<<(std::ostream& out, const FileExcept& fileExcept);
};

// ������������� ������� ���������� ��������� << ��� ������ ��������� ���������� �� �����
std::ostream& operator<<(std::ostream& out, const FileExcept& fileExcept) {
	switch (fileExcept.exception)
	{
	case FILE_EXCEPT::NONE: {
		out << " �����";
		break;
	}
	case FILE_EXCEPT::THE_FILE_IS_NOT_CREATED: {
		out << " ���� �� ������";
		break;
	}
	case FILE_EXCEPT::THE_FILE_IS_NOT_OPEN: {
		out << " ���� �� ������";
		break;
	}
	case FILE_EXCEPT::THE_FILE_IS_NOT_CLOSED: {
		out << " ���� �� ������";
		break;
	}
	case FILE_EXCEPT::THE_FILE_IS_NOT_AVAILABLE: {
		out << " ���� �� ��������";
		break;
	}
	case FILE_EXCEPT::THE_FILE_IS_NOT_READABLE: {
		out << " ���� �� �������� ��� ������";
		break;
	}
	case FILE_EXCEPT::THE_FILE_IS_NOT_WRITABLE: {
		out << " ���� �� �������� ��� ������";
		break;
	}
	}
	return out;
}

// �������� ����� ���������� ������ � �������������� �����������
class FileExceptions : public MainParentException<FileExcept> {
public:
	// ����������� ��������� ������ � �����������,
	// �������� ����������� ������������� ������
	FileExceptions(FileExcept exception_, int lineNumber_, const char* nameFile_) :
		MainParentException(exception_, lineNumber_, nameFile_)
	{}
};

