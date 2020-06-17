// Выполнение DZ_1591895550.txt
// Домашнее задание 1 из файла C__urok_01_2020_1589461417.pdf
/*
    1. Цифровой счетчик, это переменная с ограниченным диапазоном.
Значение которой сбрасывается, когда ее целочисленное значение
достигает определенного максимума (например, k принимает значения
в диапазоне от 0...100). В качестве примера такого счетчика можно
привести цифровые часы, счетчик километража.
    Опишите класс такого счетчика. Обеспечьте возможность установления
максимального и минимального значений, увеличения счетчика на 1,
возвращения текущего значения.
*/

#include <iostream>
using namespace std;

class Counter {
private:
	int min;      // минимальное значение счетчика
	int max;      // максимальное значение счетчика
	int current;  // текущее значение счетчика
public:
	Counter(int min, int max) {
		this->min = min;
		this->max = max;
		current = min;
	}
	// вывод на экран всех значений:
	void showProperties() {
		cout << " min=" << min << " max=" << max << " current=" << current << endl;
	}
	// вывод на экран текущего значения счетчика
	void showCurrent() {
		cout << " current=" << current << endl;
	}
	// возврат текущего значения счетчика
	int outputCurrent() {
		return current;
	}
	// перезадать значения счетчика
	void setInitValues(int min, int max) {
		this->min = min;
		this->max = max;
		current = min;
	}
	// возвратить увеличенное на 1 значение счетчика (current),
	// или возвратить min, если current стало больше max
	int followingValue(){
		if (++current > max) current = min;
		return current;
	}
};

int main() {
	Counter cnt(1, 5);  // создали счетчик от 1 по 5

	cnt.showProperties();
	cnt.showCurrent();
	cout << " current value = " << cnt.outputCurrent() << endl;
	cout << " following value = " << cnt.followingValue() << endl;
	cout << " following value = " << cnt.followingValue() << endl;
	cout << " following value = " << cnt.followingValue() << endl;
	cout << " following value = " << cnt.followingValue() << endl;
	cout << " following value = " << cnt.followingValue() << endl;
	cout << " following value = " << cnt.followingValue() << endl;
	cnt.setInitValues(100, 200);
	cnt.showProperties();

	return 0;
}