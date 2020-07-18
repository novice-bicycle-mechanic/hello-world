// ������� �� ����� DZ_ST_C++_03.pdf
// ������� �9
// ����: �������-�����, ������������ �������������,
//       �������� ����� default � delete �� ��������� � �������,
//       ����������[] � (), ���������� ���������� �������������� ����
// �������.
/*
� ����� ��������� ����� String �������� ���������� [], (),
�������������� ���� � int:
� [] � ���������� ������� �� ���������� �������;
� () � ���� ������ � ������, ���� ������ ���� ���������� ������, ���� ��� �1.
� �������������� � int ���������� ����� ������.
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
		cout << " ������ ����������� ~String � ���������� - ������ ������" << endl;
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
		cout << " ������ ����������� ~String � �������������� �-�������" << endl;
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
		if (this->line) {
			delete[] this->line;
			cout << " ������ ���������� ~String" << endl;
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
};
// ����� ������ ������

// ������������� ������� ������ ������� �� ������� ���������� <<
std::ostream& operator<<(std::ostream& out, const String& str) {
	out << str.line;
	return out;
}






int main() {
	setlocale(LC_ALL, "ru");

	// �������� ������
	String s("��������������������������������");
	cout << " ������� ������: " << s << endl;

	// ���������� [] ������� ��������� ����� ������
	size_t index{ 32 };
	cout << " ������� �� ����� ������ ������ � �������� " << index << ": " << s[index] << endl;

	// ���������� () �������� ������� ������� � ������
	// � ������ ������ ������� � ������ ��� -1, ���� ��� � ��� ���
	char symbol{ '\0' };
	cout << " ������ ��������� ������� \'" << symbol << "\' � ������ \"" << s << "\": " << s(symbol) << endl;

	symbol = '�';
	cout << " ������ ��������� ������� \'" << symbol << "\' � ������ \"" << s << "\": " << s(symbol) << endl;

	symbol = 'd';
	cout << " ������ ��������� ������� \'" << symbol << "\' � ������ \"" << s << "\": " << s(symbol) << endl;

	// ���������������� �������������� ���� String � ��� int
	cout << " ����� � �������� ������ \"" << s << "\" ����� ";
	String::printInt(s);

	return 0;
}
