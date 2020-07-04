// задание из файла DZ_ST_C++_01.pdf
//
// Тема: Конструкторы, деструкторы
// Встреча 2, задание
/*
Создайте приложение "Телефонная книга".
Необходимо хранить данные об абоненте
(ФИО, домашний телефон, рабочий телефон,
мобильный телефон, дополнительная информация о контакте)
внутри соответствующего класса.
Наполните класс переменными-членами, функциями-членами,
конструкторами, inline-функциями-членами, используйте
инициализаторы, реализуйте деструктор.
Обязательно необходимо выделять динамически память под ФИО.
Предоставьте пользователю возможность добавлять новых
абонентов, удалять абонентов, искать абонентов по ФИО,
показывать всех абонентов, сохранять информацию в файл
и загружать из файла.
*/
#include <iostream>
#include <clocale>
#include <Windows.h>
#include <iomanip>
#include <conio.h>
#include <fstream>
using namespace std;


// КЛАСС Абонент
class Subscriber {
private:
	char* surname    { nullptr };
	char* name       { nullptr };
	char* patronymic { nullptr };
	char* homePhone  { nullptr };
	char* workPhone  { nullptr };
	char* mobilePhone{ nullptr };
	char* additInform{ nullptr };

	std::streamsize w_surname    { 18 };
	std::streamsize w_name       { 18 };
	std::streamsize w_patromymic { 20 };
	std::streamsize w_homePhone  { 18 };
	std::streamsize w_workPhone  { 18 };
	std::streamsize w_mobilePhone{ 20 };
	std::streamsize w_additInform{ 56 };
public:
	// КОНСТРУКТОР по умолчанию
	Subscriber() {}

	// КОНСТРУКТОР с параметрами
	template <typename T>
	Subscriber(
		T surname,
		T name,
		T patronymic,
		T homePhone,
		T workPhone,
		T mobilePhone,
		T additInform
	) {
		this->surname     = toCharString(surname    );
		this->name        = toCharString(name       );
		this->patronymic  = toCharString(patronymic );
		this->homePhone   = toCharString(homePhone  );
		this->workPhone   = toCharString(workPhone  );
		this->mobilePhone = toCharString(mobilePhone);
		this->additInform = toCharString(additInform);
	}

	// КОНСТРУКТОР копирования
	Subscriber(Subscriber& object) { *this = object; }

	// ДЕКСТРУКТОР
	~Subscriber() {
		if (surname    ) delete[] surname    ;
		if (name       ) delete[] name       ;
		if (patronymic ) delete[] patronymic ;
		if (homePhone  ) delete[] homePhone  ;
		if (workPhone  ) delete[] workPhone  ;
		if (mobilePhone) delete[] mobilePhone;
		if (additInform) delete[] additInform;
	}
	
	// GETTER-ы
	char* getSurname    () { return surname    ; }
	char* getName       () { return name       ; }
	char* getPatronymic () { return patronymic ; }
	char* getHomePhone  () { return homePhone  ; }
	char* getWorkPhone  () { return workPhone  ; }
	char* getMobilePhone() { return mobilePhone; }
	char* getAdditInform() { return additInform; }

	// МЕТОД конвертации строки произвольного типа в строку типа char
	template <typename T>
	char* toCharString(T line) {
		size_t length{ 0 };
		while (line[length++] != '\0') {}
		char* charString{ nullptr };
		charString = new char[length] {'\0'};
		--length;
		if (charString) {
			for (size_t i = 0; i < length; i++) {
				charString[i] = line[i];
			}
		}
		return charString;
	}

	// МЕТОД вывода данных Абонента в три строки
	void showLine(size_t numberLine = 0) {
		switch (numberLine) {
		case 0:
		case 1: {
			cout
				<< setw(1) << ""
				<< setw(w_surname   ) << left << surname
				<< setw(w_name      ) << left << name
				<< setw(w_patromymic) << left << patronymic
				<< endl;
			if (numberLine) break;
		}
		case 2: {
			cout
				<< setw(1) << ""
				<< setw(w_homePhone  ) << left << homePhone
				<< setw(w_workPhone  ) << left << workPhone
				<< setw(w_mobilePhone) << left << mobilePhone
				<< endl;
			if (numberLine) break;
		}
		case 3: {
			cout
				<< setw(1) << ""
				<< setw(w_additInform) << left << additInform
				<< endl;
			if (numberLine) break;
		}
		}
	}

	// МЕТОД вывода заголовка в три строки
	void header(size_t numberLine = 0) {
		switch (numberLine) {
		case 0:
		case 1: {
			cout
				<< setw(1) << ""
				<< setw(w_surname   ) << left << "Фамилия"
				<< setw(w_name      ) << left << "Имя"
				<< setw(w_patromymic) << left << "Отчество"
				<< endl;
			if (numberLine) break;
		}
		case 2: {
			cout
				<< setw(1) << ""
				<< setw(w_homePhone  ) << left << "Домашний телефон"
				<< setw(w_workPhone  ) << left << "Рабочий телефон"
				<< setw(w_mobilePhone) << left << "Мобильный телефон"
				<< endl;
			if (numberLine) break;
		}
		case 3: {
			cout
				<< setw(1) << ""
				<< setw(w_additInform) << left << "Дополнительные данные"
				<< endl;
			if (numberLine) break;
		}
		}
	}

	// МЕТОД вывода данных абонента на экран - карточка
	bool showCard() {
		enum class Buttons { ESC = 27, D1 = 49, D2, D3, D4, D5, D6, D7 }; // Dn-цифра
		char button1byte{ '\0' };
		bool _saveInFile = false;
		string buffer;
		const char* fieldName[8]{
			" изменить на ",
			" 1.Фамилия: ",
			" 2.Имя: ",
			" 3.Отчество: ",
			" 4.Домашний телефон: ",
			" 5.Рабочий телефон: ",
			" 6.Мобильный телефон: ",
			" 7.Дополнительные данные: "
		};

		while (true) {
			system("cls");

			cout << " [Esc]-выход из карточки, [цифра]-редактировать поле №" << endl << endl;
			cout << "                    Карточка абонента" << endl;
			cout << fieldName[1] << surname     << endl;
			cout << fieldName[2] << name        << endl;
			cout << fieldName[3] << patronymic  << endl;
			cout << fieldName[4] << homePhone   << endl;
			cout << fieldName[5] << workPhone   << endl;
			cout << fieldName[6] << mobilePhone << endl;
			cout << fieldName[7] << additInform << endl;

			button1byte = _getch();
			if (_kbhit()) (void)_getch();
			if (('1' <= button1byte) && (button1byte <= '7')) _saveInFile = true;

			switch (button1byte) {
			case (int)Buttons::ESC: {
				return _saveInFile;
			}
			case (int)Buttons::D1: {
				cout << "-------------------------------------" << endl;
				cout << fieldName[1] << surname << fieldName[0];
				cin >> buffer;
				replaceLine(surname, toCharString(buffer));
				break;
			}
			case (int)Buttons::D2: {
				cout << "-------------------------------------" << endl;
				cout << fieldName[2] << name << fieldName[0];
				cin >> buffer;
				replaceLine(name, toCharString(buffer));
				break;
			}
			case (int)Buttons::D3: {
				cout << "-------------------------------------" << endl;
				cout << fieldName[3] << patronymic << fieldName[0];
				cin >> buffer;
				replaceLine(patronymic, toCharString(buffer));
				break;
			}
			case (int)Buttons::D4: {
				cout << "-------------------------------------" << endl;
				cout << fieldName[4] << homePhone << fieldName[0];
				cin >> buffer;
				replaceLine(homePhone, toCharString(buffer));
				break;
			}
			case (int)Buttons::D5: {
				cout << "-------------------------------------" << endl;
				cout << fieldName[5] << workPhone << fieldName[0];
				cin >> buffer;
				replaceLine(workPhone, toCharString(buffer));
				break;
			}
			case (int)Buttons::D6: {
				cout << "-------------------------------------" << endl;
				cout << fieldName[6] << mobilePhone << fieldName[0];
				cin >> buffer;
				replaceLine(mobilePhone, toCharString(buffer));
				break;
			}
			case (int)Buttons::D7: {
				cout << "-------------------------------------" << endl;
				cout << fieldName[7] << additInform << fieldName[0];
				cin >> buffer;
				replaceLine(additInform, toCharString(buffer));
				break;
			}
			}
		}
	}

	// МЕТОД вывода данных абонента в строку файла
	char* objectToLineFile() {

		size_t lengthLineFile =
			(size_t)w_surname +
			(size_t)w_name +
			(size_t)w_patromymic +
			(size_t)w_homePhone +
			(size_t)w_workPhone +
			(size_t)w_mobilePhone +
			(size_t)w_additInform +
			(size_t)7;

		char* lineFile = new char[lengthLineFile] {'\0'};
		--lengthLineFile;
		size_t currentIndex = 0;
		currentIndex = writeInLineFileFromItemObject(lineFile, lengthLineFile, currentIndex, ',', surname    );
		currentIndex = writeInLineFileFromItemObject(lineFile, lengthLineFile, currentIndex, ',', name       );
		currentIndex = writeInLineFileFromItemObject(lineFile, lengthLineFile, currentIndex, ',', patronymic );
		currentIndex = writeInLineFileFromItemObject(lineFile, lengthLineFile, currentIndex, ',', homePhone  );
		currentIndex = writeInLineFileFromItemObject(lineFile, lengthLineFile, currentIndex, ',', workPhone  );
		currentIndex = writeInLineFileFromItemObject(lineFile, lengthLineFile, currentIndex, ',', mobilePhone);
		currentIndex = writeInLineFileFromItemObject(lineFile, lengthLineFile, currentIndex, ';', additInform);

		return lineFile;
	}

	// МЕТОД записи в строку файла данных члена объекта
	size_t writeInLineFileFromItemObject(
		char* lineFile,
		size_t lengthLineFile,
		size_t currentIndexLineFile,
		char lastSymbol,
		char* additLine
	) {
		size_t index = 0;
		if (additLine) {
			while ((additLine[index] != '\0') && (currentIndexLineFile < lengthLineFile)) {
				lineFile[currentIndexLineFile] = additLine[index];
				++currentIndexLineFile;
				++index;
			}
		}
		if (currentIndexLineFile < lengthLineFile) lineFile[currentIndexLineFile] = lastSymbol;
		if ((currentIndexLineFile + 1) < lengthLineFile) ++currentIndexLineFile;

		return currentIndexLineFile;
	}

	// МЕТОД замены старой строки на новую
	void replaceLine(
		char*& oldLine,
		char* newLine
	) {
		if (oldLine) delete[] oldLine;
		oldLine = newLine;
	}

	// МЕТОД подтверждения, что первая строка включает вторую
	template <typename T>
	bool firstIncludeSecond(char* first, T _second) {
		char* second = toCharString(_second);

		bool confirmation{ false };
		size_t indexFirst{ 0 };
		size_t indexSecond{ 0 };

		while (first[indexFirst] != '\0') {
			if (first[indexFirst] == second[indexSecond]) {
				confirmation = true;
				break;
			}
			else  ++indexFirst;
		}
		if (confirmation) {
			while (second[indexSecond] != '\0') {
				if (first[indexFirst] == second[indexSecond]) {
					++indexFirst;
					++indexSecond;
				}
				else return false;
			}
		}
		return confirmation;
	}

}subscriber;
// КОНЕЦ КЛАССА Абонент



// КЛАСС Телефонная книга
class PhoneBook {
private:
	size_t lengthPhoneBook{ 0 };
	Subscriber** arrayPhoneBook{ nullptr };
	const char* nameFilePhoneBook;
	std::streamsize w_numberScriber{ 3 };
public:
	// КОНСТРУКТОР с параметром
	PhoneBook(const char* nameFile) {
//		cout << "Конструктор PhoneBook с параметром" << endl;
		nameFilePhoneBook = nameFile;
	}

	// ДЕКОНСТРУКТОР
	~PhoneBook() {
//		cout << "Деструктор ~PhoneBook" << endl;
		if (arrayPhoneBook) delete[] arrayPhoneBook;
	}

	// МЕТОД вывода Телефонной книги на экран
	void show() {

		enum class KeysC { ESC = 27 };
		enum class KeysF { BYTE1KEY = 0, F1 = 59, F2, F3, F4, F5, F6, F7, F8, F9 };
		char byte1key{ '\0' };
		char byte2key{ '\0' };
		size_t numberSubscriber{ 0 };
		bool _saveInFile = false;

		while (true) {

			system("cls");

			cout << " [Esc]-выход из программы, [F1]-карточка абонента" << endl;
			cout << " [F4]-добавить абонента, [F5]-удалить абонента, [F8]-найти абонента" << endl;
			cout << endl;
			cout << "                     Телефонная книга" << endl;
			cout << endl;

			this->uploadFromFile();

			if (!arrayPhoneBook || !arrayPhoneBook[0]) {
				cout << " Телефонная книга не содержит абонентов" << endl;
			}
			else {
				header(subscriber);
				cout << endl;
				if (arrayPhoneBook) {
					for (size_t i = 0; i < lengthPhoneBook; i++) {
						if (arrayPhoneBook[i]) showLine(i);
					}
				}
			}

			byte1key = _getch();
			if (_kbhit()) byte2key = _getch();

			// нажато [Esc] - выход из программы
			if (byte1key == (int)KeysC::ESC) break;
			// нажато [F1] - вывод на экран карточки абонента
			else if ((byte1key == (int)KeysF::BYTE1KEY) && (byte2key == (int)KeysF::F1)) {
				if (arrayPhoneBook) {
					cout << " Укажите номер абонента, чью карточку вывести на экран: ";
					cin >> numberSubscriber;
					if ((0 < numberSubscriber) && (numberSubscriber <= lengthPhoneBook) &&
						(arrayPhoneBook[indexFromNumber(numberSubscriber)])) {
						_saveInFile = arrayPhoneBook[indexFromNumber(numberSubscriber)]->showCard();
						if (_saveInFile) this->saveInFile();
					}
					else {
						cout
							<< " Абонент №"
							<< numberSubscriber
							<< " в Телефонной книге отсутствует"
							<< endl;
						Sleep(2000);
					}
				}
			}
			// нажато [F4] - добавить абонента
			else if ((byte1key == (int)KeysF::BYTE1KEY) && (byte2key == (int)KeysF::F4)) {
				this->addSubscriber("", "", "", "", "", "", "");
				this->saveInFile();
			}
			// нажато [F5] - удалить абонента
			else if ((byte1key == (int)KeysF::BYTE1KEY) && (byte2key == (int)KeysF::F5)) {
				if (arrayPhoneBook) {
					cout << " Укажите номер удаляемого абонента: ";
					cin >> numberSubscriber;
					this->delSubscriber(numberSubscriber);
				}
				this->saveInFile();
			}
			// нажато [F8] - найти абонента
			else if ((byte1key == (int)KeysF::BYTE1KEY) && (byte2key == (int)KeysF::F8)) {
				if (arrayPhoneBook) {
					string word;
					cout << " Введите для поиска слово входящее в ФИО: ";
					cin >> word;
					searchSubscriber(word);
				}
			}
		}
	}

	// МЕТОД поиска абонента по слову, входящему в ФИО
	template <typename T>
	void searchSubscriber(T word) {
		PhoneBook searchPhoneBook("search.txt");
		if (arrayPhoneBook) {
			for (size_t i = 0; i < this->lengthPhoneBook; i++) {
				if (arrayPhoneBook[i]) {
					if (arrayPhoneBook[i]->firstIncludeSecond(arrayPhoneBook[i]->getSurname   (), word) ||
						arrayPhoneBook[i]->firstIncludeSecond(arrayPhoneBook[i]->getName      (), word) ||
						arrayPhoneBook[i]->firstIncludeSecond(arrayPhoneBook[i]->getPatronymic(), word)
						) {
						searchPhoneBook.addSubscriber(
							arrayPhoneBook[i]->getSurname    (),
							arrayPhoneBook[i]->getName       (),
							arrayPhoneBook[i]->getPatronymic (),
							arrayPhoneBook[i]->getHomePhone  (),
							arrayPhoneBook[i]->getWorkPhone  (),
							arrayPhoneBook[i]->getMobilePhone(),
							arrayPhoneBook[i]->getAdditInform(),
							false
						);
					}
				}
			}
			searchPhoneBook.show();
		}
	}

	// МЕТОД вывода на экран заголовка таблицы
	template <typename T>
	void header(T& object) {

		cout << setw(w_numberScriber) << right << " № ";
		object.header(1);

		cout << setw(w_numberScriber) << right << "";
		object.header(2);

		cout << setw(w_numberScriber) << right << "";
		object.header(3);
	}

	// МЕТОД вывода на экран элемента массива как строки таблицы
	void showLine(size_t index) {

		cout << setw(w_numberScriber) << right << numberFromIndex(index);
		arrayPhoneBook[index]->showLine(1);

		cout << setw(w_numberScriber) << right << "";
		arrayPhoneBook[index]->showLine(2);

		cout << setw(w_numberScriber) << right << "";
		arrayPhoneBook[index]->showLine(3);
	}

	// МЕТОД определения индекса массива из номера в таблице
	size_t indexFromNumber(size_t number) {
		if (number) return --number;
		else return 0;
	}

	// МЕТОД определения номера в таблице из индекса массива
	size_t numberFromIndex(size_t index) {
		return ++index;
	}

	// МЕТОД добавления абонента в массив - с заданными параметрами
	template <typename T>
	void addSubscriber(
		T _surname,
		T _name,
		T _patronymic,
		T _homePhone,
		T _workPhone,
		T _mobilePhone,
		T _additInform,
		bool _saveInFile = true

	) {
		Subscriber** newArrayPhoneBook{ nullptr };
		newArrayPhoneBook = new Subscriber * [lengthPhoneBook + 1]{ nullptr };
		if (arrayPhoneBook) {
			for (size_t i = 0; i < lengthPhoneBook; i++) {
				newArrayPhoneBook[i] = arrayPhoneBook[i];
			}
		}
		newArrayPhoneBook[lengthPhoneBook] = new Subscriber{
		_surname,
		_name,
		_patronymic,
		_homePhone,
		_workPhone,
		_mobilePhone,
		_additInform
		};

		if (arrayPhoneBook) delete[] arrayPhoneBook;
		arrayPhoneBook = newArrayPhoneBook;
		newArrayPhoneBook = nullptr;
		++lengthPhoneBook;

		if (!(
			_surname[0] &&
			_name[0] &&
			_patronymic[0] &&
			_homePhone[0] &&
			_workPhone[0] &&
			_mobilePhone[0] &&
			_additInform[0]
			)) {
			if (lengthPhoneBook) arrayPhoneBook[lengthPhoneBook - 1]->showCard();
		}

		if (_saveInFile) this->saveInFile();
	}

	// МЕТОД удаления абонента
	void delSubscriber(size_t numberSubscriber) {

		if (!((0 < numberSubscriber) && (numberSubscriber <= lengthPhoneBook))) {
			cout << " Абонент с указанным номером отсутствует" << endl;
			Sleep(2000);
			return;
		}
		else {
			size_t indexSubscriber = indexFromNumber(numberSubscriber);
			Subscriber** newArrayPhoneBook{ nullptr };
			size_t newLengthPhoneBook{ 0 };

			if (lengthPhoneBook > 1) {
				newLengthPhoneBook = lengthPhoneBook - 1;
				newArrayPhoneBook = new Subscriber * [newLengthPhoneBook]{ nullptr };
				if (indexSubscriber && (indexSubscriber <= newLengthPhoneBook)) {
					for (size_t i = 0; i < indexSubscriber; i++) {
						newArrayPhoneBook[i] = arrayPhoneBook[i];
					}
				}

				for (
					size_t i = indexSubscriber, j = indexSubscriber + 1;
					(i < newLengthPhoneBook) && (j < lengthPhoneBook);
					i++, j++
					) {
					newArrayPhoneBook[i] = arrayPhoneBook[j];
				}
			}

			if (arrayPhoneBook) delete[] arrayPhoneBook;
			arrayPhoneBook = newArrayPhoneBook;
			newArrayPhoneBook = nullptr;
			lengthPhoneBook = newLengthPhoneBook;

			cout << " Абонент №" << numberSubscriber << " удален" << endl;
			Sleep(2000);
			this->saveInFile();
			return;
		}
	}

	// МЕТОД записи Телефонной книги в текстовый файл
	void saveInFile() {
		char* lineFile{ nullptr };
		ofstream fout;
		if (nameFilePhoneBook) fout.open(nameFilePhoneBook);
		if (arrayPhoneBook) {
			for (size_t i = 0; i < lengthPhoneBook; i++) {
				if (arrayPhoneBook[i]) {
					lineFile = arrayPhoneBook[i]->objectToLineFile();
					fout << lineFile << endl;
					if (lineFile) delete[] lineFile;
					lineFile = nullptr;
				}
			}
		}
		fout.close();
	}

	// МЕТОД загрузки Телефонной книги из текстового файла
	void uploadFromFile() {
		ifstream fin;
		if (nameFilePhoneBook) fin.open(nameFilePhoneBook);

		if (!fin.is_open()) {
			cout << " Файл Телефонной книги отсутствует" << endl;
		}
		else {
			if (arrayPhoneBook) delete[] arrayPhoneBook;
			arrayPhoneBook = nullptr;
			lengthPhoneBook = 0;

			const size_t lengthBuffer{ 256 };
			char buffer[lengthBuffer]{ '\0' };
			size_t indexBuffer{ 0 };

			const size_t lengthField{ 32 };
			char _surname    [lengthField]{ '\0' };
			char _name       [lengthField]{ '\0' };
			char _patronymic [lengthField]{ '\0' };
			char _homePhone  [lengthField]{ '\0' };
			char _workPhone  [lengthField]{ '\0' };
			char _mobilePhone[lengthField]{ '\0' };
			char _additInform[lengthField]{ '\0' };
			size_t indexField{ 0 };

			while (true) {
				for (size_t i = 0; i < lengthBuffer; i++) {
					buffer[i] = '\0';
				}
				fin.getline(buffer, lengthBuffer, ';');
				if (fin.eof()) break;

				indexBuffer = 0;
				if ((int)buffer[indexBuffer] == 10) ++indexBuffer;

				indexField = 0;
				while (buffer[indexBuffer] != ',') {
					_surname[indexField] = buffer[indexBuffer];
					++indexField;
					++indexBuffer;
				}
				_surname[indexField] = '\0';

				++indexBuffer;
				indexField = 0;
				while (buffer[indexBuffer] != ',') {
					_name[indexField] = buffer[indexBuffer];
					++indexField;
					++indexBuffer;
				}
				_name[indexField] = '\0';

				++indexBuffer;
				indexField = 0;
				while (buffer[indexBuffer] != ',') {
					_patronymic[indexField] = buffer[indexBuffer];
					++indexField;
					++indexBuffer;
				}
				_patronymic[indexField] = '\0';

				++indexBuffer;
				indexField = 0;
				while (buffer[indexBuffer] != ',') {
					_homePhone[indexField] = buffer[indexBuffer];
					++indexField;
					++indexBuffer;
				}
				_homePhone[indexField] = '\0';

				++indexBuffer;
				indexField = 0;
				while (buffer[indexBuffer] != ',') {
					_workPhone[indexField] = buffer[indexBuffer];
					++indexField;
					++indexBuffer;
				}
				_workPhone[indexField] = '\0';

				++indexBuffer;
				indexField = 0;
				while (buffer[indexBuffer] != ',') {
					_mobilePhone[indexField] = buffer[indexBuffer];
					++indexField;
					++indexBuffer;
				}
				_mobilePhone[indexField] = '\0';

				++indexBuffer;
				indexField = 0;
				while (buffer[indexBuffer] != '\0') {
					_additInform[indexField] = buffer[indexBuffer];
					++indexField;
					++indexBuffer;
				}
				_additInform[indexField] = '\0';

				this->addSubscriber(
					_surname,
					_name,
					_patronymic,
					_homePhone,
					_workPhone,
					_mobilePhone,
					_additInform,
					false
				);
			}
			fin.close();
		}
	}
};
// КОНЕЦ КЛАССА Телефонная книга


// ГЛАВНАЯ ФУНКЦИЯ
int main() {
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	PhoneBook phoneBook("data.txt");

//	phoneBook.addSubscriber("Иванов", "Иван", "Иванович", "83422676707", "83422655711", "89526565465", "Рыжий");
//	phoneBook.addSubscriber("Петров", "Петр", "Петрович", "83422606006", "83422644404", "89546465466", "Кудрявый");
//	phoneBook.addSubscriber("Карпов", "Карп", "Карпович", "83422656505", "83422633303", "89536312363", "В очках");

	phoneBook.show();

	return 0;
}
// КОНЕЦ ГЛАВНОЙ ФУНКЦИИ