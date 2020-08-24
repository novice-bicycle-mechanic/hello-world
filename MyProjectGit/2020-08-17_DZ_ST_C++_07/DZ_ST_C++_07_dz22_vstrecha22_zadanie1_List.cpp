// DZ_ST_C++_07_dz22_vstrecha22_zadanie1_List.inl
// подключен в конце файла "DZ_ST_C++_07_dz22_vstrecha22_zadanie1_List.h"
// записью: #include "DZ_ST_C++_07_dz22_vstrecha22_zadanie1_List.inl"
// если в конце h-файла подключать cpp-файл,
// то подключать cpp-файл к проекту нельзя !!!
// - выдаст сообщение, что функции уже определены !!!


#include "DZ_ST_C++_07_dz22_vstrecha22_zadanie1_ListExcertions.h"
#include "DZ_ST_C++_07_dz22_vstrecha22_zadanie1_List.h"


// МЕТОД добавления элемента в голову списка
template <typename T>
void List<T>::AddToHead(bool keyCount) {
    Elem<T>* newFirstElement = new Elem<T>{ (keyCount ? ++count : count), head, nullptr };
    head = newFirstElement;
    ++number;
    if (head->next) head->next->prev = head;
    if (1 == number) tail = newFirstElement;
}

// МЕТОД добавления элемента в хвост списка
template <typename T>
void List<T>::AddToTail(bool keyCount) {
    Elem<T>* newLastElement = new Elem<T>{ (keyCount ? ++count : count), nullptr, tail };
    tail = newLastElement;
    ++number;
    if (tail->prev) tail->prev->next = tail;
    if (1 == number) head = newLastElement;
}

// МЕТОД удаления всех элементов
template <typename T>
void List<T>::DeleteAll() {
    if (head) {
        Elem<T>* currElem = head;
        Elem<T>* nextElem = currElem->next;
        bool continuation{ false };   // ключ на продолжение процесса удаления элементов
        while (true) {
            continuation = (bool)currElem->next;
            delete[] currElem;
            if (continuation) {
                currElem = nextElem;
                nextElem = currElem->next;
            }
            else break;
        }
        head = nullptr;
        tail = nullptr;
        number = 0;
        count = 0;
    }
}

// МЕТОД отображения всех элементов списка на экран от первого к последнему
template <typename T>
void List<T>::Show() const {
    std::cout << " Show():     ";
    if (head) {
        Elem<T>* tempNext{ head };    // временный указатель на следующий элемент списка
        while (tempNext) {
            std::cout << " " << tempNext->value;
            if (tempNext == tail) {
                std::cout << std::endl;
                return;
            }
            tempNext = tempNext->next;
        }
        // исключение - нулевой указатель на элемент списка
        throw ListExceptions(EXCEPTIONS::NULL_POINTER_TO_A_LIST_ITEM, __LINE__, __FILE__);
    }
    else {
        // исключение - нулевой указатель на голову списка
//        throw ListExceptions(EXCEPTIONS::NULL_POINTER_TO_THE_HEAD_OF_THE_LIST, __LINE__, __FILE__);
        std::cout << std::endl;
    }
}

// МЕТОД отображения всех элементов списка на экран от последнего к первому
template <typename T>
void List<T>::RetroShow() const {
    std::cout << " RetroShow():";
    if (tail) {
        Elem<T>* tempNext{ tail };    // временный указатель на предыдущий элемент списка
        while (tempNext) {
            std::cout << " " << tempNext->value;
            if (tempNext == head) {
                std::cout << std::endl;
                return;
            }
            tempNext = tempNext->prev;
        }
        // исключение - нулевой указатель на элемент списка
        throw ListExceptions(EXCEPTIONS::NULL_POINTER_TO_A_LIST_ITEM, __LINE__, __FILE__);
    }
    else {
        // исключение - нулевой указатель на хвост списка
//        throw ListExceptions(EXCEPTIONS::NULL_POINTER_TO_THE_TAIL_OF_THE_LIST, __LINE__, __FILE__);
        std::cout << std::endl;
    }
}

// МЕТОД удаления элемента из головы списка
template <typename T>
void List<T>::DeleteFromHead() {
    if (head) {
        Elem<T>* elementToRemoveFromHead = head;
        head = head->next;
        --number;
        if (tail == elementToRemoveFromHead) tail = nullptr;
        delete[] elementToRemoveFromHead;
        elementToRemoveFromHead = nullptr;
        if (head) head->prev = nullptr;
    }
    else {
        // исключение - нулевой указатель на голову списка
        throw ListExceptions(EXCEPTIONS::NULL_POINTER_TO_THE_HEAD_OF_THE_LIST, __LINE__, __FILE__);
    }
}

// МЕТОД удаления элемента из хвоста списка
template <typename T>
void List<T>::DeleteFromTail() {
    if (tail) {
        Elem<T>* elementToRemoveFromTail{ tail };
        tail = tail->prev;
        --number;
        if (head == elementToRemoveFromTail) head = nullptr;
        delete[] elementToRemoveFromTail;
        elementToRemoveFromTail = nullptr;
        if (tail) tail->next = nullptr;
    }
    else {
        // исключение - нулевой указатель на хвост списка
        throw ListExceptions(EXCEPTIONS::NULL_POINTER_TO_THE_TAIL_OF_THE_LIST, __LINE__, __FILE__);
    }
}

// МЕТОД вставки элемента в заданную позицию списка
template <typename T>
void List<T>::insertElementInPosition(const size_t insertionPosition) {
    if (insertionPosition && (insertionPosition <= (number + 1))) {
        if (insertionPosition == 1) {
            AddToHead();
            return;
        }
        else if (head) {
            Elem<T>* prevElement{ nullptr };
            Elem<T>* currElement{ head };
            size_t currentPosition{ 1 };
            while (insertionPosition >= currentPosition) {
                if (insertionPosition == currentPosition) {
                    Elem<T>* insertionElement = new Elem<T>{
                        ++count,
                        currElement,
                        prevElement
                    };
                    prevElement->next = insertionElement;
                    if (currElement) insertionElement->next->prev = insertionElement;
                    else tail = insertionElement;
                    ++number;
                    return;
                }
                ++currentPosition;
                prevElement = currElement;
                currElement = currElement->next;
            }
            // исключение - текущая позиция в списке больше заданной
            throw ListExceptions(
                EXCEPTIONS::THE_CURRENT_POSITION_IN_THE_LIST_IS_GREATER_THAN_THE_SPECIFIED_ONE,
                __LINE__,
                __FILE__
            );
        }
        else {
            // исключение - номер позиции в списке больше максимального
            throw ListExceptions(
                EXCEPTIONS::THE_POSITION_NUMBER_IN_THE_LIST_IS_GREATER_THAN_THE_MAXIMUM, __LINE__, __FILE__
            );
        }
    }
    else {
        if (insertionPosition) {
            // исключение - номер позиции в списке больше максимального
            throw ListExceptions(
                EXCEPTIONS::THE_POSITION_NUMBER_IN_THE_LIST_IS_GREATER_THAN_THE_MAXIMUM, __LINE__, __FILE__
            );
        }
        else {
            // исключение - номер позиции в списке равен нулю
            throw ListExceptions(EXCEPTIONS::THE_POSITION_NUMBER_IN_THE_LIST_IS_ZERO, __LINE__, __FILE__);
        }
    }
}

// МЕТОД удаления элемента на заданной позиции списка
template <typename T>
void List<T>::deletingItemSpecifiedPosition(const size_t positionToDelete) {
    if (positionToDelete && (positionToDelete <= number)) {
        if (positionToDelete == 1) {
            DeleteFromHead();
            return;
        }
        else if (head->next) {
            Elem<T>* prevElement{ head->next->prev };
            Elem<T>* currElement{ head->next };
            Elem<T>* nextElement{ head->next->next };
            size_t currentPosition{ 2 };
            while (positionToDelete >= currentPosition) {
                if (positionToDelete == currentPosition) {
                    if (currElement) delete[] currElement;
                    prevElement->next = nextElement;
                    if (nextElement) nextElement->prev = prevElement;
                    else tail = prevElement;
                    --number;
                    return;
                }
                ++currentPosition;
                prevElement = currElement;
                currElement = nextElement;
                if (nextElement) nextElement = nextElement->next;
                else {
                    // исключение - текущая позиция в списке больше заданной
                    throw ListExceptions(
                        EXCEPTIONS::THE_CURRENT_POSITION_IN_THE_LIST_IS_GREATER_THAN_THE_SPECIFIED_ONE,
                        __LINE__,
                        __FILE__
                    );
                }
            }
            // исключение - текущая позиция в списке больше заданной
            throw ListExceptions(
                EXCEPTIONS::THE_CURRENT_POSITION_IN_THE_LIST_IS_GREATER_THAN_THE_SPECIFIED_ONE,
                __LINE__,
                __FILE__
            );
        }
        else {
            // исключение - номер позиции в списке больше максимального
            throw ListExceptions(
                EXCEPTIONS::THE_POSITION_NUMBER_IN_THE_LIST_IS_GREATER_THAN_THE_MAXIMUM, __LINE__, __FILE__
            );
        }
    }
    else {
        if (positionToDelete) {
            // исключение - номер позиции в списке больше максимального
            throw ListExceptions(
                EXCEPTIONS::THE_POSITION_NUMBER_IN_THE_LIST_IS_GREATER_THAN_THE_MAXIMUM, __LINE__, __FILE__
            );
        }
        else {
            // исключение - номер позиции в списке равен нулю
            throw ListExceptions(EXCEPTIONS::THE_POSITION_NUMBER_IN_THE_LIST_IS_ZERO, __LINE__, __FILE__);
        }
    }
}

// МЕТОД поиска позиции элемента с определенным значением
template <typename T>
size_t List<T>::searchForItemPositionWithSpecificValue(const T value) const {
    if (head) {
        Elem<T>* currElement{ head };
        for (size_t i = 1; i <= number; i++) {
            if (value == currElement->value) return i;
            currElement = currElement->next;
        }
        return 0;
    }
    else {
        // исключение - нулевой указатель на голову списка
        throw ListExceptions(EXCEPTIONS::NULL_POINTER_TO_THE_HEAD_OF_THE_LIST, __LINE__, __FILE__);
    }
}

// МЕТОД поиска и замены элемента с определенным значением
template <typename T>
int List<T>::findAndReplaceElementWithSpecificValue(const T previousValue, const T newValue) {
    if (head) {
        int numberElementsFound{ 0 };       // количество найденных элементов
        Elem<T>* currElement{ head };
        for (size_t i = 1; i <= number; i++) {
            if (previousValue == currElement->value) {
                currElement->value = newValue;
                ++numberElementsFound;
            }
            currElement = currElement->next;
        }
        if (numberElementsFound) return numberElementsFound;
        else return -1;
    }
    else {
        // исключение - нулевой указатель на голову списка
        throw ListExceptions(EXCEPTIONS::NULL_POINTER_TO_THE_HEAD_OF_THE_LIST, __LINE__, __FILE__);
    }
}

// МЕТОД переворота списка
template <typename T>
void List<T>::flipList() {
    if (head) {
        Elem<T>* currElement{ nullptr };
        T tempValue{ 0 };
        size_t deletingPosition{ 0 };
        for (size_t i = 2; i <= number; i++) {
            currElement = head;
            for (size_t j = 2; j <= i; j++) {
                currElement = currElement->next;
            }
            if (!currElement) break;
            tempValue = currElement->value;
            deletingPosition = i;
            deletingItemSpecifiedPosition(deletingPosition);
            AddToHead(0);
            head->value = tempValue;
        }
    }
    else {
        // исключение - нулевой указатель на голову списка
        throw ListExceptions(EXCEPTIONS::NULL_POINTER_TO_THE_HEAD_OF_THE_LIST, __LINE__, __FILE__);
    }
}

