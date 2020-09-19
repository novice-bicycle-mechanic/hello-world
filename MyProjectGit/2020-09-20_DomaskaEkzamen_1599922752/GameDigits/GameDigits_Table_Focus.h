// GameDigits_Table_Focus.h
/*
����� ���������� ������ ��� ������ Table (�������):
1. Focus (�����)
   - ������������ ����� ��� ��������� ���� �������.
   ������������ ����������� ����� ������ �� �������.
   ���������������� �������� ������ Massif.
   ������ ������ Focus � ������� �� ���������.
   ��� ����������� �� ������� - ����� �������� ������.

2. Cursor (������)
   - �������� ����� ��� ������ Focus.
   ������������ ��������� ����������������� �������
   � ��� ����������� �� �������.
   ���������������� �������� ������ Massif.
   ������ ������ Cursor ���������
   � ������ Table (�������).

3. CaptureDigit (������ �����)
   - �������� ����� ��� ������ Focus.
   ������������ ������ � ��������� �����,
   ���������� � ������ ��� ��������.
   ���������������� ��������� �������
   Massif � Cursor.
   ������ ������ CaptureDigit ���������
   � ������ Table (�������).

4. PathToCapturedDigit (���� �� ����������� �����)
   - �������� ����� ��� ������ Focus.
   ������������ ��������� ������� �� �������� �������
   ����� �������� � ����������� ������.
   ���������������� ��������� �������
   Massif, Cursor, CaptureDigit.
   ������ ������ PathToCapturedDigit ���������
   � ������ Table (�������).

5. LastDigitInTable (��������� ����� � �������)
   - �������� ����� ��� ������ Focus.
   ������ ���������� ��������� ����� �������.
   ����� ��� ����� ������������ ����� �����
   ��� ������������� �������.
   ���������������� �������� ������ Massif.
   ������ ������ LastDigitInTable ���������
   � ������ Table (�������).

6. MethodsForTransformTable
   (������ ��� ������������� �������)
   - �������� ����� ��� ������ Focus.
   �������� ������ ��� ������������� ������.
   ���������������� �������� ������ Massif.
   ������ ������ MethodsForTransformTable ���������
   � ������ createTransformedTable()
   ������ Table (�������).

*/
#pragma once


// ����� ����� (��� ������� ���� Massif)
// ��� ��������� ������ ������
class Focus {
protected:

	// ������������ ��������������� ���������
	// ������� focus = { ROW, COL } � ��� ��������.
	// ROW-����� ������ � ������� Massif,
	// COL-����� ������� � ������� Massif,
	// TOTAL-����� ��������� � ������� focus.
	enum : size_t { ROW, COL, TOTAL };

	// ������ ��������� { ROW,COL }
	// ����� ������ � Massif::massif
	size_t focus[TOTAL] = { 0,0 };

	// ������ �� �������������� ������
	Massif& massif;

public:
	// ����������� � ����������
	Focus(Massif& object) : massif(object) {}

	// ����� ������� ��� ������ ��������
	// ���������� ROW - ����� ������
	void setRow(size_t row) { focus[ROW] = row; }

	// ����� ������� ��� ������ ��������
	// ���������� COL - ����� �������/�������
	void setCol(size_t col) { focus[COL] = col; }

	// ����� �������� �� ������ ��������
	// ���������� ROW - ����� ������
	size_t getRow() const { return focus[ROW]; }

	// ����� �������� �� ������ ��������
	// ���������� COL - ����� �������/�������
	size_t getCol() const { return focus[COL]; }

	// ����� ������ ������ �� ���� ������� ������
	bool focusShiftRight() {
		// ��������, ��� ����� � ��������� �������
		if (focus[COL] == massif.maxIndexCol) {
			// ��������, ��� ����� � ��������� ������
			if (focus[ROW] == massif.maxIndexRow) {
				return false;
			}
			else {
				focus[COL] = 0;
				focus[ROW] += 1;
			}
		}
		else focus[COL] += 1;

		return true;
	}

	// ����� ������ ������ �� ���� ������� �����
	bool focusShiftLeft() {
		// ��������, ��� ����� � ������ �������
		if (focus[COL] == 0) {
			// ��������, ��� ����� � ������ ������
			if (focus[ROW] == 0) return false;
			else {
				focus[COL] = massif.maxIndexCol;
				focus[ROW] -= 1;
			}
		}
		else focus[COL] -= 1;

		return true;
	}

	// ����� ������ ������ �� ���� ������� ����
	bool focusShiftDown() {
		// ��������, ��� ����� � ��������� ������
		if (focus[ROW] == massif.maxIndexRow) {
			return false;
		}
		else focus[ROW] += 1;

		return true;
	}

	// ����� ������ ������ �� ���� ������� �����
	bool focusShiftUp() {
		// ��������, ��� ����� � ������ ������
		if (focus[ROW] == 0) return false;
		else focus[ROW] -= 1;

		return true;
	}
};
// ����� ������ �����

//-----------------------------------------

// ����� ������
// - ��������� ������ �����
class Cursor : public Focus {
public:
	// ����������� � ����������
	Cursor(Massif& object) : Focus(object) {}

	// ����� ����������� ������� �������
	void here() {
		massif[focus[ROW]][focus[COL]] = true;
	}

	// ����� �������� ������� �������
	void noHere() {
		massif[focus[ROW]][focus[COL]] = false;
	}

	// ����� ������ ������� �� ���� ������� ������
	void shiftRight() {
		massif[focus[ROW]][focus[COL]] = false;
		focusShiftRight();
		massif[focus[ROW]][focus[COL]] = true;
	}

	// ����� ������ ������� �� ���� ������� �����
	void shiftLeft() {
		massif[focus[ROW]][focus[COL]] = false;
		focusShiftLeft();
		massif[focus[ROW]][focus[COL]] = true;
	}

	// ����� ������ ������� �� ���� ������� ����
	void shiftDown() {
		massif[focus[ROW]][focus[COL]] = false;
		focusShiftDown();
		massif[focus[ROW]][focus[COL]] = true;
	}

	// ����� ������ ������� �� ���� ������� �����
	void shiftUp() {
		massif[focus[ROW]][focus[COL]] = false;
		focusShiftUp();
		massif[focus[ROW]][focus[COL]] = true;
	}
};
// ����� ������ ������

//-----------------------------------------

// ����� ������ �����
// - ��������� ������ �����
class CaptureDigit : public Focus {
private:
	// ���������� ������� { ROW,COL }
	Cursor& cursor;

	// ��������� �� ����� focusShiftRight()
	bool (CaptureDigit::Focus::* ptrRight)()
		= &CaptureDigit::Focus::focusShiftRight;

	// ��������� �� ����� focusShiftLeft()
	bool (CaptureDigit::Focus::* ptrLeft)()
		= &CaptureDigit::Focus::focusShiftLeft;

	// ��������� �� ����� focusShiftDown()
	bool (CaptureDigit::Focus::* ptrDown)()
		= &CaptureDigit::Focus::focusShiftDown;

	// ��������� �� ����� focusShiftUp()
	bool (CaptureDigit::Focus::* ptrUp)()
		= &CaptureDigit::Focus::focusShiftUp;

	// ��������� ����� �� ������ focusShift...()
	bool (CaptureDigit::Focus::* ptrShift)() { nullptr };

	// ����� ����� ������� �����
	bool captureDigit() {
		// ���������, ��� ��� �������� ��� �����
		if (!(massif[cursor.getRow()][cursor.getCol()])) {
			return false;
		}

		// ������ ������� ������ ������ ������� �������
		this->setRow(cursor.getRow());
		this->setCol(cursor.getCol());

		// �������� ����� �� �������
		// � ��������� ����������
		while ((this->*ptrShift)()) {

			// ��������� � ������� �������
			// ������� �����
			if (massif[focus[ROW]][focus[COL]]) {
				// ��������� � ������� �������
				// ������� ������������ �����
				if (massif[cursor.getRow()][cursor.getCol()]
					== massif[focus[ROW]][focus[COL]])
				{
					// �������� ������������ �����
					massif[focus[ROW]][focus[COL]] = true;
					return true;
				}
				else return false;
			}
			// ��� ���������� �����
			// - �������� ��������� �������
			else continue;
		}
		return false;
	}

public:
	// ����������� � ����������
	CaptureDigit(
		Massif& objMassif, Cursor& objCursor)
		: Focus(objMassif), cursor(objCursor)
	{}

	// ����� ������� ����� ������
	bool captureDigitRight() {
		ptrShift = ptrRight;
		return captureDigit();
	}

	// ����� ������� ����� �����
	bool captureDigitLeft() {
		ptrShift = ptrLeft;
		return captureDigit();
	}

	// ����� ������� ����� �����
	bool captureDigitDown() {
		ptrShift = ptrDown;
		return captureDigit();
	}

	// ����� ������� ����� ������
	bool captureDigitUp() {
		ptrShift = ptrUp;
		return captureDigit();
	}

	// ����� �������� ������������ ����
	// ��� �������� � �������
	bool deletingCombinedDigits() {
		massif[cursor.getRow()][cursor.getCol()].getDigit().setD0();
		massif[focus[ROW]][focus[COL]].getDigit().setD0();
		deselectCombinedDigit();
		return false;
	}

	// ����� ������ ��������� � ���������� �����
	// ����� �� �������� ���,
	// ���� ������������ �� ������ ��
	void deselectCombinedDigit() {
		massif[focus[ROW]][focus[COL]] = false;
	}
};
// ����� ������ ������ �����

//-----------------------------------------

// ����� ���� �� ����������� �����
// - ��������� ������ �����
// ������������ ������ ���� ����� ��������
// � ����������� ������
class PathToCapturedDigit : public Focus {
private:
	// ������ �� ������ ������
	Cursor& linkCursor;
	// ���������� ������� { ROW,COL }
	int cursor[TOTAL] = { 0,0 };

	// ������ �� ������ ������ �����
	CaptureDigit& linkCaptureDigit;
	// ���������� ����������� ����� { ROW,COL }
	int captureDigit[TOTAL] = { 0,0 };

	// ��������� �� ����� focusShiftRight()
	bool (PathToCapturedDigit::Focus::* ptrRight)()
		= &PathToCapturedDigit::Focus::focusShiftRight;

	// ��������� �� ����� focusShiftLeft()
	bool (PathToCapturedDigit::Focus::* ptrLeft)()
		= &PathToCapturedDigit::Focus::focusShiftLeft;

	// ��������� �� ����� focusShiftDown()
	bool (PathToCapturedDigit::Focus::* ptrDown)()
		= &PathToCapturedDigit::Focus::focusShiftDown;

	// ��������� �� ����� focusShiftUp()
	bool (PathToCapturedDigit::Focus::* ptrUp)()
		= &PathToCapturedDigit::Focus::focusShiftUp;

	// ��������� ����� �� ������ focusShift...()
	bool (PathToCapturedDigit::Focus::* ptrShift)() { nullptr };

	// ����� �������� �������� ���������
	// �������� ������ � ������ �����
	void setValue() {
		cursor[ROW] = (int)linkCursor.getRow();
		cursor[COL] = (int)linkCursor.getCol();
		captureDigit[ROW] = (int)linkCaptureDigit.getRow();
		captureDigit[COL] = (int)linkCaptureDigit.getCol();
	}

	// ����� ������ �����������
	bool searchDirections(bool mark) {
		// �������� �������� ���������
		// �������� ������ � ������ �����
		if (mark) setValue();

		// ����� ����������� �� ������� � ����������� �����
		// � �������� ����� ���� - ���� ����� 0 (������� �� > 1)
		// -> return false
		if (cursor[COL] == captureDigit[COL]) {
			if ((cursor[ROW] - captureDigit[ROW]) > 0) {
				if ((cursor[ROW] - captureDigit[ROW]) > 1) {
					ptrShift = ptrUp;
					return true;
				}
				else return false;
			}
			else {
				if ((captureDigit[ROW] - cursor[ROW]) > 1) {
					ptrShift = ptrDown;
					return true;
				}
				else return false;
			}
		}
		else if (cursor[ROW] == captureDigit[ROW]) {
			if ((cursor[COL] - captureDigit[COL]) > 0) {
				if ((cursor[COL] - captureDigit[COL]) > 1) {
					ptrShift = ptrLeft;
					return true;
				}
				else return false;
			}
			else {
				if ((captureDigit[COL] - cursor[COL]) > 1) {
					ptrShift = ptrRight;
					return true;
				}
				else return false;
			}
		}
		else if (cursor[ROW] > captureDigit[ROW]) {
			if (((cursor[COL] - captureDigit[COL]) == cursor[COL])
				&& ((cursor[ROW] - captureDigit[ROW]) == 1)
				) {
				return false;
			}
			else {
				ptrShift = ptrLeft;
				return true;
			}
		}
		else {
			if (((captureDigit[COL] - cursor[COL]) == captureDigit[COL])
				&& ((captureDigit[ROW] - cursor[ROW]) == 1)
				) {
				return false;
			}
			else {
				ptrShift = ptrRight;
				return true;
			}
		}
	}

	// ����� ����������� ����
	bool markPath(bool mark) {
		// ��������� ������� ����
		// �� ������� �� ����������� �����
		// � ���������� ��� �����������
		if (searchDirections(mark)) {

			// ������ ������� ������
			// ������ ������� �������
			this->setRow(cursor[ROW]);
			this->setCol(cursor[COL]);

			// ���������� ����
			while ((this->*ptrShift)()) {
				// �������� ���������� � ������� ����������� �����
				if (massif[focus[ROW]][focus[COL]] ==
					massif[captureDigit[ROW]][captureDigit[COL]]
					) break;
				else {
					// ��������� ������� �������
					massif[focus[ROW]][focus[COL]] = mark;
				}
			}
			return true;
		}
		else return false;
	}

public:
	// ����������� � ����������
	PathToCapturedDigit(
		Massif& objMassif,
		Cursor& objCursor,
		CaptureDigit& objCaptureDigit
	) :
		Focus(objMassif),
		linkCursor(objCursor),
		linkCaptureDigit(objCaptureDigit)
	{}

	// ����� ������� ���������� ����
	bool setMarkPath() {
		return markPath(true);
	}

	// ����� ������ ���������� ����
	bool removeMarkPath() {
		return markPath(false);
	}
};
// ����� ������ ���� �� ����������� �����

//-----------------------------------------

// ����� ��������� ����� � �������
// - ��������� ������ �����
// ������ ���������� ��������� ����� �������.
// ����� ��� ����� ������������ �����
// ����� ��� ������������� �������.
class LastDigitInTable : public Focus {
public:
	// ����������� � ����������
	LastDigitInTable(Massif& object) : Focus(object) {}

	// ����� ���������� ���������
	// ��������� ����� � �������
	bool findCoordinates() {
		// ������ ������ ����������
		// ��������� ������� �������
		// (������ ������ ����)
		setRow(massif.maxIndexRow);
		setCol(massif.maxIndexCol);

		// ��������� ������� ����� � ������� �������.
		// ���� ���� - ������� �� ������� � true
		// (���������� ��������� ����� �����
		// �������� � ������ ����� �������).
		// ���� ��� - ���������� ����� � ���������...
		// ���� �� ����� (����� � ������� ����� ����)
		// - � ������� ��� ����,
		// ������� �� ������� � false.
		do {
			if (massif[focus[ROW]][focus[COL]]) {
				return true;
			}
		} while (focusShiftLeft());
		return false;
	}
};
// ����� ������ ��������� ����� � �������

//-----------------------------------------

// ����� ������ ��� ������������� �������
// - ��������� ������ �����
class MethodsForTransformTable : public Focus {
private:
	bool noShiftFocus{ true }; // ���� �� �� ����� ������

public:
	// ����������� � ����������
	MethodsForTransformTable(Massif& object)
		: Focus(object) {}

	// ����� ����� ���������� ����
	size_t findNumberOfDigits() {

		// ���������� ��������� ����
		size_t numberOfDigitsFound{ 0 };

		// ����� � �������
		do {
			if (massif[focus[ROW]][focus[COL]]) {
				++numberOfDigitsFound;
			}
		} while (focusShiftRight());

		return numberOfDigitsFound;
	}

	// ����� ������ ��������� �����
	// �� ����������������� �������
	auto outNextDigit() {
		// ������, ��� ��������� ����� �������
		static auto endMassif{ massif[0][0] };

		// endMassif ������ ���� ���� Element
		// � �� ��������� Element::Digit::D::d0
		// �� ���� ��� �������������� � �� ��������!
		// ������� ����� ������������� �����������
		if (endMassif) {
			auto temp{ massif[0][0] };
			massif[0][0].getDigit().setD0();
			endMassif = massif[0][0];
			massif[0][0] = temp;
		}

		// ����� � ������ ��������� �����
		do {
			if (noShiftFocus) {
				if (massif[focus[ROW]][focus[COL]]) {
					noShiftFocus = false;
					return massif[focus[ROW]][focus[COL]];
				}
			}
			else noShiftFocus = true;
		} while (focusShiftRight());

		// ������, ��� ��������� ����� �������
		return endMassif;
	}
};
// ����� ������ ������ ��� ������������� �������

//-----------------------------------------
