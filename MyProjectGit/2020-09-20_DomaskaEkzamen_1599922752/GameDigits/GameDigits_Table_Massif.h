// GameDigits_Table_Massif.h
/*
����� ���������� ��������� ���� � �����
   ������ ��� ������ Table (�������):

1. Digit (�����)
   ������ � ����� Element (�������).
   ��������:
   1) ������������ enum class D ���������� �������� ����;
   2) ��������� typedef ��� ������� ����
   �������� ������������;
   3) ����-���������� digit ���� enum class D;
   4) ������ ��������������� ���������� ��� ������
   � "�������": bool(), ==, << .
   5) ��������� ������ ��� �������� �������
   ���������� �������� ������������.

   ���������� ������ ����� ��� ���� "�����":
   ��� ���� - ����� �������������, ��� ����������,
              ��� � ��������. ��� ������ �� �����
              ������ ���������� �����.
              ���������� ��� ���������� � typedef.
   ��������� ���� - � ���� ���������� �� ���� ����,
                    � ������� ����� ����� ���,
                    � ������� � �������� ����
                    ����� ���� ����� 10.
                    ����������� ��������� == �����������
                    �������� ������������ ��� ����.
   ������� ����� - � ��������� ������������ ��� d0,
                   �� ������ - ��� ' ' (������),
                   � ��������� ��������� - ��� (bool)false
                   (����������� ����������� ��������� bool() ).

2. Element (�������)
   ������ � ����� MassifRow (������ �������).
   �������� ��������� ����� Digit (�����).
   ��������:
   1) ����-���������� digit ������ Digit (�����).
   2) ���������� ������, ���������� ����������
   ������ Digit "������".
   3) ����-���������� allotted ���� bool,
   ��� ������� ��������� ������� �������� � �������.

3. MassifRow (������ �������)
   ������ � ����� Massif (������).
   �������� ��������� ����� Element (�������).
   �������� ������������ �������� ���� Element.
   ��������� ������� ������ ���������� ������� ���� Digit.

4. Massif (������)
   �������� ��������� ����� MassifRow (������ �������).
   �������� ������������ �������� ���� MassifRow.
   ��������� ������� ���������� ������� ���� Digit
   � ������ ��������� �������.
   ��������� � ������� MassifRow (������ �������)
   ����� ������������� ��������� ���������� [],
   �������������� ������ "������" �� �����������
   ������ Element (�������), � ����� ���������,
   �� ����������� ������ Digit (�����).
*/
#pragma once
#include <iostream>

// ����� ������
class Massif {
private:

	// ����� ������ �������
	class MassifRow {
	private:

		// ����� �������
		class Element {
		private:

			// ����� �����
			class Digit {
			private:
				// �������� ���� ����
				typedef char TypeDigit;

				// ������������ ����
				enum class D : TypeDigit {
					d0 = '0',     // ������� �����
					d1, d2, d3, d4, d5, d6, d7, d8, d9
				};

				// ����� - ���� ������ 
				D digit{ D::d0 };

			public:
				// ����������� �� ���������
				Digit() {}

				// ����� ���������� ��������� ()
				// - ���������� ���� ������� � bool
				operator bool() const {
					if (digit == D::d0) return false;
					else return true;
				}

				// ����� ���������� ��������� ==
				// - ��������� ���������� �� ������������
				bool operator==(const Digit& object) {
					if (this->digit == D::d0) return false;
					if (this->digit == object.digit) return true;
					if (
						((this->digit == D::d1) && (object.digit == D::d9)) ||
						((this->digit == D::d2) && (object.digit == D::d8)) ||
						((this->digit == D::d3) && (object.digit == D::d7)) ||
						((this->digit == D::d4) && (object.digit == D::d6)) ||
						((this->digit == D::d6) && (object.digit == D::d4)) ||
						((this->digit == D::d7) && (object.digit == D::d3)) ||
						((this->digit == D::d8) && (object.digit == D::d2)) ||
						((this->digit == D::d9) && (object.digit == D::d1))
						) return true;
					else return false;
				}

				// ���������� ������������� ������� ���������� ��������� <<
				// - ����� �� ����� �������
				friend std::ostream& operator<<(std::ostream& out, const Digit& object) {
					if (object) out << (TypeDigit)object.digit;
					else out << " ";
					return out;
				}

				// ������ ������� �������� �����
				void setD0() { digit = D::d0; }
				void setD1() { digit = D::d1; }
				void setD2() { digit = D::d2; }
				void setD3() { digit = D::d3; }
				void setD4() { digit = D::d4; }
				void setD5() { digit = D::d5; }
				void setD6() { digit = D::d6; }
				void setD7() { digit = D::d7; }
				void setD8() { digit = D::d8; }
				void setD9() { digit = D::d9; }
			};
			// ����� ������ �����

		// ����������� ������ Element
		private:

			Digit value;			// �������� �����
			bool allotted{ false };	// ���� ��������� �����

		public:
			// ����������� �� ���������
			Element() {}

			// ����� �������� �����
			Digit& getDigit() { return value; }

			// ����� ���������� ��������� =
			// - ������������ �������� bool ����� ��������� �����
			Element& operator=(const bool allot) {
				this->allotted = allot;
				return *this;
			}

			// ����� ���������� ��������� ()
			// - ���������� ���� ������� � bool
			operator bool() const {
				if (this->value) return true;
				else return false;
			}

			// ����� ���������� ��������� ==
			// - ��������� ���������� �� ������������
			bool operator==(const Element& element) {
				if (this->value == element.value) return true;
				else return false;
			}

			// ���������� ������������� ������� ���������� ��������� <<
			// - ����� �������� �� �����
			friend std::ostream& operator<<(
				std::ostream& out, const Element& element
				) {
				out
					// ���� ������� ������� (allotted == true)
					// - �������� ��������� �������� ���������� ������,
					// ����� - ���� �� ���������
					<< (element.allotted ? "\x1b[7m" : "\x1b[m")
					<< element.value
					<< "\x1b[m";	// ������ ��������� ������
				return out;
			}
		};
		// ����� ������ �������

	// ����������� ������ MassifRow
	private:
		Element* row{ nullptr }; // ������ �������

	public:
		// ����� ������ �������
		static const size_t length{ 9 };

		// ����������� �� ���������
		MassifRow() {
			if (!row) row = new Element[length];
		}

		// ����������
		~MassifRow() {
			if (row) delete[] row;
			row = nullptr;
		}

		// ����� ���������� ��������� []
		// - ���������� �������
		Element& operator[](const size_t index) const {
			return row[index];
		}

		// ���������� ������������� ������� ���������� ��������� <<
		// - ����� ������ ������� �� �����
		friend std::ostream& operator<<(
			std::ostream& out, const MassifRow& massifRow
			) {
			for (size_t i = 0; i < massifRow.length; i++) {
				out << massifRow.row[i];
			}
			return out;
		}
	};
	// ����� ������ ������ �������

// ����������� ������ Massif
private:
	size_t size{ 0 };				// ����� �������
	MassifRow* massif{ nullptr };	// ������ ��� ����

public:
	// ������������ ������ ������
	// �������� �������� � �������������
	// � � ������ ���������� ��������� =
	// - ���������� ������������
	volatile const size_t maxIndexRow; // = size - 1;

	// ������������ ������ ��������
	const size_t maxIndexCol = MassifRow::length - 1;

	// ����������� �� ���������
	Massif() : maxIndexRow(0) {}

	// ����������� � ����������
	Massif(size_t size_) :
		size(size_), maxIndexRow(size - 1)
	{
		if (!massif) massif = new MassifRow[size];
	}

	// ����������� �����������
	Massif(Massif&& object) noexcept
		: massif(object.massif)
		, size(object.size)
		, maxIndexRow(size - 1)
	{
		object.massif = nullptr;
		object.size = 0;
	}

	// ����������
	~Massif() {
		if (massif) delete[] massif;
		massif = nullptr;
		size = 0;
	}

	// ����� ������ �������� ����� �������
	size_t getSize() const { return size; }

	// ����� ������ ����� ������ �������
	size_t getRowLength() const {
		return MassifRow::length;
	}

	// ����� ���������� ��������� =
	// - ���������� ������������
	Massif& operator=(Massif&& object) noexcept {
		if (this != &object) {
			delete[] massif;
			size = 0;
			massif = object.massif;
			object.massif = nullptr;
			size = object.size;
			object.size = 0;
			// ������� �������� ��������� maxIndexRow
			size_t* ptr_maxIR =
				const_cast<size_t*>(&maxIndexRow);
			*ptr_maxIR = object.maxIndexRow;
		}
		return *this;
	}

	// ����� ���������� ��������� []
	// - ���������� �������
	MassifRow& operator[](const size_t index) {
		return massif[index];
	}

	// ���������� ������������� ������� ���������� ��������� <<
	// - ����� ������� �� �����
	friend std::ostream& operator<<(
		std::ostream& out, const Massif& massif
		) {
		for (size_t i = 0; i < massif.size; i++) {
			out
				<< "                             "
				<< massif.massif[i]
				<< "-"
				<< std::endl;
		}
		return out;
	}
};
// ����� ������ ������

