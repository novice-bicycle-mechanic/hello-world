// GameDigits.h
#pragma once
#include <iostream>
#include <conio.h>
#include "GameDigits_Table.h"


// КЛАСС Игра Цифры
class GameDigits {
private:
	Table table;

public:
	// КОНСТРУКТОР по умолчанию
	GameDigits(){}

	// МЕТОД ведения игры
	void go() {

		//	ключ на удаление сочетающихся цифр
		bool deleteCombinedDigits = false;

		// ключ на показ/скрытие справки
		bool showHelp{ true };

		// ключ на показ/скрытие правил игры
		bool showRulesGame{ true };


		char byte1char = 0;	// первый байт кода символа / нажатия клавиши
		char byte2char = 0;	// второй байт кода символа / нажатия клавиши
		enum keysC {		// коды нажатий клавиш (byte1char)
			NL = 10, Enter = 13, ESC = 27, SPACE = 32
		};
		enum keys0 {		// коды нажатий клавиш (byte2char, byte1char == 0)
			F1 = 59, F2, F3, F4, F5, F6, F7, F8
		};
		enum keysN32 {		// коды нажатий клавиш (byte2char и byte1char == N32 == -32)
			N32 = -32, UP = 72, LEFT = 75, RIGHT = 77, DOWN = 80,

			CTRL_LEFT = 115, CTRL_RIGHT = 116, CTRL_UP = -115, CTRL_DOWN = -111
		};

		do
		{
			system("cls");
			if (showHelp) help();
			if (showRulesGame) rulesGame();
			std::cout << table << std::endl;

			// обработка нажатий клавиш
			byte1char = _getch();
			if (_kbhit()) byte2char = _getch();

			// нажато Esc - выход из игры
			if (byte1char == keysC::ESC) break;

			// Проверка ключа удаления
			// сочетающихся цифр
			else if (deleteCombinedDigits) {
				// если нажато Enter - удалить
				// выделенные сочетающиеся цифры
				// и, при необходимости, сжать таблицу
				if (byte1char == keysC::Enter) {
					table.getCaptureDigit().deletingCombinedDigits();
					table.getPathToCapturedDigit().removeMarkPath();
				}
				else {
					// иначе обнулить ключ
					deleteCombinedDigits = false;
					// и снять выделение сочетаемой цифры и пути до нее
					table.getCaptureDigit().deselectCombinedDigit();
					table.getPathToCapturedDigit().removeMarkPath();
				}
			}


			// нажата стрелка "вверх"
			// - сдвиг курсора ВВЕРХ
			if ((byte1char == keysN32::N32)
				&& (byte2char == keysN32::UP)
				) {
				table.getCursor().shiftUp();
			}

			// нажата стрелка "вниз"
			// - сдвиг курсора ВНИЗ
			else if ((byte1char == keysN32::N32)
				&& (byte2char == keysN32::DOWN)
				) {
				table.getCursor().shiftDown();
			}

			// нажата стрелка "влево"
			// - сдвиг курсора ВЛЕВО
			else if ((byte1char == keysN32::N32)
				&& (byte2char == keysN32::LEFT)
				) {
				table.getCursor().shiftLeft();
			}

			// нажата стрелка "вправо"
			// - сдвиг курсора ВПРАВО
			else if ((byte1char == keysN32::N32)
				&& (byte2char == keysN32::RIGHT)
				) {
				table.getCursor().shiftRight();
			}

			// нажаты Ctrl+Right (Right - стрелка "вправо")
			// - захват сочетающейся цифры СПРАВА
			else if ((byte1char == keysN32::N32)
				&& (byte2char == keysN32::CTRL_RIGHT)
				) {
				deleteCombinedDigits =
					table.getCaptureDigit().captureDigitRight();
				if (deleteCombinedDigits) {
					table.getPathToCapturedDigit().setMarkPath();
				}
			}

			// нажаты Ctrl+Left (Left - стрелка "влево")
			// - захват сочетающейся цифры СЛЕВА
			else if ((byte1char == keysN32::N32)
				&& (byte2char == keysN32::CTRL_LEFT)
				) {
				deleteCombinedDigits =
					table.getCaptureDigit().captureDigitLeft();
				if (deleteCombinedDigits) {
					table.getPathToCapturedDigit().setMarkPath();
				}
			}

			// нажаты Ctrl+Down (Down - стрелка "вниз")
			// - захват сочетающейся цифры СНИЗУ
			else if ((byte1char == keysN32::N32)
				&& (byte2char == keysN32::CTRL_DOWN)
				) {
				deleteCombinedDigits =
					table.getCaptureDigit().captureDigitDown();
				if (deleteCombinedDigits) {
					table.getPathToCapturedDigit().setMarkPath();
				}
			}

			// нажаты Ctrl+Up (Up - стрелка "вверх")
			// - захват сочетающейся цифры СВЕРХУ
			else if ((byte1char == keysN32::N32)
				&& (byte2char == keysN32::CTRL_UP)
				) {
				deleteCombinedDigits =
					table.getCaptureDigit().captureDigitUp();
				if (deleteCombinedDigits) {
					table.getPathToCapturedDigit().setMarkPath();
				}
			}

			// нажата F1 - показ / скрытие справки
			else if ((byte1char == 0)
				&& (byte2char == keys0::F1)
				) {
				showHelp = !showHelp;
			}

			// нажата F2 - показ / скрытие правил игры
			else if ((byte1char == 0)
				&& (byte2char == keys0::F2)
				) {
				showRulesGame = !showRulesGame;
			}

			// нажата F4 - трансформация таблицы
			else if ((byte1char == 0)
				&& (byte2char == keys0::F4)
				) {
				table.transformTable();
			}

		} while (true);
	}

	// МЕТОД вывода на экран справки
	void help() const {

		std::cout
			<< "                 Игра \"Цифры\" - удали все цифры!\n"
			<< " Удаляются пары сочетающихся цифр - равных или суммой равных 10\n"
			<< " [Esc]-выход из программы          [F1]-показать/скрыть справку\n"
			<< " [F2]-показать/скрыть правила игры\n"
			<< " Стрелки: [Вправо],[Влево],[Вверх],[Вниз]-движение курсора\n"
			<< " [Ctrl]+[Стрелка]-захват сочетающейся цифры в направлении стрелки\n"
			<< " после [Ctrl]+[Стрелка] - [Enter]-удалить выделенные цифры\n"
			<< "                        - любое другое нажатие - отмена захвата\n"
			<< " [F4]-трансформация таблицы - дописание оставшихся цифр в конец\n"
			<< std::endl;
	}

	// МЕТОД вывода на экран правил игры
	void rulesGame() const {
		std::cout 
		<< "                           Правила игры\n"
		<< " 1.На листе бумаги пишутся цифры чисел	от 1 по 19, кроме 10\n"
		<< " (1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 13, 14, 15, 16, 17, 18, 19),\n"
		<< " в таблицу шириной 9 цифр:\n"
		<< "                             123456789\n"
		<< "                             111213141\n"
		<< "                             516171819\n"
		<< "\n"
		<< " 2.Находятся и стираются пары ближайших соседних сочетаемых цифр.\n"
		<< " Ближайшими соседними цифрами относительно рассматриваемой являются:\n"
		<< " 1) граничащие слева, справа, сверху, снизу;\n"
		<< " 2) ближайшие, расположенные слева, справа, сверху, снизу\n"
		<< " и разделенные только стертыми цифрами.\n"
		<< " Также ближайшими соседними цифрами являются последняя нестертая\n"
		<< " цифра строки и первая нестертая цифра следующей строки (вариант\n"
		<< " соседства слева - справа).\n"
		<< " Цифры сочетаются, если:\n"
		<< " 1) они равны (1=1, 2=2, 3=3, 4=4, 5=5, 6=6, 7=7, 8=8, 9=9);\n"
		<< " 2) сумма цифр равна 10 (1+9, 2+8, 3+7, 4+6, 5+5).\n"
		<< "\n"
		<< " 3.Когда все пары сочетаемых цифр стерты, оставшиеся нестертые\n"
		<< " цифры дописываются в таблицу (шириной 9 цифр), сразу после\n"
		<< " последней имеющейся ранее цифры. И игра продолжается дальше.\n"
		<< " Пример:\n"
		<< " до добавления:\n"
		<< "                             _234567__\n"
		<< "                             ____1314_\n"
		<< "                             5_617181_\n"
		<< " после добавления:\n"
		<< "                             _234567__\n"
		<< "                             ____1314_\n"
		<< "                             5_617181_\n"
		<< "                             234567131\n"
		<< "                             45617181\n"
		<< "\n"
		<< " 4.Цель игры - стереть все цифры.\n"
		<< std::endl;
	}





};
// Конец КЛАССА Игра Цифры
