// задание из файла DZ_ST_C++_02.pdf
// Встреча №5
// Тема: Константная функция-член, explicit конструктор.
// Задание.
/*
Разработать класс Reservoir (водоем).
Класс должен обязательно иметь поле «название».
Класс должен содержать:
конструктор по умолчанию,
конструктор с параметрами,
при необходимости реализовать деструктор и конструктор копирования.
Добавить методы для:
1. Определения приблизительного объема (ширина*длина*максимальная глубина);
2. Определения площади водной поверхности;
3. Метод для проверки относятся ли водоемы к одному типу (море-море; бассейн-пруд);
4. Для сравнения площади водной поверхности водоемов одного типа;
5. Для копирования объектов;
6. Остальные методы на усмотрение разработчика (методы set и get).
Написать интерфейс для работы с классом.
Реализовать динамический массив объектов класса с возможностью
добавления, удаления объектов из массива.
Реализовать возможность записи информации об объектах массива
в текстовый файл, бинарный файл.
Используйте explicit конструктор и константные функции-члены
(например, для отображения данных о водоёме и т.д.).
*/
#include <iostream>
#include <clocale>
#include <iomanip>
#include <stdio.h>

using namespace std;

#define pendl cout << endl;


// СТРУКТУРА атрибутов файла
struct FileAttribute {
	const char* name = "";    // наименование файла
	FILE* data = nullptr;     // указатель на файл
	FILE** ptrData = &data;   // указатель на указатель на файл
};
// КОНЕЦ СТРУКТУРЫ


// КЛАСС Утилиты
class Utilities {
public:
	// МЕТОД удаления динамической памяти принадлежащей указателю
	template <typename T>
	void deletePointer(T& pointer) {
		if (pointer) {
			delete[] pointer;
			pointer = nullptr;
		}
	}
	// МЕТОД возврата строки string оптимизированной длины и типа char*
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
	// МЕТОД возврата индекса массива из номера объекта в таблице
	size_t indexFromNumber(size_t number) {
		if (number > 0) return --number;
		else return 0;
	}
	// МЕТОД возврата номера объекта в таблице из индекса в массиве
	size_t numberFromIndex(size_t index) {
		return ++index;
	}
}u;
// КОНЕЦ КЛАССА


// КЛАСС-интерфейс ИВодоем
class IReservoir {
	// чистая виртуальная функция определения объема
	virtual int volume() = 0;
	// чистая виртуальная функция определения площади
	virtual int area() = 0;
};
// КОНЕЦ КЛАССА


// КЛАСС Водоем
class Reservoir : public IReservoir {
public:
	//           тип водоема:  нет__ бассейн пруд_ озеро болото
	//                      :  NONE  POOL    POND  LAKE  SWAMP
	enum class TypeReservoir { NONE, POOL,   POND, LAKE, SWAMP };

	// оценка площади водоемов одного типа
	//                      оценка: нет___ разные_типы равны  больше меньше
	//                    _________ NONE_ DIFFERENT__ EQUAL  MORE__ LESS  
	enum class CompareAreaSameType { NONE, DIFFERENT, EQUAL, MORE, LESS };

private:
	char* name = nullptr;  // название водоема
	int length = 0;        // длина водоема
	int width  = 0;        // ширина водоема
	int depth  = 0;        // глубина водоема
	TypeReservoir type = TypeReservoir::NONE;  // тип водоема

	// переменные ширины поля для печати значений
	std::streamsize w_name   = 16;
	std::streamsize w_length = 8;
	std::streamsize w_width  = 8;
	std::streamsize w_depth  = 8;
	std::streamsize w_type   = 8;
	std::streamsize w_volume = 9;
	std::streamsize w_area   = 9;

	// человеческие наименования enum-ов
	const char* typeNames[5] { "нет","бассейн","пруд","озеро","болото" };
	const char* compareNames[5]{ "нет","отличается по типу от","равны","больше","меньше" };

public:
	// КОНСТРУКТОР по умолчанию
	Reservoir(){}
	// КОНСТРУКТОР с параметрами
	template <typename T>
	explicit Reservoir(                   //     <-----    explicit    !!!
		T             name  ,
		int           length,
		int           width ,
		int           depth ,
		TypeReservoir type
	) {
		setName  (u.s(name));
		setLength(length   );
		setWidth (width    );
		setDepth (depth    );
		setType  (type     );
	}
	// КОНСТРУКТОР копирования
	Reservoir(Reservoir& object) { *this = object; }
	// ДЕСТРУКТОР
	~Reservoir() {
		u.deletePointer<char*>(this->name);
	}

	// МЕТОД расчета объема водоема
	int volume() {
		return length * width * depth;
	}
	
	// МЕТОД расчета площади водоема
	int area() {
		return length * width;
	}

	// МЕТОД сравнения типов водоемов
	//       - владельца метода с тем, что в аргументе (скобках)
	bool compareType(TypeReservoir type2) {
		if (getType() == type2) return true;
		else return false;
	}

	// МЕТОД сравнения площадей водоемов одного типа
	//       - владельца метода с тем, что в аргументе (скобках)
	CompareAreaSameType compareAreaSameType(Reservoir& reservoir2) {
		if (this->type == reservoir2.type) {
			if      (this->area() > reservoir2.area()) return CompareAreaSameType::MORE ;
			else if (this->area() < reservoir2.area()) return CompareAreaSameType::LESS ;
			else                                       return CompareAreaSameType::EQUAL;
		}
		else return CompareAreaSameType::DIFFERENT;
	}

	// МЕТОД копирования объекта
	void copy(Reservoir& reservoir2) {
		reservoir2.setName  (this->name  );
		reservoir2.setLength(this->length);
		reservoir2.setWidth (this->width );
		reservoir2.setDepth (this->depth );
		reservoir2.setType  (this->type  );
	}

	// SETTER-ы
	void setName  (char*         name  ) { this->name   = name  ; }
	void setLength(int           length) { this->length = length; }
	void setWidth (int           width ) { this->width  = width ; }
	void setDepth (int           depth ) { this->depth  = depth ; }
	void setType  (TypeReservoir type  ) { this->type   = type  ; }

	template <typename T>
	void setReservoir(
		T             name  ,
		int           length,
		int           width ,
		int           depth ,
		TypeReservoir type
	) {
		setName  (u.s(name));
		setLength(length   );
		setWidth (width    );
		setDepth (depth    );
		setType  (type     );
	}

	// GETTER-ы         !!! КОСТАНТНЫЕ !!!
	char*         getName  () const { return this->name  ; }
	int           getLength() const { return this->length; }
	int           getWidth () const { return this->width ; }
	int           getDepth () const { return this->depth ; }
	TypeReservoir getType  () const { return this->type  ; }

	// МЕТОД вывода наименования типа водоема
	const char* getTypeNames(TypeReservoir type) {
		return typeNames[(size_t)type];
	}

	// МЕТОД вывод наименования сравнения площадей
	//       водоемов одинакового типов
	const char* getCompareAreaNames(CompareAreaSameType compareArea) {
		return compareNames[(size_t)compareArea];
	}

	// МЕТОД печати заголовка строки данных водоема
	void header() {
		cout 
			<< setw(0) << " "
			<< setw(w_name-1 ) << left  << "Наименование"
			<< setw(w_length ) << right << "Длина"
			<< setw(w_width+1) << right << "Ширина"
			<< setw(w_depth  ) << right << "Глубина"
			<< "  "
			<< setw(w_type+1 ) << left  << "Тип"
			<< setw(w_volume ) << left  << "Объем"
			<< setw(w_area   ) << left  << "Площадь"
			<< endl;
	}

	// МЕТОД печати водоема на экран в строку
	void print() {
		cout
			<< setw(w_name  ) << left  << name
			<< setw(w_length) << right << length
			<< setw(w_width ) << right << width
			<< setw(w_depth ) << right << depth
			<< "  "
			<< setw(w_type  ) << left  << getTypeNames(type)
			<< setw(w_volume) << right << volume()
			<< setw(w_area  ) << right << area()
			<< endl;
	}
}r;
// КОНЕЦ КЛАССА


// КЛАСС Каталог водоемов (он же массив водоемов с методами)
class CatalogOfReservoirs {
private:
	size_t numReservoirs = 0;          // количество водоемов
	Reservoir** reservoirs = nullptr;  // массив водоемов
public:
	// КОНСТРУКТОР по умолчанию
	CatalogOfReservoirs(){}

	// ДЕСТРУКТОР
	~CatalogOfReservoirs() {
		u.deletePointer(reservoirs);
	}

	// МЕТОД добавления водоема в каталог
	template <typename T>
	void addReservoir(
		T name,
		int length,
		int width,
		int depth,
		Reservoir::TypeReservoir type
	) {
		// создаем новый, увеличенный на 1, массив buffer объектов-водоемов
		Reservoir** buffer = new Reservoir * [(numReservoirs + 1)]{ nullptr };

		// копируем reservoirs в buffer
		if (reservoirs) {
			for (size_t i = 0; i < numReservoirs; i++) {
				buffer[i] = reservoirs[i];
			}
		}
		// добавляем в массив buffer объект-водоем
		buffer[numReservoirs] = new Reservoir;
		buffer[numReservoirs]->setReservoir(u.s(name), length, width, depth, type);

		// меняем buffer на tenants
		if (reservoirs) delete[] reservoirs;
		reservoirs = buffer;
		buffer = nullptr;

		// приводим количество водоемов в соответствие с фактическим
		numReservoirs++;
	}

	// МЕТОД удаления водоема из каталога
	bool delReservoir(size_t numReservoir) {
		// конвертируем
		//   numReservoir   - человеческий номер  водоема в таблице
		// в indexReservoir - компьютерный индекс водоема в массиве
		size_t indexReservoir = u.indexFromNumber(numReservoir);

		// проверка вхождения индекса водоема в разрешенный диапазон
		if ((0 <= indexReservoir) && (indexReservoir < numReservoir)) {

			// создание нового массива водоемов меньшего на 1, чем прежний массив
			size_t newNumReservoirs = numReservoirs - 1;
			if (newNumReservoirs) {
				Reservoir** buffer = new Reservoir * [newNumReservoirs] { nullptr };

				// проверка на вхождение индекса водоема на вхождение в разрешенный диапазон
				// для копирования водоемов от начала массива до указанного водоема
				if ((0 <= indexReservoir) && (indexReservoir < numReservoir)) {

					for (size_t i = 0; i < indexReservoir; i++) {
						buffer[i] = reservoirs[i];
					}
				}

				// копирование водоемов после указанного водоема
				size_t newMinItem = indexReservoir + 1;
				for (size_t i = indexReservoir, j = newMinItem; i < newNumReservoirs; i++, j++) {
					buffer[i] = reservoirs[j];
				}
				delete[] reservoirs;
				reservoirs = buffer;
				buffer = nullptr;
				numReservoirs = newNumReservoirs;
				return true;
			}
			else {
				delete[] reservoirs;
				reservoirs = nullptr;
				numReservoirs = newNumReservoirs;
				return true;
			}
		}
		else return false;
	}

	// GETTER-ы
	Reservoir** getReservoirs(                   ) { return reservoirs              ; }
	Reservoir*  getReservoirs(size_t numReservoir) { return reservoirs[numReservoir]; }

	// МЕТОД печати заголовка каталога водоемов
	void header() {
		cout << "  №  ";
		r.header();
		cout << endl;
	}

	// МЕТОД печати массива на экран
	void print() {
		header();

		if (reservoirs) {
			for (size_t i = 0; i < numReservoirs; i++) {
				cout << setw(3) << right << u.numberFromIndex(i) << "  ";
				getReservoirs(i)->print();
			}
		}
	}

	// МЕТОД записи массива/каталога водоемов в текстовый файл
	void write(const char* nameFile) {
		FileAttribute catalog;
		catalog.name = nameFile;
		fopen_s(catalog.ptrData, catalog.name, "wt");
		for (size_t i = 0; i < numReservoirs; i++) {
			fprintf_s(
				catalog.data,
				"%s,%d,%d,%d,%d%c",
				reservoirs[i]->getName(),
				reservoirs[i]->getLength(),
				reservoirs[i]->getWidth(),
				reservoirs[i]->getDepth(),
				(int)reservoirs[i]->getType(),
				'\x0a'
			);
		}
		fclose(catalog.data);
	}


	// МЕТОД записи массива/каталога водоемов в бинарный файл
	void writeBin(const char* nameFile) {
		FileAttribute catalog;
		catalog.name = nameFile;
		fopen_s(catalog.ptrData, catalog.name, "wb");
		for (size_t i = 0; i < numReservoirs; i++) {
			fprintf_s(
				catalog.data,
				"%s,%d,%d,%d,%d%c",
				reservoirs[i]->getName(),
				reservoirs[i]->getLength(),
				reservoirs[i]->getWidth(),
				reservoirs[i]->getDepth(),
				(int)reservoirs[i]->getType(),
				';'
			);
		}
		fclose(catalog.data);
	}


	// МЕТОД загрузки массива/каталога водоемов из текстового файла
	void upload(const char* nameFile) {

		FileAttribute catalog;
		catalog.name = nameFile;

		// откроем файл или проверим наличие файла
		if (fopen_s(catalog.ptrData, catalog.name, "rt")) {
			printf_s(" Файл %s отсутствует\n", nameFile);
		}
		else {    // ниже - если файл открылся
			char* line = nullptr;
			char* contex = nullptr;
			char** ptrcontex = &contex;
			size_t lenLine = 256;

			u.deletePointer(reservoirs);
			numReservoirs = 0;

			while (true) {
				line = new char[lenLine] { '\0' };
	
				if (fgets(line, lenLine, catalog.data)) {
					contex = line;
					char* name = strtok_s(contex, ",", ptrcontex);
					size_t length = atoi(strtok_s(contex, ",", ptrcontex));
					size_t width  = atoi(strtok_s(contex, ",", ptrcontex));
					size_t depth  = atoi(strtok_s(contex, ",", ptrcontex));
					Reservoir::TypeReservoir type =
						(Reservoir::TypeReservoir)atoi(strtok_s(contex, "\n", ptrcontex));
					this->addReservoir(u.s(name), length, width, depth, type);
				}
				else {
					delete[] line;
					line = nullptr;
					contex = nullptr;
					break;
				}
			}
			fclose(catalog.data);
		}
	}


	// МЕТОД загрузки массива/каталога водоемов из бинарного файла
	void uploadBin(const char* nameFile) {

		FileAttribute catalog;
		catalog.name = nameFile;

		// откроем файл или проверим наличие файла
		if (fopen_s(catalog.ptrData, catalog.name, "rb")) {
			printf_s(" Файл %s отсутствует\n", nameFile);
		}
		else {    // ниже - если файл открылся

			size_t lenBuffer = 0;
			while (fgetc(catalog.data) != EOF) ++lenBuffer;
			char* buffer = new char[lenBuffer + 1]{ '\0' };

			fseek(catalog.data, 0, SEEK_SET);
			for (size_t i = 0; i < lenBuffer; i++) {
				buffer[i] = (char)fgetc(catalog.data);
			}

			fclose(catalog.data);

			char* contexBuffer = nullptr;
			char** ptrcontexBuffer = &contexBuffer;

			char* line = nullptr;
			char* contex = nullptr;
			char** ptrcontex = &contex;

			u.deletePointer(reservoirs);
			numReservoirs = 0;

			contexBuffer = buffer;

			while (true) {

				line = strtok_s(contexBuffer, ";", ptrcontexBuffer);
				if (!line) break;
				contex = line;

				char* name = strtok_s(contex, ",", ptrcontex);
				size_t length = atoi(strtok_s(contex, ",", ptrcontex));
				size_t width  = atoi(strtok_s(contex, ",", ptrcontex));
				size_t depth  = atoi(strtok_s(contex, ",", ptrcontex));
				Reservoir::TypeReservoir type =
					(Reservoir::TypeReservoir)atoi(strtok_s(contex, ";", ptrcontex));

				this->addReservoir(u.s(name), length, width, depth, type);
			}

			if (buffer) delete[] buffer;
			buffer = nullptr;
			contexBuffer = nullptr;

			if (line) delete[] line;
			line = nullptr;
			contex = nullptr;
		}
	}
};
// КОНЕЦ КЛАССА


// ФУНКЦИЯ сравнения площадей водоемов одного типа
void compareAreasSameType(
	CatalogOfReservoirs& catalog,
	size_t numReservoir1,
	size_t numReservoir2
) {
	cout
	<< " Сравним площади водоёмов №" << numReservoir1 << " и №" << numReservoir2 << "\n"
	<< " Водоём \""
	<< catalog.getReservoirs(u.indexFromNumber(numReservoir1))->getName()
	<< "\" "
	<< r.getCompareAreaNames(
		catalog.getReservoirs(u.indexFromNumber(numReservoir1))->compareAreaSameType(
			*catalog.getReservoirs(u.indexFromNumber(numReservoir2))
		)
	)
	<< " водоёма \""
	<< catalog.getReservoirs(u.indexFromNumber(numReservoir2))->getName()
	<< "\""
	<< endl;
}
// КОНЕЦ ФУНКЦИИ


// ФУНКЦИЯ сравнения типов водоемов
void compareTypes(
	CatalogOfReservoirs& catalog,
	size_t numReservoir1,
	size_t numReservoir2
) {
	cout
		<< " Тип водоёма №" << numReservoir1 << " - "
		<< r.getTypeNames(catalog.getReservoirs(u.indexFromNumber(numReservoir1))->getType())
		<< "\n"
		<< " Тип водоёма №" << numReservoir2 << " - "
		<< r.getTypeNames(catalog.getReservoirs(u.indexFromNumber(numReservoir2))->getType())
		<< endl;

	cout
		<< " Сравнение типов водоёмов №" << numReservoir1 << " и №" << numReservoir2 << ": "
		<< (catalog.getReservoirs(u.indexFromNumber(numReservoir1))->compareType(
			catalog.getReservoirs(u.indexFromNumber(numReservoir2))->getType()) ?
			"типы одинаковые" : "типы не одинаковые")
		<< endl;
}
// КОНЕЦ ФУНКЦИИ


// ГЛАВНАЯ ФУНКЦИЯ
int main() {
	setlocale(LC_ALL, "ru");

	// создадим объект Каталог водоемов
	CatalogOfReservoirs catalog;

	// заполним каталог объектами-водоемами
	catalog.addReservoir("Малое озеро"     ,  100,  10,  4, Reservoir::TypeReservoir::LAKE );
	catalog.addReservoir("Большое озеро"   , 2000, 500, 10, Reservoir::TypeReservoir::LAKE );
	catalog.addReservoir("Заводской пруд"  ,  200, 150,  4, Reservoir::TypeReservoir::POND );
	catalog.addReservoir("Мельничный пруд" ,  100,  20,  5, Reservoir::TypeReservoir::POND );
	catalog.addReservoir("Школьный бассейн",   25,  10,  2, Reservoir::TypeReservoir::POOL );
	catalog.addReservoir("Черное болото"   , 1000,1000,  8, Reservoir::TypeReservoir::SWAMP);

	// Заголовок экрана
	cout << "                  Операции с массивом-каталогом водоёмов" << endl;
	cout << "                  --------------------------------------" << endl;

	// печать таблицы водоемов
	catalog.print();
	pendl;

	// запишем каталог водоемов в текстовый файл
	cout << " Запишем каталог водоёмов в текстовый файл \"catalogReservoirs.txt\"" << endl;
	catalog.write("catalogReservoirs.txt");
	pendl;

	// сравнение типов водоемов №3 и №4
	compareTypes(catalog, 3, 4);
	pendl;

	// сравнение типов водоемов №1 и №4
	compareTypes(catalog, 1, 4);
	pendl;

	// сравнение площади водоемов одного типа
	compareAreasSameType(catalog, 1, 2);
	pendl;

	// сравнение площади водоемов разных типов
	compareAreasSameType(catalog, 5, 2);
	pendl;

	// копируем содержание водоема №1 в новый водоем №7
	cout << " Копируем содержание водоёма №1 в новый водоём №7" << endl;
	catalog.addReservoir("Черное болото", 1000, 1000, 8, Reservoir::TypeReservoir::SWAMP);
	catalog.getReservoirs(u.indexFromNumber(1))->copy(
		*catalog.getReservoirs(u.indexFromNumber(7))
	);
	pendl;

	// печать таблицы водоемов
	catalog.print();
	pendl;

	// запишем каталог водоемов в бинарный файл
	cout << " Запишем каталог водоёмов в бинарный файл \"catalogReservoirsBin.bin\"" << endl;
	catalog.writeBin("catalogReservoirsBin.bin");
	pendl;

	// загружаем каталог водоемов из текстового файла
	cout << " Загрузим каталог водоёмов из текстового файла \"catalogReservoirs.txt\"" << endl;
	catalog.upload("catalogReservoirs.txt");
	pendl;

	// печать таблицы водоемов
	catalog.print();
	pendl;

	// удалим запись водоема №4 из каталога
	cout << " Удалим запись водоёма №4 из каталога" << endl;
	pendl;
	catalog.delReservoir(4);

	// печать таблицы водоемов
	catalog.print();
	pendl;

	// загружаем каталог водоемов из бинарного файла
	cout << " Загрузим каталог водоёмов из бинарного файла \"catalogReservoirsBin.bin\"" << endl;
	catalog.uploadBin("catalogReservoirsBin.bin");
	pendl;

	// печать таблицы водоемов
	catalog.print();
	pendl;

	return 0;
}
// КОНЕЦ ГЛАВНОЙ ФУНКЦИИ
















