// ���������� DZ_1591895550.txt
// �������� ������� 1 �� ����� C__urok_02_2020_1589461442.pdf
/*
1.	����������� ����� Person, ������� �������� ����-
����������� ����� ��� ��������:
 �����,
 ��������,
 ����,
 ����������� ������.
�������� �������-�����, ������� ������ ��������
��� ����� ������ �������������. �������� ����-
���-���� Person::Print(), ������� ������� �������-
���������� ������ � ��������.
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
			<< "     ��� - " << this->name << "\n"
			<< " ������� - " << this->age << "\n"
			<< "     ��� - " << ((this->gender == GENDER::WOMAN) ? ("�") : ("�")) << "\n"
			<< " ������� - " << this->phone << "\n"
			<< endl;
	}
	void setName  (const char* name)  { this->name   = name; }
	void setAge   (int age)           { this->age    = age; }
	void setGender(GENDER gender)     {	this->gender = gender; }
	void setPhone (const char* phone) { this->phone  = phone; }
};


int main() {
	setlocale(LC_ALL, "ru");

	Person person("������", 35, GENDER::MAN, "89656565465");
	person.print();

	person.setName("�������");
	person.setAge(25);
	person.setGender(GENDER::WOMAN);
	person.setPhone("89454545645");
	person.print();

	return 0;
}