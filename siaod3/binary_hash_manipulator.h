#include <iostream>
using namespace std;
#include <ctime>
#include <fstream>
#include <string>
#include "hash_manipulator.h"
#include "binary_manipulator.h"

//считать и вставить запись в таблицу по номеру ее ряда (с 1, не индексу)
bool readAndInsert(string fname, MyHashTable& t, int row);

//удалить запись из файла и таблицы по ключу
void doubleDeleteByKey(string fname, MyHashTable& t, int key);

//поиск по таблице и прямой доступ к записи
Patient* searchAndGetRow(string fname, MyHashTable& t, int key);

//тестирование
void testBinaryHash();
