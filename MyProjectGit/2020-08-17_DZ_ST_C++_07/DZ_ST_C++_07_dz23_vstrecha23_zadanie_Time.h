// DZ_ST_C++_07_dz23_vstrecha23_zadanie_Time.h
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

namespace datetime
{
	// ����� �����
	class Time {
	private:
		size_t hour{ 0 };
		size_t minute{ 0 };
		size_t second{ 0 };
	public:
		enum class AT { am, pm };

		// ����������� �� ���������
		Time() {
			//	std::cout << " ����������� Time() �� ���������" << std::endl;
		}

		// ����������� � �����������
		Time(size_t hour_, size_t minute_ = 0, size_t second_ = 0) {
			//	std::cout << " ����������� Time() � �����������" << std::endl;
			if (verifyTime(hour_, minute_, second_)) exit(5);
			else {
				hour = hour_;
				minute = minute_;
				second = second_;
			}
		}

		// ����������� � ����������� �2
		Time(AT at, size_t hour_, size_t minute_ = 0, size_t second_ = 0) {
			//	std::cout << " ����������� Time() � ����������� �2" << std::endl;

			if (at == Time::AT::pm) hour_ += 12;

			if (verifyTime(hour_, minute_, second_)) exit(5);
			else {
				hour = hour_;
				minute = minute_;
				second = second_;
			}
		}

		// ����������� �����������
		Time(const Time& time) {
			//	std::cout << " ����������� Time() �����������" << std::endl;

			this->hour = time.hour;
			this->minute = time.minute;
			this->second = time.second;
		}

		// ����������
		~Time() {
			//	std::cout << " ���������� ~Time()" << std::endl;
		}

		static bool verifyTime(size_t hour_, size_t minute_ = 0, size_t second_ = 0) {
			bool error{ false };
			if (!((0 <= hour_) && (hour_ < 24))) {
				std::cout << " �������� ����� { " << hour_ << " } �� ������ � ����������� �������� 0 <= ���� < 24" << std::endl;
				error = true;
			}

			if (!((0 <= minute_) && (minute_ < 60))) {
				std::cout << " �������� ����� { " << minute_ << " } �� ������ � ����������� �������� 0 <= ������ < 60" << std::endl;
				error = true;
			}

			if (!((0 <= second_) && (second_ < 60))) {
				std::cout << " �������� ������ { " << second_ << " } �� ������ � ����������� �������� 0 <= ������� < 60" << std::endl;
				error = true;
			}
			return error;
		}

		// ����� ���������� �������� ������� ����������� ��������� =
		Time operator=(const Time& time) {
			std::cout << " ���������� ��������� = - ���������� ��������" << std::endl;
			this->hour = time.hour;
			this->minute = time.minute;
			this->second = time.second;
			return *this;
		}

		// �������� ������������� ������� ������ ������� � ������� ����������� ��������� <<
		friend std::ostream& operator<<(std::ostream& out, const Time& time);

		// �������� ������������� ������� ����� ������� � ������� ����������� ��������� >>
		friend std::istream& operator>>(std::istream& in, Time& time);

		// �������� ������������� ������� ���������� ��������� +
		friend Time operator+(const Time& time1, const Time& time2);

		// �������� ������������� ������� ���������� ��������� -
		friend Time operator-(const Time& time1, const Time& time2);

		// �������� ������������� ������� ���������� ��������� ==
		friend bool operator==(const Time& time1, const Time& time2);

		// �������� ������������� ������� ���������� ��������� !=
		friend bool operator!=(const Time& time1, const Time& time2);

		// �������� ������������� ������� ���������� ��������� >
		friend bool operator>(const Time& time1, const Time& time2);

		// �������� ������������� ������� ���������� ��������� <
		friend bool operator<(const Time& time1, const Time& time2);

	};
	// ����� ������ �����

}