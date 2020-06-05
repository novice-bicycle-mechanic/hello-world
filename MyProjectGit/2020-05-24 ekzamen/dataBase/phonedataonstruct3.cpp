// база "Телефонный справочник" на структурах
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

const char* header[] = { "Фамилия","Имя","Отчество","Телефон","Родился","Год","Месяц","День" };
Record* records = new Record[numrecords];

// ФУНКЦИЯ открыть справку
void openHelp(void) {
	printf_s("\n [F1]-закрыть справку\n\
 --------------------------------------------------------------------\n");

	printf_s(" Напишите здесь содержание справки\n");

	char byte1char = '\0';
	char byte2char = '\0';
	enum key0 { F1 = 59 };

	while (true) {
		// обработка нажатий клавиш в меню
		byte1char = _getch();
		if (_kbhit()) byte2char = _getch();
		// F1-закрыть справку
		if ((byte1char == 0) && (byte2char == F1))	break;
	}
}

// ФУНКЦИЯ вывода заголовка экрана -------------------------------------------
void titleScreen(void) {
	system("cls");
	printf_s("\
 [Esc]-выход из программы, [F1]-открыть справку \n\
 [F2]-добавить контакт, [F3]-изменить контакт, [F4]-удалить контакт\n\
 [F5]-поиск контактов,  [F10]-удалить все контакты \n\
 Сортировать: [№столбца]-по возрастанию, [Ctrl+Alt+№столбца]-по убыванию\n\
 -------------------------------------------------------------------\n");
}

// ФУНКЦИЯ записи массива records в текстовый файл ---------------------------
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

// ФУНКЦИЯ ввода строки строчными буквами ------------------------------------
// и преобразования первой буквы в прописную
char* insStr(void) {
	char* line = new char[lenField] {'\0'};
	scanf_s("%s", line, lenField);
	(void)_strlwr_s(line, lenField);
	line[0] = toupper(line[0]);
	return line;
}

// ФУНКЦИЯ добавления записи в файл ------------------------------------------
void addRecord(FileAttribute phone) {
	printf_s(" Добавление контакта в таблицу\n");
	printf_s(
		" Заполните поля контакта записями длиной меньше %d символов\n",
		lenField);
	Record currentrecord;

	// заполним поля контакта записями
	printf_s(" %s: ", header[0]);
	currentrecord.surname = insStr();
	printf_s(" Принято: %s\n", currentrecord.surname);

	printf_s(" %s: ", header[1]);
	currentrecord.name = insStr();
	printf_s(" Принято: %s\n", currentrecord.name);

	printf_s(" %s: ", header[2]);
	currentrecord.patronymic = insStr();
	printf_s(" Принято: %s\n", currentrecord.patronymic);

	printf_s(" %s: ", header[3]);
	currentrecord.phone = insStr();
	printf_s(" Принято: %s\n", currentrecord.phone);

	printf_s(" %s: ", header[5]);
	scanf_s("%d", &currentrecord.birthdate.year);
	printf_s(" Принято: %04d\n", currentrecord.birthdate.year);

	printf_s(" %s: ", header[6]);
	scanf_s("%d", &currentrecord.birthdate.month);
	printf_s(" Принято: %02d\n", currentrecord.birthdate.month);

	printf_s(" %s: ", header[7]);
	scanf_s("%d", &currentrecord.birthdate.day);
	printf_s(" Принято: %02d\n", currentrecord.birthdate.day);

	// запишем строку контакта в массив структур
	for (size_t i = 0; i < numrecords; i++)	{
		if (records[i].surname) continue;
		else {
			records[i] = currentrecord;
			break;
		}
	}
	// запишем измененный массив в текстовый файл
	saveRecordsToTextFile(phone);
}

// ФУНКЦИЯ изменения записи --------------------------------------------------
void insRecord(FileAttribute phone) {
	printf_s(" Изменение контакта в таблице\n");
	int numrecord = 0;
	int* ptrnumrecord = &numrecord;
	printf_s(" Введите номер изменяемого контакта: ");
	scanf_s("%d", ptrnumrecord);
	numrecord--;  // приводим номер человеческий к номеру в массиве
	
	// проверяем на вхождение в диапазон номеров в массиве
	if ((0 > numrecord) || (numrecord >= numrecords)) {
		printf_s(" Введенный номер контакта, равный %d, больше\n\
 максимального количества контактов равного %d\n",
			(numrecord + 1), numrecords);
	}
	else {
		// изменим поля контакта
		printf_s(" %s - %s: ", header[0], records[numrecord].surname);
		records[numrecord].surname = insStr();
		printf_s(" Принято: %s\n", records[numrecord].surname);

		printf_s(" %s - %s: ", header[1], records[numrecord].name);
		records[numrecord].name = insStr();
		printf_s(" Принято: %s\n", records[numrecord].name);

		printf_s(" %s - %s: ", header[2], records[numrecord].patronymic);
		records[numrecord].patronymic = insStr();
		printf_s(" Принято: %s\n", records[numrecord].patronymic);

		printf_s(" %s - %s: ", header[3], records[numrecord].phone);
		records[numrecord].phone = insStr();
		printf_s(" Принято: %s\n", records[numrecord].phone);

		printf_s(" %s - %s - %04d: ", header[4], header[5], records[numrecord].birthdate.year);
		scanf_s("%d", &records[numrecord].birthdate.year);
		printf_s(" Принято: %04d\n", records[numrecord].birthdate.year);

		printf_s(" %s - %s - %02d: ", header[4], header[6], records[numrecord].birthdate.month);
		scanf_s("%d", &records[numrecord].birthdate.month);
		printf_s(" Принято: %02d\n", records[numrecord].birthdate.month);

		printf_s(" %s - %s - %02d: ", header[4], header[7], records[numrecord].birthdate.day);
		scanf_s("%d", &records[numrecord].birthdate.day);
		printf_s(" Принято: %02d\n", records[numrecord].birthdate.day);

		printf_s(" Итого, принято: %02d.%02d.%04d\n",
			records[numrecord].birthdate.day,
			records[numrecord].birthdate.month,
			records[numrecord].birthdate.year);

		// запишем измененный массив в текстовый файл
		saveRecordsToTextFile(phone);
	}
}

// ФУНКЦИЯ удаления записи ---------------------------------------------------
void delRecord(FileAttribute phone) {
	printf_s(" Удаление контакта из таблицы\n");
	int numrecord = 0;
	int* ptrnumrecord = &numrecord;
	printf_s(" Введите номер удаляемого контакта: ");
	scanf_s("%d", ptrnumrecord);
	numrecord--;	// приводим номер человеческий к номеру в массиве

	// проверяем номер на вхождение в диапазон номеров в массиве
	if ((0 > numrecord) || (numrecord >= numrecords)) {
		printf_s(" Введенный номер контакта, равный %d, больше\n\
 максимального количества контактов равного %d\n",
			(numrecord + 1), numrecords);
	}
	else {
		// запишем измененный массив в текстовый файл
		saveRecordsToTextFile(phone, true, numrecord);
	}
}

// ФУНКЦИЯ удаления всех записей ---------------------------------------------
void delAllRecord(FileAttribute phone) {
	// удалим файл базы
	system("del data.txt");
	// удалим старый массив контактов records[]
	delete[] records;
	// создадим новый массив контактов records[]
	records = new Record[numrecords];
}

// ФУНКЦИЯ оценки символа для целей сортировки -------------------------------
// цифры: 0-9 ; латинские: A-Z, a-z - 51-77 ; русские: А-Я, а-я - 101-133
size_t  rankSymbol(
	unsigned char symbol							// оцениваемый символ
) {
//	printf_s("symbol=%c\n", symbol);

	size_t symbolCode = 0;

	// цифры 0-9
	if (((unsigned char)'0' <= symbol) && (symbol <= (unsigned char)'9')) {
		symbolCode = (symbol - (unsigned char)'0');
	}
	// прописные латинские символы A-Z
	else if (((unsigned char)'A' <= symbol) && (symbol <= (unsigned char)'Z')) {
		symbolCode = (symbol - (unsigned char)14);
	}
	// строчные латинские символы a-z
	else if (((unsigned char)'a' <= symbol) && (symbol <= (unsigned char)'z')) {
		symbolCode = (symbol - (unsigned char)46);
	}
	// прописные русские символы А-Е
	else if (((unsigned char)'А' <= symbol) && (symbol <= (unsigned char)'Е')) {
		symbolCode = (symbol - (unsigned char)91);
	}
	// прописной русский символ Ё
	else if (symbol == (unsigned char)'Ё') {
		symbolCode = (symbol - (unsigned char)61);
	}
	// прописные русские символы Ж-Я
	else if (((unsigned char)'Ж' <= symbol) && (symbol <= (unsigned char)'Я')) {
		symbolCode = (symbol - (unsigned char)90);
	}
	// строчные русские символы а-е
	else if (((unsigned char)'а' <= symbol) && (symbol <= (unsigned char)'е')) {
		symbolCode = (symbol - (unsigned char)123);
	}
	// строчный русский символ ё
	else if (symbol == (unsigned char)'ё') {
		symbolCode = (symbol - (unsigned char)77);
	}
	// строчные русские символы ж-я
	else if (((unsigned char)'ж' <= symbol) && (symbol <= (unsigned char)'я')) {
		symbolCode = (symbol - (unsigned char)122);
	}
	// прочие значения
	else {
		symbolCode = 0;
	}
	return symbolCode;
}

// ФУНКЦИЯ сравнения и перестановки элементов на возрастание -----------------
void minMaxArray(
	Record& one,			// элемент 1 (должен быть меньше)
	Record& two,			// элемент 2 (должен быть больше)
	char byte1char,			// номер сравниваемого поля структур
	size_t index			// индекс char-массива сравниваемого поля
) {
	Record buf;				// вспомогательная структура

	switch (byte1char) {
	case '1': {
		// если 1 > 2, то переставить элементы местами
		if(rankSymbol(one.surname[index]) > rankSymbol(two.surname[index])) {
			buf = one; one = two; two = buf;
		}
		// иначе, если элементы равны, и не равны '\0'
		else if ((rankSymbol(one.surname[index]) ==
			      rankSymbol(two.surname[index])) &&
			(rankSymbol(one.surname[index]) != '\0') &&
			(rankSymbol(two.surname[index]) != '\0')) {
			// - вызвать настоящую функцию рекурсивно для сравнения
			//   следующих по порядку символов элементов
			minMaxArray(one, two, byte1char, ++index);
		}
		// иначе (если 1 <= 2 или хоть один равен '\0') ничего не делать и выйти из функции
		break;
	}
	case '2': {
		// если 1 > 2, то переставить элементы местами
		if (rankSymbol(one.name[index]) > rankSymbol(two.name[index])) {
			buf = one; one = two; two = buf;
		}
		// иначе, если элементы равны, и не равны '\0'
		else if ((rankSymbol(one.name[index]) ==
			rankSymbol(two.name[index])) &&
			(rankSymbol(one.name[index]) != '\0') &&
			(rankSymbol(two.name[index]) != '\0')) {
			// - вызвать настоящую функцию рекурсивно для сравнения
			//   следующих по порядку символов элементов
			minMaxArray(one, two, byte1char, ++index);
		}
		// иначе (если 1 <= 2 или хоть один равен '\0') ничего не делать и выйти из функции
		break;
	}
	case '3': {
		// если 1 > 2, то переставить элементы местами
		if (rankSymbol(one.patronymic[index]) > rankSymbol(two.patronymic[index])) {
			buf = one; one = two; two = buf;
		}
		// иначе, если элементы равны, и не равны '\0'
		else if ((rankSymbol(one.patronymic[index]) ==
			rankSymbol(two.patronymic[index])) &&
			(rankSymbol(one.patronymic[index]) != '\0') &&
			(rankSymbol(two.patronymic[index]) != '\0')) {
			// - вызвать настоящую функцию рекурсивно для сравнения
			//   следующих по порядку символов элементов
			minMaxArray(one, two, byte1char, ++index);
		}
		// иначе (если 1 <= 2 или хоть один равен '\0') ничего не делать и выйти из функции
		break;
	}
	case '4': {
		// если 1 > 2, то переставить элементы местами
		if (rankSymbol(one.phone[index]) > rankSymbol(two.phone[index])) {
			buf = one; one = two; two = buf;
		}
		// иначе, если элементы равны, и не равны '\0'
		else if ((rankSymbol(one.phone[index]) ==
			rankSymbol(two.phone[index])) &&
			(rankSymbol(one.phone[index]) != '\0') &&
			(rankSymbol(two.phone[index]) != '\0')) {
			// - вызвать настоящую функцию рекурсивно для сравнения
			//   следующих по порядку символов элементов
			minMaxArray(one, two, byte1char, ++index);
		}
		// иначе (если 1 <= 2 или хоть один равен '\0') ничего не делать и выйти из функции
		break;
	}
	case '5': {
		// если год_1 > год_2, то переставить элементы местами
		if (one.birthdate.year > two.birthdate.year) {
			buf = one; one = two; two = buf;
		}
		// иначе, если год_1 == год_2, то сравнивать месяцы
		else if (one.birthdate.year == two.birthdate.year) {
			// если месяц_1 > месяц_2, то переставить элементы местами
			if (one.birthdate.month > two.birthdate.month) {
				buf = one; one = two; two = buf;
			}
			// иначе, если месяц_1 == месяц_2, то сравнивать дни
			else if (one.birthdate.month == two.birthdate.month) {
				// если день_1 > день_2, то переставить элементы местами
				if (one.birthdate.day > two.birthdate.day) {
					buf = one; one = two; two = buf;
				}
				// иначе ничего не делать
			}
		}
	}
	}
}

// ФУНКЦИЯ сравнения и перестановки элементов на убывание --------------------
void maxMinArray(
	Record& one,			// элемент 1 (должен быть больше)
	Record& two,			// элемент 2 (должен быть меньше)
	char byte2char,			// номер сравниваемого поля структур
	size_t index			// индекс char-массива сравниваемого поля
) {
	Record buf;				// вспомогательная структура

	switch (byte2char) {
	case 120: {				// нажатие Ctrl+Alt+1
		// если 1 < 2, то переставить элементы местами
		if (rankSymbol(one.surname[index]) < rankSymbol(two.surname[index])) {
			buf = one; one = two; two = buf;
		}
		// иначе, если элементы равны, и не равны '\0'
		else if ((rankSymbol(one.surname[index]) ==
			rankSymbol(two.surname[index])) &&
			(rankSymbol(one.surname[index]) != '\0') &&
			(rankSymbol(two.surname[index]) != '\0')) {
			// - вызвать настоящую функцию рекурсивно для сравнения
			//   следующих по порядку символов элементов
			maxMinArray(one, two, byte2char, ++index);
		}
		// иначе (если 1 >= 2 или хоть один равен '\0') ничего не делать и выйти из функции
		break;
	}
	case 121: {				// нажатие Ctrl+Alt+2
		// если 1 < 2, то переставить элементы местами
		if (rankSymbol(one.name[index]) < rankSymbol(two.name[index])) {
			buf = one; one = two; two = buf;
		}
		// иначе, если элементы равны, и не равны '\0'
		else if ((rankSymbol(one.name[index]) ==
			rankSymbol(two.name[index])) &&
			(rankSymbol(one.name[index]) != '\0') &&
			(rankSymbol(two.name[index]) != '\0')) {
			// - вызвать настоящую функцию рекурсивно для сравнения
			//   следующих по порядку символов элементов
			maxMinArray(one, two, byte2char, ++index);
		}
		// иначе (если 1 >= 2 или хоть один равен '\0') ничего не делать и выйти из функции
		break;
	}
	case 122: {				// нажатие Ctrl+Alt+3
		// если 1 < 2, то переставить элементы местами
		if (rankSymbol(one.patronymic[index]) < rankSymbol(two.patronymic[index])) {
			buf = one; one = two; two = buf;
		}
		// иначе, если элементы равны, и не равны '\0'
		else if ((rankSymbol(one.patronymic[index]) ==
			rankSymbol(two.patronymic[index])) &&
			(rankSymbol(one.patronymic[index]) != '\0') &&
			(rankSymbol(two.patronymic[index]) != '\0')) {
			// - вызвать настоящую функцию рекурсивно для сравнения
			//   следующих по порядку символов элементов
			maxMinArray(one, two, byte2char, ++index);
		}
		// иначе (если 1 >= 2 или хоть один равен '\0') ничего не делать и выйти из функции
		break;
	}
	case 123: {				// нажатие Ctrl+Alt+4
		// если 1 < 2, то переставить элементы местами
		if (rankSymbol(one.phone[index]) < rankSymbol(two.phone[index])) {
			buf = one; one = two; two = buf;
		}
		// иначе, если элементы равны, и не равны '\0'
		else if ((rankSymbol(one.phone[index]) ==
			rankSymbol(two.phone[index])) &&
			(rankSymbol(one.phone[index]) != '\0') &&
			(rankSymbol(two.phone[index]) != '\0')) {
			// - вызвать настоящую функцию рекурсивно для сравнения
			//   следующих по порядку символов элементов
			maxMinArray(one, two, byte2char, ++index);
		}
		// иначе (если 1 >= 2 или хоть один равен '\0') ничего не делать и выйти из функции
		break;
	}
	case 124: {				// нажатие Ctrl+Alt+5
		// если год_1 < год_2, то переставить элементы местами
		if (one.birthdate.year < two.birthdate.year) {
			buf = one; one = two; two = buf;
		}
		// иначе, если год_1 == год_2, то сравнивать месяцы
		else if (one.birthdate.year == two.birthdate.year) {
			// если месяц_1 < месяц_2, то переставить элементы местами
			if (one.birthdate.month < two.birthdate.month) {
				buf = one; one = two; two = buf;
			}
			// иначе, если месяц_1 == месяц_2, то сравнивать дни
			else if (one.birthdate.month == two.birthdate.month) {
				// если день_1 < день_2, то переставить элементы местами
				if (one.birthdate.day < two.birthdate.day) {
					buf = one; one = two; two = buf;
				}
				// иначе ничего не делать
			}
		}
	}
	}
}

// ФУНКЦИЯ сортировки массива records по возрастанию заданного поля ----------
void sortFieldAscend(Record* records, char byte1char, FileAttribute phone) {
	// если в таблице нет контактов - выход из функции
	if (!records[0].surname) return;

	// сортировка массива по указанному полю
	for (size_t i = 1; i < numrecords; i++)	{
		if (!records[i].surname) break;
		for (size_t j = 1; j < numrecords; j++)	{
			if (!records[j].surname) break;
			minMaxArray(records[j - 1], records[j], byte1char, 0);
		}
	}
	// запишем измененный массив в текстовый файл
	saveRecordsToTextFile(phone);
}

// ФУНКЦИЯ сортировки массива records по убыванию заданного поля -------------
void sortFieldDeascend(Record* records, char byte2char, FileAttribute phone) {
	// если в таблице нет контактов - выход из функции
	if (!records[0].surname) return;

	// сортировка массива по указанному полю
	for (size_t i = 1; i < numrecords; i++) {
		if (!records[i].surname) break;
		for (size_t j = 1; j < numrecords; j++) {
			if (!records[j].surname) break;
			maxMinArray(records[j - 1], records[j], byte2char, 0);
		}
	}
	// запишем измененный массив в текстовый файл
	saveRecordsToTextFile(phone);
}

// ФУНКЦИЯ сравнения, что строка поля в таблице контактов
// меньше (по старшинству символов) строки в условии
bool lessStr(
	size_t numField,
	Record searchRecord,
	char* searchArg1
) {
	bool condition = false;
	// сравнение строковых полей длиной length (см. в начале программы)
	for (size_t i = 0; i < length; i++) {
		// если символ поля таблицы равен символу в условии и оба не равны '\0'
		if ((rankSymbol(searchArg1[i]) ==
			rankSymbol((&searchRecord.surname)[numField - 1][i])) &&
			(rankSymbol(searchArg1[i]) != '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) != '\0')) {
			// ничего не делать и переходить к следующей итерации
			continue;
		}
		// иначе, если символ поля таблицы меньше символа в условии и оба не равны '\0'
		else if ((rankSymbol(searchArg1[i]) >
			rankSymbol((&searchRecord.surname)[numField - 1][i])) &&
			(rankSymbol(searchArg1[i]) != '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) != '\0')) {
			condition = true;	// - указать что условие истинно,
			break;				// и выйти из цикла
		}
		// иначе, если символ поля таблицы больше символа в условии и оба не равны '\0'
		else if ((rankSymbol(searchArg1[i]) <
			rankSymbol((&searchRecord.surname)[numField - 1][i])) &&
			(rankSymbol(searchArg1[i]) != '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) != '\0')) {
			condition = false;	// - указать что условие ложно,
			break;				// и выйти из цикла
		}
		// иначе, если символ поля таблицы равен '\0',
		// а символ в условии не равен '\0'
		else if ((rankSymbol(searchArg1[i]) != '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) == '\0')) {
			condition = true;	// - указать что условие истинно,
			break;				// и выйти из цикла
		}
		// иначе, если символ поля таблицы не равен '\0',
		// а символ в условии равен '\0'
		else if ((rankSymbol(searchArg1[i]) == '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) != '\0')) {
			condition = false;	// - указать что условие ложно,
			break;				// и выйти из цикла
		}
		// иначе, если символ поля таблицы и символ указанного условия равны '\0'
		else if ((rankSymbol(searchArg1[i]) == '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) == '\0')) {
			condition = false;	// - указать что условие ложно,
			break;				// и выйти из цикла
		}
		// иначе, все прочие комбинации
		else {
			condition = false;	// - указать, что условие ложно
			break;				// и выйти из цикла
		}
	}
	// и возвратить получившийся результат
	return condition;
}

// ФУНКЦИЯ сравнения, что дата рождения в таблице контактов
// меньше указанной в условии
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

// ФУНКЦИЯ сравнения, что строка поля в таблице контактов
// больше (по старшинству символов) строки в условии
bool moreStr(
	size_t numField,
	Record searchRecord,
	char* searchArg1
) {
	bool condition = false;
	// сравнение строковых полей длиной length (см. в начале программы)
	for (size_t i = 0; i < length; i++) {
		// если символ поля таблицы равен символу в условии и оба не равны '\0'
		if ((rankSymbol(searchArg1[i]) ==
			rankSymbol((&searchRecord.surname)[numField - 1][i])) &&
			(rankSymbol(searchArg1[i]) != '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) != '\0')) {
			// ничего не делать и переходить к следующей итерации
			continue;
		}
		// иначе, если символ поля таблицы больше символа в условии и оба не равны '\0'
		else if ((rankSymbol(searchArg1[i]) <
			rankSymbol((&searchRecord.surname)[numField - 1][i])) &&
			(rankSymbol(searchArg1[i]) != '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) != '\0')) {
			condition = true;	// - указать что условие истинно,
			break;				// и выйти из цикла
		}
		// иначе, если символ поля таблицы меньше символа в условии и оба не равны '\0'
		else if ((rankSymbol(searchArg1[i]) >
			rankSymbol((&searchRecord.surname)[numField - 1][i])) &&
			(rankSymbol(searchArg1[i]) != '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) != '\0')) {
			condition = false;	// - указать что условие ложно,
			break;				// и выйти из цикла
		}
		// иначе, если символ поля таблицы не равен '\0',
		// а символ в условии равен '\0'
		else if ((rankSymbol(searchArg1[i]) == '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) != '\0')) {
			condition = true;	// - указать что условие истинно,
			break;				// и выйти из цикла
		}
		// иначе, если символ поля таблицы равен '\0',
		// а символ в условии не равен '\0'
		else if ((rankSymbol(searchArg1[i]) != '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) == '\0')) {
			condition = false;	// - указать что условие ложно,
			break;				// и выйти из цикла
		}
		// иначе, если символ поля таблицы и символ указанного условия равны '\0'
		else if ((rankSymbol(searchArg1[i]) == '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) == '\0')) {
			condition = false;	// - указать что условие ложно,
			break;				// и выйти из цикла
		}
		// иначе, все прочие комбинации
		else {
			condition = false;	// - указать, что условие ложно
			break;				// и выйти из цикла
		}
	}
	// и возвратить получившийся результат
	return condition;
}

// ФУНКЦИЯ сравнения что дата рождения в таблице контактов
// больше указанной в условии
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

// ФУНКЦИЯ сравнения на неравенство строковых полей записей
bool notEqualStr(
	size_t numField,
	Record searchRecord,
	char* searchArg1
) {
	// сравнение строковых полей длиной length (см. в начале программы)
	for (size_t i = 0; i < length; i++) {
		// если символы полей равны, и не равны '\0'
		if ((rankSymbol(searchArg1[i]) ==
			rankSymbol((&searchRecord.surname)[numField - 1][i])) &&
			(rankSymbol(searchArg1[i]) != '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) != '\0')) {
			// - ничего не делать, переходить к следующей итерации
			continue;
		}
		// иначе, если символы полей равны, и равны '\0'
		else if ((rankSymbol(searchArg1[i]) ==
			rankSymbol((&searchRecord.surname)[numField - 1][i])) &&
			(rankSymbol(searchArg1[i]) == '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) == '\0')) {
			// - возвратить false
			return false;
		}
		// иначе (если символы полей не равны) - возвратить true
		else return true;
	}
	return false;
}

// ФУНКЦИЯ сравнения на неравенство числовых полей даты рождения
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

// ФУНКЦИЯ сравнения на равенство строковых полей записей
bool equallyStr(
	size_t numField,
	Record searchRecord,
	char* searchArg1
) {
	// сравнение строковых полей длиной length (см. в начале программы)
	for (size_t i = 0; i < length; i++) {
		// если символы полей равны, и не равны '\0'
		if ((rankSymbol(searchArg1[i]) ==
			rankSymbol((&searchRecord.surname)[numField - 1][i])) &&
			(rankSymbol(searchArg1[i]) != '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) != '\0')) {
			// - ничего не делать, переходить к следующей итерации
			continue;
		}
		// иначе, если символы полей равны, и равны '\0'
		else if ((rankSymbol(searchArg1[i]) ==
			rankSymbol((&searchRecord.surname)[numField - 1][i])) &&
			(rankSymbol(searchArg1[i]) == '\0') &&
			(rankSymbol((&searchRecord.surname)[numField - 1][i]) == '\0')) {
			// - возвратить true
			return true;
		}
		// иначе (если символы полей не равны) - возвратить false
		else return false;
	}
	return false;
}

// ФУНКЦИЯ сравнения на равенство числовых полей даты рождения
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

// ФУНКЦИЯ поиска контактов
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

	// скопируем содержание массива records в массив searchRecords
	for (size_t i = 0; i < numrecords; i++)	{
		if (!records[i].surname) break;
		searchRecords[i] = records[i];
	}

	// цикл работы с поиском записей
	while (true) {
		system("cls");
		printf_s(" Поиск контакта\n");

		// вывод на экран заголовка таблицы контактов
		printf_s("  №  %-14s %-9s %-16s %-11s %-s\n",
			header[0],
			header[1],
			header[2],
			header[3],
			header[4]
		);
		printf_s("       [1]          [2]         [3]              [4]         [5]\n");

		// вывод массива searchRecords на экран
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
 [6]-выход из режима поиска\n\
 Укажите №столбца для ввода требуемого значения контакта: ");
		scanf_s("%d", &numField);

		if ((numField < 1) || (6 < numField)) numField = 6;
		if (numField == 6) return;
		if (numField < 5) {
			printf_s("\n\
 Введите условие поиска по указанному полю. Формат условия поиска:\n\
 <код операции> <пробел> <значение>\n\
     (код операции: =(равно), !(не равно), <(меньше), >(больше))\n");
			printf_s("%s: ", header[(numField - 1)]);
			scanf_s("%s %s", operationS, lenArg, searchArg1, lenArg);
			operation = operationS[0];
		}
		else if (numField == 5) {
			searchYear1 = 0;
			searchMonth1 = 0;
			searchDay1 = 0;
			printf_s("\n\
 Введите условие поиска по указанному полю. Формат условия поиска:\n\
 <код операции> <Enter>\n\
     (код операции: =(равно), !(не равно), <(меньше), >(больше))\n\
 <год> <Enter>\n\
 <месяц> <Enter>\n\
 <день> <Enter>\n\
 В значениях года, месяца или дня укажите 0, если их сравнивать не нужно\n\
");
			printf_s(" Укажите операцию: ");
			scanf_s("%s", operationS, lenArg);
			operation = operationS[0];

			printf_s(" Укажите год: ");
			scanf_s("%4d", &searchYear1);

			printf_s(" Укажите месяц: ");
			scanf_s("%2d", &searchMonth1);

			printf_s(" Укажите день: ");
			scanf_s("%2d", &searchDay1);
		}

		Record* searchRecordsBuf = new Record[numrecords];
		bool copyRecord = false;

		// запишем в массив searchRecordsBuf
		// записи из массива searchRecords
		// удовлетворяющие заданным условиям
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

		// копируем массив searchRecordsBuf
		// в массив searchRecords
		// от начала до конца
		for (size_t i = 0; i < numrecords; i++)	{
			searchRecords[i] = searchRecordsBuf[i];
		}

		delete[] searchRecordsBuf;
	}
	delete[] searchRecords;
}

// ГЛАВНАЯ ФУНКЦИЯ -----------------------------------------------------------
int main() {
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("title Телефонный справочник");

	char byte1char = '\0';
	char byte2char = '\0';
	enum keys { ENTER = 13, ESC = 27 };
	enum key0 { F1 = 59, F2, F3, F4, F5, F6, F7, F8, F9, F10,
		CTRL_ALT_1 = 120, CTRL_ALT_2, CTRL_ALT_3, CTRL_ALT_4, CTRL_ALT_5 };

	FileAttribute phone;
	phone.name = "data.txt";

	while (true) {
		titleScreen();

		// откроем файл или проверим наличие файла телефонной базы
		if (fopen_s(phone.ptrData, phone.name, "r")) {
			printf_s(" В телефонном справочнике нет контактов\n");
		}
		else {
			// вывод на экран заголовка таблицы контактов
			printf_s("  №  %-14s %-9s %-16s %-11s %-s\n",
				header[0],
				header[1],
				header[2],
				header[3],
				header[4]
			);
			printf_s("       [1]          [2]         [3]              [4]         [5]\n");

			// считаем файл построчно и занесем данные в структуру currentrecord и в массив records
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

					// выведем на экран
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

		// обработка нажатий клавиш в начальном меню
		byte1char = _getch();
		if (_kbhit()) byte2char = _getch();
		// Esc - выход из программы
		if (byte1char == ESC) break;
		// 1...5 - сортировать контакты по возрастанию
		else if (('1' <= byte1char) && (byte1char <= '5'))
			sortFieldAscend(records, byte1char, phone);
		// Ctrl + Alt + (1...5) - сортировать контакты по убыванию
		else if ((byte1char == 0) &&
			(CTRL_ALT_1 <= byte2char) && (byte2char <= CTRL_ALT_5))
			sortFieldDeascend(records, byte2char, phone);
		// F1-открыть справку
		else if ((byte1char == 0) && (byte2char == F1)) openHelp();
		// F2-добавить контакт
		else if ((byte1char == 0) && (byte2char == F2))	addRecord(phone);
		// F3-изменить контакт
		else if ((byte1char == 0) && (byte2char == F3))	insRecord(phone);
		// F4-удалить контакт
		else if ((byte1char == 0) && (byte2char == F4))	delRecord(phone);
		// F5-искать контакт(ы)
		else if ((byte1char == 0) && (byte2char == F5))	searchRecord(records);
		// F10-удалить все контакты
		else if ((byte1char == 0) && (byte2char == F10)) delAllRecord(phone);
	}
	delete[] records;
	return 0;
}