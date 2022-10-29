#include <iostream>
using namespace std;
#include <ctime>
#include <fstream>
#include <string>
#include "hash_manipulator.h"
#include "binary_manipulator.h"

//������� � �������� ������ � ������� �� ������ �� ���� (� 1, �� �������)
bool readAndInsert(fstream& b, MyHashTable& t, int row);

//������� ������ �� ����� � ������� �� �����
void doubleDeleteByKey(fstream& b, MyHashTable& t, int key);

//����� �� ������� � ������ ������ � ������
Patient* searchAndGetRow(fstream& b, MyHashTable& t, int key);

//������������
void testBinaryHash();
