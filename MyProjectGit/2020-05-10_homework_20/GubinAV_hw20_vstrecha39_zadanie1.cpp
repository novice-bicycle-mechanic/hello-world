//задание из файла "homework 20.pdf"

//                    Домашнее задание № 20
// Тема: Структуры
//                    Встреча 39. Задание 1
//     Описать структуру Student (фамилия, группа, успеваемость
// (массив из 5 int)).  Создать  массив  студентов  и  написать
// программу, позволяющую:
// • Динамически изменять размер массива;
// • Выводить список отличников (> 75 % отличных оценок);
// • Выводить список двоечников (> 50 % оценок 2 и 3).

#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <locale.h>
#include <stdio.h>

#define N "\n"
using namespace std;

// Структура Студент::Фамилия,Группа,5 оценок
struct Student {
	char* surname = nullptr;			// фамилия
	char* group = nullptr;				// группа
	int acadPerform[5]{ 0 };			// успеваемость, 5 оценок
} currentStudent;

// вывод заголовка экрана
void header(void) {
	system("cls");
	cout
		<< "                    Домашнее задание № 20"
		N " Тема: Структура"
		N "                    Встреча 39. Задание 1"
		N "     Описать структуру Student (фамилия, группа, успеваемость"
		N " (массив из 5 int)).  Создать  массив  студентов  и  написать"
		N " программу, позволяющую:"
		N " • Динамически изменять размер массива;"
		N " • Выводить список отличников (> 75 % отличных оценок);"
		N " • Выводить список двоечников (> 50 % оценок 2 и 3)."
		N "-------------------------------------------------------------"
		N " [ESC]-выход из программы/режима, [ENTER]-ввод значения"
		N " [F4]-добавить студента,   [F5]-удалить студента"
		N "-------------------------------------------------------------"
		<< endl;
}

// оценка студента: true-отличник или false-двоечник
// у отличника >75% отличных оценок 4 и 5,
// у двоечника >50% оценок 2 и 3
int evaluationStudent(Student student){			// структура студент
	size_t estimation = 0;						// анализируемая оценка
	for (size_t i = 0; i < 5; i++) if (student.acadPerform[i] > 3) ++estimation;
	estimation *= 20;
	if (estimation > 75) return 1;
	else if (estimation < 50) return -1;
	else return 0;
}

// список студентов отличников
void listOfHonorsStudents(
	Student* listOfStudents,				// исходный список студентов
	size_t numberOfStudents					// количество студентов
) {
	cout << " " << "Список отличников (>75% отличных оценок)" << endl;
	for (size_t i = 0; i < numberOfStudents; i++) {
		if (evaluationStudent(listOfStudents[i]) > 0) {
			cout
				<< setw(3) << right << (i+1) << setw(1) << ""
				<< setw(10) << left << listOfStudents[i].surname
				<< setw(12) << left << listOfStudents[i].group;
			for (size_t j = 0; j < 5; j++) {
				cout << " " << listOfStudents[i].acadPerform[j];
			}
			cout << endl;				
		}
	}
	cout << endl;
}

// список не успевающих студентов (двоичников)
void listOfUnderperformingStudents(
	Student* listOfStudents,				// исходный список студентов
	size_t numberOfStudents					// количество студентов
) {
	cout << " " << "Список двоечников (>50% оценок 2 и 3)" << endl;
	for (size_t i = 0; i < numberOfStudents; i++) {
		if (evaluationStudent(listOfStudents[i]) < 0) {
			cout
				<< setw(3) << right << (i+1) << setw(1) << ""
				<< setw(10) << left << listOfStudents[i].surname
				<< setw(12) << left << listOfStudents[i].group;
			for (size_t j = 0; j < 5; j++) {
				cout << " " << listOfStudents[i].acadPerform[j];
			}
			cout << endl;
		}
	}
	cout << endl;
}

// функция печати списка студентов и их оценок
void printListOfStudents(
	Student* listOfStudents,				// исходный список студентов
	size_t numberOfStudents					// количество студентов
) {
	cout << "     Список учеников и их оценки" << endl;
	for (size_t i = 0; i < numberOfStudents; i++) {
		cout
			<< setw(3) << right << (i+1) << setw(1) << ""
			<< setw(10) << left << listOfStudents[i].surname
			<< setw(12) << left << listOfStudents[i].group;
		for (size_t j = 0; j < 5; j++) {
			cout << " " << listOfStudents[i].acadPerform[j];
		}
		cout << endl;
	}
	cout << endl;
}

// функция удаления элемента списка
Student* delItemList(
	Student* listOfStudents,				// исходный список студентов
	size_t& numberOfStudents,				// количество студентов
	size_t numDelStudent					// номер удаляемого студента
) {
	Student* newListOfStudents = new Student[(numberOfStudents - 1)];
	numDelStudent--;
	// скопируем в новый список студентов до удаляемого студента
	for (size_t i = 0; i < numDelStudent; i++) {
		newListOfStudents[i] = listOfStudents[i];
	}
	// скопируем в новый список студентов после удаляемого студента
	for (size_t i = numDelStudent + 1; i < numberOfStudents; i++) {
		newListOfStudents[(i - 1)] = listOfStudents[i];
	}
	numberOfStudents--;
	delete[] listOfStudents;
	return newListOfStudents;
}

// функция добавления элемента списка
Student* addItemList(
	Student* listOfStudents,				// исходный список студентов
	size_t& numberOfStudents				// количество студентов
) {
	numberOfStudents++;
	Student* newListOfStudents = new Student[numberOfStudents];
	// скопируем в новый список студентов из старого списка
	for (size_t i = 0; i < numberOfStudents; i++) {
		newListOfStudents[i] = listOfStudents[i];
	}
	delete[] listOfStudents;
	return newListOfStudents;
}


int main()
{
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	size_t numberOfStudents = 6;	// количество студентов
	Student* listOfStudents = new Student[numberOfStudents];

	listOfStudents[0] = { (char*)"Иванов",  (char*)"СТ-84-8-1",  {4,5,4,5,4} };
	listOfStudents[1] = { (char*)"Петров",  (char*)"СТ-84-8-3",  {5,3,4,4,2} };
	listOfStudents[2] = { (char*)"Сидоров", (char*)"СЧПУ-84-8-2",{4,3,5,4,5} };
	listOfStudents[3] = { (char*)"Кузнецов",(char*)"СТ-84-8-1",  {3,2,5,3,4} };
	listOfStudents[4] = { (char*)"Токарев", (char*)"СТ-84-8-3",  {3,5,3,3,5} };
	listOfStudents[5] = { (char*)"Слесарев",(char*)"СЧПУ-84-8-2",{4,3,4,3,4} };

	char byte1char = '\0';
	char byte2char = '\0';
	enum keys { ENTER = 13, ESC = 27 };
	enum key0 { F4 = 62, F5 = 63};

	do 
	{
		header();
		printListOfStudents(listOfStudents, numberOfStudents);
		listOfHonorsStudents(listOfStudents, numberOfStudents);
		listOfUnderperformingStudents(listOfStudents, numberOfStudents);

		byte1char = _getch();
		if (_kbhit()) byte2char = _getch();

		if (byte1char == keys::ESC) break;

		else if ((byte1char == 0) && (byte2char == key0::F4)) {
			cout << "-------------------------------------------------------------" << endl;
			cout << " Укажите фамилию, группу и 5 оценок добавляемого студента" << endl;

			listOfStudents = addItemList(listOfStudents, numberOfStudents);
			char* str = nullptr;
			char ss[2]{ '\0' };

			printf_s(" Введите фамилию: ");
			str = new char[32]{ '\0' };
			scanf_s("%s", str, 32);
			ss[0] = str[0];
			_strupr_s(ss);
			str[0] = ss[0];
			currentStudent.surname = str;

			printf_s(" Введите группу: ");
			str = new char[32]{ '\0' };
			scanf_s("%s", str, 32);
			_strupr_s(str, 32);
			currentStudent.group = str;

			printf_s(" Введите пять оценок через пробел: ");
			scanf_s("%d %d %d %d %d",
				&currentStudent.acadPerform[0],
				&currentStudent.acadPerform[1],
				&currentStudent.acadPerform[2],
				&currentStudent.acadPerform[3],
				&currentStudent.acadPerform[4]
				);

			listOfStudents[(numberOfStudents - 1)] = currentStudent;
		}

		else if ((byte1char == 0) && (byte2char == key0::F5)) {
			cout << "-------------------------------------------------------------" << endl;
			cout << " Укажите номер удаляемого из списка студента > ";

			size_t numDelStudent = 0;
			bool notFirstSynbol = false;

			do {
				byte1char = _getch();
				if (_kbhit()) (void)_getch();
				if (byte1char == keys::ESC) break;

				if ((!notFirstSynbol) && ('1' <= byte1char) && (byte1char <= '9')) {
					notFirstSynbol = true;
					numDelStudent = numDelStudent * 10 + (byte1char - '0');
					if (numDelStudent > numberOfStudents) break;
					cout << byte1char;
				}
			
				if (byte1char == ENTER) {
					cout << endl;
					listOfStudents = delItemList(listOfStudents, numberOfStudents, numDelStudent);
					break;
				}
			} while (true);
		}
	} while (true);

	delete[] listOfStudents;
	return 0;
}
