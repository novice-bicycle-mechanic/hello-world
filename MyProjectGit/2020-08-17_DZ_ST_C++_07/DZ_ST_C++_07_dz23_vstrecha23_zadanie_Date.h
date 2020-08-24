// DZ_ST_C++_07_dz23_vstrecha23_zadanie_Date.h
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

namespace datetime
{

	class Date {
	private:
		int day{ 0 };
		int month{ 0 };
		int year{ 0 };

		int number{ 0 };

	public:

		// ����������� �� ���������
		Date() {
			//		std::cout << " ����������� �� ���������" << std::endl;
			if (!number) number = Date::numberObject();
		}

		// ����������� � �����������
		Date(int day_, int month_, int year_) : Date() {
			//		std::cout << " ����������� � �����������" << std::endl;
			setData(day_, month_, year_);
		}


		// ����������� �����������
		Date(const Date& date) : Date() {
			//		std::cout << " ����������� �����������" << std::endl;
			this->day = date.day;
			this->month = date.month;
			this->year = date.year;
		}

		~Date() {
			//		std::cout << " ����������" << std::endl;
			Date::numberObject(-1);
		}

	private:
		void setData(int day_, int month_, int year_) {
			if (verifyData(day_, month_, year_)) {
				day = day_;
				month = month_;
				year = year_;
			}
		}


		static bool verifyData(int day_, int month_, int year_) {
			bool leap_year = (year_ == 0) || (year_ % 400 == 0) || ((year_ % 4 == 0) && (year_ % 100 != 0));
			bool day_b{ false };
			bool month_b{ false };
			bool year_b{ false };

			if ((1970 <= year_) && (year_ <= 2038)) year_b = true;
			else {
				std::cout << " ����� ���� �� ������ � ����������� �������� 1970-2038" << std::endl;
				return false;
			}

			if ((1 <= month_) && (month_ <= 12)) month_b = true;
			else {
				std::cout << " ����� ������ �� ������ � ����������� �������� 1-12" << std::endl;
				return false;
			}

			switch (month_)
			{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
			{
				if ((1 <= day_) && (day_ <= 31)) day_b = true;
				else {
					std::cout << " ����� ��� �� ������ � ����������� �������� 1-31" << std::endl;
					return false;
				}
				break;
			}
			case 4:
			case 6:
			case 9:
			case 11:
			{
				if ((1 <= day_) && (day_ <= 30)) day_b = true;
				else {
					std::cout << " ����� ��� �� ������ � ����������� �������� 1-30" << std::endl;
					return false;
				}
				break;
			}
			case 2:
			{
				if ((1 <= day_) && (day_ <= (leap_year ? 29 : 28))) day_b = true;
				else {
					std::cout << " ����� ��� �� ������ � ����������� �������� 1-" << (leap_year ? 29 : 28) << std::endl;
					return false;
				}
				break;
			}
			default:
			{
				std::cout << " ����� ������ �� ������ � ����������� �������� 1-12" << std::endl;
				return false;
				break;
			}
			}
			return (year_b && month_b && year_b);
		}

		// ����������� ����� ��������� ��������
		static int numberObject(int key = 1) {
			static int counter{ 0 };
			return counter += key;
		}

	public:

		// ����� ���������� ���� �� 1 ����
		void increase() {
			bool leap_year = (year == 0) || (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));

			++day;

			switch (month)
			{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
			{
				if (day > 31) {
					day = 1;
					++month;
				}
				break;
			}
			case 4:
			case 6:
			case 9:
			case 11:
			{
				if (day > 30) {
					day = 1;
					++month;
				}
				break;
			}
			case 2:
			{
				if (day > (leap_year ? 29 : 28)) {
					day = 1;
					++month;
				}
				break;
			}
			}

			if (month > 12) ++year;
		}

		// ����� ��������� ���� �� 1 ����
		void reduce() {
			bool leap_year = (year == 0) || (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));

			--day;

			if (day < 1) {
				--month;
				switch (month)
				{
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:
				{
					day = 31;
					break;
				}
				case 4:
				case 6:
				case 9:
				case 11:
				{
					day = 30;
					break;
				}
				case 2:
				{
					day = leap_year ? 29 : 28;
					break;
				}
				}
			}

			if (month < 1) --year;
		}

		// ����� ���������� ��������� ������ ������� ()
		// ���������� ����� �������
		int operator()(void) const { return number; }

		// ����� ���������� �������� ������� ����������� ��������� =
		Date operator=(const Date& date) {
			this->day = date.day;
			this->month = date.month;
			this->year = date.year;
			return *this;
		}

		// ����� ���������� ��������� ++C
		Date& operator++() {
			this->increase();
			return *this;
		}

		// ����� ���������� ��������� --C
		Date& operator--() {
			this->reduce();
			return *this;
		}

		// ����� ���������� ��������� C++
		Date operator++(int) {
			Date temp(*this);
			this->increase();
			return temp;
		}

		// ����� ���������� ��������� C--
		Date operator--(int) {
			Date temp(*this);
			this->reduce();
			return temp;
		}

		// ����� ���������� ��������� +=
		Date& operator+=(int value) {
			if (value >= 0) {
				for (int i = 0; i < value; i++) {
					this->increase();
				}
			}
			else {
				for (int i = 0; i > value; i--) {
					this->reduce();
				}
			}
			return *this;
		}

		// ����� ���������� ��������� -=
		Date& operator-=(int value) {
			if (value >= 0) {
				for (int i = 0; i < value; i++) {
					this->reduce();
				}
			}
			else {
				for (int i = 0; i > value; i--) {
					this->increase();
				}
			}
			return *this;
		}

		// �������� ������������� ������� ������ ������� � ������� ����������� ��������� <<
		friend std::ostream& operator<<(std::ostream& out, const Date& date);

		// �������� ������������� ������� ������ ������� � ������� ����������� ��������� >>
		friend std::istream& operator>>(std::istream& in, Date& date);

		// �������� ������������� ������� ���������� ��������� ==
		friend bool operator==(const Date& date1, const Date& date2);

		// �������� ������������� ������� ���������� ��������� !=
		friend bool operator!=(const Date& date1, const Date& date2);

		// �������� ������������� ������� ���������� ��������� >
		friend bool operator>(const Date& date1, const Date& date2);

		// �������� ������������� ������� ���������� ��������� <
		friend bool operator<(const Date& date1, const Date& date2);
	};
}
