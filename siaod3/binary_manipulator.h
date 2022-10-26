#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include "Patient.h"

using namespace std;
void createTextFile(string fname, int length);
void textToBinary(string fname);
void binaryToText(string fname);
void printAllBinary(string fname);
void printRowBinary(string fname, int row);
void deleteByKey_alt(string fname, int key);
void deleteByKey(string fname, int key);
void onlyPatientsWith(string fname, int illness);
void newDoctorFor(string fname, int* cards, int n, char doctor[16]);
void testBinF();