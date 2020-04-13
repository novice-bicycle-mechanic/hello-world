// doublyLinkedList.cpp

#include <iostream>
#include <clocale>
#include <conio.h>

#define N "\n"

using namespace std;


//-------------------------------------------------------------------------


struct Item							// ��������� ���� �������� ����������� ������
{
	int num = 0;					// ����� ��������

	Item* next = nullptr;			// ��������� �� ��������� ������� ����������� ������

	Item* prev = nullptr;			// ��������� �� ���������� ������� ����������� ������
};


//-------------------------------------------------------------------------


int itemNumber					// ������� ��������� ������ �������� ������
(
	bool notReset				// ���� 1/0 �� ��������� ����������� ���������� number
)
{
	static int number = 0;

	return (notReset) ? (++number) : (number = 0);
}


//-------------------------------------------------------------------------


void listOutput
(
	Item* List					// ��������� �� ������
)
{
	if (List)
	{
		Item* buf = List;

		cout << " ������ >";

		while ((buf->next) != nullptr)
		{
			cout << " " << buf->num;

			buf = buf->next;
		}

		cout << " " << buf->num << N << endl;
	}
	else 
	{
		cout << " ������ �����������" << N << endl;
	}
}


//-------------------------------------------------------------------------


void outBackAndForth
(
	Item* List					// ��������� �� ������
)
{

	Item* buf = List;

	cout << " ������ �� ������ ���� � ������� >";

	while ((buf->next) != nullptr)
	{
		cout << " " << buf->num;

		buf = buf->next;
	}

	while ((buf->prev) != nullptr)
	{
		cout << " " << buf->num;

		buf = buf->prev;
	}

	cout << " " << buf->num << N << endl;
}


//-------------------------------------------------------------------------


void addItem
(
	Item* List					// ��������� �� ������
)
{
	Item* listItem = new Item;

	Item* buf = List;

	listItem->num = itemNumber(1);

	while ((buf->next) != nullptr)
	{
		buf = buf->next;
	}

	buf->next = listItem;

	listItem->prev = buf;
}


//-------------------------------------------------------------------------


void delItem
(
	Item* List					// ��������� �� ������
)
{
	Item* buf = List;

	while ((buf->next) != nullptr)
	{
		buf = buf->next;
	}

	buf = buf->prev;

	delete buf->next;

	buf->next = nullptr;
}


//-------------------------------------------------------------------------


void delItemN
(
	Item* List,					// ��������� �� ������

	size_t length				// ���������� ��������� ���������
)
{
	Item* buf = List;

	size_t num = 0;

	while ((buf->next) != nullptr)
	{
		buf = buf->next;

		num++;
	}

	while ((num) && (length))
	{
		delItem(List);

		num--;

		length--;
	}
}


//-------------------------------------------------------------------------


void delList				// �������� ���� ��������� ������
(
	Item* List					// ��������� �� ������
)
{
	Item* buf = List;

	int num = 1;

	while ((buf->next) != nullptr)
	{
		num++;

		buf = buf->next;
	}

	while (num > 1)
	{
		buf = buf->prev;

		delete buf->next;

		buf->next = nullptr;

		listOutput(List);							// ����� ������ �� �����

		num--;
	}

	delete List;

	List = nullptr;

	listOutput(List);							// ����� ������ �� �����
}


//-------------------------------------------------------------------------


int main()
{
	setlocale(LC_ALL, "ru");

	//--------------------------------------

	size_t length = 0;							// ���������� ����������� ��������� ������

	Item* List = new Item;

	List->num = itemNumber(1);					// ��������� ����� 1 ������� �������� ������

	cout << " ������ ���������� ������ �� ������ ��������" << N << endl;

	listOutput(List);							// ����� ������ �� �����

	cout << " � ����������� ������ �������� ���� �������" << N << endl;

	addItem(List);								// �������� ������� � ������

	listOutput(List);							// ����� ������ �� �����

	cout << " ������� ���������� ����������� ��������� ������: ";

	cin >> length;

	cout << endl;

	for (size_t i = 0; i < length; i++)
	{
		addItem(List);
	}

	listOutput(List);							// ����� ������ �� �����

	cout
		<< " ����� ��������� ����������� ������ � ������� ���������� ����������,"

		N N"     ������� �� ������� � ����������, � ��� �� ����������,"

		N N"     ����� �� ���������� � �����������, � ��� �� �������."

		<< N << endl;

	outBackAndForth(List);		// ����� ��������� ������ �� ������� � ���������� � �������

	cout << " � ����������� ������ ������ ���� �������" << N << endl;

	delItem(List);				// �������� ������ �������� ����������� ������

	listOutput(List);			// ����� ������ �� �����

	outBackAndForth(List);		// ����� ��������� ������ �� ������� � ���������� � �������

	cout << " ������� ���������� ��������� ��������� ������: ";

	cin >> length;

	cout << endl;

	delItemN(List, length);		// ������� ��������� ���������� ��������� ������, �� �� ������

	listOutput(List);			// ����� ������ �� �����

	outBackAndForth(List);		// ����� ��������� ������ �� ������� � ���������� � �������

	cout << " �������� ���� ��������� ������ - �������� ����� ������" << N << endl;

	delList(List);				// �������� ���� ��������� ������ � ������ ������

	//--------------------------------------

	return 0;
}