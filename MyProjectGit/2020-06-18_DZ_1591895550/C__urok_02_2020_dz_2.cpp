// ���������� DZ_1591895550.txt
// �������� ������� 2 �� ����� C__urok_02_2020_1589461442.pdf
/*
2.	����������� ����� String, ������� � ���������� ����� �������������� ��� ������ �� ��������.
����� ������ ���������:
  ����������� �� ���������, ����������� ������� ������ ������ 80 ��������;
  �����������, ����������� ��������� ������ ������������� �������;
  �����������, ������� ������ ������ � �������������� � �������, ���������� �� ������������.
����� ������ ��������� ������ ��� ����� ����� � ���������� � ������ ����� �� �����.
*/
#include <iostream>
#include <clocale>
using namespace std;


class String {
private:
	char* line;

	// ������� ����� ������ �������������
	size_t lengthString(const char* str) {
		size_t length = 0;
		while (str[length++]);
		return --length;
	}
public:
	// ����������� �� ��������� �� ������ �� 80 ��������
	String() {
		this->line = new char[80] { '\0' };
	}
	// ����������� �� ������ ��������� �������
	String(size_t sizeLine) {
		this->line = new char[sizeLine]{ '\0' };
	}
	// �����������, ���������������� ������ ������� C-������� ������������
	String(const char* strInit) {
		setLineConst(strInit);
	}
	// ����������
	~String() {
		delete[] this->line;
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
		this->line = new char[len + 1]{ '\0' };
		// �������� � ������ ������� ������ �������������
		for (size_t i = 0; i < len; i++) {
			line[i] = strInit[i];
		}
	}
	// ����� ����� C-������ ������������
	const char* inputLine() {
		char line[256]{ '\0' };
		cout << "������� ������ ������ �� 255 ��������" "\n" "> ";
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