#include "binary_manipulator.h"

//создает текстовый файл со строками
void createTextFile(string fname, int length)
{
	ofstream tout;
	if (!tout.is_open()) {
		tout.open(fname + ".txt");
	}
	string doctors[5] = { "Ivanov", "Petrov", "Razshildyeav", "Archipov", "Shabalov"};

	int n = rand() % 10 + length;
	//карточка код фамилия
	for (int i = 0; i < n; i++) {
		tout << (int)rand() % 10 + i * 10 + 1000 << " " << (int)rand() % 15 + 1 << " " << doctors[rand() % 5] << "\n";
	}
	tout.clear();
	if (tout.good()) {
		tout.close();
	}
	else {
		exit(1);
	}
}

//создает бинарный файл по текстовому
void textToBinary(string fname)
{
	ofstream bout;
	bout.open(fname + "_bin.dat", ios::binary);
	ifstream tin;
	tin.open(fname + ".txt");
	if (!bout.is_open() or !tin.is_open()) {
		exit(2);
	}
	Patient temp;
	tin >> temp.card >> temp.illness >> temp.doctor;
	while (!tin.eof()) {
		bout.write((char*)&temp, sizeof(Patient));
		tin >> temp.card >> temp.illness >> temp.doctor;
	}
	bout.clear();
	tin.clear();
	if (bout.good() and tin.good()) {
		bout.close();
		tin.close();
	}
	else {
		exit(3);
	}
}

//создает текстовый файл по бинарному
void binaryToText(string fname)
{
	ifstream bin;
	bin.open(fname + "_bin.dat", ios::binary);
	ofstream tout;
	tout.open(fname + "_text.txt");
	if (!tout.is_open() or !bin.is_open()) {
		exit(4);
	}
	Patient temp;
	bin.read((char*)&temp, sizeof(Patient));
	while (!bin.eof()) {
		tout << temp.card << " " << temp.illness << " " << temp.doctor << "\n";
		bin.read((char*)&temp, sizeof(Patient));
	}
	tout.clear();
	bin.clear();
	if (tout.good() and bin.good()) {
		tout.close();
		bin.close();
	}
	else {
		exit(5);
	}
}

//печатает из бинарного файла
void printAllBinary(string fname)
{
	ifstream bin;
	bin.open(fname + "_bin.dat", ios::binary);
	if (!bin.is_open()) {
		exit(6);
	}
	Patient temp;
	bin.read((char*)&temp, sizeof(Patient));
	while (!bin.eof()) {
		cout << temp.card << " " << temp.illness << " " << temp.doctor << "\n";
		bin.read((char*)&temp, sizeof(Patient));
	}
	bin.clear();
	if (bin.good()) {
		bin.close();
	}
	else {
		exit(7);
	}
}

//печатает из бинарного файла 1 запись (row это НОМЕР ряда, а не индекс)
void printRowBinary(string fname, int row)
{
	ifstream bin;
	bin.open(fname + "_bin.dat", ios::binary);
	if (!bin.is_open()) {
		exit(8);
	}
	Patient temp;
	bin.seekg((row - 1) * sizeof(Patient), ios::beg);
	bin.read((char*)&temp, sizeof(Patient));
	if (bin.eof() or row < 1) {
		cout << "out of range\n";
	}
	else {
		cout << temp.card << " " << temp.illness << " " << temp.doctor << "\n";
	}
	bin.clear();
	if (bin.good()) {
		bin.close();
	}
	else {
		exit(9);
	}
}

//доступ к записи
Patient* getRowBinary(string fname, int row){
	ifstream bin;
	bin.open(fname + "_bin.dat", ios::binary);
	if (!bin.is_open()) {
		exit(20);
	}
	Patient temp;
	bool flag = false;
	bin.seekg((row - 1) * sizeof(Patient), ios::beg);
	bin.read((char*)&temp, sizeof(Patient));
	if (bin.eof() or row < 1) {
		flag = true;
	}
	bin.clear();
	if (bin.good()) {
		bin.close();
	}
	else {
		exit(21);
	}
	if (flag) {
		return nullptr;
	}
	Patient *res = new Patient;
	res->card = temp.card;
	for (int i = 0; i < 16; i++) {
		res->doctor[i] = temp.doctor[i];
	}
	res->illness = temp.illness;
	return res;
}

//заменяет на последнюю запись
void deleteByKey(string fname, int key)
{
	ifstream bin;
	bin.open(fname + "_bin.dat", ios::binary);
	if (!bin.is_open()) {
		exit(10);
	}
	Patient last;
	int i = 0;
	int pos = -1;
	bin.read((char*)&last, sizeof(Patient));
	if (last.card == key) {
		pos = i;
	}
	i++;
	while (!bin.eof()) {
		bin.read((char*)&last, sizeof(Patient));
		if (last.card == key) {
			pos = i;
		}
		i++;
	}
	bin.clear();
	if (bin.good()) {
		bin.close();
	}
	else {
		exit(11);
	}
	if (pos == -1) {
		cout << "No such patient\n";
	}
	else {
		fstream bout;
		bout.open(fname + "_bin.dat", ios::binary | ios::out | ios::in);
		if (!bout.is_open()) {
			exit(12);
		}

		bout.seekg(pos * sizeof(Patient), ios::beg);
		bout.write((char*)&last, sizeof(Patient));

		//bout.flush();
		bout.clear();
		if (bout.good()) {
			bout.close();
		}
		else {
			exit(13);
		}
	}
	
}

//удаляет запись смещением всех остальных (в конце дублируется запись)
void deleteByKey_alt(string fname, int key)
{
	fstream b;
	b.open(fname + "_bin.dat", ios::binary | ios::out | ios::in);
	if (!b.is_open()) {
		exit(18);
	}
	int is_deleted = 0;
	int count = 0;
	Patient temp;
	while (b.read((char*)&temp, sizeof(Patient))) {
		if (temp.card == key) {
			is_deleted = 1;
			//b.seekg(sizeof(Patient) * (count + is_deleted), ios::beg);
			if (!b.read((char*)&temp, sizeof(Patient))) {
				break;
			}
		}
		b.clear();
		b.seekg(sizeof(Patient) * (count), ios::beg);
		cout << temp.card << " " << temp.illness << " " << temp.doctor << "\n";
		b.write((char*)&temp, sizeof(Patient));
		count++;
		b.clear();
		b.seekg(sizeof(Patient) * (count + is_deleted), ios::beg);
	}
	b.clear();
	if (b.good()) {
		b.close();
	}
	else {
		exit(19);
	}
}

//выбирает определенных больных
void onlyPatientsWith(string fname, int illness)
{
	ofstream bout;
	bout.open(fname + to_string(illness) + "_bin.dat", ios::binary);
	ifstream bin;
	bin.open(fname + "_bin.dat", ios::binary);
	//cout << "DELETE THIS\n" << bout.is_open() << " " << bin.is_open() << "\nDELETE THIS\n";
	if (!bout.is_open() or !bin.is_open()) {
		exit(14);
	}
	Patient temp;
	bin.read((char*)&temp, sizeof(Patient));
	while (!bin.eof()) {
		if (temp.illness == illness) {
			bout.write((char*)&temp, sizeof(Patient));
		}
		bin.read((char*)&temp, sizeof(Patient));
	}
	bout.clear();
	bin.clear();
	if (bout.good() and bin.good()) {
		bout.close();
		bin.close();
	}
	else {
		exit(15);
	}
}

//назначает доктора, не готова
void newDoctorFor(string fname, int* cards, int n, char doctor[16])
{
	fstream b;
	b.open(fname + "_bin.dat", ios::binary | ios::out | ios::in);
	if (!b.is_open()) {
		exit(16);
	}
	Patient temp;
	int count = 0;
	b.read((char*)&temp, sizeof(Patient));
	while (!b.eof())
	{
		for (int i = 0; i < n; i++) {
			if (temp.card == cards[i]) {
				for (int j = 0; j < 16; j++) {
					temp.doctor[j] = doctor[j];
				}
				break;
			}
		}
		//шагнули назад и переписали
		b.seekg(sizeof(Patient) * (count), ios::beg);
		b.write((char*)&temp, sizeof(Patient));
		//cout << temp.card << " " << temp.illness << " " << temp.doctor << " " << count << "\n";
		count++;
		b.clear();
		//шагаем дальше и читаем для будущего раза
		b.seekg(sizeof(Patient) * (count), ios::beg);
		b.read((char*)&temp, sizeof(Patient));
	}
	b.clear();
	if (b.good()) {
		b.close();
	}
	else {
		exit(17);
	}
}

//тестирование из предыдущей работы
string testBinF()
{
	Patient* temp = nullptr;
	string str;
	cout << "Enter file name: ";
	cin >> str;
	int* arr;
	int data;
	cout << "How much notes? ";
	cin >> data;
	createTextFile(str, data);
	int task = 1;
	cout << "File " << str << ".txt was created and filled with random notes. ";

	while (task > 0 and task < 8) {
		cout << "Choose task:\n1) To binary\n2) To text\n3) Print from binary file\n4) Print row\n5) Delete by key\n6) Create new file with only illness\n7) New doctor to\n";
		cin >> task;
		switch (task)
		{
		case 1:
			textToBinary(str);
			cout << "Binary file is " << str << "_bin.dat\n";
			cout << "---completed---\n\n";
			break;
		case 2:
			binaryToText(str);
			cout << "Text file is " << str << "_text.txt\n";
			cout << "---completet---\n\n";
			break;
		case 3:
			printAllBinary(str);
			cout << "\n---completed---\n\n";
			break;
		case 4:
			cout << "Row = ";
			cin >> data;
			cout << "Row " << data << ": ";
			temp = getRowBinary(str, data);
			if (temp) {
				cout << temp->card << " " << temp->illness << " " << temp->doctor;
			}
			cout << "\n---completed---\n\n";
			break;
		case 5:
			cout << "Key = ";
			cin >> data;
			deleteByKey(str, data);
			cout << "\n---completed---\n\n";
			break;
		case 6:
			cout << "Illness = ";
			cin >> data;
			onlyPatientsWith(str, data);
			cout << str << data << "_bin.dat:\n";
			printAllBinary(str + to_string(data));
			cout << "\n---completed---\n\n";
			break;
		case 7:
			cout << "How much patients? ";
			cin >> data;
			arr = new int[data];
			for (int i = 0; i < data; i++) {
				cout << i + 1 << ") ";
				cin >> arr[i];
			}
			cout << "Who is new doctor? ";
			char doc[16];
			cin >> doc;
			newDoctorFor(str, arr, data, doc);
			cout << "\n---completed---\n\n";
			delete[] arr;
			break;
		default:
			break;
		}
	}
	cout << "---exit---\n";
	return str;
}

