// задание из файла DZ_1592244250.txt
// файл Lab_C++_week_1.pdf, Встреча 1, задание 1
/*
Реализуйте класс “Студент”. Необходимо хранить в перемен-
ных-членах класса: ФИО, дату рождения, контактный телефон,
город, страну, название учебного заведения, город и страну (где
находится учебное заведение), номер группы. Реализуйте функ-
ции-члены класса для ввода данных, вывода данных, реализуйте
аксессоры для доступа к отдельным переменным-членам.
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

		cout << "          Заполнение анкеты студента" << endl;
		cout << "          --------------------------" << endl;

		cout << "  Введите фамилию студента: ";
		cin >> buffer;
		this->surname = setString(buffer);

		cout << "      Введите имя студента: ";
		cin >> buffer;
		this->name = setString(buffer);

		cout << " Введите отчество студента: ";
		cin >> buffer;
		this->patronimyc = setString(buffer);

		cout << "    Введите номер дня даты рождения студента: ";
		cin >> this->birthdate.day;

		cout << " Введите номер месяца даты рождения студента: ";
		cin >> this->birthdate.month;

		cout << "   Введите номер года даты рождения студента: ";
		cin >> this->birthdate.year;

		cout << " Введите номер телефона студента: ";
		cin >> buffer;
		this->phone = setString(buffer);

		cout << "  Введите город студента: ";
		cin >> buffer;
		this->city = setString(buffer);

		cout << " Введите страну студента: ";
		cin >> buffer;
		this->country = setString(buffer);

		cout << "    Введите номер группы в институте студента: ";
		cin >> buffer;
		this->groupNumber = setString(buffer);

		cout << "      Введите наименование института студента: ";
		cin >> buffer;
		this->educatName = setString(buffer);

		cout << "  Введите город нахождения института студента: ";
		cin >> buffer;
		this->educatCity = setString(buffer);

		cout << " Введите страну нахождения института студента: ";
		cin >> buffer;
		this->educatCountry = setString(buffer);

		cout << " ---------------------------------------------------------------------------" << endl;

		delete[] buffer;
	}

	void printQuestionnaire() {
		cout << "            Анкета студента" << endl;
		cout << "            ---------------" << endl;
		cout << "  Фамилия: " << surname << endl;
		cout << "      Имя: " << name << endl;
		cout << " Отчество: " << patronimyc << endl;
		cout
			<< " Дата рождения: "
			<< (birthdate.day < 10 ? "0" : "")
			<< birthdate.day
			<< "."
			<< (birthdate.month < 10 ? "0" : "")
			<< birthdate.month
			<< "."
			<< birthdate.year
			<< endl;
		cout << "    Номер телефона: " << phone << endl;
		cout << "  Город проживания: " << city << endl;
		cout << " Страна проживания: " << country << endl;
		cout << "                 Номер учебной группы: " << groupNumber << endl;
		cout << "      Наименование учебного заведения: " << educatName << endl;
		cout << "  Город нахождения учебного заведения: " << educatCity << endl;
		cout << " Страна нахождения учебного заведения: " << educatCountry << endl;
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

	// метод возврата строки string оптимизированной длины и типа char*
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
	
	cout << " Задан новый номер телефона студента: ";
	student.setPhone(student.setString("89526565465"));
	cout << student.getPhone() << endl;

	cout << " Задан новый город проживания студента: ";
	student.setCity(student.setString("Москва"));
	cout << student.getCity() << endl;

	system("pause");

	student.printQuestionnaire();

	return 0;
}







