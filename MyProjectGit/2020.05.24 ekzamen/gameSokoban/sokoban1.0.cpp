// игра сокобан
#include <Windows.h>
#include <conio.h>
#include <stdio.h>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
WORD defaultColor = 0x0007;		// цвет фона и символов по умолчанию

// структура описания единицы изображения игры - квадратного пикселя
struct Pixel {
	char litera = '\0';			// буква-литерал типа пикселя
	WORD palette = 0x0000;		// палитра - смотри ниже
	int frame = 0;				// рамка квадрата: 0-нет, 1-по краям, -1 - и середине
	char left = ' ';			// левый символ квадрата
	char right = ' ';			// правый символ квадрата
};

Pixel Wall     = { 'w', 0x0080, -1, '\xC5', '\xC5' };  // w - wall - стена
Pixel Floor    = { 'f', 0x0078, 1, ' ', ' ' };		   // f - floor - пол
Pixel Box      = { 'b', 0x00e0, 1, ' ', ' ' };		   // b - box - ящик
Pixel Pusher   = { 'p', 0x0020, 1, ' ', ' ' };		   // p - pusher - толкач
Pixel Location = { 'l', 0x007c, 1, ' ', ' ' };		   // l - location - местоположение (ящика, окончательное)
Pixel Space    = { ' ', 0x0000, 1, ' ', ' ' };		   //' '- space (пробел) - пространство за стенами

// Функция печати квадрата - пикселя плана изображения
void Square(Pixel pixel) {
	// палитра - совокупность цветов фона и текста,
	// и элементов рамки одного символа - половины квадрата,
	// и режимов задания цвета
	// код - 16-тиричное число 0xbbbb, b - 16-разрядный бит (0-9,a-f)
	// 0x***b - цвет текста, (0-7)-обычный, (8-f)-интенсивные (0-7)
	// 0x**b* - цвет фона, (0-7)-обычный, (8-f)-интенсивные (0-7)
	// 0xbb** - части рамки: 04-сверху, 80-снизу, 08-слева, 10-справа;
	// 0xbb** - режим: 40-поменять цвет фона на цвет текста, и наоборот;
	// 0xbb** - режим: 01-начать задание цвета, 02-закончить
	// коды режимов, обрамления и цветов можно суммировать,
	// кроме 0x0100 и 0x0200

	if (pixel.frame) pixel.palette += 0x9c00;  // + 0x0400 + 0x8000 + 0x0800 + 0x1000 <-- рамки;
	SetConsoleTextAttribute(hConsole, 0x0100);
	SetConsoleTextAttribute(hConsole, (pixel.palette - ((pixel.frame > 0) ? 0x1000 : 0)));
	printf_s("%c", pixel.left);
	SetConsoleTextAttribute(hConsole, (pixel.palette - ((pixel.frame > 0) ? 0x0800 : 0)));
	printf_s("%c", pixel.right);
	SetConsoleTextAttribute(hConsole, 0x0200);
	SetConsoleTextAttribute(hConsole, defaultColor);
}

// Функция печати одного символа плана игры на экране
void PrintChar(char symbol) {       // символ - код типа выводимого квадрата
	     if (symbol == Wall.litera)     Square(Wall);      // w - wall - стена
	else if (symbol == Floor.litera)    Square(Floor);     // f - floor - пол
	else if (symbol == Box.litera)      Square(Box);       // b - box - ящик
	else if (symbol == Pusher.litera)   Square(Pusher);    // p - pusher - толкач
	else if (symbol == Location.litera) Square(Location);  // l - location - место ящика
	else if (symbol == Space.litera)    Square(Space);     //' '- space - пространство за стенами
	SetConsoleTextAttribute(hConsole, defaultColor);
}

// Функция управления расположением курсора
void cursorControl(	int x, int y) {
	COORD  dwCursorPosition;				// структура позиции курсора в буфере экрана консоли
	dwCursorPosition.X = x;					// X - Горизонтальная координата или значение столбца (с 0)
	dwCursorPosition.Y = y;					// Y - Вертикальная координата или значение строки (с 0)
	SetConsoleCursorPosition(hConsole, dwCursorPosition);	// ставим курсор в начале плана
}

// Функция вывода справки
size_t helpOutput(void) {

	SetConsoleOutputCP(866);
	printf_s(" ");
	Square(Wall);
	SetConsoleOutputCP(1251);
	printf_s(" - стена склада, сдвинуть нельзя\n");

	printf_s(" ");
	Square(Floor);
	printf_s(" - пол склада, по нему толкают ящик\n");

	printf_s(" ");
	Square(Location);
	printf_s(" - место, куда затолкать ящик\n");

	printf_s(" ");
	Square(Box);
	printf_s(" - ящик\n");

	printf_s(" ");
	Square(Pusher);
	printf_s(" - толкач, толкает 1 ящик, тянуть не может\n");

	printf_s(" Нажимайте стрелки и толкайте ящики на их места\n");
	printf_s(" ----------------------------------------------\n");

	return 7;	// количество строк занимаемых справкой
}


// ГЛАВНАЯ ФУНКЦИЯ
int main() {
	bool game = true;						// ключ "начать игру снова"
	bool helpIsOpen = true;					// ключ "справка открыта"
	bool clearScreen = true;				// ключ на очистку экрана
	char byte1char = 0;						// первый байт кода символа / нажатия клавиши
	char byte2char = 0;						// второй байт кода символа / нажатия клавиши
	enum keysC {							// коды нажатий клавиш (byte1char)
		NL = 10, Enter = 13, ESC = 27, SPACE = 32 };
	enum keys0 {							// коды нажатий клавиш (byte2char, byte1char == 0)
		F1 = 59, F2, F3, F4, F5, F6, F7, F8
	};
	enum keysN32 {							// коды нажатий клавиш (byte2char и byte1char == N32 == -32)
		N32 = -32, HOME = 71, UP = 72, LEFT = 75, RIGHT = 77, END = 79, DOWN = 80
	};

	const size_t v = 11;		// количество символов по вертикали (кол-строк)
	const size_t h = 15;		// количество символов по горизонтали (кол-во колонок +1)
	size_t currPosPush[2]{ 0 }; // текущая позиция толкача
	size_t totalBoxes = 0;		// ящиков всего
	size_t boxesInPlace = 0;	// ящиков на месте
	size_t length = h - 1;		// длина строки
	size_t numLinesHelp = 0;	// количество строк занимаемых справкой
	size_t numLinesTitle = 0;	// количество строк занимаемых заголовком игры
	size_t numLinesResult = 0;	// количество строк до результата игры

	// для плана игры ниже
	// w - wall - стена
	// f - floor - пол
	// b - box - ящик
	// p - pusher - толкач
	// l - location - местоположение (ящика окончательное)
	//' '- space (пробел) - пространство за стенами

	char intGamePlan[v][h] = {	// план внутренней игры

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

	char fixedObjects[v][h]{ '\0' };	// план неподвижных объектов (квадратов)
	char mobileObjects[v][h]{ '\0' };	// план подвижных объектов (квадратов)
	char currentPlan[v][h]{ '\0' };		// текущий объединенный план

	//------------------------------------------------------------------------
	COORD  dwCursorPosition;			// структура позиции курсора в буфере экрана консоли
	dwCursorPosition.X = 0;				// X - Горизонтальная координата или значение столбца (с 0)
	dwCursorPosition.Y = 0;				// Y - Вертикальная координата или значение строки (с 0)
	CONSOLE_CURSOR_INFO consoleCursorInfo;
	const CONSOLE_CURSOR_INFO* lpConsoleCursorInfo = &consoleCursorInfo;
	PCONSOLE_CURSOR_INFO pConsoleCursorInfo = &consoleCursorInfo;
	GetConsoleCursorInfo(hConsole, pConsoleCursorInfo);	// задаем размер курсора в структуре значением по 
														// умолчанию, чтобы работала функция видимости курсора
	consoleCursorInfo.bVisible = false;							// задаем "курсор не видим"
	SetConsoleCursorInfo(hConsole, lpConsoleCursorInfo);		// включаем заданную видимость курсора
	//------------------------------------------------------------------------

	system("title Сокобан 1.0");
	system("mode con cols=50 lines=29");

	while (game)		// цикл запуска сеанса игры
	{
		totalBoxes = 0;		// ящиков всего
		boxesInPlace = 0;	// ящиков на месте

			// укажем на плане неподвижные объекты
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

			// укажем на плане подвижные объекты
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


		// массив позиций мест под ящики
		size_t** posPlacesBoxes = new size_t * [totalBoxes] {0};
		size_t indexPosPlacesBoxes = 0;  // индекс массива позиций

		// заполним массив позиций мест под ящики координатами
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

		while (true)	// цикл текущего сеанса игры
		{
			// очистка экрана и открытие/закрытие справки по нажатию F1
			if (clearScreen) {
				system("cls");
				clearScreen = false;
				if (helpIsOpen) numLinesHelp = helpOutput();
			}
			cursorControl(0, (helpIsOpen ? numLinesHelp : 0));

			// укажем на текущем плане положение объектов
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

			// определение количества ящиков на месте
			boxesInPlace = 0;
			for (size_t i = 0; i < indexPosPlacesBoxes; i++) {
				if (currentPlan[posPlacesBoxes[i][0]][posPlacesBoxes[i][1]] == Box.litera) {
					boxesInPlace++;
				}
			}

			SetConsoleOutputCP(1251);
			printf_s(" %s\n", (helpIsOpen ? "[F1]-закрыть справку" : "[F1]-открыть справку"));
			printf_s(" [Esc]-выход из игры, [Пробел]-начать игру снова\n\n\n");

			printf_s("                  Ящиков всего: %d\n", totalBoxes);
			printf_s("               Ящиков на месте: %d\n", boxesInPlace);

			numLinesTitle = 6;
			SetConsoleOutputCP(866);

			// вывод игры на экран
			for (size_t i = 0; i < v; i++) {
				printf_s("         ");
				for (size_t j = 0; j < length; j++) {
					PrintChar(currentPlan[i][j]);
				}
				printf_s("\n");
			}

			// сообщении об окончании игры
			if ((totalBoxes) && (totalBoxes == boxesInPlace)) {
				printf_s("\n");
				SetConsoleOutputCP(1251);
				printf_s(" Миссия выполнена - ящики расставлены по местам\n");
				numLinesResult = 1;
				game = false;
			}

			// обработка нажатий клавиш
 			byte1char = _getch();
			if (_kbhit()) byte2char = _getch();

			if (byte1char == keysC::ESC)		// нажато Esc - выход из игры
			{
				delete[] * posPlacesBoxes;		// массив сигналов "Ящики на месте" удален
				game = false;
				break;
			}
			else if (byte1char == keysC::SPACE)	// нажато ПРОБЕЛ - начать новую игру
			{
				delete[] * posPlacesBoxes;		// массив сигналов "Ящики на месте" удален
				game = true;
				cursorControl(0, ((helpIsOpen ? numLinesHelp : 0) + numLinesTitle + v + numLinesResult));
				printf_s("%-*c", 49, ' ');
				break;
			}
			else if ((byte1char == 0) && (byte2char == keys0::F1))	// нажато F1 - закрыть/открыть справку
			{
				helpIsOpen = !helpIsOpen;
				clearScreen = true;
			}
			// нажата стрелка "вверх"
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
			// нажата стрелка "вниз"
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
			// нажата стрелка "влево"
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
			// нажата стрелка "вправо"
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