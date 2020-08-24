// DZ_ST_C++_07_dz23_vstrecha23_zadanie_Date.cpp
//
// ������� �� ����� DZ_ST_C++_03.pdf
// ������� �10
// ����: ���������� ���������� ����������� ���������,
//       ������������� �������, ������������� ����������,
//       ���������� ����� - ������
// �������.
/*
�������� ����� � ������ Date ��� �������� ����
(��� ����������� ����� ���������).
� ������ ������ ���� �������-����, ������� ����������� ���� �� 1.
�������� ��������������� ������������ � �������-�����.
� ������ ������ ���� ����������� ��������:
++, -- ,!=, ==, >, <, >>, <<, =, +=, -=, ().
����������� ������� � ������������� ����������.
*/
#pragma once
#include <iostream>
#include <ctime>
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_Date.h"


namespace datetime
{
	// ������������� ������� ������ ������� � ������� ����������� ��������� <<
	std::ostream& operator<<(std::ostream& out, const Date& date) {
		out
			<< (date.day < 10 ? "0" : "")
			<< date.day
			<< "."
			<< (date.month < 10 ? "0" : "")
			<< date.month
			<< "."
			<< (date.year < 10 ? "000" :
				(date.year < 100 ? "00" :
					(date.year < 1000 ? "0" : "")))
			<< date.year;
		return out;
	}

	// ������������� ������� ������ ������� � ������� ����������� ��������� >>
	std::istream& operator>>(std::istream& in, Date& date) {
		Date temp;
		in >> temp.day;
		in >> temp.month;
		in >> temp.year;

		if (Date::verifyData(temp.day, temp.month, temp.year)) {
			date = temp;
			return in;
		}
		else return in;
	}

	// ������������� ������� ���������� ��������� ==
	bool operator==(const Date& date1, const Date& date2) {
		return
			(date1.year == date2.year) &&
			(date1.month == date2.month) &&
			(date1.day == date2.day);
	}

	// ������������� ������� ���������� ��������� !=
	bool operator!=(const Date& date1, const Date& date2) {
		return
			(date1.year != date2.year) ||
			(date1.month != date2.month) ||
			(date1.day != date2.day);
	}

	// ������������� ������� ���������� ��������� >
	bool operator>(const Date& date1, const Date& date2) {
		return
			(date1.year > date2.year) ||
			((date1.year == date2.year) && (date1.month > date2.month)) ||
			((date1.year == date2.year) && (date1.month == date2.month) && (date1.day > date2.day));
	}

	// ������������� ������� ���������� ��������� <
	bool operator<(const Date& date1, const Date& date2) {
		return
			(date1.year < date2.year) ||
			((date1.year == date2.year) && (date1.month < date2.month)) ||
			((date1.year == date2.year) && (date1.month == date2.month) && (date1.day < date2.day));
	}
}
