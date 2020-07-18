// задание из файла DZ_ST_C++_03.pdf
// Встреча №10
// Тема: Перегрузка операторов глобальными функциями,
//       дружественные функции, дружественная перегрузка,
//       перегрузка ввода - вывода
// Задание.
/*
Создайте класс с именем Date для хранения даты
(или используйте ранее созданный).
В классе должна быть функция-член, которая увеличивает день на 1.
Напишите соответствующие конструкторы и функции-члены.
В классе должны быть перегружены операции:
++, -- ,!=, ==, >, <, >>, <<, =, +=, -=, ().
Используйте обычную и дружественную перегрузку.
*/

#include <iostream>
#include <clocale>
#include <ctime>
using namespace std;


class Date {
private:
	int day{ 0 };
	int month{ 0 };
	int year{ 0 };
	
	int number{ 0 };

public:

	// КОНСТРУКТОР по умолчанию
	Date(){
//		cout << " Конструктор по умолчанию" << endl;
		if (!number) number = Date::numberObject();
	}

	// КОНСТРУКТОР с параметрами
	Date(int day_, int month_, int year_) : Date() {
//		cout << " Конструктор с параметрами" << endl;
		setData(day_, month_, year_);
	}


	// КОНСТРУКТОР копирования
	Date(const Date& date) : Date() {
//		cout << " Конструктор копирования" << endl;
		this->day = date.day;
		this->month = date.month;
		this->year = date.year;
	}

	~Date() {
//		cout << " Деструктор" << endl;
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
			cout << " Номер года не входит в разрешенный диапазон 1970-2038" << endl;
			return false;
		}

		if ((1 <= month_) && (month_ <= 12)) month_b = true;
		else {
			cout << " Номер месяца не входит в разрешенный диапазон 1-12" << endl;
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
				cout << " Номер дня не входит в разрешенный диапазон 1-31" << endl;
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
				cout << " Номер дня не входит в разрешенный диапазон 1-30" << endl;
				return false;
			}
			break;
		}
		case 2:
		{
			if ((1 <= day_) && (day_ <= (leap_year ? 29 : 28))) day_b = true;
			else {
				cout << " Номер дня не входит в разрешенный диапазон 1-" << (leap_year ? 29 : 28) << endl;
				return false;
			}
			break;
		}
		default:
		{
			cout << " Номер месяца не входит в разрешенный диапазон 1-12" << endl;
			return false;
			break;
		}
		}
		return (year_b && month_b && year_b);
	}

	// статический метод нумерации объектов
	static int numberObject(int key = 1) {
		static int counter{ 0 };
		return counter += key;
	}

public:
	
	// метод увеличения даты на 1 день
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

	// метод уменьшить дату на 1 день
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

	// метод перегрузки оператора вызова функции ()
	// возвращает номер объекта
	int operator()(void) const { return number; }

	// метод присвоения значения объекта перегрузкой оператора =
	Date operator=(const Date& date) {
		this->day = date.day;
		this->month = date.month;
		this->year = date.year;
		return *this;
	}

	// метод перегрузки оператора ++C
	Date& operator++() {
		this->increase();
		return *this;
	}

	// метод перегрузки оператора --C
	Date& operator--() {
		this->reduce();
		return *this;
	}

	// метод перегрузки оператора C++
	Date operator++(int) {
		Date temp(*this);
		this->increase();
		return temp;
	}

	// метод перегрузки оператора C--
	Date operator--(int) {
		Date temp(*this);
		this->reduce();
		return temp;
	}

	// метод перегрузки оператора +=
	Date& operator+=(int value) {
		if (value >= 0) {
			for (int i = 0; i < value; i++)	{
				this->increase();
			}
		}
		else {
			for (int i = 0; i > value; i--)	{
				this->reduce();
			}
		}
		return *this;
	}

	// метод перегрузки оператора -=
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

	// прототип дружественной функции вывода объекта в консоль перегрузкой оператора <<
	friend std::ostream& operator<<(std::ostream& out, const Date& date);

	// прототип дружественной функции вывода объекта в консоль перегрузкой оператора >>
	friend std::istream& operator>>(std::istream& in, Date& date);

	// прототип дружественной функции перегрузки оператора ==
	friend bool operator==(const Date& date1, const Date& date2);

	// прототип дружественной функции перегрузки оператора !=
	friend bool operator!=(const Date& date1, const Date& date2);

	// прототип дружественной функции перегрузки оператора >
	friend bool operator>(const Date& date1, const Date& date2);

	// прототип дружественной функции перегрузки оператора <
	friend bool operator<(const Date& date1, const Date& date2);
};

// дружественная функция вывода объекта в консоль перегрузкой оператора <<
std::ostream& operator<<(std::ostream& out, const Date& date) {
	out
		<< (date.day < 10 ? "0" : "")
		<< date.day
		<< "."
		<< (date.month < 10 ? "0" : "")
		<< date.month
		<< "."
		<< ( date.year < 10 ? "000" :
			(date.year < 100 ? "00" :
			(date.year < 1000 ? "0" : "")))
		<< date.year;
	return out;
}

// дружественная функция вывода объекта в консоль перегрузкой оператора >>
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

// Дружественная ФУНКЦИЯ перегрузки оператора ==
bool operator==(const Date& date1, const Date& date2) {
	return
		(date1.year == date2.year) &&
		(date1.month == date2.month) && 
		(date1.day == date2.day);
}

// Дружественная ФУНКЦИЯ перегрузки оператора !=
bool operator!=(const Date& date1, const Date& date2) {
	return 
		(date1.year != date2.year) ||
		(date1.month != date2.month) ||
		(date1.day != date2.day);
}

// Дружественная ФУНКЦИЯ перегрузки оператора >
bool operator>(const Date& date1, const Date& date2) {
	return
		(date1.year > date2.year) ||
		((date1.year == date2.year) && (date1.month > date2.month)) ||
		((date1.year == date2.year) && (date1.month == date2.month) && (date1.day > date2.day));
}

// Дружественная ФУНКЦИЯ перегрузки оператора <
bool operator<(const Date& date1, const Date& date2) {
	return
		(date1.year < date2.year) ||
		((date1.year == date2.year) && (date1.month < date2.month)) ||
		((date1.year == date2.year) && (date1.month == date2.month) && (date1.day < date2.day));
}

// ГЛАВНАЯ ФУНКЦИЯ
int main() {
	setlocale(LC_ALL, "ru");

	// создание объекта конструктором по умолчанию
	cout << " Создадим объект Дата Конструктором по умолчанию:  ";
	Date date1;
	cout << "Дата == " << date1 << endl;
	cout << endl;

	// вывод номера объекта перегруженным оператором ()
	cout << " Выведем оператором () номер объекта-даты: " << date1() << endl;
	cout << endl;

	// создание объекта конструктором с параметрами
	cout << " Создадим объект Дата Конструктором с параметрами: ";
	Date date2(29, 02, 2000);
	cout << "Дата " << date2() << " == " << date2 << endl;
	cout << endl;

	// создание объекта конструктором копирования
	cout << " Создадим объект Дата Конструктором копирования копированием Даты " << date2() << " >>>" << endl;
	Date date3(date2);
	cout << " Дата " << date3() << " == " << date3 << endl;
	cout << endl;

	// присвоение значений объекту перегруженным оператором =
	cout << " Присвоим объекту Дата " << date1() << " значение объекта Дата" << date2() << ": ";
	date1 = date2;
	cout << "Дата " << date1() << " == " << date1 << endl;
	cout << endl;

	// изменение значения объекта перегруженным оператором ++C
	cout << " Изменим значение объекта Дата " << date1() << " == " << date1 << " оператором ++С >>> " << endl;
	cout << " Дата " << date1() << " == " << ++date1 << endl;
	cout << endl;

	// изменение значения объекта перегруженным оператором --C
	cout << " Изменим значение объекта Дата " << date1() << " == " << date1 << " оператором --С >>> " << endl;
	cout << " Дата " << date1() << " == " << --date1 << endl;
	cout << endl;

	// изменение значения объекта перегруженным оператором C++
	cout << " Изменим значение объекта Дата " << date1() << " == " << date1 << " оператором С++ >>> " << endl;
	cout << " Возвращенное значение: Дата " << date1() << " == " << date1++ << endl;
	cout << " Измененное значение  : Дата " << date1() << " == " << date1 << endl;
	cout << endl;

	// изменение значения объекта перегруженным оператором C--
	cout << " Изменим значение объекта Дата " << date1() << " == " << date1 << " оператором С-- >>> " << endl;
	cout << " Возвращенное значение: Дата " << date1() << " == " << date1-- << endl;
	cout << " Измененное значение  : Дата " << date1() << " == " << date1 << endl;
	cout << endl;

	int value{ 0 };

	// изменение значения объекта перегруженным оператором +=
	value = 20;
	cout
		<< " Изменим значение объекта Дата " << date1() << " == " << date1
		<< " оператором += на " << value << " >>> " << endl;
	cout << " Дата " << date1() << " == " << (date1 += value) << endl;
	cout << endl;

	// изменение значения объекта перегруженным оператором +=
	value = -5;
	cout
		<< " Изменим значение объекта Дата " << date1() << " == " << date1
		<< " оператором += на " << value << " >>> " << endl;
	cout << " Дата " << date1() << " == " << (date1 += value) << endl;
	cout << endl;

	// изменение значения объекта перегруженным оператором -=
	value = 10;
	cout
		<< " Изменим значение объекта Дата " << date1() << " == " << date1
		<< " оператором -= на " << value << " >>> " << endl;
	cout << " Дата " << date1() << " == " << (date1 -= value) << endl;
	cout << endl;

	// изменение значения объекта перегруженным оператором -=
	value = -20;
	cout
		<< " Изменим значение объекта Дата " << date1() << " == " << date1
		<< " оператором -= на " << value << " >>> " << endl;
	cout << " Дата " << date1() << " == " << (date1 -= value) << endl;
	cout << endl;

	// сравним объекты на равенство
	cout
		<< " Сравним объекты на равенство >>> \n" 
		<< " Дата " << date1() << " == " << date1
		<< (date1 == date2 ? "" : " не")
		<< " равна Дате " << date2() << " == " << date2
		<< endl;
	cout << endl;

	// сравним объекты на равенство
	cout
		<< " Сравним объекты на равенство >>> \n"
		<< " Дата " << date3() << " == " << date3
		<< (date3 == date2 ? "" : " не")
		<< " равна Дате " << date2() << " == " << date2
		<< endl;
	cout << endl;

	// сравним объекты на неравенство
	cout
		<< " Сравним объекты на неравенство >>> \n"
		<< " Дата " << date1() << " == " << date1
		<< (date1 != date2 ? " не" : "")
		<< " равна Дате " << date2() << " == " << date2
		<< endl;
	cout << endl;

	// сравним объекты на неравенство
	cout
		<< " Сравним объекты на неравенство >>> \n"
		<< " Дата " << date3() << " == " << date3
		<< (date3 != date2 ? " не" : "")
		<< " равна Дате " << date2() << " == " << date2
		<< endl;
	cout << endl;

	// сравним объекты на больше
	cout
		<< " Сравним объекты на больше >>> \n"
		<< " Дата " << date1() << " == " << date1
		<< (date1 > date2 ? "" : " не")
		<< " больше Даты " << date2() << " == " << date2
		<< endl;
	cout << endl;

	// сравним объекты на больше
	cout
		<< " Сравним объекты на больше >>> \n"
		<< " Дата " << date3() << " == " << date3
		<< (date3 > date2 ? "" : " не")
		<< " больше Даты " << date2() << " == " << date2
		<< endl;
	cout << endl;

	// сравним объекты на меньше
	cout
		<< " Сравним объекты на меньше >>> \n"
		<< " Дата " << date2() << " == " << date2
		<< (date2 < date1 ? "" : " не")
		<< " меньше Даты " << date1() << " == " << date1
		<< endl;
	cout << endl;

	// сравним объекты на меньше
	cout
		<< " Сравним объекты на меньше >>> \n"
		<< " Дата " << date2() << " == " << date2
		<< (date2 < date3 ? "" : " не")
		<< " меньше Даты " << date3() << " == " << date3
		<< endl;
	cout << endl;

	// присвоение значения объекту ручным вводом из консоли

	cout << " Введите через пробел параметры Даты " << date1() << " : день месяц год > ";
	cin >> date1;
	cout << " Дата " << date1() << " == " << date1 << endl;
	cout << endl;

	return 0;
}



