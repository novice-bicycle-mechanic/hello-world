// задание 1 из файла Domasnee_zadanie_1594661480.txt
// Выполните домашние задания после уроков 3, 4, 5
// Урок 3. Задание 1
/*
Создайте класс Date, который будет содержать информацию
о дате (день, месяц, год). С помощью механизма
перегрузки операторов, определите операцию
разности двух дат (результат в виде количества дней
между датами), а также операцию увеличения даты
на определенное количество дней.
*/
// Примечание разработчика:
// класс Date заимствован из DZ_ST_C++_03_vstrecha_10_zadanie_.cpp
// с уже реализованной операцией увеличения даты на n дней
// с исправлением ошибок в методах increase() и reduce()
// (при переходе в другой месяц/год значение месяца/года менялось не всегда)
// Содержание функции operator- заимствовано из файла
// GubinAV_hw4_vstrecha8_zadanie1.cpp с исправлением ошибок copy-paste и
// и изменением логики вычисления разницы - разница теперь математическая.

#include <iostream>
#include <clocale>
using namespace std;


class Date {
private:
	int day{ 0 };
	int month{ 0 };
	int year{ 0 };

	int number{ 0 };

public:

	// КОНСТРУКТОР по умолчанию
	Date() {
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

		if ((1970 <= year_) && (year_ < 2038)) year_b = true;
		else {
			cout << " Номер года не входит в разрешенный диапазон 1970-2037" << endl;
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

		if (month > 12) {
			month = 1;
			++year;
		}
	}

	// метод уменьшить дату на 1 день
	void reduce() {
		bool leap_year = (year == 0) || (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));

		--day;

		if (day < 1) {
			--month;

			if (month < 1) {
				month = 12;
				--year;
			}

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

		if (month < 1) {
			month = 12;
			--year;
		}
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

	// прототип дружественной функции перегрузки оператора -
	friend int operator-(const Date& date1, const Date& date2);

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
		<< (date.year < 10 ? "000" :
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

// Дружественная ФУНКЦИЯ перегрузки оператора -
int operator-(const Date& date1_, const Date& date2_) {

	//-------------- проверка дат на больше-меньше ---------------------------------

	Date dateMax;   // большая дата
	Date dateMin;   // меньшая дата
	int sign{ 0 };  // знак разницы дат

	if (date1_ > date2_) {
		dateMax = date1_;
		dateMin = date2_;
		sign = 1;
	}
	else {
		dateMax = date2_;
		dateMin = date1_;
		sign = -1;
	}

	//---------------- исходные данные -------------------------------------------------

	int year_initial = dateMin.year;				// год начальный

	int month_initial = dateMin.month;				// месяц начальный

	int day_initial = dateMin.day;					// день начальный

	int year_end = dateMax.year;					// год конечный

	int month_end = dateMax.month;					// месяц конечный

	int day_end = dateMax.day;						// день конечный

	int full_years_between_dates = 0;						// полных лет между датами

	int full_months_between_the_date_of_one_year = 0;		// полных месяцев между датами одного года

	int full_days_between_the_date_one_month = 0;			// полных дней между датами одного месяца

	int full_days_to_the_end_of_the_month = 0;				// полных дней до конца месяца

	int full_days_from_the_beginning_of_the_month = 0;		// полных дней с начала месяца

	int full_days_in_full_months_to_the_end_of_the_year = 0;	// полных дней в полных месяцах до конца года

	int full_days_in_full_months_from_the_beginning_of_the_year = 0; // полных дней в полных месяцах с начала года

	int full_days_in_full_years_between_dates = 0;			// полных дней в полных годах между датами

	int full_days_in_the_full_months_between_the_date_of_one_year = 0; // полных дней в полных месяцах между датами одного года

	int total_full_days_between_dates = 0;					// всего полных дней между датами

	int number_of_days_per_month = 0;						// количество дней в месяце

	int number_of_leap_years_between_dates = 0;				// количество високосных годов между датами

	// ключ - год начальный високосный
	bool key_year_initial_high_axis =
		(year_initial == 0) || (year_initial % 400 == 0) ||
		((year_initial % 4 == 0) && (year_initial % 100 != 0));	

	// ключ - год конечный високосный
	bool key_year_end_high_axis =
		(year_end == 0) || (year_end % 400 == 0) ||
		((year_end % 4 == 0) && (year_end % 100 != 0));	

	// массив количества дней в месяцах
	int number_Of_Days_Per_Month[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };


	// -------------- Конец исходных данных -----------------------------------

	full_days_to_the_end_of_the_month =
		((month_initial == 2) ? ((int)key_year_initial_high_axis) : (0)) +
		number_Of_Days_Per_Month[month_initial] - day_initial;

	full_days_from_the_beginning_of_the_month = day_end;

	if (year_end == year_initial)			// год дат один и тот же
	{
		if (month_end == month_initial)				// месяц дат один и тот же
		{
			if (day_end == day_initial)						// день дат один и тот же
			{
				total_full_days_between_dates = 0;
			}
			else											// дни дат разные
			{
				total_full_days_between_dates = day_end - day_initial;
			}
		}
		else										// месяцы дат разные
		{
			if (month_end == month_initial + 1)				// месяцы соседние
			{
				total_full_days_between_dates =
					full_days_to_the_end_of_the_month + full_days_from_the_beginning_of_the_month;
			}
			else											// месяцы не соседние
			{
				for (int i = month_initial + 1; i < month_end; i++)		// сумма дней в полных месяцах
				{
					full_days_in_the_full_months_between_the_date_of_one_year +=
						(number_Of_Days_Per_Month[i] + 
							((i == 2) ? ((int)key_year_initial_high_axis) : (0)));
				}

				total_full_days_between_dates =
					full_days_to_the_end_of_the_month +
					full_days_in_the_full_months_between_the_date_of_one_year +
					full_days_from_the_beginning_of_the_month;
			}
		}
	}
	else									// годы дат разные
	{
		for (int i = month_initial + 1; i <= 12; i++)		// сумма дней в полных месяцах до конца года
		{
			full_days_in_full_months_to_the_end_of_the_year +=
				(number_Of_Days_Per_Month[i] +
					((i == 2) ? ((int)key_year_initial_high_axis) : (0)));
		}

		for (int i = 1; i < month_end; i++)					// сумма дней в полных месяцах с начала года
		{
			full_days_in_full_months_from_the_beginning_of_the_year +=
				(number_Of_Days_Per_Month[i] +
					((i == 2) ? ((int)key_year_end_high_axis) : (0)));
		}

		if (year_end == year_initial + 1)			// годы соседние
		{
			total_full_days_between_dates =
				full_days_to_the_end_of_the_month +
				full_days_in_full_months_to_the_end_of_the_year +
				full_days_from_the_beginning_of_the_month +
				full_days_in_full_months_from_the_beginning_of_the_year;
		}
		else										// годы не соседние
		{
			full_years_between_dates = year_end - year_initial - 1;

			number_of_leap_years_between_dates = (year_end - year_initial - 1) / 4;
	
			full_days_in_full_years_between_dates =
				full_years_between_dates * 365 + number_of_leap_years_between_dates;

			total_full_days_between_dates =
				full_days_to_the_end_of_the_month +
				full_days_in_full_months_to_the_end_of_the_year +
				full_days_in_full_years_between_dates +
				full_days_in_full_months_from_the_beginning_of_the_year +
				full_days_from_the_beginning_of_the_month;
		}
	}

	return total_full_days_between_dates * sign;
}


// ГЛАВНАЯ ФУНКЦИЯ
int main() {
	setlocale(LC_ALL, "ru");

	// создание объекта конструктором с параметрами
	cout << " Создадим объект Дата Конструктором с параметрами >>> \n ";
	Date date2(10, 03, 2000);
	cout << "Дата " << date2() << " == " << date2 << endl;
	cout << endl;

	// создание объекта конструктором копирования
	cout << " Создадим объект Дата Конструктором копирования копированием Даты " << date2() << " >>>" << endl;
	Date date3(date2);
	cout << " Дата " << date3() << " == " << date3 << endl;
	cout << endl;

	int value{ 0 };

	// изменение значения объекта перегруженным оператором +=
	value = -1600;
	cout
		<< " Изменим значение объекта Дата " << date3() << " == " << date3
		<< " оператором += на " << value << " >>> " << endl;
	cout << " Дата " << date3() << " == " << (date3 += value) << endl;
	cout << endl;


	// найдем разность дат в днях
	cout
		<< " Найдем разность дат в днях >>> \n"
		<< "( Дата " << date3() << " == " << date3 << " )"
		<< " - "
		<< "( Дата " << date2() << " == " << date2 << " )"
		<< " = "
		<< (date3 - date2)
		<< endl;
	cout << endl;

	return 0;
}

