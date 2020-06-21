// ������� �� ����� DZ_1592244250.txt
// ���� Lab_C++_week_1.pdf, ������� 1, ������� 1
/*
���������� ����� ��������. ���������� ������� � �������-
���-������ ������: ���, ���� ��������, ���������� �������,
�����, ������, �������� �������� ���������, ����� � ������ (���
��������� ������� ���������), ����� ������. ���������� ����-
���-����� ������ ��� ����� ������, ������ ������, ����������
��������� ��� ������� � ��������� ����������-������.
*/

#include <iostream>
#include <clocale>
#include <Windows.h>
using namespace std;

struct Str {
	char* line = nullptr;
	size_t length = 0;
};


class Student {
private:
	char* surname = nullptr;
	char* name = nullptr;
	char* patronimyc = nullptr;
	struct Birthdate {
		size_t day = 0;
		size_t month = 0;
		size_t year = 0;
	}birthdate;
	char* phone = nullptr;
	char* city = nullptr;
	char* country = nullptr;
	char* groupNumber = nullptr;
	char* educatName = nullptr;
	char* educatCity = nullptr;
	char* educatCountry = nullptr;
public:
	~Student() {
		delete[] surname;
		delete[] name;
		delete[] patronimyc;
		delete[] phone;
		delete[] city;
		delete[] country;
		delete[] groupNumber;
		delete[] educatName;
		delete[] educatCity;
		delete[] educatCountry;
	}

	void inputStudent() {
		char* buffer = new char[128]{ '\0' };

		cout << "          ���������� ������ ��������" << endl;
		cout << "          --------------------------" << endl;

		cout << "  ������� ������� ��������: ";
		cin >> buffer;
		this->surname = setString(buffer);

		cout << "      ������� ��� ��������: ";
		cin >> buffer;
		this->name = setString(buffer);

		cout << " ������� �������� ��������: ";
		cin >> buffer;
		this->patronimyc = setString(buffer);

		cout << "    ������� ����� ��� ���� �������� ��������: ";
		cin >> this->birthdate.day;

		cout << " ������� ����� ������ ���� �������� ��������: ";
		cin >> this->birthdate.month;

		cout << "   ������� ����� ���� ���� �������� ��������: ";
		cin >> this->birthdate.year;

		cout << " ������� ����� �������� ��������: ";
		cin >> buffer;
		this->phone = setString(buffer);

		cout << "  ������� ����� ��������: ";
		cin >> buffer;
		this->city = setString(buffer);

		cout << " ������� ������ ��������: ";
		cin >> buffer;
		this->country = setString(buffer);

		cout << "    ������� ����� ������ � ��������� ��������: ";
		cin >> buffer;
		this->groupNumber = setString(buffer);

		cout << "      ������� ������������ ��������� ��������: ";
		cin >> buffer;
		this->educatName = setString(buffer);

		cout << "  ������� ����� ���������� ��������� ��������: ";
		cin >> buffer;
		this->educatCity = setString(buffer);

		cout << " ������� ������ ���������� ��������� ��������: ";
		cin >> buffer;
		this->educatCountry = setString(buffer);

		cout << " ---------------------------------------------------------------------------" << endl;

		delete[] buffer;
	}

	void printQuestionnaire() {
		cout << "            ������ ��������" << endl;
		cout << "            ---------------" << endl;
		cout << "  �������: " << surname << endl;
		cout << "      ���: " << name << endl;
		cout << " ��������: " << patronimyc << endl;
		cout
			<< " ���� ��������: "
			<< (birthdate.day < 10 ? "0" : "")
			<< birthdate.day
			<< "."
			<< (birthdate.month < 10 ? "0" : "")
			<< birthdate.month
			<< "."
			<< birthdate.year
			<< endl;
		cout << "    ����� ��������: " << phone << endl;
		cout << "  ����� ����������: " << city << endl;
		cout << " ������ ����������: " << country << endl;
		cout << "                 ����� ������� ������: " << groupNumber << endl;
		cout << "      ������������ �������� ���������: " << educatName << endl;
		cout << "  ����� ���������� �������� ���������: " << educatCity << endl;
		cout << " ������ ���������� �������� ���������: " << educatCountry << endl;
		cout << " ---------------------------------------------------------------------------" << endl;
	}

	char* getSurname()         { return surname; }
	char* getName()            { return name; }
	char* getPatronimyc()      { return patronimyc; }
	char* getPhone()           { return phone; }
	char* getCity()            { return city; }
	char* getCountry()         { return country; }
	char* getGroupNumber()     { return groupNumber; }
	char* getEducatName()      { return educatName; }
	char* getEducatCity()      { return educatCity; }
	char* getEducatCountry()   { return educatCountry; }
	size_t getDayBirthdate()   { return birthdate.day; }
	size_t getMonthBirthdate() { return birthdate.month; }
	size_t getYearBirthdate()  { return birthdate.year; }

	void setPhone(char* str) { phone = str; }
	void setCity(char* str)  { city = str; }

	// ����� �������� ������ string ���������������� ����� � ���� char*
	template <typename T>
	char* setString(T* string) {
		size_t length = 0;
		while (string[length++]);
		char* line = new char[length] {'\0'};
		--length;
		if (length) {
			for (size_t i = 0; i < length; i++) {
				line[i] = string[i];
			}
		}
		return line;
	}
};


int main() {
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Student student;
	student.inputStudent();
	student.printQuestionnaire();

	system("pause");
	
	cout << " ����� ����� ����� �������� ��������: ";
	student.setPhone(student.setString("89526565465"));
	cout << student.getPhone() << endl;

	cout << " ����� ����� ����� ���������� ��������: ";
	student.setCity(student.setString("������"));
	cout << student.getCity() << endl;

	system("pause");

	student.printQuestionnaire();

	return 0;
}







