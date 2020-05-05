// ������� ���������, ���������� ������ � ������� � ������������ ��������� +-*/, � �.�. � 16-����

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int vyrajenie(int a, string s, int b) {
	if (s == "+") return a + b;
	else if (s == "-") return a - b;
	else if (s == "*") return a * b;
	else if (s == "/") return a / b;
	else return 0;
}

int main() {
	setlocale(LC_ALL, "");
	string a;
	string oper;
	string b;

	cout << " ������� ��������� (a <������> <+|-|*|/> <������> b ): ";
	cin >> a >> oper >> b;
	cout
		<< " " << a << " " << oper << " " << b << " = "
		<< to_string(vyrajenie(stoi(a), oper, stoi(b))) << endl;

	cout << " ������� ��������� (a <������> <+|-|*|/> <������> b ): ";
	cin >> a >> oper >> b;
	cout
		<< " " << a << " " << oper << " " << b << " = "
		<< to_string(vyrajenie(stoi(a), oper, stoi(b))) << endl;

	cout << " ������� ��������� (a <������> <+|-|*|/> <������> b ): ";
	cin >> a >> oper >> b;
	cout
		<< " " << a << " " << oper << " " << b << " = "
		<< to_string(vyrajenie(stoi(a), oper, stoi(b))) << endl;

	cout << " ������� ��������� (a <������> <+|-|*|/> <������> b ): ";
	cin >> a >> oper >> b;
	cout
		<< " " << a << " " << oper << " " << b << " = "
		<< to_string(vyrajenie(stoi(a), oper, stoi(b))) << endl;

	cout << " ������� ����� ��� �������� � 16-�������� ������: ";
	cin >> a;
	cout << showbase;
	cout << " " << dec << stoi(a) << " == " << hex << stoi(a) << endl;
	cout << noshowbase;

	return 0;
}