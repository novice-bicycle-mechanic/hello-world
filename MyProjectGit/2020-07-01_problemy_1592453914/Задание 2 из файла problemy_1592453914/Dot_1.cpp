#include <iostream>
#include "Dot_1.h"

using namespace std;

void Dot::Input() {
	cout << "������� x";
	cin >> x;
	cout << "������� y";
	cin >> y;
	cout << "������� z";
	cin >> z;

}

void Dot::cout_coord() {
	cout << "(" << x << "," << y << "," << z << ")";
}

