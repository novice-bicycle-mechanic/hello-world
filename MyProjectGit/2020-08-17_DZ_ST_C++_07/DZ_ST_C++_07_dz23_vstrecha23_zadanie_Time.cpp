// DZ_ST_C++_07_dz23_vstrecha23_zadanie_Time.cpp
//
// ������� 1 �� ����� Domasnee_zadanie_1594661480.txt
// ��������� �������� ������� ����� ������ 3, 4, 5
// ���� 5. ������� 1
/*
1. �������� ����� �����, � ������� ����������� ��������
��������, ���������, ���������, ����� � ������ �� �����,
����������� ����������� ������� �� ������������� �������
am (pm): 10:00 pm = 22:00, 12:00 pm =00:00.
*/
#pragma once
#include <iostream>
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_Time.h"

namespace datetime
{

	// ������������� ������� ������ ������� � ������� ����������� ��������� <<
	std::ostream& operator<<(std::ostream& out, const Time& time) {
		out
			<< (time.hour < 10 ? "0" : "")
			<< time.hour
			<< ":"
			<< (time.minute < 10 ? "0" : "")
			<< time.minute
			<< ":"
			<< (time.second < 10 ? "0" : "")
			<< time.second
			;
		return out;
	}


	// ������������� ������� ������ ������� � ������� ����������� ��������� >>
	std::istream& operator>>(std::istream& in, Time& time1) {
		Time temp;
		in >> temp.hour;
		in >> temp.minute;
		in >> temp.second;

		if (!(Time::verifyTime(temp.hour, temp.minute, temp.second))) {
			time1 = temp;
			return in;
		}
		else return in;
	}


	// ������������� ������� ���������� ��������� +
	Time operator+(const Time& time1, const Time& time2) {
		Time time3;
		size_t buffer_hour{ 0 };
		size_t buffer_minute{ 0 };

		time3.second = (
			(time1.second + time2.second) > 60 ?
			(++buffer_minute, time1.second + time2.second - 60) :
			(time1.second + time2.second)
			);

		time3.minute = (
			(time1.minute + time2.minute + buffer_minute) > 60 ?
			(++buffer_hour, time1.minute + time2.minute + buffer_minute - 60) :
			(time1.minute + time2.minute + buffer_minute)
			);

		time3.hour = (
			(time1.hour + time2.hour + buffer_hour) > 23 ?
			(time1.hour + time2.hour + buffer_hour - 24) :
			(time1.hour + time2.hour + buffer_hour)
			);

		return time3;
	}

	// ������������� ������� ���������� ��������� -
	Time operator-(const Time& timeFirst, const Time& timeSecond) {
		Time time1;
		Time time2;
		Time time3;

		if (timeFirst > timeSecond) {
			time1 = timeFirst;
			time2 = timeSecond;
		}
		else {
			time2 = timeFirst;
			time1 = timeSecond;
		}

		time3.hour = time1.hour - time2.hour;
		time3.minute = time1.minute - time2.minute;
		time3.second = time1.second - time2.second;

		return time3;
	}

	// ������������� ������� ���������� ��������� ==
	bool operator==(const Time& time1, const Time& time2) {
		return
			(time1.hour == time2.hour) &&
			(time1.minute == time2.minute) &&
			(time1.second == time2.second);
	}

	// ������������� ������� ���������� ��������� !=
	bool operator!=(const Time& time1, const Time& time2) {
		return
			(time1.hour != time2.hour) ||
			(time1.minute != time2.minute) ||
			(time1.second != time2.second);
	}

	// ������������� ������� ���������� ��������� >
	bool operator>(const Time& time1, const Time& time2) {
		return
			(time1.hour > time2.hour) ||
			((time1.hour == time2.hour) && (time1.minute > time2.minute)) ||
			((time1.hour == time2.hour) && (time1.minute == time2.minute) && (time1.second > time2.second));
	}

	// ������������� ������� ���������� ��������� <
	bool operator<(const Time& time1, const Time& time2) {
		return
			(time1.hour < time2.hour) ||
			((time1.hour == time2.hour) && (time1.minute < time2.minute)) ||
			((time1.hour == time2.hour) && (time1.minute == time2.minute) && (time1.second < time2.second));
	}

}
