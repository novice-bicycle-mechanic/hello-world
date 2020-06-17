// ���������� DZ_1591895550.txt
// �������� ������� 2 �� ����� C__urok_01_2020_1589461417.pdf
/*
 2.	�������� �����, ����������� ������ ���������. �������
����� ����������� � ������� ���������������� ������.
*/

#include <iostream>
#include <clocale>
using namespace std;

enum class GENDER { WOMAN, MAN };

// ����� �������
class Student {
private:
	const char* surname;
	const char* name;
	const char* patronymic;
	int age;
	GENDER gender;
public:
	// ����������� �� ���������
	Student() {
		surname = "";
		name = "";
		patronymic = "";
		age = 0;
		gender = GENDER::MAN;
	}
	// ����������� �� ����������
	Student(
		const char* surname,
		const char* name,
		const char* patronymic,
		int age,
		GENDER gender
	) {
		this->surname = surname;
		this->name = name;
		this->patronymic = patronymic;
		this->age = age;
		this->gender = gender;
	}

	// ������� �������� ������� ��������
	const char* getSurname()    { return surname; }     // ����� �������
	const char* getName()       { return name; }        // ����� �����
	const char* getPatronymic() { return patronymic; }  // ����� ��������
	int         getAge()        { return age; }         // ����� ��������
	// ����� ����
	const char* getGender() {
		switch (gender) {
		default:
		case GENDER::WOMAN: return "�"; break;
		case GENDER::MAN:   return "�";   break;
		}
	}
	// ������ �������	
	void printProperties() {
		cout
			<< " " << this->surname
			<< " " << this->name
			<< " " << this->patronymic
			<< " " << this->age
			<< " " << this->getGender()
			<< endl;
	}
};



// ����� ������ ���������
class GroupStudents {
private:
	const char* nameGroup;
	Student** group;
	size_t groupSizeCurrent;
	size_t groupSizeMax;
public:
	// ������� ������: ������ ��� ������
	// � ������������ ���������� ��������� � ���
	GroupStudents(const char* nameGroup, size_t groupSizeMax) {
		this->nameGroup = nameGroup;
		this->groupSizeCurrent = 0;
		this->groupSizeMax = groupSizeMax;
		this->group = new Student * [this->groupSizeMax]{ nullptr };
		cout << "������ ����������� GroupStudents" << endl;
	}
	// ������������� ������
	~GroupStudents() {
		delete[] group;	
		cout << "������ ���������� ~GroupStudents" << endl;
	}
	// ���������� ��� ������
	const char* getNameGroup() { return nameGroup; }
	// ���������� ������������ ������ ������
	size_t getGroupSizeMax() { return groupSizeMax; }
	// ���������� ������� ������ ������
	size_t getGroupSizeCurrent() {
		return groupSizeCurrent;
	}
	// �������� �������� ������, ����� ���������
	void printProperties() {
		cout
			<< " nameGroup = " << nameGroup << "\n"
			<< " groupSizeMax = " << groupSizeMax << "\n"
			<< " groupSizeCurrent = " << groupSizeCurrent
			<< endl;
	}
	// �������� �������� �����
	void printStudent(size_t numStud) {
		if (Student* s = this->getStudent(numStud)) s->printProperties();
	}
	// ������� �������� ����� ... (0 < ����� <= groupSizeCurrent)
	Student* getStudent(size_t numStudent) {
		if ((0 < numStudent) && (numStudent <= groupSizeCurrent)) {
			return group[--numStudent];
		}
		else {
			return nullptr;
		}
	}
	// �������� �������� � ������
	// ���������� ����� �������� � ������, ���� ������� ���������
	// ���������� 0, ���� ������� �� ���������:
	// ������ ��������� ��� ��������� �� �������� ������
	size_t addStudent(Student* student) {

		if (groupSizeCurrent >= groupSizeMax) return 999;
		else {
			group[groupSizeCurrent] = student;
			if (group[groupSizeCurrent]) return ++groupSizeCurrent;
			else return 888;
		}
	}
	// ������� �������� �� ������
	// ���������� ����� ������� ���������� ��������� � ������
	// ��� 0, ���� ����� ���������� �������� ��� ������������ ���������
	size_t delStudent(size_t numStud) {
		// �������� ������ ��������� ������
		if (!((0 < numStud) && (numStud <= groupSizeCurrent))) return 0;
		// �������� � ����� ������ ������� �������� �������
		// ����� ���������� �������
		for (size_t i = --numStud; i < groupSizeCurrent; i++) {
			group[i] = group[i + 1];
		}
		// ��������� �������� ����� ������� �� ������������
		groupSizeCurrent--;
		// ���������� ����� ����� �������
		return groupSizeCurrent;
	}
};


int main() {
	setlocale(LC_ALL, "ru");

	GroupStudents groupStud("��-84-8-1",10);
	groupStud.printProperties();
	cout << groupStud.getNameGroup() << endl;
	cout << groupStud.getGroupSizeMax() << endl;
	cout << groupStud.getGroupSizeCurrent() << endl;

	Student student1("������", "����", "��������", 35, GENDER::MAN);
	student1.printProperties();
	Student student2("������", "����", "��������", 53, GENDER::MAN);
	student2.printProperties();
	Student student3("������������", "����������", "�������������", 25, GENDER::WOMAN);
	student3.printProperties();

	groupStud.printStudent(groupStud.addStudent(&student1));
	groupStud.printStudent(groupStud.addStudent(&student2));
	groupStud.printStudent(groupStud.addStudent(&student3));
	groupStud.printProperties();

	cout << groupStud.delStudent(1) << endl;
	groupStud.printStudent(1);
	groupStud.printStudent(2);
	groupStud.printStudent(3);

	cout << groupStud.delStudent(1) << endl;
	groupStud.printStudent(1);
	groupStud.printStudent(2);
	groupStud.printStudent(3);

	cout << groupStud.delStudent(1) << endl;
	groupStud.printStudent(1);
	groupStud.printStudent(2);
	groupStud.printStudent(3);

	cout << groupStud.delStudent(1) << endl;
	groupStud.printStudent(1);
	groupStud.printStudent(2);
	groupStud.printStudent(3);

	return 0;
}