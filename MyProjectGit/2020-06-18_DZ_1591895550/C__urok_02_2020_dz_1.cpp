// Выполнение DZ_1591895550.txt
// Домашнее задание 1 из файла C__urok_02_2020_1589461442.pdf
/*
1.	Разработать класс Person, который содержит соот-
ветствующие члены для хранения:
 имени,
 возраста,
 пола,
 телефонного номера.
Напишите функции-члены, которые смогут изменять
эти члены данных индивидуально. Напишите функ-
цию-член Person::Print(), которая выводит отформа-
тированные данные о человеке.
*/
#include <iostream>
#include <clocale>
using namespace std;

enum class GENDER { WOMAN, MAN };

class Person {
private:
	const char* name;
	int age;
	GENDER gender;
	const char* phone;
public:
	Person(
		const char* name,
		int age,
		GENDER gender,
		const char* phone
	) {
		this->name = name;
		this->age = age;
		this->gender = gender;
		this->phone = phone;
	}
	void print() {
		cout
			<< "     Имя - " << this->name << "\n"
			<< " Возраст - " << this->age << "\n"
			<< "     Пол - " << ((this->gender == GENDER::WOMAN) ? ("Ж") : ("М")) << "\n"
			<< " Телефон - " << this->phone << "\n"
			<< endl;
	}
	void setName  (const char* name)  { this->name   = name; }
	void setAge   (int age)           { this->age    = age; }
	void setGender(GENDER gender)     {	this->gender = gender; }
	void setPhone (const char* phone) { this->phone  = phone; }
};


int main() {
	setlocale(LC_ALL, "ru");

	Person person("Сергей", 35, GENDER::MAN, "89656565465");
	person.print();

	person.setName("Наталья");
	person.setAge(25);
	person.setGender(GENDER::WOMAN);
	person.setPhone("89454545645");
	person.print();

	return 0;
}