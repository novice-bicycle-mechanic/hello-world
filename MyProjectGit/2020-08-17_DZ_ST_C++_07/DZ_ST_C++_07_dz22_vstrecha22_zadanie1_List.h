// DZ_ST_C++_07_dz22_vstrecha22_zadanie1_List.h

#pragma once
#include <iostream>

// ������ �������� ����������� ������
template <typename T>
struct Elem {
    T value{ 0 };              // �������� ��������
    Elem<T>* next{ nullptr };  // ����� ���������� ��������
    Elem<T>* prev{ nullptr };  // ����� ����������� ��������
};

// ������������ ����������� � ���������� ������������� ����� ��� ������ List
enum class TYPES {
//      type                 int           size_t
    SHORT              = -1022626503, // 3272340793,
    UNSIGNED_SHORT     = -1039404122, // 3255563174,
    INT                = -854850313,  // 3440116983,
    UNSIGNED_INT       = -871627932,  // 3423339364,
    LONG               = -821295075,  // 3473672221,
    UNSIGNED_LONG      = -838072694,  // 3456894602,
    LONG_LONG          = 1695257516,  // 1695257516,
    UNSIGNED_LONG_LONG = 1712035135,  // 1712035135,
};

// ������ ������ ����������� ������
template <typename T>
class List {
private:
    Elem<T>* head{ nullptr };  // ��������� �� ������ ������
    Elem<T>* tail{ nullptr };  // ��������� �� ����� ������
    size_t number{ 0 };        // ���������� ��������� � ������
    T count{ 0 };              // ����� ���������� �������� ������
public:
    // ����������� �� ���������
    List() {
//        std::cout << " ����������� �� ��������� ��� ������" << std::endl;
//        std::cout << (int)typeid(T).hash_code() << std::endl;
        TYPES typeList = (TYPES)typeid(T).hash_code();
        switch (typeList)
        {
        case TYPES::SHORT:
        case TYPES::UNSIGNED_SHORT:
        case TYPES::INT:
        case TYPES::UNSIGNED_INT:
        case TYPES::LONG:
        case TYPES::UNSIGNED_LONG:
        case TYPES::LONG_LONG:
        case TYPES::UNSIGNED_LONG_LONG:
            break;
        default:
            // ���������� - ������������ ��� ���������� ������
            // ���������: short, unsigned short, int, unsigned int,
            // long, unsigned long, long long, unsigned long long
            throw ListExceptions(EXCEPTIONS::INVALID_CLASS_INSTANCE_TYPE, __LINE__, __FILE__);
        }
    }

    // ����������
    ~List() {
//        std::cout << " ���������� ������" << std::endl;
        DeleteAll();
    }

    // ����� �������������� � ���������� ��������� � ������
    size_t getNumber() const { return number; }

    // ����� ���������� �������� � ������ ������
    void AddToHead(bool keyCount = true);

    // ����� ���������� �������� � ����� ������
    void AddToTail(bool keyCount = true);

    // ����� �������� ���� ���������
    void DeleteAll();

    // ����� ����������� ���� ��������� ������ �� ����� �� ������� � ����������
    void Show() const;

    // ����� ����������� ���� ��������� ������ �� ����� �� ���������� � �������
    void RetroShow() const;

    // ����� �������� �������� �� ������ ������
    void DeleteFromHead();

    // ����� �������� �������� �� ������ ������
    void DeleteFromTail();

    // ����� ������� �������� � �������� ������� ������
    void insertElementInPosition(const size_t insertionPosition);

    // ����� �������� �������� �� �������� ������� ������
    void deletingItemSpecifiedPosition(const size_t positionToDelete);

    // ����� ������ ������� �������� � ������������ ���������
    size_t searchForItemPositionWithSpecificValue(const T value) const;

    // ����� ������ � ������ �������� � ������������ ���������
    int findAndReplaceElementWithSpecificValue(const T previousValue, const T newValue);

    // ����� ���������� ������
    void flipList();
};



