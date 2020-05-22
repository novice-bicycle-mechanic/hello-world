// ������� �� ����� "zadaci_na_fajly_1589392470.txt"
#include <clocale>
#include <cstdio>

using namespace std;

//----------------------------------------------------------------------------------
// ������� ������ ������� ��� ����� ����������
// ���������: A-Z, a-z - 1-26 ; �������: �-�, �-� - 101-133
size_t  rankSymbol(
	unsigned char symbol							// ����������� ������
) {
	if ((64 < symbol) && (symbol < 91))	{			// ��������� ��������� ������� A-Z
		return (symbol - (unsigned char)64);
	}
	else if ((96 < symbol) && (symbol < 123)) {		// �������� ��������� ������� a-z
		return (symbol - (unsigned char)96);
	}
	else if ((191 < symbol) && (symbol < 198)) {	// ��������� ������� ������� �-�
		return (symbol - (unsigned char)91);
	}
	else if (symbol == 168) {						// ��������� ������� ������ �
		return (symbol - (unsigned char)61);
	}
	else if ((197 < symbol) && (symbol < 224)) {	// ��������� ������� ������� �-�
		return (symbol - (unsigned char)90);
	}
	else if ((223 < symbol) && (symbol < 230)) {	// �������� ������� ������� �-�
		return (symbol - (unsigned char)123);
	}
	else if (symbol == 184)	{						// �������� ������� ������ �
		return (symbol - (unsigned char)77);
	}
	else if ((229 < symbol) && (symbol < 256)) {	// �������� ������� ������� �-�
		return (symbol - (unsigned char)122);
	}
	else {
		return 0;									// ������ ��������
	}
}

//----------------------------------------------------------------------------------
// ������� ��������� � ������������ ��������� �� �������
void minArray(
	char*& one,						// ������� 1 (������ ���� ������)
	char*& two,						// ������� 2 (������ ���� ������)
	size_t index					// ������ char-������� ��������
) {
	char* buf = nullptr;			// ��������������� ��������� �� �������
	if (rankSymbol(one[index]) > rankSymbol(two[index])) {	// ���� 1 > 2
		buf = one;			    			// ����������� �������� �������
		one = two;
		two = buf;
	}
	// �����, ���� �������� �����, � �� ����� '\0'
	else if (
		(rankSymbol(one[index]) == rankSymbol(two[index])) &&
		(rankSymbol(one[index]) != '\0') &&
		(rankSymbol(two[index]) != '\0')) {
		// - ������� ��������� ������� ���������� ��� ���������
		//   ��������� �� ������� �������� ���������
		minArray(one, two, ++index);
	}
	// ���� 1 < 2 ��� ���� ���� ����� '\0' - ������ �� ������ � ����� �� �������
}

//----------------------------------------------------------------------------------
// ������� ���������� �������� � ���������
void sortWords(
	char** words,			// ������ ����
	const size_t lines		// ���������� ����� � �������, �� �����
) {
	for (size_t i = 1; i < lines; i++) {
		if (!words[i]) break;
		for (size_t j = 1; j < lines; j++) {  // j=1 !!! �� j=0 !!!
			if (!words[j]) break;
			minArray(words[j - 1], words[j], 0);
		}
	}
}

//----------------------------------------------------------------------------------

int main() {
	setlocale(LC_ALL, "ru");

	printf_s("            ������� �� ����� \"zadaci_na_fajly_1589392470.txt\"\n\n");
	printf_s("\
     ��������� ���� �������� ������������ ����� �� ���������� �����, �� \n\
 ������ ����� � ������, �� ����� 40 ���� � �����. ����� ����� ���������� \n\
 80-� ���������. ���������� ����� � ������ ����, ������������ �� � \n\
 ���������� �������.\n\n");

	const size_t lines = 40;    // ���������� ����� � �������� �����, �� �����
	const size_t columns = 80;  // ���������� �������� � ������ � �������� �����, �� �����

	// ������� ���� � ��������� �������
	const char* nameFile1 = "proverb.txt";
	FILE* firstFile = nullptr;
	FILE** ptrFirstFile = &firstFile;

	if (fopen_s(ptrFirstFile, nameFile1, "r"))	{
		printf_s(" �� ������� ������� ���� %s\n", nameFile1);
		return 0;
	}
	
	// ������� ����� �� ����� � ������
	printf_s(" �������� ����� ���� �� ����� %s\n\n", nameFile1);
	char** words = new char* [lines] {nullptr};  // ������ ����/�����
	for (size_t i = 0; i < lines; i++) {         // ������� ����� �� ����� � ������
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

	// ����������� �����/������ � ������� � ���������� �������
	sortWords(words, lines);


	// ������� ���� ��� ��������������� ����
	const char* nameFile2 = "proverb2.txt";
	FILE* secondFile = nullptr;
	FILE** ptrSecondFile = &secondFile;
	if (fopen_s(ptrSecondFile, nameFile2, "w")) {
		printf_s(" �� ������� ������� ���� %s\n", nameFile2);
		return 0;
	}

	// ������� ����� �� ������� � ����
	for (size_t i = 0; i < lines; i++) {
		if (!words[i]) break;
		fprintf_s(secondFile, "%s\x0A", words[i]);
	}
	fclose(secondFile);

	printf_s(" ��������������� ����� ���� � ����� %s\n\n", nameFile2);
	for (size_t i = 0; i < lines; i++) {
		if (!words[i]) break;
		printf_s(" %s\n", words[i]);
	}

	// ������ ������ ���� �� ������
	for (size_t i = 0; i < lines; i++) {
		if (!words[i]) break;
		else delete[] words[i];
	}
	delete[] words;

	return 0;
}