// задание из файла DZ_ST_C++_03.pdf
// Встреча №9
// Тема: Функции-члены, генерируемые автоматически,
//       ключевые слова default и delete по отношению к классам,
//       перегрузка[] и (), перегрузка операторов преобразования типа
// Задание.
/*
В ранее созданный класс String добавьте перегрузку [], (),
преобразования типа к int:
• [] — возвращает элемент по указанному индексу;
• () — ищет символ в строке, если символ есть возвращает индекс, если нет –1.
• Преобразование к int возвращает длину строки.
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

	// КОНСТРУКТОР переноса (перемещения)
	String(String&& str) noexcept :line(nullptr) {
		cout << " Вызван конструктор переноса" << endl;
		line = str.line;
		str.line = nullptr;
		lenLine = lengthString((const char*)line);
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
};
// КОНЕЦ КЛАССА Строка

// Дружественная ФУНКЦИЯ вывода объекта на консоль оператором <<
std::ostream& operator<<(std::ostream& out, const String& str) {
	out << str.line;
	return out;
}






int main() {
	setlocale(LC_ALL, "ru");

	// создадим строку
	String s("абвгдеёжзийклмнопрстуфхцчшщъыьэюя");
	cout << " Создана строка: " << s << endl;

	// оператором [] вызовем отдельную букву строки
	size_t index{ 32 };
	cout << " Выведем на экран символ строки с индексом " << index << ": " << s[index] << endl;

	// оператором () проверим наличие символа в строке
	// и вернем индекс символа в строке или -1, если его в ней нет
	char symbol{ '\0' };
	cout << " Найдем положение символа \'" << symbol << "\' в строке \"" << s << "\": " << s(symbol) << endl;

	symbol = 'в';
	cout << " Найдем положение символа \'" << symbol << "\' в строке \"" << s << "\": " << s(symbol) << endl;

	symbol = 'd';
	cout << " Найдем положение символа \'" << symbol << "\' в строке \"" << s << "\": " << s(symbol) << endl;

	// продемонстрируем преобразование типа String в тип int
	cout << " Длина в символах строки \"" << s << "\" равна ";
	String::printInt(s);

	return 0;
}
