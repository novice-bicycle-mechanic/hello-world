//задание из файла "homework 20.pdf"

//                    Домашнее задание № 20
// Тема: Структуры
//                    Встреча 39. Задание 2
//     Описать структуру Man (Фамилия, Имя, Возраст, Дата рождения).
// Создать массив, предусмотреть:
// • Вывод информации с сортировкой по фамилии или имени;
// • Вывод списка именинников месяца с указанием даты рождения;
// • Изменение размеров массива при добавлении и удалении записей;
// • Поиск по фамилии и имени;
// • Редактирование записи.
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

// опишем структуру Man
struct Man {
	char* surname = new char[sizebuf::BUF]{ '\0' };   // фамилия
	char* name = new char[sizebuf::BUF]{ '\0' };      // имя
	size_t age = 0;        // возраст
	struct Birthdate {     // день рождения:
		size_t day = 0;    // - день
		size_t month = 0;  // - месяц
		size_t year = 0;   // - год
	} birthdate;
};


// ФУНКЦИЯ вывода заголовка экрана с текстом меню
void titleScreen() {
	system("cls");
	printf_s("\
 [Esc]-выход из программы\n\
 [F1]-добавить запись, [F2]-удалить запись, [F4]-изменить запись\n\
 Сортировать: [F5]-по фамилии, [F6]-по имени\n\
 Найти: [F7]-по фамилии, [F8]-по имени, [F9]-именинников месяца\n\
 ---------------------------------------------------------------\n\
");
}


// ФУНКЦИЯ заполнения структуры Man
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


// ФУНКЦИЯ добавления записи в массив Man
void addRecord(Man* man, Man**& list, size_t& length) {

	// создадим новый массив buffer типа Man** увеличенный
	// на 1 запись по сравнению с прежним массивом listMan
	Man** buffer = new Man * [length + 1]{ nullptr };

	// скопируем прежний массив listMan в новый массив buffer
	if (list) {
		for (size_t i = 0; i < length; i++) {
			buffer[i] = list[i];
		}
	}

	// удалим прежний массив listMan
	if (list) {
		delete[] list;
		list = nullptr;
	}

	// присвоим прежнему "указателю на массив"
	// listMan новый массив buffer
	list = buffer;
	buffer = nullptr;

	// заполним последнюю запись обновленного массива listMan
	list[length] = man;

	// увеличим значение длины массива listMan до фактической
	length++;
}


// ФУНКЦИЯ удаления записи из массива listMan
// возвращает true при успехе или false, если номер
// удаляемой записи не входит в разрешенный диапазон
bool delRecord(size_t numDelRecord, Man**& listMan, size_t& lengthMan) {

	// уменьшение номера удаляемой записи numDelRecord на 1
	// для приведения человеческого номера к машинному
	numDelRecord--;

	// проверка номера удаляемой записи numDelRecord
	// на вхождение в разрешенный диапазон,
	// если не входит - возврат из функции false
	if (!((0 <= numDelRecord) && (numDelRecord < lengthMan))) {
		return false;
	}
	// создадим новый массив buffer типа Man** уменьшенный
	// на 1 запись по сравнению с прежним массивом listMan
	Man** buffer = new Man * [lengthMan - 1]{ nullptr };

	// скопируем прежний массив listMan в новый массив buffer
	// сначала и до удаляемой записи numDelRecord
	for (size_t i = 0; i < numDelRecord; i++) {
		buffer[i] = listMan[i];
	}
	// скопируем прежний массив listMan в новый массив buffer
	// после удаляемой записи numDelRecord
	if ((numDelRecord + 1) < lengthMan) {
		for (size_t i = (numDelRecord + 1); i < lengthMan; i++) {
			buffer[i - 1] = listMan[i];
		}
	}
	// удалим прежний массив listMan
	// и назначим указателю на прежний массив listMan новый массив buffer,
	// указатель на который затем обнулим
	if (listMan) delete[] listMan;
	listMan = buffer;
	buffer = nullptr;

	// уменьшим значение длины массива lengthMan на 1
	// в соответствие с фактической длиной массива listMan
	lengthMan--;

	// возврат из функции true - успешное выполнение
	return true;
}


// ФУНКЦИЯ вывода массива типа Man** на экран
void printList(Man** list, size_t length) {
	printf_s("  №  Фамилия          Имя          Возраст   День рождения\n");

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


// ФУНКЦИЯ ввода записи в структуру
Man* inputMan() {
	Man* man = new Man;

	printf_s(" Введите через пробелы данные:\n\
 фамилию, имя, возраст, день, месяц и год рождения\n > ");

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


// ФУНКЦИЯ ввода номера записи массива listMan
size_t inputNumRecord() {
	printf_s(" Введите номер записи: ");
	size_t number = 0;
	scanf_s("%d", &number);
	return number;
}


// ФУНКЦИЯ изменения указанной записи массива listMan
void editRecord(size_t numRecord, Man** listMan, size_t& lengthMan) {
	// уменьшение номера удаляемой записи numDelRecord на 1
	// для приведения человеческого номера к машинному
	numRecord--;

	// проверка номера удаляемой записи numDelRecord
	// на вхождение в разрешенный диапазон,
	// если не входит - возврат из функции false
	if (!((0 <= numRecord) && (numRecord < lengthMan))) {
		printf_s(" Номер записи не входит в разрешенный диапазон\n");
		system("pause");
		return;
	}

	FieldsListMan fieldListMan = FieldsListMan::NONE;
	printf_s(" Укажите номер редактируемого поля:\n\
 [1]-Фамилия, [2]-Имя, [3]-Возраст, [4]-дата рождения > ");
	scanf_s("%d", &fieldListMan);
	switch (fieldListMan) {
	case FieldsListMan::SURNAME: {
		printf_s(" Фамилию \"%s\" заменить на: ", listMan[numRecord]->surname);
		char* newSurname = new char[sizebuf::BUF]{ '\0' };
		scanf_s("%s", newSurname, sizebuf::BUF);
		listMan[numRecord]->surname = newSurname;
		break;
	}
	case FieldsListMan::NAME: {
		printf_s(" Имя \"%s\" заменить на: ", listMan[numRecord]->name);
		char* newName = new char[sizebuf::BUF]{ '\0' };
		scanf_s("%s", newName, sizebuf::BUF);
		listMan[numRecord]->name = newName;
		break;
	}
	case FieldsListMan::AGE: {
		printf_s(" Возраст \"%d\" заменить на: ", listMan[numRecord]->age);
		scanf_s("%d", &listMan[numRecord]->age);
		break;
	}
	case FieldsListMan::BIRTHDATE: {
		printf_s(" Дату рождения \"%02d.%02d.%04d\" заменить на\n (через пробелы): день месяц год > ",
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


// ФУНКЦИЯ оценки символа для целей сортировки
// латинские: A-Z, a-z - 1-26 ; русские: А-Я, а-я - 101-133
size_t  rankSymbol(
	unsigned char symbol							// оцениваемый символ
) {
	if ((64 < symbol) && (symbol < 91)) {			// прописные латинские символы A-Z	
		return (symbol - (unsigned char)64);
	}
	else if ((96 < symbol) && (symbol < 123)) {		// строчные латинские символы a-z
		return (symbol - (unsigned char)96);
	}
	else if ((191 < symbol) && (symbol < 198)) {	// прописные русские символы А-Е
		return (symbol - (unsigned char)91);
	}
	else if (symbol == 168) {						// прописной русский символ Ё
		return (symbol - (unsigned char)61);
	}
	else if ((197 < symbol) && (symbol < 224)) {	// прописные русские символы Ж-Я
		return (symbol - (unsigned char)90);
	}
	else if ((223 < symbol) && (symbol < 230)) {	// строчные русские символы а-е
		return (symbol - (unsigned char)123);
	}
	else if (symbol == 184) {						// строчный русский символ ё
		return (symbol - (unsigned char)77);
	}
	else if ((229 < symbol) && (symbol < 256)) {	// строчные русские символы ж-я
		return (symbol - (unsigned char)122);
	}
	else {
		return 0;									// прочие значения
	}
}


// ФУНКЦИЯ сравнения и перестановки элементов на минимум
void minArray(
	Man*& oneRecord,				// запись 1 (ее строка должна быть меньше)
	Man*& twoRecord,				// запись 2 (ее строка должна быть больше)
	char* one,						// строка записи 1 (должна быть меньше)
	char* two,						// строка записи 2 (должна быть больше)
	size_t index					// индекс char-массива элемента
) {
	Man* bufRecord = nullptr;		// вспомогательный указатель на элемент
	if (rankSymbol(one[index]) > rankSymbol(two[index])) {	// если 1 > 2
		bufRecord = oneRecord;											// переставить элементы местами
		oneRecord = twoRecord;
		twoRecord = bufRecord;
	}
	// иначе, если элементы равны, и не равны '\0'
	else if ((rankSymbol(one[index]) == rankSymbol(two[index])) &&
		     (rankSymbol(one[index]) != '\0') &&
		     (rankSymbol(two[index]) != '\0')) {
		// - вызвать настоящую функцию рекурсивно для сравнения
		//   следующих по порядку символов элементов
		minArray(oneRecord, twoRecord, one, two, ++index);
	}
	// если 1 < 2 или хоть один равен '\0' - ничего не делать и выйти из функции
}


// ФУНКЦИЯ сортировки массивов с фамилиями/именами
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


// ФУНКЦИЯ поиска записи по фамилии
void searchSurname(
	Man** listMan,              // исходный массив
	size_t lengthMan            // длина исходного массива
) {
	// задаем фамилию, записи с которой необходимо найти
	char* surname = new char[sizebuf::BUF]{ '\0' };
	printf_s(" Введите фамилию поиска: ");
	scanf_s("%s", surname, sizebuf::BUF);
	_strlwr_s(surname, sizebuf::BUF);  // перевод строки в нижний регистр

	// создаем буферную строку поиска
	char* bufferSurname = new char[sizebuf::BUF]{ '\0' };

	// создаем массив записей с найденными фамилиями
	size_t lengthSurname = 0;
	Man** listSurname = new Man * [lengthMan] {nullptr};

	// проверка вхождения заданной строки фамилии
	// в буферную строку фамилии скопированной
	// из записи массива listMan
	for (size_t i = 0; i < lengthMan; i++) {
		// копируем поле surname массива listMan в буферную строку фамилии
		for (size_t j = 0; j < sizebuf::BUF; j++) {
			bufferSurname[j] = listMan[i]->surname[j];
		}
		_strlwr_s(bufferSurname, sizebuf::BUF);  // перевод строки в нижний регистр
		// ищем вхождение заданной строки в буферной строке имени
		if (strstr(bufferSurname, surname)) {
			// если нашли - добавляем запись из массива listMan в массив listSurname
			listSurname[lengthSurname] = new Man;
			// копируем поле surname 
			for (size_t j = 0; j < sizebuf::BUF; j++) {
				listSurname[lengthSurname]->surname[j] = listMan[i]->surname[j];
			}
			// копируем поле name
			for (size_t j = 0; j < sizebuf::BUF; j++) {
				listSurname[lengthSurname]->name[j] = listMan[i]->name[j];
			}
			// копируем поле age
			listSurname[lengthSurname]->age = listMan[i]->age;
			// копируем поле birthdate.day
			listSurname[lengthSurname]->birthdate.day = listMan[i]->birthdate.day;
			// копируем поле birthdate.month
			listSurname[lengthSurname]->birthdate.month = listMan[i]->birthdate.month;
			// копируем поле birthdate.year
			listSurname[lengthSurname]->birthdate.year = listMan[i]->birthdate.year;
			// увеличиваем индекс массива listSurname
			lengthSurname++;
		}
	}

	char byte1key = '\0';

	while (true) {
		system("cls");
		printf_s("[Esc]-выход из поиска по фамилии\n\
---------------------------------------------------------------\n\
");

		printf_s("  №  Фамилия          Имя          Возраст   День рождения\n");

		// вывод массива listSurname на экран
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
		// если нажато [Esc] - выход из поиска
		if (byte1key == KeysC::ESC) break;
	}

	// удаляем локальные динамические переменные
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


// ФУНКЦИЯ поиска записи по имени
void searchName(
	Man** listMan,              // исходный массив
	size_t lengthMan            // длина исходного массива
) {
	// задаем имя, записи с которым необходимо найти
	char* name = new char[sizebuf::BUF]{ '\0' };
	printf_s(" Введите имя поиска: ");
	scanf_s("%s", name, sizebuf::BUF);
	_strlwr_s(name, sizebuf::BUF);  // перевод строки в нижний регистр

	// создаем буферную строку поиска
	char* bufferName = new char[sizebuf::BUF]{ '\0' };

	// создаем массив записей с найденными именами
	size_t lengthName = 0;
	Man** listName = new Man * [lengthMan] {nullptr};

	// проверка вхождения заданной строки имени
	// в буферную строку имени скопированной
	// из записи массива listMan
	for (size_t i = 0; i < lengthMan; i++) {
		// копируем поле name массива listMan в буферную строку имени
		for (size_t j = 0; j < sizebuf::BUF; j++) {
			bufferName[j] = listMan[i]->name[j];
		}
		_strlwr_s(bufferName, sizebuf::BUF);  // перевод строки в нижний регистр
		// ищем вхождение заданной строки в буферной строке имени
		if (strstr(bufferName, name)) {
			// если нашли - добавляем запись из массива listMan в массив listName
			listName[lengthName] = new Man;
			// копируем поле surname 
			for (size_t j = 0; j < sizebuf::BUF; j++) {
				listName[lengthName]->surname[j] = listMan[i]->surname[j];
			}
			// копируем поле name
			for (size_t j = 0; j < sizebuf::BUF; j++) {
				listName[lengthName]->name[j] = listMan[i]->name[j];
			}
			// копируем поле age
			listName[lengthName]->age = listMan[i]->age;
			// копируем поле birthdate.day
			listName[lengthName]->birthdate.day = listMan[i]->birthdate.day;
			// копируем поле birthdate.month
			listName[lengthName]->birthdate.month = listMan[i]->birthdate.month;
			// копируем поле birthdate.year
			listName[lengthName]->birthdate.year = listMan[i]->birthdate.year;
			// увеличиваем индекс массива listSurname
			lengthName++;
		}
	}

	char byte1key = '\0';

	while (true) {
		system("cls");
		printf_s("[Esc]-выход из поиска по имени\n\
---------------------------------------------------------------\n\
");

		printf_s("  №  Фамилия          Имя          Возраст   День рождения\n");

		// вывод массива listSurname на экран
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
		// если нажато [Esc] - выход из поиска
		if (byte1key == KeysC::ESC) break;
	}

	// удаляем локальные динамические переменные
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


// ФУНКЦИЯ поиска записи с именинником месяца
void searchBirthdayManMonth(
	Man** listMan,              // исходный массив
	size_t lengthMan            // длина исходного массива
) {
	// задаем месяц, записи с именинником которого необходимо найти
	size_t month = 0;
	printf_s(" Введите месяц поиска: ");
	scanf_s("%d", &month);

	// создаем массив записей с найденными именами
	size_t lengthBirthday = 0;
	Man** listBirthday = new Man * [lengthMan] {nullptr};

	// проверка равенства значения заданного месяца
	// и месяца даты рождения в записи массива listMan
	for (size_t i = 0; i < lengthMan; i++) {
		// ищем равенство месяцев в записи массива listMan
		if (listMan[i]->birthdate.month == month) {
			// если нашли - добавляем запись в массив listBirthday
			listBirthday[lengthBirthday] = new Man;
			// копируем поле surname 
			for (size_t j = 0; j < sizebuf::BUF; j++) {
				listBirthday[lengthBirthday]->surname[j] = listMan[i]->surname[j];
			}
			// копируем поле name
			for (size_t j = 0; j < sizebuf::BUF; j++) {
				listBirthday[lengthBirthday]->name[j] = listMan[i]->name[j];
			}
			// копируем поле age
			listBirthday[lengthBirthday]->age = listMan[i]->age;
			// копируем поле birthdate.day
			listBirthday[lengthBirthday]->birthdate.day = listMan[i]->birthdate.day;
			// копируем поле birthdate.month
			listBirthday[lengthBirthday]->birthdate.month = listMan[i]->birthdate.month;
			// копируем поле birthdate.year
			listBirthday[lengthBirthday]->birthdate.year = listMan[i]->birthdate.year;
			// увеличиваем индекс массива listSurname
			lengthBirthday++;
		}
	}

	char byte1key = '\0';

	while (true) {
		system("cls");
		printf_s("[Esc]-выход из поиска именинника\n\
---------------------------------------------------------------\n\
");

		printf_s("  №  Фамилия          Имя          Возраст   День рождения\n");

		// вывод массива listBirthday на экран
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
		// если нажато [Esc] - выход из поиска
		if (byte1key == KeysC::ESC) break;
	}

	// удаляем локальные динамические переменные
	if (listBirthday) {
		for (size_t i = 0; i < lengthMan; i++) {
			if (listBirthday[i]) delete[] listBirthday[i];
			listBirthday[i] = nullptr;
		}
		delete[] listBirthday;
		listBirthday = nullptr;
	}
}


// ГЛАВНАЯ ФУНКЦИЯ
int main() {
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Man** listMan = nullptr;      // указатель на массив "Список man"
	size_t lengthMan = 0;         // длина массива "Список man"

	// автоматическое заполнение таблицы данными
	addRecord(setMan((char*)"Иванов", (char*)"Сергей", 35, 3, 7, 1985), listMan, lengthMan);
	addRecord(setMan((char*)"Петров", (char*)"Андрей", 53, 8, 12, 1967), listMan, lengthMan);
	addRecord(setMan((char*)"Андреев", (char*)"Иван", 63, 2, 3, 1957), listMan, lengthMan);
	addRecord(setMan((char*)"Сергеев", (char*)"Петр", 25, 11, 1, 1995), listMan, lengthMan);

	// переменные для обработки нажатий клавиш
	char byte1key = '\0';
	char byte2key = '\0';

	// цикл работы с таблицей
	while (true) {
		titleScreen();
		printList(listMan, lengthMan);

		// обработка нажатий клавиш
		byte1key = _getch();
		if(_kbhit()) byte2key = _getch();

		// если нажато [Esc] - выход из программы
		if (byte1key == KeysC::ESC) break;
		// если нажато [F1] - добавить запись в массив listMan
		else if ((byte1key == KeysF::BYTE1KEY) && (byte2key == KeysF::F1)) {
			addRecord(inputMan(), listMan, lengthMan);
		}
		// если нажато [F2] - удалить указанную запись из массива listMan
		else if ((byte1key == KeysF::BYTE1KEY) && (byte2key == KeysF::F2)) {
			delRecord(inputNumRecord(), listMan, lengthMan);
		}
		// если нажато [F4] - изменить указанную запись в массиве listMan
		else if ((byte1key == KeysF::BYTE1KEY) && (byte2key == KeysF::F4)) {
			editRecord(inputNumRecord(), listMan, lengthMan);
		}
		// если нажато [F5] - сортировать массив listMan по возрастанию фамилий
		else if ((byte1key == KeysF::BYTE1KEY) && (byte2key == KeysF::F5)) {
			sortNames(FieldsListMan::SURNAME, listMan, lengthMan);
		}
		// если нажато [F6] - сортировать массив listMan по возрастанию имен
		else if ((byte1key == KeysF::BYTE1KEY) && (byte2key == KeysF::F6)) {
			sortNames(FieldsListMan::NAME, listMan, lengthMan);
		}
		// если нажато [F7] - искать в массиве listMan запись по фамилии
		else if ((byte1key == KeysF::BYTE1KEY) && (byte2key == KeysF::F7)) {
			searchSurname(listMan, lengthMan);
		}
		// если нажато [F8] - искать в массиве listMan запись по имени
		else if ((byte1key == KeysF::BYTE1KEY) && (byte2key == KeysF::F8)) {
			searchName(listMan, lengthMan);
		}
		// если нажато [F9] - искать в массиве listMan запись 
		// с именинником указанного месяца
		else if ((byte1key == KeysF::BYTE1KEY) && (byte2key == KeysF::F9)) {
			searchBirthdayManMonth(listMan, lengthMan);
		}
	}

	// удаляем локальные динамические переменные
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