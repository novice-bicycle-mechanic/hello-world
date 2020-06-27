/*
Реализуйте  класс  “Точка”.  
Необходимо  хранить  координаты  x,  y,  z  в  переменных-членах  класса.  
Реализуйте  функции-члены  класса  для  ввода  данных,  вывода  данных,  реализуйте  аксессо-ры  для  доступа  к  переменным-членам,  
реализуйте  сохранение  в  файл и загрузку данных из файла.
*/
#include <iostream>
#include <fstream>
#include "Dot_1.h"

using namespace std;



int main()
{
	setlocale(LC_ALL, "Russian");
	Dot x;
	x.Input();
	x.cout_coord();
	Dot y;
	y.Input();
	y.cout_coord();
	y.fout_in_file();
	x.fout_in_file();

}
