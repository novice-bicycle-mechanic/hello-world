// ������� 1 �� ����� Domasnee_zadanie_1594661480.txt
// ��������� �������� ������� ����� ������ 3, 4, 5
// ���� 3. ������� 1
/*
�������� ����� Date, ������� ����� ��������� ����������
� ���� (����, �����, ���). � ������� ���������
���������� ����������, ���������� ��������
�������� ���� ��� (��������� � ���� ���������� ����
����� ������), � ����� �������� ���������� ����
�� ������������ ���������� ����.
*/
// ���������� ������������:
// ����� Date ����������� �� DZ_ST_C++_03_vstrecha_10_zadanie_.cpp
// � ��� ������������� ��������� ���������� ���� �� n ����
// � ������������ ������ � ������� increase() � reduce()
// (��� �������� � ������ �����/��� �������� ������/���� �������� �� ������)
// ���������� ������� operator- ������������ �� �����
// GubinAV_hw4_vstrecha8_zadanie1.cpp � ������������ ������ copy-paste �
// � ���������� ������ ���������� ������� - ������� ������ ��������������.

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

	// ����������� �� ���������
	Date() {
		//		cout << " ����������� �� ���������" << endl;
		if (!number) number = Date::numberObject();
	}

	// ����������� � �����������
	Date(int day_, int month_, int year_) : Date() {
		//		cout << " ����������� � �����������" << endl;
		setData(day_, month_, year_);
	}


	// ����������� �����������
	Date(const Date& date) : Date() {
		//		cout << " ����������� �����������" << endl;
		this->day = date.day;
		this->month = date.month;
		this->year = date.year;
	}

	~Date() {
		//		cout << " ����������" << endl;
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
			cout << " ����� ���� �� ������ � ����������� �������� 1970-2037" << endl;
			return false;
		}

		if ((1 <= month_) && (month_ <= 12)) month_b = true;
		else {
			cout << " ����� ������ �� ������ � ����������� �������� 1-12" << endl;
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
				cout << " ����� ��� �� ������ � ����������� �������� 1-31" << endl;
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
				cout << " ����� ��� �� ������ � ����������� �������� 1-30" << endl;
				return false;
			}
			break;
		}
		case 2:
		{
			if ((1 <= day_) && (day_ <= (leap_year ? 29 : 28))) day_b = true;
			else {
				cout << " ����� ��� �� ������ � ����������� �������� 1-" << (leap_year ? 29 : 28) << endl;
				return false;
			}
			break;
		}
		default:
		{
			cout << " ����� ������ �� ������ � ����������� �������� 1-12" << endl;
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

		if (month > 12) {
			month = 1;
			++year;
		}
	}

	// ����� ��������� ���� �� 1 ����
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

	// �������� ������������� ������� ���������� ��������� -
	friend int operator-(const Date& date1, const Date& date2);

};

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

// ������������� ������� ���������� ��������� -
int operator-(const Date& date1_, const Date& date2_) {

	//-------------- �������� ��� �� ������-������ ---------------------------------

	Date dateMax;   // ������� ����
	Date dateMin;   // ������� ����
	int sign{ 0 };  // ���� ������� ���

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

	//---------------- �������� ������ -------------------------------------------------

	int year_initial = dateMin.year;				// ��� ���������

	int month_initial = dateMin.month;				// ����� ���������

	int day_initial = dateMin.day;					// ���� ���������

	int year_end = dateMax.year;					// ��� ��������

	int month_end = dateMax.month;					// ����� ��������

	int day_end = dateMax.day;						// ���� ��������

	int full_years_between_dates = 0;						// ������ ��� ����� ������

	int full_months_between_the_date_of_one_year = 0;		// ������ ������� ����� ������ ������ ����

	int full_days_between_the_date_one_month = 0;			// ������ ���� ����� ������ ������ ������

	int full_days_to_the_end_of_the_month = 0;				// ������ ���� �� ����� ������

	int full_days_from_the_beginning_of_the_month = 0;		// ������ ���� � ������ ������

	int full_days_in_full_months_to_the_end_of_the_year = 0;	// ������ ���� � ������ ������� �� ����� ����

	int full_days_in_full_months_from_the_beginning_of_the_year = 0; // ������ ���� � ������ ������� � ������ ����

	int full_days_in_full_years_between_dates = 0;			// ������ ���� � ������ ����� ����� ������

	int full_days_in_the_full_months_between_the_date_of_one_year = 0; // ������ ���� � ������ ������� ����� ������ ������ ����

	int total_full_days_between_dates = 0;					// ����� ������ ���� ����� ������

	int number_of_days_per_month = 0;						// ���������� ���� � ������

	int number_of_leap_years_between_dates = 0;				// ���������� ���������� ����� ����� ������

	// ���� - ��� ��������� ����������
	bool key_year_initial_high_axis =
		(year_initial == 0) || (year_initial % 400 == 0) ||
		((year_initial % 4 == 0) && (year_initial % 100 != 0));	

	// ���� - ��� �������� ����������
	bool key_year_end_high_axis =
		(year_end == 0) || (year_end % 400 == 0) ||
		((year_end % 4 == 0) && (year_end % 100 != 0));	

	// ������ ���������� ���� � �������
	int number_Of_Days_Per_Month[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };


	// -------------- ����� �������� ������ -----------------------------------

	full_days_to_the_end_of_the_month =
		((month_initial == 2) ? ((int)key_year_initial_high_axis) : (0)) +
		number_Of_Days_Per_Month[month_initial] - day_initial;

	full_days_from_the_beginning_of_the_month = day_end;

	if (year_end == year_initial)			// ��� ��� ���� � ��� ��
	{
		if (month_end == month_initial)				// ����� ��� ���� � ��� ��
		{
			if (day_end == day_initial)						// ���� ��� ���� � ��� ��
			{
				total_full_days_between_dates = 0;
			}
			else											// ��� ��� ������
			{
				total_full_days_between_dates = day_end - day_initial;
			}
		}
		else										// ������ ��� ������
		{
			if (month_end == month_initial + 1)				// ������ ��������
			{
				total_full_days_between_dates =
					full_days_to_the_end_of_the_month + full_days_from_the_beginning_of_the_month;
			}
			else											// ������ �� ��������
			{
				for (int i = month_initial + 1; i < month_end; i++)		// ����� ���� � ������ �������
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
	else									// ���� ��� ������
	{
		for (int i = month_initial + 1; i <= 12; i++)		// ����� ���� � ������ ������� �� ����� ����
		{
			full_days_in_full_months_to_the_end_of_the_year +=
				(number_Of_Days_Per_Month[i] +
					((i == 2) ? ((int)key_year_initial_high_axis) : (0)));
		}

		for (int i = 1; i < month_end; i++)					// ����� ���� � ������ ������� � ������ ����
		{
			full_days_in_full_months_from_the_beginning_of_the_year +=
				(number_Of_Days_Per_Month[i] +
					((i == 2) ? ((int)key_year_end_high_axis) : (0)));
		}

		if (year_end == year_initial + 1)			// ���� ��������
		{
			total_full_days_between_dates =
				full_days_to_the_end_of_the_month +
				full_days_in_full_months_to_the_end_of_the_year +
				full_days_from_the_beginning_of_the_month +
				full_days_in_full_months_from_the_beginning_of_the_year;
		}
		else										// ���� �� ��������
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


// ������� �������
int main() {
	setlocale(LC_ALL, "ru");

	// �������� ������� ������������� � �����������
	cout << " �������� ������ ���� ������������� � ����������� >>> \n ";
	Date date2(10, 03, 2000);
	cout << "���� " << date2() << " == " << date2 << endl;
	cout << endl;

	// �������� ������� ������������� �����������
	cout << " �������� ������ ���� ������������� ����������� ������������ ���� " << date2() << " >>>" << endl;
	Date date3(date2);
	cout << " ���� " << date3() << " == " << date3 << endl;
	cout << endl;

	int value{ 0 };

	// ��������� �������� ������� ������������� ���������� +=
	value = -1600;
	cout
		<< " ������� �������� ������� ���� " << date3() << " == " << date3
		<< " ���������� += �� " << value << " >>> " << endl;
	cout << " ���� " << date3() << " == " << (date3 += value) << endl;
	cout << endl;


	// ������ �������� ��� � ����
	cout
		<< " ������ �������� ��� � ���� >>> \n"
		<< "( ���� " << date3() << " == " << date3 << " )"
		<< " - "
		<< "( ���� " << date2() << " == " << date2 << " )"
		<< " = "
		<< (date3 - date2)
		<< endl;
	cout << endl;

	return 0;
}

