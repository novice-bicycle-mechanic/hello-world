// ���� �������
#include <Windows.h>
#include <conio.h>
#include <stdio.h>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
WORD defaultColor = 0x0007;		// ���� ���� � �������� �� ���������

// ��������� �������� ������� ����������� ���� - ����������� �������
struct Pixel {
	char litera = '\0';			// �����-������� ���� �������
	WORD palette = 0x0000;		// ������� - ������ ����
	int frame = 0;				// ����� ��������: 0-���, 1-�� �����, -1 - � ��������
	char left = ' ';			// ����� ������ ��������
	char right = ' ';			// ������ ������ ��������
};

Pixel Wall     = { 'w', 0x0080, -1, '\xC5', '\xC5' };  // w - wall - �����
Pixel Floor    = { 'f', 0x0078, 1, ' ', ' ' };		   // f - floor - ���
Pixel Box      = { 'b', 0x00e0, 1, ' ', ' ' };		   // b - box - ����
Pixel Pusher   = { 'p', 0x0020, 1, ' ', ' ' };		   // p - pusher - ������
Pixel Location = { 'l', 0x007c, 1, ' ', ' ' };		   // l - location - �������������� (�����, �������������)
Pixel Space    = { ' ', 0x0000, 1, ' ', ' ' };		   //' '- space (������) - ������������ �� �������

// ������� ������ �������� - ������� ����� �����������
void Square(Pixel pixel) {
	// ������� - ������������ ������ ���� � ������,
	// � ��������� ����� ������ ������� - �������� ��������,
	// � ������� ������� �����
	// ��� - 16-�������� ����� 0xbbbb, b - 16-��������� ��� (0-9,a-f)
	// 0x***b - ���� ������, (0-7)-�������, (8-f)-����������� (0-7)
	// 0x**b* - ���� ����, (0-7)-�������, (8-f)-����������� (0-7)
	// 0xbb** - ����� �����: 04-������, 80-�����, 08-�����, 10-������;
	// 0xbb** - �����: 40-�������� ���� ���� �� ���� ������, � ��������;
	// 0xbb** - �����: 01-������ ������� �����, 02-���������
	// ���� �������, ���������� � ������ ����� �����������,
	// ����� 0x0100 � 0x0200

	if (pixel.frame) pixel.palette += 0x9c00;  // + 0x0400 + 0x8000 + 0x0800 + 0x1000 <-- �����;
	SetConsoleTextAttribute(hConsole, 0x0100);
	SetConsoleTextAttribute(hConsole, (pixel.palette - ((pixel.frame > 0) ? 0x1000 : 0)));
	printf_s("%c", pixel.left);
	SetConsoleTextAttribute(hConsole, (pixel.palette - ((pixel.frame > 0) ? 0x0800 : 0)));
	printf_s("%c", pixel.right);
	SetConsoleTextAttribute(hConsole, 0x0200);
	SetConsoleTextAttribute(hConsole, defaultColor);
}

// ������� ������ ������ ������� ����� ���� �� ������
void PrintChar(char symbol) {       // ������ - ��� ���� ���������� ��������
	     if (symbol == Wall.litera)     Square(Wall);      // w - wall - �����
	else if (symbol == Floor.litera)    Square(Floor);     // f - floor - ���
	else if (symbol == Box.litera)      Square(Box);       // b - box - ����
	else if (symbol == Pusher.litera)   Square(Pusher);    // p - pusher - ������
	else if (symbol == Location.litera) Square(Location);  // l - location - ����� �����
	else if (symbol == Space.litera)    Square(Space);     //' '- space - ������������ �� �������
	SetConsoleTextAttribute(hConsole, defaultColor);
}

// ������� ���������� ������������� �������
void cursorControl(	int x, int y) {
	COORD  dwCursorPosition;				// ��������� ������� ������� � ������ ������ �������
	dwCursorPosition.X = x;					// X - �������������� ���������� ��� �������� ������� (� 0)
	dwCursorPosition.Y = y;					// Y - ������������ ���������� ��� �������� ������ (� 0)
	SetConsoleCursorPosition(hConsole, dwCursorPosition);	// ������ ������ � ������ �����
}

// ������� ������ �������
size_t helpOutput(void) {

	SetConsoleOutputCP(866);
	printf_s(" ");
	Square(Wall);
	SetConsoleOutputCP(1251);
	printf_s(" - ����� ������, �������� ������\n");

	printf_s(" ");
	Square(Floor);
	printf_s(" - ��� ������, �� ���� ������� ����\n");

	printf_s(" ");
	Square(Location);
	printf_s(" - �����, ���� ��������� ����\n");

	printf_s(" ");
	Square(Box);
	printf_s(" - ����\n");

	printf_s(" ");
	Square(Pusher);
	printf_s(" - ������, ������� 1 ����, ������ �� �����\n");

	printf_s(" ��������� ������� � �������� ����� �� �� �����\n");
	printf_s(" ----------------------------------------------\n");

	return 7;	// ���������� ����� ���������� ��������
}


// ������� �������
int main() {
	bool game = true;						// ���� "������ ���� �����"
	bool helpIsOpen = true;					// ���� "������� �������"
	bool clearScreen = true;				// ���� �� ������� ������
	char byte1char = 0;						// ������ ���� ���� ������� / ������� �������
	char byte2char = 0;						// ������ ���� ���� ������� / ������� �������
	enum keysC {							// ���� ������� ������ (byte1char)
		NL = 10, Enter = 13, ESC = 27, SPACE = 32 };
	enum keys0 {							// ���� ������� ������ (byte2char, byte1char == 0)
		F1 = 59, F2, F3, F4, F5, F6, F7, F8
	};
	enum keysN32 {							// ���� ������� ������ (byte2char � byte1char == N32 == -32)
		N32 = -32, HOME = 71, UP = 72, LEFT = 75, RIGHT = 77, END = 79, DOWN = 80
	};

	const size_t v = 11;		// ���������� �������� �� ��������� (���-�����)
	const size_t h = 15;		// ���������� �������� �� ����������� (���-�� ������� +1)
	size_t currPosPush[2]{ 0 }; // ������� ������� �������
	size_t totalBoxes = 0;		// ������ �����
	size_t boxesInPlace = 0;	// ������ �� �����
	size_t length = h - 1;		// ����� ������
	size_t numLinesHelp = 0;	// ���������� ����� ���������� ��������
	size_t numLinesTitle = 0;	// ���������� ����� ���������� ���������� ����
	size_t numLinesResult = 0;	// ���������� ����� �� ���������� ����

	// ��� ����� ���� ����
	// w - wall - �����
	// f - floor - ���
	// b - box - ����
	// p - pusher - ������
	// l - location - �������������� (����� �������������)
	//' '- space (������) - ������������ �� �������

	char intGamePlan[v][h] = {	// ���� ���������� ����

		{"   wwwwwwwww  "},
		{"   wfffwfffw  "},
		{"   wfffbbbfw  "},
		{"wwwwbbwwfffwww"},
		{"wlllffwffffffw"},
		{"wlllffwpfffbfw"},
		{"wlllffwwwwwbww"},
		{"wwwwfffffffffw"},
		{"   wffwwwfbbfw"},
		{"   wwww wffwww"},
		{"        wwww  "}

	};

	char fixedObjects[v][h]{ '\0' };	// ���� ����������� �������� (���������)
	char mobileObjects[v][h]{ '\0' };	// ���� ��������� �������� (���������)
	char currentPlan[v][h]{ '\0' };		// ������� ������������ ����

	//------------------------------------------------------------------------
	COORD  dwCursorPosition;			// ��������� ������� ������� � ������ ������ �������
	dwCursorPosition.X = 0;				// X - �������������� ���������� ��� �������� ������� (� 0)
	dwCursorPosition.Y = 0;				// Y - ������������ ���������� ��� �������� ������ (� 0)
	CONSOLE_CURSOR_INFO consoleCursorInfo;
	const CONSOLE_CURSOR_INFO* lpConsoleCursorInfo = &consoleCursorInfo;
	PCONSOLE_CURSOR_INFO pConsoleCursorInfo = &consoleCursorInfo;
	GetConsoleCursorInfo(hConsole, pConsoleCursorInfo);	// ������ ������ ������� � ��������� ��������� �� 
														// ���������, ����� �������� ������� ��������� �������
	consoleCursorInfo.bVisible = false;							// ������ "������ �� �����"
	SetConsoleCursorInfo(hConsole, lpConsoleCursorInfo);		// �������� �������� ��������� �������
	//------------------------------------------------------------------------

	system("title ������� 1.0");
	system("mode con cols=50 lines=29");

	while (game)		// ���� ������� ������ ����
	{
		totalBoxes = 0;		// ������ �����
		boxesInPlace = 0;	// ������ �� �����

			// ������ �� ����� ����������� �������
			for (size_t i = 0; i < v; i++) {
				for (size_t j = 0; j < h; j++) {
					if ((intGamePlan[i][j] == Space.litera) ||
						(intGamePlan[i][j] == Wall.litera) ||
						(intGamePlan[i][j] == Floor.litera) ||
						(intGamePlan[i][j] == Location.litera)) {
						fixedObjects[i][j] = intGamePlan[i][j];
					}
					else {
						fixedObjects[i][j] = Floor.litera;
					}
				}
			}

			// ������ �� ����� ��������� �������
			for (size_t i = 0; i < v; i++) {
				for (size_t j = 0; j < h; j++) {
					if ((intGamePlan[i][j] == Box.litera) || (intGamePlan[i][j] == Pusher.litera)) {
						mobileObjects[i][j] = intGamePlan[i][j];
						if (intGamePlan[i][j] == Pusher.litera) {
							currPosPush[0] = i;
							currPosPush[1] = j;
						}
						else if (intGamePlan[i][j] == Box.litera) {
							totalBoxes++;
						}
					}
					else {
						mobileObjects[i][j] = Space.litera;
					}
				}
			}


		// ������ ������� ���� ��� �����
		size_t** posPlacesBoxes = new size_t * [totalBoxes] {0};
		size_t indexPosPlacesBoxes = 0;  // ������ ������� �������

		// �������� ������ ������� ���� ��� ����� ������������
		for (size_t i = 0; i < v; i++) {
			for (size_t j = 0; j < h; j++) {
				if (fixedObjects[i][j] == Location.litera) {
					posPlacesBoxes[indexPosPlacesBoxes] = new size_t[2];
					posPlacesBoxes[indexPosPlacesBoxes][0] = i;
					posPlacesBoxes[indexPosPlacesBoxes][1] = j;
					indexPosPlacesBoxes++;
				}
			}
		}

		//---------------------------------------------------------------------------

		while (true)	// ���� �������� ������ ����
		{
			// ������� ������ � ��������/�������� ������� �� ������� F1
			if (clearScreen) {
				system("cls");
				clearScreen = false;
				if (helpIsOpen) numLinesHelp = helpOutput();
			}
			cursorControl(0, (helpIsOpen ? numLinesHelp : 0));

			// ������ �� ������� ����� ��������� ��������
			for (size_t i = 0; i < v; i++) {
				for (size_t j = 0; j < h; j++) {
					if ((mobileObjects[i][j] == Box.litera) || (mobileObjects[i][j] == Pusher.litera)) {
						currentPlan[i][j] = mobileObjects[i][j];
					}
					else {
						currentPlan[i][j] = fixedObjects[i][j];
					}
				}
			}

			// ����������� ���������� ������ �� �����
			boxesInPlace = 0;
			for (size_t i = 0; i < indexPosPlacesBoxes; i++) {
				if (currentPlan[posPlacesBoxes[i][0]][posPlacesBoxes[i][1]] == Box.litera) {
					boxesInPlace++;
				}
			}

			SetConsoleOutputCP(1251);
			printf_s(" %s\n", (helpIsOpen ? "[F1]-������� �������" : "[F1]-������� �������"));
			printf_s(" [Esc]-����� �� ����, [������]-������ ���� �����\n\n\n");

			printf_s("                  ������ �����: %d\n", totalBoxes);
			printf_s("               ������ �� �����: %d\n", boxesInPlace);

			numLinesTitle = 6;
			SetConsoleOutputCP(866);

			// ����� ���� �� �����
			for (size_t i = 0; i < v; i++) {
				printf_s("         ");
				for (size_t j = 0; j < length; j++) {
					PrintChar(currentPlan[i][j]);
				}
				printf_s("\n");
			}

			// ��������� �� ��������� ����
			if ((totalBoxes) && (totalBoxes == boxesInPlace)) {
				printf_s("\n");
				SetConsoleOutputCP(1251);
				printf_s(" ������ ��������� - ����� ����������� �� ������\n");
				numLinesResult = 1;
				game = false;
			}

			// ��������� ������� ������
 			byte1char = _getch();
			if (_kbhit()) byte2char = _getch();

			if (byte1char == keysC::ESC)		// ������ Esc - ����� �� ����
			{
				delete[] * posPlacesBoxes;		// ������ �������� "����� �� �����" ������
				game = false;
				break;
			}
			else if (byte1char == keysC::SPACE)	// ������ ������ - ������ ����� ����
			{
				delete[] * posPlacesBoxes;		// ������ �������� "����� �� �����" ������
				game = true;
				cursorControl(0, ((helpIsOpen ? numLinesHelp : 0) + numLinesTitle + v + numLinesResult));
				printf_s("%-*c", 49, ' ');
				break;
			}
			else if ((byte1char == 0) && (byte2char == keys0::F1))	// ������ F1 - �������/������� �������
			{
				helpIsOpen = !helpIsOpen;
				clearScreen = true;
			}
			// ������ ������� "�����"
			else if (game && (byte1char == keysN32::N32) && (byte2char == keysN32::UP))
			{
				if ((currPosPush[0] > 0) && (
					(currentPlan[(currPosPush[0] - 1)][currPosPush[1]] == Floor.litera) ||
					(currentPlan[(currPosPush[0] - 1)][currPosPush[1]] == Location.litera)))
				{
					mobileObjects[currPosPush[0]][currPosPush[1]] = Space.litera;
					currPosPush[0]--;
					mobileObjects[currPosPush[0]][currPosPush[1]] = Pusher.litera;
				}
				else if ((currPosPush[0] > 1) &&
					(currentPlan[(currPosPush[0] - 1)][currPosPush[1]] == Box.litera) && (
					(currentPlan[(currPosPush[0] - 2)][currPosPush[1]] == Floor.litera) ||
					(currentPlan[(currPosPush[0] - 2)][currPosPush[1]] == Location.litera)))
				{
					mobileObjects[currPosPush[0]][currPosPush[1]] = Space.litera;
					currPosPush[0]--;
					mobileObjects[currPosPush[0]][currPosPush[1]] = Pusher.litera;
					mobileObjects[(currPosPush[0] - 1)][currPosPush[1]] = Box.litera;
				}
			}
			// ������ ������� "����"
			else if (game && (byte1char == keysN32::N32) && (byte2char == keysN32::DOWN))
			{
				if ((currPosPush[0] < (v - 1)) && (
					(currentPlan[(currPosPush[0] + 1)][currPosPush[1]] == Floor.litera) ||
					(currentPlan[(currPosPush[0] + 1)][currPosPush[1]] == Location.litera)))
				{
					mobileObjects[currPosPush[0]][currPosPush[1]] = Space.litera;
					currPosPush[0]++;
					mobileObjects[currPosPush[0]][currPosPush[1]] = Pusher.litera;
				}
				else if ((currPosPush[0] < (v - 2)) &&
					(currentPlan[(currPosPush[0] + 1)][currPosPush[1]] == Box.litera) && (
						(currentPlan[(currPosPush[0] + 2)][currPosPush[1]] == Floor.litera) ||
						(currentPlan[(currPosPush[0] + 2)][currPosPush[1]] == Location.litera)))
				{
					mobileObjects[currPosPush[0]][currPosPush[1]] = Space.litera;
					currPosPush[0]++;
					mobileObjects[currPosPush[0]][currPosPush[1]] = Pusher.litera;
					mobileObjects[(currPosPush[0] + 1)][currPosPush[1]] = Box.litera;
				}
			}
			// ������ ������� "�����"
			else if (game && (byte1char == keysN32::N32) && (byte2char == keysN32::LEFT))
			{
				if ((currPosPush[1] > 0) && (
					(currentPlan[currPosPush[0]][(currPosPush[1] - 1)] == Floor.litera) ||
					(currentPlan[currPosPush[0]][(currPosPush[1] - 1)] == Location.litera)))
				{
					mobileObjects[currPosPush[0]][currPosPush[1]] = Space.litera;
					currPosPush[1]--;
					mobileObjects[currPosPush[0]][currPosPush[1]] = Pusher.litera;
				}
				else if ((currPosPush[1] > 1) &&
					(currentPlan[currPosPush[0]][(currPosPush[1] - 1)] == Box.litera) && (
						(currentPlan[currPosPush[0]][(currPosPush[1] - 2)] == Floor.litera) ||
						(currentPlan[currPosPush[0]][(currPosPush[1] - 2)] == Location.litera)))
				{
					mobileObjects[currPosPush[0]][currPosPush[1]] = Space.litera;
					currPosPush[1]--;
					mobileObjects[currPosPush[0]][currPosPush[1]] = Pusher.litera;
					mobileObjects[currPosPush[0]][(currPosPush[1] - 1)] = Box.litera;
				}
			}
			// ������ ������� "������"
			else if (game && (byte1char == keysN32::N32) && (byte2char == keysN32::RIGHT))
			{
				if ((currPosPush[1] < (h - 1)) && (
					(currentPlan[currPosPush[0]][(currPosPush[1] + 1)] == Floor.litera) ||
					(currentPlan[currPosPush[0]][(currPosPush[1] + 1)] == Location.litera)))
				{
					mobileObjects[currPosPush[0]][currPosPush[1]] = Space.litera;
					currPosPush[1]++;
					mobileObjects[currPosPush[0]][currPosPush[1]] = Pusher.litera;
				}
				else if ((currPosPush[1] < (h - 2)) &&
					(currentPlan[currPosPush[0]][(currPosPush[1] + 1)] == Box.litera) && (
						(currentPlan[currPosPush[0]][(currPosPush[1] + 2)] == Floor.litera) ||
						(currentPlan[currPosPush[0]][(currPosPush[1] + 2)] == Location.litera)))
				{
					mobileObjects[currPosPush[0]][currPosPush[1]] = Space.litera;
					currPosPush[1]++;
					mobileObjects[currPosPush[0]][currPosPush[1]] = Pusher.litera;
					mobileObjects[currPosPush[0]][(currPosPush[1] + 1)] = Box.litera;
				}
			}
		}
	}
	return 0;
}