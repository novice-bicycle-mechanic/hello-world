// ������� �� ����� "homework 18.pdf"
	//--------------------------------------------

	//                          �������� ������� �18

	// ����: ����������� ������������ �������

	//                         ������� �35. ������� 2

	//     ���� 3 ��������� ������� A, B, C. ���������� ����� � �������� ��� ���
	// ������ ������������ � ���������� ��� ������� �� ���.
	//     �������:
	// � ������� ���������� ������, ������� �������� ����� �������� ��� A, B, C.
	// � ������� ���������� ������, ������� �������� ���������� �������� ��� A, B, C.
	// � ������� ���������� ������, ������� �������� ����� �������� ��� A � C.
	// � ������� ���������� ������, ������� �������� ������������� �������� ���
	//   A, B, C ��� ����������.

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include <iomanip>

#define N "\n"

using namespace std;


//--------------------------------------------------------------------


bool compareToMatchPreviousOnes			// ������� �������� � ��������� ��������� ������� ��������
										//         value �� �������� � ���������������� ����������
(
	int value,								// ����������� �� ���������� ��������

	int** twoDimArr,						// ��������� �� ��������� ������

	size_t row,								// ����� ������ �������, ��� ��������� value

	size_t col,								// ����� ������� �������, ��� ��������� value

	size_t colMax							// ����� ������� �������, ��� ��������� value
)
{
	for (size_t i = 0; i <= row; i++)
	{
		for (size_t j = 0; j < ((i != row) ? (colMax) : (col)); j++)
		{
			if (twoDimArr[i][j] == value)
			{
				return true;
			}
		}
	}

	return false;
}


//--------------------------------------------------------------------


bool compareToMatchPreviousOnes			// ������� �������� � ��������� ���������� ������� ��������
										//         value �� �������� � ���������������� ����������
(
	int value,								// ����������� �� ���������� ��������

	int* oneDimArr,							// ��������� �� ���������� ������

	size_t numItem							// ����� �������� �������, ��� ��������� value
)
{
	for (size_t i = 0; i < numItem; i++)
	{
		if (oneDimArr[i] == value)
		{
			return true;
		}
	}

	return false;
}


//--------------------------------------------------------------------


bool uniqueElementInTwoDimArray			// ������� �������� � ��������� ��������� �������
										//         �������� value �� �� �������� � ����������
(
	int value,								// ����������� �� ���������� ��������

	int** twoDimArr,						// ��������� �� ��������� ������

	size_t row,								// ���������� ����� �������

	size_t col								// ���������� ������� �������
)
{
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{
			if (twoDimArr[i][j] == value)
			{
				return false;
			}
		}
	}

	return true;
}


//--------------------------------------------------------------------


int* unique							// ������� ������ ���������� �������� � ���� ��������� ��������
									//         � �������� ����������� ������� � ���������� ����������
(
	size_t& sizeNewArr,						// ������ �� ������ ������� ���������� ���������

	int** first,							// ������ ������

	size_t* sizesFirst,						// ������� ������� �������

	int** second,							// ������ ������

	size_t* sizesSecond,					// ������� ������� �������

	int** third,							// ������ ������

	size_t* sizesThird						// ������� �������� �������
)
{
	int* arrUnique = nullptr;				// ��������� �� ������ ���������� ���������

	size_t sizeUnique = 0;					// ������ ������� ���������� ���������

	for (size_t k = 0; k < 2; k++)			// ���� ������� ������: 0 - ������� � ��������; 1 - ����������
	{
		sizeUnique = 0;

		// �������� �� ������������ �������� ������� �������

		for (size_t i = 0; i < sizesFirst[0]; i++)
		{
			for (size_t j = 0; j < sizesFirst[1]; j++)
			{
				if ((!compareToMatchPreviousOnes(first[i][j], first, i, j, sizesFirst[1]))

					&& (uniqueElementInTwoDimArray(first[i][j], second, sizesSecond[0], sizesSecond[1]))

					&& (uniqueElementInTwoDimArray(first[i][j], third, sizesThird[0], sizesThird[1])))
				{
					// ���� ������� ����������

					if (arrUnique)								// ���� ����� �� nullptr
					{
						arrUnique[sizeUnique] = first[i][j];	// ������ ��������
					}

					sizeUnique++;								// ����������� ������ ��� ��������� ��������
				}
			}
		}

		// �������� �� ������������ �������� ������� �������

		for (size_t i = 0; i < sizesSecond[0]; i++)
		{
			for (size_t j = 0; j < sizesSecond[1]; j++)
			{
				if ((!compareToMatchPreviousOnes(second[i][j], second, i, j, sizesSecond[1]))

					&& (uniqueElementInTwoDimArray(second[i][j], first, sizesFirst[0], sizesFirst[1]))

					&& (uniqueElementInTwoDimArray(second[i][j], third, sizesThird[0], sizesThird[1])))
				{
					// ���� ������� ����������

					if (arrUnique)								// ���� ����� �� nullptr
					{
						arrUnique[sizeUnique] = second[i][j];	// ������ ��������
					}

					sizeUnique++;								// ����������� ������ ��� ��������� ��������
				}
			}
		}

		// �������� �� ������������ �������� �������� �������

		for (size_t i = 0; i < sizesThird[0]; i++)
		{
			for (size_t j = 0; j < sizesThird[1]; j++)
			{
				if ((!compareToMatchPreviousOnes(third[i][j], third, i, j, sizesThird[1]))

					&& (uniqueElementInTwoDimArray(third[i][j], first, sizesFirst[0], sizesFirst[1]))

					&& (uniqueElementInTwoDimArray(third[i][j], second, sizesSecond[0], sizesSecond[1])))
				{
					// ���� ������� ����������

					if (arrUnique)								// ���� ����� �� nullptr
					{
						arrUnique[sizeUnique] = third[i][j];	// ������ ��������
					}

					sizeUnique++;								// ����������� ������ ��� ��������� ��������
				}
			}
		}

		if (!arrUnique)								// ���� ����� nullptr
		{
			sizeNewArr = sizeUnique;				// �������� ������������ ����� �������

			arrUnique = new int[sizeUnique] {0};	// ������� ������ ������������ �����
		}
	}

	return arrUnique;
}


//--------------------------------------------------------------------


int* negative						// ������� ������ ������������� �������� ��� ���������� � ���� ���������
									//         �������� � �������� ����������� ������� � ���������� ����������
(
	size_t& sizeNewArr,						// ������ �� ������ ������� ������������� ���������

	int** first,							// ������ ������

	size_t* sizesFirst,						// ������� ������� �������

	int** second,							// ������ ������

	size_t* sizesSecond,					// ������� ������� �������

	int** third,							// ������ ������

	size_t* sizesThird						// ������� �������� �������
)
{
	int* arrNegative = nullptr;				// ��������� �� ������ ������������� ���������

	size_t sizeNegative = 0;				// ������ ������� ������������� ���������

	for (size_t k = 0; k < 2; k++)			// ���� ������� ������: 0 - ������� � ��������; 1 - ����������
	{
		sizeNegative = 0;

		// �������� �� ��������������� �������� ������� �������

		for (size_t i = 0; i < sizesFirst[0]; i++)
		{
			for (size_t j = 0; j < sizesFirst[1]; j++)
			{
				if ((first[i][j] < 0)
					
					&& (!compareToMatchPreviousOnes(first[i][j], first, i, j, sizesFirst[1])))
				{
					// ���� ������� ������������� � ���������� � ��������� �������

					if (arrNegative)								// ���� ����� �� nullptr
					{
						arrNegative[sizeNegative] = first[i][j];	// ������ ��������
					}

					sizeNegative++;									// ����������� ������ ��� ��������� ��������
				}
			}
		}

		// �������� �� ��������������� �������� ������� �������

		for (size_t i = 0; i < sizesSecond[0]; i++)
		{
			for (size_t j = 0; j < sizesSecond[1]; j++)
			{
				if ((second[i][j] < 0)

					&& (!compareToMatchPreviousOnes(second[i][j], second, i, j, sizesSecond[1]))
					
					&& (uniqueElementInTwoDimArray(second[i][j], first, sizesFirst[0], sizesFirst[1]))
				)
				{
					// ���� ������� ������������� � ���������� � ��������� �������
					// � �� ����������� � ������ �������

					if (arrNegative)								// ���� ����� �� nullptr
					{
						arrNegative[sizeNegative] = second[i][j];	// ������ ��������
					}

					sizeNegative++;									// ����������� ������ ��� ��������� ��������
				}
			}
		}

		// �������� �� ��������������� �������� �������� �������

		for (size_t i = 0; i < sizesThird[0]; i++)
		{
			for (size_t j = 0; j < sizesThird[1]; j++)
			{
				if ((third[i][j] < 0)

					&& (!compareToMatchPreviousOnes(third[i][j], third, i, j, sizesThird[1]))

					&& (uniqueElementInTwoDimArray(third[i][j], first, sizesFirst[0], sizesFirst[1]))

					&& (uniqueElementInTwoDimArray(third[i][j], second, sizesSecond[0], sizesSecond[1]))
					)
				{
					// ���� ������� ������������� � ���������� � ��������� �������
					// � �� ����������� � ������ �������
					// � �� ����������� �� ������ �������

					if (arrNegative)								// ���� ����� �� nullptr
					{
						arrNegative[sizeNegative] = third[i][j];	// ������ ��������
					}

					sizeNegative++;									// ����������� ������ ��� ��������� ��������
				}
			}
		}

		if (!arrNegative)								// ���� ����� nullptr
		{
			sizeNewArr = sizeNegative;					// �������� ������������ ����� �������

			arrNegative = new int[sizeNegative] {0};	// ������� ������ ������������ �����
		}
	}

	return arrNegative;
}


//--------------------------------------------------------------------


int* general					// ������� ���������� ����� ��������� � ���� ��������� ��������
(
	size_t& sizeNewArr,						// ������ �� ������ ������� ����� ���������

	int** first,							// ������ ������

	size_t* sizesFirst,						// ������� ������� �������

	int** second,							// ������ ������

	size_t* sizesSecond						// ������� ������� �������
)
{
	// ���������� ����� ��������� ��� ���������� ��������
	// �� ��������� ���������� ��������� � ���������� �� ���.
	// ������ ��������� �������� ������: ������� ���������
	// ���������� ����� ��������� � �������� ������ ����� ���������,
	// � �� ��� ������� ������ ��� � �������� ����� ������ ������ ����������.
	// ����������� ��������� - ���������� ��� ������� � ����, �������������,
	// � ������� �� ��������, ��� ����� � ���� ����������� - �����.

	int** min = nullptr;					// ��������� �� ���������� ������

	size_t* sizesMin = nullptr;				// ��������� �� ������ �������� ����������� �������

	int** two = nullptr;					// ��������� �� ������ �2

	size_t* sizesTwo = nullptr;				// ��������� �� ������ �������� ������� �2

	int* arrGeneral = nullptr;				// ��������� �� ������ ����� ���������

	size_t sizeGeneral = 0;					// ������ ������� ����� ���������

	// ������ ���������� ������ �� ��������

	if (sizesFirst[0] * sizesFirst[1] <= sizesSecond[0] * sizesSecond[1])
	{
		min = first;

		sizesMin = sizesFirst;

		two = second;

		sizesTwo = sizesSecond;
	}
	else
	{
		min = second;

		sizesMin = sizesSecond;

		two = first;

		sizesTwo = sizesFirst;
	}

	// ��������� ���������� ����� ��������� � ��������,
	// �������� ���������� ������ ����� ��������� ���� ��������� ��������,
	// �������� ��������� ������ ������ ����������

	for (size_t k = 0; k < 2; k++)			// ���� ������� ������: 0 - ������� � ��������; 1 - ����������
	{
		sizeGeneral = 0;

		for (size_t i = 0; i < sizesMin[0]; i++)		// ��� ����� ������ ������������� ��������
		{
			for (size_t j = 0; j < sizesMin[1]; j++)
			{
				// �������� ����� ������������ �� �������� �������
				// �� ������� min �� ���������� ���������� � �����
				// ������������ � ���� �� �������

				if (compareToMatchPreviousOnes(min[i][j], min, i, j, sizesMin[1]))
				{
					continue;	// ����� � ��������� �������� ���� ���� ����������
				}

				for (size_t x = 0; x < sizesTwo[0]; x++)	// ��� ����� ��������� ��������� �� ��������
				{
					for (size_t y = 0; y < sizesTwo[1]; y++)
					{
						if (two[x][y] == min[i][j])
						{
							// �������� ����� ������������ �� �������� �������
							// �� ������� two �� ���������� ���������� � �����
							// ������������ � ���� �� �������

							if (compareToMatchPreviousOnes(two[x][y], two, x, y, sizesTwo[1]))
							{
								continue;	// ����� � ��������� �������� ���� ���� ����������
							}

							if (arrGeneral)	// ���� ����� �� nullptr
							{
								arrGeneral[sizeGeneral] = min[i][j];	// ������ ��������
							}

							sizeGeneral++;	// ����������� ������ ��� ��������� ��������
						}
					}
				}
			}
		}

		if (!arrGeneral)							// ���� ����� nullptr
		{
			sizeNewArr = sizeGeneral;					// �������� ������������ ����� �������

			arrGeneral = new int[sizeGeneral] {0};	// ������� ������ ������������ �����
		}
	}

	return arrGeneral;
}


//--------------------------------------------------------------------


int* general					// ������� ���������� ����� ��������� � ����������
								//         � ��������� ��������
(
	size_t& sizeNewArr,						// ������ �� ������ ������� ����� ���������

	int* min,								// ����������� ���������� ������

	size_t sizesMin,						// ������� ������� �������

	int** two,								// ������ ��������� ������

	size_t* sizesTwo						// ������� ������� �������
)
{
	// ���������� ����� ��������� ��� ���������� ��������
	// �� ��������� ���������� ��������� � ���������� �� ���.
	// ������ ��������� �������� ������: ������� ���������
	// ���������� ����� ��������� � �������� ������ ����� ���������,
	// � �� ��� ������� ������ ��� � �������� ����� ������ ������ ����������.
	// ����������� ��������� - ���������� ��� ������� � ����, �������������,
	// � ������� �� ��������, ��� ����� � ���� ����������� - �����.

	int* arrGeneral = nullptr;				// ��������� �� ������ ����� ���������

	size_t sizeGeneral = 0;					// ������ ������� ����� ���������

	// ��������� ���������� ����� ��������� � ��������,
	// �������� ���������� ������ ����� ��������� ���� ��������� ��������,
	// �������� ��������� ������ ������ ����������

	bool outIter = false;					// ����� �� ��������

	for (size_t k = 0; k < 2; k++)			// ���� ������� ������: 0 - ������� � ��������; 1 - ����������
	{
		sizeGeneral = 0;

		for (size_t i = 0; i < sizesMin; i++)		// ���� ������ ������������� ��������
		{
			// �������� ����� ������������ �� �������� �������
			// �� ������� min �� ���������� ���������� � �����
			// ������������ � ���� �� �������

			if (compareToMatchPreviousOnes(min[i], min, i))
			{
				continue;	// ����� � ��������� �������� ���� ���� ����������
			}

			for (size_t x = 0; x < sizesTwo[0]; x++)	// ��� ����� ��������� ��������� �� ��������
			{
				for (size_t y = 0; y < sizesTwo[1]; y++)
				{
					if (two[x][y] == min[i])
					{
						// �������� ����� ������������ �� �������� �������
						// �� ������� two �� ���������� ���������� � �����
						// ������������ � ���� �� �������

						if (compareToMatchPreviousOnes(two[x][y], two, x, y, sizesTwo[1]))
						{
							continue;	// ����� � ��������� �������� ���� ���� ����������
						}

						if (arrGeneral)	// ���� ����� �� nullptr
						{
							arrGeneral[sizeGeneral] = min[i];	// ������ ��������
						}

						sizeGeneral++;	// ����������� ������ ��� ��������� ��������
					}
				}
			}
		}

		if (!arrGeneral)							// ���� ����� nullptr
		{
			sizeNewArr = sizeGeneral;				// �������� ������������ ����� �������

			arrGeneral = new int[sizeGeneral] {0};	// ������� ������ ������������ �����
		}
	}

	return arrGeneral;
}


//--------------------------------------------------------------------


bool createAnArray					// ������� �������� ���������� ������� (true-����� �� ���������)
(
	char name,								// ������������� ��� ������� ��� ���������

	int**& twoDimArr,						// ��������� �� ����������� ��������� ������

	size_t& row,							// ���������� ����� � ����������� �������

	size_t& col								// ���������� ������� � ����������� �������
)
{
	unsigned char byte1char = 0;			// ������ ���� ���� ������� / ������� �������

	enum key { BackSpace = 8, Enter = 13, ESC = 27 };		// ���� ������

	bool firstSymbol = false;				// ���� ������� �������

	size_t num = 0;							// ��������������� ����������

	for (size_t i = 0; i < 2; i++)			// ���� ������� �����: ���������� ����� ��� �������
	{
		firstSymbol = false;

		cout
			<< " ������� ���������� "
			
			<< (i ? "������� (4-10)" : "����� (1-3)")
			
			<< " � ������� " << name << ": > ";

		while (true)						// ���� ����� ��������
		{
			byte1char = _getch();

			if (_kbhit()) { (void)_getch(); }

			if (byte1char == ESC)
			{
				return true;			
			}

			if ((('0' < byte1char) && (byte1char <= '9'))
				
				|| ((firstSymbol) && (byte1char == '0')))
			{
				firstSymbol = true;

				cout << byte1char;

				if (i)
				{
					col = col * 10 + (byte1char - 48);

					num = col;

					if (col > 10)
					{
						col = 10;

						num = col;

						byte1char = Enter;
					}
				}
				else 
				{
					row = row * 10 + (byte1char - 48);

					num = row;

					if (row > 3)
					{
						row = 3;

						num = row;

						byte1char = Enter;
					}
				}
			}

			if (byte1char == Enter)
			{
				if ((i) && (col < 4))
				{
					col = 4;

					num = col;
				}

				byte1char = 0;

				break;
			}
		}

		cout << "\t" "��������� ������ " << num << N << endl;
	}

	twoDimArr = new int* [row];					// ������� ��������� ������ (������ ������� �����)

	for (size_t i = 0; i < row; i++)			// ������������� �������� ���������� �������
	{
		twoDimArr[i] = new int[col];			// - �������� ������� �������
	}

	for (size_t i = 0; i < row; i++)			// ������������� �������
	{
		for (size_t j = 0; j < col; j++)
		{
			// - ���������� ���������� +/- ����������

			twoDimArr[i][j] = rand() * row * col * 2 / RAND_MAX - (row * col);
		}
	}

	return false;
}


//--------------------------------------------------------------------


void printArray				// ������� ������ �� ����� ���������� �������
(
	int** twoDimArr,						// ��������� �� ����� ��������� ������

	size_t row,								// ���������� ����� � ����������� �������

	size_t col								// ���������� ������� � ����������� �������
)
{
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{
			cout << setw(7) << twoDimArr[i][j];
		}

		cout << N << endl;
	}
}


//--------------------------------------------------------------------


void printArray				// ������� ������ �� ����� ����������� �������
(
	int* oneDimArr,						// ��������� �� ����� ���������� ������

	size_t sizeArr						// ������ ����������� �������
)
{
	for (size_t i = 0; i < sizeArr; i++)
	{
		cout
			<< setw(7) << oneDimArr[i]

			<< (((  (!((i + 1) % 10)) && (i != 0)) || ((i + 1) == sizeArr)) ? (N N) : (""));
	}
}


//--------------------------------------------------------------------


template <typename T>

T** delArray						// ������� �������� ���������� �������
(
	T** twoDimArr,							// ��������� ��������� ������

	size_t row								// ���������� ����� � ����������� �������
)
{
	for (size_t i = 0; i < row; i++)
	{
		delete[] twoDimArr[i];				// �������� ����� ���������� �������
	}

	delete[] twoDimArr;						// ������������� �������� ���������� �������

	return nullptr;							// ������� �������� ���������
}


//--------------------------------------------------------------------


template <typename T>

T* delArray							// ������� �������� ����������� �������
(
	T* oneDimArr							// ��������� ���������� ������
)
{
	delete[] oneDimArr;						// �������� ����������� �������

	return nullptr;							// ������� �������� ���������
}


//--------------------------------------------------------------------


int main()
{
	SetConsoleOutputCP(1251);

	//--------------------------------------------

	//                          �������� ������� �18

	// ����: ����������� ������������ �������

	//                         ������� �35. ������� 2

	//     ���� 3 ��������� ������� A, B, C. ���������� ����� � �������� ��� ���
	// ������ ������������ � ���������� ��� ������� �� ���.
	//     �������:
	// � ������� ���������� ������, ������� �������� ����� �������� ��� A, B, C.
	// � ������� ���������� ������, ������� �������� ���������� �������� ��� A, B, C.
	// � ������� ���������� ������, ������� �������� ����� �������� ��� A � C.
	// � ������� ���������� ������, ������� �������� ������������� �������� ���
	//   A, B, C ��� ����������.

	cout
		<< "                              �������� ������� �18"

		N N" ����: ����������� ������������ �������"

		N N"                             ������� �35. ������� 2"

		N N"     ���� 3 ��������� ������� A, B, C. ���������� ����� � �������� ��� ���"
		
		N N" ������ ������������ � ���������� ��� ������� �� ���."
		
		N N"     �������:"

		N N" � ������� ���������� ������, ������� �������� ����� �������� ��� A, B, C."
		
		N N" � ������� ���������� ������, ������� �������� ���������� �������� ��� A, B, C."
		
		N N" � ������� ���������� ������, ������� �������� ����� �������� ��� A � C."
		
		N N" � ������� ���������� ������, ������� �������� ������������� �������� ���"
		
		N N"   A, B, C ��� ����������."

		N N" ------------------------------------------------------------------------------"

		<< N << endl;

	cout << " [ESC]-����� �� ���������, [Enter]-���� �����" << N << endl;

	int** arrayA = nullptr;							// �0 ��������� ������ A

	int** arrayB = nullptr;							// �1 ��������� ������ B

	int** arrayC = nullptr;							// �2 ��������� ������ C

	int* generalABC = nullptr;						// �0 ���������� ������ � ���������� ������ ��� A, B, C

	int* uniqueABC = nullptr;						// �1 ���������� ������ � ���������� ����������� ��� A, B, C

	int* generalAC = nullptr;						// �2 ���������� ������ � ���������� ������ ��� A � C

	int* negativeABC = nullptr;						// �3 ���������� ������ � �������������� ����������
													// ��� A, B, C ��� ����������

	srand((unsigned int)time(0));					// ��������� ��������� �������� ��� rand()

	(void)rand();									// �������� ������ ��� ��������� ��������� ��������

	(void)rand();									// �������� ������ ��� ��������� ��������� ��������

	// �������� ������ �������� ���������� ����� � ������� ��������� ��������

	size_t** rowCol = new size_t * [3]{ nullptr };
	
	for (size_t i = 0; i < 3; i++)
	{
		rowCol[i] = new size_t[2]{0};
	}

	// �������� ������ �������� ���������� ��������� ���������� ��������

	size_t* arrSize = new size_t[4]{};

	// �������� � ������������� ��������� �������� A, B, C

	if      (createAnArray('A', arrayA, rowCol[0][0], rowCol[0][1]))
	{
		return 0;													// ����� �� ���������
	}
	else if (createAnArray('B', arrayB, rowCol[1][0], rowCol[1][1]))
	{
		delArray(arrayA, rowCol[0][0]);								// �������� ���������� ������� A

		return 0;													// ����� �� ���������
	}
	else if (createAnArray('C', arrayC, rowCol[2][0], rowCol[2][1]))
	{
		delArray(arrayA, rowCol[0][0]);								// �������� ���������� ������� A

		delArray(arrayB, rowCol[1][0]);								// �������� ���������� ������� B

		return 0;													// ����� �� ���������
	}

	cout << " ������ ������ A:" << N << endl;

	printArray(arrayA, rowCol[0][0], rowCol[0][1]);		// ����� �� ����� ���������� ������� A

	cout << " ������ ������ B:" << N << endl;

	printArray(arrayB, rowCol[1][0], rowCol[1][1]);		// ����� �� ����� ���������� ������� B

	cout << " ������ ������ C:" << N << endl;

	printArray(arrayC, rowCol[2][0], rowCol[2][1]);		// ����� �� ����� ���������� ������� C

	// �������� ���������� ������ ����� �������� ��� �������� A � C.

	generalAC = general(arrSize[2], arrayA, rowCol[0], arrayC, rowCol[2]);

	// �������� ���������� ������ ����� �������� ��� �������� A, B, C (��� AC � B)

	generalABC = general(arrSize[0], generalAC, arrSize[2], arrayB, rowCol[1]);

	// �������� ���������� ������ ����� �������� ��� �������� A, B, C (��� AC � B)

	uniqueABC = unique(arrSize[1], arrayA, rowCol[0], arrayB, rowCol[1], arrayC, rowCol[2]);

	// �������� ���������� ������ ������������� �������� ��� ���������� ��� �������� A, B, C

	negativeABC = negative(arrSize[3], arrayA, rowCol[0], arrayB, rowCol[1], arrayC, rowCol[2]);

	// ����� �� ����� ����������� ������� ����� ��������� ��� �������� A, B, C

	cout
		<< " ������ ������ ����� ��� �������� A, B, C ��������� ������ "

		<< arrSize[0] << " :" << N << endl;

	printArray(generalABC, arrSize[0]);

	// ����� �� ����� ����������� ������� ����� ��������� ��� �������� A � C

	cout
		<< " ������ ������ ����� ��� �������� A � C ��������� ������ "

		<< arrSize[2] << " :" << N << endl;

	printArray(generalAC, arrSize[2]);

	// ����� �� ����� ����������� ������� ���������� ��������� ��� �������� A, B, C

	cout
		<< " ������ ������ ���������� ��� �������� A, B, C ��������� ������ "

		<< arrSize[1] << " :" << N << endl;

	printArray(uniqueABC, arrSize[1]);

	// ����� �� ����� ����������� ������� ������������� ��������� ��� �������� A, B, C

	cout
		<< " ������ ������ ������������� ��������� ��� �������� A, B, C ������ "

		<< arrSize[3] << " :" << N << endl;

	printArray(negativeABC, arrSize[3]);

	// �������� �������� ����� ���������� ���������

	arrayA = delArray(arrayA, rowCol[0][0]);	// �������� ���������� ������� A

	arrayB = delArray(arrayB, rowCol[1][0]);	// �������� ���������� ������� B

	arrayC = delArray(arrayC, rowCol[2][0]);	// �������� ���������� ������� C

	rowCol = delArray(rowCol, 3);				// �������� ���������� ������� ����� � �������

	generalABC = delArray(generalABC);		// �������� ����������� ������� ����� ��������� �������� A, B, C

	uniqueABC = delArray(uniqueABC);		// �������� ����������� ������� ���������� ��������� �������� A, B, C

	generalAC = delArray(generalAC);		// �������� ����������� ������� ����� ��������� �������� A, C

	negativeABC = delArray(negativeABC);	// �������� ����������� ������� ������������� ��������� �������� A, B, C

	arrSize = delArray(arrSize);			// �������� ����������� ������� ���� ��������

	//--------------------------------------------

	return 0;
}