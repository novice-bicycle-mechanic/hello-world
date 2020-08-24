// DZ_ST_C++_07_dz23_vstrecha23_zadanie_Time_main.cpp
//
// ������� 1 �� ����� Domasnee_zadanie_1594661480.txt
// ��������� �������� ������� ����� ������ 3, 4, 5
// ���� 5. ������� 1
/*
1. �������� ����� �����, � ������� ����������� ��������
��������, ���������, ���������, ����� � ������ �� �����,
����������� ����������� ������� �� ������������� �������
am (pm): 10:00 pm = 22:00, 12:00 pm =00:00.
*/

#include <iostream>
#include <clocale>
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_Time.h"
using namespace datetime;


// ������� �������
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

	// ������� ������� �� ���������
	std::cout
		<< " ������� ������� �� ��������� >>> \n"
		<< " ����� " << time1
		<< (time1 == time2 ? "" : " ��")
		<< " ����� ������� " << time2
		<< std::endl;
	std::cout << std::endl;

	// ������� ������� �� ���������
	std::cout
		<< " ������� ������� �� ��������� >>> \n"
		<< " ����� " << time3
		<< (time3 == time2 ? "" : " ��")
		<< " ����� ������� " << time2
		<< std::endl;
	std::cout << std::endl;

	// ������� ������� �� �����������
	std::cout
		<< " ������� ������� �� ����������� >>> \n"
		<< " ����� " << time5
		<< (time5 != time2 ? " ��" : "")
		<< " ����� ������� " << time2
		<< std::endl;
	std::cout << std::endl;

	// ������� ������� �� �����������
	std::cout
		<< " ������� ������� �� ����������� >>> \n"
		<< " ����� " << time6
		<< (time6 != time2 ? " ��" : "")
		<< " ����� ������� " << time2
		<< std::endl;
	std::cout << std::endl;

	// ������� ������� �� ������
	std::cout
		<< " ������� ������� �� ������ >>> \n"
		<< " ����� " << time7
		<< (time7 > time2 ? "" : " ��")
		<< " ������ ������� " << time2
		<< std::endl;
	std::cout << std::endl;

	// ������� ������� �� ������
	std::cout
		<< " ������� ������� �� ������ >>> \n"
		<< " ����� " << time6
		<< (time6 > time2 ? "" : " ��")
		<< " ������ ������� " << time2
		<< std::endl;
	std::cout << std::endl;

	// ������� ������� �� ������
	std::cout
		<< " ������� ������� �� ������ >>> \n"
		<< " ����� " << time7
		<< (time7 < time2 ? "" : " ��")
		<< " ������ ������� " << time2
		<< std::endl;
	std::cout << std::endl;

	// ������� ������� �� ������
	std::cout
		<< " ������� ������� �� ������ >>> \n"
		<< " ����� " << time6
		<< (time6 < time2 ? "" : " ��")
		<< " ������ ������� " << time2
		<< std::endl;
	std::cout << std::endl;

	// ������ ������������ ����� - �� �������
	Time time9(Time::AT::am, 10);
	std::cout << " time9 �� �����������, 10:00 am: " << time9 << std::endl;
	std::cout << std::endl;

	// ������ ������������ ����� - ����� �������
	Time time10(Time::AT::pm, 10);
	std::cout << " time10 �� �����������, 10:00 pm: " << time10 << std::endl;
	std::cout << std::endl;
/*
	// ������ �����
	std::cout << " ������� ����� �������: ���� ������ �������\n � ���������: 00 00 00 - 23 59 59 >>> \n";
	std::cin >> time1;
	std::cout << " time1: " << time1 << std::endl;
	std::cout << std::endl;
*/
	return 0;
}
// ����� ������� �������
