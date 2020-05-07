// ����������� ���������� ���������� �������� ��� ���������� ���������
// 1 - .,!? 1
// 2 - ���� ABC 2
// 3 - ���� DEF 3
// 4 - ���� GHI 4
// 5 - ���� JKL 5
// 6 - ���� MNO 6
// 7 - ���� PQRS 7
// 8 - ���� TUV 8
// 9 - ���� WXYZ 9
// 0 - ' ' 0
// *
// #

#include <iostream>
#include <clocale>
#include <Windows.h>
#include <conio.h>
#define N "\n"
using namespace std;

// ������� ������ ��������� ������ - ���� ���������� ��������
void header(void)
{
	system("cls");

	cout <<
		N "\t" "�����   ����  ������"
		N "\t" " ESC   Enter    BS"
		N
		N "\t" "  1      2      3"
		N "\t" " .,!?   ����   ����"
		N "\t" "        ABC    DEF"
		N
		N "\t" "  4      5      6"
		N "\t" " ����   ����   ����"
		N "\t" " GHI    JKL    MNO"
		N
		N "\t" "  7      8      9"
		N "\t" " ����   ����   ����"
		N "\t" " PQRS   TUV    WXYZ"
		N
		N "\t" "  *      0      #"
		N "\t" "        '_'"
		<< N << endl;
}

int main()
{
	setlocale(LC_ALL, "");

	unsigned char byte1char = '\0';					// ��� ������� ��������������
	unsigned char byte2char = '\0';					// ��� ������� ����������
	enum keys { BS = 8, Enter = 13, ESC = 27 };		// ���� ������� ������
	unsigned int timeCode = 0;						// ������� ���������� ��������� ��������
	unsigned int delay = 8;							// ����� ���������� �������� �������
	char str[256]{ '\0' };							// ������ ���������
	size_t idx = 0;									// ������ ������ ���������
	size_t indexS = 0;								// ������ ������ �������� � �������
	size_t indexMax = 0;							// ������������ ������ � ������ �������� � �������
	size_t numKey = 0;								// ����� �������
	char key[12][10]{								// ������ �������� � ������
		{' ','0','\0','\0','\0','\0','\0','\0','\0','\0'},		// 0
		{'.',',','!','?','1','\0','\0','\0','\0','\0'},			// 1
		{'�','�','�','�','A','B','C','2','\0','\0'},			// 2
		{'�','�','�','�','D','E','F','3','\0','\0'},			// 3
		{'�','�','�','�','G','H','I','4','\0','\0'},			// 4
		{'�','�','�','�','J','K','L','5','\0','\0'},			// 5
		{'�','�','�','�','M','N','O','6','\0','\0'},			// 6
		{'�','�','�','�','P','Q','R','S','7','\0'},				// 7
		{'�','�','�','�','T','U','V','8','\0','\0'},			// 8
		{'�','�','�','�','W','X','Y','Z','9','\0'},				// 9
		{'*','\0','\0','\0','\0','\0','\0','\0','\0','\0'},		// * (10)
		{'#','\0','\0','\0','\0','\0','\0','\0','\0','\0'}		// # (11)
	};

	header();

	do
	{
		byte1char = _getch();
		if (_kbhit()) (void)_getch();

		if (byte1char == ESC) break;						// ���� ������ ESC - ����� �� ���������

		if ((('0' <= byte1char) && (byte1char <= '9'))		// ���� ������ ������� ���������� ��������
			|| (byte1char == '*') || (byte1char == '#'))
		{
			if (byte1char != byte2char)						// ���� ��� ������� ��� ���������� �������
			{
				indexS = 0;

				switch (byte1char)							// ������ ��������� �������
				{
				case '0': numKey = 0; indexMax = 1; break;
				case '1': numKey = 1; indexMax = 4; break;
				case '2': numKey = 2; indexMax = 7; break;
				case '3': numKey = 3; indexMax = 7; break;
				case '4': numKey = 4; indexMax = 7; break;
				case '5': numKey = 5; indexMax = 7; break;
				case '6': numKey = 6; indexMax = 7; break;
				case '7': numKey = 7; indexMax = 8; break;
				case '8': numKey = 8; indexMax = 7; break;
				case '9': numKey = 9; indexMax = 8; break;
				case '*': numKey = 10; indexMax = 0; break;
				case '#': numKey = 11; indexMax = 0; break;
				}
				byte2char = byte1char;
			}

			cout << key[numKey][indexS];	// ����� ������� ������� �� ������ ��� ������� �������
			cout << "\x1b[D";				// ������� ������ ��� ��������� ��������� ������

			while (true)
			{
				if (_kbhit() && (timeCode <= delay))		// ���� ���� ������� �������
				{
					indexS++;		// ������ ������ ���������� ������� �� ������ � �������
					if (indexS > indexMax) indexS = 0;

					cout << key[numKey][indexS];	// ������� �������� ��������� ������
					cout << "\x1b[D";				// ������� ������ ��� ��������� ��������� ������

					timeCode = 0;
					break;
				}
				else if (timeCode > delay)					// ���� ������� ����� �� ����
				{
					str[idx++] = key[numKey][indexS];		// ������ ��������� �������� ������ � ������ ���������
					cout << key[numKey][indexS];			// ������� / ��������� ��������� �������� ������

					byte2char = '\0';
					indexS = 0;
					timeCode = 0;
					break;
				}
				else if (!_kbhit())		// ���� �������� ������� �� ����
				{
					timeCode++;			// ����������� ��� ��������
				}

				Sleep(100);				// �������� ������� 0,1 ���.
			}
		}

		if (byte1char == Enter)			// ���� ������ Enter - ���� � �������� ���������
		{
			header();										// ��������� �����
			cout << " ����������: " << str << N << endl;	// ����� ������������� ���������

			byte2char = '\0';
			indexS = 0;
			timeCode = 0;
			idx = 0;
			for (size_t i = 0; i < 256; i++) str[i] = '\0';		// ������� ������ ���������
		}

		if (byte1char == BS)				// ���� ������ BackSpace - ������ ���������� �������
		{
			if (idx) str[--idx] = '\0';		// ������ "�����" � ������� ���������� ������� ������
			header();						// ��������� �����
			cout << str;					// ������� ����������� �� 1 ������ ������
		}
		
	} while (true);

	return 0;
}

