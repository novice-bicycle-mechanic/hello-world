// GameDigits_Table.h
#pragma once
#include <iostream>
#include "GameDigits_Table_Massif.h"
#include "GameDigits_Table_Focus.h"


// КЛАСС Таблица
class Table {
private:
	// массив цифр
	Massif massif;

	// курсор для massif
	Cursor cursor{ massif };

	// Объект для захвата и удаления
	// сочетающейся цифры
	CaptureDigit captureDigit{ massif, cursor };

	// Объект для обозначения пути
	// от курсора до захваченной цифры
	// когда между ними стертые цифры
	PathToCapturedDigit pathToCapturedDigit
	{ massif, cursor, captureDigit };

	// Объект для хранения координат
	// последней цифры вновь созданной таблицы
	// (после нее будут дописываться новые цифры
	// при трансформации таблицы)
	LastDigitInTable lastDigitInTable{ massif };

	// ФУНКЦИЯ создания начальной таблицы игры
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

	// КОНСТРУКТОР по умолчанию
	Table() {
		massif = start();
		cursor.here();
		lastDigitInTable.findCoordinates();
	}

	// МЕТОД трансформирования таблицы
	void transformTable() {
		cursor.noHere();
		massif = createTransformedTable(massif);
		cursor.here();
		lastDigitInTable.findCoordinates();
	}

	// МЕТОД создания трансформированной таблицы
	Massif createTransformedTable(Massif& massif) {

		// размер нового массива
		size_t sizeNewMassif{ 0 };
	
		// добавим размер существующего массива
		sizeNewMassif += massif.getSize();

		// определим количество добавляемых
		// в новый массив цифр:

		// объект для подсчета цифр в таблице
		MethodsForTransformTable transformer(massif);
		// количество дописываемых цифр
		size_t numberOfDigitsToAdd =
			transformer.findNumberOfDigits();

		// максимальное количество цифр, которое
		// можно дописать в последнюю строку
		// существующей таблицы
		size_t maxNumDigitsInLastRow =
			massif.maxIndexCol - lastDigitInTable.getCol();

		// определим количество добавляемых в таблицу строк:

		// количество добавляемых строк
		size_t numberOfRowToAdd{ 0 };

		// если максимальное к дописанию в последней строке
		// количество цифр больше или равно количеству
		// найденных в существующей таблице цифр
		if (maxNumDigitsInLastRow >= numberOfDigitsToAdd) {
			// количество добавляемых строк равно 0
			numberOfRowToAdd = 0;
		}
		else {			// иначе
			// уменьшим количество дописываемых цифр
			// на количество дописываемых в последнюю
			// строку существующей таблицы
			numberOfDigitsToAdd -= maxNumDigitsInLastRow;

			// найдем количество добавляемых строк
			// под оставшееся количество дописываемых цифр

			// если остаток целочисленного деления
			// количества дописываемых цифр
			// на длину строки таблицы
			// не равен 0,
			// количество добавляемых строк равно:
			if (numberOfDigitsToAdd % massif.getRowLength()) {

				numberOfRowToAdd = 1 +
					numberOfDigitsToAdd / massif.getRowLength();
			}
			else {		// иначе, равно:
				numberOfRowToAdd = 
					numberOfDigitsToAdd / massif.getRowLength();
			}
		}

		// увеличим размер нового массива на рассчитанное
		// количество добавляемых строк
		sizeNewMassif += numberOfRowToAdd;

		// создадим новый массив
		Massif newMassif(sizeNewMassif);

		// Перепишем значения из существующего массива
		// в новый массив
		for (size_t row = 0; row < massif.getSize(); row++) {
			for (size_t col = 0; col < massif.getRowLength(); col++) {
				newMassif[row][col] = massif[row][col];
			}
		}

		// зададим начальное положение фокуса
		// для метода outNextDigit()
		transformer.setRow(0);
		transformer.setCol(0);

		// Допишем цифры из начала существующего массива в
		// конец последней записанной строки нового массива
		for (
			size_t row = lastDigitInTable.getRow(),
			col = lastDigitInTable.getCol() + 1;
			col < massif.getRowLength();
			col++
			) {
			newMassif[row][col] = transformer.outNextDigit();
		}

		// допишем оставшиеся цифры из существующего массива
		// в добавленные строки нового массива
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
		// выдача нового массива
		return newMassif;
	}

	// МЕТОД возврата объекта Курсор
	Cursor& getCursor() { return cursor; }

	// МЕТОД возврата объекта Захват цифры
	CaptureDigit& getCaptureDigit() {
		return captureDigit;
	}

	// МЕТОД возврата объекта Путь до захваченной цифры
	PathToCapturedDigit& getPathToCapturedDigit() {
		return pathToCapturedDigit;
	}

	// Встроенная дружественная ФУНКЦИЯ перегрузки оператора <<
	// - вывод таблицы на экран
	friend std::ostream& operator<<(
		std::ostream& out, const Table& table
		) {
		out << table.massif;
		return out;
	}
};
// Конец КЛАССА Таблица


