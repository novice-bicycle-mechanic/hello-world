// ������� �� ����� DZ_1592244250.txt
// ���� Lab_C++_week_1.pdf, ������� 1, ������� 2
/*
���������� ����� �������. ���������� ������� ����������
x, y, z � ����������-������ ������. ���������� �������-�����
������ ��� ����� ������, ������ ������, ���������� ���������
��� ������� � ����������-������, ���������� ���������� �
���� � �������� ������ �� �����.
*/
#include <iostream>
#include <clocale>
#include <stdio.h>

using namespace std;

// ��������� ��������� �����
struct FileAttribute {
	const char* name = "";    // ������������ �����
	FILE* data = nullptr;     // ��������� �� ����
	FILE** ptrData = &data;   // ��������� �� ��������� �� ����
};


class Point {
private:
	int x = 0;
	int y = 0;
	int z = 0;
public:
	Point(int x, int y, int z) { setXYZ(x, y, z); }

	int getX() { return x; }
	int getY() { return y; }
	int getZ() { return z; }

	void setX(int x) { this->x = x;	}
	void setY(int y) { this->y = y; }
	void setZ(int z) { this->z = z; }
	void setXYZ(int x, int y, int z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void input() {
		cout << " ������� ���������� ����� (����� �������: x y z): ";
		cin >> this->x >> this->y >> this->z;
	}

	// ����� ������ ��������� ����� �� ������
	void print() {
		cout
			<< " x = " << this->x << ", y = " << this->y << ", z = " << this->z << endl;
	}

	// ����� �������� ��������� ����� �� ���������� �����
	void upload(const char* nameFile) {

		FileAttribute point;
		point.name = nameFile;

		// ������� ���� ��� �������� ������� �����
		if (fopen_s(point.ptrData, point.name, "r")) {
			printf_s(" ���� %s �����������\n", nameFile);
		}
		else {    // ���� - ���� ���� ��������
			char* line = nullptr;
			char* contex = nullptr;
			char** ptrcontex = &contex;
			size_t lenLine = 256;
			line = new char[lenLine] { '\0' };

			if (fgets(line, lenLine, point.data)) {
				contex = line;
				this->x = atoi(strtok_s(contex, ",", ptrcontex));
				this->y = atoi(strtok_s(contex, ",", ptrcontex));
				this->z = atoi(strtok_s(contex, "\n", ptrcontex));
			}

			delete[] line;
			line = nullptr;
			contex = nullptr;

			fclose(point.data);
		}
	}

	// ����� ������ ��������� ����� � ��������� ����
	void write(const char* nameFile) {
		FileAttribute point;
		point.name = nameFile;
		fopen_s(point.ptrData, point.name, "w");
		fprintf_s(point.data, "%d,%d,%d%c",	this->x, this->y, this->z, '\x0a');
		fclose(point.data);
	}
};



int main() {
	setlocale(LC_ALL, "ru");

	Point point(1, 2, 3);
	cout << " ������ ��� ���������� �����:";
	point.print();
	cout << " -----------------------------------------------------------------" << endl;

	point.input();
	cout << " ������ ��� ����� ����� � ������:";
	point.print();
	cout << " -----------------------------------------------------------------" << endl;

	cout << " ������ �������������: x=12 y=14 z=16.\n ��������:";
	point.setXYZ(12, 14, 16);
	point.print();

	cout << " ���������� ����� �������� � ���� point.txt" << endl;
	point.write("point.txt");
	cout << " -----------------------------------------------------------------" << endl;

	cout << " ������ �������������: x=5. ��������: ";
	point.setX(5);
	cout << point.getX() << endl;

	cout << " ������ �������������: y=7. ��������: ";
	point.setY(7);
	cout << point.getY() << endl;

	cout << " ������ �������������: z=9. ��������: ";
	point.setZ(9);
	cout << point.getZ() << endl;

	cout << " ��������:";
	point.print();
	cout << " -----------------------------------------------------------------" << endl;

	cout << " ���������� ����� ��������� �� ����� point.txt" << endl;
	point.upload("point.txt");

	cout << " ��������:";
	point.print();
	cout << " -----------------------------------------------------------------" << endl;

	return 0;
}
















