// DZ_ST_C++_07_dz23_vstrecha23_zadanie_Time_main.cpp
//
// задание 1 из файла Domasnee_zadanie_1594661480.txt
// Выполните домашние задания после уроков 3, 4, 5
// Урок 5. Задание 1
/*
1. Создайте класс Время, в котором реализованы операции
сложения, вычитания, сравнения, ввода и вывода на экран,
возможность конвертации времени из американского формата
am (pm): 10:00 pm = 22:00, 12:00 pm =00:00.
*/

#include <iostream>
#include <clocale>
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_Time.h"
using namespace spaceTime;


// ГЛАВНАЯ ФУНКЦИЯ
int main() {
	setlocale(LC_ALL, "ru");

	Time time1;
	std::cout << " time1: " << time1 << std::endl;
	std::cout << std::endl;

	Time time2(13, 34, 35);
	std::cout << " time2: " << time2 << std::endl;
	std::cout << std::endl;

	Time time3(time2);
	std::cout << " time3: " << time3 << std::endl;
	std::cout << std::endl;

	Time time4 = time2;
	std::cout << " time4: " << time4 << std::endl;
	std::cout << std::endl;

	Time time5;
	time5 = time2;
	std::cout << " time5: " << time5 << std::endl;
	std::cout << std::endl;

	Time time6 = time2 + time3;
	std::cout << " time6 = time2 + time3 == " << time6 << std::endl;
	std::cout << std::endl;

	Time time7;
	time7 = time2 + time6;
	std::cout << " time7 = time2 + time6 == " << time7 << std::endl;
	std::cout << std::endl;

	Time time8 = time6 - time5;
	std::cout << " time8 = time6 - time5 == " << time8 << std::endl;
	std::cout << std::endl;

	// сравним объекты на равенство
	std::cout
		<< " Сравним объекты на равенство >>> \n"
		<< " Время " << time1
		<< (time1 == time2 ? "" : " не")
		<< " равно Времени " << time2
		<< std::endl;
	std::cout << std::endl;

	// сравним объекты на равенство
	std::cout
		<< " Сравним объекты на равенство >>> \n"
		<< " Время " << time3
		<< (time3 == time2 ? "" : " не")
		<< " равно Времени " << time2
		<< std::endl;
	std::cout << std::endl;

	// сравним объекты на неравенство
	std::cout
		<< " Сравним объекты на неравенство >>> \n"
		<< " Время " << time5
		<< (time5 != time2 ? " не" : "")
		<< " равно Времени " << time2
		<< std::endl;
	std::cout << std::endl;

	// сравним объекты на неравенство
	std::cout
		<< " Сравним объекты на неравенство >>> \n"
		<< " Время " << time6
		<< (time6 != time2 ? " не" : "")
		<< " равно Времени " << time2
		<< std::endl;
	std::cout << std::endl;

	// сравним объекты на больше
	std::cout
		<< " Сравним объекты на больше >>> \n"
		<< " Время " << time7
		<< (time7 > time2 ? "" : " не")
		<< " больше Времени " << time2
		<< std::endl;
	std::cout << std::endl;

	// сравним объекты на больше
	std::cout
		<< " Сравним объекты на больше >>> \n"
		<< " Время " << time6
		<< (time6 > time2 ? "" : " не")
		<< " больше Времени " << time2
		<< std::endl;
	std::cout << std::endl;

	// сравним объекты на меньше
	std::cout
		<< " Сравним объекты на меньше >>> \n"
		<< " Время " << time7
		<< (time7 < time2 ? "" : " не")
		<< " меньше Времени " << time2
		<< std::endl;
	std::cout << std::endl;

	// сравним объекты на меньше
	std::cout
		<< " Сравним объекты на меньше >>> \n"
		<< " Время " << time6
		<< (time6 < time2 ? "" : " не")
		<< " меньше Времени " << time2
		<< std::endl;
	std::cout << std::endl;

	// введем американское время - до полудня
	Time time9(Time::AT::am, 10);
	std::cout << " time9 по американски, 10:00 am: " << time9 << std::endl;
	std::cout << std::endl;

	// введем американское время - после полудня
	Time time10(Time::AT::pm, 10);
	std::cout << " time10 по американски, 10:00 pm: " << time10 << std::endl;
	std::cout << std::endl;
/*
	// введем время
	std::cout << " Введите через пробелы: часы минуты секунды\n в диапазоне: 00 00 00 - 23 59 59 >>> \n";
	std::cin >> time1;
	std::cout << " time1: " << time1 << std::endl;
	std::cout << std::endl;
*/

	Test test1(13, 34, 35);
	std::cout << " test1: " << test1 << std::endl;
	std::cout << std::endl;

	Test test2(8, 14, 32);
	std::cout << " test2: " << test2 << std::endl;
	std::cout << std::endl;

	Test test3 = test1 + test2;
	std::cout << " test3 = test1 + test2 == " << test3 << std::endl;
	std::cout << std::endl;

	return 0;
}
// Конец ГЛАВНОЙ ФУНКЦИИ
