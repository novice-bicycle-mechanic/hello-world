// ������� �� ����� DZ_ST_C++_01.pdf
//
// ����: ������������, �����������
// ������� 2, �������
/*
�������� ���������� "���������� �����".
���������� ������� ������ �� ��������
(���, �������� �������, ������� �������,
��������� �������, �������������� ���������� � ��������)
������ ���������������� ������.
��������� ����� �����������-�������, ���������-�������,
��������������, inline-���������-�������, �����������
��������������, ���������� ����������.
����������� ���������� �������� ����������� ������ ��� ���.
������������ ������������ ����������� ��������� �����
���������, ������� ���������, ������ ��������� �� ���,
���������� ���� ���������, ��������� ���������� � ����
� ��������� �� �����.
*/
#include <iostream>
#include <clocale>
#include <Windows.h>
#include <iomanip>
#include <conio.h>
#include <fstream>
using namespace std;


// ����� �������
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
	// ����������� �� ���������
	Subscriber() {}

	// ����������� � �����������
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

	// ����������� �����������
	Subscriber(Subscriber& object) { *this = object; }

	// �����������
	~Subscriber() {
		if (surname    ) delete[] surname    ;
		if (name       ) delete[] name       ;
		if (patronymic ) delete[] patronymic ;
		if (homePhone  ) delete[] homePhone  ;
		if (workPhone  ) delete[] workPhone  ;
		if (mobilePhone) delete[] mobilePhone;
		if (additInform) delete[] additInform;
	}
	
	// GETTER-�
	char* getSurname    () { return surname    ; }
	char* getName       () { return name       ; }
	char* getPatronymic () { return patronymic ; }
	char* getHomePhone  () { return homePhone  ; }
	char* getWorkPhone  () { return workPhone  ; }
	char* getMobilePhone() { return mobilePhone; }
	char* getAdditInform() { return additInform; }

	// ����� ����������� ������ ������������� ���� � ������ ���� char
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

	// ����� ������ ������ �������� � ��� ������
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

	// ����� ������ ��������� � ��� ������
	void header(size_t numberLine = 0) {
		switch (numberLine) {
		case 0:
		case 1: {
			cout
				<< setw(1) << ""
				<< setw(w_surname   ) << left << "�������"
				<< setw(w_name      ) << left << "���"
				<< setw(w_patromymic) << left << "��������"
				<< endl;
			if (numberLine) break;
		}
		case 2: {
			cout
				<< setw(1) << ""
				<< setw(w_homePhone  ) << left << "�������� �������"
				<< setw(w_workPhone  ) << left << "������� �������"
				<< setw(w_mobilePhone) << left << "��������� �������"
				<< endl;
			if (numberLine) break;
		}
		case 3: {
			cout
				<< setw(1) << ""
				<< setw(w_additInform) << left << "�������������� ������"
				<< endl;
			if (numberLine) break;
		}
		}
	}

	// ����� ������ ������ �������� �� ����� - ��������
	bool showCard() {
		enum class Buttons { ESC = 27, D1 = 49, D2, D3, D4, D5, D6, D7 }; // Dn-�����
		char button1byte{ '\0' };
		bool _saveInFile = false;
		string buffer;
		const char* fieldName[8]{
			" �������� �� ",
			" 1.�������: ",
			" 2.���: ",
			" 3.��������: ",
			" 4.�������� �������: ",
			" 5.������� �������: ",
			" 6.��������� �������: ",
			" 7.�������������� ������: "
		};

		while (true) {
			system("cls");

			cout << " [Esc]-����� �� ��������, [�����]-������������� ���� �" << endl << endl;
			cout << "                    �������� ��������" << endl;
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

	// ����� ������ ������ �������� � ������ �����
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

	// ����� ������ � ������ ����� ������ ����� �������
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

	// ����� ������ ������ ������ �� �����
	void replaceLine(
		char*& oldLine,
		char* newLine
	) {
		if (oldLine) delete[] oldLine;
		oldLine = newLine;
	}

	// ����� �������������, ��� ������ ������ �������� ������
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
// ����� ������ �������



// ����� ���������� �����
class PhoneBook {
private:
	size_t lengthPhoneBook{ 0 };
	Subscriber** arrayPhoneBook{ nullptr };
	const char* nameFilePhoneBook;
	std::streamsize w_numberScriber{ 3 };
public:
	// ����������� � ����������
	PhoneBook(const char* nameFile) {
//		cout << "����������� PhoneBook � ����������" << endl;
		nameFilePhoneBook = nameFile;
	}

	// �������������
	~PhoneBook() {
//		cout << "���������� ~PhoneBook" << endl;
		if (arrayPhoneBook) delete[] arrayPhoneBook;
	}

	// ����� ������ ���������� ����� �� �����
	void show() {

		enum class KeysC { ESC = 27 };
		enum class KeysF { BYTE1KEY = 0, F1 = 59, F2, F3, F4, F5, F6, F7, F8, F9 };
		char byte1key{ '\0' };
		char byte2key{ '\0' };
		size_t numberSubscriber{ 0 };
		bool _saveInFile = false;

		while (true) {

			system("cls");

			cout << " [Esc]-����� �� ���������, [F1]-�������� ��������" << endl;
			cout << " [F4]-�������� ��������, [F5]-������� ��������, [F8]-����� ��������" << endl;
			cout << endl;
			cout << "                     ���������� �����" << endl;
			cout << endl;

			this->uploadFromFile();

			if (!arrayPhoneBook || !arrayPhoneBook[0]) {
				cout << " ���������� ����� �� �������� ���������" << endl;
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

			// ������ [Esc] - ����� �� ���������
			if (byte1key == (int)KeysC::ESC) break;
			// ������ [F1] - ����� �� ����� �������� ��������
			else if ((byte1key == (int)KeysF::BYTE1KEY) && (byte2key == (int)KeysF::F1)) {
				if (arrayPhoneBook) {
					cout << " ������� ����� ��������, ��� �������� ������� �� �����: ";
					cin >> numberSubscriber;
					if ((0 < numberSubscriber) && (numberSubscriber <= lengthPhoneBook) &&
						(arrayPhoneBook[indexFromNumber(numberSubscriber)])) {
						_saveInFile = arrayPhoneBook[indexFromNumber(numberSubscriber)]->showCard();
						if (_saveInFile) this->saveInFile();
					}
					else {
						cout
							<< " ������� �"
							<< numberSubscriber
							<< " � ���������� ����� �����������"
							<< endl;
						Sleep(2000);
					}
				}
			}
			// ������ [F4] - �������� ��������
			else if ((byte1key == (int)KeysF::BYTE1KEY) && (byte2key == (int)KeysF::F4)) {
				this->addSubscriber("", "", "", "", "", "", "");
				this->saveInFile();
			}
			// ������ [F5] - ������� ��������
			else if ((byte1key == (int)KeysF::BYTE1KEY) && (byte2key == (int)KeysF::F5)) {
				if (arrayPhoneBook) {
					cout << " ������� ����� ���������� ��������: ";
					cin >> numberSubscriber;
					this->delSubscriber(numberSubscriber);
				}
				this->saveInFile();
			}
			// ������ [F8] - ����� ��������
			else if ((byte1key == (int)KeysF::BYTE1KEY) && (byte2key == (int)KeysF::F8)) {
				if (arrayPhoneBook) {
					string word;
					cout << " ������� ��� ������ ����� �������� � ���: ";
					cin >> word;
					searchSubscriber(word);
				}
			}
		}
	}

	// ����� ������ �������� �� �����, ��������� � ���
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

	// ����� ������ �� ����� ��������� �������
	template <typename T>
	void header(T& object) {

		cout << setw(w_numberScriber) << right << " � ";
		object.header(1);

		cout << setw(w_numberScriber) << right << "";
		object.header(2);

		cout << setw(w_numberScriber) << right << "";
		object.header(3);
	}

	// ����� ������ �� ����� �������� ������� ��� ������ �������
	void showLine(size_t index) {

		cout << setw(w_numberScriber) << right << numberFromIndex(index);
		arrayPhoneBook[index]->showLine(1);

		cout << setw(w_numberScriber) << right << "";
		arrayPhoneBook[index]->showLine(2);

		cout << setw(w_numberScriber) << right << "";
		arrayPhoneBook[index]->showLine(3);
	}

	// ����� ����������� ������� ������� �� ������ � �������
	size_t indexFromNumber(size_t number) {
		if (number) return --number;
		else return 0;
	}

	// ����� ����������� ������ � ������� �� ������� �������
	size_t numberFromIndex(size_t index) {
		return ++index;
	}

	// ����� ���������� �������� � ������ - � ��������� �����������
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

	// ����� �������� ��������
	void delSubscriber(size_t numberSubscriber) {

		if (!((0 < numberSubscriber) && (numberSubscriber <= lengthPhoneBook))) {
			cout << " ������� � ��������� ������� �����������" << endl;
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

			cout << " ������� �" << numberSubscriber << " ������" << endl;
			Sleep(2000);
			this->saveInFile();
			return;
		}
	}

	// ����� ������ ���������� ����� � ��������� ����
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

	// ����� �������� ���������� ����� �� ���������� �����
	void uploadFromFile() {
		ifstream fin;
		if (nameFilePhoneBook) fin.open(nameFilePhoneBook);

		if (!fin.is_open()) {
			cout << " ���� ���������� ����� �����������" << endl;
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
// ����� ������ ���������� �����


// ������� �������
int main() {
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	PhoneBook phoneBook("data.txt");

//	phoneBook.addSubscriber("������", "����", "��������", "83422676707", "83422655711", "89526565465", "�����");
//	phoneBook.addSubscriber("������", "����", "��������", "83422606006", "83422644404", "89546465466", "��������");
//	phoneBook.addSubscriber("������", "����", "��������", "83422656505", "83422633303", "89536312363", "� �����");

	phoneBook.show();

	return 0;
}
// ����� ������� �������