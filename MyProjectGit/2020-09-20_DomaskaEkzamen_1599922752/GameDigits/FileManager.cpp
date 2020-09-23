// FileManager.cpp
#include <iostream>
#include <clocale>
#include <cstdio>
#include <cstdlib>
#include <io.h>
#include <ctime>
#include <conio.h>
#include <direct.h>
#include <cstring>
#include <string>


// КЛАСС Файловый менеджер
class FileManager {
private:
	// структура реквизитов файла/папки
	struct _finddata_t c_file {};
	// структура реквизитов копии файла/папки
	struct _finddata_t c_file_copy {};
	// указатель на позицию в списке поиска
	// файлов/папок в текущей папке
	intptr_t hFile{};
	// маска для поиска файла/папки
	const char* mask = "*.*";
	// счетчик позиций в списке файлов/папок
	size_t countPositions{ 0 };
	// всего позиций в списке файлов/папок
	size_t totalPositions{ 0 };
	// Буфер для временного хранения
	// имени папки исходного (вырезаемого) объекта
	char bufForTempStorageFolderNameOldObj[_MAX_PATH]{ '\0' };

	// Ключ вырезать(true) / копировать(false) объект
	bool cut_notCopy_object{ false };
public:
	// КОНСТРУКТОР по умолчанию
	FileManager(){}

	// МЕТОД начала и поддержания
	// работы файлового менеджера
	void go() {
		system("title Файловый менеджер");
		while (workingInCurrentFolder());
	}

	// МЕТОД Работа в текущей папке
	bool workingInCurrentFolder() {
		system("cls");
		printNameCurrentFolder();

		countPositions = 0;
		totalPositions = dirViaFind();

		std::cout << std::endl;
		printHelp();
		printNameCurrentFolder();
		printListTitle();

		char byte1char = 0;	// первый байт кода символа / нажатия клавиши
		char byte2char = 0;	// второй байт кода символа / нажатия клавиши

		enum keysC {		// коды нажатий клавиш (byte1char)
			NL = 10, Enter = 13, ESC = 27, SPACE = 32
		};
		enum keys0 {		// коды нажатий клавиш (byte2char, byte1char == 0)
			F1 = 59, F2, F3, F4, F5, F6, F7, F8, F9, F10,

			CTRL_F1 = 94, CTRL_F2, CTRL_F3, CTRL_F4, CTRL_F5, CTRL_F6
		};
		enum keysN32 {		// коды нажатий клавиш (byte2char и byte1char == N32 == -32)
			N32 = -32, UP = 72, LEFT = 75, RIGHT = 77, DOWN = 80,

			F11 = -123, F12 = -122,

			CTRL_LEFT = 115, CTRL_RIGHT = 116, CTRL_UP = -115, CTRL_DOWN = -111,

			CTRL_F11 = -119, CTRL_F12 = -118
		};

		do
		{
			// обработка нажатий клавиш
			byte1char = _getch();
			if (_kbhit()) byte2char = _getch();

			// нажато Esc - выход из программы
			if (byte1char == keysC::ESC) return false;

			// нажато F1 - показ / скрытие справки
			else if ((byte1char == 0)
				&& (byte2char == keys0::F1)
				) {
				printHelp();
			}

			// нажато F2 - вывод названия папки
			else if ((byte1char == 0)
				&& (byte2char == keys0::F2)
				) {
				printNameCurrentFolder();
			}

			// нажато F3 - открыть папку
			else if ((byte1char == 0)
				&& (byte2char == keys0::F3)
				) {
				if (openFolder()) return true;
			}

			// нажато F4 - закрыть папку
			//             (выход из папки)
			else if ((byte1char == 0)
				&& (byte2char == keys0::F4)
				) {
				toParentFolder();
				return true;
			}

			// нажато F5 - создать папку в текущей папке
			else if ((byte1char == 0)
				&& (byte2char == keys0::F5)
				) {
				createFolder();
				totalPositions = dirViaFind();
				std::cout << std::endl;
				printListTitle();
			}

			// нажато Ctrl+F5 - создать текстовый файл
			// в текущей папке
			else if ((byte1char == 0)
				&& (byte2char == keys0::CTRL_F5)
				) {
				createFile();
				totalPositions = dirViaFind();
				std::cout << std::endl;
				printListTitle();
			}

			// нажато F6 - удалить папку/файл в текущей папке
			else if ((byte1char == 0)
				&& (byte2char == keys0::F6)
				) {
				removeObject();
				countPositions = 0;
				totalPositions = dirViaFind();
				std::cout << std::endl;
				printListTitle();
			}

			// нажато F7 - переименовать папку/файл
			else if ((byte1char == 0)
				&& (byte2char == keys0::F7)
				) {
				renameObject();
				countPositions = 0;
				totalPositions = dirViaFind();
				std::cout << std::endl;
				printListTitle();
			}

			// нажато F8 - копировать папку/файл
			else if ((byte1char == 0)
				&& (byte2char == keys0::F8)
				) {
				copyObject();
			}

			// нажато F9 - вырезать папку/файл
			else if ((byte1char == 0)
				&& (byte2char == keys0::F9)
				) {
				cutObject();
				countPositions = 0;
				totalPositions = dirViaFind();
				std::cout << std::endl;
				printListTitle();
			}

			// нажато F10 - вставить папку/файл
			else if ((byte1char == 0)
				&& (byte2char == keys0::F10)
				) {
				insertObject();
				countPositions = 0;
				totalPositions = dirViaFind();
				std::cout << std::endl;
				printListTitle();
			}

			// нажато F11 - вывод списка папок/файлов
			else if ((byte1char == keysN32::N32)
				&& (byte2char == keysN32::F11)
				) {
				dirViaFind();
			}

			// нажато F12 - вывод заголовка списка
			else if ((byte1char == keysN32::N32)
			&& (byte2char == keysN32::F12)
			) {
				printListTitle();
			}

			// нажато стрелка "вниз"
			// - сдвиг курсора ВНИЗ
			else if ((byte1char == keysN32::N32)
				&& (byte2char == keysN32::DOWN)
				) {
				if (countPositions < totalPositions) {
					++countPositions;
					dirViaFind(false, countPositions);
				}
			}

			// нажато стрелка "вверх"
			// - сдвиг курсора ВВЕРХ
			if ((byte1char == keysN32::N32)
				&& (byte2char == keysN32::UP)
				) {
				if (countPositions > 1) {
					if (countPositions <= totalPositions) {
						--countPositions;
					}
					else countPositions;
					dirViaFind(false, countPositions);
				}
			}

			// нажато Ctrl+F11 - поиск файла/папки
			else if ((byte1char == keysN32::N32)
				&& (byte2char == keysN32::CTRL_F11)
				) {
				searchObject();
			}

			// нажато Ctrl+F12 - сменить диск
			else if ((byte1char == keysN32::N32)
				&& (byte2char == keysN32::CTRL_F12)
				) {
				selectDrive();
			}

		} while (true);
	}

	// МЕТОД печати справки по работе с программой
	void printHelp() const {
		std::cout
			<< " [Esc]-выход из программы       "
			<< " [F1]-справка по управляющим клавишам"
			<< "\n"
			<< " [F2]-имя текущей папки    "
			<< " [F3]-открыть папку   "
			<< " [F4]-выход из папки"
			<< "\n"
			<< " [F5]-создать папку "
			<< " [Ctrl]+[F5]-создать файл    "
			<< " [F6]-удалить"
			<< "\n"
			<< " [F7]-переименовать "
			<< " [F8]-копировать "
			<< " [F9]-вырезать   "
			<< " [F10]-вставить"
			<< "\n"
			<< " [F11]-вывод списка папок/файлов     "
			<< " [F12]-вывод заголовка списка"
			<< "\n"
			<< " [Стрелка ВНИЗ]-вниз по списку       "
			<< " [Стрелка ВВЕРХ]-вверх по списку"
			<< "\n"
			<< " [Ctrl]+[F11]-искать файл/папку      "
			<< " [Ctrl]+[F12]-сменить диск"
			<< "\n"
			<< std::endl;
	}

	// МЕТОД печати имени текущей папки
	void printNameCurrentFolder() const {
		// буфер под имя текущей папки
		char nameCurrentFolder[_MAX_PATH];

		// Имя текущей папки
		std::cout
			<< " Папка: "
			<< _getcwd(
				nameCurrentFolder,
				_countof(nameCurrentFolder))
			<< std::endl;
	}

	// МЕТОД Открыть папку
	bool openFolder() const {
		if (c_file.attrib & _A_SUBDIR) {
			std::cout << " Исходная";
			printNameCurrentFolder();
			if (!_chdir(c_file.name)) return true;
			std::cout << "Результат";
			printNameCurrentFolder();
		}
		else {
			std::cout
				<< " Выберите стрелками папку для открытия"
				<< std::endl;
		}
		return false;
	}

	// МЕТОД печати заголовка списка
	void printListTitle() const {
		printf(" N  RDO HID SYS ARC  DATE %19c TYPE      SIZE NAME\n", ' ');
		printf("--- --- --- --- ---  ---- %19c ----      ---- ----\n", ' ');
	}

	// МЕТОД печати строки в списке файлов/папок
	void printLinePosition(size_t count) const {
		char buffer[32]; // буфер под дату
		printf("%3d ", count);
		printf((c_file.attrib & _A_RDONLY) ? " Y  " : " N  ");
		printf((c_file.attrib & _A_HIDDEN) ? " Y  " : " N  ");
		printf((c_file.attrib & _A_SYSTEM) ? " Y  " : " N  ");
		printf((c_file.attrib & _A_ARCH) ? " Y  " : " N  ");
		ctime_s(buffer, _countof(buffer), &c_file.time_write);
		printf(
			" %.24s %4s %9ld %-12s",
			buffer,
			((c_file.attrib & _A_SUBDIR) ? "DIR " : "FILE"),
			c_file.size,
			c_file.name
		);
		printf("\n");
	}

	// МЕТОД реализации команды dir через find
	size_t dirViaFind(
		bool show = true,
		size_t count = 0,
		const char* mask = "*.*"
	) {
		size_t maxCount{ 0 };
		if (count) {
			maxCount = count;
			count = 0;
		}

		// Найти первый файл *.* в текущей папке
		if ((hFile = _findfirst(mask, &c_file)) == -1L) {
			printf("Нет файлов %s в текущей папке!\n", mask);
			return 0;
		}
		else {
			if (show) printListTitle();

			do {
				++count;
				if (show) printLinePosition(count);
				else {
					if (count == maxCount)
						printLinePosition(count);
				}
				if (count == maxCount) break;
			} while (_findnext(hFile, &c_file) == 0);
			_findclose(hFile);
			return count;
		}
	}

	// МЕТОД (перехода) В родительскую папку
	// (Закрыть текущую папку)
	int toParentFolder() const {
		return _chdir("..");
	}

	// Перечисление типов объектов файловой системы
	// FILE = 0 - файл, DIR = 1 - папка
	enum TYPE{File, DIR};

	// МЕТОД Имя создаваемого объекта
	const char* nameOfObjectToCreate(
		bool type,
		char* pathAndNameNewObject
	) {
		// Имя текущей папки
		char nameCurrentFolder[_MAX_PATH]{ '\0' };
		(void)_getcwd(
			nameCurrentFolder,
			_countof(nameCurrentFolder)
		);

		// ввод имени создаваемого объекта
		char nameNewObject[_MAX_PATH]{ '\0' };

		if (type) {
			std::cout
				<< " Папка будет создана в текущей папке!\n"
				<< " Введите имя создаваемой папки > ";
		}
		else {
			std::cout
				<< " Файл будет создан в текущей папке!\n"
				<< " Введите имя создаваемого файла > ";
		}
		std::cin >> nameNewObject;

		// добавление имени создаваемого объекта
		// к имени текущей папки

		strcpy_s(
			pathAndNameNewObject,
			_MAX_PATH,
			nameCurrentFolder
		);

		strcat_s(
			pathAndNameNewObject,
			_MAX_PATH,
			"\\"
		);

		strcat_s(
			pathAndNameNewObject,
			_MAX_PATH,
			nameNewObject
		);

		return pathAndNameNewObject;
	}

	// МЕТОД Создать папку
	void createFolder() {

		// Буфер под имя создаваемой папки
		char pathAndNameNewObject[_MAX_PATH]{ '\0' };

		// создание новой папки
		if (_mkdir(
			nameOfObjectToCreate(
				TYPE::DIR,
				pathAndNameNewObject)
		)) {
			std::cout << "Папка не создана" << std::endl;
		}
	}

	// МЕТОД Создать файл
	void createFile() {

		// Буфер под имя создаваемого файла
		char pathAndNameNewObject[_MAX_PATH]{ '\0' };

		FILE* stream{ nullptr };

		// создание нового файла
		if (fopen_s(
			&stream,
			nameOfObjectToCreate(
				TYPE::File,
				pathAndNameNewObject),
				"at"
		)) {
			std::cout << "Файл не создан" << std::endl;
		}
		else {
			if (stream) (void)fclose(stream);
		}
	}

	// МЕТОД Удалить (папку, файл)
	bool removeObject() {
		if (c_file.attrib & _A_SUBDIR) {
			// удаление папки
			if (_rmdir(c_file.name)) {
				std::cout
					<< " Удаление папки не выполнено"
					<< std::endl;
				return false;
			}
			else return true;
		}
		// удаление файла
		else {
			if (remove(c_file.name)) {
				std::cout
					<< " Удаление файла не выполнено"
					<< std::endl;
				return false;
			}
			else return true;
		}
	}

	// МЕТОД Переименовать папку/файл
	void renameObject() {

		std::string newNameObject;
		std::cout
			<< " Укажите только имя, без пути, чтобы \n"
			<< " переименовать "
			<< ((c_file.attrib & _A_SUBDIR)
				? "папку " : "файл ")
			<< c_file.name
			<< "\n"
			<< " в :> ";

		std::cin >> newNameObject;

		// Переименование
		if (rename(
			c_file.name,
			newNameObject.c_str()
		)) {
			std::cout
				<< " Переименование не выполнено"
				<< std::endl;
		}
	}

	// МЕТОД копирования реквизитов объекта
	void copyingObjectDetails() {
		// сохраним реквизиты копируемого объекта
		c_file_copy = c_file;
		// сохраним имя папки копируемого объекта
		(void)_getcwd(
			bufForTempStorageFolderNameOldObj,
			_countof(bufForTempStorageFolderNameOldObj)
		);

		std::cout
			<< ((c_file_copy.attrib & _A_SUBDIR)
				? " Папка " : " Файл ")
			<< c_file_copy.name
			<< " скопирован"
			<< ((c_file_copy.attrib & _A_SUBDIR)
				? "а" : "")
			<< std::endl;
	}

	// МЕТОД копирования объекта
	// для создания его копии
	void copyObject() {
		cut_notCopy_object = false;
		copyingObjectDetails();
	}

	// МЕТОД копирования объекта 
	// для его вырезания (перемещения)
	void cutObject() {
		cut_notCopy_object = true;
		copyingObjectDetails();
	}

	// МЕТОД вставки объекта
	void insertObject() {

		// Создаем скопированный объект
		if (c_file_copy.attrib & _A_SUBDIR) {
			// Создаем папку
			if (_mkdir(
				c_file_copy.name
			)) {
				std::cout << "Папка не создана" << std::endl;
			}
		}
		else {
			// Создаем файл
			FILE* stream{ nullptr };
			if (fopen_s(
				&stream,
				c_file_copy.name,
				"at"
			)) {
				std::cout << "Файл не создан" << std::endl;
			}
			else {
				if (stream) (void)fclose(stream);
			}
		}

		// Удаляем вырезанный объект
		if (cut_notCopy_object) {

			// Буфер для временного хранения
			// имени папки вставленного объекта
			char bufForTempStorageFolderNameInsObj[_MAX_PATH]{ '\0' };

			// сохраним имя папки вставленного объекта
			(void)_getcwd(
				bufForTempStorageFolderNameInsObj,
				_countof(bufForTempStorageFolderNameInsObj)
			);

			// переходим в исходную папку
			(void)_chdir(bufForTempStorageFolderNameOldObj);

			// Удаляем исходный объект
			c_file = c_file_copy;
			printNameCurrentFolder();
			removeObject();
			dirViaFind();

			// переходим в папку вставленного объекта
			(void)_chdir(bufForTempStorageFolderNameInsObj);
			printNameCurrentFolder();

			// Выключаем ключ на вырезание объекта
			cut_notCopy_object = false;
		}
	}

	// МЕТОД поиска объекта (папки/файла)
	void searchObject() {

		// Имя папки поиска
		char nameOfSearchFolder[_MAX_PATH]{ '\0' };

		// сохраним имя текущей папки как папки поиска
		(void)_getcwd(
			nameOfSearchFolder,
			_countof(nameOfSearchFolder)
		);

		// имя файла поиска
		std::string searchFileName;
		std::cout << " Введите имя или маску файла/папки поиска > ";
		std::cin >> searchFileName;
		std::cout
			<< " Начат поиск файла/папки "
			<< searchFileName
			<< std::endl;

		// начнем поиск
		searchAtSpecifiedAndChildFolders(
			nameOfSearchFolder,
			searchFileName
		);

		// закончен поиск файла
		std::cout
			<< " Закончен поиск файла/папки "
			<< searchFileName
			<< std::endl;
	}

	// МЕТОД поиск в указанной и дочерних папках
	void searchAtSpecifiedAndChildFolders(
		std::string x_nameOfSearchFolder,
		std::string x_mask
	) {
		// переходим в папку поиска
		(void)_chdir(x_nameOfSearchFolder.c_str());

		// Получение текущей рабочей папки
		char nameOfSearchFolder[_MAX_PATH]{ '\0' };
		(void)_getcwd(
			nameOfSearchFolder,
			_countof(nameOfSearchFolder)
		);

		struct _finddata_t x_c_file;
		intptr_t x_hFile;

		// поиск первого файла в текущей папке
		if ((x_hFile = _findfirst(x_mask.c_str(), &x_c_file)) == -1L) { 

			// поиск папок для поиска
			if ((x_hFile = _findfirst("*.*", &x_c_file)) == -1L) {
			}
			else {
				do {
					// если текущая позиция поиска - папка,
					// и это не ".", и не "..",
					// то запускаем поиск в этой папке,
					// а затем продолжим поиск в исходной папке
					if (
						 (x_c_file.attrib & _A_SUBDIR) &&
						!(x_c_file.attrib & _A_HIDDEN) &&
						!(x_c_file.attrib & _A_SYSTEM)						
						) {
						std::string newNameOfSearchFolder = x_c_file.name;
						if (
							(newNameOfSearchFolder != ".") &&
							(newNameOfSearchFolder != "..")
							) {
							searchAtSpecifiedAndChildFolders(
								newNameOfSearchFolder, x_mask
							);
						}
					}
				} while (_findnext(x_hFile, &x_c_file) == 0);
				_findclose(x_hFile);
			}
		}
		// дальнейший поиск
		else {
			std::cout
				<< " "
				<< nameOfSearchFolder
				<< std::endl;

			printf("RDO HID SYS ARC  DATE %19c TYPE      SIZE NAME\n", ' ');
			printf("--- --- --- ---  ---- %19c ----      ---- ----\n", ' ');
			do {
				char buffer[30];
				printf((x_c_file.attrib & _A_RDONLY) ? " Y  " : " N  ");
				printf((x_c_file.attrib & _A_HIDDEN) ? " Y  " : " N  ");
				printf((x_c_file.attrib & _A_SYSTEM) ? " Y  " : " N  ");
				printf((x_c_file.attrib & _A_ARCH) ? " Y  " : " N  ");
				ctime_s(buffer, _countof(buffer), &x_c_file.time_write);
				printf(
					" %.24s %4s %9ld %-12s",
					buffer,
					((x_c_file.attrib & _A_SUBDIR) ? "DIR " : "FILE"),
					x_c_file.size,
					x_c_file.name
				);
				printf("\n");

				// если текущая позиция поиска - папка,
				// и это не ".", и не "..",
				// то запускаем поиск в этой папке,
				// а затем продолжим поиск в исходной папке
				if (
					(x_c_file.attrib & _A_SUBDIR) &&
					!(x_c_file.attrib & _A_HIDDEN) &&
					!(x_c_file.attrib & _A_SYSTEM)
					) {
					std::string newNameOfSearchFolder = x_c_file.name;
					if (
						(newNameOfSearchFolder != ".") &&
						(newNameOfSearchFolder != "..")
						) {
						searchAtSpecifiedAndChildFolders(
							newNameOfSearchFolder, x_mask
						);
					}
				}
			} while (_findnext(x_hFile, &x_c_file) == 0);
			_findclose(x_hFile);

			// поиск папок для поиска
			if ((x_hFile = _findfirst("*.*", &x_c_file)) == -1L) {
			}
			else {
				do {
					// если текущая позиция поиска - папка,
					// и это не ".", и не "..",
					// то запускаем поиск в этой папке,
					// а затем продолжим поиск в исходной папке
					if (
						(x_c_file.attrib & _A_SUBDIR) &&
						!(x_c_file.attrib & _A_HIDDEN) &&
						!(x_c_file.attrib & _A_SYSTEM)
						) {
						std::string newNameOfSearchFolder = x_c_file.name;
						if (
							(newNameOfSearchFolder != ".") &&
							(newNameOfSearchFolder != "..")
							) {
							searchAtSpecifiedAndChildFolders(
								newNameOfSearchFolder, x_mask
							);
						}
					}
				} while (_findnext(x_hFile, &x_c_file) == 0);
				_findclose(x_hFile);
			}
		}

		// выход из текущей папки
		(void)_chdir("..");
	}

	// МЕТОД выбора диска
	void selectDrive() {

		// Структура Диск
		struct Drive {
			bool key{ false };  // ключ наличия
			std::string name;   // имя диска
		};

		// создадим набор дисков
		const int length{ 27 };
		Drive setOfDrives[length];
		std::string driveName{ "@:" };

		// заполним набор дисков
		for (int i = 0; i < length; i++) {
			setOfDrives[i].name = driveName;
			++driveName[0];
		}

		/*
		// печать содержания setOfDrives
		for (int i = 0; i < length; i++) {
			std::cout
				<< setOfDrives[i].name
				<< "  "
				<< setOfDrives[i].key
				<< std::endl;
		}
		*/

		// получим битовую маску набора дисков
		unsigned long uDriveMask = _getdrives();
		if (uDriveMask) {
			for (int i = 1; i < length; i++) {
				if (uDriveMask & 1)
					setOfDrives[i].key = true;
				uDriveMask >>= 1;
			}
		}

		// Получим текущий диск
		setOfDrives[0].name = setOfDrives[_getdrive()].name;
		std::cout
			<< " Текущий диск: "
			<< setOfDrives[0].name
			<< std::endl;

		// распечатаем доступные диски
		std::string diskName;

		std::cout << " Имеются диски: " << std::endl;
		for (int i = 1; i < length; i++) {
			if (setOfDrives[i].key) {
				// печать имени диска
				std::cout
					<< setOfDrives[i].name
					<< "   ";

				// печать доступности диска
				if (i == _getdrive()) {
					std::cout << "текущий";
				}
				else {
					char buffer[_MAX_PATH]{ '\0' };
					std::string currentFolder;

					if (_getcwd(buffer, _MAX_PATH)) {
						if (buffer)	currentFolder = buffer;
					}

					if (_chdrive(i)) {
						std::cout << "не доступен";
					}
					else {
						std::cout << "доступен";
						(void)_chdir(currentFolder.c_str());
					}
				}
				std::cout << std::endl;
			}
		}

		// Сменим диск
		std::cout << " Введите имя нового диска > ";
		std::cin >> diskName;

		for (int i = 1; i < length; i++) {
			if (setOfDrives[i].name[0] == diskName[0]) {
				if (setOfDrives[i].key) {
					if (_chdrive(i)) {
						std::cout
							<< " Диск "
							<< setOfDrives[i].name
							<< " не доступен. Смена диска не произведена"
							<< std::endl;
						break;
					}
					else {
						setOfDrives[0].name =
							setOfDrives[_getdrive()].name;

						std::cout
							<< " Новый текущий диск: "
							<< setOfDrives[0].name
							<< std::endl;
						break;
					}
				}
				else {
					std::cout
						<< " Указанный диск не существует"
						<< std::endl;
					break;
				}
			}
			else if (i == (length - 1)) {
				std::cout
					<< " Указанный диск не существует\n"
					<< std::endl;
				break;
			}
		}

		std::cout << std::endl;
		printHelp();
		printNameCurrentFolder();
		dirViaFind();
		std::cout << std::endl;
		printHelp();
		printNameCurrentFolder();
	}
};
// КЛАСС Файловый менеджер


// ГЛАВНАЯ ФУНКЦИЯ
int main() {
	setlocale(LC_ALL, "ru");

	FileManager fm;
	fm.go();
}
