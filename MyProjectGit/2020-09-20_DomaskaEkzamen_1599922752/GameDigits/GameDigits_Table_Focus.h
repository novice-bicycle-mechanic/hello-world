// GameDigits_Table_Focus.h
/*
Здесь определены классы для класса Table (Таблица):
1. Focus (Фокус)
   - родительский класс для указанных ниже классов.
   Обеспечивает перемещение точки фокуса по таблице.
   Инициализируется объектом класса Massif.
   Объект класса Focus в Таблице не создается.
   Все воздействие на Таблицу - через дочерние классы.

2. Cursor (Курсор)
   - дочерний класс для класса Focus.
   Обеспечивает подсветку пользовательского курсора
   и его перемещение по таблице.
   Инициализируется объектом класса Massif.
   Объект класса Cursor создается
   в классе Table (Таблица).

3. CaptureDigit (Захват цифры)
   - дочерний класс для класса Focus.
   Обеспечивает захват и подсветку цифры,
   сочетаемой с цифрой под курсором.
   Инициализируется объектами классов
   Massif и Cursor.
   Объект класса CaptureDigit создается
   в классе Table (Таблица).

4. PathToCapturedDigit (Путь до захваченной цифры)
   - дочерний класс для класса Focus.
   Обеспечивает подсветку позиций со стертыми цифрами
   между курсором и захваченной цифрой.
   Инициализируется объектами классов
   Massif, Cursor, CaptureDigit.
   Объект класса PathToCapturedDigit создается
   в классе Table (Таблица).

5. LastDigitInTable (Последняя цифра в таблице)
   - дочерний класс для класса Focus.
   Хранит координаты последней цифры таблицы.
   После нее будут записываться новые цифры
   при трансформации таблицы.
   Инициализируется объектом класса Massif.
   Объект класса LastDigitInTable создается
   в классе Table (Таблица).

6. MethodsForTransformTable
   (Методы для трансформации таблицы)
   - дочерний класс для класса Focus.
   Содержит методы для трансформации таблиц.
   Инициализируется объектом класса Massif.
   Объект класса MethodsForTransformTable создается
   в методе createTransformedTable()
   класса Table (Таблица).

*/
#pragma once


// КЛАСС Фокус (для массива типа Massif)
// ему наследуют другие классы
class Focus {
protected:

	// ПЕРЕЧИСЛЕНИЕ идентификаторов элементов
	// массива focus = { ROW, COL } и ему подобных.
	// ROW-номер строки в массиве Massif,
	// COL-номер колонки в массиве Massif,
	// TOTAL-всего элементов в массиве focus.
	enum : size_t { ROW, COL, TOTAL };

	// массив координат { ROW,COL }
	// точка фокуса в Massif::massif
	size_t focus[TOTAL] = { 0,0 };

	// ссылка на обрабатываемый массив
	Massif& massif;

public:
	// КОНСТРУКТОР с параметром
	Focus(Massif& object) : massif(object) {}

	// МЕТОД задания для фокуса значения
	// координаты ROW - номер строки
	void setRow(size_t row) { focus[ROW] = row; }

	// МЕТОД задания для фокуса значения
	// координаты COL - номер колонки/столбца
	void setCol(size_t col) { focus[COL] = col; }

	// МЕТОД возврата из фокуса значения
	// координаты ROW - номер строки
	size_t getRow() const { return focus[ROW]; }

	// МЕТОД возврата из фокуса значения
	// координаты COL - номер колонки/столбца
	size_t getCol() const { return focus[COL]; }

	// МЕТОД сдвига фокуса на одну позицию ВПРАВО
	bool focusShiftRight() {
		// Проверка, что фокус в последней колонке
		if (focus[COL] == massif.maxIndexCol) {
			// Проверка, что фокус в последней строке
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

	// МЕТОД сдвига фокуса на одну позицию ВЛЕВО
	bool focusShiftLeft() {
		// Проверка, что фокус в первой колонке
		if (focus[COL] == 0) {
			// Проверка, что фокус в первой строке
			if (focus[ROW] == 0) return false;
			else {
				focus[COL] = massif.maxIndexCol;
				focus[ROW] -= 1;
			}
		}
		else focus[COL] -= 1;

		return true;
	}

	// МЕТОД сдвига фокуса на одну позицию ВНИЗ
	bool focusShiftDown() {
		// Проверка, что фокус в последней строке
		if (focus[ROW] == massif.maxIndexRow) {
			return false;
		}
		else focus[ROW] += 1;

		return true;
	}

	// МЕТОД сдвига фокуса на одну позицию ВВЕРХ
	bool focusShiftUp() {
		// Проверка, что фокус в первой строке
		if (focus[ROW] == 0) return false;
		else focus[ROW] -= 1;

		return true;
	}
};
// Конец КЛАССА Фокус

//-----------------------------------------

// КЛАСС Курсор
// - наследник класса Фокус
class Cursor : public Focus {
public:
	// КОНСТРУКТОР с параметром
	Cursor(Massif& object) : Focus(object) {}

	// МЕТОД обозначения позиции курсора
	void here() {
		massif[focus[ROW]][focus[COL]] = true;
	}

	// МЕТОД сокрытия позиции курсора
	void noHere() {
		massif[focus[ROW]][focus[COL]] = false;
	}

	// МЕТОД сдвига курсора на одну позицию ВПРАВО
	void shiftRight() {
		massif[focus[ROW]][focus[COL]] = false;
		focusShiftRight();
		massif[focus[ROW]][focus[COL]] = true;
	}

	// МЕТОД сдвига курсора на одну позицию ВЛЕВО
	void shiftLeft() {
		massif[focus[ROW]][focus[COL]] = false;
		focusShiftLeft();
		massif[focus[ROW]][focus[COL]] = true;
	}

	// МЕТОД сдвига курсора на одну позицию ВНИЗ
	void shiftDown() {
		massif[focus[ROW]][focus[COL]] = false;
		focusShiftDown();
		massif[focus[ROW]][focus[COL]] = true;
	}

	// МЕТОД сдвига курсора на одну позицию ВВЕРХ
	void shiftUp() {
		massif[focus[ROW]][focus[COL]] = false;
		focusShiftUp();
		massif[focus[ROW]][focus[COL]] = true;
	}
};
// Конец КЛАССА Курсор

//-----------------------------------------

// КЛАСС Захват Цифры
// - наследник класса Фокус
class CaptureDigit : public Focus {
private:
	// Координаты курсора { ROW,COL }
	Cursor& cursor;

	// УКАЗАТЕЛЬ на МЕТОД focusShiftRight()
	bool (CaptureDigit::Focus::* ptrRight)()
		= &CaptureDigit::Focus::focusShiftRight;

	// УКАЗАТЕЛЬ на МЕТОД focusShiftLeft()
	bool (CaptureDigit::Focus::* ptrLeft)()
		= &CaptureDigit::Focus::focusShiftLeft;

	// УКАЗАТЕЛЬ на МЕТОД focusShiftDown()
	bool (CaptureDigit::Focus::* ptrDown)()
		= &CaptureDigit::Focus::focusShiftDown;

	// УКАЗАТЕЛЬ на МЕТОД focusShiftUp()
	bool (CaptureDigit::Focus::* ptrUp)()
		= &CaptureDigit::Focus::focusShiftUp;

	// УКАЗАТЕЛЬ общий на МЕТОДЫ focusShift...()
	bool (CaptureDigit::Focus::* ptrShift)() { nullptr };

	// МЕТОД общий захвата цифры
	bool captureDigit() {
		// Проверяем, что под курсором нет цифры
		if (!(massif[cursor.getRow()][cursor.getCol()])) {
			return false;
		}

		// Задаем позицию фокуса равную позиции курсора
		this->setRow(cursor.getRow());
		this->setCol(cursor.getCol());

		// Сдвигаем фокус на позицию
		// с проверкой результата
		while ((this->*ptrShift)()) {

			// Проверяем в текущей позиции
			// наличие цифры
			if (massif[focus[ROW]][focus[COL]]) {
				// Проверяем в текущей позиции
				// наличие сочетающейся цифры
				if (massif[cursor.getRow()][cursor.getCol()]
					== massif[focus[ROW]][focus[COL]])
				{
					// Выделяем сочетающуюся цифру
					massif[focus[ROW]][focus[COL]] = true;
					return true;
				}
				else return false;
			}
			// При отсутствии цифры
			// - проверка следующей позиции
			else continue;
		}
		return false;
	}

public:
	// КОНСТРУКТОР с параметром
	CaptureDigit(
		Massif& objMassif, Cursor& objCursor)
		: Focus(objMassif), cursor(objCursor)
	{}

	// МЕТОД захвата цифры СПРАВА
	bool captureDigitRight() {
		ptrShift = ptrRight;
		return captureDigit();
	}

	// МЕТОД захвата цифры СЛЕВА
	bool captureDigitLeft() {
		ptrShift = ptrLeft;
		return captureDigit();
	}

	// МЕТОД захвата цифры СНИЗУ
	bool captureDigitDown() {
		ptrShift = ptrDown;
		return captureDigit();
	}

	// МЕТОД захвата цифры СВЕРХУ
	bool captureDigitUp() {
		ptrShift = ptrUp;
		return captureDigit();
	}

	// МЕТОД удаления сочетающихся цифр
	// под курсором и фокусом
	bool deletingCombinedDigits() {
		massif[cursor.getRow()][cursor.getCol()].getDigit().setD0();
		massif[focus[ROW]][focus[COL]].getDigit().setD0();
		deselectCombinedDigit();
		return false;
	}

	// МЕТОД снятия выделения с сочетаемой цифры
	// после ее удаления или,
	// если пользователь не удалил ее
	void deselectCombinedDigit() {
		massif[focus[ROW]][focus[COL]] = false;
	}
};
// Конец КЛАССА Захват цифры

//-----------------------------------------

// КЛАСС Путь до захваченной цифры
// - наследник класса Фокус
// подсвечивает пустые поля между курсором
// и захваченной цифрой
class PathToCapturedDigit : public Focus {
private:
	// Ссылка на объект Курсор
	Cursor& linkCursor;
	// Координаты курсора { ROW,COL }
	int cursor[TOTAL] = { 0,0 };

	// Ссылка на объект Захват цифры
	CaptureDigit& linkCaptureDigit;
	// Координаты захваченной цифры { ROW,COL }
	int captureDigit[TOTAL] = { 0,0 };

	// УКАЗАТЕЛЬ на МЕТОД focusShiftRight()
	bool (PathToCapturedDigit::Focus::* ptrRight)()
		= &PathToCapturedDigit::Focus::focusShiftRight;

	// УКАЗАТЕЛЬ на МЕТОД focusShiftLeft()
	bool (PathToCapturedDigit::Focus::* ptrLeft)()
		= &PathToCapturedDigit::Focus::focusShiftLeft;

	// УКАЗАТЕЛЬ на МЕТОД focusShiftDown()
	bool (PathToCapturedDigit::Focus::* ptrDown)()
		= &PathToCapturedDigit::Focus::focusShiftDown;

	// УКАЗАТЕЛЬ на МЕТОД focusShiftUp()
	bool (PathToCapturedDigit::Focus::* ptrUp)()
		= &PathToCapturedDigit::Focus::focusShiftUp;

	// УКАЗАТЕЛЬ общий на МЕТОДЫ focusShift...()
	bool (PathToCapturedDigit::Focus::* ptrShift)() { nullptr };

	// МЕТОД загрузки значений координат
	// объектов Курсор и Захват цифры
	void setValue() {
		cursor[ROW] = (int)linkCursor.getRow();
		cursor[COL] = (int)linkCursor.getCol();
		captureDigit[ROW] = (int)linkCaptureDigit.getRow();
		captureDigit[COL] = (int)linkCaptureDigit.getCol();
	}

	// МЕТОД поиска направления
	bool searchDirections(bool mark) {
		// загрузка значений координат
		// объектов Курсор и Захват цифры
		if (mark) setValue();

		// поиск направления от Курсора к захваченной цифре
		// и проверка длины пути - если равна 0 (разница не > 1)
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

	// МЕТОД обозначения пути
	bool markPath(bool mark) {
		// проверить наличие пути
		// от курсора до захваченной цифры
		// и определить его направление
		if (searchDirections(mark)) {

			// Задаем позицию фокуса
			// равную позиции курсора
			this->setRow(cursor[ROW]);
			this->setCol(cursor[COL]);

			// маркировка пути
			while ((this->*ptrShift)()) {
				// Проверка нахождения в позиции захваченной цифры
				if (massif[focus[ROW]][focus[COL]] ==
					massif[captureDigit[ROW]][captureDigit[COL]]
					) break;
				else {
					// Выделение текущей позиции
					massif[focus[ROW]][focus[COL]] = mark;
				}
			}
			return true;
		}
		else return false;
	}

public:
	// КОНСТРУКТОР с параметром
	PathToCapturedDigit(
		Massif& objMassif,
		Cursor& objCursor,
		CaptureDigit& objCaptureDigit
	) :
		Focus(objMassif),
		linkCursor(objCursor),
		linkCaptureDigit(objCaptureDigit)
	{}

	// МЕТОД задания маркировки пути
	bool setMarkPath() {
		return markPath(true);
	}

	// МЕТОД снятия маркировки пути
	bool removeMarkPath() {
		return markPath(false);
	}
};
// Конец КЛАССА Путь до захваченной цифры

//-----------------------------------------

// КЛАСС Последняя цифра в таблице
// - наследник класса Фокус
// Хранит координаты последней цифры таблицы.
// После нее будут записываться новые
// цифры при трансформации таблицы.
class LastDigitInTable : public Focus {
public:
	// КОНСТРУКТОР с параметром
	LastDigitInTable(Massif& object) : Focus(object) {}

	// МЕТОД нахождения координат
	// последней цифры в таблице
	bool findCoordinates() {
		// Задаем фокусу координаты
		// последней позиции таблицы
		// (нижний правый угол)
		setRow(massif.maxIndexRow);
		setCol(massif.maxIndexCol);

		// Проверяем наличие цифры в текущей позиции.
		// Если есть - выходим из функции с true
		// (координаты последней точки будут
		// хранится в фокусе этого объекта).
		// Если нет - сдвигаемся влево и повторяем...
		// Если не нашли (фокус в верхнем левом углу)
		// - в таблице нет цифр,
		// выходим из функции с false.
		do {
			if (massif[focus[ROW]][focus[COL]]) {
				return true;
			}
		} while (focusShiftLeft());
		return false;
	}
};
// Конец КЛАССА Последняя цифра в таблице

//-----------------------------------------

// КЛАСС Методы для трансформации таблицы
// - наследник класса Фокус
class MethodsForTransformTable : public Focus {
private:
	bool noShiftFocus{ true }; // ключ на не сдвиг фокуса

public:
	// КОНСТРУКТОР с параметром
	MethodsForTransformTable(Massif& object)
		: Focus(object) {}

	// МЕТОД Найти количество цифр
	size_t findNumberOfDigits() {

		// количество найденных цифр
		size_t numberOfDigitsFound{ 0 };

		// Поиск и подсчет
		do {
			if (massif[focus[ROW]][focus[COL]]) {
				++numberOfDigitsFound;
			}
		} while (focusShiftRight());

		return numberOfDigitsFound;
	}

	// МЕТОД выдачи следующей цифры
	// из трансформируемого массива
	auto outNextDigit() {
		// сигнал, что достигнут конец таблицы
		static auto endMassif{ massif[0][0] };

		// endMassif должен быть типа Element
		// и со значением Element::Digit::D::d0
		// но этот тип инкапсулирован и не доступен!
		// поэтому нужна нижеследующая конструкция
		if (endMassif) {
			auto temp{ massif[0][0] };
			massif[0][0].getDigit().setD0();
			endMassif = massif[0][0];
			massif[0][0] = temp;
		}

		// поиск и выдача следующей цифры
		do {
			if (noShiftFocus) {
				if (massif[focus[ROW]][focus[COL]]) {
					noShiftFocus = false;
					return massif[focus[ROW]][focus[COL]];
				}
			}
			else noShiftFocus = true;
		} while (focusShiftRight());

		// сигнал, что достигнут конец таблицы
		return endMassif;
	}
};
// Конец КЛАССА Методы для трансформации таблицы

//-----------------------------------------
