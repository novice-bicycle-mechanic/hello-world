// Выполнение DZ_1591895550.txt
// Домашнее задание 2 из файла C__urok_01_2020_1589461417.pdf
/*
 2.	Написать класс, описывающий группу студентов. Студент
также реализуется с помощью соответствующего класса.
*/

#include <iostream>
#include <clocale>
using namespace std;

enum class GENDER { WOMAN, MAN };

// класс Студент
class Student {
private:
	const char* surname;
	const char* name;
	const char* patronymic;
	int age;
	GENDER gender;
public:
	// конструктор по умолчанию
	Student() {
		surname = "";
		name = "";
		patronymic = "";
		age = 0;
		gender = GENDER::MAN;
	}
	// конструктор со значениями
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

	// возврат значений свойств студента
	const char* getSurname()    { return surname; }     // вывод фамилии
	const char* getName()       { return name; }        // вывод имени
	const char* getPatronymic() { return patronymic; }  // вывод отчества
	int         getAge()        { return age; }         // вывод возраста
	// вывод пола
	const char* getGender() {
		switch (gender) {
		default:
		case GENDER::WOMAN: return "ж"; break;
		case GENDER::MAN:   return "м";   break;
		}
	}
	// печать свойств	
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



// класс Группа студентов
class GroupStudents {
private:
	const char* nameGroup;
	Student** group;
	size_t groupSizeCurrent;
	size_t groupSizeMax;
public:
	// создать группу: задать имя группы
	// и максимальное количество студентов в ней
	GroupStudents(const char* nameGroup, size_t groupSizeMax) {
		this->nameGroup = nameGroup;
		this->groupSizeCurrent = 0;
		this->groupSizeMax = groupSizeMax;
		this->group = new Student * [this->groupSizeMax]{ nullptr };
		cout << "Вызван конструктор GroupStudents" << endl;
	}
	// ликвидировать группу
	~GroupStudents() {
		delete[] group;	
		cout << "Вызван деструктор ~GroupStudents" << endl;
	}
	// возвратить имя группы
	const char* getNameGroup() { return nameGroup; }
	// возвратить максимальный размер группы
	size_t getGroupSizeMax() { return groupSizeMax; }
	// возвратить текущий размер группы
	size_t getGroupSizeCurrent() {
		return groupSizeCurrent;
	}
	// печатать свойства группы, кроме студентов
	void printProperties() {
		cout
			<< " nameGroup = " << nameGroup << "\n"
			<< " groupSizeMax = " << groupSizeMax << "\n"
			<< " groupSizeCurrent = " << groupSizeCurrent
			<< endl;
	}
	// печатать студента номер
	void printStudent(size_t numStud) {
		if (Student* s = this->getStudent(numStud)) s->printProperties();
	}
	// возврат студента номер ... (0 < номер <= groupSizeCurrent)
	Student* getStudent(size_t numStudent) {
		if ((0 < numStudent) && (numStudent <= groupSizeCurrent)) {
			return group[--numStudent];
		}
		else {
			return nullptr;
		}
	}
	// добавить студента в группу
	// возврашает номер студента в группе, если студент добавился
	// возвращает 0, если студент не добавился:
	// группа заполнена или указатель на студента пустой
	size_t addStudent(Student* student) {

		if (groupSizeCurrent >= groupSizeMax) return 999;
		else {
			group[groupSizeCurrent] = student;
			if (group[groupSizeCurrent]) return ++groupSizeCurrent;
			else return 888;
		}
	}
	// удалить студента из группы
	// возвращает новое текущее количество студентов в группе
	// или 0, если номер удаляемого студента вне разрешенного диапазона
	size_t delStudent(size_t numStud) {
		// проверка номера удаляемой строки
		if (!((0 < numStud) && (numStud <= groupSizeCurrent))) return 0;
		// копируем в новый массив объекты прежного массива
		// после удаляемого объекта
		for (size_t i = --numStud; i < groupSizeCurrent; i++) {
			group[i] = group[i + 1];
		}
		// уменьшаем значение длины массива до фактического
		groupSizeCurrent--;
		// возвращаем новую длину массива
		return groupSizeCurrent;
	}
};


int main() {
	setlocale(LC_ALL, "ru");

	GroupStudents groupStud("СТ-84-8-1",10);
	groupStud.printProperties();
	cout << groupStud.getNameGroup() << endl;
	cout << groupStud.getGroupSizeMax() << endl;
	cout << groupStud.getGroupSizeCurrent() << endl;

	Student student1("Иванов", "Иван", "Иванович", 35, GENDER::MAN);
	student1.printProperties();
	Student student2("Петров", "Петр", "Петрович", 53, GENDER::MAN);
	student2.printProperties();
	Student student3("Александрова", "Александра", "Александровна", 25, GENDER::WOMAN);
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