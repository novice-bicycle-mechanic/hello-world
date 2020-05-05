// сделать программу, получающую строку с числами и возвращающую результат +-*/, и т.ч. в 16-виде

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

	cout << " ¬ведите выражение (a <пробел> <+|-|*|/> <пробел> b ): ";
	cin >> a >> oper >> b;
	cout
		<< " " << a << " " << oper << " " << b << " = "
		<< to_string(vyrajenie(stoi(a), oper, stoi(b))) << endl;

	cout << " ¬ведите выражение (a <пробел> <+|-|*|/> <пробел> b ): ";
	cin >> a >> oper >> b;
	cout
		<< " " << a << " " << oper << " " << b << " = "
		<< to_string(vyrajenie(stoi(a), oper, stoi(b))) << endl;

	cout << " ¬ведите выражение (a <пробел> <+|-|*|/> <пробел> b ): ";
	cin >> a >> oper >> b;
	cout
		<< " " << a << " " << oper << " " << b << " = "
		<< to_string(vyrajenie(stoi(a), oper, stoi(b))) << endl;

	cout << " ¬ведите выражение (a <пробел> <+|-|*|/> <пробел> b ): ";
	cin >> a >> oper >> b;
	cout
		<< " " << a << " " << oper << " " << b << " = "
		<< to_string(vyrajenie(stoi(a), oper, stoi(b))) << endl;

	cout << " ¬ведите число дл€ перевода в 16-тиричный формат: ";
	cin >> a;
	cout << showbase;
	cout << " " << dec << stoi(a) << " == " << hex << stoi(a) << endl;
	cout << noshowbase;

	return 0;
}