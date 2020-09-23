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


// ����� �������� ��������
class FileManager {
private:
	// ��������� ���������� �����/�����
	struct _finddata_t c_file {};
	// ��������� ���������� ����� �����/�����
	struct _finddata_t c_file_copy {};
	// ��������� �� ������� � ������ ������
	// ������/����� � ������� �����
	intptr_t hFile{};
	// ����� ��� ������ �����/�����
	const char* mask = "*.*";
	// ������� ������� � ������ ������/�����
	size_t countPositions{ 0 };
	// ����� ������� � ������ ������/�����
	size_t totalPositions{ 0 };
	// ����� ��� ���������� ��������
	// ����� ����� ��������� (�����������) �������
	char bufForTempStorageFolderNameOldObj[_MAX_PATH]{ '\0' };

	// ���� ��������(true) / ����������(false) ������
	bool cut_notCopy_object{ false };
public:
	// ����������� �� ���������
	FileManager(){}

	// ����� ������ � �����������
	// ������ ��������� ���������
	void go() {
		system("title �������� ��������");
		while (workingInCurrentFolder());
	}

	// ����� ������ � ������� �����
	bool workingInCurrentFolder() {
		system("cls");
		printNameCurrentFolder();

		countPositions = 0;
		totalPositions = dirViaFind();

		std::cout << std::endl;
		printHelp();
		printNameCurrentFolder();
		printListTitle();

		char byte1char = 0;	// ������ ���� ���� ������� / ������� �������
		char byte2char = 0;	// ������ ���� ���� ������� / ������� �������

		enum keysC {		// ���� ������� ������ (byte1char)
			NL = 10, Enter = 13, ESC = 27, SPACE = 32
		};
		enum keys0 {		// ���� ������� ������ (byte2char, byte1char == 0)
			F1 = 59, F2, F3, F4, F5, F6, F7, F8, F9, F10,

			CTRL_F1 = 94, CTRL_F2, CTRL_F3, CTRL_F4, CTRL_F5, CTRL_F6
		};
		enum keysN32 {		// ���� ������� ������ (byte2char � byte1char == N32 == -32)
			N32 = -32, UP = 72, LEFT = 75, RIGHT = 77, DOWN = 80,

			F11 = -123, F12 = -122,

			CTRL_LEFT = 115, CTRL_RIGHT = 116, CTRL_UP = -115, CTRL_DOWN = -111,

			CTRL_F11 = -119, CTRL_F12 = -118
		};

		do
		{
			// ��������� ������� ������
			byte1char = _getch();
			if (_kbhit()) byte2char = _getch();

			// ������ Esc - ����� �� ���������
			if (byte1char == keysC::ESC) return false;

			// ������ F1 - ����� / ������� �������
			else if ((byte1char == 0)
				&& (byte2char == keys0::F1)
				) {
				printHelp();
			}

			// ������ F2 - ����� �������� �����
			else if ((byte1char == 0)
				&& (byte2char == keys0::F2)
				) {
				printNameCurrentFolder();
			}

			// ������ F3 - ������� �����
			else if ((byte1char == 0)
				&& (byte2char == keys0::F3)
				) {
				if (openFolder()) return true;
			}

			// ������ F4 - ������� �����
			//             (����� �� �����)
			else if ((byte1char == 0)
				&& (byte2char == keys0::F4)
				) {
				toParentFolder();
				return true;
			}

			// ������ F5 - ������� ����� � ������� �����
			else if ((byte1char == 0)
				&& (byte2char == keys0::F5)
				) {
				createFolder();
				totalPositions = dirViaFind();
				std::cout << std::endl;
				printListTitle();
			}

			// ������ Ctrl+F5 - ������� ��������� ����
			// � ������� �����
			else if ((byte1char == 0)
				&& (byte2char == keys0::CTRL_F5)
				) {
				createFile();
				totalPositions = dirViaFind();
				std::cout << std::endl;
				printListTitle();
			}

			// ������ F6 - ������� �����/���� � ������� �����
			else if ((byte1char == 0)
				&& (byte2char == keys0::F6)
				) {
				removeObject();
				countPositions = 0;
				totalPositions = dirViaFind();
				std::cout << std::endl;
				printListTitle();
			}

			// ������ F7 - ������������� �����/����
			else if ((byte1char == 0)
				&& (byte2char == keys0::F7)
				) {
				renameObject();
				countPositions = 0;
				totalPositions = dirViaFind();
				std::cout << std::endl;
				printListTitle();
			}

			// ������ F8 - ���������� �����/����
			else if ((byte1char == 0)
				&& (byte2char == keys0::F8)
				) {
				copyObject();
			}

			// ������ F9 - �������� �����/����
			else if ((byte1char == 0)
				&& (byte2char == keys0::F9)
				) {
				cutObject();
				countPositions = 0;
				totalPositions = dirViaFind();
				std::cout << std::endl;
				printListTitle();
			}

			// ������ F10 - �������� �����/����
			else if ((byte1char == 0)
				&& (byte2char == keys0::F10)
				) {
				insertObject();
				countPositions = 0;
				totalPositions = dirViaFind();
				std::cout << std::endl;
				printListTitle();
			}

			// ������ F11 - ����� ������ �����/������
			else if ((byte1char == keysN32::N32)
				&& (byte2char == keysN32::F11)
				) {
				dirViaFind();
			}

			// ������ F12 - ����� ��������� ������
			else if ((byte1char == keysN32::N32)
			&& (byte2char == keysN32::F12)
			) {
				printListTitle();
			}

			// ������ ������� "����"
			// - ����� ������� ����
			else if ((byte1char == keysN32::N32)
				&& (byte2char == keysN32::DOWN)
				) {
				if (countPositions < totalPositions) {
					++countPositions;
					dirViaFind(false, countPositions);
				}
			}

			// ������ ������� "�����"
			// - ����� ������� �����
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

			// ������ Ctrl+F11 - ����� �����/�����
			else if ((byte1char == keysN32::N32)
				&& (byte2char == keysN32::CTRL_F11)
				) {
				searchObject();
			}

			// ������ Ctrl+F12 - ������� ����
			else if ((byte1char == keysN32::N32)
				&& (byte2char == keysN32::CTRL_F12)
				) {
				selectDrive();
			}

		} while (true);
	}

	// ����� ������ ������� �� ������ � ����������
	void printHelp() const {
		std::cout
			<< " [Esc]-����� �� ���������       "
			<< " [F1]-������� �� ����������� ��������"
			<< "\n"
			<< " [F2]-��� ������� �����    "
			<< " [F3]-������� �����   "
			<< " [F4]-����� �� �����"
			<< "\n"
			<< " [F5]-������� ����� "
			<< " [Ctrl]+[F5]-������� ����    "
			<< " [F6]-�������"
			<< "\n"
			<< " [F7]-������������� "
			<< " [F8]-���������� "
			<< " [F9]-��������   "
			<< " [F10]-��������"
			<< "\n"
			<< " [F11]-����� ������ �����/������     "
			<< " [F12]-����� ��������� ������"
			<< "\n"
			<< " [������� ����]-���� �� ������       "
			<< " [������� �����]-����� �� ������"
			<< "\n"
			<< " [Ctrl]+[F11]-������ ����/�����      "
			<< " [Ctrl]+[F12]-������� ����"
			<< "\n"
			<< std::endl;
	}

	// ����� ������ ����� ������� �����
	void printNameCurrentFolder() const {
		// ����� ��� ��� ������� �����
		char nameCurrentFolder[_MAX_PATH];

		// ��� ������� �����
		std::cout
			<< " �����: "
			<< _getcwd(
				nameCurrentFolder,
				_countof(nameCurrentFolder))
			<< std::endl;
	}

	// ����� ������� �����
	bool openFolder() const {
		if (c_file.attrib & _A_SUBDIR) {
			std::cout << " ��������";
			printNameCurrentFolder();
			if (!_chdir(c_file.name)) return true;
			std::cout << "���������";
			printNameCurrentFolder();
		}
		else {
			std::cout
				<< " �������� ��������� ����� ��� ��������"
				<< std::endl;
		}
		return false;
	}

	// ����� ������ ��������� ������
	void printListTitle() const {
		printf(" N  RDO HID SYS ARC  DATE %19c TYPE      SIZE NAME\n", ' ');
		printf("--- --- --- --- ---  ---- %19c ----      ---- ----\n", ' ');
	}

	// ����� ������ ������ � ������ ������/�����
	void printLinePosition(size_t count) const {
		char buffer[32]; // ����� ��� ����
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

	// ����� ���������� ������� dir ����� find
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

		// ����� ������ ���� *.* � ������� �����
		if ((hFile = _findfirst(mask, &c_file)) == -1L) {
			printf("��� ������ %s � ������� �����!\n", mask);
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

	// ����� (��������) � ������������ �����
	// (������� ������� �����)
	int toParentFolder() const {
		return _chdir("..");
	}

	// ������������ ����� �������� �������� �������
	// FILE = 0 - ����, DIR = 1 - �����
	enum TYPE{File, DIR};

	// ����� ��� ������������ �������
	const char* nameOfObjectToCreate(
		bool type,
		char* pathAndNameNewObject
	) {
		// ��� ������� �����
		char nameCurrentFolder[_MAX_PATH]{ '\0' };
		(void)_getcwd(
			nameCurrentFolder,
			_countof(nameCurrentFolder)
		);

		// ���� ����� ������������ �������
		char nameNewObject[_MAX_PATH]{ '\0' };

		if (type) {
			std::cout
				<< " ����� ����� ������� � ������� �����!\n"
				<< " ������� ��� ����������� ����� > ";
		}
		else {
			std::cout
				<< " ���� ����� ������ � ������� �����!\n"
				<< " ������� ��� ������������ ����� > ";
		}
		std::cin >> nameNewObject;

		// ���������� ����� ������������ �������
		// � ����� ������� �����

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

	// ����� ������� �����
	void createFolder() {

		// ����� ��� ��� ����������� �����
		char pathAndNameNewObject[_MAX_PATH]{ '\0' };

		// �������� ����� �����
		if (_mkdir(
			nameOfObjectToCreate(
				TYPE::DIR,
				pathAndNameNewObject)
		)) {
			std::cout << "����� �� �������" << std::endl;
		}
	}

	// ����� ������� ����
	void createFile() {

		// ����� ��� ��� ������������ �����
		char pathAndNameNewObject[_MAX_PATH]{ '\0' };

		FILE* stream{ nullptr };

		// �������� ������ �����
		if (fopen_s(
			&stream,
			nameOfObjectToCreate(
				TYPE::File,
				pathAndNameNewObject),
				"at"
		)) {
			std::cout << "���� �� ������" << std::endl;
		}
		else {
			if (stream) (void)fclose(stream);
		}
	}

	// ����� ������� (�����, ����)
	bool removeObject() {
		if (c_file.attrib & _A_SUBDIR) {
			// �������� �����
			if (_rmdir(c_file.name)) {
				std::cout
					<< " �������� ����� �� ���������"
					<< std::endl;
				return false;
			}
			else return true;
		}
		// �������� �����
		else {
			if (remove(c_file.name)) {
				std::cout
					<< " �������� ����� �� ���������"
					<< std::endl;
				return false;
			}
			else return true;
		}
	}

	// ����� ������������� �����/����
	void renameObject() {

		std::string newNameObject;
		std::cout
			<< " ������� ������ ���, ��� ����, ����� \n"
			<< " ������������� "
			<< ((c_file.attrib & _A_SUBDIR)
				? "����� " : "���� ")
			<< c_file.name
			<< "\n"
			<< " � :> ";

		std::cin >> newNameObject;

		// ��������������
		if (rename(
			c_file.name,
			newNameObject.c_str()
		)) {
			std::cout
				<< " �������������� �� ���������"
				<< std::endl;
		}
	}

	// ����� ����������� ���������� �������
	void copyingObjectDetails() {
		// �������� ��������� ����������� �������
		c_file_copy = c_file;
		// �������� ��� ����� ����������� �������
		(void)_getcwd(
			bufForTempStorageFolderNameOldObj,
			_countof(bufForTempStorageFolderNameOldObj)
		);

		std::cout
			<< ((c_file_copy.attrib & _A_SUBDIR)
				? " ����� " : " ���� ")
			<< c_file_copy.name
			<< " ����������"
			<< ((c_file_copy.attrib & _A_SUBDIR)
				? "�" : "")
			<< std::endl;
	}

	// ����� ����������� �������
	// ��� �������� ��� �����
	void copyObject() {
		cut_notCopy_object = false;
		copyingObjectDetails();
	}

	// ����� ����������� ������� 
	// ��� ��� ��������� (�����������)
	void cutObject() {
		cut_notCopy_object = true;
		copyingObjectDetails();
	}

	// ����� ������� �������
	void insertObject() {

		// ������� ������������� ������
		if (c_file_copy.attrib & _A_SUBDIR) {
			// ������� �����
			if (_mkdir(
				c_file_copy.name
			)) {
				std::cout << "����� �� �������" << std::endl;
			}
		}
		else {
			// ������� ����
			FILE* stream{ nullptr };
			if (fopen_s(
				&stream,
				c_file_copy.name,
				"at"
			)) {
				std::cout << "���� �� ������" << std::endl;
			}
			else {
				if (stream) (void)fclose(stream);
			}
		}

		// ������� ���������� ������
		if (cut_notCopy_object) {

			// ����� ��� ���������� ��������
			// ����� ����� ������������ �������
			char bufForTempStorageFolderNameInsObj[_MAX_PATH]{ '\0' };

			// �������� ��� ����� ������������ �������
			(void)_getcwd(
				bufForTempStorageFolderNameInsObj,
				_countof(bufForTempStorageFolderNameInsObj)
			);

			// ��������� � �������� �����
			(void)_chdir(bufForTempStorageFolderNameOldObj);

			// ������� �������� ������
			c_file = c_file_copy;
			printNameCurrentFolder();
			removeObject();
			dirViaFind();

			// ��������� � ����� ������������ �������
			(void)_chdir(bufForTempStorageFolderNameInsObj);
			printNameCurrentFolder();

			// ��������� ���� �� ��������� �������
			cut_notCopy_object = false;
		}
	}

	// ����� ������ ������� (�����/�����)
	void searchObject() {

		// ��� ����� ������
		char nameOfSearchFolder[_MAX_PATH]{ '\0' };

		// �������� ��� ������� ����� ��� ����� ������
		(void)_getcwd(
			nameOfSearchFolder,
			_countof(nameOfSearchFolder)
		);

		// ��� ����� ������
		std::string searchFileName;
		std::cout << " ������� ��� ��� ����� �����/����� ������ > ";
		std::cin >> searchFileName;
		std::cout
			<< " ����� ����� �����/����� "
			<< searchFileName
			<< std::endl;

		// ������ �����
		searchAtSpecifiedAndChildFolders(
			nameOfSearchFolder,
			searchFileName
		);

		// �������� ����� �����
		std::cout
			<< " �������� ����� �����/����� "
			<< searchFileName
			<< std::endl;
	}

	// ����� ����� � ��������� � �������� ������
	void searchAtSpecifiedAndChildFolders(
		std::string x_nameOfSearchFolder,
		std::string x_mask
	) {
		// ��������� � ����� ������
		(void)_chdir(x_nameOfSearchFolder.c_str());

		// ��������� ������� ������� �����
		char nameOfSearchFolder[_MAX_PATH]{ '\0' };
		(void)_getcwd(
			nameOfSearchFolder,
			_countof(nameOfSearchFolder)
		);

		struct _finddata_t x_c_file;
		intptr_t x_hFile;

		// ����� ������� ����� � ������� �����
		if ((x_hFile = _findfirst(x_mask.c_str(), &x_c_file)) == -1L) { 

			// ����� ����� ��� ������
			if ((x_hFile = _findfirst("*.*", &x_c_file)) == -1L) {
			}
			else {
				do {
					// ���� ������� ������� ������ - �����,
					// � ��� �� ".", � �� "..",
					// �� ��������� ����� � ���� �����,
					// � ����� ��������� ����� � �������� �����
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
		// ���������� �����
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

				// ���� ������� ������� ������ - �����,
				// � ��� �� ".", � �� "..",
				// �� ��������� ����� � ���� �����,
				// � ����� ��������� ����� � �������� �����
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

			// ����� ����� ��� ������
			if ((x_hFile = _findfirst("*.*", &x_c_file)) == -1L) {
			}
			else {
				do {
					// ���� ������� ������� ������ - �����,
					// � ��� �� ".", � �� "..",
					// �� ��������� ����� � ���� �����,
					// � ����� ��������� ����� � �������� �����
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

		// ����� �� ������� �����
		(void)_chdir("..");
	}

	// ����� ������ �����
	void selectDrive() {

		// ��������� ����
		struct Drive {
			bool key{ false };  // ���� �������
			std::string name;   // ��� �����
		};

		// �������� ����� ������
		const int length{ 27 };
		Drive setOfDrives[length];
		std::string driveName{ "@:" };

		// �������� ����� ������
		for (int i = 0; i < length; i++) {
			setOfDrives[i].name = driveName;
			++driveName[0];
		}

		/*
		// ������ ���������� setOfDrives
		for (int i = 0; i < length; i++) {
			std::cout
				<< setOfDrives[i].name
				<< "  "
				<< setOfDrives[i].key
				<< std::endl;
		}
		*/

		// ������� ������� ����� ������ ������
		unsigned long uDriveMask = _getdrives();
		if (uDriveMask) {
			for (int i = 1; i < length; i++) {
				if (uDriveMask & 1)
					setOfDrives[i].key = true;
				uDriveMask >>= 1;
			}
		}

		// ������� ������� ����
		setOfDrives[0].name = setOfDrives[_getdrive()].name;
		std::cout
			<< " ������� ����: "
			<< setOfDrives[0].name
			<< std::endl;

		// ����������� ��������� �����
		std::string diskName;

		std::cout << " ������� �����: " << std::endl;
		for (int i = 1; i < length; i++) {
			if (setOfDrives[i].key) {
				// ������ ����� �����
				std::cout
					<< setOfDrives[i].name
					<< "   ";

				// ������ ����������� �����
				if (i == _getdrive()) {
					std::cout << "�������";
				}
				else {
					char buffer[_MAX_PATH]{ '\0' };
					std::string currentFolder;

					if (_getcwd(buffer, _MAX_PATH)) {
						if (buffer)	currentFolder = buffer;
					}

					if (_chdrive(i)) {
						std::cout << "�� ��������";
					}
					else {
						std::cout << "��������";
						(void)_chdir(currentFolder.c_str());
					}
				}
				std::cout << std::endl;
			}
		}

		// ������ ����
		std::cout << " ������� ��� ������ ����� > ";
		std::cin >> diskName;

		for (int i = 1; i < length; i++) {
			if (setOfDrives[i].name[0] == diskName[0]) {
				if (setOfDrives[i].key) {
					if (_chdrive(i)) {
						std::cout
							<< " ���� "
							<< setOfDrives[i].name
							<< " �� ��������. ����� ����� �� �����������"
							<< std::endl;
						break;
					}
					else {
						setOfDrives[0].name =
							setOfDrives[_getdrive()].name;

						std::cout
							<< " ����� ������� ����: "
							<< setOfDrives[0].name
							<< std::endl;
						break;
					}
				}
				else {
					std::cout
						<< " ��������� ���� �� ����������"
						<< std::endl;
					break;
				}
			}
			else if (i == (length - 1)) {
				std::cout
					<< " ��������� ���� �� ����������\n"
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
// ����� �������� ��������


// ������� �������
int main() {
	setlocale(LC_ALL, "ru");

	FileManager fm;
	fm.go();
}
