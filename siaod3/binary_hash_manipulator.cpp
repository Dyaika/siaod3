#include "binary_hash_manipulator.h"

bool readAndInsert(string fname, MyHashTable& t, int row)
{
	Patient* temp;
	temp = getRowBinary(fname, row);
	if (temp) {
		insertInHashTable(temp->card, row - 1, t);
		return true;
	}
	else {
		return false;
	}
}

void doubleDeleteByKey(string fname, MyHashTable& t, int key)
{
	deleteByKey(fname, key);
	deleteFromHashTable(key, t);
}

Patient* searchAndGetRow(string fname, MyHashTable& t, int key)
{
	int offset;
	offset = searchInHashTable(key, t);
	if (offset != -1) {
		return getRowBinary(fname, offset + 1);
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
	createTextFile(str, length);
	textToBinary(str);
	cout << "File " << str << "_bin.dat was created and filled with " << length << " random notes.\n";
	if (length < 200) {
		printAllBinary(str);
	}
	else {
		cout << "1) ";
		printRowBinary(str, 1);
		cout << length / 2 << ") ";
		printRowBinary(str, length / 2);
		cout << length << ") ";
		printRowBinary(str, length);
	}
	int task = 1;
	int row = 1;
	double time;
	int data;
	Patient* temp = nullptr;
	MyHashTable t;
	t.createHashTable();
	cout << "Empty hash table created.\n";
	while (task > 0 and task < 4) {
		cout << "\nChoose task:\n1) Read note and insert to hash table\n2) Delete by key\n3) Find note by key\n";
		cin >> task;
		switch (task)
		{
		case 1:
			if (row <= length) {
				cout << "Add all? 1-yes\n";
				cin >> data;
				if (data == 1) {
					while (row <= length) {
						readAndInsert(str, t, row);
						row++;
					}
					cout << "Added " << row - 1 << "/" << length << "\n";
				}
				else {
					readAndInsert(str, t, row);
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
			cout << "Key = ";
			cin >> data;
			doubleDeleteByKey(str, t, data);
			cout << "---completed---\n\n";
			break;
		case 3:
			cout << "Key = ";
			cin >> data;
			time = clock();
			temp = searchAndGetRow(str, t, data);
			cout << "it took " << clock() - time << "ms to find.\n";
			if (temp) {
				cout << temp->card << " " << temp->illness << " " << temp->doctor;
			}
			else {
				cout << "no note with this key";
			}
			cout << "\n---completed---\n\n";
			break;
		default:
			if (length < 200) {
				cout << "Final " << str << "_bin.dat:\n";
				printAllBinary(str);
				cout << "Final hash table:\n";
				printTable(t);
			}
			break;
		}
	}
	cout << "---exit---\n";
}
