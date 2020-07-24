// задание 1 из файла Domasnee_zadanie_1594661480.txt
// Выполните домашние задания после уроков 3, 4, 5
// Урок 3. Задание 2
/*
Добавить в строковый класс функцию, которая создает строку,
содержащую пересечение двух строк, то есть общие символы для двух строк.
Например, результатом пересечения строк «sdqcg» «rgfas34» будет строка «sg».
Для реализации функции перегрузить оператор * (бинарное умножение).
*/
#include <iostream>
#include <clocale>
using namespace std;


// КЛАСС Строка
class String {
private:
	char* line{ nullptr };
	size_t lenLine{ 0 };

	// используется в методе перегрузки оператора []
	// для возврата корректного значения при неправильном индексе
	char zero[1]{ '\0' };

	// МЕТОД возврата длины строки инициализации
	size_t lengthString(const char* str) {
		size_t length = 0;
		while (str[length++]);
		--length;
		lenLine = length;
		return length;
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
		lenLine = length;
		counter(true);
	}

public:

	// КОНСТРУКТОР на строку заданного размера
	String(size_t sizeLine) {
		allocatingDynamicMemory(sizeLine);
		cout << " Вызван конструктор String с параметром - длиной строки - " << sizeLine << endl;
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
		cout << " Вызван конструктор String с инициализацией С-строкой" << endl;
	}

	// КОНСТРУКТОР переноса (перемещения)
	String(String&& str) noexcept :line(nullptr) {
		cout << " Вызван конструктор переноса" << endl;
		line = str.line;
		str.line = nullptr;
		lenLine = lengthString((const char*)line);
	}

	// ДЕСТРУКТОР
	~String() {
		if (line) {
			cout << " Вызван деструктор ~String" << endl;
			delete[] line;
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

	// МЕТОД ввода строки с клавиатуры
	static String inputString() {
		String str;
		cout << "Введите строку длиной до 80 символов" "\n" "> ";
		cin >> str.line;
		return str;
	}

	// МЕТОД ввода C-строки пользователя
	void inputLine() {
		char line[81]{ '\0' };
		cout << "Введите строку длиной до 80 символов" "\n" "> ";
		cin >> line;
		lenLine = lengthString((const char*)line);
	}

	// МЕТОД демонстрации количества созданных объектов-строк
	int showNumberLine() {
		return counter();
	}

	// МЕТОД присвоения значения элементу строки line
	void setItemLine(size_t index, char symbol) {
		line[index] = symbol;
	}

	// метод перегрузки оператора индексации [] 
	const char& operator[](const size_t index) const {
		if ((0 <= index) && (index <= lenLine))	return line[index];
		else return zero[0];
	}

	// метод перегрузки оператора вызова функции ()
	int operator()(const char& symbol) const {
		for (size_t i = 0; i < lenLine; i++) {
			if (symbol == line[i]) return i;
		}
		return -1;
	}

	// метод перегрузки операции преобразования значения типа String
	// в тип int - возвращает длину строки
	operator int() {
		return (int)lenLine;
	}

	// метод для демонстрации перегрузки операции преобразования типа в int
	static void printInt(int value) { cout << value << endl; }

	// прототип дружественной функции вывода объекта на консоль оператором <<
	friend std::ostream& operator<<(std::ostream& out, const String& str);

	// прототип дружественной функции пересечения строк оператором *
	friend String operator*(const String& str1, const String& str2);
};
// КОНЕЦ КЛАССА Строка


// Дружественная ФУНКЦИЯ вывода объекта на консоль оператором <<
std::ostream& operator<<(std::ostream& out, const String& str) {
	out << str.line;
	return out;
}


// Дружественная ФУНКЦИЯ пересечения строк оператором *
String operator*(const String& str1, const String& str2) {

	// создадим строку 3 хранящую результат пересечения строк
	String str3(str1.lenLine);
	str3.lenLine = 0;

	// ключ на переход к сравнению с символами строки 2
	bool str2_b{ false }; 

	// перебор символов строки 1
	for (size_t i = 0; i < str1.lenLine; i++)
	{
		str2_b = false;

		// перебор символов строки 3
		for (size_t j = 0; j < str1.lenLine; j++)
		{
			// если текущий символ строки 3 не равен '\0',
			// иначе выход из цикла с str2_b = true
			// - текущий символ строки 1 ранее не встречался в строке 2
			// (значит строка 3 закончилась)

			// сравниваем его с текущим символом строки 1,
			// если они равны - выход из цикла с str2_b = false
			// - переход к следующему символу строки 1
			// (значит текущий символ строки 1 уже встречался в обоих строках)

			if (str3.line[j]) {
				if (str3.line[j] == str1.line[i]) {
					str2_b = false;
					break;
				}
			}
			else {
				str2_b = true;
				break;
			}

			// если str2_b = true - выход из цикла перебора символов строки 3
			// - переход к перебору символов строки 2
			if (str2_b) break;
		}

		// переход к сравнению текущего символа строки 1 с символами строки 2
		if (str2_b) {

			// перебор символов строки 2
			for (size_t k = 0; k < str2.lenLine; k++)
			{
				// если символ строки 2 равен символу строки 1
				// - поместить символ строки 1 в позицию текущей длины строки 3,
				// увеличить длину строки 3 на 1
				// и выйти из цикла перебора символов строки 2
				// для перехода к следующему символу строки 1
				if (str2.line[k] == str1.line[i]) {
					str3.line[str3.lenLine] = str1.line[i];
					++str3.lenLine;
					str2_b = false;
					break;
				}
			}
		}
	}

	return str3;
}


// ГЛАВНАЯ ФУНКЦИЯ
int main() {
	setlocale(LC_ALL, "ru");

	// создадим строку 1
	String str1("красиво жить не запретишь");
	cout << "    Создана Строка 1: " << str1 << endl;
	cout << endl;

	// создадим строку 2
	String str2("красота спасет мир");
	cout << "    Создана Строка 2: " << str2 << endl;
	cout << endl;

	// найдем пересечение строк
	String str3 = str1 * str2;
	cout << "    Создана Строка 3 = Строка 1 * Строка 2 >>> " << str3 << endl;
	cout << endl;

	return 0;
}
