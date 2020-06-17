// Выполнение DZ_1591895550.txt
// Домашнее задание 2 из файла C__urok_02_2020_1589461442.pdf
/*
2.	Разработать класс String, который в дальнейшем будет использоваться для работы со строками.
Класс должен содержать:
  конструктор по умолчанию, позволяющий создать строку длиной 80 символов;
  конструктор, позволяющий создавать строку произвольного размера;
  конструктор, который создаёт строку и инициализирует её строкой, полученной от пользователя.
Класс должен содержать методы для ввода строк с клавиатуры и вывода строк на экран.
*/
#include <iostream>
#include <clocale>
using namespace std;


class String {
private:
	char* line;

	// возврат длины строки инициализации
	size_t lengthString(const char* str) {
		size_t length = 0;
		while (str[length++]);
		return --length;
	}
public:
	// конструктор по умолчанию на строку до 80 символов
	String() {
		this->line = new char[80] { '\0' };
	}
	// конструктор на строку заданного размера
	String(size_t sizeLine) {
		this->line = new char[sizeLine]{ '\0' };
	}
	// конструктор, инициализирующий строку объекта C-строкой пользователя
	String(const char* strInit) {
		setLineConst(strInit);
	}
	// деструктор
	~String() {
		delete[] this->line;
	}
	// метод вывода строки на экран
	void printLine() {
		cout << this->line << endl;
	}
	// метод задания строки объекта C-строкой
	void setLineConst(const char* strInit) {
		// определяем длину инициализирующей строки
		size_t len = lengthString(strInit);
		// выделяем динамическую память под строку объекта
		this->line = new char[len + 1]{ '\0' };
		// копируем в строку объекта строку инициализации
		for (size_t i = 0; i < len; i++) {
			line[i] = strInit[i];
		}
	}
	// метод ввода C-строки пользователя
	const char* inputLine() {
		char line[256]{ '\0' };
		cout << "Введите строку длиной до 255 символов" "\n" "> ";
		cin >> line;
		return line;
	}
};

int main() {
	setlocale(LC_ALL, "ru");

	String str = "ZZZZZZZZZZbbbbbbbbbbccccccccccddddddddddeeeeeeeeeeffffffffffggggggggggXXXXXXXXX";
	str.printLine();
	str.setLineConst("aaaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeffffffffffgggggggggghhhhhhhhh");
	str.printLine();

	return 0;
}