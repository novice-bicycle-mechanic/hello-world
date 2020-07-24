// ������� 1 �� ����� Domasnee_zadanie_1594661480.txt
// ��������� �������� ������� ����� ������ 3, 4, 5
// ���� 3. ������� 2
/*
�������� � ��������� ����� �������, ������� ������� ������,
���������� ����������� ���� �����, �� ���� ����� ������� ��� ���� �����.
��������, ����������� ����������� ����� �sdqcg� �rgfas34� ����� ������ �sg�.
��� ���������� ������� ����������� �������� * (�������� ���������).
*/
#include <iostream>
#include <clocale>
using namespace std;


// ����� ������
class String {
private:
	char* line{ nullptr };
	size_t lenLine{ 0 };

	// ������������ � ������ ���������� ��������� []
	// ��� �������� ����������� �������� ��� ������������ �������
	char zero[1]{ '\0' };

	// ����� �������� ����� ������ �������������
	size_t lengthString(const char* str) {
		size_t length = 0;
		while (str[length++]);
		--length;
		lenLine = length;
		return length;
	}

	// ����� ����� ������� ������ (��� ��������� == TRUE - ���������� ��������)
	static int counter(bool counting = false) {
		static int account{ 0 };
		if (counting) ++account;
		return account;
	}

	// ����� ��������� ������������ ������ ������ line
	void allocatingDynamicMemory(size_t length) {
		line = new char[length + 1]{ '\0' };
		lenLine = length;
		counter(true);
	}

public:

	// ����������� �� ������ ��������� �������
	String(size_t sizeLine) {
		allocatingDynamicMemory(sizeLine);
		cout << " ������ ����������� String � ���������� - ������ ������ - " << sizeLine << endl;
	}

	// ����������� �� ��������� �� ������ �� 80 �������� !!! � �������������� ������������ !!!
	String() : String(80) {
		cout
			<< " ������ ����������� ~String �� ��������� - � ������ ������ 80"
			<< " � �������������� ������������ � ����������" << endl;
	}

	// �����������, ���������������� ������ ������� C-������� ������������
	String(const char* strInit) {
		setLineConst(strInit);
		cout << " ������ ����������� String � �������������� �-�������" << endl;
	}

	// ����������� �������� (�����������)
	String(String&& str) noexcept :line(nullptr) {
		cout << " ������ ����������� ��������" << endl;
		line = str.line;
		str.line = nullptr;
		lenLine = lengthString((const char*)line);
	}

	// ����������
	~String() {
		if (line) {
			cout << " ������ ���������� ~String" << endl;
			delete[] line;
		}
	}

	// ����� ������ ������ �� �����
	void printLine() {
		cout << this->line << endl;
	}

	// ����� ������� ������ ������� C-�������
	void setLineConst(const char* strInit) {
		// ���������� ����� ���������������� ������
		size_t len = lengthString(strInit);
		// �������� ������������ ������ ��� ������ �������
		allocatingDynamicMemory(len);
		// �������� � ������ ������� ������ �������������
		for (size_t i = 0; i < len; i++) {
			line[i] = strInit[i];
		}
	}

	// ����� ����� ������ � ����������
	static String inputString() {
		String str;
		cout << "������� ������ ������ �� 80 ��������" "\n" "> ";
		cin >> str.line;
		return str;
	}

	// ����� ����� C-������ ������������
	void inputLine() {
		char line[81]{ '\0' };
		cout << "������� ������ ������ �� 80 ��������" "\n" "> ";
		cin >> line;
		lenLine = lengthString((const char*)line);
	}

	// ����� ������������ ���������� ��������� ��������-�����
	int showNumberLine() {
		return counter();
	}

	// ����� ���������� �������� �������� ������ line
	void setItemLine(size_t index, char symbol) {
		line[index] = symbol;
	}

	// ����� ���������� ��������� ���������� [] 
	const char& operator[](const size_t index) const {
		if ((0 <= index) && (index <= lenLine))	return line[index];
		else return zero[0];
	}

	// ����� ���������� ��������� ������ ������� ()
	int operator()(const char& symbol) const {
		for (size_t i = 0; i < lenLine; i++) {
			if (symbol == line[i]) return i;
		}
		return -1;
	}

	// ����� ���������� �������� �������������� �������� ���� String
	// � ��� int - ���������� ����� ������
	operator int() {
		return (int)lenLine;
	}

	// ����� ��� ������������ ���������� �������� �������������� ���� � int
	static void printInt(int value) { cout << value << endl; }

	// �������� ������������� ������� ������ ������� �� ������� ���������� <<
	friend std::ostream& operator<<(std::ostream& out, const String& str);

	// �������� ������������� ������� ����������� ����� ���������� *
	friend String operator*(const String& str1, const String& str2);
};
// ����� ������ ������


// ������������� ������� ������ ������� �� ������� ���������� <<
std::ostream& operator<<(std::ostream& out, const String& str) {
	out << str.line;
	return out;
}


// ������������� ������� ����������� ����� ���������� *
String operator*(const String& str1, const String& str2) {

	// �������� ������ 3 �������� ��������� ����������� �����
	String str3(str1.lenLine);
	str3.lenLine = 0;

	// ���� �� ������� � ��������� � ��������� ������ 2
	bool str2_b{ false }; 

	// ������� �������� ������ 1
	for (size_t i = 0; i < str1.lenLine; i++)
	{
		str2_b = false;

		// ������� �������� ������ 3
		for (size_t j = 0; j < str1.lenLine; j++)
		{
			// ���� ������� ������ ������ 3 �� ����� '\0',
			// ����� ����� �� ����� � str2_b = true
			// - ������� ������ ������ 1 ����� �� ���������� � ������ 2
			// (������ ������ 3 �����������)

			// ���������� ��� � ������� �������� ������ 1,
			// ���� ��� ����� - ����� �� ����� � str2_b = false
			// - ������� � ���������� ������� ������ 1
			// (������ ������� ������ ������ 1 ��� ���������� � ����� �������)

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

			// ���� str2_b = true - ����� �� ����� �������� �������� ������ 3
			// - ������� � �������� �������� ������ 2
			if (str2_b) break;
		}

		// ������� � ��������� �������� ������� ������ 1 � ��������� ������ 2
		if (str2_b) {

			// ������� �������� ������ 2
			for (size_t k = 0; k < str2.lenLine; k++)
			{
				// ���� ������ ������ 2 ����� ������� ������ 1
				// - ��������� ������ ������ 1 � ������� ������� ����� ������ 3,
				// ��������� ����� ������ 3 �� 1
				// � ����� �� ����� �������� �������� ������ 2
				// ��� �������� � ���������� ������� ������ 1
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


// ������� �������
int main() {
	setlocale(LC_ALL, "ru");

	// �������� ������ 1
	String str1("������� ���� �� ���������");
	cout << "    ������� ������ 1: " << str1 << endl;
	cout << endl;

	// �������� ������ 2
	String str2("������� ������ ���");
	cout << "    ������� ������ 2: " << str2 << endl;
	cout << endl;

	// ������ ����������� �����
	String str3 = str1 * str2;
	cout << "    ������� ������ 3 = ������ 1 * ������ 2 >>> " << str3 << endl;
	cout << endl;

	return 0;
}
