// DZ_ST_C++_07_dz22_vstrecha22_zadanie1_main.cpp
//
// Задание из файла DZ_ST_C++_07.pdf
// Домашнее задание №22
// Встреча №22, задание 1
// Тема: Исключения
/*
Добавьте в класс двусвязного списка механизм обработки исключений.
На ваш выбор генерируйте исключения в случае ошибок.
Например, нехватка памяти, попытка удаления из пустого списка и т.д.
*/
//
// Задания из файла Lab_C++_week_5.pdf
// Лабораторная работа №16
// Встреча №16
// Тема: Динамические структуры данных - двусвязный список
//
// Задание 1
/*
Создайте шаблонный класс двусвязного списка для работы с целыми значениями.
Требуется создать реализации для типичных операций над элементами:
AddToHead – добавление элемента в голову;
AddToTail – добавление элемента в хвост;
DeleteFromHead – удаление элемента из головы;
DeleteFromTail – удаление элемента из хвоста;
DeleteAll – удаление всех элементов;
Show – отображение всех элементов списка на экран.
*/
//
// Задание 2
/*
Добавить в класс из задания 1 следующие функции:
1) вставка элемента в заданную позицию,
2) удаление элемента по заданной позиции,
3) поиск заданного элемента
    (функция возвращает позицию найденного элемента в случае успеха
    или NULL в случае неудачи),
4) поиск и замена заданного элемента
    (функция возвращает количество замененных элементов в случае успеха
    или -1 в случае неудачи),
5) переворот списка.
*/

#include <iostream>
#include <clocale>
#include "DZ_ST_C++_07_dz22_vstrecha22_zadanie1_ListExcertions.h"
#include "DZ_ST_C++_07_dz22_vstrecha22_zadanie1_List.h"
#include "DZ_ST_C++_07_dz22_vstrecha22_zadanie1_List.cpp"


// ГЛАВНАЯ ФУНКЦИЯ
int main() {
    setlocale(LC_ALL, "ru");

    try
    {
        std::cout << " Создадим список \"a\"" << std::endl;
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

        size_t i = 2;       // номер позиции вставляемого элемента
        std::cout << " Вставим в список элемент в позицию " << i << std::endl;
        a.insertElementInPosition(i);
        a.Show();
        a.RetroShow();

        std::cout << std::endl;

        std::cout << " Перевернем список" << std::endl;
        a.flipList();
        a.Show();
        a.RetroShow();

        std::cout << std::endl;

        a.AddToHead();
        a.Show();
        a.RetroShow();

        std::cout << std::endl;

        int value = 2;
        std::cout << " Найдем элемент со значением " << value << std::endl;
        if (size_t position = a.searchForItemPositionWithSpecificValue(value)) {
            std::cout << " Элемент со значением " << value << " находится в позиции " << position << std::endl;
        }
        else {
            std::cout << " Элемент со значением " << value << " отсутствует" << std::endl;
        }

        std::cout << std::endl;

        int previousValue = 2;
        int newValue = 10;
        std::cout
            << " Найдем элемент со значением " << previousValue
            << " и заменим его на значение " << newValue
            << std::endl;
        int num = a.findAndReplaceElementWithSpecificValue(previousValue, newValue);
        if (num) {
            std::cout << " Найдено и заменено " << num << " элементов: " << std::endl;
            a.Show();
            a.RetroShow();
        }
        else {
            std::cout << " Элементы со значением " << previousValue << " отсутствуют" << std::endl;
        }

        std::cout << std::endl;

        size_t j = 4;       // номер позиции удаляемого элемента
        std::cout << " Удалим из списка элемент из позиции " << j << std::endl;
        a.deletingItemSpecifiedPosition(j);
        a.Show();
        a.RetroShow();
        std::cout << " Количество элементов в списке равно " << a.getNumber() << std::endl;

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

        std::cout << " Создадим список \"b\"" << std::endl;
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

        std::cout << " Перевернем список" << std::endl;
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