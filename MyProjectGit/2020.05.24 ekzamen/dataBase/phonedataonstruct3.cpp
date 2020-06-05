// ���� "���������� ����������" �� ����������
#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>

const size_t lenrecord = 120;
const size_t numrecords = 64;
const size_t lenField = 24;
size_t length = lenField - 1;
size_t numField = 5;

struct Record {
	char* surname    = nullptr;
	char* name       = nullptr;
	char* patronymic = nullptr;
	char* phone      = nullptr;
	struct Birthdate{
		size_t year = 0;
		size_t month = 1;
		size_t day = 1;
	} birthdate;
};

struct FileAttribute {
	const char* name = "";
	FILE* data = nullptr;
	FILE** ptrData = &data;
};

const char* header[] = { "�������","���","��������","�������","�������","���","�����","����" };
Record* records = new Record[numrecords];

// ������� ������� �������
void openHelp(void) {
	printf_s("\n [F1]-������� �������\n\
 --------------------------------------------------------------------\n");

	printf_s(" �������� ����� ���������� �������\n");

	char byte1char = '\0';
	char byte2char = '\0';
	enum key0 { F1 = 59 };

	while (true) {
		// ��������� ������� ������ � ����
		byte1char = _getch();
		if (_kbhit()) byte2char = _getch();
		// F1-������� �������
		if ((byte1char == 0) && (byte2char == F1))	break;
	}
}

// ������� ������ ��������� ������ -------------------------------------------
void titleScreen(void) {
	system("cls");
	printf_s("\
 [Esc]-����� �� ���������, [F1]-������� ������� \n\
 [F2]-�������� �������, [F3]-�������� �������, [F4]-������� �������\n\
 [F5]-����� ���������,  [F10]-������� ��� �������� \n\
 �����������: [��������]-�� �����������, [Ctrl+Alt+��������]-�� ��������\n\
 -------------------------------------------------------------------\n");
}

// ������� ������ ������� records � ��������� ���� ---------------------------
void saveRecordsToTextFile(
	FileAttribute phone,
	bool delRecord = false,
	size_t numrecord = 0
) {
	fopen_s(phone.ptrData, phone.name, "w");
	for (size_t i = 0; i < numrecords; i++) {
		if (!records[i].surname) {
			if(delRecord) {
				Record currentrecord;
				records[i-1] = currentrecord;
			}
			break;
		}
		else if (delRecord && (i == numrecord)) continue;
		else {
			fprintf_s(phone.data, "%s,%s,%s,%s,%02d.%02d.%04d%c",
				records[i].surname,
				records[i].name,
				records[i].patronymic,
				records[i].phone,
				records[i].birthdate.day,
				records[i].birthdate.month,
				records[i].birthdate.year,
				'\x0a');
		}
	}
	fclose(phone.data);
}

// ������� ����� ������ ��������� ������� ------------------------------------
// � �������������� ������ ����� � ���������
char* insStr(void) {
	char* line = new char[lenField] {'\0'};
	scanf_s("%s", line, lenField);
	(void)_strlwr_s(line, lenField);
	line[0] = toupper(line[0]);
	return line;
}

// ������� ���������� ������ � ���� ------------------------------------------
void addRecord(FileAttribute phone) {
	printf_s(" ���������� �������� � �������\n");
	printf_s(
		" ��������� ���� �������� �������� ������ ������ %d ��������\n",
		lenField);
	Record currentrecord;

	// �������� ���� �������� ��������
	printf_s(" %s: ", header[0]);
	currentrecord.surname = insStr();
	printf_s(" �������: %s\n", currentrecord.surname);

	printf_s(" %s: ", header[1]);
	currentrecord.name = insStr();
	printf_s(" �������: %s\n", currentrecord.name);

	printf_s(" %s: ", header[2]);
	currentrecord.patronymic = insStr();
	printf_s(" �������: %s\n", currentrecord.patronymic);

	printf_s(" %s: ", header[3]);
	currentrecord.phone = insStr();
	printf_s(" �������: %s\n", currentrecord.phone);

	printf_s(" %s: ", header[5]);
	scanf_s("%d", &currentrecord.birthdate.year);
	printf_s(" �������: %04d\n", currentrecord.birthdate.year);

	printf_s(" %s: ", header[6]);
	scanf_s("%d", &currentrecord.birthdate.month);
	printf_s(" �������: %02d\n", currentrecord.birthdate.month);

	printf_s(" %s: ", header[7]);
	scanf_s("%d", &currentrecord.birthdate.day);
	printf_s(" �������: %02d\n", currentrecord.birthdate.day);

	// ������� ������ �������� � ������ ��������
	for (size_t i = 0; i < numrecords; i++)	{
		if (records[i].surname) continue;
		else {
			records[i] = currentrecord;
			break;
		}
	}
	// ������� ���������� ������ � ��������� ����
	saveRecordsToTextFile(phone);
}

// ������� ��������� ������ --------------------------------------------------
void insRecord(FileAttribute phone) {
	printf_s(" ��������� �������� � �������\n");
	int numrecord = 0;
	int* ptrnumrecord = &numrecord;
	printf_s(" ������� ����� ����������� ��������: ");
	scanf_s("%d", ptrnumrecord);
	numrecord--;  // �������� ����� ������������ � ������ � �������
	
	// ��������� �� ��������� � �������� ������� � �������
	if ((0 > numrecord) || (numrecord >= numrecords)) {
		printf_s(" ��������� ����� ��������, ������ %d, ������\n\
 ������������� ���������� ��������� ������� %d\n",
			(numrecord + 1), numrecords);
	}
	else {
		// ������� ���� ��������
		printf_s(" %s - %s: ", header[0], records[numrecord].surname);
		records[numrecord].surname = insStr();
		printf_s(" �������: %s\n", records[numrecord].surname);

		printf_s(" %s - %s: ", header[1], records[numrecord].name);
		records[numrecord].name = insStr();
		printf_s(" �������: %s\n", records[numrecord].name);

		printf_s(" %s - %s: ", header[2], records[numrecord].patronymic);
		records[numrecord].patronymic = insStr();
		printf_s(" �������: %s\n", records[numrecord].patronymic);

		printf_s(" %s - %s: ", header[3], records[numrecord].phone);
		records[numrecord].phone = insStr();
		printf_s(" �������: %s\n", records[numrecord].phone);

		printf_s(" %s - %s - %04d: ", header[4], header[5], records[numrecord].birthdate.year);
		scanf_s("%d", &records[numrecord].birthdate.year);
		printf_s(" �������: %04d\n", records[numrecord].birthdate.year);

		printf_s(" %s - %s - %02d: ", header[4], header[6], records[numrecord].birthdate.month);
		scanf_s("%d", &records[numrecord].birthdate.month);
		printf_s(" �������: %02d\n", records[numrecord].birthdate.month);

		printf_s(" %s - %s - %02d: ", header[4], header[7], records[numrecord].birthdate.day);
		scanf_s("%d", &records[numrecord].birthdate.day);
		printf_s(" �������: %02d\n", records[numrecord].birthdate.day);

		printf_s(" �����, �������: %02d.%02d.%04d\n",
			records[numrecord].birthdate.day,
			records[numrecord].birthdate.month,
			records[numrecord].birthdate.year);

		// ������� ���������� ������ � ��������� ����
		saveRecordsToTextFile(phone);
	}
}

// ������� �������� ������ ---------------------------------------------------
void delRecord(FileAttribute phone) {
	printf_s(" �������� �������� �� �������\n");
	int numrecord = 0;
	int* ptrnumrecord = &numrecord;
	printf_s(" ������� ����� ���������� ��������: ");
	scanf_s("%d", ptrnumrecord);
	numrecord--;	// �������� ����� ������������ � ������ � �������

	// ��������� ����� �� ��������� � �������� ������� � �������
	if ((0 > numrecord) || (numrecord >= numrecords)) {
		printf_s(" ��������� ����� ��������, ������ %d, ������\n\
 ������������� ���������� ��������� ������� %d\n",
			(numrecord + 1), numrecords);
	}
	else {
		// ������� ���������� ������ � ��������� ����
		saveRecordsToTextFile(phone, true, numrecord);
	}
}

// ������� �������� ���� ������� ---------------------------------------------
void delAllRecord(FileAttribute phone) {
	// ������ ���� ����
	system("del data.txt");
	// ������ ������ ������ ��������� records[]
	delete[] records;
	// �������� ����� ������ ��������� records[]
	records = new Record[numrecords];
}

// ������� ������ ������� ��� ����� ���������� -------------------------------
// �����: 0-9 ; ���������: A-Z, a-z - 51-77 ; �������: �-�, �-� - 101-133
size_t  rankSymbol(
	unsigned char symbol							// ����������� ������
) {
//	printf_s("symbol=%c\n", symbol);

	size_t symbolCode = 0;

	// ����� 0-9
	if (((unsigned char)'0' <= symbol) && (symbol <= (unsigned char)'9')) {
		symbolCode = (symbol - (unsigned char)'0');
	}
	// ��������� ��������� ������� A-Z
	else if (((unsigned char)'A' <= symbol) && (symbol <= (unsigned char)'Z')) {
		symbolCode = (symbol - (unsigned char)14);
	}
	// �������� ��������� ������� a-z
	else if (((unsigned char)'a' <= symbol) && (symbol <= (unsigned char)'z')) {
		symbolCode = (symbol - (unsigned char)46);
	}
	// ��������� ������� ������� �-�
	else if (((unsigned char)'�' <= symbol) && (symbol <= (unsigned char)'�')) {
		symbolCode = (symbol - (unsigned char)91);
	}
	// ��������� ������� ������ �
	else if (symbol == (unsigned char)'�') {
		symbolCode = (symbol - (unsigned char)61);
	}
	// ��������� ������� ������� �-�
	else if (((unsigned char)'�' <= symbol) && (symbol <= (unsigned char)'�')) {
		symbolCode = (symbol - (unsigned char)90);
	}
	// �������� ������� ������� �-�
	else if (((unsigned char)'�' <= symbol) && (symbol <= (unsigned char)'�')) {
		symbolCode = (symbol - (unsigned char)123);
	}
	// �������� ������� ������ �
	else if (symbol == (unsigned char)'�') {
		symbolCode = (symbol - (unsigned char)77);
	}
	// �������� ������� ������� �-�
	else if (((unsigned char)'�' <= symbol) && (symbol <= (unsigned char)'�')) {
		symbolCode = (symbol - (unsigned char)122);
	}
	// ������ ��������
	else {
		symbolCode = 0;
	}
	return symbolCode;
}

// ������� ��������� � ������������ ��������� �� ����������� -----------------
void minMaxArray(
	Record& one,			// ������� 1 (������ ���� ������)
	Record& two,			// ������� 2 (������ ���� ������)
	char byte1char,			// ����� ������������� ���� ��������
	size_t index			// ������ char-������� ������������� ����
) {
	Record buf;				// ��������������� ���������

	switch (byte1char) {
	case '1': {
		// ���� 1 > 2, �� ����������� �������� �������
		if(rankSymbol(one.surname[index]) > rankSymbol(two.surname[index])) {
			buf = one; one = two; two = buf;
		}
		// �����, ���� �������� �����, � �� ����� '\0'
		else if ((rankSymbol(one.surname[index]) ==
			      rankSymbol(two.surname[index])) &&
			(rankSymbol(one.surname[index]) != '\0') &&
			(rankSymbol(two.surname[index]) != '\0')) {
			// - ������� ��������� ������� ���������� ��� ���������
			//   ��������� �� ������� �������� ���������
			minMaxArray(one, two, byte1char, ++index);
		}
		// ����� (���� 1 <= 2 ��� ���� ���� ����� '\0') ������ �� ������ � ����� �� �������
		break;
	}
	case '2': {
		// ���� 1 > 2, �� ����������� �������� �������
		if (rankSymbol(one.name[index]) > rankSymbol(two.name[index])) {
			buf = one; one = two; two = buf;
		}
		// �����, ���� �������� �����, � �� ����� '\0'
		else if ((rankSymbol(one.name[index]) ==
			rankSymbol(two.name[index])) &&
			(rankSymbol(one.name[index]) != '\0') &&
			(rankSymbol(two.name[index]) != '\0')) {
			// - ������� ��������� ������� ���������� ��� ���������
			//   ��������� �� ������� �������� ���������
			minMaxArray(one, two, byte1char, ++index);
		}
		// ����� (���� 1 <= 2 ��� ���� ���� ����� '\0') ������ �� ������ � ����� �� �������
		break;
	}
	case '3': {
		// ���� 1 > 2, �� ����������� �������� �������
		if (rankSymbol(one.patronymic[index]) > rankSymbol(two.patronymic[index])) {
			buf = one; one = two; two = buf;
		}
		// �����, ���� �������� �����, � �� ����� '\0'
		else if ((rankSymbol(one.patronymic[index]) ==
			rankSymbol(two.patronymic[index])) &&
			(rankSymbol(one.patronymic[index]) != '\0') &&
			(rankSymbol(two.patronymic[index]) != '\0')) {
			// - ������� ��������� ������� ���������� ��� ���������
			//   ��������� �� ������� �������� ���������
			minMaxArray(one, two, byte1char, ++index);
		}
		// ����� (���� 1 <= 2 ��� ���� ���� ����� '\0') ������ �� ������ � ����� �� �������
		break;
	}
	case '4': {
		// ���� 1 > 2, �� ����������� �������� �������
		if (rankSymbol(one.phone[index]) > rankSymbol(two.phone[index])) {
			buf = one; one = two; two = buf;
		}
		// �����, ���� �������� �����, � �� ����� '\0'
		else if ((rankSymbol(one.phone[index]) ==
			rankSymbol(two.phone[index])) &&
			(rankSymbol(one.phone[index]) != '\0') &&
			(rankSymbol(two.phone[index]) != '\0')) {
			// - ������� ��������� ������� ���������� ��� ���������
			//   ��������� �� ������� �������� ���������
			minMaxArray(one, two, byte1char, ++index);
		}
		// ����� (���� 1 <= 2 ��� ���� ���� ����� '\0') ������ �� ������ � ����� �� �������
		break;
	}
	case '5': {
		// ���� ���_1 > ���_2, �� ����������� �������� �������
		if (one.birthdate.year > two.birthdate.year) {
			buf = one; one = two; two = buf;
		}
		// �����, ���� ���_1 == ���_2, �� ���������� ������
		else if (one.birthdate.year == two.birthdate.year) {
			// ���� �����_1 > �����_2, �� ����������� �������� �������
			if (one.birthdate.month > two.birthdate.month) {
				buf = one; one = two; two = buf;
			}
			// �����, ���� �����_1 == �����_2, �� ���������� ���
			else if (one.birthdate.month == two.birthdate.month) {
				// ���� ����_1 > ����_2, �� ����������� �������� �������
				if (one.birthdate.day > two.birthdate.day) {
					buf = one; one = two; two = buf;
				}
				// ����� ������ �� ������
			}
		}
	}
	}
}

// ������� ��������� � ������������ ��������� �� �������� --------------------
void maxMinArray(
	Record& one,			// ������� 1 (������ ���� ������)
	Record& two,			// ������� 2 (������ ���� ������)
	char byte2char,			// ����� ������������� ���� ��������
	size_t index			// ������ char-������� ������������� ����
) {
	Record buf;				// ��������������� ���������

	switch (byte2char) {
	case 120: {				// ������� Ctrl+Alt+1
		// ���� 1 < 2, �� ����������� �������� �������
		if (rankSymbol(one.surname[index]) < rankSymbol(two.surname[index])) {
			buf = one; one = two; two = buf;
		}
		// �����, ���� �������� �����, � �� ����� '\0'
		else if ((rankSymbol(one.surname[index]) ==
			rankSymbol(two.surname[index])) &&
			(rankSymbol(one.surname[index]) != '\0') &&
			(rankSymbol(two.surname[index]) != '\0')) {
			// - ������� ��������� ������� ���������� ��� ���������
			//   ��������� �� ������� �������� ���������
			maxMinArray(one, two, byte2char, ++index);
		}
		// ����� (���� 1 >= 2 ��� ���� ���� ����� '\0') ������ �� ������ � ����� �� �������
		break;
	}
	case 121: {				// ������� Ctrl+Alt+2
		// ���� 1 < 2, �� ����������� �������� �������
		if (rankSymbol(one.name[index]) < rankSymbol(two.name[index])) {
			buf = one; one = two; two = buf;
		}
		// �����, ���� �������� �����, � �� ����� '\0'
		else if ((rankSymbol(one.name[index]) ==
			rankSymbol(two.name[index])) &&
			(rankSymbol(one.name[index]) != '\0') &&
			(rankSymbol(two.name[index]) != '\0')) {
			// - ������� ��������� ������� ���������� ��� ���������
			//   ��������� �� ������� �������� ���������
			maxMinArray(one, two, byte2char, ++index);
		}
		// ����� (���� 1 >= 2 ��� ���� ���� ����� '\0') ������ �� ������ � ����� �� �������
		break;
	}
	case 122: {				// ������� Ctrl+Alt+3
		// ���� 1 < 2, �� ����������� �������� �������
		if (rankSymbol(one.patronymic[index]) < rankSymbol(two.patronymic[index])) {
			buf = one; one = two; two = buf;
		}
		// �����, ���� �������� �����, � �� ����� '\0'
		else if ((rankSymbol(one.patronymic[index]) ==
			rankSymbol(two.patronymic[index])) &&
			(rankSymbol(one.patronymic[index]) != '\0') &&
			(rankSymbol(two.patronymic[index]) != '\0')) {
			// - ������� ��������� ������� ���������� ��� ���������
			//   ��������� �� ������� �������� ���������
			maxMinArray(one, two, byte2char, ++index);
		}
		// ����� (���� 1 >= 2 ��� ���� ���� ����� '\0') ������ �� ������ � ����� �� �������
		break;
	}
	case 123: {				// ������� Ctrl+Alt+4
		// ���� 1 < 2, �� ����������� �������� �������
		if (rankSymbol(one.phone[index]) < rankSymbol(two.phone[index])) {
			buf = one; one = two; two = buf;
		}
		// �����, ���� �������� �����, � �� ����� '\0'
		else if ((rankSymbol(one.phone[index]) ==
			rankSymbol(two.phone[index])) &&
			(rankSymbol(one.phone[index]) != '\0') &&
			(rankSymbol(two.phone[index]) != '\0')) {
			// - ������� ��������� ������� ���������� ��� ���������
			//   ��������� �� ������� �������� ���������
			maxMinArray(one, two, byte2char, ++index);
		}
		// ����� (���� 1 >= 2 ��� ���� ���� ����� '\0') ������ �� ������ � ����� �� �������
		break;
	}
	case 124: {				// ������� Ctrl+Alt+5
		// ���� ���_1 < ���_2, �� ����������� �������� �������
		if (one.birthdate.year < two.birthdate.year) {
			buf = one; one = two; two = buf;
		}
		// �����, ���� ���_1 == ���_2, �� ���������� ������
		else if (one.birthdate.year == two.birthdate.year) {
			// ���� �����_1 < �����_2, �� ����������� �������� �������
			if (one.birthdate.month < two.birthdate.month) {
				buf = one; one = two; two = buf;
			}
			// �����, ���� �����_1 == �����_2, �� ���������� ���
			else if (one.birthdate.month == two.birthdate.month) {
				// ���� ����_1 < ����_2, �� ����������� �������� �������
				if (one.birthdate.day < two.birthdate.day) {
					buf = one; one = two; two = buf;
				}
				// ����� ������ �� ������
			}
		}
	}
	}
}

// ������� ���������� ������� records �� ����������� ��������� ���� ----------
void sortFieldAscend(Record* records, char byte1char, FileAttribute phone) {
	// ���� � ������� ��� ��������� - ����� �� �������
	if (!records[0].surname) return;

	// ���������� ������� �� ���������� ����
	for (size_t i = 1; i < numrecords; i++)	{
		if (!records[i].surname) break;
		for (size_t j = 1; j < numrecords; j++)	{
			if (!records[j].surname) break;
			minMaxArray(records[j - 1], records[j], byte1char, 0);
		}
	}
	// ������� ���������� ������ � ��������� ����
	saveRecordsToTextFile(phone);
}

// ������� ���������� ������� records �� �������� ��������� ���� -------------
void sortFieldDeascend(Record* records, char byte2char, FileAttribute phone) {
	// ���� � ������� ��� ��������� - ����� �� �������
	if (!records[0].surname) return;

	// ���������� ������� �� ���������� ����
	for (size_t i = 1; i < numrecords; i++) {
		if (!records[i].surname) break;
		for (size_t j = 1; j < numrecords; j++) {
			if (!records[j].surname) break;
			maxMinArray(records[j - 1], records[j], byte2char, 0);
		}
	}
	// ������� ���������� ������ � ��������� ����
	saveRecordsToTextFile(phone);
}

// ������� ���������, ��� ������ ���� � ������� ���������
// ������ (�� ����������� ��������) ������ � �������
bool lessStr(
	size_t numField,
	Record searchRecord,
	char* searchArg1
) {
	bool condition = false;
	// ��������� ��������� ����� ������ length (��. � ������ ���������)
	for (size_t i = 0; i < length; i++) {
		// ���� ������ ���� ������� ����� ������� � ������� � ��� �� ����� '\0'
		if ((rankSymbol(searchArg1[i]) ==
			rankSymbol((&searchRecord.surname)[numField - 1][i])) &&
			(rankSymbol(searchArg1[i]) != '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) != '\0')) {
			// ������ �� ������ � ���������� � ��������� ��������
			continue;
		}
		// �����, ���� ������ ���� ������� ������ ������� � ������� � ��� �� ����� '\0'
		else if ((rankSymbol(searchArg1[i]) >
			rankSymbol((&searchRecord.surname)[numField - 1][i])) &&
			(rankSymbol(searchArg1[i]) != '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) != '\0')) {
			condition = true;	// - ������� ��� ������� �������,
			break;				// � ����� �� �����
		}
		// �����, ���� ������ ���� ������� ������ ������� � ������� � ��� �� ����� '\0'
		else if ((rankSymbol(searchArg1[i]) <
			rankSymbol((&searchRecord.surname)[numField - 1][i])) &&
			(rankSymbol(searchArg1[i]) != '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) != '\0')) {
			condition = false;	// - ������� ��� ������� �����,
			break;				// � ����� �� �����
		}
		// �����, ���� ������ ���� ������� ����� '\0',
		// � ������ � ������� �� ����� '\0'
		else if ((rankSymbol(searchArg1[i]) != '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) == '\0')) {
			condition = true;	// - ������� ��� ������� �������,
			break;				// � ����� �� �����
		}
		// �����, ���� ������ ���� ������� �� ����� '\0',
		// � ������ � ������� ����� '\0'
		else if ((rankSymbol(searchArg1[i]) == '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) != '\0')) {
			condition = false;	// - ������� ��� ������� �����,
			break;				// � ����� �� �����
		}
		// �����, ���� ������ ���� ������� � ������ ���������� ������� ����� '\0'
		else if ((rankSymbol(searchArg1[i]) == '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) == '\0')) {
			condition = false;	// - ������� ��� ������� �����,
			break;				// � ����� �� �����
		}
		// �����, ��� ������ ����������
		else {
			condition = false;	// - �������, ��� ������� �����
			break;				// � ����� �� �����
		}
	}
	// � ���������� ������������ ���������
	return condition;
}

// ������� ���������, ��� ���� �������� � ������� ���������
// ������ ��������� � �������
bool lessNum(
	Record searchRecord,
	size_t searchYear1,
	size_t searchMonth1,
	size_t searchDay1
) {
	if (searchYear1 && (searchRecord.birthdate.year < searchYear1)) return true;
	else if (searchYear1 && (searchRecord.birthdate.year > searchYear1)) return false;

	else if (searchMonth1 && (searchRecord.birthdate.month < searchMonth1)) return true;
	else if (searchMonth1 && (searchRecord.birthdate.month > searchMonth1)) return false;

	else if (searchDay1 && (searchRecord.birthdate.day < searchDay1)) return true;
	else if (searchDay1 && (searchRecord.birthdate.day > searchDay1)) return false;

	else return false;
}

// ������� ���������, ��� ������ ���� � ������� ���������
// ������ (�� ����������� ��������) ������ � �������
bool moreStr(
	size_t numField,
	Record searchRecord,
	char* searchArg1
) {
	bool condition = false;
	// ��������� ��������� ����� ������ length (��. � ������ ���������)
	for (size_t i = 0; i < length; i++) {
		// ���� ������ ���� ������� ����� ������� � ������� � ��� �� ����� '\0'
		if ((rankSymbol(searchArg1[i]) ==
			rankSymbol((&searchRecord.surname)[numField - 1][i])) &&
			(rankSymbol(searchArg1[i]) != '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) != '\0')) {
			// ������ �� ������ � ���������� � ��������� ��������
			continue;
		}
		// �����, ���� ������ ���� ������� ������ ������� � ������� � ��� �� ����� '\0'
		else if ((rankSymbol(searchArg1[i]) <
			rankSymbol((&searchRecord.surname)[numField - 1][i])) &&
			(rankSymbol(searchArg1[i]) != '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) != '\0')) {
			condition = true;	// - ������� ��� ������� �������,
			break;				// � ����� �� �����
		}
		// �����, ���� ������ ���� ������� ������ ������� � ������� � ��� �� ����� '\0'
		else if ((rankSymbol(searchArg1[i]) >
			rankSymbol((&searchRecord.surname)[numField - 1][i])) &&
			(rankSymbol(searchArg1[i]) != '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) != '\0')) {
			condition = false;	// - ������� ��� ������� �����,
			break;				// � ����� �� �����
		}
		// �����, ���� ������ ���� ������� �� ����� '\0',
		// � ������ � ������� ����� '\0'
		else if ((rankSymbol(searchArg1[i]) == '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) != '\0')) {
			condition = true;	// - ������� ��� ������� �������,
			break;				// � ����� �� �����
		}
		// �����, ���� ������ ���� ������� ����� '\0',
		// � ������ � ������� �� ����� '\0'
		else if ((rankSymbol(searchArg1[i]) != '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) == '\0')) {
			condition = false;	// - ������� ��� ������� �����,
			break;				// � ����� �� �����
		}
		// �����, ���� ������ ���� ������� � ������ ���������� ������� ����� '\0'
		else if ((rankSymbol(searchArg1[i]) == '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) == '\0')) {
			condition = false;	// - ������� ��� ������� �����,
			break;				// � ����� �� �����
		}
		// �����, ��� ������ ����������
		else {
			condition = false;	// - �������, ��� ������� �����
			break;				// � ����� �� �����
		}
	}
	// � ���������� ������������ ���������
	return condition;
}

// ������� ��������� ��� ���� �������� � ������� ���������
// ������ ��������� � �������
bool moreNum(
	Record searchRecord,
	size_t searchYear1,
	size_t searchMonth1,
	size_t searchDay1
) {
	if      (searchYear1 && (searchRecord.birthdate.year > searchYear1)) return true;
	else if (searchYear1 && (searchRecord.birthdate.year < searchYear1)) return false;

	else if (searchMonth1 && (searchRecord.birthdate.month > searchMonth1)) return true;
	else if (searchMonth1 && (searchRecord.birthdate.month < searchMonth1)) return false;

	else if (searchDay1 && (searchRecord.birthdate.day > searchDay1)) return true;
	else if (searchDay1 && (searchRecord.birthdate.day < searchDay1)) return false;

	else return false;
}

// ������� ��������� �� ����������� ��������� ����� �������
bool notEqualStr(
	size_t numField,
	Record searchRecord,
	char* searchArg1
) {
	// ��������� ��������� ����� ������ length (��. � ������ ���������)
	for (size_t i = 0; i < length; i++) {
		// ���� ������� ����� �����, � �� ����� '\0'
		if ((rankSymbol(searchArg1[i]) ==
			rankSymbol((&searchRecord.surname)[numField - 1][i])) &&
			(rankSymbol(searchArg1[i]) != '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) != '\0')) {
			// - ������ �� ������, ���������� � ��������� ��������
			continue;
		}
		// �����, ���� ������� ����� �����, � ����� '\0'
		else if ((rankSymbol(searchArg1[i]) ==
			rankSymbol((&searchRecord.surname)[numField - 1][i])) &&
			(rankSymbol(searchArg1[i]) == '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) == '\0')) {
			// - ���������� false
			return false;
		}
		// ����� (���� ������� ����� �� �����) - ���������� true
		else return true;
	}
	return false;
}

// ������� ��������� �� ����������� �������� ����� ���� ��������
bool notEqualNum(
	Record searchRecord,
	size_t searchYear1,
	size_t searchMonth1,
	size_t searchDay1
) {
	if ((searchYear1  && (searchRecord.birthdate.year  != searchYear1))  ||
		(searchMonth1 && (searchRecord.birthdate.month != searchMonth1)) ||
		(searchDay1   && (searchRecord.birthdate.day   != searchDay1))) {
		return true;
	}
	return false;
}

// ������� ��������� �� ��������� ��������� ����� �������
bool equallyStr(
	size_t numField,
	Record searchRecord,
	char* searchArg1
) {
	// ��������� ��������� ����� ������ length (��. � ������ ���������)
	for (size_t i = 0; i < length; i++) {
		// ���� ������� ����� �����, � �� ����� '\0'
		if ((rankSymbol(searchArg1[i]) ==
			rankSymbol((&searchRecord.surname)[numField - 1][i])) &&
			(rankSymbol(searchArg1[i]) != '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) != '\0')) {
			// - ������ �� ������, ���������� � ��������� ��������
			continue;
		}
		// �����, ���� ������� ����� �����, � ����� '\0'
		else if ((rankSymbol(searchArg1[i]) ==
			rankSymbol((&searchRecord.surname)[numField - 1][i])) &&
			(rankSymbol(searchArg1[i]) == '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) == '\0')) {
			// - ���������� true
			return true;
		}
		// ����� (���� ������� ����� �� �����) - ���������� false
		else return false;
	}
	return false;
}

// ������� ��������� �� ��������� �������� ����� ���� ��������
bool equallyNum(
	Record searchRecord,
	size_t searchYear1,
	size_t searchMonth1,
	size_t searchDay1
) {
	if ((!searchYear1  || (searchRecord.birthdate.year  == searchYear1))  &&
		(!searchMonth1 || (searchRecord.birthdate.month == searchMonth1)) &&
		(!searchDay1   || (searchRecord.birthdate.day   == searchDay1))) {
		return true;
	}
	return false;
}

// ������� ������ ���������
void searchRecord(Record* records) {
	Record* searchRecords = new Record[numrecords];
	size_t numField = 0;
	size_t lenArg = 32;
	char operation = '\0';
	char* operationS = new char[lenArg] {'\0'};
	char* searchArg1 = new char[lenArg] {'\0'};
	char* searchArg2 = new char[lenArg] {'\0'};
	size_t searchYear1 = 0;
	size_t searchMonth1 = 0;
	size_t searchDay1 = 0;

	// ��������� ���������� ������� records � ������ searchRecords
	for (size_t i = 0; i < numrecords; i++)	{
		if (!records[i].surname) break;
		searchRecords[i] = records[i];
	}

	// ���� ������ � ������� �������
	while (true) {
		system("cls");
		printf_s(" ����� ��������\n");

		// ����� �� ����� ��������� ������� ���������
		printf_s("  �  %-14s %-9s %-16s %-11s %-s\n",
			header[0],
			header[1],
			header[2],
			header[3],
			header[4]
		);
		printf_s("       [1]          [2]         [3]              [4]         [5]\n");

		// ����� ������� searchRecords �� �����
		for (size_t i = 0; i < numrecords; i++)	{
			if (!searchRecords[i].surname) continue;
			printf_s("%3d  %-12s %-10s %-15s %-12s %02d.%02d.%04d\n", (i + 1),
				searchRecords[i].surname,
				searchRecords[i].name,
				searchRecords[i].patronymic,
				searchRecords[i].phone,
				searchRecords[i].birthdate.day,
				searchRecords[i].birthdate.month,
				searchRecords[i].birthdate.year
			);
		}

		printf_s("\
 [6]-����� �� ������ ������\n\
 ������� �������� ��� ����� ���������� �������� ��������: ");
		scanf_s("%d", &numField);

		if ((numField < 1) || (6 < numField)) numField = 6;
		if (numField == 6) return;
		if (numField < 5) {
			printf_s("\n\
 ������� ������� ������ �� ���������� ����. ������ ������� ������:\n\
 <��� ��������> <������> <��������>\n\
     (��� ��������: =(�����), !(�� �����), <(������), >(������))\n");
			printf_s("%s: ", header[(numField - 1)]);
			scanf_s("%s %s", operationS, lenArg, searchArg1, lenArg);
			operation = operationS[0];
		}
		else if (numField == 5) {
			searchYear1 = 0;
			searchMonth1 = 0;
			searchDay1 = 0;
			printf_s("\n\
 ������� ������� ������ �� ���������� ����. ������ ������� ������:\n\
 <��� ��������> <Enter>\n\
     (��� ��������: =(�����), !(�� �����), <(������), >(������))\n\
 <���> <Enter>\n\
 <�����> <Enter>\n\
 <����> <Enter>\n\
 � ��������� ����, ������ ��� ��� ������� 0, ���� �� ���������� �� �����\n\
");
			printf_s(" ������� ��������: ");
			scanf_s("%s", operationS, lenArg);
			operation = operationS[0];

			printf_s(" ������� ���: ");
			scanf_s("%4d", &searchYear1);

			printf_s(" ������� �����: ");
			scanf_s("%2d", &searchMonth1);

			printf_s(" ������� ����: ");
			scanf_s("%2d", &searchDay1);
		}

		Record* searchRecordsBuf = new Record[numrecords];
		bool copyRecord = false;

		// ������� � ������ searchRecordsBuf
		// ������ �� ������� searchRecords
		// ��������������� �������� ��������
		for (size_t i = 0, j= 0; i < numrecords; i++)	{
			if (!searchRecords[i].surname) break;

			switch (operation) {
			case '=': {
				if (numField < 5) {
					copyRecord = equallyStr(numField, searchRecords[i], searchArg1);
				}
				else if (numField == 5) {
					copyRecord = equallyNum(searchRecords[i], searchYear1, searchMonth1, searchDay1);
				}
				break;
			}
			case '!': {
				if (numField < 5) {
					copyRecord = notEqualStr(numField, searchRecords[i], searchArg1);
				}
				else if (numField == 5) {
					copyRecord = notEqualNum(searchRecords[i], searchYear1, searchMonth1, searchDay1);
				}
				break;
			}
			case '>': {
				if (numField < 5) {
					copyRecord = moreStr(numField, searchRecords[i], searchArg1);
				}
				else if (numField == 5) {
					copyRecord = moreNum(searchRecords[i], searchYear1, searchMonth1, searchDay1);
				}
				break;
			}
			case '<': {
				if (numField < 5) {
					copyRecord = lessStr(numField, searchRecords[i], searchArg1);
				}
				else if (numField == 5) {
					copyRecord = lessNum(searchRecords[i], searchYear1, searchMonth1, searchDay1);
				}
				break;
			}
			}

			if (copyRecord) searchRecordsBuf[j++] = searchRecords[i];
			copyRecord = false;
		}

		// �������� ������ searchRecordsBuf
		// � ������ searchRecords
		// �� ������ �� �����
		for (size_t i = 0; i < numrecords; i++)	{
			searchRecords[i] = searchRecordsBuf[i];
		}

		delete[] searchRecordsBuf;
	}
	delete[] searchRecords;
}

// ������� ������� -----------------------------------------------------------
int main() {
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("title ���������� ����������");

	char byte1char = '\0';
	char byte2char = '\0';
	enum keys { ENTER = 13, ESC = 27 };
	enum key0 { F1 = 59, F2, F3, F4, F5, F6, F7, F8, F9, F10,
		CTRL_ALT_1 = 120, CTRL_ALT_2, CTRL_ALT_3, CTRL_ALT_4, CTRL_ALT_5 };

	FileAttribute phone;
	phone.name = "data.txt";

	while (true) {
		titleScreen();

		// ������� ���� ��� �������� ������� ����� ���������� ����
		if (fopen_s(phone.ptrData, phone.name, "r")) {
			printf_s(" � ���������� ����������� ��� ���������\n");
		}
		else {
			// ����� �� ����� ��������� ������� ���������
			printf_s("  �  %-14s %-9s %-16s %-11s %-s\n",
				header[0],
				header[1],
				header[2],
				header[3],
				header[4]
			);
			printf_s("       [1]          [2]         [3]              [4]         [5]\n");

			// ������� ���� ��������� � ������� ������ � ��������� currentrecord � � ������ records
			Record currentrecord;
			char* line = nullptr;
			char* contex = nullptr;
			char** ptrcontex = &contex;
			for (size_t i = 0; i < numrecords; i++) {
				line = new char[lenrecord] { '\0' };

				if (fgets(line, lenrecord, phone.data)) {
					contex = line;
					currentrecord.surname    = strtok_s(contex, ",", ptrcontex);
					currentrecord.name       = strtok_s(contex, ",", ptrcontex);
					currentrecord.patronymic = strtok_s(contex, ",", ptrcontex);
					currentrecord.phone      = strtok_s(contex, ",", ptrcontex);
					currentrecord.birthdate.day   = atoi(strtok_s(contex, ".", ptrcontex));
					currentrecord.birthdate.month = atoi(strtok_s(contex, ".", ptrcontex));
					currentrecord.birthdate.year  = atoi(strtok_s(contex, "\n", ptrcontex));
					records[i] = currentrecord;

					// ������� �� �����
					printf_s("%3d  %-12s %-10s %-15s %-12s %02d.%02d.%04d\n", (i + 1),
						records[i].surname,
						records[i].name,
						records[i].patronymic,
						records[i].phone,
						records[i].birthdate.day,
						records[i].birthdate.month,
						records[i].birthdate.year
					);
				}
				else {
					delete[] line;
					break;
				}
			}
			fclose(phone.data);
		}

		// ��������� ������� ������ � ��������� ����
		byte1char = _getch();
		if (_kbhit()) byte2char = _getch();
		// Esc - ����� �� ���������
		if (byte1char == ESC) break;
		// 1...5 - ����������� �������� �� �����������
		else if (('1' <= byte1char) && (byte1char <= '5'))
			sortFieldAscend(records, byte1char, phone);
		// Ctrl + Alt + (1...5) - ����������� �������� �� ��������
		else if ((byte1char == 0) &&
			(CTRL_ALT_1 <= byte2char) && (byte2char <= CTRL_ALT_5))
			sortFieldDeascend(records, byte2char, phone);
		// F1-������� �������
		else if ((byte1char == 0) && (byte2char == F1)) openHelp();
		// F2-�������� �������
		else if ((byte1char == 0) && (byte2char == F2))	addRecord(phone);
		// F3-�������� �������
		else if ((byte1char == 0) && (byte2char == F3))	insRecord(phone);
		// F4-������� �������
		else if ((byte1char == 0) && (byte2char == F4))	delRecord(phone);
		// F5-������ �������(�)
		else if ((byte1char == 0) && (byte2char == F5))	searchRecord(records);
		// F10-������� ��� ��������
		else if ((byte1char == 0) && (byte2char == F10)) delAllRecord(phone);
	}
	delete[] records;
	return 0;
}