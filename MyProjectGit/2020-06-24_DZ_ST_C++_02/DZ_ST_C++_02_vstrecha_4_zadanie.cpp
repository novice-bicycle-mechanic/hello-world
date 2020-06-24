// ������� �� ����� DZ_ST_C++_02.pdf
// ������� �4
// ����: ��������� this. ��������� �����������. ����������� �����������.
// �������.
/*
�������� ���������, ����������� ���������������
���. ���������� ����� ������ ��������, ����������,
����. ����� ���������� �������� ������������ ������
�������� ������ ��������. ����� ���� �������� ������
�������� ������ ����������.
������ �� ������� �������� ����������-����� � ����-
���-�����, ������� ���������� ��� ���������� �������
������. �������� ���� ��������, ��� ������ ��� ����-
����� �������� ���������� �����������. ��������, ���
��� � ������ ��������. �� ��������� ���������� ������
���������� �������������� (����������� �����������
����������), �������������. � main �������������� ��-
���� ����������� ������ �������.
*/
#include <iostream>
#include <clocale>
#include <iomanip>
using namespace std;

#define pendl cout << endl;


// ����� �������
class Utilities {
public:
	// ����� �������� ������������ ������ ������������� ���������
	template <typename T>
	void deletePointer(T& pointer) {
		if (pointer) {
			delete[] pointer;
			pointer = nullptr;
		}
	}
	// ����� �������� ������ string ���������������� ����� � ���� char*
	template <typename T>
	char* s(T* string) {
		size_t length = 0;
		while (string[length++]);
		char* line = new char[length] {'\0'};
		--length;
		if (length) {
			for (size_t i = 0; i < length; i++) {
				line[i] = string[i];
			}
		}
		return line;
	}
	// ����� �������� ������� ������� �� ������ ������� � �������
	size_t numberToIndex(size_t number) {
		if (number > 0) return --number;
		else return 0;
	}
	// ����� �������� ������ ������� � ������� �� ������� � �������
	size_t indexToNumber(size_t index) {
		return ++index;
	}
}u;


// ����� �������
class Human {
public:
	enum class Gender { NONE, WOMAN, MAN };
private:
	char* surname    = nullptr;    // �������
	char* name       = nullptr;    // ���
	char* patronymic = nullptr;    // ��������
	Gender gender = Gender::NONE;  // ���
	struct {
		size_t day   = 0;          // ����  - ���� ��������
		size_t month = 0;          // ����� - ���� ��������
		size_t year  = 0;          // ���   - ���� ��������
	}birthdate;                    // ���� ��������
	std::streamsize p_surname = 14;
	std::streamsize p_name = 12;
	std::streamsize p_patronymic = 16;
public:
	// ����������� �� ���������
	Human(){}
	// ����������� � �����������
	Human(
		char*  surname   ,
		char*  name      ,
		char*  patronymic,
		Gender gender    ,
		size_t day       ,
		size_t month     ,
		size_t year
	) {
		setSurname       (surname   );
		setName          (name      );
		setPatronymic    (patronymic);
		setGender        (gender    );
		setBirthdateDay  (day       );
		setBirthdateMonth(month     );
		setBirthdateYear (year      );
	}
	// ����������� �����������
	Human(Human& object) { *this = object; }
	// ����������
	~Human() {
		if (surname   )delete[] surname   ;
		if (name      )delete[] name      ;
		if (patronymic)delete[] patronymic;
	}

	// ������� ���� ������ �������� �����
	void setHuman(
		char* surname,
		char* name,
		char* patronymic,
		Gender gender,
		size_t day,
		size_t month,
		size_t year
	) {
		setSurname(surname);
		setName(name);
		setPatronymic(patronymic);
		setGender(gender);
		setBirthdateDay(day);
		setBirthdateMonth(month);
		setBirthdateYear(year);
	}

	// setter-�
	void setSurname       (char* surname   ) { this->surname         = surname   ; }
	void setName          (char* name      ) { this->name            = name      ; }
	void setPatronymic    (char* patronymic) { this->patronymic      = patronymic; }
	void setGender        (Gender gender   ) { this->gender          = gender    ; }
	void setBirthdateDay  (size_t day      ) { this->birthdate.day   = day       ; }
	void setBirthdateMonth(size_t month    ) { this->birthdate.month = month     ; }
	void setBirthdateYear (size_t year     ) { this->birthdate.year  = year      ; }

	// getter-�
	char*  getSurname       () { return surname        ; }
	char*  getName          () { return name           ; }
	char*  getPatronymic    () { return patronymic     ; }
	Gender getGender        () { return gender         ; }
	size_t getBirthdateDay  () { return birthdate.day  ; }
	size_t getBirthdateMonth() { return birthdate.month; }
	size_t getBirthdateYear () { return birthdate.year ; }

	// ������ ��������� ��� ������ ��������
	void header() {
		cout
			<< setw(p_surname   ) << left << "�������"
			<< setw(p_name      ) << left << "���"
			<< setw(p_patronymic) << left << "��������"
			<< setw(5) << left << "���"
			<< "���� ��������"
			<< endl;
	}

	// ������ ������ ��������
	void print() {
		cout
			<< setw(p_surname   ) << left << surname
			<< setw(p_name      ) << left << name
			<< setw(p_patronymic) << left << patronymic
			<< " " << setw(3) << left << (gender == Human::Gender::MAN ? "�" : "�")
			<< setw(2) << ""
			<< (birthdate.day < 10 ? "0" : "") << birthdate.day << "."
			<< (birthdate.month < 10 ? "0" : "") << birthdate.month << "."
			<< birthdate.year
			<< endl;
	}
}h;


// ����� ��������
class Flat {
private:
	size_t numFlat    = 0;      // ����� ��������
	size_t floor      = 0;      // ���� ������������ ��������
	size_t numRooms   = 0;      // ���������� ������
	size_t area       = 0;      // ������� ��������, ��.�
	size_t height     = 0;      // ������ ������, ��
	size_t numTenants = 0;      // ���������� �������
	Human** tenants = nullptr;  // ������ ������

	std::streamsize w_numFlat    = 6;
	std::streamsize w_floor      = 8;
	std::streamsize w_numRooms   = 7;
	std::streamsize w_area       = 8;
	std::streamsize w_height     = 9;
	std::streamsize w_numTenants = 8;

public:
	// ����������� �� ���������
	Flat(){}
	// ����������� � �����������
	Flat(
		size_t floor   ,
		size_t numRooms,
		size_t area    ,
		size_t height
	) {
		setFloor   (floor   );
		setNumRooms(numRooms);
		setArea    (area    );
		setHeight  (height  );
	}
	// ����������� �����������
	Flat(Flat& object) { *this = object; }
	// ����������
	~Flat() {
		if (tenants) delete[] tenants;
		tenants = nullptr;
	}

	// ����� ���������� ������ � ��������
	template <typename T>
	void addTenant(
		T surname,
		T name,
		T patronymic,
		Human::Gender gender,
		size_t day,
		size_t month,
		size_t year
	) {
		// ������� �����, ����������� �� 1, ������ buffer ��������-���������
		Human** buffer = new Human * [(numTenants + 1)]{ nullptr };

		// �������� tenants � buffer
		if (tenants) {
			for (size_t i = 0; i < numTenants; i++) {
				buffer[i] = tenants[i];
			}
		}
		// ��������� � ������ buffer ������ �������� - ������
		buffer[numTenants] = new Human;
		buffer[numTenants]->setHuman(u.s(surname), u.s(name), u.s(patronymic), gender, day, month, year);
	
		// ������ buffer �� tenants
		if (tenants) delete[] tenants;
		tenants = buffer;
		buffer = nullptr;

		// �������� ���������� ������� � ������������ � �����������
		numTenants++;
	}

	// ����� �������� ������ �� ��������
	bool delTenant(size_t numTenant) {
		// ������������
		//   numTenant   - ������������ �����  ������ � �������
		// � indexTenant - ������������ ������ ������ � �������
		size_t indexTenant = u.numberToIndex(numTenant);

		// �������� ��������� ������� ������ � ����������� ��������
		if ((0 <= indexTenant) && (indexTenant < numTenants)) {

			// �������� ������ ������� ������� �������� �� 1, ��� ������� ������
			size_t newNumTenants = numTenants - 1;

			if (newNumTenants) {

				Human** buffer = new Human * [newNumTenants] { nullptr };

				// �������� �� ��������� ������� ������ �� ��������� � ����������� ��������
				// ��� ����������� ������� �� ������ ������� �� ���������� ������
				if ((0 <= indexTenant) && (indexTenant < numTenants)) {

					for (size_t i = 0; i < indexTenant; i++) {
						buffer[i] = tenants[i];
					}
				}

				// ����������� ������� ����� ���������� ������
				size_t newMinItem = indexTenant + 1;
				for (size_t i = indexTenant, j = newMinItem; i < newNumTenants; i++, j++) {
					buffer[i] = tenants[j];
				}

				delete[] tenants;
				tenants = buffer;
				buffer = nullptr;
				numTenants = newNumTenants;
				return true;
			}
			else {

				delete[] tenants;
				tenants = nullptr;
				numTenants = newNumTenants;
				return true;
			}

		}
		else return false;
	}

	// setter-�
	void setNumFlat (size_t numFlat ) { this->numFlat  = numFlat ; }
	void setFloor   (size_t floor   ) { this->floor    = floor   ; }
	void setNumRooms(size_t numRooms) { this->numRooms = numRooms; }
	void setArea    (size_t area    ) { this->area     = area    ; }
	void setHeight  (size_t height  ) { this->height   = height  ; }

	void setFlat(
		size_t floor,
		size_t numRooms,
		size_t area,
		size_t height
	) {
		setFloor(floor);
		setNumRooms(numRooms);
		setArea(area);
		setHeight(height);
	}

	// getter-�
	size_t getNumFlat   () { return numFlat   ; }
	size_t getFloor     () { return floor     ; }
	size_t getNumRooms  () { return numRooms  ; }
	size_t getArea      () { return area      ; }
	size_t getHeight    () { return height    ; }
	size_t getNumTenants() { return numTenants; }

	Human** getTenants(                 ) { return tenants            ; }
	Human*  getTenants(size_t numTenants) { return tenants[numTenants]; }

	// ������ ��������� ������� ������� ��������
	void headerTenants(size_t numFlat = 0, std::streamsize w_numFlat = 0) {
		cout << setw(3) << "  �  ";
		if (numFlat) {
			cout << setw(w_numFlat) << " ��.  ";
		}
		h.header();
	}

	// ������ ������ ������� ��������
	size_t printTenants(size_t numberTenant = 0, size_t numFlat = 0, std::streamsize w_numFlat = 0) {
		if (tenants) {
			for (size_t i = 0; i < numTenants; i++) {
				if (numFlat) {
					++numberTenant;
					cout << setw(w_numFlat) << right << numberTenant;
					cout << setw(w_numFlat) << right << numFlat;
					cout << "   ";
				}
				else {
					cout << setw(3) << right << u.indexToNumber(i) << "  ";
				}
				tenants[i]->print();
			}
		}
		return numberTenant;
	}

	// ������ ��������� ��� ������ ������ �������� � ������
	void headerLine() {
		cout << " ��������  ����  ������  �������  ������  �������" << endl;
	}

	// ������ ������ �������� � ������
	void printLine() {
		cout
			<< setw(w_numFlat) << numFlat
			<< setw(w_floor) << floor
			<< setw(w_numRooms) << numRooms
			<< setw(w_area) << area
			<< setw(w_height) << height
			<< setw(w_numTenants) << numTenants
			<< endl;
	}

	// ������ �������� ��������
	void printCard() {

		cout << "                �������� ��������" << endl;
		cout << "                -----------------" << endl;
		cout << "         ����� ��������: " << getNumFlat   () << endl;
		cout << "                   ����: " << getFloor     () << endl;
		cout << "      ���������� ������: " << getNumRooms  () << endl;
		cout << " ������� ��������, ��.�: " << getArea      () << endl;
		cout << "    ������ ��������, ��: " << getHeight    () << endl;
		cout << "     ���������� �������: " << getNumTenants() << endl;

		if (getNumTenants()) {
			cout << " -------------------- ������ �������� ----------------------" << endl;
			headerTenants();
			printTenants();
		}
	}
}f;


// ����� ���
class House {
private:
	Flat** flats = nullptr;       // ������ �������
	size_t numFlats  = 0;         // ���������� �������
	size_t numFloors = 0;         // ���������� ������
	struct {
		char* country = nullptr;  // ������     - ������
		char* region  = nullptr;  // �������    - ������
		char* city    = nullptr;  // �����      - ������
		char* street  = nullptr;  // �����      - ������
		size_t numHouse = 0;      // ����� ���� - ������
	}address;                     // �����
public:
	// ����������� �� ���������
	House(){}
	// ����������� � �����������
	House(
		size_t numFlats ,
		size_t numFloors,
		char*  country  ,
		char*  region   ,
		char*  city     ,
		char*  street   ,
		size_t numHouse	
	) {
		setNunFlats (numFlats );
		setNumFloors(numFloors);
		setCountry  (country  );
		setRegion   (region   );
		setCity     (city     );
		setStreet   (street   );
		setNumHouse (numHouse );
		setFlats();
	}

	// ����������� �����������
	House(House& object) { *this = object; }

	// ����������
	~House() {
		u.deletePointer<Flat**>(flats          );
		u.deletePointer<char* >(address.country);
		u.deletePointer<char* >(address.region );
		u.deletePointer<char* >(address.city   );
		u.deletePointer<char* >(address.street );
	}

	// setter-�
	void setNumFloors(size_t numFloors) { this->numFloors        = numFloors; }
	void setCountry  (char*  country  ) { this->address.country  = country  ; }
	void setRegion   (char*  region   ) { this->address.region   = region   ; }
	void setCity     (char*  city     ) { this->address.city     = city     ; }
	void setStreet   (char*  street   ) { this->address.street   = street   ; }
	void setNumHouse (size_t numHouse ) { this->address.numHouse = numHouse ; }

	// ������� ���������� ������� � ����
	// � �������� ������� ������� ���������� �������
	void setNunFlats(size_t numFlats) {
		if (this->numFlats != numFlats) {
			this->numFlats = numFlats;
			if (flats) delete[] flats;
			flats = new Flat * [this->numFlats]{ nullptr };
		}
	}

	// ������� ������� - ��� ������, ������ �����
	void setFlats() {
		// �������� � ������� �������� � ������ �� ������
		if (flats) {
			for (size_t i = 0; i < numFlats; i++) {
				if (!flats[i]) {
					flats[i] = new Flat;
					flats[i]->setNumFlat(u.indexToNumber(i));
				}
			}
		}
	}

	// getter-�
	size_t getNumFlats () { return this->numFlats        ; }
	size_t getNumFloors() { return this->numFloors       ; }
	char*  getCountry  () { return this->address.country ; }
	char*  getRegion   () { return this->address.region  ; }
	char*  getCity     () { return this->address.city    ; }
	char*  getStreet   () { return this->address.street  ; }
	size_t getNumHouse () { return this->address.numHouse; }

	Flat** getFlats(              ) { return this->flats         ; }
	Flat*  getFlats(size_t numFlat) { return this->flats[numFlat]; }

	// ����� ������ �������� ������� ����
	void printProperties() {
		cout << "      �������� ����" << endl;
		cout << "      -------------" << endl;
		cout << " ���������� ������� = " << getNumFlats () << endl;
		cout << " ���������� ������  = " << getNumFloors() << endl;
		cout << " �����:" << endl;
		cout << "        ������: " << getCountry () << endl;
		cout << "        ������: " << getRegion  () << endl;
		cout << "         �����: " << getCity    () << endl;
		cout << "         �����: " << getStreet  () << endl;
		cout << "    ����� ����: " << getNumHouse() << endl;
	}

	// ����� ������ ������� �������
	void printFlats() {
		if (flats) {
			cout << "                  �������� ����" << endl;
			cout << "                  -------------" << endl;
			f.headerLine();
			for (size_t i = 0; i < this->numFlats; i++) {
				this->flats[i]->printLine();
			}
		}
	}

	// ����� ������ ������� ������� ����
	void printTenants() {
		if (flats) {
			cout << "                           ������ ����" << endl;
			cout << "                           -----------" << endl;
			f.headerTenants(1, 4);
			pendl;

			size_t numberTenant = 0;
			// ������ ������� ������� �������
			for (size_t i = 0; i < this->numFlats; i++)	{
				numberTenant = flats[i]->printTenants(numberTenant, u.indexToNumber(i), 4);
			}
		}
	}
};


// ������� �������
int main() {
	setlocale(LC_ALL, "ru");

	// �������� ������ ���
	House house(
		9,                     // ���������� �������
		5,                     // ���������� ������
		u.s("������"),         // ������ ������
		u.s("�������� ����"),  // ������ ������
		u.s("�����"),          // ����� ������
		u.s("������"),         // ����� ������
		1                      // ����� ���� ������
	);

	// ������� ��������� ������� ����:
	// (� ��������)->(����, ���-�� ������, �������(��.�), ������ ������(��))
	house.getFlats(u.numberToIndex(1))->setFlat(1, 1, 30, 250);
	house.getFlats(u.numberToIndex(2))->setFlat(1, 1, 30, 250);
	house.getFlats(u.numberToIndex(3))->setFlat(2, 1, 30, 250);
	house.getFlats(u.numberToIndex(4))->setFlat(2, 2, 50, 250);
	house.getFlats(u.numberToIndex(5))->setFlat(3, 1, 30, 250);
	house.getFlats(u.numberToIndex(6))->setFlat(3, 2, 50, 250);
	house.getFlats(u.numberToIndex(7))->setFlat(4, 1, 30, 250);
	house.getFlats(u.numberToIndex(8))->setFlat(4, 2, 50, 250);
	house.getFlats(u.numberToIndex(9))->setFlat(5, 3, 80, 350);

	// ������� ������� ����
	house.getFlats(u.numberToIndex(1))->addTenant("������"    , "����"     , "��������"     , Human::Gender::MAN  , 14,  5, 1957);
	house.getFlats(u.numberToIndex(1))->addTenant("�������"   , "�����"    , "����������"   , Human::Gender::WOMAN, 22,  3, 1961);
	house.getFlats(u.numberToIndex(2))->addTenant("���������" , "�������"  , "�����������"  , Human::Gender::MAN  ,  7,  9, 1939);
	house.getFlats(u.numberToIndex(2))->addTenant("����������", "�������"  , "�������"      , Human::Gender::WOMAN, 23, 12, 1945);
	house.getFlats(u.numberToIndex(3))->addTenant("��������"  , "������"   , "����������"   , Human::Gender::MAN  ,  1,  7, 1968);
	house.getFlats(u.numberToIndex(3))->addTenant("���������" , "��������" , "�������������", Human::Gender::WOMAN, 24,  2, 1973);
	house.getFlats(u.numberToIndex(4))->addTenant("�������"   , "�������"  , "����������"   , Human::Gender::MAN  , 11,  8, 1985);
	house.getFlats(u.numberToIndex(4))->addTenant("��������"  , "�������"  , "��������"     , Human::Gender::WOMAN,  3,  4, 1986);
	house.getFlats(u.numberToIndex(4))->addTenant("��������"  , "��������" , "����������"   , Human::Gender::WOMAN, 16, 12, 2006);
	house.getFlats(u.numberToIndex(4))->addTenant("��������"  , "�����"    , "����������"   , Human::Gender::WOMAN,  8,  6, 2011);
	house.getFlats(u.numberToIndex(5))->addTenant("���������" , "������"   , "����������"   , Human::Gender::MAN  , 28,  3, 1993);
	house.getFlats(u.numberToIndex(5))->addTenant("����������", "������"   , "���������"    , Human::Gender::WOMAN,  8,  7, 2001);
	house.getFlats(u.numberToIndex(5))->addTenant("���������" , "������"   , "����������"   , Human::Gender::MAN  , 14, 10, 2018);
	house.getFlats(u.numberToIndex(6))->addTenant("��������"  , "��������" , "����������"   , Human::Gender::MAN  , 21,  5, 1975);
	house.getFlats(u.numberToIndex(6))->addTenant("���������" , "�����"    , "��������"     , Human::Gender::WOMAN, 19,  2, 1975);
	house.getFlats(u.numberToIndex(6))->addTenant("��������"  , "�������"  , "������������" , Human::Gender::MAN  , 17,  1, 2004);
	house.getFlats(u.numberToIndex(6))->addTenant("��������"  , "��������" , "������������" , Human::Gender::MAN  , 14, 10, 2008);
	house.getFlats(u.numberToIndex(7))->addTenant("����������", "����"     , "�������������", Human::Gender::WOMAN,  5,  4, 1988);
	house.getFlats(u.numberToIndex(8))->addTenant("�������"   , "������"   , "���������"    , Human::Gender::MAN  ,  4,  3, 1990);
	house.getFlats(u.numberToIndex(8))->addTenant("��������"  , "��������" , "����������"   , Human::Gender::WOMAN, 29, 12, 1996);
	house.getFlats(u.numberToIndex(8))->addTenant("��������"  , "�������"  , "���������"    , Human::Gender::WOMAN, 26, 12, 2015);
	house.getFlats(u.numberToIndex(8))->addTenant("��������"  , "�������"  , "���������"    , Human::Gender::WOMAN, 26, 12, 2015);
	house.getFlats(u.numberToIndex(9))->addTenant("�������"   , "���������", "���������"    , Human::Gender::MAN  ,  6,  7, 1980);
	house.getFlats(u.numberToIndex(9))->addTenant("��������"  , "�����"    , "����������"   , Human::Gender::WOMAN, 27, 12, 1994);
	house.getFlats(u.numberToIndex(9))->addTenant("�������"   , "������"   , "�������������", Human::Gender::MAN  ,  9, 10, 2019);

	// ����������� �������� �������� ���� (�������� ����)
	house.printProperties();
	pendl;

	// ����������� ������� ������� ����
	house.printFlats();
	pendl;

	// ����������� ������� ������� ����
	house.printTenants();
	pendl;

	// ����������� �������� �������� �7
	house.getFlats(u.numberToIndex(7))->printCard();
	pendl;

	// ������� ������� ������ �������� �7 ����������� �.�.
	cout << " ������� ������� ������ �������� �7 ����������� �.�. �� ����������" << endl;
	house.getFlats(u.numberToIndex(7))->getTenants()[u.numberToIndex(1)]->setSurname(u.s("����������"));

	// ������� ������ � �������� �7
	cout << " ������� � �������� �7 ������ ������ ���������� �.�." << endl << endl;
	house.getFlats(u.numberToIndex(7))->addTenant("���������", "�������", "��������", Human::Gender::MAN, 8, 7, 1980);

	// ����������� �������� �������� �7
	house.getFlats(u.numberToIndex(7))->printCard();
	pendl;

	// ������ ������ �������� �7 ���������� �.�.
	cout << " ������ �� �������� �7 ������ ���������� �.�." << endl << endl;
	house.getFlats(u.numberToIndex(7))->delTenant(2);

	// ����������� �������� �������� �7
	house.getFlats(u.numberToIndex(7))->printCard();
	pendl;

	// ����������� ������� ������� ����
	house.printTenants();

	return 0;
}