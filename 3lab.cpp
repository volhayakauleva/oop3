//�����������. ������� ������ ������������ �� ���������� ������ � ������� ���������� ��������.

#include "stdafx.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iomanip>

using namespace std;

struct Element {
	string name;
	string country;
	int parts;
	int year;
	double rate;

	~Element()                       
	{
		name = "";
		country = "";
		parts = NULL;
		year = NULL;
		rate = NULL;
	}
};
const int MAX = 100;
class Cartoons
{

public:
	Element elements[MAX];
	int top;

	Cartoons() { top = -1; }
	~Cartoons() {};

	void In (string name, string country, int parts, int year, double rate)
	{
		Element newCartoon = { name, country, parts, year, rate };
		elements[++top] = newCartoon;
	}

	void TopElem() {
		if (top < 0)
			throw string("���� ����!");
		cout << "��������� �������: " << setw(14)
			<< elements[top].name << setw(14)
			<< elements[top].country << setw(14)
			<< elements[top].year << setw(14)
			<< elements[top].parts << setw(14)
			<< elements[top].rate << endl;
	}

	void Out() {
		if (top < 0)
		{
			throw string("���� ����!");
		}
		elements[top].~Element();
		top--;
	}

	void Print() {
		if (top < 0)
			throw string("���� ����!");
		for (int i = 0; i <= top; i++)
		{
			cout << i+1 << ". " << setw(14)
				<< elements[i].name << setw(14)
				<< elements[i].country << setw(14)
				<< elements[i].year << setw(14)
				<< elements[i].parts << setw(14)
				<< elements[i].rate << endl;
		}
		cout << endl;
	}

	void Quicksort(Element * mas, int first, int last, int parametr)
	{
		Element mid, temp;
		int f = first, l = last;
		mid = mas[(f + l) / 2];
		do
		{
			switch (parametr)
			{
			case 0:
				while (mas[f].name < mid.name) f++;
				while (mas[l].name > mid.name) l--;
				break;
			case 1:
				while (mas[f].country < mid.country) f++;
				while (mas[l].country > mid.country) l--;
				break;
			case 2:
				while (mas[f].year < mid.year) f++;
				while (mas[l].year > mid.year) l--;
				break;
			case 3:
				while (mas[f].parts < mid.parts) f++;
				while (mas[l].parts > mid.parts) l--;
				break;
			case 4:
				while (mas[f].rate > mid.rate) f++;
				while (mas[l].rate < mid.rate) l--;
				break;
			}		
			if (f <= l)
			{
				temp = mas[f];
				mas[f] = mas[l];
				mas[l] = temp;
				f++;
				l--;
			}
		} while (f<l);
		if (first<l) Quicksort(mas, first, l, parametr);
		if (f<last) Quicksort(mas, f, last, parametr);
	};

};

class textFile {
public:
	void static writeInFile(Cartoons cart)
	{
		cout << "������� �������� ������ � ����.";
		try {
			string path = "File.txt";
			ofstream fout(path, ofstream::out || ofstream::app);
			if (!fout.is_open()) {
				throw "������ �������� �����!";
			}
			cout << "\n���� ������� ������!" << endl;

			for (int i = 0; i <= cart.top; i++)
			{
				fout << i + 1 << ". " << setw(14)
					<< cart.elements[i].name << setw(14)
					<< cart.elements[i].country << setw(14)
					<< cart.elements[i].parts << setw(14)
					<< cart.elements[i].year << setw(14)
					<< cart.elements[i].rate << endl;
			}
			cout << endl;
			fout.close();

			cout << "������ ��������." << endl;
		}
		catch (char *str) {
			cout << str << endl;
		}
	}

	void static readFromFile()
	{
		cout << "\n������� ������� ������ �� �����!" << endl;

		try {
			ifstream in("File.txt");
			string name;
			string country;
			int parts;
			int year;
			double rate;
			string top;

			Cartoons current;
			if (!in.is_open()) {
				throw "������ �������� �����!";
			}

			if (in.is_open()) {
				while (in >> top >> name >> country >> parts >> year >> rate) {
					current.In(name, country, parts, year, rate);
				}
			}

			in.close();
			cout << "\n���������:" << endl;
			current.Print();
			}
		catch (char *str) {
			cout << str << endl;
		}
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	Cartoons example;
	example.In("����������", "��������", 2, 1982, 8.845);
	example.In("���������", "�����", 1, 2000, 9.015);
	example.In("�������", "������", 1, 1998, 8.168);
	example.In("������������", "�������", 2, 2015, 8.745);
	example.In("������������_2", "�������", 2, 2019, 7.900);
	example.In("���������", "�������", 1, 2010, 8.55);

	example.Print();
	textFile::writeInFile(example);
	textFile::readFromFile();

	cout << "\n���������� �� �����:" << endl;
	example.Quicksort(example.elements, 0, example.top, 0);
	example.Print();

	cout << "\n���������� �� ������:" << endl;
	example.Quicksort(example.elements, 0, example.top, 1);
	example.Print();

	cout << "\n���������� �� ����:" << endl;
	example.Quicksort(example.elements, 0, example.top, 2);
	example.Print();

	cout << "\n���������� �� ������:" << endl;
	example.Quicksort(example.elements, 0, example.top, 3);
	example.Print();

	cout << "\n���������� �� ��������:" << endl;
	example.Quicksort(example.elements, 0, example.top, 4);
	example.Print();
	
	cout << "\n���������� �� ���������� ������ �� ���������� ��������:" << endl;
	example.Quicksort(example.elements, 0, example.top, 3);
	int leftPart = 0;
	for (int i = 1; i < example.top; i++)
	{	
		if (leftPart != i && (example.elements[i].parts != example.elements[i+1].parts || (i+1) == example.top))
		{
			if (i + 1 == example.top)
				example.Quicksort(example.elements, leftPart, i+1, 4);
			else {
				example.Quicksort(example.elements, leftPart, i, 4);
				leftPart = i + 1;
			}		
		}
	}
	example.Print();

	system("pause");
	return 0;
}
