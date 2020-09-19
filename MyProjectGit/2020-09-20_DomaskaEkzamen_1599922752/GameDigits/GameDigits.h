// GameDigits.h
#pragma once
#include <iostream>
#include <conio.h>
#include "GameDigits_Table.h"


// ����� ���� �����
class GameDigits {
private:
	Table table;

public:
	// ����������� �� ���������
	GameDigits(){}

	// ����� ������� ����
	void go() {

		//	���� �� �������� ������������ ����
		bool deleteCombinedDigits = false;

		// ���� �� �����/������� �������
		bool showHelp{ true };

		// ���� �� �����/������� ������ ����
		bool showRulesGame{ true };


		char byte1char = 0;	// ������ ���� ���� ������� / ������� �������
		char byte2char = 0;	// ������ ���� ���� ������� / ������� �������
		enum keysC {		// ���� ������� ������ (byte1char)
			NL = 10, Enter = 13, ESC = 27, SPACE = 32
		};
		enum keys0 {		// ���� ������� ������ (byte2char, byte1char == 0)
			F1 = 59, F2, F3, F4, F5, F6, F7, F8
		};
		enum keysN32 {		// ���� ������� ������ (byte2char � byte1char == N32 == -32)
			N32 = -32, UP = 72, LEFT = 75, RIGHT = 77, DOWN = 80,

			CTRL_LEFT = 115, CTRL_RIGHT = 116, CTRL_UP = -115, CTRL_DOWN = -111
		};

		do
		{
			system("cls");
			if (showHelp) help();
			if (showRulesGame) rulesGame();
			std::cout << table << std::endl;

			// ��������� ������� ������
			byte1char = _getch();
			if (_kbhit()) byte2char = _getch();

			// ������ Esc - ����� �� ����
			if (byte1char == keysC::ESC) break;

			// �������� ����� ��������
			// ������������ ����
			else if (deleteCombinedDigits) {
				// ���� ������ Enter - �������
				// ���������� ������������ �����
				// �, ��� �������������, ����� �������
				if (byte1char == keysC::Enter) {
					table.getCaptureDigit().deletingCombinedDigits();
					table.getPathToCapturedDigit().removeMarkPath();
				}
				else {
					// ����� �������� ����
					deleteCombinedDigits = false;
					// � ����� ��������� ���������� ����� � ���� �� ���
					table.getCaptureDigit().deselectCombinedDigit();
					table.getPathToCapturedDigit().removeMarkPath();
				}
			}


			// ������ ������� "�����"
			// - ����� ������� �����
			if ((byte1char == keysN32::N32)
				&& (byte2char == keysN32::UP)
				) {
				table.getCursor().shiftUp();
			}

			// ������ ������� "����"
			// - ����� ������� ����
			else if ((byte1char == keysN32::N32)
				&& (byte2char == keysN32::DOWN)
				) {
				table.getCursor().shiftDown();
			}

			// ������ ������� "�����"
			// - ����� ������� �����
			else if ((byte1char == keysN32::N32)
				&& (byte2char == keysN32::LEFT)
				) {
				table.getCursor().shiftLeft();
			}

			// ������ ������� "������"
			// - ����� ������� ������
			else if ((byte1char == keysN32::N32)
				&& (byte2char == keysN32::RIGHT)
				) {
				table.getCursor().shiftRight();
			}

			// ������ Ctrl+Right (Right - ������� "������")
			// - ������ ������������ ����� ������
			else if ((byte1char == keysN32::N32)
				&& (byte2char == keysN32::CTRL_RIGHT)
				) {
				deleteCombinedDigits =
					table.getCaptureDigit().captureDigitRight();
				if (deleteCombinedDigits) {
					table.getPathToCapturedDigit().setMarkPath();
				}
			}

			// ������ Ctrl+Left (Left - ������� "�����")
			// - ������ ������������ ����� �����
			else if ((byte1char == keysN32::N32)
				&& (byte2char == keysN32::CTRL_LEFT)
				) {
				deleteCombinedDigits =
					table.getCaptureDigit().captureDigitLeft();
				if (deleteCombinedDigits) {
					table.getPathToCapturedDigit().setMarkPath();
				}
			}

			// ������ Ctrl+Down (Down - ������� "����")
			// - ������ ������������ ����� �����
			else if ((byte1char == keysN32::N32)
				&& (byte2char == keysN32::CTRL_DOWN)
				) {
				deleteCombinedDigits =
					table.getCaptureDigit().captureDigitDown();
				if (deleteCombinedDigits) {
					table.getPathToCapturedDigit().setMarkPath();
				}
			}

			// ������ Ctrl+Up (Up - ������� "�����")
			// - ������ ������������ ����� ������
			else if ((byte1char == keysN32::N32)
				&& (byte2char == keysN32::CTRL_UP)
				) {
				deleteCombinedDigits =
					table.getCaptureDigit().captureDigitUp();
				if (deleteCombinedDigits) {
					table.getPathToCapturedDigit().setMarkPath();
				}
			}

			// ������ F1 - ����� / ������� �������
			else if ((byte1char == 0)
				&& (byte2char == keys0::F1)
				) {
				showHelp = !showHelp;
			}

			// ������ F2 - ����� / ������� ������ ����
			else if ((byte1char == 0)
				&& (byte2char == keys0::F2)
				) {
				showRulesGame = !showRulesGame;
			}

			// ������ F4 - ������������� �������
			else if ((byte1char == 0)
				&& (byte2char == keys0::F4)
				) {
				table.transformTable();
			}

		} while (true);
	}

	// ����� ������ �� ����� �������
	void help() const {

		std::cout
			<< "                 ���� \"�����\" - ����� ��� �����!\n"
			<< " ��������� ���� ������������ ���� - ������ ��� ������ ������ 10\n"
			<< " [Esc]-����� �� ���������          [F1]-��������/������ �������\n"
			<< " [F2]-��������/������ ������� ����\n"
			<< " �������: [������],[�����],[�����],[����]-�������� �������\n"
			<< " [Ctrl]+[�������]-������ ������������ ����� � ����������� �������\n"
			<< " ����� [Ctrl]+[�������] - [Enter]-������� ���������� �����\n"
			<< "                        - ����� ������ ������� - ������ �������\n"
			<< " [F4]-������������� ������� - ��������� ���������� ���� � �����\n"
			<< std::endl;
	}

	// ����� ������ �� ����� ������ ����
	void rulesGame() const {
		std::cout 
		<< "                           ������� ����\n"
		<< " 1.�� ����� ������ ������� ����� �����	�� 1 �� 19, ����� 10\n"
		<< " (1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 13, 14, 15, 16, 17, 18, 19),\n"
		<< " � ������� ������� 9 ����:\n"
		<< "                             123456789\n"
		<< "                             111213141\n"
		<< "                             516171819\n"
		<< "\n"
		<< " 2.��������� � ��������� ���� ��������� �������� ���������� ����.\n"
		<< " ���������� ��������� ������� ������������ ��������������� ��������:\n"
		<< " 1) ���������� �����, ������, ������, �����;\n"
		<< " 2) ���������, ������������� �����, ������, ������, �����\n"
		<< " � ����������� ������ �������� �������.\n"
		<< " ����� ���������� ��������� ������� �������� ��������� ���������\n"
		<< " ����� ������ � ������ ��������� ����� ��������� ������ (�������\n"
		<< " ��������� ����� - ������).\n"
		<< " ����� ����������, ����:\n"
		<< " 1) ��� ����� (1=1, 2=2, 3=3, 4=4, 5=5, 6=6, 7=7, 8=8, 9=9);\n"
		<< " 2) ����� ���� ����� 10 (1+9, 2+8, 3+7, 4+6, 5+5).\n"
		<< "\n"
		<< " 3.����� ��� ���� ���������� ���� ������, ���������� ���������\n"
		<< " ����� ������������ � ������� (������� 9 ����), ����� �����\n"
		<< " ��������� ��������� ����� �����. � ���� ������������ ������.\n"
		<< " ������:\n"
		<< " �� ����������:\n"
		<< "                             _234567__\n"
		<< "                             ____1314_\n"
		<< "                             5_617181_\n"
		<< " ����� ����������:\n"
		<< "                             _234567__\n"
		<< "                             ____1314_\n"
		<< "                             5_617181_\n"
		<< "                             234567131\n"
		<< "                             45617181\n"
		<< "\n"
		<< " 4.���� ���� - ������� ��� �����.\n"
		<< std::endl;
	}





};
// ����� ������ ���� �����
