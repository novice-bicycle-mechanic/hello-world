// задание из файла problemy_1592453914.txt
// файл Lab_C++_week_1.pdf, Встреча 2, задание 1
/*
    К уже реализованному классу Точка добавьте необходимые
конструкторы, сделайте ряд функций inline, используйте
инициализаторы.

(Файл Lab_C++_week_1.pdf, Встреча 1, задание 2:
Реализуйте класс “Точка”. Необходимо хранить координаты
x, y, z в переменных-членах класса. Реализуйте функции-члены
класса для ввода данных, вывода данных, реализуйте аксессоры
для доступа к переменным-членам, реализуйте сохранение в
файл и загрузку данных из файла.)
*/
#include <iostream>
#include <clocale>
#include <stdio.h>

using namespace std;

// СТРУКТУРА Атрибутов файла
struct FileAttribute {
	const char* name = "";    // наименование файла
	FILE* data = nullptr;     // указатель на файл
	FILE** ptrData = &data;   // указатель на указатель на файл
};
// КОНЕЦ СТРУКТУРЫ Атрибутов файла


// КЛАСС Точка
class Point {
private:
	int x{};
	int y{};
	int z{};
public:
	// КОНСТРУКТОР по умолчанию
	Point(){}

	// КОНСТРУКТОР с параметрами
	Point(int x, int y, int z) { setXYZ(x, y, z); }

	// КОНСТРУКТОР копирования
	Point(Point& object) { *this = object; }

	// GETTER-ы
	inline int getX() { return x; }
	inline int getY() { return y; }
	inline int getZ() { return z; }

	// SETTER-ы
	inline void setX(int x) { this->x = x;	}
	inline void setY(int y) { this->y = y; }
	inline void setZ(int z) { this->z = z; }
	inline void setXYZ(int x, int y, int z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	// МЕТОД ввода точки с консоли
	inline void input() {
		cout << " Введите координаты точки (через пробелы: x y z): ";
		cin >> this->x >> this->y >> this->z;
	}

	// МЕТОД печати координат точки на экране
	inline void print() {
		cout
			<< " x = " << this->x << ", y = " << this->y << ", z = " << this->z << endl;
	}

	// МЕТОД загрузки координат точки из текстового файла
	void upload(const char* nameFile) {

		FileAttribute point;
		point.name = nameFile;

		// откроем файл или проверим наличие файла
		if (fopen_s(point.ptrData, point.name, "r")) {
			printf_s(" Файл %s отсутствует\n", nameFile);
		}
		else {    // ниже - если файл открылся
			char* line = nullptr;
			char* contex = nullptr;
			char** ptrcontex = &contex;
			size_t lenLine = 256;
			line = new char[lenLine] { '\0' };

			if (fgets(line, lenLine, point.data)) {
				contex = line;
				this->x = atoi(strtok_s(contex, ",", ptrcontex));
				this->y = atoi(strtok_s(contex, ",", ptrcontex));
				this->z = atoi(strtok_s(contex, "\n", ptrcontex));
			}

			delete[] line;
			line = nullptr;
			contex = nullptr;

			fclose(point.data);
		}
	}

	// МЕТОД записи координат точки в текстовый файл
	void write(const char* nameFile) {
		FileAttribute point;
		point.name = nameFile;
		fopen_s(point.ptrData, point.name, "w");
		fprintf_s(point.data, "%d,%d,%d%c",	this->x, this->y, this->z, '\x0a');
		fclose(point.data);
	}
};
// КОНЕЦ КЛАССА Точка


// ГЛАВНАЯ ФУНКЦИЯ
int main() {
	setlocale(LC_ALL, "ru");

	Point point{ 1, 2, 3 };
	cout << " Задано при объявлении точки:";
	point.print();
	cout << " -----------------------------------------------------------------" << endl;

	point.input();
	cout << " Задано при вводе точки с экрана:";
	point.print();
	cout << " -----------------------------------------------------------------" << endl;

	cout << " Задано автоматически: x=12 y=14 z=16.\n Проверка:";
	point.setXYZ(12, 14, 16);
	point.print();

	cout << " Координаты точки записаны в файл point.txt" << endl;
	point.write("point.txt");
	cout << " -----------------------------------------------------------------" << endl;

	cout << " Задано автоматически: x=5. Проверка: ";
	point.setX(5);
	cout << point.getX() << endl;

	cout << " Задано автоматически: y=7. Проверка: ";
	point.setY(7);
	cout << point.getY() << endl;

	cout << " Задано автоматически: z=9. Проверка: ";
	point.setZ(9);
	cout << point.getZ() << endl;

	cout << " Проверка:";
	point.print();
	cout << " -----------------------------------------------------------------" << endl;

	cout << " Координаты точки загружены из файла point.txt" << endl;
	point.upload("point.txt");

	cout << " Проверка:";
	point.print();
	cout << " -----------------------------------------------------------------" << endl;

	return 0;
}
// КОНЕЦ ГЛАВНОЙ ФУНКЦИИ















