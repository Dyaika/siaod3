#include <iostream>
using namespace std;
#include <ctime>
#include <fstream>
#include <string>
#include "hash_manipulator.h"
#include "binary_manipulator.h"

//считать и вставить запись в таблицу по номеру ее ряда (с 1, не индексу)
bool readAndInsert(fstream& b, MyHashTable& t, int row);

//удалить запись из файла и таблицы по ключу
void doubleDeleteByKey(fstream& b, MyHashTable& t, int key);

//поиск по таблице и прямой доступ к записи
Patient* searchAndGetRow(fstream& b, MyHashTable& t, int key);

//тестирование
void testBinaryHash();
