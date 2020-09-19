// GameDigits_Table.h
#pragma once
#include <iostream>
#include "GameDigits_Table_Massif.h"
#include "GameDigits_Table_Focus.h"


// ����� �������
class Table {
private:
	// ������ ����
	Massif massif;

	// ������ ��� massif
	Cursor cursor{ massif };

	// ������ ��� ������� � ��������
	// ������������ �����
	CaptureDigit captureDigit{ massif, cursor };

	// ������ ��� ����������� ����
	// �� ������� �� ����������� �����
	// ����� ����� ���� ������� �����
	PathToCapturedDigit pathToCapturedDigit
	{ massif, cursor, captureDigit };

	// ������ ��� �������� ���������
	// ��������� ����� ����� ��������� �������
	// (����� ��� ����� ������������ ����� �����
	// ��� ������������� �������)
	LastDigitInTable lastDigitInTable{ massif };

	// ������� �������� ��������� ������� ����
	Massif start() {
		Massif massif(3);

		massif[0][0].getDigit().setD1();
		massif[0][1].getDigit().setD2();
		massif[0][2].getDigit().setD3();
		massif[0][3].getDigit().setD4();
		massif[0][4].getDigit().setD5();
		massif[0][5].getDigit().setD6();
		massif[0][6].getDigit().setD7();
		massif[0][7].getDigit().setD8();
		massif[0][8].getDigit().setD9();

		massif[1][0].getDigit().setD1();
		massif[1][1].getDigit().setD1();
		massif[1][2].getDigit().setD1();
		massif[1][3].getDigit().setD2();
		massif[1][4].getDigit().setD1();
		massif[1][5].getDigit().setD3();
		massif[1][6].getDigit().setD1();
		massif[1][7].getDigit().setD4();
		massif[1][8].getDigit().setD1();

		massif[2][0].getDigit().setD5();
		massif[2][1].getDigit().setD1();
		massif[2][2].getDigit().setD6();
		massif[2][3].getDigit().setD1();
		massif[2][4].getDigit().setD7();
		massif[2][5].getDigit().setD1();
		massif[2][6].getDigit().setD8();
		massif[2][7].getDigit().setD1();
		massif[2][8].getDigit().setD9();

		return massif;
	}

public:

	// ����������� �� ���������
	Table() {
		massif = start();
		cursor.here();
		lastDigitInTable.findCoordinates();
	}

	// ����� ����������������� �������
	void transformTable() {
		cursor.noHere();
		massif = createTransformedTable(massif);
		cursor.here();
		lastDigitInTable.findCoordinates();
	}

	// ����� �������� ������������������ �������
	Massif createTransformedTable(Massif& massif) {

		// ������ ������ �������
		size_t sizeNewMassif{ 0 };
	
		// ������� ������ ������������� �������
		sizeNewMassif += massif.getSize();

		// ��������� ���������� �����������
		// � ����� ������ ����:

		// ������ ��� �������� ���� � �������
		MethodsForTransformTable transformer(massif);
		// ���������� ������������ ����
		size_t numberOfDigitsToAdd =
			transformer.findNumberOfDigits();

		// ������������ ���������� ����, �������
		// ����� �������� � ��������� ������
		// ������������ �������
		size_t maxNumDigitsInLastRow =
			massif.maxIndexCol - lastDigitInTable.getCol();

		// ��������� ���������� ����������� � ������� �����:

		// ���������� ����������� �����
		size_t numberOfRowToAdd{ 0 };

		// ���� ������������ � ��������� � ��������� ������
		// ���������� ���� ������ ��� ����� ����������
		// ��������� � ������������ ������� ����
		if (maxNumDigitsInLastRow >= numberOfDigitsToAdd) {
			// ���������� ����������� ����� ����� 0
			numberOfRowToAdd = 0;
		}
		else {			// �����
			// �������� ���������� ������������ ����
			// �� ���������� ������������ � ���������
			// ������ ������������ �������
			numberOfDigitsToAdd -= maxNumDigitsInLastRow;

			// ������ ���������� ����������� �����
			// ��� ���������� ���������� ������������ ����

			// ���� ������� �������������� �������
			// ���������� ������������ ����
			// �� ����� ������ �������
			// �� ����� 0,
			// ���������� ����������� ����� �����:
			if (numberOfDigitsToAdd % massif.getRowLength()) {

				numberOfRowToAdd = 1 +
					numberOfDigitsToAdd / massif.getRowLength();
			}
			else {		// �����, �����:
				numberOfRowToAdd = 
					numberOfDigitsToAdd / massif.getRowLength();
			}
		}

		// �������� ������ ������ ������� �� ������������
		// ���������� ����������� �����
		sizeNewMassif += numberOfRowToAdd;

		// �������� ����� ������
		Massif newMassif(sizeNewMassif);

		// ��������� �������� �� ������������� �������
		// � ����� ������
		for (size_t row = 0; row < massif.getSize(); row++) {
			for (size_t col = 0; col < massif.getRowLength(); col++) {
				newMassif[row][col] = massif[row][col];
			}
		}

		// ������� ��������� ��������� ������
		// ��� ������ outNextDigit()
		transformer.setRow(0);
		transformer.setCol(0);

		// ������� ����� �� ������ ������������� ������� �
		// ����� ��������� ���������� ������ ������ �������
		for (
			size_t row = lastDigitInTable.getRow(),
			col = lastDigitInTable.getCol() + 1;
			col < massif.getRowLength();
			col++
			) {
			newMassif[row][col] = transformer.outNextDigit();
		}

		// ������� ���������� ����� �� ������������� �������
		// � ����������� ������ ������ �������
		for (
			size_t row = lastDigitInTable.getRow() + 1;
			row < newMassif.getSize();
			row++
			) {
			for (
				size_t col = 0;
				col < newMassif.getRowLength();
				col++
				) {
				newMassif[row][col] = transformer.outNextDigit();
			}
		}
		// ������ ������ �������
		return newMassif;
	}

	// ����� �������� ������� ������
	Cursor& getCursor() { return cursor; }

	// ����� �������� ������� ������ �����
	CaptureDigit& getCaptureDigit() {
		return captureDigit;
	}

	// ����� �������� ������� ���� �� ����������� �����
	PathToCapturedDigit& getPathToCapturedDigit() {
		return pathToCapturedDigit;
	}

	// ���������� ������������� ������� ���������� ��������� <<
	// - ����� ������� �� �����
	friend std::ostream& operator<<(
		std::ostream& out, const Table& table
		) {
		out << table.massif;
		return out;
	}
};
// ����� ������ �������


