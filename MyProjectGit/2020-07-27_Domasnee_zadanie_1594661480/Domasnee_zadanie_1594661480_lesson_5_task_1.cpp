// ������� 1 �� ����� Domasnee_zadanie_1594661480.txt
// ��������� �������� ������� ����� ������ 3, 4, 5
// ���� 5. ������� 1
/*
1. �������� ����� �����, � ������� ����������� ��������
��������, ���������, ���������, ����� � ������ �� �����,
����������� ����������� ������� �� ������������� �������
am (pm): 10:00 pm = 22:00, 12:00 pm =00:00.
*/

#include <iostream>
#include <clocale>
using namespace std;

// ����� �����
class Time {
private:
	size_t hour{ 0 };
	size_t minute{ 0 };
	size_t second{ 0 };
public:
	enum class AT{am, pm};

	// ����������� �� ���������
	Time(){
		cout << " ����������� Time() �� ���������" << endl;
	}

	// ����������� � �����������
	Time(size_t hour_, size_t minute_ = 0, size_t second_ = 0) {
		cout << " ����������� Time() � �����������" << endl;
		if (verifyTime(hour_, minute_, second_)) exit(5);
		else {
			hour = hour_;
			minute = minute_;
			second = second_;
		}
	}

	// ����������� � ����������� �2
	Time(AT at, size_t hour_, size_t minute_ = 0, size_t second_ = 0) {
		cout << " ����������� Time() � ����������� �2" << endl;

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
		cout << " ����������� Time() �����������" << endl;

		this->hour = time.hour;
		this->minute = time.minute;
		this->second = time.second;
	}

	// ����������
	~Time() {
		cout << " ���������� ~Time()" << endl;
	}

	static bool verifyTime(size_t hour_, size_t minute_ = 0, size_t second_ = 0) {
		bool error{ false };
		if (!((0 <= hour_) && (hour_ < 24))) {
			cout << " �������� ����� { " << hour_ << " } �� ������ � ����������� �������� 0 <= ���� < 24" << endl;
			error = true;
		}

		if (!((0 <= minute_) && (minute_ < 60))) {
			cout << " �������� ����� { " << minute_ << " } �� ������ � ����������� �������� 0 <= ������ < 60" << endl;
			error = true;
		}

		if (!((0 <= second_) && (second_ < 60))) {
			cout << " �������� ������ { " << second_ << " } �� ������ � ����������� �������� 0 <= ������� < 60" << endl;
			error = true;
		}
		return error;
	}

	// ����� ���������� �������� ������� ����������� ��������� =
	Time operator=(const Time& time) {
		cout << " ���������� ��������� = - ���������� ��������" << endl;
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


// ������� �������
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

	// ������� ������� �� ���������
	cout
		<< " ������� ������� �� ��������� >>> \n"
		<< " ����� " << time1
		<< (time1 == time2 ? "" : " ��")
		<< " ����� ������� " << time2
		<< endl;
	cout << endl;

	// ������� ������� �� ���������
	cout
		<< " ������� ������� �� ��������� >>> \n"
		<< " ����� " << time3
		<< (time3 == time2 ? "" : " ��")
		<< " ����� ������� " << time2
		<< endl;
	cout << endl;

	// ������� ������� �� �����������
	cout
		<< " ������� ������� �� ����������� >>> \n"
		<< " ����� " << time5
		<< (time5 != time2 ? " ��" : "")
		<< " ����� ������� " << time2
		<< endl;
	cout << endl;

	// ������� ������� �� �����������
	cout
		<< " ������� ������� �� ����������� >>> \n"
		<< " ����� " << time6
		<< (time6 != time2 ? " ��" : "")
		<< " ����� ������� " << time2
		<< endl;
	cout << endl;

	// ������� ������� �� ������
	cout
		<< " ������� ������� �� ������ >>> \n"
		<< " ����� " << time7
		<< (time7 > time2 ? "" : " ��")
		<< " ������ ������� " << time2
		<< endl;
	cout << endl;

	// ������� ������� �� ������
	cout
		<< " ������� ������� �� ������ >>> \n"
		<< " ����� " << time6
		<< (time6 > time2 ? "" : " ��")
		<< " ������ ������� " << time2
		<< endl;
	cout << endl;

	// ������� ������� �� ������
	cout
		<< " ������� ������� �� ������ >>> \n"
		<< " ����� " << time7
		<< (time7 < time2 ? "" : " ��")
		<< " ������ ������� " << time2
		<< endl;
	cout << endl;

	// ������� ������� �� ������
	cout
		<< " ������� ������� �� ������ >>> \n"
		<< " ����� " << time6
		<< (time6 < time2 ? "" : " ��")
		<< " ������ ������� " << time2
		<< endl;
	cout << endl;

	// ������ ������������ ����� - �� �������
	Time time9(Time::AT::am, 10);
	cout << " time9 �� �����������, 10:00 am: " << time9 << endl;
	cout << endl;

	// ������ ������������ ����� - ����� �������
	Time time10(Time::AT::pm, 10);
	cout << " time10 �� �����������, 10:00 pm: " << time10 << endl;
	cout << endl;

	// ������ �����
	cout << " ������� ����� �������: ���� ������ �������\n � ���������: 00 00 00 - 23 59 59 >>> \n";
	cin >> time1;
	cout << " time1: " << time1 << endl;
	cout << endl;

	return 0;
}
// ����� ������� �������
