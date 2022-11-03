#include "binary_hash_manipulator.h"

bool readAndInsert(fstream& b, MyHashTable& t, int row)
{
	Patient* temp;
	temp = getRowBinary(b, row);
	if (temp) {
		insertInHashTable(temp->card, row - 1, t);
		return true;
	}
	else {
		return false;
	}
}

void doubleDeleteByKey(fstream& b, MyHashTable& t, int key)
{
	deleteByKey(b, key);
	deleteFromHashTable(key, t);
}

Patient* searchAndGetRow(fstream& b, MyHashTable& t, int key)
{
	int offset;
	offset = searchInHashTable(key, t);
	if (offset != -1) {
		return getRowBinary(b, offset + 1);
	}
	else {
		return nullptr;
	}
}

void testBinaryHash()
{
	cout << "Enter file name: ";
	string str;
	cin >> str;
	cout << "How much notes schould it have? ";
	int length;
	cin >> length;
	createTextFile(str + ".txt", length);
	//создаем бинарный файл
	ofstream b0;
	b0.open(str + "_bin.dat", ios::binary);
	b0.close();
	//открываем его для чтения/записи
	fstream b;
	//cout << "-0-0-0";
	b.open(str + "_bin.dat", ios::binary | ios::out | ios::in);
	textToBinary(str + ".txt", b);
	cout << "File " << str << "_bin.dat was created and filled with " << length << " random notes.\n";
	if (length < 200) {
		printAllBinary(b);
	}
	else {
		cout << "1) ";
		printRowBinary(b, 1);
		cout << "\n" << length / 2 << ") ";
		printRowBinary(b, length / 2);
		cout << "\n" << length << ") ";
		printRowBinary(b, length);
		cout << "\n";
	}
	int task = 1;
	int row = 1;
	double time;
	int data;
	Patient* temp = nullptr;
	MyHashTable t;
	t.createHashTable();
	cout << "Empty hash table created.\n";
	while (task > 0 and task < 6) {
		cout << "Choose task:\n1) Read note and insert to hash table\n2) Delete by key\n3) Find note by key\n4) Print file\n5) Print table\n";
		cin >> task;
		switch (task)
		{
		case 1:
			if (row <= length) {
				cout << "Add all? 1-yes\n";
				cin >> data;
				if (data == 1) {
					while (row <= length) {
						readAndInsert(b, t, row);
						row++;
					}
					cout << "Added " << row - 1 << "/" << length << "\n";
				}
				else {
					readAndInsert(b, t, row);
					cout << "Added " << row << "/" << length << "\n";
					row++;

				}
			}
			else {
				cout << "All notes are already in hash table\n";
			}
			cout << "---completed---\n\n";
			break;
		case 2:
			cout << "Key to delete = ";
			cin >> data;
			doubleDeleteByKey(b, t, data);
			cout << "---completed---\n\n";
			break;
		case 3:
			cout << "Key = ";
			cin >> data;
			time = clock();
			temp = searchAndGetRow(b, t, data);
			cout << "it took " << clock() - time << "ms to find.\n";
			if (temp) {
				cout << temp->card << " " << temp->illness << " " << temp->doctor;
			}
			else {
				cout << "no note with this key";
			}
			cout << "\n---completed---\n\n";
			break;
		case 4:
			printAllBinary(b);
			cout << "---completed---\n\n";
			break;
		case 5:
			printTable(t);
			break;
		default:
			if (length < 200) {
				cout << "Final " << str << "_bin.dat:\n";
				//printAllBinary(str);
				cout << "Final hash table:\n";
				printTable(t);
			}
			break;
		}
	}
	b.close();
	cout << "---exit---\n";
}
