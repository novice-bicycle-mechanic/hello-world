// ������� �� ����� problemy_1592453914.txt
// ���� Lab_C++_week_1.pdf, ������� 2, ������� 4
/*
	� ��� �������������� ������ Student �������� �����������
������������, ����������, �������� ��� ������� inline,
����������� ��������������. ����������� �������� ������ ���
��� �������� �����������, ���������� ������ ����������
����������� � �����������.
(���� Lab_C++_week_1.pdf, ������� 1, ������� 1:
���������� ����� ��������. ���������� ������� � �������-
���-������ ������: ���, ���� ��������, ���������� �������,
�����, ������, �������� �������� ���������, ����� � ������ (���
��������� ������� ���������), ����� ������. ���������� ����-
���-����� ������ ��� ����� ������, ������ ������, ����������
��������� ��� ������� � ��������� ����������-������.)
*/

#include <iostream>
#include <clocale>
#include <Windows.h>
using namespace std;

// ��������� ������
struct Str {
	char* line = nullptr;
	size_t length = 0;
};
// ����� ��������� ������


// ����� �������
class Student {
private:
	char* surname   { nullptr };
	char* name      { nullptr };
	char* patronimyc{ nullptr };
	struct {
		size_t day  {0};
		size_t month{0};
		size_t year {0};
	}birthdate;
	char* phone        { nullptr };
	char* city         { nullptr };
	char* country      { nullptr };
	char* groupNumber  { nullptr };
	char* educatName   { nullptr };
	char* educatCity   { nullptr };
	char* educatCountry{ nullptr };
public:
	// ����������� �� ���������
	Student(){}
	// ����������� �����������
	Student(Student& object) { *this = object; }
	// ����������
	~Student() {
		if (surname      ) delete[] surname      ;
		if (name         ) delete[] name         ;
		if (patronimyc   ) delete[] patronimyc   ;
		if (phone        ) delete[] phone        ;
		if (city         ) delete[] city         ;
		if (country      ) delete[] country      ;
		if (groupNumber  ) delete[] groupNumber  ;
		if (educatName   ) delete[] educatName   ;
		if (educatCity   ) delete[] educatCity   ;
		if (educatCountry) delete[] educatCountry;
	}

	// ����� ����� ������ ��������
	void inputStudent() {
		char* buffer = new char[128]{ '\0' };

		cout << "          ���������� ������ ��������" << endl;
		cout << "          --------------------------" << endl;

		cout << "  ������� ������� ��������: ";
		cin >> buffer;
		this->surname = setString(buffer);

		cout << "      ������� ��� ��������: ";
		cin >> buffer;
		this->name = setString(buffer);

		cout << " ������� �������� ��������: ";
		cin >> buffer;
		this->patronimyc = setString(buffer);

		cout << "    ������� ����� ��� ���� �������� ��������: ";
		cin >> this->birthdate.day;

		cout << " ������� ����� ������ ���� �������� ��������: ";
		cin >> this->birthdate.month;

		cout << "   ������� ����� ���� ���� �������� ��������: ";
		cin >> this->birthdate.year;

		cout << " ������� ����� �������� ��������: ";
		cin >> buffer;
		this->phone = setString(buffer);

		cout << "  ������� ����� ��������: ";
		cin >> buffer;
		this->city = setString(buffer);

		cout << " ������� ������ ��������: ";
		cin >> buffer;
		this->country = setString(buffer);

		cout << "    ������� ����� ������ � ��������� ��������: ";
		cin >> buffer;
		this->groupNumber = setString(buffer);

		cout << "      ������� ������������ ��������� ��������: ";
		cin >> buffer;
		this->educatName = setString(buffer);

		cout << "  ������� ����� ���������� ��������� ��������: ";
		cin >> buffer;
		this->educatCity = setString(buffer);

		cout << " ������� ������ ���������� ��������� ��������: ";
		cin >> buffer;
		this->educatCountry = setString(buffer);

		cout << " ---------------------------------------------------------------------------" << endl;

		if (buffer) delete[] buffer;
		buffer = nullptr;
	}

	// ����� ������ ������ �������� �� �����
	void printQuestionnaire() {
		cout << "            ������ ��������" << endl;
		cout << "            ---------------" << endl;
		cout << "  �������: " << surname << endl;
		cout << "      ���: " << name << endl;
		cout << " ��������: " << patronimyc << endl;
		cout
			<< " ���� ��������: "
			<< (birthdate.day < 10 ? "0" : "")
			<< birthdate.day
			<< "."
			<< (birthdate.month < 10 ? "0" : "")
			<< birthdate.month
			<< "."
			<< birthdate.year
			<< endl;
		cout << "    ����� ��������: " << phone << endl;
		cout << "  ����� ����������: " << city << endl;
		cout << " ������ ����������: " << country << endl;
		cout << "                 ����� ������� ������: " << groupNumber << endl;
		cout << "      ������������ �������� ���������: " << educatName << endl;
		cout << "  ����� ���������� �������� ���������: " << educatCity << endl;
		cout << " ������ ���������� �������� ���������: " << educatCountry << endl;
		cout << " ---------------------------------------------------------------------------" << endl;
	}

	// GETTER-�
	inline char*  getSurname       () { return surname        ; }
	inline char*  getName          () { return name           ; }
	inline char*  getPatronimyc    () { return patronimyc     ; }
	inline char*  getPhone         () { return phone          ; }
	inline char*  getCity          () { return city           ; }
	inline char*  getCountry       () { return country        ; }
	inline char*  getGroupNumber   () { return groupNumber    ; }
	inline char*  getEducatName    () { return educatName     ; }
	inline char*  getEducatCity    () { return educatCity     ; }
	inline char*  getEducatCountry () { return educatCountry  ; }
	inline size_t getDayBirthdate  () { return birthdate.day  ; }
	inline size_t getMonthBirthdate() { return birthdate.month; }
	inline size_t getYearBirthdate () { return birthdate.year ; }

	// SETTER-�
	inline void setPhone(char* str) { phone = str; }
	inline void setCity (char* str) { city  = str; }

	// ����� �������� ������ string ���������������� ����� � ���� char*
	template <typename T>
	char* setString(T* string) {
		size_t length = 0;
		while (string[length++]);
		char* line = new char[length] {'\0'};
		--length;
		if (length) {
			for (size_t i = 0; i < length; i++) {
				line[i] = string[i];
			}
		}
		return line;
	}
};
// ����� ������ �������


// ������� �������
int main() {
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Student student;
	student.inputStudent();
	student.printQuestionnaire();

	cout << endl;
	
	cout << " ����� ����� ����� �������� ��������: ";
	student.setPhone(student.setString("89526565465"));
	cout << student.getPhone() << endl;

	cout << " ����� ����� ����� ���������� ��������: ";
	student.setCity(student.setString("������"));
	cout << student.getCity() << endl;

	cout << endl;

	student.printQuestionnaire();

	return 0;
}
// ����� ������� �������