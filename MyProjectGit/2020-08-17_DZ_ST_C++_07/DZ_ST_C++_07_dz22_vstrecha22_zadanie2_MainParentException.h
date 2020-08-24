// DZ_ST_C++_07_dz22_vstrecha22_zadanie2_MainParentException.h
#pragma once
#include <iostream>


// ������� ������������ �����-������ ����������
template <typename T>
class MainParentException {
private:
	T exception;                      // ����������
	int lineNumber{ 0 };              // ����� ������ ��������� ����������
	const char* nameFile;             // ��� ����� ��������� ����������
public:
	// ����������� � �����������
	MainParentException(T exception_, int lineNumber_, const char* nameFile_) :
		exception(exception_), lineNumber(lineNumber_), nameFile(nameFile_)
	{}

	// ����� ���������� ��������� << ��� ������ �� �����
	// ��������� ���������� � �������������� �����������
	friend std::ostream& operator<<(std::ostream& out, const MainParentException<T>& except) {
		out << " ������!\n"
			<< " ���� " << except.nameFile << "\n"
			<< " ������ " << except.lineNumber << ": "
			<< except.exception
			;
		return out;
	}

};

