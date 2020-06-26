//������� �� ����� "homework 20.pdf"

//                    �������� ������� � 20
// ����: ���������
//                    ������� 39. ������� 1
//     ������� ��������� Student (�������, ������, ������������
// (������ �� 5 int)).  �������  ������  ���������  �  ��������
// ���������, �����������:
// � ����������� �������� ������ �������;
// � �������� ������ ���������� (> 75 % �������� ������);
// � �������� ������ ���������� (> 50 % ������ 2 � 3).

#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <locale.h>
#include <stdio.h>

#define N "\n"
using namespace std;

// ��������� �������::�������,������,5 ������
struct Student {
	char* surname = nullptr;			// �������
	char* group = nullptr;				// ������
	int acadPerform[5]{ 0 };			// ������������, 5 ������
} currentStudent;

// ����� ��������� ������
void header(void) {
	system("cls");
	cout
		<< "                    �������� ������� � 20"
		N " ����: ���������"
		N "                    ������� 39. ������� 1"
		N "     ������� ��������� Student (�������, ������, ������������"
		N " (������ �� 5 int)).  �������  ������  ���������  �  ��������"
		N " ���������, �����������:"
		N " � ����������� �������� ������ �������;"
		N " � �������� ������ ���������� (> 75 % �������� ������);"
		N " � �������� ������ ���������� (> 50 % ������ 2 � 3)."
		N "-------------------------------------------------------------"
		N " [ESC]-����� �� ���������/������, [ENTER]-���� ��������"
		N " [F4]-�������� ��������,   [F5]-������� ��������"
		N "-------------------------------------------------------------"
		<< endl;
}

// ������ ��������: true-�������� ��� false-��������
// � ��������� >75% �������� ������ 4 � 5,
// � ��������� >50% ������ 2 � 3
int evaluationStudent(Student student){			// ��������� �������
	size_t estimation = 0;						// ������������� ������
	for (size_t i = 0; i < 5; i++) if (student.acadPerform[i] > 3) ++estimation;
	estimation *= 20;
	if (estimation > 75) return 1;
	else if (estimation < 50) return -1;
	else return 0;
}

// ������ ��������� ����������
void listOfHonorsStudents(
	Student* listOfStudents,				// �������� ������ ���������
	size_t numberOfStudents					// ���������� ���������
) {
	cout << " " << "������ ���������� (>75% �������� ������)" << endl;
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

// ������ �� ���������� ��������� (����������)
void listOfUnderperformingStudents(
	Student* listOfStudents,				// �������� ������ ���������
	size_t numberOfStudents					// ���������� ���������
) {
	cout << " " << "������ ���������� (>50% ������ 2 � 3)" << endl;
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

// ������� ������ ������ ��������� � �� ������
void printListOfStudents(
	Student* listOfStudents,				// �������� ������ ���������
	size_t numberOfStudents					// ���������� ���������
) {
	cout << "     ������ �������� � �� ������" << endl;
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

// ������� �������� �������� ������
Student* delItemList(
	Student* listOfStudents,				// �������� ������ ���������
	size_t& numberOfStudents,				// ���������� ���������
	size_t numDelStudent					// ����� ���������� ��������
) {
	Student* newListOfStudents = new Student[(numberOfStudents - 1)];
	numDelStudent--;
	// ��������� � ����� ������ ��������� �� ���������� ��������
	for (size_t i = 0; i < numDelStudent; i++) {
		newListOfStudents[i] = listOfStudents[i];
	}
	// ��������� � ����� ������ ��������� ����� ���������� ��������
	for (size_t i = numDelStudent + 1; i < numberOfStudents; i++) {
		newListOfStudents[(i - 1)] = listOfStudents[i];
	}
	numberOfStudents--;
	delete[] listOfStudents;
	return newListOfStudents;
}

// ������� ���������� �������� ������
Student* addItemList(
	Student* listOfStudents,				// �������� ������ ���������
	size_t& numberOfStudents				// ���������� ���������
) {
	numberOfStudents++;
	Student* newListOfStudents = new Student[numberOfStudents];
	// ��������� � ����� ������ ��������� �� ������� ������
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

	size_t numberOfStudents = 6;	// ���������� ���������
	Student* listOfStudents = new Student[numberOfStudents];

	listOfStudents[0] = { (char*)"������",  (char*)"��-84-8-1",  {4,5,4,5,4} };
	listOfStudents[1] = { (char*)"������",  (char*)"��-84-8-3",  {5,3,4,4,2} };
	listOfStudents[2] = { (char*)"�������", (char*)"����-84-8-2",{4,3,5,4,5} };
	listOfStudents[3] = { (char*)"��������",(char*)"��-84-8-1",  {3,2,5,3,4} };
	listOfStudents[4] = { (char*)"�������", (char*)"��-84-8-3",  {3,5,3,3,5} };
	listOfStudents[5] = { (char*)"��������",(char*)"����-84-8-2",{4,3,4,3,4} };

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
			cout << " ������� �������, ������ � 5 ������ ������������ ��������" << endl;

			listOfStudents = addItemList(listOfStudents, numberOfStudents);
			char* str = nullptr;
			char ss[2]{ '\0' };

			printf_s(" ������� �������: ");
			str = new char[32]{ '\0' };
			scanf_s("%s", str, 32);
			ss[0] = str[0];
			_strupr_s(ss);
			str[0] = ss[0];
			currentStudent.surname = str;

			printf_s(" ������� ������: ");
			str = new char[32]{ '\0' };
			scanf_s("%s", str, 32);
			_strupr_s(str, 32);
			currentStudent.group = str;

			printf_s(" ������� ���� ������ ����� ������: ");
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
			cout << " ������� ����� ���������� �� ������ �������� > ";

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
