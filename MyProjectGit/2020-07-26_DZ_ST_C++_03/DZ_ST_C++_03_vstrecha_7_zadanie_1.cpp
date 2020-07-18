// задание из файла DZ_ST_C++_03.pdf
// Встреча №7
// Тема: Перегрузка инкремента и декремента.
//       Перегрузка логических операторов.
//       Возврат по ссылке.
//       Перегрузка оператора присваивания
// Задание 1.
/*
Создать класс Overcoat (верхняя одежда).
Реализовать перегруженные операторы:
1. Проверка на равенство типов одежды (операция ==).
2. Операцию присваивания одного объекта в другой (операция =).
3. Сравнение по цене двух пальто одного типа (операция >).
*/

#include <iostream>
#include <clocale>
using namespace std;


class Overcoat {
public:
	//ВЕРХНЯЯ ОДЕЖДА: ПУСТО КУРТКА  ПАЛЬТО  ПЛАЩ   ШУБА
	//              OVERCOAT    VOID    JACKET    COAT       CLOAK   FUR_COAT
	enum class	OVERCOAT { VOID, JACKET, COAT, CLOAK, FUR_COAT };

private:
	OVERCOAT clothes{ OVERCOAT::VOID };
	int price{ 0 };

	const char* name_overcoat[5]{ "Пусто","Куртка","Пальто","Плащ","Шуба" };

public:
	Overcoat(){}
	Overcoat(OVERCOAT clothes, int price) : clothes(clothes), price(price) {}

	const char* name_clothes(OVERCOAT clothes) const {
	}

	// Метод перегрузки оператора =
	Overcoat operator=(const Overcoat& overcoat) {
		this->clothes = overcoat.clothes;
		this->price = overcoat.price;
		return *this;
	}

	// прототип дружественной функции вывода комплексного числа на консоль оператором <<
	friend std::ostream& operator<<(std::ostream& out, const Overcoat& overcoat);

	// прототип дружественной функции перегрузки оператора ==
	friend bool operator==(const Overcoat& overcoat1, const Overcoat& overcoat2);

	// прототип дружественной функции перегрузки оператора >
	friend bool operator>(const Overcoat& overcoat1, const Overcoat& overcoat2);
};


// Дружественная ФУНКЦИЯ вывода объекта на консоль оператором <<
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
	out << " " << overcoat.price << " руб.";
	return out;
}
// КОНЕЦ дружественной ФУНКЦИИ оператора <<


// Дружественная ФУНКЦИЯ перегрузки оператора ==
bool operator==(const Overcoat& overcoat1, const Overcoat& overcoat2) {
	return overcoat1.clothes == overcoat2.clothes;
}
// КОНЕЦ дружественной ФУНКЦИИ оператора ==


// Дружественная ФУНКЦИЯ перегрузки оператора >
bool operator>(const Overcoat& overcoat1, const Overcoat& overcoat2) {
		return overcoat1.price > overcoat2.price;
}
// КОНЕЦ дружественной ФУНКЦИИ оператора >


int main() {
	setlocale(LC_ALL, "ru");

	Overcoat одежда1(Overcoat::OVERCOAT::COAT, 1500);
	Overcoat одежда2(Overcoat::OVERCOAT::COAT, 1400);

	Overcoat одежда3(Overcoat::OVERCOAT::JACKET, 1300);
	Overcoat одежда4(Overcoat::OVERCOAT::JACKET, 1200);

	Overcoat одежда5(Overcoat::OVERCOAT::CLOAK, 1100);
	Overcoat одежда6(Overcoat::OVERCOAT::CLOAK, 1300);

	cout << " Создадим предметы одежды:" << endl;

	int number{ 0 };

	cout << " " << ++number << " " << одежда1 << endl;
	cout << " " << ++number << " " << одежда2 << endl;
	cout << " " << ++number << " " << одежда3 << endl;
	cout << " " << ++number << " " << одежда4 << endl;
	cout << " " << ++number << " " << одежда5 << endl;
	cout << " " << ++number << " " << одежда6 << endl;

	cout << " Создадим новый предмет одежды на основании " << одежда1 << ":" << endl;
	Overcoat одежда7 = одежда1;
	cout << " " << ++number << " " << одежда7 << endl;

	cout
		<< " Тип одежды \""
		<< одежда1
		<< "\""
		<< (одежда1 == одежда2 ? "" : "не")
		<< " совпадает с типом одежды \""
		<< одежда2
		<< "\""
		<< endl;

	cout
		<< " Тип одежды \""
		<< одежда3
		<< "\""
		<< (одежда3 == одежда2 ? "" : "не")
		<< " совпадает с типом одежды \""
		<< одежда2
		<< "\""
		<< endl;

	cout
		<< " Одежда \""
		<< одежда1
		<< "\""
		<< " стоит "
		<< (одежда1 > одежда2 ? "" : "не")
		<< " больше, чем одежда \""
		<< одежда2
		<< "\""
		<< endl;

	cout << " Присвоим объекту " << одежда1 << " значение объекта " << одежда6 << ": ";
	одежда1 = одежда6;
	cout << одежда1 << endl;

	return 0;
}

