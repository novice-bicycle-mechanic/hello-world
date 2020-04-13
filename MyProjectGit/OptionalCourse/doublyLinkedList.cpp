// doublyLinkedList.cpp

#include <iostream>
#include <clocale>
#include <conio.h>

#define N "\n"

using namespace std;


//-------------------------------------------------------------------------


struct Item							// структура типа элемента двусвязного списка
{
	int num = 0;					// номер элемента

	Item* next = nullptr;			// указатель на следующий элемент двусвязного списка

	Item* prev = nullptr;			// указатель на предыдущий элемент двусвязного списка
};


//-------------------------------------------------------------------------


int itemNumber					// ФУНКЦИЯ генерации номера элемента списка
(
	bool notReset				// ключ 1/0 не обнуления статической переменной number
)
{
	static int number = 0;

	return (notReset) ? (++number) : (number = 0);
}


//-------------------------------------------------------------------------


void listOutput
(
	Item* List					// указатель на список
)
{
	if (List)
	{
		Item* buf = List;

		cout << " Список >";

		while ((buf->next) != nullptr)
		{
			cout << " " << buf->num;

			buf = buf->next;
		}

		cout << " " << buf->num << N << endl;
	}
	else 
	{
		cout << " Список отсутствует" << N << endl;
	}
}


//-------------------------------------------------------------------------


void outBackAndForth
(
	Item* List					// указатель на список
)
{

	Item* buf = List;

	cout << " Проход по списку туда и обратно >";

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
	Item* List					// указатель на список
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
	Item* List					// указатель на список
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
	Item* List,					// указатель на список

	size_t length				// количество удаляемых элементов
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


void delList				// удаление всех элементов списка
(
	Item* List					// указатель на список
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

		listOutput(List);							// вывод списка на экран

		num--;
	}

	delete List;

	List = nullptr;

	listOutput(List);							// вывод списка на экран
}


//-------------------------------------------------------------------------


int main()
{
	setlocale(LC_ALL, "ru");

	//--------------------------------------

	size_t length = 0;							// количество добавляемых элементов списка

	Item* List = new Item;

	List->num = itemNumber(1);					// присвоить номер 1 первому элементу списка

	cout << " Создан двусвязный список из одного элемента" << N << endl;

	listOutput(List);							// вывод списка на экран

	cout << " К двусвязному списку добавлен один элемент" << N << endl;

	addItem(List);								// добавить элемент к списку

	listOutput(List);							// вывод списка на экран

	cout << " Укажите количество добавляемых элементов списка: ";

	cin >> length;

	cout << endl;

	for (size_t i = 0; i < length; i++)
	{
		addItem(List);
	}

	listOutput(List);							// вывод списка на экран

	cout
		<< " Вывод элементов двусвязного списка в порядке внутренних указателей,"

		N N"     сначала от первого к следующему, и так до последнего,"

		N N"     затем от последнего к предыдущему, и так до первого."

		<< N << endl;

	outBackAndForth(List);		// вывод элементов списка от первого к последнему и обратно

	cout << " У двусвязного списка удален один элемент" << N << endl;

	delItem(List);				// удаление одного элемента двусвязного списка

	listOutput(List);			// вывод списка на экран

	outBackAndForth(List);		// вывод элементов списка от первого к последнему и обратно

	cout << " Укажите количество удаляемых элементов списка: ";

	cin >> length;

	cout << endl;

	delItemN(List, length);		// удалить указанное количество элементов списка, но не первый

	listOutput(List);			// вывод списка на экран

	outBackAndForth(List);		// вывод элементов списка от первого к последнему и обратно

	cout << " Удаление всех элементов списка - удаление всего списка" << N << endl;

	delList(List);				// удаление всех элементов списка и самого списка

	//--------------------------------------

	return 0;
}