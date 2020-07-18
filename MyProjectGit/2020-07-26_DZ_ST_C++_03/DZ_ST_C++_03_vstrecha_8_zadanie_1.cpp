// ������� �� ����� DZ_ST_C++_03.pdf
// ������� �8
// ����: ����������� ��������
// ������� 1.
/*
�������� � ��� ������������ ����� String ����������� ��������.
*/
// ���� ������� �� "������������� ������ String"
//---------------------------------------------------------------------------
// ������� �� ����� DZ_ST_C++_01.pdf
//
// ����: ����������� ����������-����� � �������-�����,
//       ��������� ������� �������������
// ������� 3, �������
/*
    ����������� ����� String, ������� � ���������� ����� ��������������
��� ������ �� ��������.
����� ������ ���������:
� ����������� �� ���������, ����������� ������� ������ ������ 80 ��������;
� �����������, ����������� ��������� ������ ������������� �������;
� �����������, ������� ������ ������ � �������������� � �������,
���������� �� ������������.
    ���������� ������� ����������, � ����� ������������ ���������
������������� �������������, ���� ��� ��������.
    ����� ������ ��������� ������ ��� ����� ����� � ���������� �
������ ����� �� �����. ����� ����� ����������� �����������
�������-����, ������� ����� ���������� ���������� ���������
�������� �����.
*/
//----------------------------------------------------------------------------
#include <iostream>
#include <clocale>
#include <Windows.h>
#include <iomanip>
#include <conio.h>
using namespace std;


// ����� ������
class String {
private:
	char* line{ nullptr };

	// ����� �������� ����� ������ �������������
	size_t lengthString(const char* str) {
		size_t length = 0;
		while (str[length++]);
		return --length;
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
//		char line[81]{ '\0' };
		cout << "������� ������ ������ �� 80 ��������" "\n" "> ";
		cin >> str.line;
		return str;
	}


	// ����� ����� C-������ ������������
	void inputLine() {
		char line[81]{ '\0' };
		cout << "������� ������ ������ �� 80 ��������" "\n" "> ";
		cin >> line;
	}

	// ����� ������������ ���������� ��������� ��������-�����
	int showNumberLine() {
		return counter();
	}

	// ����� ���������� �������� �������� ������ line
	void setItemLine(size_t index, char symbol) {
		line[index] = symbol;
	}


	//----------------------------------------------------------------------

	// ����������� �������� (�����������)
	String(String&& str) noexcept :line(nullptr) {               // <--- ����������� �������� !!!
		cout << " ������ ����������� ��������" << endl;
		line = str.line;
		str.line = nullptr;
	}

	//----------------------------------------------------------------------


};
// ����� ������ ������


// ������� �������
int main() {
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	String str1;
	cout
		<< " ������� ������ �"
		<< str1.showNumberLine()
		<< " ������������� �� ��������� � ��������� ���������:"
		<< endl;
	for (size_t i = 0, j = 33; i < 80; i++, j++) {
		str1.setItemLine(i, (char)j);
	}
	str1.printLine();
	cout << "--------------------------------------------------------------------------------" << endl;

	String str2(40);
	cout
		<< " ������� ������ �"
		<< str2.showNumberLine()
		<< " ������ 40 ������������� � ���������� � ��������� ���������:"
		<< endl;
	for (size_t i = 0, j = 33; i < 40; i++, j++) {
		str2.setItemLine(i, (char)j);
	}
	str2.printLine();
	cout << "--------------------------------------------------------------------------------" << endl;

	String str3 = "ZZZZZZZZZZbbbbbbbbbbccccccccccddddddddddeeeeeeeeeeffffffffffggggggggggXXXXXXXXX";
	cout << " ������� ������ �" << str3.showNumberLine() << " � ����������� �-������:" << endl;
	str3.printLine();
	cout << "--------------------------------------------------------------------------------" << endl;

	String str4("aaaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeffffffffffgggggggggghhhhhhhhh");
	cout << " ������� ������ �" << str4.showNumberLine() << " � �������������� �-�������:" << endl;
	str4.printLine();
	cout << "--------------------------------------------------------------------------------" << endl;
/*
	char stringUser[80]{ '\0' };
	char symbol{ '\0' };
	cout << " ������� ������ ������ �� 79 �������� \n>";

	for (size_t i = 0; i < 79; i++) {
		symbol = _getch();
		if (symbol == 13) break;
		stringUser[i] = symbol;
		cout << symbol;
	}
	cout << endl;

	String str5(stringUser);
	cout << " ������� ������ �" << str5.showNumberLine() << " � �������������� �-������� ������������:" << endl;
	str5.printLine();
	cout << "--------------------------------------------------------------------------------" << endl;
*/
	//------------------------------------------------------------------

	// ������ ���������� ������������ �������� (�����������)
	// �������� ������
	
	String b = String::inputString();

	b.printLine();

	//------------------------------------------------------------------

	return 0;
}
// ����� ������� �������
