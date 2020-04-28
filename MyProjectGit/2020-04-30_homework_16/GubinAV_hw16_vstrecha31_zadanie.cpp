// ������� �� ����� "homework 16.pdf"
//----------------------------------------------------------------------------------
	//                        �������� ������� �16
	// ����: ������
	//                        ������� �31. �������

	//     ��������� ���� ���������� ������� ������������ ������������� �������:

	// int mystrcmp(const char* str1, const char* str2); - ������� ���������� ��� ������, �, ����
	// ������ ����� ���������� 0, ���� ������ ������ ������ ������, �� ���������� 1, ����� - 1.

	// int StringToNumber(char* str); - ������� ������������ ������ � ����� � ���������� ��� �����.

	// char* NumberToString(int  number); - ������� ������������ ����� � ������ � ����������
	// ��������� �� ��� ������.

	// char* Uppercase(char* str); - ������� ����������� ������ � ������� �������.

	// char* Lowercase(char* str); - ������� ����������� ������ � ������ �������.

	// char* mystrrev(char* str); - ������� ����������� ������ � ���������� ��������� �� ����� ������.
//----------------------------------------------------------------------------------

#include <iostream>
#include <Windows.h>

#define N "\n"
#define NN "\n\n"
#define nel "\n" << endl

using namespace std;


//--------------------------------------------------------------------------------


size_t lenStr						// ������� ��������� ����� ������
(
	const char* str							// ���������� ������
)
{
	size_t len = 0;							// ����� ������

	while (true) if (!str[len++]) return --len;
}


//--------------------------------------------------------------------------------


int mystrcmp						// ������� ��������� ���� �����
(
	const char* str1,						// ������ 1

	const char* str2						// ������ 2
)
{
	if (lenStr(str1) > lenStr(str2)) return 1;

	else if (lenStr(str1) < lenStr(str2)) return -1;

	else return 0;
}


//--------------------------------------------------------------------------------


void visualMyStringCompare			// ������� ������������ ������ ������� mystrcmp()
(
	const char* str1,						// ������ 1

	const char* str2						// ������ 2
)
{
	int estimation = mystrcmp(str1, str2);

	cout
		<< " ������ ��� ������:"
		
		N " \"" << str1 << "\"" " � \"" << str2 << "\"" << endl;

	cout
		<< " ����� ������ \"" << str1 << "\""

		N << ((estimation)
			
			? ((estimation == 1)?(" ������ �����"):(" ������ �����"))
			
			: (" ����� �����"))

		<< " ������ \""	<< str2 << "\""

		<< nel;
}


//--------------------------------------------------------------------------------


int StringToNumber					// ������� ����������� ������ � �����
(
	char* str								// �������������� ������
)
{
	int number = 0;							// ����� ���������������� �� ������

	size_t len = 0;							// ������ ������� ������

	while (true)
	{
		if (str[len])
		{
			number = number * 10 + (str[len] - '0');
		}
		else 
		{
			return number;
		}

		len++;
	}
}


//--------------------------------------------------------------------------------


char* mystrrev						// ������� �������������� ������
(
	char* str								// ������������� ������
)
{
	size_t length = lenStr(str);					// ����� ������ str

	char* rts = new char[(length + 1)]{ '\0' };		// �������� ������ ��� ��������������� ������

	// ��������� � �������� ������� ������ str � ������ rts

	for (size_t i = 0; i < length; i++)	rts[i] = str[(length - 1 - i)];

	return rts;										// ������� ��������� �� ��������������� ������
}


//--------------------------------------------------------------------------------


char* NumberToString				// ������� ����������� ����� � ������
(
	int  number								// �������������� �����
)
{
	char* digits = new char[12]{};

	size_t len = 0;

	while (number)
	{
		digits[len++] = (number % 10) + '0';

		number /= 10;
	}

	char* stigid = mystrrev(digits);

	delete[] digits;

	return stigid;
}


//--------------------------------------------------------------------------------


char charCaseLowerToUpperAndBackRu	// ������� �������� ������� �� ������� �������� � ������� � ��������
(
	char symbol,						// �������������� ������

	bool trend,							// ����������� �����������: true/false - ������->������� / �������->������

	unsigned int numCP					// ����� ������� �������� ��� �������� �������� �����
)
{
	if ((!trend) && (64 < symbol) && (symbol < 91))  return (symbol + 32);

	else if ((trend) && (96 < symbol) && (symbol < 123)) return (symbol - 32);

	else if ((!trend) && (numCP == 1251) && ((191 - 256) < symbol) && (symbol < (224 - 256))) return (symbol + 32);

	else if ((trend) && (numCP == 1251) && ((223 - 256) < symbol) && (symbol < (256 - 256))) return (symbol - 32);

	else if ((!trend) && (numCP == 1251) && (symbol == (168 - 256))) return (symbol + 16);

	else if ((trend) && (numCP == 1251) && (symbol == (184 - 256))) return (symbol - 16);

	else if ((!trend) && (numCP == 866) && ((127 - 256) < symbol) && (symbol < (160 - 256))) return (symbol + 32);

	else if ((trend) && (numCP == 866) && ((159 - 256) < symbol) && (symbol < (176 - 256))) return (symbol - 32);

	else if ((trend) && (numCP == 866) && ((223 - 256) < symbol) && (symbol < (240 - 256))) return (symbol - 80);

	else if ((!trend) && (numCP == 866) && (symbol == (240 - 256))) return (symbol + 1);

	else if ((trend) && (numCP == 866) && (symbol == (241 - 256))) return (symbol - 1);

	else return symbol;
}


//--------------------------------------------------------------------------------


char* UpperCase						// ������� ��� �������������� ������ � ������� �������
(
	char* str								// ������������� ������
)
{
	size_t length = lenStr(str);

	char* STR = new char[(length + 1)]{ '\0' };

	for (size_t i = 0; i < length; i++)
	{
		STR[i] = charCaseLowerToUpperAndBackRu(str[i], true, GetConsoleOutputCP());
	}

	return STR;
}


//--------------------------------------------------------------------------------


char* LowerCase						// ������� ��� �������������� ������ � ������ �������
(
	char* STR								// ������������� ������
)
{
	size_t length = lenStr(STR);

	char* str = new char[(length + 1)]{ '\0' };

	for (size_t i = 0; i < length; i++)
	{
		str[i] = charCaseLowerToUpperAndBackRu(STR[i], false, GetConsoleOutputCP());
	}

	return str;
}


//--------------------------------------------------------------------------------


int main()
{
	SetConsoleOutputCP(1251);

	//----------------------------------

	cout
		<< "                       �������� ������� �16"

		NN " ����: ������"

		NN "                       ������� �31. �������"

		NN "     ��������� ���� ���������� ������� ������������ ������������� �������:"

		NN " int mystrcmp(const  char*  str1,  const  char*  str2); - ������� ���������� ���"

		N  " ������, �, ����  ������  �����  ���������� 0, ���� ������ ������ ������ ������,"

		N  " �� ���������� 1, ����� - 1."

		NN " int StringToNumber(char* str);-������� ������������ ������ � ����� � ����������"

		N  " ��� �����."

		NN " char* NumberToString(int  number); - �������  ������������  �����  �  ������  �"

		N  " ���������� ��������� �� ��� ������."

		NN " char* UpperCase(char* str); - �������  �����������  ������  �  ������� �������."

		NN " char* LowerCase(char* str); - �������  �����������  ������  �  ������  �������."

		NN " char* mystrrev(char* str); - ������� ����������� ������ � ����������  ���������"

		N  " �� ����� ������."

		N  " -------------------------------------------------------------------------------"

		<< endl;

	cout << " ���������� ������� { int mystrcmp(const char* str1, const char* str2); }" << nel;

	const char* str1 = "�������, ������ ����������";

	const char* str2 = "������� ������, ����������";

	visualMyStringCompare(str1, str2);

	const char* str3 = "������� ����";

	const char* str4 = "��� �� ����� �� ����";

	visualMyStringCompare(str3, str4);

	const char* str5 = "�� ����� � ����, ������� ��������� ����";

	const char* str6 = "�� ��� ��������, �� � ���������";

	visualMyStringCompare(str5, str6);

	cout << " -------------------------------------------------------------------------------" << endl;

	cout << " ���������� ������� { int StringToNumber(char* str); }" << nel;

	char digits1[] =  "1234567890";					// ������ "�����"

	int number1 = StringToNumber(digits1);			// ����� ���������������� �� ������

	cout << " ������ ������ \"" << digits1 << "\"" << endl;

	cout
		<< " ������������ ������ " << "(" << typeid(digits1).name() << ")\"" << digits1 << "\""
		
		<< " � ����� " << "(" << typeid(number1).name() << ")" << number1
		
		<< endl;

	cout << " -------------------------------------------------------------------------------" << endl;

	cout << " ���������� ������� { char* NumberToString(int  number); }" << nel;

	int number2 = 1234567890;						// �����

	char* digits2 = NumberToString(number2);		// ������ ���������������� �� �����

	cout << " ������ ����� " << number2 << endl;

	cout
		<< " ������������ ����� " << "(" << typeid(number2).name() << ")" << number2

		<< " � ������ " << "(" << typeid(digits2).name() << ")\"" << digits2 << "\""

		<< endl;

	cout << " -------------------------------------------------------------------------------" << endl;

	cout << " ���������� ������� { char* UpperCase(char* str); }" << nel;

	// �������� ������ ��� �������������� � ������� �������

	char strLower1[] = "\"abcdefghijkimnopqrstuvwxyz ��������������������������������\"";

	// �������� ��������������� � ������� ������� ������

	char* strUpper1 = UpperCase(strLower1);

	cout << " ������ ������: " N " " << strLower1 << nel;

	cout << " ����������� � � ������� �������: " N " " << strUpper1 << endl;

	cout << " -------------------------------------------------------------------------------" << endl;

	cout << " ���������� ������� { char* LowerCase(char* str); }" << nel;

	// �������� ������ ��� �������������� � ������ �������

	char strUpper2[] = "\"ABCDEFGHIJKLMNOPQRSTUVWXYZ �����Ũ��������������������������\"";

	// �������� ��������������� � ������ ������� ������

	char* strLower2 = LowerCase(strUpper2);

	cout << " ������ ������: " N " " << strUpper2 << nel;

	cout << " ����������� � � ������ �������: " N " " << strLower2 << endl;

	cout << " -------------------------------------------------------------------------------" << endl;

	cout << " ���������� ������� { char* mystrrev(char* str); }" << nel;

	// �������� ������, ������� ����� �������������

	char str[] = "0123456789 abcdefghijkimnopqrstuvwxyz ��������������������������������";

	// ����������� ������

	char* rts = mystrrev(str);

	cout << " ������ ������: " N " " << str << nel;

	cout << " ����������� �: " N " " << rts << endl;

	cout << " -------------------------------------------------------------------------------" << endl;

	//----------------------------------

	return 0;
}
