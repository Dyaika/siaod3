#include <iostream>
using namespace std;
#include <ctime>
#include <fstream>
#include <string>
#include "hash_manipulator.h"
#include "binary_manipulator.h"

//������� � �������� ������ � ������� �� ������ �� ���� (� 1, �� �������)
bool readAndInsert(string fname, MyHashTable& t, int row);

//������� ������ �� ����� � ������� �� �����
void doubleDeleteByKey(string fname, MyHashTable& t, int key);

//����� �� ������� � ������ ������ � ������
Patient* searchAndGetRow(string fname, MyHashTable& t, int key);

//������������
void testBinaryHash();
