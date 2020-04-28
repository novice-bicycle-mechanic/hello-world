// задание из файла "homework 18.pdf"

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <iomanip>


#define N "\n"
#define NN "\n\n"
#define NEL "\n" << endl

using namespace std;


//----------------------------------------------------------------------------------


	//                        Домашнее задание №18

	// Тема: Структуры

	//                       Встреча №36. Задание 2

	//     Реализовать  структуру  «Автомобиль»  (длина, клиренс (высота
	// посадки),  объем  двигателя,  мощность  двигателя,  диаметр колес,
	// цвет, тип коробки передач). Создайте функции для задания значений,
	// отображения значений, поиска значений.


//----------------------------------------------------------------------------------


void header							// ФУНКЦИЯ вывода заголовка экрана
(
	void
)
{
	system("cls");

	cout
		<< "                       Домашнее задание №18"

		NN " Тема: Структуры"

		NN "                      Встреча №36. Задание 2"

		NN "     Реализовать  структуру  «Автомобиль»  (длина,  клиренс (высота"

		NN " посадки),  объем  двигателя,  мощность  двигателя,  диаметр колес,"

		NN " цвет, тип коробки передач). Создайте функции для задания значений,"

		NN " отображения значений, поиска значений."

		N " ----------------------------------------------------------------------"

		<< endl;

	//------------------------------------------

	SetConsoleOutputCP(CP_UTF8);	// задаем кодовую страницу для символов Юникода

	// создаем в стеке строку меню из символов Юникода

	wchar_t s[] = L"\
\
 Выбор номера автомобиля клавишами: [F1]-[F8],[Home],[End],[←],[→]\
\n\n\
 Выбор характеристики для изменения: [1]-[8]-по номеру, [0]-все подряд\
\n\n\
 Поиск характеристики по значению / всех значений: [g] или [п]\
\n\n\
 [ESC]-выход из программы / изменения, [Enter]-ввод значения";

	// определяем размер в байтах строки "s" состоящей из символов Юникода

	int bufferSize = WideCharToMultiByte(CP_UTF8, 0, s, -1, NULL, 0, NULL, NULL);

	// создаем в динамической памяти char-массив в байтах под строку из s

	LPSTR m = new char[bufferSize];

	// конвертируем строку s из символов Юникода в char-строку m

	WideCharToMultiByte(CP_UTF8, 0, s, -1, m, bufferSize, NULL, NULL);

	cout << m << endl;			// выводим полученную строку на экран

	SetConsoleCP(1251);

	SetConsoleOutputCP(1251);

	cout << " ----------------------------------------------------------------------" << endl;
}


//----------------------------------------------------------------------------------


struct CAR										// тип - автомобиль
{
	char name[32]{ '\0' };						// имя / модель автомобиля

	size_t length = 0;							// длина автомобиля

	size_t clearance = 0;						// клиренс - высота дорожного просвета

	double engineVolume = 0;					// объем двигателя

	size_t enginePower = 0;						// мощность двигателя

	size_t diameterOfWheels = 0;				// диаметр колес

	char color[32]{ '\0' };						// цвет

	char transmissionType[32]{ '\0' };			// тип коробки переключения передач
} Car;

const size_t numCars = 9;						// количество автомобилей (уменьшить на 1)

CAR cars[numCars]{};							// массив автомобилей (номера использовать с 1 до (numCars-1)

const char* featureName[] =						// имена характеристик автомобиля
{
	" Характеристики автомобиля № ",

	" 1.Имя или модель: "," 2.Длина, мм: "," 3.Клиренс, мм: "," 4.Объем двигателя, литров: ",

	" 5.Мощность двигателя, л.с.: "," 6.Диаметр колес, мм: "," 7.Цвет: "," 8.Тип коробки передач: "
};


//----------------------------------------------------------------------------------


void getValues				// ФУНКЦИЯ отображения значений характеристик автомобиля
(
	CAR car,							// структура "автомобиль"

	size_t numCar = 1					// номер автомобиля в массиве
)
{
	streamsize indent = 30;				// отступ правой границы имени характеристики от левого края экрана

	cout << setw(indent) << featureName[0] << numCar << NEL;

	cout << setw(indent) << featureName[1] << car.name << NEL;
	
	cout << setw(indent) << featureName[2] << car.length << NEL;

	cout << setw(indent) << featureName[3] << car.clearance<< NEL;

	cout << setw(indent) << featureName[4] << car.engineVolume << NEL;

	cout << setw(indent) << featureName[5] << car.enginePower << NEL;

	cout << setw(indent) << featureName[6] << car.diameterOfWheels << NEL;

	cout << setw(indent) << featureName[7] << car.color << NEL;

	cout << setw(indent) << featureName[8] << car.transmissionType << endl;

	cout << " ----------------------------------------------------------------------" << endl;
}


//----------------------------------------------------------------------------------


bool setValue				// ФУНКЦИЯ задания значений характеристик автомобиля
(
	CAR& car,								// структура "автомобиль"

	size_t num								// номер изменяемой характеристики
)
{
	unsigned char byte1char = 0;			// первый байт кода символа / нажатия клавиши

	enum keys {Enter = 13, ESC = 27};		// коды нажатий клавиш

	bool notFirstChar = false;				// ключ "вводимый символ не первый"

	size_t numMax = 0;						// максимальное значение числовой характеристики

	double numValueToEnter = 0;				// вводимое числовое значение

	char lineToEnter[32]{ '\0' };			// вводимая строка

	size_t indexStr = 0;					// индекс вводимой строки

	bool changeMode = true;					// ключ "режим изменения"

	bool decimalPoint = false;				// ключ "десятичная точка" на порядок ввода вещественного числа

	double multiplierForDecPoint = 0.1;		// множитель разряда цифры числа за десятичной точкой




	do										// выбор указанной изменяемой характеристики
	{
		switch (num)
		{
		case 1:
		{
			cout << featureName[num] << car.name << " изменить на ";

			break;
		}
		case 2:
		{
			cout << featureName[num] << car.length << " изменить на ";

			numMax = 10000;

			break;
		}
		case 3:
		{
			cout << featureName[num] << car.clearance << " изменить на ";

			numMax = 1000;

			break;
		}
		case 4:
		{
			cout << featureName[num] << car.engineVolume << " изменить на ";

			numMax = 10;

			break;
		}
		case 5:
		{
			cout << featureName[num] << car.enginePower << " изменить на ";

			numMax = 1000;

			break;
		}
		case 6:
		{
			cout << featureName[num] << car.diameterOfWheels << " изменить на ";

			numMax = 1000;

			break;
		}
		case 7:
		{
			cout << featureName[num] << car.color << " изменить на ";

			break;
		}
		case 8:
		{
			cout << featureName[num] << car.transmissionType << " изменить на ";

			break;
		}
		}

		do										// ввод значения указанной характеристики
		{
			byte1char = _getch();				// считали первый байт символа / нажатия

			if (_kbhit()) (void)_getch();		// если есть, "считали" второй байт нажатия

			if (byte1char == ESC)
			{
				return false;
			}

			if ((byte1char != Enter)

				&& (2 <= num) && (num <= 6)

				&& (('1' <= byte1char) && (byte1char <= '9')

					|| ((notFirstChar) && (byte1char == '0'))

					|| ((num == 4) && (notFirstChar) && (!decimalPoint) && (byte1char == '.'))

					)
				)
			{
				if (num == 4)
				{
					if (decimalPoint)
					{
						numValueToEnter = numValueToEnter + (byte1char - '0') * multiplierForDecPoint;

						multiplierForDecPoint /= 10;
					}
					else if (byte1char == '.')
					{
						decimalPoint = true;
					}
					else
					{
						numValueToEnter = numValueToEnter * 10 + (byte1char - '0');
					}
				}
				else
				{
					numValueToEnter = numValueToEnter * 10 + (byte1char - '0');
				}

				if (numValueToEnter <= numMax)
				{
					cout << byte1char;

					byte1char = 0;

					if ((num != 4) && ((numValueToEnter * 10) > numMax))
					{
						byte1char = Enter;
					}
				}
				else
				{
					numValueToEnter /= 10;

					byte1char = Enter;
				}

				notFirstChar = true;
			}
			else if ((byte1char != Enter) && ((num == 1) || (num == 7) || (num == 8)))
			{
				lineToEnter[indexStr++] = byte1char;

				cout << byte1char;

				byte1char = 0;
			}

			if (byte1char == Enter)
			{
				if ((2 <= num) && (num <= 6))
				{
					switch (num)
					{
					case 2:
					{
						car.length = (size_t)numValueToEnter;

						break;
					}
					case 3:
					{
						car.clearance = (size_t)numValueToEnter;

						break;
					}
					case 4:
					{
						car.engineVolume = numValueToEnter;

						break;
					}
					case 5:
					{
						car.enginePower = (size_t)numValueToEnter;

						break;
					}
					case 6:
					{
						car.diameterOfWheels = (size_t)numValueToEnter;

						break;
					}
					}
				}
				else if ((num == 1) || (num == 7) || (num == 8))
				{
					switch (num)
					{
					case 1:
					{
						for (size_t i = 0; i < 32; i++)
						{
							car.name[i] = lineToEnter[i];
						}

						break;
					}
					case 7:
					{
						for (size_t i = 0; i < 32; i++)
						{
							car.color[i] = lineToEnter[i];
						}

						break;
					}
					case 8:
					{
						for (size_t i = 0; i < 32; i++)
						{
							car.transmissionType[i] = lineToEnter[i];
						}

						break;
					}
					}

				}

				byte1char = 0;

				changeMode = false;

				break;
			}

		} while (true);

	} while (changeMode);

	return false;
}


//----------------------------------------------------------------------------------


template <typename T>

T* linkStructMem
(
	CAR cars[],								// массив структур "автомобиль"

	size_t numCar,							// номер автомобиля

	size_t numAnalyzCharac,					// номер анализируемой характеристики

	T type									// образец типа
)
{
	char* a = cars[numCar].name;

	size_t* b = &cars[numCar].length;

	size_t* c = &cars[numCar].clearance;

	double* d = &cars[numCar].engineVolume;

	size_t* e = &cars[numCar].enginePower;

	size_t* f = &cars[numCar].diameterOfWheels;

	char* g = cars[numCar].color;

	char* h = cars[numCar].transmissionType;

	switch (numAnalyzCharac)
	{
	case 1: return (T*)a;

	case 2: return (T*)b;

	case 3: return (T*)c;

	case 4: return (T*)d;

	case 5: return (T*)e;

	case 6: return (T*)f;

	case 7: return (T*)g;

	case 8: return (T*)h;
	}

	return 0;
}


//----------------------------------------------------------------------------------


template <typename T>

bool compare						// ФУНКЦИЯ сравнения анализируемой характеристики с заданным значением
(
	CAR cars[],								// массив структур "автомобиль"

	size_t numCar,							// номер автомобиля

	size_t numAnalyzCharac,					// номер анализируемой характеристики

	char parseOperation,					// операция анализа

	T valueForAnalysis						// значение для анализа
)
{
	if (parseOperation == '=')
	{
		if (*linkStructMem(cars, numCar, numAnalyzCharac, valueForAnalysis) == valueForAnalysis) return true;

		else return false;	
	}
	else if (parseOperation == '<')
	{
		if (*linkStructMem(cars, numCar, numAnalyzCharac, valueForAnalysis) < valueForAnalysis) return true;

		else return false;
	}
	if (parseOperation == '>')
	{
		if (*linkStructMem(cars, numCar, numAnalyzCharac, valueForAnalysis) > valueForAnalysis) return true;

		else return false;
	}

	return 0;
}


//----------------------------------------------------------------------------------


bool searchForObjects				// ФУНКЦИЯ поиска объектов
(
	CAR cars[],								// массив структур "автомобиль"

	size_t length,							// длина массива структур "автомобиль"

	size_t numAnalyzCharac,					// номер анализируемой характеристики

	char parseOperation,					// операция анализа

	char lineToEnter[],						// вводимая строка

	size_t numCharacToSelect				// номер характеристики для отбора
)
{
	double valueForAnalysis = 0;			// значение для анализа

	unsigned char byte1char = 0;			// первый байт кода символа / нажатия клавиши

	enum keys { Enter = 13, ESC = 27 };		// коды нажатий клавиш

	size_t numMax = 0;						// максимальное значение числовой характеристики

	size_t indexStr = 0;					// индекс вводимой строки

	size_t indexStrMax = 31;				// индекс вводимой строки максимальный

	bool changeMode = true;					// ключ "режим изменения"

	bool decimalPoint = false;				// ключ "десятичная точка" на порядок ввода вещественного числа

	double multiplierForDecPoint = 0.1;		// множитель разряда цифры числа за десятичной точкой

	char compareSign = '\0';				// знак сравнения: = , < , >

	bool numCompare = false;				// ключ на ввод числа после знака сравнения

	bool notFirstChar = false;				// ключ "не первый символ"

	if (parseOperation == '+')
	{
		cout << featureName[numAnalyzCharac] << NEL;

		{
			bool z = false;

		for (size_t i = 1; i < length; i++)
		{
			switch (numAnalyzCharac)
			{
			case 1: if (cars[i].name[0])             { cout << " • " << cars[i].name;             z = true; break; } else continue;

			case 2: if (cars[i].length)              { cout << " • " << cars[i].length;           z = true; break; } else continue;

			case 3: if (cars[i].clearance)           { cout << " • " << cars[i].clearance;        z = true; break; } else continue;

			case 4: if (cars[i].engineVolume)        { cout << " • " << cars[i].engineVolume;     z = true; break; } else continue;

			case 5: if (cars[i].enginePower)         { cout << " • " << cars[i].enginePower;      z = true; break; } else continue;

			case 6: if (cars[i].diameterOfWheels)    { cout << " • " << cars[i].diameterOfWheels; z = true; break; } else continue;

			case 7: if (cars[i].color[0])            { cout << " • " << cars[i].color;            z = true; break; } else continue;

			case 8: if (cars[i].transmissionType[0]) { cout << " • " << cars[i].transmissionType; z = true; break; } else continue;
			}
		}

			cout << (z ? " • " : " Нет значений") << NEL;
		}

	}
	else if ((2 <= numAnalyzCharac) && (numAnalyzCharac <= 6))
	{
		cout << featureName[numAnalyzCharac];

		do
		{
			byte1char = _getch();				// считали первый байт символа / нажатия

			if (_kbhit()) (void)_getch();		// если есть, "считали" второй байт нажатия

			if (byte1char == ESC)
			{
				return true;
			}
			else if ((byte1char == '=') || (byte1char == '<') || (byte1char == '>'))
			{
				parseOperation = byte1char;

				cout << byte1char << " ";

				byte1char = 0;

				break;
			}

		} while (true);

		do
		{
			byte1char = _getch();				// считали первый байт символа / нажатия

			if (_kbhit()) (void)_getch();		// если есть, "считали" второй байт нажатия

			if (byte1char == ESC)
			{
				return true;
			}

			if ((('1' <= byte1char) && (byte1char <= '9')) || (notFirstChar &&(byte1char == '0')))
			{
				notFirstChar = true;

				valueForAnalysis = valueForAnalysis * 10 + (byte1char - '0');

				cout << byte1char;

				byte1char = 0;

				if (valueForAnalysis > 999'999)	byte1char = Enter;
			}

			if (byte1char == Enter)
			{
				cout << NEL;

				break;
			}

		} while (true);

		cout
			<< " Результат поиска выражения {"

			<< featureName[numAnalyzCharac] << parseOperation << " " << valueForAnalysis << "}"
			
			NN " для характеристики {" << featureName[numCharacToSelect] << "}"

			<< NEL;

		{
			bool z = false;

		for (size_t i = 1; i < length; i++)
		{
			if (numAnalyzCharac == 4)
			{
				if (compare<double>(cars, i, numAnalyzCharac, parseOperation, (double)valueForAnalysis))
				{
					switch (numCharacToSelect)
					{
					case 1: if (cars[i].name[0])             { cout << featureName[numCharacToSelect] << cars[i].name;             z = true; break; } else continue;

					case 2: if (cars[i].length)              { cout << featureName[numCharacToSelect] << cars[i].length;           z = true; break; } else continue;

					case 3: if (cars[i].clearance)           { cout << featureName[numCharacToSelect] << cars[i].clearance;        z = true; break; } else continue;

					case 4: if (cars[i].engineVolume)        { cout << featureName[numCharacToSelect] << cars[i].engineVolume;     z = true; break; } else continue;

					case 5: if (cars[i].enginePower)         { cout << featureName[numCharacToSelect] << cars[i].enginePower;      z = true; break; } else continue;

					case 6: if (cars[i].diameterOfWheels)    { cout << featureName[numCharacToSelect] << cars[i].diameterOfWheels; z = true; break; } else continue;

					case 7: if (cars[i].color[0])            { cout << featureName[numCharacToSelect] << cars[i].color;            z = true; break; } else continue;

					case 8: if (cars[i].transmissionType[0]) { cout << featureName[numCharacToSelect] << cars[i].transmissionType; z = true; break; } else continue;
					}

					cout << NEL;
				}
			}
			else 
			{
				if (compare<size_t>(cars, i, numAnalyzCharac, parseOperation, (size_t)valueForAnalysis))
				{
					switch (numCharacToSelect)
					{
					case 1: if (cars[i].name[0])             { cout << featureName[numCharacToSelect] << cars[i].name;             z = true; break; } else continue;

					case 2: if (cars[i].length)              { cout << featureName[numCharacToSelect] << cars[i].length;           z = true; break; } else continue;

					case 3: if (cars[i].clearance)           { cout << featureName[numCharacToSelect] << cars[i].clearance;        z = true; break; } else continue;

					case 4: if (cars[i].engineVolume)        { cout << featureName[numCharacToSelect] << cars[i].engineVolume;     z = true; break; } else continue;

					case 5: if (cars[i].enginePower)         { cout << featureName[numCharacToSelect] << cars[i].enginePower;      z = true; break; } else continue;

					case 6: if (cars[i].diameterOfWheels)    { cout << featureName[numCharacToSelect] << cars[i].diameterOfWheels; z = true; break; } else continue;

					case 7: if (cars[i].color[0])            { cout << featureName[numCharacToSelect] << cars[i].color;            z = true; break; } else continue;

					case 8: if (cars[i].transmissionType[0]) { cout << featureName[numCharacToSelect] << cars[i].transmissionType; z = true; break; } else continue;
					}

					cout << NEL;
				}
			}
		}

		cout << (z ? "" : " Нет значений соответствующих условию") << NEL;
		}
	}
	else if ((numAnalyzCharac == 1) || (numAnalyzCharac == 7) || (numAnalyzCharac == 8))
	{
		cout << featureName[numAnalyzCharac];

		for (size_t i = 0; i < indexStrMax; i++)
		{
			byte1char = _getch();				// считали первый байт символа / нажатия

			if (_kbhit()) (void)_getch();		// если есть, "считали" второй байт нажатия

			if (byte1char == ESC)
			{
				return true;
			}
			else if ((31 < byte1char) && (byte1char <= 256))
			{
				lineToEnter[i] = byte1char;

				cout << byte1char;

				byte1char = 0;
			}
			else if (byte1char == Enter)
			{
				break;
			}
		}

		cout << NEL;

		cout
			<< " Результат поиска вхождения строки {" << lineToEnter << "}"

			NN " в строку характеристики № " << numCharacToSelect
			
			<< " {" << featureName[numCharacToSelect] << "}"

			<< NEL;

		char* strAnalyzCharac = nullptr;

		bool entry = false;					// индикатор вхождения строки условия в строку характеристики

		for (size_t i = 1; i < length; i++)
		{
			switch (numAnalyzCharac)
			{
			case 1: strAnalyzCharac = cars[i].name; break;

			case 7: strAnalyzCharac = cars[i].color; break;

			case 8: strAnalyzCharac = cars[i].transmissionType; break;
			}

			size_t j = 0;

			size_t k = 0;

			while
				(
				(j < indexStrMax) && (k < indexStrMax)
				
				&& (strAnalyzCharac[0] != '\0') && (lineToEnter[0] != '\0')
				)
			{

				if (
					(!entry) && (strAnalyzCharac[j] != lineToEnter[k])
					
					&& (strAnalyzCharac[j] != '\0') && (lineToEnter[k] != '\0')					
					)
				{
					j++;
				}
				else
					if
					(
						(!entry) && (strAnalyzCharac[j] == lineToEnter[k])
						
						&& (strAnalyzCharac[j] != '\0') && (lineToEnter[k] != '\0')
					)
					{
						j++;

						k++;

						entry = true;
					}
				else
					if
					(
						(entry) && (strAnalyzCharac[j] == lineToEnter[k])

						&& (strAnalyzCharac[j] != '\0') && (lineToEnter[k] != '\0')
					)
					{
						j++;

						k++;
					}
				else if	((entry) && (lineToEnter[k] == '\0'))
				{
					break;
				}
				else if ((strAnalyzCharac[j] == '\0') && (lineToEnter[k] != '\0'))
				{
					entry = false;

					break;
				}
			}

			if(entry)
			{
				switch (numCharacToSelect)
				{
				case 1: if (cars[i].name[0])             { cout << featureName[numCharacToSelect] << cars[i].name;             break; } else continue;

				case 2: if (cars[i].length)              { cout << featureName[numCharacToSelect] << cars[i].length;           break; } else continue;

				case 3: if (cars[i].clearance)           { cout << featureName[numCharacToSelect] << cars[i].clearance;        break; } else continue;

				case 4: if (cars[i].engineVolume)        { cout << featureName[numCharacToSelect] << cars[i].engineVolume;     break; } else continue;

				case 5: if (cars[i].enginePower)         { cout << featureName[numCharacToSelect] << cars[i].enginePower;      break; } else continue;

				case 6: if (cars[i].diameterOfWheels)    { cout << featureName[numCharacToSelect] << cars[i].diameterOfWheels; break; } else continue;

				case 7: if (cars[i].color[0])            { cout << featureName[numCharacToSelect] << cars[i].color;            break; } else continue;

				case 8: if (cars[i].transmissionType[0]) { cout << featureName[numCharacToSelect] << cars[i].transmissionType; break; } else continue;
				}

				cout << NEL;
			}
			else 
			{
				continue;			
			}
		}

		cout << (entry ? "" : " Нет значений соответствующих условию") << NEL;
	}

	return false;
}


//----------------------------------------------------------------------------------


int main()
{
	SetConsoleCP(1251);

	SetConsoleOutputCP(1251);

	//------------------------------------------

	size_t numCar = 1;						// номер автомобиля в массиве

	int mode = 1;							// режим работы: 1/(1,9)/(2,3)/0 - просмотр / заполнение / поиск / выход

	size_t num = 1;							// номер характеристики при заполнении всех подряд, mode = 9

	char byte1char = 0;						// первый байт кода символа / нажатия клавиши

	char byte2char = 0;						// второй байт кода символа / нажатия клавиши

	enum keysC { Enter = 13, ESC = 27 };	// коды нажатий клавиш (byte1char)

	enum keys0								// коды нажатий клавиш (byte2char, byte1char = 0)
	{
		F1 = 59, F2, F3, F4, F5, F6, F7, F8
	};

	enum keys224							// коды нажатий клавиш (byte2char, byte1char = 224)
	{
		HOME = 71, UP = 72, LEFT = 75, RIGHT = 77, END = 79, DOWN = 80
	};

	double numValueToEnter = 0;				// вводимое числовое значение

	char lineToEnter[32]{ '\0' };			// вводимая строка

	char objectSearch = '\0';				// объект поиска

	size_t numAnalyzCharac = 0;				// номер анализируемой характеристики

	size_t numCharacToSelect = 0;			// номер характеристики для отбора

	char parseOperation = '\0';				// операция анализа

	// зададим характеристики для нескольких автомобилей для примера

	cars[1] = { "Lada XRAY Cross",4171,215,1.6,113,(size_t)(215 * 50 / 100. * 2 + 17 * 25.4),"красный","автомат" };

	cars[2] = { "Lada 4x4 3-дв.",3740,200,1.7,83,(size_t)(185 * 75 / 100. * 2 + 16 * 25.4),"белый","механик" };

	cars[3] = { "Lada Granta",4268,180,1.6,106,(size_t)(175 * 65 / 100. * 2 + 14 * 25.4),"синий","робот" };

	cars[4] = { "Lada Vesta SE",4410,144,1.6,113,(size_t)(195 * 55 / 100. * 2 + 16 * 25.4),"черный","вариатор" };

	while (mode)
	{
		if (mode != 2)
		{
			header();

			getValues(cars[numCar], numCar);
		}
		else 
		{
			mode = 1;
		}

		while (true)										// цикл обработки меню
		{
			if (mode != 9)
			{
				byte1char = _getch();						// считали первый байт символа / нажатия

				if (_kbhit()) { byte2char = _getch(); }		// если есть, считали второй байт нажатия
			}

			if (byte1char == ESC)							// если нажато ESC
			{
				mode = 0;									// - выход из программы

				break;
			}
			
			// В строке ниже byte1char это первый байт нажатий HOME, END, LEFT, RIGHT
			// код которого -32=(224-256) в char, или 224=(-32+256) в unsigned char,
			// или 'а' в CP1251, или 'р' в CP866.

			if (byte1char == -32)	
			{
				if      (byte2char == HOME)
				{
					numCar = 1;

					break;
				}
				else if (byte2char == END)
				{
					numCar = numCars - 1;

					break;
				}
				else if (byte2char == LEFT)
				{
					numCar = (numCar > 1) ? (--numCar) : (numCar);

					break;
				}
				else if (byte2char == RIGHT)
				{
					numCar = (numCar < (numCars - 1)) ? (++numCar) : (numCar);

					break;
				}
			}

			if ((byte1char == 0) && (F1 <= byte2char) && (byte2char <= F8))	// если нажато Fn
			{
				numCar = byte2char - F1 + 1;								// - показ автомобиля № n

				break;
			}

			if (byte1char == '0')							// если нажато n == 0
			{
				header();

				getValues(cars[numCar], numCar);

				if (num <= 8)								// - перебор всех характеристик от 1 до 8
				{
					if (setValue(cars[numCar], num))		// - изменение характеристики n
					{
						mode = 0;

						break;
					}

					num++;
				}
			
				mode = (num > 8) ? (num = 1, 1) : (9);

				break;			
			}
			else if (('1' <= byte1char) && (byte1char <= '8'))				// если нажато n == 1...8
			{
				if (mode == 1)
				{
					header();

					getValues(cars[numCar], numCar);

					if (setValue(cars[numCar], (size_t)(byte1char - '0')))	// - изменение характеристики n
					{
						mode = 0;

						break;
					}
				}
				else if (mode == 2)
				{
					cout << byte1char << NEL;

					if ((objectSearch != '+') && ((byte1char == '1') || (byte1char == '7') || (byte1char == '8')))
					{
						cout
							<< " Значение характеристики № " << byte1char

							<< " должно включать {текст}" << NEL;
					}
					else if ((objectSearch != '+') && ('2' <= byte1char) && (byte1char <= '6'))
					{
						cout
							<< " Значение характеристики № " << byte1char

							<< " сравнивается с выражением {=|<|> число}" << NEL;					
					}
					else if (objectSearch == '+')
					{
					}
					else
					{

						cout << " Значение " << byte1char << " не может быть обработано" << endl;

						system("pause");

						break;
					}

					numAnalyzCharac	= (size_t)(byte1char - '0');

					parseOperation = (objectSearch == '+') ? (objectSearch) : ('\0');

					if (searchForObjects(					// - поиск объектов

						cars,								// массив структур "автомобиль"

						numCars,							// длина массива структур "автомобиль"

						numAnalyzCharac,					// номер анализируемой характеристики

						parseOperation,						// операция анализа

						lineToEnter,						// вводимая строка

						numCharacToSelect					// номер характеристики для отбора
						)
						)
					{
						mode = 0;

						break;
					}
				}

				break;
			}

			if((byte1char == 'g')||(byte1char == 'п'))
			{
				header();

				getValues(cars[numCar], numCar);

				cout << " Найти: [+]- все значения, [1]-[8]-характеристику > ";

				mode = 2;

				do
				{
					byte1char = _getch();						// считали первый байт символа / нажатия

					if (_kbhit()) { byte2char = _getch(); }		// если есть, считали второй байт нажатия

					if (byte1char == ESC)							// если нажато ESC
					{
						mode = 0;									// - выход из программы

						break;
					}

					if ((byte1char == '+') || (('1' <= byte1char) && (byte1char <= '8')))
					{
						if (byte1char == '+') cout << byte1char << NEL;

						else cout << "№ " << byte1char << NEL;

						objectSearch = byte1char;

						byte1char = 0;

						break;
					}

				} while (true);

				numCharacToSelect = (objectSearch == '+') ? (0) : ((size_t)(objectSearch - '0'));

				cout
					<< " Найти"

					<< ((objectSearch == '+') ? (" все значения ") : (" характеристику № "))

					<< ((objectSearch == '+') ? ((char)(8)) : (objectSearch))

					<< ((objectSearch == '+') ? ("") : (" по значению"))

					<< " характеристики № ";			
			}
		}
	}

	//------------------------------------------

	return 0;
}