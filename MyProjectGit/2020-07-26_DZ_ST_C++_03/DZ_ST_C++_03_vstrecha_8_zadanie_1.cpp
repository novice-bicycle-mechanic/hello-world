// задание из файла DZ_ST_C++_03.pdf
// Встреча №8
// Тема: Конструктор переноса
// Задание 1.
/*
Добавить в уже существующий класс String конструктор переноса.
*/
// ниже задание по "существующему классу String"
//---------------------------------------------------------------------------
// задание из файла DZ_ST_C++_01.pdf
//
// Тема: Статические переменные-члены и функции-члены,
//       различные способы инициализации
// Встреча 3, задание
/*
    Разработать класс String, который в дальнейшем будет использоваться
для работы со строками.
Класс должен содержать:
• Конструктор по умолчанию, позволяющий создать строку длиной 80 символов;
• Конструктор, позволяющий создавать строку произвольного размера;
• Конструктор, который создаёт строку и инициализирует её строкой,
полученной от пользователя.
    Необходимо создать деструктор, а также использовать механизмы
делегирования конструкторов, если это возможно.
    Класс должен содержать методы для ввода строк с клавиатуры и
вывода строк на экран. Также нужно реализовать статическую
функцию-член, которая будет возвращать количество созданных
объектов строк.
*/
//----------------------------------------------------------------------------
#include <iostream>
#include <clocale>
#include <Windows.h>
#include <iomanip>
#include <conio.h>
using namespace std;


// КЛАСС Строка
class String {
private:
	char* line{ nullptr };

	// МЕТОД возврата длины строки инициализации
	size_t lengthString(const char* str) {
		size_t length = 0;
		while (str[length++]);
		return --length;
	}

	// МЕТОД учета вызовов метода (при аргументе == TRUE - увеличение счетчика)
	static int counter(bool counting = false) {
		static int account{ 0 };
		if (counting) ++account;
		return account;
	}

	// МЕТОД выделения динамической памяти строке line
	void allocatingDynamicMemory(size_t length) {
		line = new char[length + 1]{ '\0' };
		counter(true);
	}

public:

	// КОНСТРУКТОР на строку заданного размера
	String(size_t sizeLine) {
		allocatingDynamicMemory(sizeLine);
		cout << " Вызван конструктор ~String с параметром - длиной строки" << endl;
	}

	// КОНСТРУКТОР по умолчанию на строку до 80 символов !!! с делегированием конструктора !!!
	String() : String(80) {
		cout
			<< " Вызван конструктор ~String по умолчанию - с длиной строки 80"
			<< " и делегированием конструктору с параметром" << endl;
	}

	// КОНСТРУКТОР, инициализирующий строку объекта C-строкой пользователя
	String(const char* strInit) {
		setLineConst(strInit);
		cout << " Вызван конструктор ~String с инициализацией С-строкой" << endl;
	}



	// ДЕСТРУКТОР
	~String() {
		if (this->line) {
			delete[] this->line;
			cout << " Вызван деструктор ~String" << endl;
		}
	}

	// МЕТОД вывода строки на экран
	void printLine() {
		cout << this->line << endl;
	}

	// МЕТОД задания строки объекта C-строкой
	void setLineConst(const char* strInit) {
		// определяем длину инициализирующей строки
		size_t len = lengthString(strInit);
		// выделяем динамическую память под строку объекта
		allocatingDynamicMemory(len);
		// копируем в строку объекта строку инициализации
		for (size_t i = 0; i < len; i++) {
			line[i] = strInit[i];
		}
	}

	static String inputString() {
		String str;
//		char line[81]{ '\0' };
		cout << "Введите строку длиной до 80 символов" "\n" "> ";
		cin >> str.line;
		return str;
	}


	// МЕТОД ввода C-строки пользователя
	void inputLine() {
		char line[81]{ '\0' };
		cout << "Введите строку длиной до 80 символов" "\n" "> ";
		cin >> line;
	}

	// МЕТОД демонстрации количества созданных объектов-строк
	int showNumberLine() {
		return counter();
	}

	// МЕТОД присвоения значения элементу строки line
	void setItemLine(size_t index, char symbol) {
		line[index] = symbol;
	}


	//----------------------------------------------------------------------

	// КОНСТРУКТОР переноса (перемещения)
	String(String&& str) noexcept :line(nullptr) {               // <--- конструктор переноса !!!
		cout << " Вызван конструктор переноса" << endl;
		line = str.line;
		str.line = nullptr;
	}

	//----------------------------------------------------------------------


};
// КОНЕЦ КЛАССА Строка


// ГЛАВНАЯ ФУНКЦИЯ
int main() {
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	String str1;
	cout
		<< " Создана строка №"
		<< str1.showNumberLine()
		<< " конструктором по умолчанию и заполнена символами:"
		<< endl;
	for (size_t i = 0, j = 33; i < 80; i++, j++) {
		str1.setItemLine(i, (char)j);
	}
	str1.printLine();
	cout << "--------------------------------------------------------------------------------" << endl;

	String str2(40);
	cout
		<< " Создана строка №"
		<< str2.showNumberLine()
		<< " длиной 40 конструктором с параметром и заполнена символами:"
		<< endl;
	for (size_t i = 0, j = 33; i < 40; i++, j++) {
		str2.setItemLine(i, (char)j);
	}
	str2.printLine();
	cout << "--------------------------------------------------------------------------------" << endl;

	String str3 = "ZZZZZZZZZZbbbbbbbbbbccccccccccddddddddddeeeeeeeeeeffffffffffggggggggggXXXXXXXXX";
	cout << " Создана строка №" << str3.showNumberLine() << " с присвоением С-строки:" << endl;
	str3.printLine();
	cout << "--------------------------------------------------------------------------------" << endl;

	String str4("aaaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeffffffffffgggggggggghhhhhhhhh");
	cout << " Создана строка №" << str4.showNumberLine() << " с инициализацией С-строкой:" << endl;
	str4.printLine();
	cout << "--------------------------------------------------------------------------------" << endl;
/*
	char stringUser[80]{ '\0' };
	char symbol{ '\0' };
	cout << " Введите строку длиной до 79 символов \n>";

	for (size_t i = 0; i < 79; i++) {
		symbol = _getch();
		if (symbol == 13) break;
		stringUser[i] = symbol;
		cout << symbol;
	}
	cout << endl;

	String str5(stringUser);
	cout << " Создана строка №" << str5.showNumberLine() << " с инициализацией С-строкой пользователя:" << endl;
	str5.printLine();
	cout << "--------------------------------------------------------------------------------" << endl;
*/
	//------------------------------------------------------------------

	// Пример применения Конструктора переноса (перемещения)
	// создадим строку
	
	String b = String::inputString();

	b.printLine();

	//------------------------------------------------------------------

	return 0;
}
// КОНЕЦ ГЛАВНОЙ ФУНКЦИИ
