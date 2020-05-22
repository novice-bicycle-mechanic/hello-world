// задание из файла "zadaci_na_fajly_1589392470.txt"
#include <clocale>
#include <cstdio>

using namespace std;

//----------------------------------------------------------------------------------
// ФУНКЦИЯ оценки символа для целей сортировки
// латинские: A-Z, a-z - 1-26 ; русские: А-Я, а-я - 101-133
size_t  rankSymbol(
	unsigned char symbol							// оцениваемый символ
) {
	if ((64 < symbol) && (symbol < 91))	{			// прописные латинские символы A-Z
		return (symbol - (unsigned char)64);
	}
	else if ((96 < symbol) && (symbol < 123)) {		// строчные латинские символы a-z
		return (symbol - (unsigned char)96);
	}
	else if ((191 < symbol) && (symbol < 198)) {	// прописные русские символы А-Е
		return (symbol - (unsigned char)91);
	}
	else if (symbol == 168) {						// прописной русский символ Ё
		return (symbol - (unsigned char)61);
	}
	else if ((197 < symbol) && (symbol < 224)) {	// прописные русские символы Ж-Я
		return (symbol - (unsigned char)90);
	}
	else if ((223 < symbol) && (symbol < 230)) {	// строчные русские символы а-е
		return (symbol - (unsigned char)123);
	}
	else if (symbol == 184)	{						// строчный русский символ ё
		return (symbol - (unsigned char)77);
	}
	else if ((229 < symbol) && (symbol < 256)) {	// строчные русские символы ж-я
		return (symbol - (unsigned char)122);
	}
	else {
		return 0;									// прочие значения
	}
}

//----------------------------------------------------------------------------------
// ФУНКЦИЯ сравнения и перестановки элементов на минимум
void minArray(
	char*& one,						// элемент 1 (должен быть меньше)
	char*& two,						// элемент 2 (должен быть больше)
	size_t index					// индекс char-массива элемента
) {
	char* buf = nullptr;			// вспомогательный указатель на элемент
	if (rankSymbol(one[index]) > rankSymbol(two[index])) {	// если 1 > 2
		buf = one;			    			// переставить элементы местами
		one = two;
		two = buf;
	}
	// иначе, если элементы равны, и не равны '\0'
	else if (
		(rankSymbol(one[index]) == rankSymbol(two[index])) &&
		(rankSymbol(one[index]) != '\0') &&
		(rankSymbol(two[index]) != '\0')) {
		// - вызвать настоящую функцию рекурсивно для сравнения
		//   следующих по порядку символов элементов
		minArray(one, two, ++index);
	}
	// если 1 < 2 или хоть один равен '\0' - ничего не делать и выйти из функции
}

//----------------------------------------------------------------------------------
// ФУНКЦИЯ сортировки массивов с фамилиями
void sortWords(
	char** words,			// массив слов
	const size_t lines		// количество строк в массиве, не более
) {
	for (size_t i = 1; i < lines; i++) {
		if (!words[i]) break;
		for (size_t j = 1; j < lines; j++) {  // j=1 !!! не j=0 !!!
			if (!words[j]) break;
			minArray(words[j - 1], words[j], 0);
		}
	}
}

//----------------------------------------------------------------------------------

int main() {
	setlocale(LC_ALL, "ru");
	printf_s("            Задание из файла \"zadaci_na_fajly_1589392470.txt\"\n\n");
	printf_s("\
     Текстовый файл содержит произвольные слова на английском языке, по \n\
 одному слову в строке, не более 40 слов в файле. Длина слова ограничена \n\
 80-ю символами. Переписать слова в другой файл, отсортировав их в \n\
 алфавитном порядке.\n\n");

	const size_t lines = 40;    // количество строк в исходном файле, не более
	const size_t columns = 80;  // количество символов в строке в исходном файле, не более

	// откроем файл с исходными словами
	const char* nameFile1 = "proverb.txt";
	FILE* firstFile = nullptr;
	FILE** ptrFirstFile = &firstFile;
	if (fopen_s(ptrFirstFile, nameFile1, "r"))	{
		printf_s(" Не удалось открыть файл %s\n", nameFile1);
		return 0;
	}
	
	// запишем слова из файла в массив
	printf_s(" Исходный набор слов из файла %s\n\n", nameFile1);
	char** words = new char* [lines] {nullptr};  // массив слов/строк
	for (size_t i = 0; i < lines; i++) {         // запишем слова из файла в массив
		words[i] = new char[(columns + 1)]{ '\0' };
		if (!fgets(words[i], columns, firstFile)) {
			delete[] words[i];
			words[i] = nullptr;
			printf_s("\n");
			break;
		}
		for (size_t j = 0; j < columns; j++) {
			if ((words[i][j] == 10) || (words[i][j] == 13)) {
				words[i][j] = '\0';
				continue;
			}
			if (words[i][j] == '\0') break;
		}
		printf_s(" %s\n", words[i]);
	}
	fclose(firstFile);

	// отсортируем слова/строки в массиве в алфавитном порядке
	sortWords(words, lines);

	// откроем файл для отсортированных слов
	const char* nameFile2 = "proverb2.txt";
	FILE* secondFile = nullptr;
	FILE** ptrSecondFile = &secondFile;
	if (fopen_s(ptrSecondFile, nameFile2, "w")) {
		printf_s(" Не удалось открыть файл %s\n", nameFile2);
		return 0;
	}

	// запишем слова из массива в файл
	for (size_t i = 0; i < lines; i++) {
		if (!words[i]) break;
		fprintf_s(secondFile, "%s\x0A", words[i]);
	}
	fclose(secondFile);

	printf_s(" Отсортированный набор слов в файле %s\n\n", nameFile2);
	for (size_t i = 0; i < lines; i++) {
		if (!words[i]) break;
		printf_s(" %s\n", words[i]);
	}

	// удалим массив слов из памяти
	for (size_t i = 0; i < lines; i++) {
		if (!words[i]) break;
		else delete[] words[i];
	}
	delete[] words;

	return 0;
}
