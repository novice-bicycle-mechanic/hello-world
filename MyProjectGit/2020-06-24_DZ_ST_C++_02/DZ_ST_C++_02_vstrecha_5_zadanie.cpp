// ������� �� ����� DZ_ST_C++_02.pdf
// ������� �5
// ����: ����������� �������-����, explicit �����������.
// �������.
/*
����������� ����� Reservoir (������).
����� ������ ����������� ����� ���� ���������.
����� ������ ���������:
����������� �� ���������,
����������� � �����������,
��� ������������� ����������� ���������� � ����������� �����������.
�������� ������ ���:
1. ����������� ���������������� ������ (������*�����*������������ �������);
2. ����������� ������� ������ �����������;
3. ����� ��� �������� ��������� �� ������� � ������ ���� (����-����; �������-����);
4. ��� ��������� ������� ������ ����������� �������� ������ ����;
5. ��� ����������� ��������;
6. ��������� ������ �� ���������� ������������ (������ set � get).
�������� ��������� ��� ������ � �������.
����������� ������������ ������ �������� ������ � ������������
����������, �������� �������� �� �������.
����������� ����������� ������ ���������� �� �������� �������
� ��������� ����, �������� ����.
����������� explicit ����������� � ����������� �������-�����
(��������, ��� ����������� ������ � ������ � �.�.).
*/
#include <iostream>
#include <clocale>
#include <iomanip>
#include <stdio.h>

using namespace std;

#define pendl cout << endl;


// ��������� ��������� �����
struct FileAttribute {
	const char* name = "";    // ������������ �����
	FILE* data = nullptr;     // ��������� �� ����
	FILE** ptrData = &data;   // ��������� �� ��������� �� ����
};
// ����� ���������


// ����� �������
class Utilities {
public:
	// ����� �������� ������������ ������ ������������� ���������
	template <typename T>
	void deletePointer(T& pointer) {
		if (pointer) {
			delete[] pointer;
			pointer = nullptr;
		}
	}
	// ����� �������� ������ string ���������������� ����� � ���� char*
	template <typename T>
	char* s(T* string) {
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
	// ����� �������� ������� ������� �� ������ ������� � �������
	size_t indexFromNumber(size_t number) {
		if (number > 0) return --number;
		else return 0;
	}
	// ����� �������� ������ ������� � ������� �� ������� � �������
	size_t numberFromIndex(size_t index) {
		return ++index;
	}
}u;
// ����� ������


// �����-��������� �������
class IReservoir {
	// ������ ����������� ������� ����������� ������
	virtual int volume() = 0;
	// ������ ����������� ������� ����������� �������
	virtual int area() = 0;
};
// ����� ������


// ����� ������
class Reservoir : public IReservoir {
public:
	//           ��� �������:  ���__ ������� ����_ ����� ������
	//                      :  NONE  POOL    POND  LAKE  SWAMP
	enum class TypeReservoir { NONE, POOL,   POND, LAKE, SWAMP };

	// ������ ������� �������� ������ ����
	//                      ������: ���___ ������_���� �����  ������ ������
	//                    _________ NONE_ DIFFERENT__ EQUAL  MORE__ LESS  
	enum class CompareAreaSameType { NONE, DIFFERENT, EQUAL, MORE, LESS };

private:
	char* name = nullptr;  // �������� �������
	int length = 0;        // ����� �������
	int width  = 0;        // ������ �������
	int depth  = 0;        // ������� �������
	TypeReservoir type = TypeReservoir::NONE;  // ��� �������

	// ���������� ������ ���� ��� ������ ��������
	std::streamsize w_name   = 16;
	std::streamsize w_length = 8;
	std::streamsize w_width  = 8;
	std::streamsize w_depth  = 8;
	std::streamsize w_type   = 8;
	std::streamsize w_volume = 9;
	std::streamsize w_area   = 9;

	// ������������ ������������ enum-��
	const char* typeNames[5] { "���","�������","����","�����","������" };
	const char* compareNames[5]{ "���","���������� �� ���� ��","�����","������","������" };

public:
	// ����������� �� ���������
	Reservoir(){}
	// ����������� � �����������
	template <typename T>
	explicit Reservoir(                   //     <-----    explicit    !!!
		T             name  ,
		int           length,
		int           width ,
		int           depth ,
		TypeReservoir type
	) {
		setName  (u.s(name));
		setLength(length   );
		setWidth (width    );
		setDepth (depth    );
		setType  (type     );
	}
	// ����������� �����������
	Reservoir(Reservoir& object) { *this = object; }
	// ����������
	~Reservoir() {
		u.deletePointer<char*>(this->name);
	}

	// ����� ������� ������ �������
	int volume() {
		return length * width * depth;
	}
	
	// ����� ������� ������� �������
	int area() {
		return length * width;
	}

	// ����� ��������� ����� ��������
	//       - ��������� ������ � ���, ��� � ��������� (�������)
	bool compareType(TypeReservoir type2) {
		if (getType() == type2) return true;
		else return false;
	}

	// ����� ��������� �������� �������� ������ ����
	//       - ��������� ������ � ���, ��� � ��������� (�������)
	CompareAreaSameType compareAreaSameType(Reservoir& reservoir2) {
		if (this->type == reservoir2.type) {
			if      (this->area() > reservoir2.area()) return CompareAreaSameType::MORE ;
			else if (this->area() < reservoir2.area()) return CompareAreaSameType::LESS ;
			else                                       return CompareAreaSameType::EQUAL;
		}
		else return CompareAreaSameType::DIFFERENT;
	}

	// ����� ����������� �������
	void copy(Reservoir& reservoir2) {
		reservoir2.setName  (this->name  );
		reservoir2.setLength(this->length);
		reservoir2.setWidth (this->width );
		reservoir2.setDepth (this->depth );
		reservoir2.setType  (this->type  );
	}

	// SETTER-�
	void setName  (char*         name  ) { this->name   = name  ; }
	void setLength(int           length) { this->length = length; }
	void setWidth (int           width ) { this->width  = width ; }
	void setDepth (int           depth ) { this->depth  = depth ; }
	void setType  (TypeReservoir type  ) { this->type   = type  ; }

	template <typename T>
	void setReservoir(
		T             name  ,
		int           length,
		int           width ,
		int           depth ,
		TypeReservoir type
	) {
		setName  (u.s(name));
		setLength(length   );
		setWidth (width    );
		setDepth (depth    );
		setType  (type     );
	}

	// GETTER-�         !!! ���������� !!!
	char*         getName  () const { return this->name  ; }
	int           getLength() const { return this->length; }
	int           getWidth () const { return this->width ; }
	int           getDepth () const { return this->depth ; }
	TypeReservoir getType  () const { return this->type  ; }

	// ����� ������ ������������ ���� �������
	const char* getTypeNames(TypeReservoir type) {
		return typeNames[(size_t)type];
	}

	// ����� ����� ������������ ��������� ��������
	//       �������� ����������� �����
	const char* getCompareAreaNames(CompareAreaSameType compareArea) {
		return compareNames[(size_t)compareArea];
	}

	// ����� ������ ��������� ������ ������ �������
	void header() {
		cout 
			<< setw(0) << " "
			<< setw(w_name-1 ) << left  << "������������"
			<< setw(w_length ) << right << "�����"
			<< setw(w_width+1) << right << "������"
			<< setw(w_depth  ) << right << "�������"
			<< "  "
			<< setw(w_type+1 ) << left  << "���"
			<< setw(w_volume ) << left  << "�����"
			<< setw(w_area   ) << left  << "�������"
			<< endl;
	}

	// ����� ������ ������� �� ����� � ������
	void print() {
		cout
			<< setw(w_name  ) << left  << name
			<< setw(w_length) << right << length
			<< setw(w_width ) << right << width
			<< setw(w_depth ) << right << depth
			<< "  "
			<< setw(w_type  ) << left  << getTypeNames(type)
			<< setw(w_volume) << right << volume()
			<< setw(w_area  ) << right << area()
			<< endl;
	}
}r;
// ����� ������


// ����� ������� �������� (�� �� ������ �������� � ��������)
class CatalogOfReservoirs {
private:
	size_t numReservoirs = 0;          // ���������� ��������
	Reservoir** reservoirs = nullptr;  // ������ ��������
public:
	// ����������� �� ���������
	CatalogOfReservoirs(){}

	// ����������
	~CatalogOfReservoirs() {
		u.deletePointer(reservoirs);
	}

	// ����� ���������� ������� � �������
	template <typename T>
	void addReservoir(
		T name,
		int length,
		int width,
		int depth,
		Reservoir::TypeReservoir type
	) {
		// ������� �����, ����������� �� 1, ������ buffer ��������-��������
		Reservoir** buffer = new Reservoir * [(numReservoirs + 1)]{ nullptr };

		// �������� reservoirs � buffer
		if (reservoirs) {
			for (size_t i = 0; i < numReservoirs; i++) {
				buffer[i] = reservoirs[i];
			}
		}
		// ��������� � ������ buffer ������-������
		buffer[numReservoirs] = new Reservoir;
		buffer[numReservoirs]->setReservoir(u.s(name), length, width, depth, type);

		// ������ buffer �� tenants
		if (reservoirs) delete[] reservoirs;
		reservoirs = buffer;
		buffer = nullptr;

		// �������� ���������� �������� � ������������ � �����������
		numReservoirs++;
	}

	// ����� �������� ������� �� ��������
	bool delReservoir(size_t numReservoir) {
		// ������������
		//   numReservoir   - ������������ �����  ������� � �������
		// � indexReservoir - ������������ ������ ������� � �������
		size_t indexReservoir = u.indexFromNumber(numReservoir);

		// �������� ��������� ������� ������� � ����������� ��������
		if ((0 <= indexReservoir) && (indexReservoir < numReservoir)) {

			// �������� ������ ������� �������� �������� �� 1, ��� ������� ������
			size_t newNumReservoirs = numReservoirs - 1;
			if (newNumReservoirs) {
				Reservoir** buffer = new Reservoir * [newNumReservoirs] { nullptr };

				// �������� �� ��������� ������� ������� �� ��������� � ����������� ��������
				// ��� ����������� �������� �� ������ ������� �� ���������� �������
				if ((0 <= indexReservoir) && (indexReservoir < numReservoir)) {

					for (size_t i = 0; i < indexReservoir; i++) {
						buffer[i] = reservoirs[i];
					}
				}

				// ����������� �������� ����� ���������� �������
				size_t newMinItem = indexReservoir + 1;
				for (size_t i = indexReservoir, j = newMinItem; i < newNumReservoirs; i++, j++) {
					buffer[i] = reservoirs[j];
				}
				delete[] reservoirs;
				reservoirs = buffer;
				buffer = nullptr;
				numReservoirs = newNumReservoirs;
				return true;
			}
			else {
				delete[] reservoirs;
				reservoirs = nullptr;
				numReservoirs = newNumReservoirs;
				return true;
			}
		}
		else return false;
	}

	// GETTER-�
	Reservoir** getReservoirs(                   ) { return reservoirs              ; }
	Reservoir*  getReservoirs(size_t numReservoir) { return reservoirs[numReservoir]; }

	// ����� ������ ��������� �������� ��������
	void header() {
		cout << "  �  ";
		r.header();
		cout << endl;
	}

	// ����� ������ ������� �� �����
	void print() {
		header();

		if (reservoirs) {
			for (size_t i = 0; i < numReservoirs; i++) {
				cout << setw(3) << right << u.numberFromIndex(i) << "  ";
				getReservoirs(i)->print();
			}
		}
	}

	// ����� ������ �������/�������� �������� � ��������� ����
	void write(const char* nameFile) {
		FileAttribute catalog;
		catalog.name = nameFile;
		fopen_s(catalog.ptrData, catalog.name, "wt");
		for (size_t i = 0; i < numReservoirs; i++) {
			fprintf_s(
				catalog.data,
				"%s,%d,%d,%d,%d%c",
				reservoirs[i]->getName(),
				reservoirs[i]->getLength(),
				reservoirs[i]->getWidth(),
				reservoirs[i]->getDepth(),
				(int)reservoirs[i]->getType(),
				'\x0a'
			);
		}
		fclose(catalog.data);
	}


	// ����� ������ �������/�������� �������� � �������� ����
	void writeBin(const char* nameFile) {
		FileAttribute catalog;
		catalog.name = nameFile;
		fopen_s(catalog.ptrData, catalog.name, "wb");
		for (size_t i = 0; i < numReservoirs; i++) {
			fprintf_s(
				catalog.data,
				"%s,%d,%d,%d,%d%c",
				reservoirs[i]->getName(),
				reservoirs[i]->getLength(),
				reservoirs[i]->getWidth(),
				reservoirs[i]->getDepth(),
				(int)reservoirs[i]->getType(),
				';'
			);
		}
		fclose(catalog.data);
	}


	// ����� �������� �������/�������� �������� �� ���������� �����
	void upload(const char* nameFile) {

		FileAttribute catalog;
		catalog.name = nameFile;

		// ������� ���� ��� �������� ������� �����
		if (fopen_s(catalog.ptrData, catalog.name, "rt")) {
			printf_s(" ���� %s �����������\n", nameFile);
		}
		else {    // ���� - ���� ���� ��������
			char* line = nullptr;
			char* contex = nullptr;
			char** ptrcontex = &contex;
			size_t lenLine = 256;

			u.deletePointer(reservoirs);
			numReservoirs = 0;

			while (true) {
				line = new char[lenLine] { '\0' };
	
				if (fgets(line, lenLine, catalog.data)) {
					contex = line;
					char* name = strtok_s(contex, ",", ptrcontex);
					size_t length = atoi(strtok_s(contex, ",", ptrcontex));
					size_t width  = atoi(strtok_s(contex, ",", ptrcontex));
					size_t depth  = atoi(strtok_s(contex, ",", ptrcontex));
					Reservoir::TypeReservoir type =
						(Reservoir::TypeReservoir)atoi(strtok_s(contex, "\n", ptrcontex));
					this->addReservoir(u.s(name), length, width, depth, type);
				}
				else {
					delete[] line;
					line = nullptr;
					contex = nullptr;
					break;
				}
			}
			fclose(catalog.data);
		}
	}


	// ����� �������� �������/�������� �������� �� ��������� �����
	void uploadBin(const char* nameFile) {

		FileAttribute catalog;
		catalog.name = nameFile;

		// ������� ���� ��� �������� ������� �����
		if (fopen_s(catalog.ptrData, catalog.name, "rb")) {
			printf_s(" ���� %s �����������\n", nameFile);
		}
		else {    // ���� - ���� ���� ��������

			size_t lenBuffer = 0;
			while (fgetc(catalog.data) != EOF) ++lenBuffer;
			char* buffer = new char[lenBuffer + 1]{ '\0' };

			fseek(catalog.data, 0, SEEK_SET);
			for (size_t i = 0; i < lenBuffer; i++) {
				buffer[i] = (char)fgetc(catalog.data);
			}

			fclose(catalog.data);

			char* contexBuffer = nullptr;
			char** ptrcontexBuffer = &contexBuffer;

			char* line = nullptr;
			char* contex = nullptr;
			char** ptrcontex = &contex;

			u.deletePointer(reservoirs);
			numReservoirs = 0;

			contexBuffer = buffer;

			while (true) {

				line = strtok_s(contexBuffer, ";", ptrcontexBuffer);
				if (!line) break;
				contex = line;

				char* name = strtok_s(contex, ",", ptrcontex);
				size_t length = atoi(strtok_s(contex, ",", ptrcontex));
				size_t width  = atoi(strtok_s(contex, ",", ptrcontex));
				size_t depth  = atoi(strtok_s(contex, ",", ptrcontex));
				Reservoir::TypeReservoir type =
					(Reservoir::TypeReservoir)atoi(strtok_s(contex, ";", ptrcontex));

				this->addReservoir(u.s(name), length, width, depth, type);
			}

			if (buffer) delete[] buffer;
			buffer = nullptr;
			contexBuffer = nullptr;

			if (line) delete[] line;
			line = nullptr;
			contex = nullptr;
		}
	}
};
// ����� ������


// ������� ��������� �������� �������� ������ ����
void compareAreasSameType(
	CatalogOfReservoirs& catalog,
	size_t numReservoir1,
	size_t numReservoir2
) {
	cout
	<< " ������� ������� ������� �" << numReservoir1 << " � �" << numReservoir2 << "\n"
	<< " ����� \""
	<< catalog.getReservoirs(u.indexFromNumber(numReservoir1))->getName()
	<< "\" "
	<< r.getCompareAreaNames(
		catalog.getReservoirs(u.indexFromNumber(numReservoir1))->compareAreaSameType(
			*catalog.getReservoirs(u.indexFromNumber(numReservoir2))
		)
	)
	<< " ������ \""
	<< catalog.getReservoirs(u.indexFromNumber(numReservoir2))->getName()
	<< "\""
	<< endl;
}
// ����� �������


// ������� ��������� ����� ��������
void compareTypes(
	CatalogOfReservoirs& catalog,
	size_t numReservoir1,
	size_t numReservoir2
) {
	cout
		<< " ��� ������ �" << numReservoir1 << " - "
		<< r.getTypeNames(catalog.getReservoirs(u.indexFromNumber(numReservoir1))->getType())
		<< "\n"
		<< " ��� ������ �" << numReservoir2 << " - "
		<< r.getTypeNames(catalog.getReservoirs(u.indexFromNumber(numReservoir2))->getType())
		<< endl;

	cout
		<< " ��������� ����� ������� �" << numReservoir1 << " � �" << numReservoir2 << ": "
		<< (catalog.getReservoirs(u.indexFromNumber(numReservoir1))->compareType(
			catalog.getReservoirs(u.indexFromNumber(numReservoir2))->getType()) ?
			"���� ����������" : "���� �� ����������")
		<< endl;
}
// ����� �������


// ������� �������
int main() {
	setlocale(LC_ALL, "ru");

	// �������� ������ ������� ��������
	CatalogOfReservoirs catalog;

	// �������� ������� ���������-���������
	catalog.addReservoir("����� �����"     ,  100,  10,  4, Reservoir::TypeReservoir::LAKE );
	catalog.addReservoir("������� �����"   , 2000, 500, 10, Reservoir::TypeReservoir::LAKE );
	catalog.addReservoir("��������� ����"  ,  200, 150,  4, Reservoir::TypeReservoir::POND );
	catalog.addReservoir("���������� ����" ,  100,  20,  5, Reservoir::TypeReservoir::POND );
	catalog.addReservoir("�������� �������",   25,  10,  2, Reservoir::TypeReservoir::POOL );
	catalog.addReservoir("������ ������"   , 1000,1000,  8, Reservoir::TypeReservoir::SWAMP);

	// ��������� ������
	cout << "                  �������� � ��������-��������� �������" << endl;
	cout << "                  --------------------------------------" << endl;

	// ������ ������� ��������
	catalog.print();
	pendl;

	// ������� ������� �������� � ��������� ����
	cout << " ������� ������� ������� � ��������� ���� \"catalogReservoirs.txt\"" << endl;
	catalog.write("catalogReservoirs.txt");
	pendl;

	// ��������� ����� �������� �3 � �4
	compareTypes(catalog, 3, 4);
	pendl;

	// ��������� ����� �������� �1 � �4
	compareTypes(catalog, 1, 4);
	pendl;

	// ��������� ������� �������� ������ ����
	compareAreasSameType(catalog, 1, 2);
	pendl;

	// ��������� ������� �������� ������ �����
	compareAreasSameType(catalog, 5, 2);
	pendl;

	// �������� ���������� ������� �1 � ����� ������ �7
	cout << " �������� ���������� ������ �1 � ����� ����� �7" << endl;
	catalog.addReservoir("������ ������", 1000, 1000, 8, Reservoir::TypeReservoir::SWAMP);
	catalog.getReservoirs(u.indexFromNumber(1))->copy(
		*catalog.getReservoirs(u.indexFromNumber(7))
	);
	pendl;

	// ������ ������� ��������
	catalog.print();
	pendl;

	// ������� ������� �������� � �������� ����
	cout << " ������� ������� ������� � �������� ���� \"catalogReservoirsBin.bin\"" << endl;
	catalog.writeBin("catalogReservoirsBin.bin");
	pendl;

	// ��������� ������� �������� �� ���������� �����
	cout << " �������� ������� ������� �� ���������� ����� \"catalogReservoirs.txt\"" << endl;
	catalog.upload("catalogReservoirs.txt");
	pendl;

	// ������ ������� ��������
	catalog.print();
	pendl;

	// ������ ������ ������� �4 �� ��������
	cout << " ������ ������ ������ �4 �� ��������" << endl;
	pendl;
	catalog.delReservoir(4);

	// ������ ������� ��������
	catalog.print();
	pendl;

	// ��������� ������� �������� �� ��������� �����
	cout << " �������� ������� ������� �� ��������� ����� \"catalogReservoirsBin.bin\"" << endl;
	catalog.uploadBin("catalogReservoirsBin.bin");
	pendl;

	// ������ ������� ��������
	catalog.print();
	pendl;

	return 0;
}
// ����� ������� �������
















