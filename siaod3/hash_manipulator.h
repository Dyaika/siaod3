#include <iostream>
#include <fstream>
#include <string>
#include "Patient.h"
using namespace std;

//однонаправленный список, хранит уникальное значение key пациента и его позицию в файле
#ifndef listelem_struct
#define listelem_struct
struct ListElem
{
	int key = 0;
	int offset = 0;//на сколько смещаемся от начала файла
	ListElem* next = nullptr;
};
#endif // !listelem_struct

#ifndef typeitem_struct
#define typeitem_struct
struct typeitem
{
	ListElem* head = nullptr;
	~typeitem();
};

#endif // !typeitem_struct


#ifndef myhashtable_struct
#define myhashtable_struct
struct MyHashTable
{
	int L = 5;
	typeitem* T;
	void createHashTable();
	~MyHashTable();

};
#endif // !myhashtable_struct


void printTable(MyHashTable& t);
int hashFunc(int key, int L);
void insertInHashTable(int key, int offset, MyHashTable& t);
void deleteFromHashTable(int key, MyHashTable& t);
int searchInHashTable(int key, MyHashTable& t);
void testHashT();
void reHash(MyHashTable& t);