// DZ_ST_C++_07_dz23_vstrecha23_zadanie_Time.h
//
// задание 1 из файла Domasnee_zadanie_1594661480.txt
// Выполните домашние задания после уроков 3, 4, 5
// Урок 5. Задание 1
/*
1. Создайте класс Время, в котором реализованы операции
сложения, вычитания, сравнения, ввода и вывода на экран,
возможность конвертации времени из американского формата
am (pm): 10:00 pm = 22:00, 12:00 pm =00:00.
*/
#pragma once
#include <iostream>

namespace datetime
{
	// КЛАСС Время
	class Time {
	private:
		size_t hour{ 0 };
		size_t minute{ 0 };
		size_t second{ 0 };
	public:
		enum class AT { am, pm };

		// КОНСТРУКТОР по умолчанию
		Time() {
			//	std::cout << " Конструктор Time() по умолчанию" << std::endl;
		}

		// КОНСТРУКТОР с параметрами
		Time(size_t hour_, size_t minute_ = 0, size_t second_ = 0) {
			//	std::cout << " Конструктор Time() с параметрами" << std::endl;
			if (verifyTime(hour_, minute_, second_)) exit(5);
			else {
				hour = hour_;
				minute = minute_;
				second = second_;
			}
		}

		// КОНСТРУКТОР с параметрами №2
		Time(AT at, size_t hour_, size_t minute_ = 0, size_t second_ = 0) {
			//	std::cout << " Конструктор Time() с параметрами №2" << std::endl;

			if (at == Time::AT::pm) hour_ += 12;

			if (verifyTime(hour_, minute_, second_)) exit(5);
			else {
				hour = hour_;
				minute = minute_;
				second = second_;
			}
		}

		// Конструктор копирования
		Time(const Time& time) {
			//	std::cout << " Конструктор Time() копирования" << std::endl;

			this->hour = time.hour;
			this->minute = time.minute;
			this->second = time.second;
		}

		// Деструктор
		~Time() {
			//	std::cout << " Деструктор ~Time()" << std::endl;
		}

		static bool verifyTime(size_t hour_, size_t minute_ = 0, size_t second_ = 0) {
			bool error{ false };
			if (!((0 <= hour_) && (hour_ < 24))) {
				std::cout << " Значение часов { " << hour_ << " } не входит в разрешенный диапазон 0 <= Часы < 24" << std::endl;
				error = true;
			}

			if (!((0 <= minute_) && (minute_ < 60))) {
				std::cout << " Значение минут { " << minute_ << " } не входит в разрешенный диапазон 0 <= Минуты < 60" << std::endl;
				error = true;
			}

			if (!((0 <= second_) && (second_ < 60))) {
				std::cout << " Значение секунд { " << second_ << " } не входит в разрешенный диапазон 0 <= Секунды < 60" << std::endl;
				error = true;
			}
			return error;
		}

		// метод присвоения значения объекту перегрузкой оператора =
		Time operator=(const Time& time) {
			std::cout << " Перегрузка оператора = - присвоение значения" << std::endl;
			this->hour = time.hour;
			this->minute = time.minute;
			this->second = time.second;
			return *this;
		}

		// прототип дружественной функции вывода объекта в консоль перегрузкой оператора <<
		friend std::ostream& operator<<(std::ostream& out, const Time& time);

		// прототип дружественной функции ввода объекта с консоли перегрузкой оператора >>
		friend std::istream& operator>>(std::istream& in, Time& time);

		// прототип дружественной функции перегрузки оператора +
		friend Time operator+(const Time& time1, const Time& time2);

		// прототип дружественной функции перегрузки оператора -
		friend Time operator-(const Time& time1, const Time& time2);

		// прототип дружественной функции перегрузки оператора ==
		friend bool operator==(const Time& time1, const Time& time2);

		// прототип дружественной функции перегрузки оператора !=
		friend bool operator!=(const Time& time1, const Time& time2);

		// прототип дружественной функции перегрузки оператора >
		friend bool operator>(const Time& time1, const Time& time2);

		// прототип дружественной функции перегрузки оператора <
		friend bool operator<(const Time& time1, const Time& time2);

	};
	// Конец КЛАССА Время

}