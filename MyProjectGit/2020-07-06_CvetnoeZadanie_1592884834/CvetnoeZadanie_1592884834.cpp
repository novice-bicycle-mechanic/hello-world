// ������� �� ����� CvetnoeZadanie_1592884834.txt
/*
�������� ������� ::
����������� ����� ����.
���� ����������� � ��������� � ���� �������� "��������� ������������"
(������ �����, ���������� �� ������������� �������� ���������)
�������� RGB, CMYK, CMY, HSV, HSI, LAB ... �� ����� ����� ������.
� ������ �� ��� ����������� ��������������, ������� ����������.
��� �� �����, ������ ����� ��������� � ������ ������ ������������� ������������ �����.
� ������� �����, � ���� �������, ���� ������������� � ������� �������� ���������
(����� �������������� ���������, ����� ������� ���������� ������� �����!).

������ ::
1) ����������� ���������� ����� ����
2) ����������� � ���� ������� ������ ��������� �������� �������, ��������, CMYK, RGB, HSV.
(��������, � ������� �������� ����� C ��� ������������� �������� ������� ������ union, ��� �� ������ �� �������)
3) ����������� ����� �������������. �� �������� � ��������� � ������� � �������� ������������ ���������������!!!
4) ���������� ������� �������������� ������ �� ����� �������� ������ � ������
5) ���������� ������� ������� � ������ �������� ������ (���������).
��� ���� ������� � ������ ������������ �� ������ ����.
6) ���������� ������� ������ � ������� :: ����� ������� �����������.

�������� ��������� ��������� :: ���������� ���� �� ����
1) ���������� ������! (����� ���� ���������������� ���� ���
� �������� �������� ������ ����������, ��� � ������� ������ �� ������).
�� ����, ����� ������� �������������� ������������ ����� ������ � ������ ����������
(����� ��������� �������, ��� �������)
2) ���������� ������:: (�� ������ ��� � ������)
�������������� ��������� �������� ��� ������, ��� � �������� ������.
����� �������� ��� ��������� ������ � �������.
3) ���������������� ���� ������:: ������ ������� � ������
(�������� � ����������� � ���� ������ ����� ������ RGB)
����� �� �������������� �� ��� ��������� ������. ��������������,
��� ��������� ������ (����� � ����� ����������� ��������),
���������� ��� ������������� �� ���� �������
(������� � ������� ������� ����� CMYK, ��� ����� ������� ������������� ����� � ���� ������,
� � �������� ������������ �� ������ CMYK ������������� ����� � ������ �������),
����� ���������������.
*/

/*
���������� �� ����:
1. �� ���� ��������� �������� ������� � ������� ����� �� ����� ����������
����� ����������� ������ RGB - ��� ����������� ��� ���������� ����� �� ������ ��������.
� ������ ������ ���������� ����� ���������� ����������� � ������� ����� ���� � �����������
3-� ������ ������: �������� (R), �������� (G) � ������ (B).
��� ����������� ������� ������� �������� ����� ������������ ����� �� 0 �� 255.
��������� ���� ������������ ������� ����� �������� ������� ������: ��������,
255.255.255 - �����, 0.0.0 - ������, 255.0.0 - �������, 0.255.0 - �������, 0.0.255 - �����.
2. ������ CMYK - ��� ������ ����� ��������� ������ �� ����� �������� (����� ����� ������).
� ������ ������ ����� ���������� ���������� �� ������ ����� �������� ������ ������:
�������� (C), ���������� (M) � ������� (Y). ��� ���������� � ���������� ���������� ������� ������
������ ���������� ������ ����. � ���������������� ���������� ����-���������� ����.
����� �������� ������ ���� ��� ������ ������� ������ ��������� ������ � ������ ��������
������ ������ ���� (K). ���������� ���������� ���� � ������ CMYK �� ������ �������� �� ��������:
1) �� ������ �������� ���� ���������� � ����������� � ������� ����, � ���� ��������� ������
���������� �� ����� ������ ���������-��������;
2) �������� �������� � ������ CMYK ���� ����������� ���� ��� ����������������� ���������,
� ���������� ���� ������� �� ������-���������� ������� ������, ������ � ���� ���������
����������� ��������� �����.
�������, ��� ������������ ���������� ���������� ������ CMY, ������� ���� �������
����� ����� ������ � ���������� ������ ������ RGB:
�������� - ��� ��������, �������� - ��� ����������, ������ - ��� �������.
��� ��������� �������� �������� ��������� ������� ������ CMY - CMY255, � �������
����� �������� ������ �� 0 �� 255.
���������� �������� ������ �������������� �� CMYK � ������� ����������� ������.
3.������ ������������ �������� ������ ����� ���������� ����������� �������� �� ������ ��������,
� ��������� ����������� �����������.
*/

#include <iostream>
#include <clocale>
using namespace std;


// ��������� ������ RGB, �������� ������� ����� 0-255
struct RGB
{
	unsigned char red{ 0 };
	unsigned char green{ 0 };
	unsigned char blue{ 0 };
};


// ��������� ������ CMY, �������� ������� ����� 0-255
struct CMY
{
	unsigned char cyan{ 0 };
	unsigned char magenta{ 0 };
	unsigned char yellow{ 0 };
};


// ��������� ������ CMYK, �������� ������� ����� 0-100, ����� ���� ������ ����� 100
struct CMYK
{
private:
	unsigned char cyan{ 0 };
	unsigned char magenta{ 0 };
	unsigned char yellow{ 0 };
	unsigned char black{ 0 };

public:
	CMYK(
		unsigned char cyan,
		unsigned char magenta,
		unsigned char yellow,
		unsigned char black
	) {
		if ((cyan <= 100) && (magenta <= 100) && (yellow <= 100) && (black <= 100) &&
			(100 == (cyan + magenta + yellow + black))) {
			this->cyan = cyan;
			this->magenta = magenta;
			this->yellow = yellow;
			this->black = black;
		}
	}

	int getCyan() const { return (int)cyan; }
	int getMagenta() const { return (int)magenta; }
	int getYellow() const { return (int)yellow; }
	int getBlack() const { return (int)black; }
};


// ����� ����
class Color
{
private:
	union
	{
		RGB rgb;
		CMY cmy;
		CMYK cmyk;
	};
public:
	explicit Color() :Color(rgb) {}
	explicit Color(RGB rgb) :rgb{ rgb } {}
	explicit Color(CMY cmy) :cmy{ cmy } {}
	explicit Color(CMYK cmyk) :cmyk{ cmyk } {}
	explicit Color(const Color& object) { *this = object; }

	RGB getRGB() const { return rgb; }
	CMY getCMY() const { return cmy; }
	CMYK getCMYK() const { return cmyk; }

	void printRGB() {
		cout << "RGB " << (int)rgb.red << "," << (int)rgb.green << "," << (int)rgb.blue << endl;
	}

	void printCMY() {
		cout << "CMY " << (int)cmy.cyan << "," << (int)cmy.magenta << "," << (int)cmy.yellow << endl;
	}

	void printCMYK() {
		cout
			<< "CMYK "
			<< cmyk.getCyan() << ","
			<< cmyk.getMagenta() << ","
			<< cmyk.getYellow() << ","
			<< cmyk.getBlack()
			<< endl;
	}

	static CMY cmyFromCMYK(CMYK cmyk) {

		CMY cmy{
			(unsigned char)cmyk.getCyan(),
			(unsigned char)cmyk.getMagenta(),
			(unsigned char)cmyk.getYellow()
		};

		if (cmyk.getBlack()) {
			int one_third{ 0 };
			int remains{ 0 };

			one_third = cmyk.getBlack() / 3;

			cmy.cyan += one_third;
			cmy.magenta += one_third;
			cmy.yellow += one_third;

			if ((cmyk.getBlack() % 3) > 2) {
				cmy.cyan++;
				cmy.magenta++;
				cmy.yellow = 100 - cmy.cyan - cmy.magenta;
			}
			else if ((cmyk.getBlack() % 3) > 1) {
				cmy.cyan++;
				cmy.magenta = 100 - cmy.cyan - cmy.yellow;
			}
			else {
				cmy.cyan = 100 - cmy.magenta - cmy.yellow;
			}
		}

		int cyan{ 0 };
		int magenta{ 0 };
		int yellow{ 0 };

		cyan = cmy.cyan * 255 / 100;
		magenta = cmy.magenta * 255 / 100;
		yellow = cmy.yellow * 255 / 100;

		cmy.cyan = cyan;
		cmy.magenta = magenta;
		cmy.yellow = yellow;

		return cmy;
	}

	static RGB rgbFromCMY(CMY cmy) {

		RGB rgb{
			(unsigned char)(255 - cmy.cyan),
			(unsigned char)(255 - cmy.magenta),
			(unsigned char)(255 - cmy.yellow)
		};

		return rgb;
	}

	static CMY cmyFromRGB(RGB rgb) {

		CMY cmy{
			(unsigned char)(255 - rgb.red),
			(unsigned char)(255 - rgb.green),
			(unsigned char)(255 - rgb.blue)
		};

		return cmy;
	}
};



int main() {
	setlocale(LC_ALL, "ru");

//	RGB rgb{ 255,0,0 };
//	CMY cmy{ 0,0,255 };
	CMYK cmyk{ 0,0,50,50 };

	Color color1{ cmyk };
	color1.printCMYK();

	Color color2{ Color::cmyFromCMYK(cmyk) };
	color2.printCMY();

	Color color3{ Color::rgbFromCMY(Color::cmyFromCMYK(cmyk)) };
	color3.printRGB();

	Color color4{ Color::rgbFromCMY(color2.getCMY()) };
	color3.printRGB();

	Color color5{ Color::cmyFromRGB(color3.getRGB()) };
	color5.printCMY();

	return 0;
}

















