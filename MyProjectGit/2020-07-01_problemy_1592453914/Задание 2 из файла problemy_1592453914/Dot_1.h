#pragma once
#include <fstream>
using namespace std;

class Dot {

private:
	int x;
	int y;
	int z;

public:

	void Input();

	void cout_coord();

	int getX() {
		return x;
	}

	int getY() {
		return y;
	}

	int getZ() {
		return z;
	}

	Dot() {
		x = 0;
		y = 0;
		z = 0;
	}
	Dot(int a, int b, int c) {

		x = a;
		y = b;
		z = c;
		
	}
	~Dot() {

	}

	void fout_in_file() {
		ofstream fout;
		fout.open("Dot_Coords.txt");
		fout << "(" << x << "," << y << "," << z << ")" << endl;
		fout.close();
	}

	void cout_full() {
		ifstream fcout;
		fcout.open("Dot_Coords.txt");
		char r;
		fcout >> r >> x >> r >> y >> r >> z >> r;
		fcout.close();
	}
};

