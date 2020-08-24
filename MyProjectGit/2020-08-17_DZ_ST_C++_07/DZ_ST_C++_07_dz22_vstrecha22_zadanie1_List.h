// DZ_ST_C++_07_dz22_vstrecha22_zadanie1_List.h

#pragma once
#include <iostream>

// Шаблон элемента двусвязного списка
template <typename T>
struct Elem {
    T value{ 0 };              // значение элемента
    Elem<T>* next{ nullptr };  // адрес следующего элемента
    Elem<T>* prev{ nullptr };  // адрес предыдущего элемента
};

// Перечисление разрешенных к применению целочисленных типов для класса List
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

// Шаблон класса двусвязного списка
template <typename T>
class List {
private:
    Elem<T>* head{ nullptr };  // указатель на голову списка
    Elem<T>* tail{ nullptr };  // указатель на хвост списка
    size_t number{ 0 };        // количество элементов в списке
    T count{ 0 };              // номер созданного элемента списка
public:
    // КОНСТРУКТОР по умолчанию
    List() {
//        std::cout << " Конструктор по умолчанию для списка" << std::endl;
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
            // исключение - недопустимый тип экземпляра класса
            // разрешены: short, unsigned short, int, unsigned int,
            // long, unsigned long, long long, unsigned long long
            throw ListExceptions(EXCEPTIONS::INVALID_CLASS_INSTANCE_TYPE, __LINE__, __FILE__);
        }
    }

    // ДЕСТРУКТОР
    ~List() {
//        std::cout << " Деструктор списка" << std::endl;
        DeleteAll();
    }

    // МЕТОД информирования о количестве элементов в списке
    size_t getNumber() const { return number; }

    // МЕТОД добавления элемента в голову списка
    void AddToHead(bool keyCount = true);

    // МЕТОД добавления элемента в хвост списка
    void AddToTail(bool keyCount = true);

    // МЕТОД удаления всех элементов
    void DeleteAll();

    // МЕТОД отображения всех элементов списка на экран от первого к последнему
    void Show() const;

    // МЕТОД отображения всех элементов списка на экран от последнего к первому
    void RetroShow() const;

    // МЕТОД удаления элемента из головы списка
    void DeleteFromHead();

    // МЕТОД удаления элемента из хвоста списка
    void DeleteFromTail();

    // МЕТОД вставки элемента в заданную позицию списка
    void insertElementInPosition(const size_t insertionPosition);

    // МЕТОД удаления элемента на заданной позиции списка
    void deletingItemSpecifiedPosition(const size_t positionToDelete);

    // МЕТОД поиска позиции элемента с определенным значением
    size_t searchForItemPositionWithSpecificValue(const T value) const;

    // МЕТОД поиска и замены элемента с определенным значением
    int findAndReplaceElementWithSpecificValue(const T previousValue, const T newValue);

    // МЕТОД переворота списка
    void flipList();
};



