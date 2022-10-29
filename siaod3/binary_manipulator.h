#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include "Patient.h"

using namespace std;

//������� ��������� ���� �� ��������
void createTextFile(string fname, int length);

//������� �������� ���� �� ����������
void textToBinary(string fname, fstream& b);

//������� ��������� ���� �� ���������
void binaryToText(fstream& b, string fname);

//�������� �� ��������� �����
void printAllBinary(fstream& b);

//�������� 1 ���
void printRowBinary(fstream& b, int row);

//������ � ������
Patient* getRowBinary(fstream& b, int row);

void deleteByKey_alt(string fname, int key);//������ ����������

bool deleteByKey(fstream& b, int key);
void onlyPatientsWith(fstream& b, string fname, int illness);
void newDoctorFor(fstream& b, int* cards, int n, char doctor[16]);
string testBinF();

//bin.open(fname + "_bin.dat", ios::binary);