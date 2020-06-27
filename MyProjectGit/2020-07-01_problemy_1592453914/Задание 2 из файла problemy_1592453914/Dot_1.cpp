#include <iostream>
#include "Dot_1.h"

using namespace std;

void Dot::Input() {
	cout << "¬ведите x";
	cin >> x;
	cout << "¬ведите y";
	cin >> y;
	cout << "¬ведите z";
	cin >> z;

}

void Dot::cout_coord() {
	cout << "(" << x << "," << y << "," << z << ")";
}

