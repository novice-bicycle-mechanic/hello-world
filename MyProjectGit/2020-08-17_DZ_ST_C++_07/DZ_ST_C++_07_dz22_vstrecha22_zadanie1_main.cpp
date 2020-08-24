// DZ_ST_C++_07_dz22_vstrecha22_zadanie1_main.cpp
//
// ������� �� ����� DZ_ST_C++_07.pdf
// �������� ������� �22
// ������� �22, ������� 1
// ����: ����������
/*
�������� � ����� ����������� ������ �������� ��������� ����������.
�� ��� ����� ����������� ���������� � ������ ������.
��������, �������� ������, ������� �������� �� ������� ������ � �.�.
*/
//
// ������� �� ����� Lab_C++_week_5.pdf
// ������������ ������ �16
// ������� �16
// ����: ������������ ��������� ������ - ���������� ������
//
// ������� 1
/*
�������� ��������� ����� ����������� ������ ��� ������ � ������ ����������.
��������� ������� ���������� ��� �������� �������� ��� ����������:
AddToHead � ���������� �������� � ������;
AddToTail � ���������� �������� � �����;
DeleteFromHead � �������� �������� �� ������;
DeleteFromTail � �������� �������� �� ������;
DeleteAll � �������� ���� ���������;
Show � ����������� ���� ��������� ������ �� �����.
*/
//
// ������� 2
/*
�������� � ����� �� ������� 1 ��������� �������:
1) ������� �������� � �������� �������,
2) �������� �������� �� �������� �������,
3) ����� ��������� ��������
    (������� ���������� ������� ���������� �������� � ������ ������
    ��� NULL � ������ �������),
4) ����� � ������ ��������� ��������
    (������� ���������� ���������� ���������� ��������� � ������ ������
    ��� -1 � ������ �������),
5) ��������� ������.
*/

#include <iostream>
#include <clocale>
#include "DZ_ST_C++_07_dz22_vstrecha22_zadanie1_ListExcertions.h"
#include "DZ_ST_C++_07_dz22_vstrecha22_zadanie1_List.h"
#include "DZ_ST_C++_07_dz22_vstrecha22_zadanie1_List.cpp"


// ������� �������
int main() {
    setlocale(LC_ALL, "ru");

    try
    {
        std::cout << " �������� ������ \"a\"" << std::endl;
        List<int> a;

        a.AddToHead();
        a.Show();
        a.RetroShow();

        a.AddToHead();
        a.Show();
        a.RetroShow();

        a.AddToHead();
        a.Show();
        a.RetroShow();

        std::cout << std::endl;

        size_t i = 2;       // ����� ������� ������������ ��������
        std::cout << " ������� � ������ ������� � ������� " << i << std::endl;
        a.insertElementInPosition(i);
        a.Show();
        a.RetroShow();

        std::cout << std::endl;

        std::cout << " ���������� ������" << std::endl;
        a.flipList();
        a.Show();
        a.RetroShow();

        std::cout << std::endl;

        a.AddToHead();
        a.Show();
        a.RetroShow();

        std::cout << std::endl;

        int value = 2;
        std::cout << " ������ ������� �� ��������� " << value << std::endl;
        if (size_t position = a.searchForItemPositionWithSpecificValue(value)) {
            std::cout << " ������� �� ��������� " << value << " ��������� � ������� " << position << std::endl;
        }
        else {
            std::cout << " ������� �� ��������� " << value << " �����������" << std::endl;
        }

        std::cout << std::endl;

        int previousValue = 2;
        int newValue = 10;
        std::cout
            << " ������ ������� �� ��������� " << previousValue
            << " � ������� ��� �� �������� " << newValue
            << std::endl;
        int num = a.findAndReplaceElementWithSpecificValue(previousValue, newValue);
        if (num) {
            std::cout << " ������� � �������� " << num << " ���������: " << std::endl;
            a.Show();
            a.RetroShow();
        }
        else {
            std::cout << " �������� �� ��������� " << previousValue << " �����������" << std::endl;
        }

        std::cout << std::endl;

        size_t j = 4;       // ����� ������� ���������� ��������
        std::cout << " ������ �� ������ ������� �� ������� " << j << std::endl;
        a.deletingItemSpecifiedPosition(j);
        a.Show();
        a.RetroShow();
        std::cout << " ���������� ��������� � ������ ����� " << a.getNumber() << std::endl;

        std::cout << std::endl;

        a.DeleteFromHead();
        a.Show();
        a.RetroShow();

        a.DeleteFromHead();
        a.Show();
        a.RetroShow();

        a.DeleteFromHead();
        a.Show();
        a.RetroShow();

        a.DeleteFromHead();
        a.Show();
        a.RetroShow();

        std::cout << std::endl;

        std::cout << " �������� ������ \"b\"" << std::endl;
        List<char> b;
        b.Show();
        b.RetroShow();

        b.AddToTail();
        b.Show();
        b.RetroShow();

        b.AddToTail();
        b.Show();
        b.RetroShow();

        b.AddToTail();
        b.Show();
        b.RetroShow();

        b.DeleteFromTail();
        b.Show();
        b.RetroShow();

        b.DeleteFromTail();
        b.Show();
        b.RetroShow();

        b.DeleteFromTail();
        b.Show();
        b.RetroShow();

        std::cout << std::endl;

        std::cout << " ���������� ������" << std::endl;
        b.flipList();
        b.Show();
        b.RetroShow();

        std::cout << std::endl;

    }
    catch (const ListExceptions& exception) {
        std::cout << exception << std::endl;
    }

    return 0;
}