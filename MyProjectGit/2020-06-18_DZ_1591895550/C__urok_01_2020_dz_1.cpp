// ���������� DZ_1591895550.txt
// �������� ������� 1 �� ����� C__urok_01_2020_1589461417.pdf
/*
    1. �������� �������, ��� ���������� � ������������ ����������.
�������� ������� ������������, ����� �� ������������� ��������
��������� ������������� ��������� (��������, k ��������� ��������
� ��������� �� 0...100). � �������� ������� ������ �������� �����
�������� �������� ����, ������� �����������.
    ������� ����� ������ ��������. ���������� ����������� ������������
������������� � ������������ ��������, ���������� �������� �� 1,
����������� �������� ��������.
*/

#include <iostream>
using namespace std;

class Counter {
private:
	int min;      // ����������� �������� ��������
	int max;      // ������������ �������� ��������
	int current;  // ������� �������� ��������
public:
	Counter(int min, int max) {
		this->min = min;
		this->max = max;
		current = min;
	}
	// ����� �� ����� ���� ��������:
	void showProperties() {
		cout << " min=" << min << " max=" << max << " current=" << current << endl;
	}
	// ����� �� ����� �������� �������� ��������
	void showCurrent() {
		cout << " current=" << current << endl;
	}
	// ������� �������� �������� ��������
	int outputCurrent() {
		return current;
	}
	// ���������� �������� ��������
	void setInitValues(int min, int max) {
		this->min = min;
		this->max = max;
		current = min;
	}
	// ���������� ����������� �� 1 �������� �������� (current),
	// ��� ���������� min, ���� current ����� ������ max
	int followingValue(){
		if (++current > max) current = min;
		return current;
	}
};

int main() {
	Counter cnt(1, 5);  // ������� ������� �� 1 �� 5

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