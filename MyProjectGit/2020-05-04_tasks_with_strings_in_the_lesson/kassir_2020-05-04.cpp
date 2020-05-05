// задача о размене купюр кассиром
// есть билетная касса без денег
// билет стоит 25 денег
// деньги могут быть достоиноством 25, 50, 100
// стоит очередь за билетами
// у каждого в очереди одна купюра в 25 или 50 или 100 денег
// сможет ли кассир обслужить очередь без отказа из-за отсутствия купюр для сдачи

#include <iostream>
#include <ctime>
using namespace std;



int main() {
	setlocale(LC_ALL, "");
	srand((unsigned int)time(0));
	rand(); rand(); rand(); rand();
	const size_t length = 10;
	int ochered[length]{};
	for (size_t i = 0; i < length; i++)
	{
		ochered[i] = rand() * 3 / RAND_MAX;
	}
	for (size_t i = 0; i < length; i++)
	{
		ochered[i] = (ochered[i] == 0) ? (25) : ((ochered[i] == 1) ? (50) : (100));
	}
	for (size_t i = 0; i < length; i++)
	{
		cout << " " << ochered[i];
	}
	cout << endl;
	int kupyra25 = 0;
	int kupyra50 = 0;
	int kupyra100 = 0;
	bool obslujivanie = true;
	for (size_t i = 0; i < length; i++)
	{
		if (ochered[i] == 25) { kupyra25++; }
		else if ((ochered[i] == 50) && (kupyra25 > 0)) { kupyra50++; }
		else if ((ochered[i] == 100) && ((kupyra25 >= 3) || (kupyra50 >= 1) && (kupyra25 >= 1))) { kupyra100++; }
		else 
		{
			obslujivanie = false;
			cout << " Отказ в обслуживании клиента № " << (i+1) << endl;
			break;
		}
	}
	if (obslujivanie) cout << " Очередь обслужена полностью" << endl;
	return 0;
}



