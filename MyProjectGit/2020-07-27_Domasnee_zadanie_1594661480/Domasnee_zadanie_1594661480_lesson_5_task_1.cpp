// задание 1 из файла Domasnee_zadanie_1594661480.txt
// Выполните домашние задания после уроков 3, 4, 5
// Урок 5. Задание 1
/*
1. Создайте класс Время, в котором реализованы операции
сложения, вычитания, сравнения, ввода и вывода на экран,
возможность конвертации времени из американского формата
am (pm): 10:00 pm = 22:00, 12:00 pm =00:00.
*/

#include <iostream>
#include <clocale>
using namespace std;

// КЛАСС Время
class Time {
private:
	size_t hour{ 0 };
	size_t minute{ 0 };
	size_t second{ 0 };
public:
	enum class AT{am, pm};

	// КОНСТРУКТОР по умолчанию
	Time(){
		cout << " Конструктор Time() по умолчанию" << endl;
	}

	// КОНСТРУКТОР с параметрами
	Time(size_t hour_, size_t minute_ = 0, size_t second_ = 0) {
		cout << " Конструктор Time() с параметрами" << endl;
		if (verifyTime(hour_, minute_, second_)) exit(5);
		else {
			hour = hour_;
			minute = minute_;
			second = second_;
		}
	}

	// КОНСТРУКТОР с параметрами №2
	Time(AT at, size_t hour_, size_t minute_ = 0, size_t second_ = 0) {
		cout << " Конструктор Time() с параметрами №2" << endl;

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
		cout << " Конструктор Time() копирования" << endl;

		this->hour = time.hour;
		this->minute = time.minute;
		this->second = time.second;
	}

	// Деструктор
	~Time() {
		cout << " Деструктор ~Time()" << endl;
	}

	static bool verifyTime(size_t hour_, size_t minute_ = 0, size_t second_ = 0) {
		bool error{ false };
		if (!((0 <= hour_) && (hour_ < 24))) {
			cout << " Значение часов { " << hour_ << " } не входит в разрешенный диапазон 0 <= Часы < 24" << endl;
			error = true;
		}

		if (!((0 <= minute_) && (minute_ < 60))) {
			cout << " Значение минут { " << minute_ << " } не входит в разрешенный диапазон 0 <= Минуты < 60" << endl;
			error = true;
		}

		if (!((0 <= second_) && (second_ < 60))) {
			cout << " Значение секунд { " << second_ << " } не входит в разрешенный диапазон 0 <= Секунды < 60" << endl;
			error = true;
		}
		return error;
	}

	// метод присвоения значения объекту перегрузкой оператора =
	Time operator=(const Time& time) {
		cout << " Перегрузка оператора = - присвоение значения" << endl;
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


// дружественная функция вывода объекта в консоль перегрузкой оператора <<
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


// дружественная функция вывода объекта в консоль перегрузкой оператора >>
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


// Дружественная ФУНКЦИЯ перегрузки оператора +
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

// Дружественная ФУНКЦИЯ перегрузки оператора -
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

// Дружественная ФУНКЦИЯ перегрузки оператора ==
bool operator==(const Time& time1, const Time& time2) {
	return
		(time1.hour == time2.hour) &&
		(time1.minute == time2.minute) &&
		(time1.second == time2.second);
}

// Дружественная ФУНКЦИЯ перегрузки оператора !=
bool operator!=(const Time& time1, const Time& time2) {
	return
		(time1.hour != time2.hour) ||
		(time1.minute != time2.minute) ||
		(time1.second != time2.second);
}

// Дружественная ФУНКЦИЯ перегрузки оператора >
bool operator>(const Time& time1, const Time& time2) {
	return
		(time1.hour > time2.hour) ||
		((time1.hour == time2.hour) && (time1.minute > time2.minute)) ||
		((time1.hour == time2.hour) && (time1.minute == time2.minute) && (time1.second > time2.second));
}

// Дружественная ФУНКЦИЯ перегрузки оператора <
bool operator<(const Time& time1, const Time& time2) {
	return
		(time1.hour < time2.hour) ||
		((time1.hour == time2.hour) && (time1.minute < time2.minute)) ||
		((time1.hour == time2.hour) && (time1.minute == time2.minute) && (time1.second < time2.second));
}


// ГЛАВНАЯ ФУНКЦИЯ
int main() {
	setlocale(LC_ALL, "ru");

	Time time1;
	cout << " time1: " << time1 << endl;
	cout << endl;

	Time time2(13, 34, 35);
	cout << " time2: " << time2 << endl;
	cout << endl;

	Time time3(time2);
	cout << " time3: " << time3 << endl;
	cout << endl;

	Time time4 = time2;
	cout << " time4: " << time4 << endl;
	cout << endl;

	Time time5;
	time5 = time2;
	cout << " time5: " << time5 << endl;
	cout << endl;

	Time time6 = time2 + time3;
	cout << " time6 = time2 + time3 == " << time6 << endl;
	cout << endl;

	Time time7;
	time7 = time2 + time6;
	cout << " time7 = time2 + time6 == " << time7 << endl;
	cout << endl;

	Time time8 = time6 - time5;
	cout << " time8 = time6 - time5 == " << time8 << endl;
	cout << endl;

	// сравним объекты на равенство
	cout
		<< " Сравним объекты на равенство >>> \n"
		<< " Время " << time1
		<< (time1 == time2 ? "" : " не")
		<< " равно Времени " << time2
		<< endl;
	cout << endl;

	// сравним объекты на равенство
	cout
		<< " Сравним объекты на равенство >>> \n"
		<< " Время " << time3
		<< (time3 == time2 ? "" : " не")
		<< " равно Времени " << time2
		<< endl;
	cout << endl;

	// сравним объекты на неравенство
	cout
		<< " Сравним объекты на неравенство >>> \n"
		<< " Время " << time5
		<< (time5 != time2 ? " не" : "")
		<< " равно Времени " << time2
		<< endl;
	cout << endl;

	// сравним объекты на неравенство
	cout
		<< " Сравним объекты на неравенство >>> \n"
		<< " Время " << time6
		<< (time6 != time2 ? " не" : "")
		<< " равно Времени " << time2
		<< endl;
	cout << endl;

	// сравним объекты на больше
	cout
		<< " Сравним объекты на больше >>> \n"
		<< " Время " << time7
		<< (time7 > time2 ? "" : " не")
		<< " больше Времени " << time2
		<< endl;
	cout << endl;

	// сравним объекты на больше
	cout
		<< " Сравним объекты на больше >>> \n"
		<< " Время " << time6
		<< (time6 > time2 ? "" : " не")
		<< " больше Времени " << time2
		<< endl;
	cout << endl;

	// сравним объекты на меньше
	cout
		<< " Сравним объекты на меньше >>> \n"
		<< " Время " << time7
		<< (time7 < time2 ? "" : " не")
		<< " меньше Времени " << time2
		<< endl;
	cout << endl;

	// сравним объекты на меньше
	cout
		<< " Сравним объекты на меньше >>> \n"
		<< " Время " << time6
		<< (time6 < time2 ? "" : " не")
		<< " меньше Времени " << time2
		<< endl;
	cout << endl;

	// введем американское время - до полудня
	Time time9(Time::AT::am, 10);
	cout << " time9 по американски, 10:00 am: " << time9 << endl;
	cout << endl;

	// введем американское время - после полудня
	Time time10(Time::AT::pm, 10);
	cout << " time10 по американски, 10:00 pm: " << time10 << endl;
	cout << endl;

	// введем время
	cout << " Введите через пробелы: часы минуты секунды\n в диапазоне: 00 00 00 - 23 59 59 >>> \n";
	cin >> time1;
	cout << " time1: " << time1 << endl;
	cout << endl;

	return 0;
}
// Конец ГЛАВНОЙ ФУНКЦИИ
