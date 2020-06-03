#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string.h>
#include "windows.h"
#pragma warning(disable : 4996)

using namespace std;

struct Element {
	char name[40];
	char country[40];
	int parts;
	int year;
	double rate;
};

class TextFile {
private:
	Element object;
	Element objr = { "", "", 0,0,0 };
	char fileName[20] = "file.dat";
	int count = 0;
public:
	TextFile() {
		try {
			FILE* f = fopen(fileName, "ab");

			if (f == NULL)
				throw "Файл не существует.";

			ifstream fin("file.dat", ios::binary);
			while (fin.read((char*)&objr.name, sizeof(Element))) {
				++count;
			}
			fin.close();
		}
		catch (char* str) {
			cout << str << endl;
		}
	}

	void setData() {
		try {
			int choice = 1;
			fstream file(fileName, ios::binary | ios::out);

			if (!file)
				throw "Файл не существует.";
			object = { "Белоснежка", "Германия", 2, 1982, 8.85 };
			file.write(reinterpret_cast<char*>(&object), sizeof(Element));
			object = { "Русалочка", "Дания", 1, 2000, 9.015 };
			file.write(reinterpret_cast<char*>(&object), sizeof(Element));
			object = { "Колобок", "Россия", 1, 1998, 8.168 };
			file.write(reinterpret_cast<char*>(&object), sizeof(Element));
			object = { "Суперсемейка_2", "Америка", 2, 2019, 7.9 };
			file.write(reinterpret_cast<char*>(&object), sizeof(Element));
			object = { "Суперсемейка", "Америка", 2, 2015, 8.74};
			file.write(reinterpret_cast<char*>(&object), sizeof(Element));
			object = { "Рапунцель", "Америка", 1, 2010, 8.55 };
			file.write(reinterpret_cast<char*>(&object), sizeof(Element));
			count = 6;

			cout << "\nИзначальные данные записаны. Добавить еще? 1 - да, 0 - нет: ";
			cin >> choice;
			while (choice == 1)
			{
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "Название: ";
				cin.getline(object.name, 40);
				cout << "Страна: ";
				cin.clear();
				cin.getline(object.country, 40);
				cout << "Части: ";
				cin >> object.parts;
				cout << "Год: ";
				cin >> object.year;
				cout << "Рейтинг: ";
				cin >> object.rate;
				file.write(reinterpret_cast<char*>(&object), sizeof(Element));

				cout << "\nДобавить еще? 1 - да, 0 - нет: ";
				cin >> choice;
				cout << endl;
				++this->count;
			}
			
			file.close();
		}
		catch (char* str) {
			cout << str << endl;
		}
	}

	void sortData(int props) {
		FILE* f = fopen(fileName, "r+");
		Element left, right;
		for (int i = 0; i < count; i++)
		{
			std::fseek(f, i * (sizeof(Element)), SEEK_SET);
			std::fread(&left, sizeof(Element), 1, f);
			for (int j = count - 1; j > i; j--)
			{
				std::fseek(f, j * (sizeof(Element)), SEEK_SET);
				std::fread(&right, sizeof(Element), 1, f);
				if (compare(left, right, props))
				{
					std::fseek(f, j * (sizeof(Element)), SEEK_SET);
					std::fwrite(&left, sizeof(Element), 1, f);
					std::fseek(f, i * (sizeof(Element)), SEEK_SET);
					std::fwrite(&right, sizeof(Element), 1, f);
					left = right;
				}
			}
		}
		std::fclose(f);
	}
	
	bool compare(Element L, Element R, int props)
	{
		switch (props)
		{
		case 1: 
			for (int i = 0; i < min(strlen(L.name), strlen(R.name)); i++)
			{
				if (L.name[i] != R.name[i])
					return L.name[i] > R.name[i] ? true : false;
			}
			return strlen(L.name) > strlen(R.name) ? true : false;
		
		case 2: 
			for (int i = 0; i < min(strlen(L.country), strlen(R.country)); i++)
			{
				if (L.country[i] != R.country[i])
					return L.country[i] > R.country[i] ? true : false;
			}
		case 3: return L.parts > R.parts ? true : false;
		case 4: return L.year > R.year ? true : false;
		default: return L.rate < R.rate ? true : false;
		}
	}

	void showData() {
		try {
			FILE* f;
			Element object;
			f = fopen(fileName, "rb");

			if (f == NULL)
				throw "Файл не существует.";

			for (int i = 0; i < count; i++) {
				fread(&object, sizeof(Element), 1, f);
				cout << i+1 << ". " 
					<< setw(15) << object.name 
					<< setw(15) << object.country 
					<< setw(15) << object.parts 
					<< setw(15) << object.year 
					<< setw(15) << object.rate << endl;
			}

			cout << endl;
			std::fclose(f);
		}
		catch (char* str) {
			cout << str << endl;
		}
	}
};


int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	TextFile* example = new TextFile();
	int choice;

	cout << "Меню: \n1 - Записать; 2 - Показать; 3 - Сорт по названию; \n4 - Сорт по стране; 5 - Сорт по частям; 6 - Сорт по году; 7 - Сорт по рейтингу \n8 - Выход" << endl;
	cout << "\nВыбор: ";
	cin >> choice;

	while (choice >= 1 & choice <= 7) {
		switch (choice)
		{
		case 1: {
			example->setData();
			break;
		}
		case 2: {
			cout << setw(45) << "Мультфильмы:" << endl;
			cout << endl;
			example->showData();
			break;
		}
		case 3: {
			example->sortData(1);
			cout << setw(40) << "По названию: " << endl;
			cout << endl;
			example->showData();
			break;
		}
		case 4: {
			example->sortData(2);
			cout << setw(40) << "По стране" << endl;
			cout << endl;
			example->showData();
			break;
		}
		case 5: {
			example->sortData(3);
			cout << setw(40) << "По частям" << endl;
			cout << endl;
			example->showData();
			break;
		}
		case 6: {
			example->sortData(4);
			cout << setw(40) << "По году" << endl;
			cout << endl;
			example->showData();
			break;
		}
		case 7:
			example->sortData(5);
			cout << setw(40) << "По рейтингу" << endl;
			cout << endl;
			example->showData();
			break;
		}
		cout << "Выбор: ";
		cin >> choice;
	}

	system("pause");
	return 0;
}

