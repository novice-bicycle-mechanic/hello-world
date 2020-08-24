// DZ_ST_C++_07_dz22_vstrecha22_zadanie2_main.cpp
//
// Задание из файла DZ_ST_C++_07.pdf
// Домашнее задание №22
// Встреча №22, задание 2
// Тема: Исключения
/*
Создайте иерархию пользовательских классов-исключений.
В ней должны быть классы для разных ситуаций.
В качестве предметной области используйте ваши
практические и домашние задания. Например, должны
присутствовать классы для обработки всевозможных
математических ошибок, нехватки памяти, проблемам
по работе с файлами и т.д.
*/

#include <iostream>
#include <clocale>
#include "DZ_ST_C++_07_dz22_vstrecha22_zadanie2_Exceptions.h"


int main() {
	setlocale(LC_ALL, "ru");

	int number{ 0 };

	// Демонстрация работы исключений
	while (++number) {
		try	{
			switch (number)	{
			//-------------------------------------------------------
			case 1:	throw MathExceptions(
				MathExcept(MATH_EXCEPT::INVALID_ARGUMENT_TYPE),
				__LINE__, __FILE__
			);
			case 2:	throw MathExceptions(
				MathExcept(MATH_EXCEPT::DIVISION_BY_ZERO),
				__LINE__, __FILE__
			);
			case 3: throw MathExceptions(
				MathExcept(MATH_EXCEPT::THE_SQUARE_ROOT_OF_A_NEGATIVE_NUMBER),
				__LINE__, __FILE__
			);
			//-------------------------------------------------------
			case 4: throw IndexExceptions(
				IndexExcept(INDEX_EXCEPT::THE_INDEX_VALUE_IS_LESS_THAN_ZERO),
				__LINE__, __FILE__
			);
			case 5: throw IndexExceptions(
				IndexExcept(INDEX_EXCEPT::THE_INDEX_VALUE_IS_LESS_THAN_THE_SPECIFIED_VALUE),
				__LINE__, __FILE__
			);
			case 6: throw IndexExceptions(
				IndexExcept(INDEX_EXCEPT::THE_INDEX_VALUE_IS_GREATER_THAN_THE_MAXIMUM),
				__LINE__, __FILE__
			);
			case 7: throw IndexExceptions(
				IndexExcept(INDEX_EXCEPT::THE_INDEX_VALUE_IS_GREATER_THAN_THE_SPECIFIED_VALUE),
				__LINE__, __FILE__
			);
			//-------------------------------------------------------
			case 8: throw MemoryExceptions(
				MemoryExcept(MEMORY_EXCEPT::NOT_ENOUGH_STACK_MEMORY),
				__LINE__, __FILE__
			);
			case 9: throw MemoryExceptions(
				MemoryExcept(MEMORY_EXCEPT::NOT_ENOUGH_DYNAMIC_MEMORY),
				__LINE__, __FILE__
			);
			case 10: throw MemoryExceptions(
				MemoryExcept(MEMORY_EXCEPT::DYNAMIC_MEMORY_IS_NOT_ALLOCATED),
				__LINE__, __FILE__
			);
			case 11: throw MemoryExceptions(
				MemoryExcept(MEMORY_EXCEPT::THE_ALLOCATED_DYNAMIC_MEMORY_WAS_NOT_DELETED),
				__LINE__, __FILE__
			);
			//-------------------------------------------------------
			case 12: throw FileExceptions(
				FileExcept(FILE_EXCEPT::THE_FILE_IS_NOT_CREATED),
				__LINE__, __FILE__
			);
			case 13: throw FileExceptions(
				FileExcept(FILE_EXCEPT::THE_FILE_IS_NOT_OPEN),
				__LINE__, __FILE__
			);
			case 14: throw FileExceptions(
				FileExcept(FILE_EXCEPT::THE_FILE_IS_NOT_CLOSED),
				__LINE__, __FILE__
			);
			case 15: throw FileExceptions(
				FileExcept(FILE_EXCEPT::THE_FILE_IS_NOT_AVAILABLE),
				__LINE__, __FILE__
			);
			case 16: throw FileExceptions(
				FileExcept(FILE_EXCEPT::THE_FILE_IS_NOT_READABLE),
				__LINE__, __FILE__
			);
			case 17: throw FileExceptions(
				FileExcept(FILE_EXCEPT::THE_FILE_IS_NOT_WRITABLE),
				__LINE__, __FILE__
			);
			//-------------------------------------------------------
			case 18: throw MainParentException<int>(1, __LINE__, __FILE__);
			}
			break;
		}
		catch (const MathExceptions& exception) {
			std::cout << exception << std::endl;
		}
		catch (const IndexExceptions& exception) {
			std::cout << exception << std::endl;
		}
		catch (const MemoryExceptions& exception) {
			std::cout << exception << std::endl;
		}
		catch (const FileExceptions& exception) {
			std::cout << exception << std::endl;
		}
		catch (...) {
			std::cout << " Исключение неизвестного типа" << std::endl;
		}
	}

	return 0;
}
