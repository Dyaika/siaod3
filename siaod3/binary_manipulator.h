#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include "Patient.h"

using namespace std;

//создает текстовый файл со строками
void createTextFile(string fname, int length);

//создает бинарный файл по текстовому
void textToBinary(string fname, fstream& b);

//создает текстовый файл по бинарному
void binaryToText(fstream& b, string fname);

//печатает из бинарного файла
void printAllBinary(fstream& b);

//печатает 1 ряд
void printRowBinary(fstream& b, int row);

//доступ к записи
Patient* getRowBinary(fstream& b, int row);

void deleteByKey_alt(string fname, int key);//старая реализация

bool deleteByKey(fstream& b, int key);
void onlyPatientsWith(fstream& b, string fname, int illness);
void newDoctorFor(fstream& b, int* cards, int n, char doctor[16]);
string testBinF();

//bin.open(fname + "_bin.dat", ios::binary);