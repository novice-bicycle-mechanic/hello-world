//������� �� ����� "homework 20.pdf"

//                    �������� ������� � 20
// ����: ���������
//                    ������� 39. ������� 2
//     ������� ��������� Man (�������, ���, �������, ���� ��������).
// ������� ������, �������������:
// � ����� ���������� � ����������� �� ������� ��� �����;
// � ����� ������ ����������� ������ � ��������� ���� ��������;
// � ��������� �������� ������� ��� ���������� � �������� �������;
// � ����� �� ������� � �����;
// � �������������� ������.
#include <Windows.h>
#include <conio.h>
#include <locale.h>
#include <stdio.h>
#include <time.h>

enum sizebuf { BUF = 32 };
enum KeysC { ESC = 27 };
enum KeysF { BYTE1KEY = 0, F1 = 59, F2, F3, F4, F5, F6, F7, F8, F9 };

enum class FieldsListMan { NONE, SURNAME, NAME, AGE, BIRTHDATE } fieldListMan;
enum class DisplayedList { LISTMAN, SIARCHLISTSURNAME, SIARCHLISTNAME } displayedList;

// ������ ��������� Man
struct Man {
	char* surname = new char[sizebuf::BUF]{ '\0' };   // �������
	char* name = new char[sizebuf::BUF]{ '\0' };      // ���
	size_t age = 0;        // �������
	struct Birthdate {     // ���� ��������:
		size_t day = 0;    // - ����
		size_t month = 0;  // - �����
		size_t year = 0;   // - ���
	} birthdate;
};


// ������� ������ ��������� ������ � ������� ����
void titleScreen() {
	system("cls");
	printf_s("\
 [Esc]-����� �� ���������\n\
 [F1]-�������� ������, [F2]-������� ������, [F4]-�������� ������\n\
 �����������: [F5]-�� �������, [F6]-�� �����\n\
 �����: [F7]-�� �������, [F8]-�� �����, [F9]-����������� ������\n\
 ---------------------------------------------------------------\n\
");
}


// ������� ���������� ��������� Man
Man* setMan(
	char* surname,
	char* name,
	size_t age,
	size_t day,
	size_t month,
	size_t year
) {
	Man* man = new Man;
	*man = { surname, name, age, { day, month, year } };
	return man;
}


// ������� ���������� ������ � ������ Man
void addRecord(Man* man, Man**& list, size_t& length) {

	// �������� ����� ������ buffer ���� Man** �����������
	// �� 1 ������ �� ��������� � ������� �������� listMan
	Man** buffer = new Man * [length + 1]{ nullptr };

	// ��������� ������� ������ listMan � ����� ������ buffer
	if (list) {
		for (size_t i = 0; i < length; i++) {
			buffer[i] = list[i];
		}
	}

	// ������ ������� ������ listMan
	if (list) {
		delete[] list;
		list = nullptr;
	}

	// �������� �������� "��������� �� ������"
	// listMan ����� ������ buffer
	list = buffer;
	buffer = nullptr;

	// �������� ��������� ������ ������������ ������� listMan
	list[length] = man;

	// �������� �������� ����� ������� listMan �� �����������
	length++;
}


// ������� �������� ������ �� ������� listMan
// ���������� true ��� ������ ��� false, ���� �����
// ��������� ������ �� ������ � ����������� ��������
bool delRecord(size_t numDelRecord, Man**& listMan, size_t& lengthMan) {

	// ���������� ������ ��������� ������ numDelRecord �� 1
	// ��� ���������� ������������� ������ � ���������
	numDelRecord--;

	// �������� ������ ��������� ������ numDelRecord
	// �� ��������� � ����������� ��������,
	// ���� �� ������ - ������� �� ������� false
	if (!((0 <= numDelRecord) && (numDelRecord < lengthMan))) {
		return false;
	}
	// �������� ����� ������ buffer ���� Man** �����������
	// �� 1 ������ �� ��������� � ������� �������� listMan
	Man** buffer = new Man * [lengthMan - 1]{ nullptr };

	// ��������� ������� ������ listMan � ����� ������ buffer
	// ������� � �� ��������� ������ numDelRecord
	for (size_t i = 0; i < numDelRecord; i++) {
		buffer[i] = listMan[i];
	}
	// ��������� ������� ������ listMan � ����� ������ buffer
	// ����� ��������� ������ numDelRecord
	if ((numDelRecord + 1) < lengthMan) {
		for (size_t i = (numDelRecord + 1); i < lengthMan; i++) {
			buffer[i - 1] = listMan[i];
		}
	}
	// ������ ������� ������ listMan
	// � �������� ��������� �� ������� ������ listMan ����� ������ buffer,
	// ��������� �� ������� ����� �������
	if (listMan) delete[] listMan;
	listMan = buffer;
	buffer = nullptr;

	// �������� �������� ����� ������� lengthMan �� 1
	// � ������������ � ����������� ������ ������� listMan
	lengthMan--;

	// ������� �� ������� true - �������� ����������
	return true;
}


// ������� ������ ������� ���� Man** �� �����
void printList(Man** list, size_t length) {
	printf_s("  �  �������          ���          �������   ���� ��������\n");

	if (list) {
		for (size_t i = 0; i < length; i++) {
			printf_s("%3d  %-16s %-12s %7d      %02d.%02d.%04d\n",
				(i + 1),
				list[i]->surname,
				list[i]->name,
				list[i]->age,
				list[i]->birthdate.day,
				list[i]->birthdate.month,
				list[i]->birthdate.year
				);
		}
	}
}


// ������� ����� ������ � ���������
Man* inputMan() {
	Man* man = new Man;

	printf_s(" ������� ����� ������� ������:\n\
 �������, ���, �������, ����, ����� � ��� ��������\n > ");

	scanf_s("%s %s %d %d %d %d",
		man->surname, sizebuf::BUF,
		man->name, sizebuf::BUF,
		&man->age,
		&man->birthdate.day,
		&man->birthdate.month,
		&man->birthdate.year
	);
	return man;
}


// ������� ����� ������ ������ ������� listMan
size_t inputNumRecord() {
	printf_s(" ������� ����� ������: ");
	size_t number = 0;
	scanf_s("%d", &number);
	return number;
}


// ������� ��������� ��������� ������ ������� listMan
void editRecord(size_t numRecord, Man** listMan, size_t& lengthMan) {
	// ���������� ������ ��������� ������ numDelRecord �� 1
	// ��� ���������� ������������� ������ � ���������
	numRecord--;

	// �������� ������ ��������� ������ numDelRecord
	// �� ��������� � ����������� ��������,
	// ���� �� ������ - ������� �� ������� false
	if (!((0 <= numRecord) && (numRecord < lengthMan))) {
		printf_s(" ����� ������ �� ������ � ����������� ��������\n");
		system("pause");
		return;
	}

	FieldsListMan fieldListMan = FieldsListMan::NONE;
	printf_s(" ������� ����� �������������� ����:\n\
 [1]-�������, [2]-���, [3]-�������, [4]-���� �������� > ");
	scanf_s("%d", &fieldListMan);
	switch (fieldListMan) {
	case FieldsListMan::SURNAME: {
		printf_s(" ������� \"%s\" �������� ��: ", listMan[numRecord]->surname);
		char* newSurname = new char[sizebuf::BUF]{ '\0' };
		scanf_s("%s", newSurname, sizebuf::BUF);
		listMan[numRecord]->surname = newSurname;
		break;
	}
	case FieldsListMan::NAME: {
		printf_s(" ��� \"%s\" �������� ��: ", listMan[numRecord]->name);
		char* newName = new char[sizebuf::BUF]{ '\0' };
		scanf_s("%s", newName, sizebuf::BUF);
		listMan[numRecord]->name = newName;
		break;
	}
	case FieldsListMan::AGE: {
		printf_s(" ������� \"%d\" �������� ��: ", listMan[numRecord]->age);
		scanf_s("%d", &listMan[numRecord]->age);
		break;
	}
	case FieldsListMan::BIRTHDATE: {
		printf_s(" ���� �������� \"%02d.%02d.%04d\" �������� ��\n (����� �������): ���� ����� ��� > ",
			listMan[numRecord]->birthdate.day,
			listMan[numRecord]->birthdate.month,
			listMan[numRecord]->birthdate.year			
			);
		scanf_s("%d %d %d",
			&listMan[numRecord]->birthdate.day,
			&listMan[numRecord]->birthdate.month,
			&listMan[numRecord]->birthdate.year
			);
		break;
	}
	}
}


// ������� ������ ������� ��� ����� ����������
// ���������: A-Z, a-z - 1-26 ; �������: �-�, �-� - 101-133
size_t  rankSymbol(
	unsigned char symbol							// ����������� ������
) {
	if ((64 < symbol) && (symbol < 91)) {			// ��������� ��������� ������� A-Z	
		return (symbol - (unsigned char)64);
	}
	else if ((96 < symbol) && (symbol < 123)) {		// �������� ��������� ������� a-z
		return (symbol - (unsigned char)96);
	}
	else if ((191 < symbol) && (symbol < 198)) {	// ��������� ������� ������� �-�
		return (symbol - (unsigned char)91);
	}
	else if (symbol == 168) {						// ��������� ������� ������ �
		return (symbol - (unsigned char)61);
	}
	else if ((197 < symbol) && (symbol < 224)) {	// ��������� ������� ������� �-�
		return (symbol - (unsigned char)90);
	}
	else if ((223 < symbol) && (symbol < 230)) {	// �������� ������� ������� �-�
		return (symbol - (unsigned char)123);
	}
	else if (symbol == 184) {						// �������� ������� ������ �
		return (symbol - (unsigned char)77);
	}
	else if ((229 < symbol) && (symbol < 256)) {	// �������� ������� ������� �-�
		return (symbol - (unsigned char)122);
	}
	else {
		return 0;									// ������ ��������
	}
}


// ������� ��������� � ������������ ��������� �� �������
void minArray(
	Man*& oneRecord,				// ������ 1 (�� ������ ������ ���� ������)
	Man*& twoRecord,				// ������ 2 (�� ������ ������ ���� ������)
	char* one,						// ������ ������ 1 (������ ���� ������)
	char* two,						// ������ ������ 2 (������ ���� ������)
	size_t index					// ������ char-������� ��������
) {
	Man* bufRecord = nullptr;		// ��������������� ��������� �� �������
	if (rankSymbol(one[index]) > rankSymbol(two[index])) {	// ���� 1 > 2
		bufRecord = oneRecord;											// ����������� �������� �������
		oneRecord = twoRecord;
		twoRecord = bufRecord;
	}
	// �����, ���� �������� �����, � �� ����� '\0'
	else if ((rankSymbol(one[index]) == rankSymbol(two[index])) &&
		     (rankSymbol(one[index]) != '\0') &&
		     (rankSymbol(two[index]) != '\0')) {
		// - ������� ��������� ������� ���������� ��� ���������
		//   ��������� �� ������� �������� ���������
		minArray(oneRecord, twoRecord, one, two, ++index);
	}
	// ���� 1 < 2 ��� ���� ���� ����� '\0' - ������ �� ������ � ����� �� �������
}


// ������� ���������� �������� � ���������/�������
void sortNames(FieldsListMan fieldListMan, Man** listMan, size_t lengthMan) {

	if (fieldListMan == FieldsListMan::SURNAME) {
		for (size_t i = 1; i < lengthMan; i++) {
			for (size_t j = 1; j < lengthMan; j++) {
				minArray(listMan[j - 1], listMan[j], listMan[j - 1]->surname, listMan[j]->surname, 0);
			}
		}
	}
	else if (fieldListMan == FieldsListMan::NAME) {
		for (size_t i = 1; i < lengthMan; i++) {
			for (size_t j = 1; j < lengthMan; j++) {
				minArray(listMan[j - 1], listMan[j], listMan[j - 1]->name, listMan[j]->name, 0);
			}
		}
	}
}


// ������� ������ ������ �� �������
void searchSurname(
	Man** listMan,              // �������� ������
	size_t lengthMan            // ����� ��������� �������
) {
	// ������ �������, ������ � ������� ���������� �����
	char* surname = new char[sizebuf::BUF]{ '\0' };
	printf_s(" ������� ������� ������: ");
	scanf_s("%s", surname, sizebuf::BUF);
	_strlwr_s(surname, sizebuf::BUF);  // ������� ������ � ������ �������

	// ������� �������� ������ ������
	char* bufferSurname = new char[sizebuf::BUF]{ '\0' };

	// ������� ������ ������� � ���������� ���������
	size_t lengthSurname = 0;
	Man** listSurname = new Man * [lengthMan] {nullptr};

	// �������� ��������� �������� ������ �������
	// � �������� ������ ������� �������������
	// �� ������ ������� listMan
	for (size_t i = 0; i < lengthMan; i++) {
		// �������� ���� surname ������� listMan � �������� ������ �������
		for (size_t j = 0; j < sizebuf::BUF; j++) {
			bufferSurname[j] = listMan[i]->surname[j];
		}
		_strlwr_s(bufferSurname, sizebuf::BUF);  // ������� ������ � ������ �������
		// ���� ��������� �������� ������ � �������� ������ �����
		if (strstr(bufferSurname, surname)) {
			// ���� ����� - ��������� ������ �� ������� listMan � ������ listSurname
			listSurname[lengthSurname] = new Man;
			// �������� ���� surname 
			for (size_t j = 0; j < sizebuf::BUF; j++) {
				listSurname[lengthSurname]->surname[j] = listMan[i]->surname[j];
			}
			// �������� ���� name
			for (size_t j = 0; j < sizebuf::BUF; j++) {
				listSurname[lengthSurname]->name[j] = listMan[i]->name[j];
			}
			// �������� ���� age
			listSurname[lengthSurname]->age = listMan[i]->age;
			// �������� ���� birthdate.day
			listSurname[lengthSurname]->birthdate.day = listMan[i]->birthdate.day;
			// �������� ���� birthdate.month
			listSurname[lengthSurname]->birthdate.month = listMan[i]->birthdate.month;
			// �������� ���� birthdate.year
			listSurname[lengthSurname]->birthdate.year = listMan[i]->birthdate.year;
			// ����������� ������ ������� listSurname
			lengthSurname++;
		}
	}

	char byte1key = '\0';

	while (true) {
		system("cls");
		printf_s("[Esc]-����� �� ������ �� �������\n\
---------------------------------------------------------------\n\
");

		printf_s("  �  �������          ���          �������   ���� ��������\n");

		// ����� ������� listSurname �� �����
		if (listSurname) {
			for (size_t i = 0; i < lengthSurname; i++) {
				if (listSurname[i]) {
					printf_s("%3d  %-16s %-12s %7d      %02d.%02d.%04d\n",
						(i + 1),
						listSurname[i]->surname,
						listSurname[i]->name,
						listSurname[i]->age,
						listSurname[i]->birthdate.day,
						listSurname[i]->birthdate.month,
						listSurname[i]->birthdate.year
					);
				}
				else break;
			}
		}

		byte1key = _getch();
		// ���� ������ [Esc] - ����� �� ������
		if (byte1key == KeysC::ESC) break;
	}

	// ������� ��������� ������������ ����������
	if (surname) delete[] surname;
	surname = nullptr;
	if (listSurname) {
		for (size_t i = 0; i < lengthMan; i++) {
			if (listSurname[i]) delete[] listSurname[i];
			listSurname[i] = nullptr;
		}
		delete[] listSurname;
		listSurname = nullptr;
	}
}


// ������� ������ ������ �� �����
void searchName(
	Man** listMan,              // �������� ������
	size_t lengthMan            // ����� ��������� �������
) {
	// ������ ���, ������ � ������� ���������� �����
	char* name = new char[sizebuf::BUF]{ '\0' };
	printf_s(" ������� ��� ������: ");
	scanf_s("%s", name, sizebuf::BUF);
	_strlwr_s(name, sizebuf::BUF);  // ������� ������ � ������ �������

	// ������� �������� ������ ������
	char* bufferName = new char[sizebuf::BUF]{ '\0' };

	// ������� ������ ������� � ���������� �������
	size_t lengthName = 0;
	Man** listName = new Man * [lengthMan] {nullptr};

	// �������� ��������� �������� ������ �����
	// � �������� ������ ����� �������������
	// �� ������ ������� listMan
	for (size_t i = 0; i < lengthMan; i++) {
		// �������� ���� name ������� listMan � �������� ������ �����
		for (size_t j = 0; j < sizebuf::BUF; j++) {
			bufferName[j] = listMan[i]->name[j];
		}
		_strlwr_s(bufferName, sizebuf::BUF);  // ������� ������ � ������ �������
		// ���� ��������� �������� ������ � �������� ������ �����
		if (strstr(bufferName, name)) {
			// ���� ����� - ��������� ������ �� ������� listMan � ������ listName
			listName[lengthName] = new Man;
			// �������� ���� surname 
			for (size_t j = 0; j < sizebuf::BUF; j++) {
				listName[lengthName]->surname[j] = listMan[i]->surname[j];
			}
			// �������� ���� name
			for (size_t j = 0; j < sizebuf::BUF; j++) {
				listName[lengthName]->name[j] = listMan[i]->name[j];
			}
			// �������� ���� age
			listName[lengthName]->age = listMan[i]->age;
			// �������� ���� birthdate.day
			listName[lengthName]->birthdate.day = listMan[i]->birthdate.day;
			// �������� ���� birthdate.month
			listName[lengthName]->birthdate.month = listMan[i]->birthdate.month;
			// �������� ���� birthdate.year
			listName[lengthName]->birthdate.year = listMan[i]->birthdate.year;
			// ����������� ������ ������� listSurname
			lengthName++;
		}
	}

	char byte1key = '\0';

	while (true) {
		system("cls");
		printf_s("[Esc]-����� �� ������ �� �����\n\
---------------------------------------------------------------\n\
");

		printf_s("  �  �������          ���          �������   ���� ��������\n");

		// ����� ������� listSurname �� �����
		if (listName) {
			for (size_t i = 0; i < lengthName; i++) {
				if (listName[i]) {
					printf_s("%3d  %-16s %-12s %7d      %02d.%02d.%04d\n",
						(i + 1),
						listName[i]->surname,
						listName[i]->name,
						listName[i]->age,
						listName[i]->birthdate.day,
						listName[i]->birthdate.month,
						listName[i]->birthdate.year
					);
				}
				else break;
			}
		}

		byte1key = _getch();
		// ���� ������ [Esc] - ����� �� ������
		if (byte1key == KeysC::ESC) break;
	}

	// ������� ��������� ������������ ����������
	if (name) delete[] name;
	name = nullptr;
	if (listName) {
		for (size_t i = 0; i < lengthMan; i++) {
			if (listName[i]) delete[] listName[i];
			listName[i] = nullptr;
		}
		delete[] listName;
		listName = nullptr;
	}
}


// ������� ������ ������ � ����������� ������
void searchBirthdayManMonth(
	Man** listMan,              // �������� ������
	size_t lengthMan            // ����� ��������� �������
) {
	// ������ �����, ������ � ����������� �������� ���������� �����
	size_t month = 0;
	printf_s(" ������� ����� ������: ");
	scanf_s("%d", &month);

	// ������� ������ ������� � ���������� �������
	size_t lengthBirthday = 0;
	Man** listBirthday = new Man * [lengthMan] {nullptr};

	// �������� ��������� �������� ��������� ������
	// � ������ ���� �������� � ������ ������� listMan
	for (size_t i = 0; i < lengthMan; i++) {
		// ���� ��������� ������� � ������ ������� listMan
		if (listMan[i]->birthdate.month == month) {
			// ���� ����� - ��������� ������ � ������ listBirthday
			listBirthday[lengthBirthday] = new Man;
			// �������� ���� surname 
			for (size_t j = 0; j < sizebuf::BUF; j++) {
				listBirthday[lengthBirthday]->surname[j] = listMan[i]->surname[j];
			}
			// �������� ���� name
			for (size_t j = 0; j < sizebuf::BUF; j++) {
				listBirthday[lengthBirthday]->name[j] = listMan[i]->name[j];
			}
			// �������� ���� age
			listBirthday[lengthBirthday]->age = listMan[i]->age;
			// �������� ���� birthdate.day
			listBirthday[lengthBirthday]->birthdate.day = listMan[i]->birthdate.day;
			// �������� ���� birthdate.month
			listBirthday[lengthBirthday]->birthdate.month = listMan[i]->birthdate.month;
			// �������� ���� birthdate.year
			listBirthday[lengthBirthday]->birthdate.year = listMan[i]->birthdate.year;
			// ����������� ������ ������� listSurname
			lengthBirthday++;
		}
	}

	char byte1key = '\0';

	while (true) {
		system("cls");
		printf_s("[Esc]-����� �� ������ ����������\n\
---------------------------------------------------------------\n\
");

		printf_s("  �  �������          ���          �������   ���� ��������\n");

		// ����� ������� listBirthday �� �����
		if (listBirthday) {
			for (size_t i = 0; i < lengthBirthday; i++) {
				if (listBirthday[i]) {
					printf_s("%3d  %-16s %-12s %7d      %02d.%02d.%04d\n",
						(i + 1),
						listBirthday[i]->surname,
						listBirthday[i]->name,
						listBirthday[i]->age,
						listBirthday[i]->birthdate.day,
						listBirthday[i]->birthdate.month,
						listBirthday[i]->birthdate.year
					);
				}
				else break;
			}
		}

		byte1key = _getch();
		// ���� ������ [Esc] - ����� �� ������
		if (byte1key == KeysC::ESC) break;
	}

	// ������� ��������� ������������ ����������
	if (listBirthday) {
		for (size_t i = 0; i < lengthMan; i++) {
			if (listBirthday[i]) delete[] listBirthday[i];
			listBirthday[i] = nullptr;
		}
		delete[] listBirthday;
		listBirthday = nullptr;
	}
}


// ������� �������
int main() {
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Man** listMan = nullptr;      // ��������� �� ������ "������ man"
	size_t lengthMan = 0;         // ����� ������� "������ man"

	// �������������� ���������� ������� �������
	addRecord(setMan((char*)"������", (char*)"������", 35, 3, 7, 1985), listMan, lengthMan);
	addRecord(setMan((char*)"������", (char*)"������", 53, 8, 12, 1967), listMan, lengthMan);
	addRecord(setMan((char*)"�������", (char*)"����", 63, 2, 3, 1957), listMan, lengthMan);
	addRecord(setMan((char*)"�������", (char*)"����", 25, 11, 1, 1995), listMan, lengthMan);

	// ���������� ��� ��������� ������� ������
	char byte1key = '\0';
	char byte2key = '\0';

	// ���� ������ � ��������
	while (true) {
		titleScreen();
		printList(listMan, lengthMan);

		// ��������� ������� ������
		byte1key = _getch();
		if(_kbhit()) byte2key = _getch();

		// ���� ������ [Esc] - ����� �� ���������
		if (byte1key == KeysC::ESC) break;
		// ���� ������ [F1] - �������� ������ � ������ listMan
		else if ((byte1key == KeysF::BYTE1KEY) && (byte2key == KeysF::F1)) {
			addRecord(inputMan(), listMan, lengthMan);
		}
		// ���� ������ [F2] - ������� ��������� ������ �� ������� listMan
		else if ((byte1key == KeysF::BYTE1KEY) && (byte2key == KeysF::F2)) {
			delRecord(inputNumRecord(), listMan, lengthMan);
		}
		// ���� ������ [F4] - �������� ��������� ������ � ������� listMan
		else if ((byte1key == KeysF::BYTE1KEY) && (byte2key == KeysF::F4)) {
			editRecord(inputNumRecord(), listMan, lengthMan);
		}
		// ���� ������ [F5] - ����������� ������ listMan �� ����������� �������
		else if ((byte1key == KeysF::BYTE1KEY) && (byte2key == KeysF::F5)) {
			sortNames(FieldsListMan::SURNAME, listMan, lengthMan);
		}
		// ���� ������ [F6] - ����������� ������ listMan �� ����������� ����
		else if ((byte1key == KeysF::BYTE1KEY) && (byte2key == KeysF::F6)) {
			sortNames(FieldsListMan::NAME, listMan, lengthMan);
		}
		// ���� ������ [F7] - ������ � ������� listMan ������ �� �������
		else if ((byte1key == KeysF::BYTE1KEY) && (byte2key == KeysF::F7)) {
			searchSurname(listMan, lengthMan);
		}
		// ���� ������ [F8] - ������ � ������� listMan ������ �� �����
		else if ((byte1key == KeysF::BYTE1KEY) && (byte2key == KeysF::F8)) {
			searchName(listMan, lengthMan);
		}
		// ���� ������ [F9] - ������ � ������� listMan ������ 
		// � ����������� ���������� ������
		else if ((byte1key == KeysF::BYTE1KEY) && (byte2key == KeysF::F9)) {
			searchBirthdayManMonth(listMan, lengthMan);
		}
	}

	// ������� ��������� ������������ ����������
	if (listMan) {
		for (size_t i = 0; i < lengthMan; i++) {
			if (listMan[i]) delete[] listMan[i];
			listMan[i] = nullptr;
		}
		delete[] listMan;
		listMan = nullptr;
	}

	return 0;
}