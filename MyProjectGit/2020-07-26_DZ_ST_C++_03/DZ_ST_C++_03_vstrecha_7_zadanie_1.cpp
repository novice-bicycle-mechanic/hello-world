// ������� �� ����� DZ_ST_C++_03.pdf
// ������� �7
// ����: ���������� ���������� � ����������.
//       ���������� ���������� ����������.
//       ������� �� ������.
//       ���������� ��������� ������������
// ������� 1.
/*
������� ����� Overcoat (������� ������).
����������� ������������� ���������:
1. �������� �� ��������� ����� ������ (�������� ==).
2. �������� ������������ ������ ������� � ������ (�������� =).
3. ��������� �� ���� ���� ������ ������ ���� (�������� >).
*/

#include <iostream>
#include <clocale>
using namespace std;


class Overcoat {
public:
	//������� ������: ����� ������  ������  ����   ����
	//              OVERCOAT    VOID    JACKET    COAT       CLOAK   FUR_COAT
	enum class	OVERCOAT { VOID, JACKET, COAT, CLOAK, FUR_COAT };

private:
	OVERCOAT clothes{ OVERCOAT::VOID };
	int price{ 0 };

	const char* name_overcoat[5]{ "�����","������","������","����","����" };

public:
	Overcoat(){}
	Overcoat(OVERCOAT clothes, int price) : clothes(clothes), price(price) {}

	const char* name_clothes(OVERCOAT clothes) const {
	}

	// ����� ���������� ��������� =
	Overcoat operator=(const Overcoat& overcoat) {
		this->clothes = overcoat.clothes;
		this->price = overcoat.price;
		return *this;
	}

	// �������� ������������� ������� ������ ������������ ����� �� ������� ���������� <<
	friend std::ostream& operator<<(std::ostream& out, const Overcoat& overcoat);

	// �������� ������������� ������� ���������� ��������� ==
	friend bool operator==(const Overcoat& overcoat1, const Overcoat& overcoat2);

	// �������� ������������� ������� ���������� ��������� >
	friend bool operator>(const Overcoat& overcoat1, const Overcoat& overcoat2);
};


// ������������� ������� ������ ������� �� ������� ���������� <<
std::ostream& operator<<(std::ostream& out, const Overcoat& overcoat) {
	switch (overcoat.clothes)
	{
	case Overcoat::OVERCOAT::VOID: out << overcoat.name_overcoat[(int)Overcoat::OVERCOAT::VOID];
		break;
	case Overcoat::OVERCOAT::JACKET: out << overcoat.name_overcoat[(int)Overcoat::OVERCOAT::JACKET];
		break;
	case Overcoat::OVERCOAT::COAT: out << overcoat.name_overcoat[(int)Overcoat::OVERCOAT::COAT];
		break;
	case Overcoat::OVERCOAT::CLOAK: out << overcoat.name_overcoat[(int)Overcoat::OVERCOAT::CLOAK];
		break;
	case Overcoat::OVERCOAT::FUR_COAT: out << overcoat.name_overcoat[(int)Overcoat::OVERCOAT::FUR_COAT];
		break;
	default:
		break;
	}
	out << " " << overcoat.price << " ���.";
	return out;
}
// ����� ������������� ������� ��������� <<


// ������������� ������� ���������� ��������� ==
bool operator==(const Overcoat& overcoat1, const Overcoat& overcoat2) {
	return overcoat1.clothes == overcoat2.clothes;
}
// ����� ������������� ������� ��������� ==


// ������������� ������� ���������� ��������� >
bool operator>(const Overcoat& overcoat1, const Overcoat& overcoat2) {
		return overcoat1.price > overcoat2.price;
}
// ����� ������������� ������� ��������� >


int main() {
	setlocale(LC_ALL, "ru");

	Overcoat ������1(Overcoat::OVERCOAT::COAT, 1500);
	Overcoat ������2(Overcoat::OVERCOAT::COAT, 1400);

	Overcoat ������3(Overcoat::OVERCOAT::JACKET, 1300);
	Overcoat ������4(Overcoat::OVERCOAT::JACKET, 1200);

	Overcoat ������5(Overcoat::OVERCOAT::CLOAK, 1100);
	Overcoat ������6(Overcoat::OVERCOAT::CLOAK, 1300);

	cout << " �������� �������� ������:" << endl;

	int number{ 0 };

	cout << " " << ++number << " " << ������1 << endl;
	cout << " " << ++number << " " << ������2 << endl;
	cout << " " << ++number << " " << ������3 << endl;
	cout << " " << ++number << " " << ������4 << endl;
	cout << " " << ++number << " " << ������5 << endl;
	cout << " " << ++number << " " << ������6 << endl;

	cout << " �������� ����� ������� ������ �� ��������� " << ������1 << ":" << endl;
	Overcoat ������7 = ������1;
	cout << " " << ++number << " " << ������7 << endl;

	cout
		<< " ��� ������ \""
		<< ������1
		<< "\""
		<< (������1 == ������2 ? "" : "��")
		<< " ��������� � ����� ������ \""
		<< ������2
		<< "\""
		<< endl;

	cout
		<< " ��� ������ \""
		<< ������3
		<< "\""
		<< (������3 == ������2 ? "" : "��")
		<< " ��������� � ����� ������ \""
		<< ������2
		<< "\""
		<< endl;

	cout
		<< " ������ \""
		<< ������1
		<< "\""
		<< " ����� "
		<< (������1 > ������2 ? "" : "��")
		<< " ������, ��� ������ \""
		<< ������2
		<< "\""
		<< endl;

	cout << " �������� ������� " << ������1 << " �������� ������� " << ������6 << ": ";
	������1 = ������6;
	cout << ������1 << endl;

	return 0;
}

