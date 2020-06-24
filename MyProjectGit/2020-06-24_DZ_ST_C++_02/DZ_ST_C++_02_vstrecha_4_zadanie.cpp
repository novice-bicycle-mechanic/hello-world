// задание из файла DZ_ST_C++_02.pdf
// Встреча №4
// Тема: Указатель this. Побитовое копирование. Конструктор копирования.
// Задание.
/*
Создайте программу, имитирующую многоквартирный
дом. Необходимо иметь классы “Человек”, “Квартира”,
“Дом”. Класс “Квартира” содержит динамический массив
объектов класса “Человек”. Класс “Дом” содержит массив
объектов класса “Квартира”.
Каждый из классов содержит переменные-члены и функ-
ции-члены, которые необходимы для предметной области
класса. Обращаем ваше внимание, что память под стро-
ковые значения выделяется динамически. Например, для
ФИО в классе “Человек”. Не забывайте обеспечить классы
различными конструкторами (конструктор копирования
обязателен), деструкторами. В main протестировать ра-
боту полученного набора классов.
*/
#include <iostream>
#include <clocale>
#include <iomanip>
using namespace std;

#define pendl cout << endl;


// КЛАСС Утилиты
class Utilities {
public:
	// метод удаления динамической памяти принадлежащей указателю
	template <typename T>
	void deletePointer(T& pointer) {
		if (pointer) {
			delete[] pointer;
			pointer = nullptr;
		}
	}
	// метод возврата строки string оптимизированной длины и типа char*
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
	// метод возврата индекса массива из номера объекта в таблице
	size_t numberToIndex(size_t number) {
		if (number > 0) return --number;
		else return 0;
	}
	// метод возврата номера объекта в таблице из индекса в массиве
	size_t indexToNumber(size_t index) {
		return ++index;
	}
}u;


// КЛАСС Человек
class Human {
public:
	enum class Gender { NONE, WOMAN, MAN };
private:
	char* surname    = nullptr;    // фамилия
	char* name       = nullptr;    // имя
	char* patronymic = nullptr;    // отчество
	Gender gender = Gender::NONE;  // пол
	struct {
		size_t day   = 0;          // день  - даты рождения
		size_t month = 0;          // месяц - даты рождения
		size_t year  = 0;          // год   - даты рождения
	}birthdate;                    // дата рождения
	std::streamsize p_surname = 14;
	std::streamsize p_name = 12;
	std::streamsize p_patronymic = 16;
public:
	// конструктор по умолчанию
	Human(){}
	// конструктор с параметрами
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
	// конструктор копирования
	Human(Human& object) { *this = object; }
	// деструктор
	~Human() {
		if (surname   )delete[] surname   ;
		if (name      )delete[] name      ;
		if (patronymic)delete[] patronymic;
	}

	// задание всех данных человека сразу
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

	// setter-ы
	void setSurname       (char* surname   ) { this->surname         = surname   ; }
	void setName          (char* name      ) { this->name            = name      ; }
	void setPatronymic    (char* patronymic) { this->patronymic      = patronymic; }
	void setGender        (Gender gender   ) { this->gender          = gender    ; }
	void setBirthdateDay  (size_t day      ) { this->birthdate.day   = day       ; }
	void setBirthdateMonth(size_t month    ) { this->birthdate.month = month     ; }
	void setBirthdateYear (size_t year     ) { this->birthdate.year  = year      ; }

	// getter-ы
	char*  getSurname       () { return surname        ; }
	char*  getName          () { return name           ; }
	char*  getPatronymic    () { return patronymic     ; }
	Gender getGender        () { return gender         ; }
	size_t getBirthdateDay  () { return birthdate.day  ; }
	size_t getBirthdateMonth() { return birthdate.month; }
	size_t getBirthdateYear () { return birthdate.year ; }

	// печать заголовка для данных человека
	void header() {
		cout
			<< setw(p_surname   ) << left << "Фамилия"
			<< setw(p_name      ) << left << "Имя"
			<< setw(p_patronymic) << left << "Отчество"
			<< setw(5) << left << "Пол"
			<< "Дата рождения"
			<< endl;
	}

	// печать данных человека
	void print() {
		cout
			<< setw(p_surname   ) << left << surname
			<< setw(p_name      ) << left << name
			<< setw(p_patronymic) << left << patronymic
			<< " " << setw(3) << left << (gender == Human::Gender::MAN ? "М" : "Ж")
			<< setw(2) << ""
			<< (birthdate.day < 10 ? "0" : "") << birthdate.day << "."
			<< (birthdate.month < 10 ? "0" : "") << birthdate.month << "."
			<< birthdate.year
			<< endl;
	}
}h;


// КЛАСС Квартира
class Flat {
private:
	size_t numFlat    = 0;      // номер квартиры
	size_t floor      = 0;      // этаж расположения квартиры
	size_t numRooms   = 0;      // количество комнат
	size_t area       = 0;      // площадь квартиры, кв.м
	size_t height     = 0;      // высота комнат, см
	size_t numTenants = 0;      // количество жильцов
	Human** tenants = nullptr;  // массив жильцы

	std::streamsize w_numFlat    = 6;
	std::streamsize w_floor      = 8;
	std::streamsize w_numRooms   = 7;
	std::streamsize w_area       = 8;
	std::streamsize w_height     = 9;
	std::streamsize w_numTenants = 8;

public:
	// конструктор по умолчанию
	Flat(){}
	// конструктор с параметрами
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
	// конструктор копирования
	Flat(Flat& object) { *this = object; }
	// деструктор
	~Flat() {
		if (tenants) delete[] tenants;
		tenants = nullptr;
	}

	// метод добавления жильца в квартиру
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
		// создаем новый, увеличенный на 1, массив buffer объектов-Человеков
		Human** buffer = new Human * [(numTenants + 1)]{ nullptr };

		// копируем tenants в buffer
		if (tenants) {
			for (size_t i = 0; i < numTenants; i++) {
				buffer[i] = tenants[i];
			}
		}
		// добавляем в массив buffer объект Человека - жильца
		buffer[numTenants] = new Human;
		buffer[numTenants]->setHuman(u.s(surname), u.s(name), u.s(patronymic), gender, day, month, year);
	
		// меняем buffer на tenants
		if (tenants) delete[] tenants;
		tenants = buffer;
		buffer = nullptr;

		// приводим количество жильцов в соответствие с фактическим
		numTenants++;
	}

	// метод удаления жильца из квартиры
	bool delTenant(size_t numTenant) {
		// конвертируем
		//   numTenant   - человеческий номер  жильца в таблице
		// в indexTenant - компьютерный индекс жильца в массиве
		size_t indexTenant = u.numberToIndex(numTenant);

		// проверка вхождения индекса жильца в разрешенный диапазон
		if ((0 <= indexTenant) && (indexTenant < numTenants)) {

			// создание нового массива жильцов меньшего на 1, чем прежний массив
			size_t newNumTenants = numTenants - 1;

			if (newNumTenants) {

				Human** buffer = new Human * [newNumTenants] { nullptr };

				// проверка на вхождение индекса жильца на вхождение в разрешенный диапазон
				// для копирования жильцов от начала массива до указанного жильца
				if ((0 <= indexTenant) && (indexTenant < numTenants)) {

					for (size_t i = 0; i < indexTenant; i++) {
						buffer[i] = tenants[i];
					}
				}

				// копирование жильцов после указанного жильца
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

	// setter-ы
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

	// getter-ы
	size_t getNumFlat   () { return numFlat   ; }
	size_t getFloor     () { return floor     ; }
	size_t getNumRooms  () { return numRooms  ; }
	size_t getArea      () { return area      ; }
	size_t getHeight    () { return height    ; }
	size_t getNumTenants() { return numTenants; }

	Human** getTenants(                 ) { return tenants            ; }
	Human*  getTenants(size_t numTenants) { return tenants[numTenants]; }

	// печать заголовка таблицы жильцов квартиры
	void headerTenants(size_t numFlat = 0, std::streamsize w_numFlat = 0) {
		cout << setw(3) << "  №  ";
		if (numFlat) {
			cout << setw(w_numFlat) << " Кв.  ";
		}
		h.header();
	}

	// печать данных жильцов квартиры
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

	// печать заголовка для печати данных квартиры в строку
	void headerLine() {
		cout << " Квартира  Этаж  Комнат  Площадь  Высота  Жильцов" << endl;
	}

	// печать данных квартиры в строку
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

	// печать карточки квартиры
	void printCard() {

		cout << "                Карточка квартиры" << endl;
		cout << "                -----------------" << endl;
		cout << "         Номер квартиры: " << getNumFlat   () << endl;
		cout << "                   Этаж: " << getFloor     () << endl;
		cout << "      Количество комнат: " << getNumRooms  () << endl;
		cout << " Площадь квартиры, кв.м: " << getArea      () << endl;
		cout << "    Высота потолков, см: " << getHeight    () << endl;
		cout << "     Количество жильцов: " << getNumTenants() << endl;

		if (getNumTenants()) {
			cout << " -------------------- Жильцы квартиры ----------------------" << endl;
			headerTenants();
			printTenants();
		}
	}
}f;


// КЛАСС Дом
class House {
private:
	Flat** flats = nullptr;       // массив квартир
	size_t numFlats  = 0;         // количество квартир
	size_t numFloors = 0;         // количество этажей
	struct {
		char* country = nullptr;  // страна     - адреса
		char* region  = nullptr;  // область    - адреса
		char* city    = nullptr;  // город      - адреса
		char* street  = nullptr;  // улица      - адреса
		size_t numHouse = 0;      // номер дома - адреса
	}address;                     // адрес
public:
	// конструктор по умолчанию
	House(){}
	// конструктор с параметрами
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

	// конструктор копирования
	House(House& object) { *this = object; }

	// деструктор
	~House() {
		u.deletePointer<Flat**>(flats          );
		u.deletePointer<char* >(address.country);
		u.deletePointer<char* >(address.region );
		u.deletePointer<char* >(address.city   );
		u.deletePointer<char* >(address.street );
	}

	// setter-ы
	void setNumFloors(size_t numFloors) { this->numFloors        = numFloors; }
	void setCountry  (char*  country  ) { this->address.country  = country  ; }
	void setRegion   (char*  region   ) { this->address.region   = region   ; }
	void setCity     (char*  city     ) { this->address.city     = city     ; }
	void setStreet   (char*  street   ) { this->address.street   = street   ; }
	void setNumHouse (size_t numHouse ) { this->address.numHouse = numHouse ; }

	// задание количества квартир в доме
	// и создание массива квартир указанного размера
	void setNunFlats(size_t numFlats) {
		if (this->numFlats != numFlats) {
			this->numFlats = numFlats;
			if (flats) delete[] flats;
			flats = new Flat * [this->numFlats]{ nullptr };
		}
	}

	// задание квартир - без данных, только номер
	void setFlats() {
		// создадим в массиве квартиры и укажем их номера
		if (flats) {
			for (size_t i = 0; i < numFlats; i++) {
				if (!flats[i]) {
					flats[i] = new Flat;
					flats[i]->setNumFlat(u.indexToNumber(i));
				}
			}
		}
	}

	// getter-ы
	size_t getNumFlats () { return this->numFlats        ; }
	size_t getNumFloors() { return this->numFloors       ; }
	char*  getCountry  () { return this->address.country ; }
	char*  getRegion   () { return this->address.region  ; }
	char*  getCity     () { return this->address.city    ; }
	char*  getStreet   () { return this->address.street  ; }
	size_t getNumHouse () { return this->address.numHouse; }

	Flat** getFlats(              ) { return this->flats         ; }
	Flat*  getFlats(size_t numFlat) { return this->flats[numFlat]; }

	// метод печати карточки свойств дома
	void printProperties() {
		cout << "      Карточка дома" << endl;
		cout << "      -------------" << endl;
		cout << " Количество квартир = " << getNumFlats () << endl;
		cout << " Количество этажей  = " << getNumFloors() << endl;
		cout << " Адрес:" << endl;
		cout << "        страна: " << getCountry () << endl;
		cout << "        регион: " << getRegion  () << endl;
		cout << "         город: " << getCity    () << endl;
		cout << "         улица: " << getStreet  () << endl;
		cout << "    номер дома: " << getNumHouse() << endl;
	}

	// метод печати таблицы квартир
	void printFlats() {
		if (flats) {
			cout << "                  Квартиры дома" << endl;
			cout << "                  -------------" << endl;
			f.headerLine();
			for (size_t i = 0; i < this->numFlats; i++) {
				this->flats[i]->printLine();
			}
		}
	}

	// метод печати таблицы жильцов дома
	void printTenants() {
		if (flats) {
			cout << "                           Жильцы дома" << endl;
			cout << "                           -----------" << endl;
			f.headerTenants(1, 4);
			pendl;

			size_t numberTenant = 0;
			// печать жильцов массива квартир
			for (size_t i = 0; i < this->numFlats; i++)	{
				numberTenant = flats[i]->printTenants(numberTenant, u.indexToNumber(i), 4);
			}
		}
	}
};


// ГЛАВНАЯ ФУНКЦИЯ
int main() {
	setlocale(LC_ALL, "ru");

	// создадим объект Дом
	House house(
		9,                     // количество квартир
		5,                     // количество этажей
		u.s("Россия"),         // страна адреса
		u.s("Пермский край"),  // регион адреса
		u.s("Пермь"),          // город адреса
		u.s("Ленина"),         // улица адреса
		1                      // номер дома адреса
	);

	// зададим параметры квартир дома:
	// (№ квартиры)->(этаж, кол-во комнат, площадь(кв.м), высота комнат(см))
	house.getFlats(u.numberToIndex(1))->setFlat(1, 1, 30, 250);
	house.getFlats(u.numberToIndex(2))->setFlat(1, 1, 30, 250);
	house.getFlats(u.numberToIndex(3))->setFlat(2, 1, 30, 250);
	house.getFlats(u.numberToIndex(4))->setFlat(2, 2, 50, 250);
	house.getFlats(u.numberToIndex(5))->setFlat(3, 1, 30, 250);
	house.getFlats(u.numberToIndex(6))->setFlat(3, 2, 50, 250);
	house.getFlats(u.numberToIndex(7))->setFlat(4, 1, 30, 250);
	house.getFlats(u.numberToIndex(8))->setFlat(4, 2, 50, 250);
	house.getFlats(u.numberToIndex(9))->setFlat(5, 3, 80, 350);

	// зададим жильцов дома
	house.getFlats(u.numberToIndex(1))->addTenant("Иванов"    , "Иван"     , "Иванович"     , Human::Gender::MAN  , 14,  5, 1957);
	house.getFlats(u.numberToIndex(1))->addTenant("Иванова"   , "Мария"    , "Викторовна"   , Human::Gender::WOMAN, 22,  3, 1961);
	house.getFlats(u.numberToIndex(2))->addTenant("Филимонов" , "Филимон"  , "Филимонович"  , Human::Gender::MAN  ,  7,  9, 1939);
	house.getFlats(u.numberToIndex(2))->addTenant("Филимонова", "Наталья"  , "Ниловна"      , Human::Gender::WOMAN, 23, 12, 1945);
	house.getFlats(u.numberToIndex(3))->addTenant("Кузнецов"  , "Андрей"   , "Степанович"   , Human::Gender::MAN  ,  1,  7, 1968);
	house.getFlats(u.numberToIndex(3))->addTenant("Кузнецова" , "Светлана" , "Александровна", Human::Gender::WOMAN, 24,  2, 1973);
	house.getFlats(u.numberToIndex(4))->addTenant("Федоров"   , "Николай"  , "Викторович"   , Human::Gender::MAN  , 11,  8, 1985);
	house.getFlats(u.numberToIndex(4))->addTenant("Федорова"  , "Надежда"  , "Ивановна"     , Human::Gender::WOMAN,  3,  4, 1986);
	house.getFlats(u.numberToIndex(4))->addTenant("Федорова"  , "Светлана" , "Николаевна"   , Human::Gender::WOMAN, 16, 12, 2006);
	house.getFlats(u.numberToIndex(4))->addTenant("Федорова"  , "Мария"    , "Николаевна"   , Human::Gender::WOMAN,  8,  6, 2011);
	house.getFlats(u.numberToIndex(5))->addTenant("Сухоруков" , "Виктор"   , "Леонидович"   , Human::Gender::MAN  , 28,  3, 1993);
	house.getFlats(u.numberToIndex(5))->addTenant("Сухорукова", "Оксана"   , "Андреевна"    , Human::Gender::WOMAN,  8,  7, 2001);
	house.getFlats(u.numberToIndex(5))->addTenant("Сухоруков" , "Михаил"   , "Викторович"   , Human::Gender::MAN  , 14, 10, 2018);
	house.getFlats(u.numberToIndex(6))->addTenant("Безруков"  , "Вячеслав" , "Михаилович"   , Human::Gender::MAN  , 21,  5, 1975);
	house.getFlats(u.numberToIndex(6))->addTenant("Безрукова" , "Лидия"    , "Петровна"     , Human::Gender::WOMAN, 19,  2, 1975);
	house.getFlats(u.numberToIndex(6))->addTenant("Безруков"  , "Николай"  , "Вячеславович" , Human::Gender::MAN  , 17,  1, 2004);
	house.getFlats(u.numberToIndex(6))->addTenant("Безруков"  , "Владимир" , "Вячеславович" , Human::Gender::MAN  , 14, 10, 2008);
	house.getFlats(u.numberToIndex(7))->addTenant("Куприянова", "Нина"     , "Станиславовна", Human::Gender::WOMAN,  5,  4, 1988);
	house.getFlats(u.numberToIndex(8))->addTenant("Никонов"   , "Леонид"   , "Андреевич"    , Human::Gender::MAN  ,  4,  3, 1990);
	house.getFlats(u.numberToIndex(8))->addTenant("Никонова"  , "Светлана" , "Викторовна"   , Human::Gender::WOMAN, 29, 12, 1996);
	house.getFlats(u.numberToIndex(8))->addTenant("Никонова"  , "Надежда"  , "Андреевна"    , Human::Gender::WOMAN, 26, 12, 2015);
	house.getFlats(u.numberToIndex(8))->addTenant("Никонова"  , "Татьяна"  , "Андреевна"    , Human::Gender::WOMAN, 26, 12, 2015);
	house.getFlats(u.numberToIndex(9))->addTenant("Бородин"   , "Александр", "Федорович"    , Human::Gender::MAN  ,  6,  7, 1980);
	house.getFlats(u.numberToIndex(9))->addTenant("Бородина"  , "Елена"    , "Леонидовна"   , Human::Gender::WOMAN, 27, 12, 1994);
	house.getFlats(u.numberToIndex(9))->addTenant("Бородин"   , "Виктор"   , "Александрович", Human::Gender::MAN  ,  9, 10, 2019);

	// распечатаем заданные свойства дома (карточку дома)
	house.printProperties();
	pendl;

	// распечатаем таблицу квартир дома
	house.printFlats();
	pendl;

	// распечатаем таблицу жильцов дома
	house.printTenants();
	pendl;

	// распечатаем карточку квартиры №7
	house.getFlats(u.numberToIndex(7))->printCard();
	pendl;

	// изменим фамилию жильца квартиры №7 Куприяновой Н.С.
	cout << " Изменим фамилию жильца квартиры №7 Куприяновой Н.С. на Парамонову" << endl;
	house.getFlats(u.numberToIndex(7))->getTenants()[u.numberToIndex(1)]->setSurname(u.s("Парамонова"));

	// добавим жильца в квартиру №7
	cout << " Добавим в квартиру №7 нового жильца Парамонова А.К." << endl << endl;
	house.getFlats(u.numberToIndex(7))->addTenant("Парамонов", "Алексей", "Карпович", Human::Gender::MAN, 8, 7, 1980);

	// распечатаем карточку квартиры №7
	house.getFlats(u.numberToIndex(7))->printCard();
	pendl;

	// удалим жильца квартиры №7 Парамонова А.К.
	cout << " Удалим из квартиры №7 жильца Парамонова А.К." << endl << endl;
	house.getFlats(u.numberToIndex(7))->delTenant(2);

	// распечатаем карточку квартиры №7
	house.getFlats(u.numberToIndex(7))->printCard();
	pendl;

	// распечатаем таблицу жильцов дома
	house.printTenants();

	return 0;
}