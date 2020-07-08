// задание из файла CvetnoeZadanie_1592884834.txt
/*
Домашнее задание ::
реализовать Класс Цвет.
Цвет представлен в программе в виде элемента "цветового пространства"
(модели цвета, основанной на использовании цветовых координат)
например RGB, CMYK, CMY, HSV, HSI, LAB ... их очень много разных.
У каждой из них определённое предназначение, область применения.
Тем не менее, каждый набор координат в рамках модели соответствует определённому цвету.
У каждого цвета, в свою очередь, есть представление в системе цветовых координат
(ищите дополнительные источники, чтобы изучить предметную область лучше!).

Задачи ::
1) реализовать простейший класс Цвет
2) реализовать в виде наборов данных несколько цветовых моделей, например, CMYK, RGB, HSV.
(например, с помощью средства языка C для множественной разметки области памяти union, как мы делали на занятии)
3) реализовать набор конструкторов. Не впадайте в крайности и помните о принципе единственной ответственности!!!
4) Реализуйте функции преобразования данных из одной цветовой модели в другую
5) Реализуйте функции доступа к данным цветовой модели (аксессоры).
При этом помните о защите пользователя от самого себя.
6) Реализуйте функции вывода в консоль :: будет удобнее тестировать.

Возможно несколько сценариев :: реализуйте хотя бы один
1) неизменные данные! (класс цвет инициализируется один раз
и изменить цветовую модель невозможно, как и сменить данные на другие).
то есть, после каждого преобразования генерируется новый объект с новыми свойствами
(может оказаться сложнее, чем кажется)
2) изменяемые данные:: (мы делали так в классе)
преобразование полностью изменяет как данные, так и цветовую модель.
Нужно подумать над удобством работы с классом.
3) Оптимизированный блок данных:: данные попадая в объект
(например в конструктор в виде тройки чисел модели RGB)
сразу же конвертируются во все возможные модели. Соответственно,
при изменении данных (можно и нужно реализовать мутаторы),
изменяются все представления во всех моделях
(передаём в мутатор четвёрку чисел CMYK, тем самым задавая представление цвета в этой модели,
а в мутаторе генерируются на основе CMYK представления цвета в других моделях),
чтобы соответствовать.
*/

/*
Информация по теме:
1. Из всех возможных цветовых моделей с выводом цвета на экран компьютера
можно реализовать только RGB - она разработана для реализации цвета на экране монитора.
В данной модели излучаемые цвета получаются добавлением к черному цвету фона и смешиванием
3-х других цветов: красного (R), зеленого (G) и синего (B).
Для обозначения оттенка каждого базового цвета используется шкала от 0 до 255.
Составной цвет обозначается триадой чисел оттенков базовых цветов: например,
255.255.255 - белый, 0.0.0 - черный, 255.0.0 - красный, 0.255.0 - зеленый, 0.0.255 - синий.
2. Модель CMYK - это модель цвета смешанных красок на белом покрытии (белом листе бумаги).
В данной модели цвета получаются вычитанием из белого цвета подложки цветов краски:
голубого (C), пурпурного (M) и желтого (Y). При смешивании в одинаковом количестве базовых цветов
должен получиться черный цвет. В действительности получается серо-коричневый цвет.
Чтобы получить черный цвет или сочные оттенки других составных цветов в модель добавлен
чистый черный цвет (K). Отобразить полученный цвет в модели CMYK на экране монитора не возможно:
1) на экране монитора цвет излучается и суммируется к черному фону, а цвет смешанных красок
вычитается из цвета белого основания-подложки;
2) числовые значения в модели CMYK есть специальные коды для краскосмешивающих автоматов,
и получаемый цвет зависит от физико-химических свойств красок, бумаги и даже освещения
полученного печатного листа.
Поэтому, для приближенных вычислений используют модель CMY, которая есть разница
между белым цветом и значениями цветов модели RGB:
красного - для голубого, зеленого - для пурпурного, синего - для желтого.
Для упрощения подобных расчетов применяют вариант модели CMY - CMY255, в которой
цвета задаются шкалой от 0 до 255.
Полученные значения цветов корректируются до CMYK с помощью специальных таблиц.
3.Другие существующие цветовые модели также невозможно реализовать напрямую на экране монитора,
и требуется специальная конвертация.
*/

#include <iostream>
#include <clocale>
using namespace std;


// СТРУКТУРА модели RGB, значения каждого цвета 0-255
struct RGB
{
	unsigned char red{ 0 };
	unsigned char green{ 0 };
	unsigned char blue{ 0 };
};


// СТРУКТУРА модели CMY, значения каждого цвета 0-255
struct CMY
{
	unsigned char cyan{ 0 };
	unsigned char magenta{ 0 };
	unsigned char yellow{ 0 };
};


// СТРУКТУРА модели CMYK, значения каждого цвета 0-100, сумма всех цветов равна 100
struct CMYK
{
private:
	unsigned char cyan{ 0 };
	unsigned char magenta{ 0 };
	unsigned char yellow{ 0 };
	unsigned char black{ 0 };

public:
	CMYK(
		unsigned char cyan,
		unsigned char magenta,
		unsigned char yellow,
		unsigned char black
	) {
		if ((cyan <= 100) && (magenta <= 100) && (yellow <= 100) && (black <= 100) &&
			(100 == (cyan + magenta + yellow + black))) {
			this->cyan = cyan;
			this->magenta = magenta;
			this->yellow = yellow;
			this->black = black;
		}
	}

	int getCyan() const { return (int)cyan; }
	int getMagenta() const { return (int)magenta; }
	int getYellow() const { return (int)yellow; }
	int getBlack() const { return (int)black; }
};


// КЛАСС Цвет
class Color
{
private:
	union
	{
		RGB rgb;
		CMY cmy;
		CMYK cmyk;
	};
public:
	explicit Color() :Color(rgb) {}
	explicit Color(RGB rgb) :rgb{ rgb } {}
	explicit Color(CMY cmy) :cmy{ cmy } {}
	explicit Color(CMYK cmyk) :cmyk{ cmyk } {}
	explicit Color(const Color& object) { *this = object; }

	RGB getRGB() const { return rgb; }
	CMY getCMY() const { return cmy; }
	CMYK getCMYK() const { return cmyk; }

	void printRGB() {
		cout << "RGB " << (int)rgb.red << "," << (int)rgb.green << "," << (int)rgb.blue << endl;
	}

	void printCMY() {
		cout << "CMY " << (int)cmy.cyan << "," << (int)cmy.magenta << "," << (int)cmy.yellow << endl;
	}

	void printCMYK() {
		cout
			<< "CMYK "
			<< cmyk.getCyan() << ","
			<< cmyk.getMagenta() << ","
			<< cmyk.getYellow() << ","
			<< cmyk.getBlack()
			<< endl;
	}

	static CMY cmyFromCMYK(CMYK cmyk) {

		CMY cmy{
			(unsigned char)cmyk.getCyan(),
			(unsigned char)cmyk.getMagenta(),
			(unsigned char)cmyk.getYellow()
		};

		if (cmyk.getBlack()) {
			int one_third{ 0 };
			int remains{ 0 };

			one_third = cmyk.getBlack() / 3;

			cmy.cyan += one_third;
			cmy.magenta += one_third;
			cmy.yellow += one_third;

			if ((cmyk.getBlack() % 3) > 2) {
				cmy.cyan++;
				cmy.magenta++;
				cmy.yellow = 100 - cmy.cyan - cmy.magenta;
			}
			else if ((cmyk.getBlack() % 3) > 1) {
				cmy.cyan++;
				cmy.magenta = 100 - cmy.cyan - cmy.yellow;
			}
			else {
				cmy.cyan = 100 - cmy.magenta - cmy.yellow;
			}
		}

		int cyan{ 0 };
		int magenta{ 0 };
		int yellow{ 0 };

		cyan = cmy.cyan * 255 / 100;
		magenta = cmy.magenta * 255 / 100;
		yellow = cmy.yellow * 255 / 100;

		cmy.cyan = cyan;
		cmy.magenta = magenta;
		cmy.yellow = yellow;

		return cmy;
	}

	static RGB rgbFromCMY(CMY cmy) {

		RGB rgb{
			(unsigned char)(255 - cmy.cyan),
			(unsigned char)(255 - cmy.magenta),
			(unsigned char)(255 - cmy.yellow)
		};

		return rgb;
	}

	static CMY cmyFromRGB(RGB rgb) {

		CMY cmy{
			(unsigned char)(255 - rgb.red),
			(unsigned char)(255 - rgb.green),
			(unsigned char)(255 - rgb.blue)
		};

		return cmy;
	}
};



int main() {
	setlocale(LC_ALL, "ru");

//	RGB rgb{ 255,0,0 };
//	CMY cmy{ 0,0,255 };
	CMYK cmyk{ 0,0,50,50 };

	Color color1{ cmyk };
	color1.printCMYK();

	Color color2{ Color::cmyFromCMYK(cmyk) };
	color2.printCMY();

	Color color3{ Color::rgbFromCMY(Color::cmyFromCMYK(cmyk)) };
	color3.printRGB();

	Color color4{ Color::rgbFromCMY(color2.getCMY()) };
	color3.printRGB();

	Color color5{ Color::cmyFromRGB(color3.getRGB()) };
	color5.printCMY();

	return 0;
}

















