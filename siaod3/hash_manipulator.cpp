#include "hash_manipulator.h"

//печатает что есть в таблице
void printTable(MyHashTable& t)
{
	ListElem* cur;
	for (int i = 0; i < t.L; i++) {
		cout << i << ": {";
		cur = t.T[i].head;
		if (cur) {
			while (cur) {
				cout << "\n    " << cur->key << ": " << cur->offset;
				cur = cur->next;
			}
		}
		cout << "}\n\n";
	}
}

//хэш-функция (число + сумма его цифр % L)
int hashFunc(int key, int L)
{
	int sum = key;
	//int koef = 2147483647 / key;
	int koef = 1;
	while (key > 0) {
		sum += (key % 10) * koef;
		key /= 10;
	}
	return sum % L;
}

//добавляет элемент
void insertInHashTable(int key, int offset, MyHashTable& t)
{
	int count = 0;
	int i = hashFunc(key, t.L);
	ListElem* data = new ListElem;
	data->key = key;
	data->offset = offset;
	if (t.T[i].head == nullptr) {
		t.T[i].head = data;
	}
	else {
		ListElem* cur = t.T[i].head;
		count++;
		while (cur->next) {
			count++;
			cur = cur->next;
		}
		cur->next = data;
	}
	//если записей в 1 элементе много то рехешируем
	//cout << count << "\n";
	if (count >= t.L) {
		reHash(t);
	}
}

//удаляет элемент из таблицы
void deleteFromHashTable(int key, MyHashTable& t)
{
	ListElem* last = nullptr;
	ListElem* cur = t.T[hashFunc(key, t.L)].head;
	while (cur and cur->key != key) {
		last = cur;
		cur = cur->next;
	}
	if (cur) {
		if (last) {
			last->next = cur->next;
		}
		else {
			t.T[hashFunc(key, t.L)].head = cur->next;
		}
		delete cur;
	}
}

//делает пустой массив списков
void MyHashTable::createHashTable()
{
	T = new typeitem[L];
}

//деструктор таблицы
MyHashTable::~MyHashTable()
{
	delete[] T;
	//cout << "DESTRUCTOR " << L;
}

//возвращает смещение иначе -1
int searchInHashTable(int key, MyHashTable& t)
{
	int i = hashFunc(key, t.L);
	ListElem* cur = t.T[i].head;
	while (cur and cur->key != key) {
		cur = cur->next;
	}
	if (!cur) {
		return -1;
	}
	else {
		return cur->offset;
	}
}

//увеличивает размер таблицы в 2 раза
void reHash(MyHashTable& t)
{
	//cout << "rehashing " << t.L;
	t.L = t.L * 2;
	typeitem* oldT = t.T;
	t.createHashTable();
	ListElem* cur;
	//переносим каждый элемент в новый массив, затем удаляем старый
	for (int i = 0; i < t.L / 2; i++) {
		if (oldT[i].head) {
			while (oldT[i].head) {
				cur = oldT[i].head;//запомили удаляемый элемент
				insertInHashTable(cur->key, cur->offset, t);
				oldT[i].head = cur->next;
				delete cur;
			}
		}
	}
	delete[] oldT;
	//cout << "->" << t.L << "\n";
}

//тестирование
void testHashT()
{
	MyHashTable t;
	t.createHashTable();

	int data;
	cout << "How much random elements should we insert?: ";
	cin >> data;
	for (int i = 0; i < data; i++) {
		insertInHashTable((int)rand() % 10 + i * 10 + 1000, i, t);

	}
	cout << "Hash table was created and filled with " << data << " random nodes. ";
	int task = 1;
	while (task > 0 and task < 7) {
		cout << "Choose task:\n1) Test hash function (without inserting)\n2) Print table\n3) Insert node\n4) Delete node\n5) Find node\n6) Rehash table\n";
		cin >> task;
		switch (task)
		{
		case 1:
			cout << "Key = ";
			cin >> data;
			cout << "Table length = " << t.L << "; ";
			cout << "hash = " << hashFunc(data, t.L);
			cout << "\n---completed---\n\n";
			break;
		case 2:
			printTable(t);
			cout << "---completed---\n\n";
			break;
		case 3:
			data = 0;
			while (data != -1) {
				cout << "key, offset (or -1 to stop): ";
				cin >> data;
				if (data != -1) {
					cin >> task;
					insertInHashTable(data, task, t);
				}
			}
			task = 3;
			cout << "\n---completed---\n\n";
			break;
		case 4:
			data = 0;
			while (data != -1) {
				cout << "key (-1 to stop): ";
				cin >> data;
				if (data != -1) {
					deleteFromHashTable(data, t);
				}
			}
			cout << "\n---completed---\n\n";
			break;
		case 5:
			cout << "Key = ";
			cin >> data;
			cout << "offset = " << searchInHashTable(data, t);
			cout << "\n---completed---\n\n";
			break;
		case 6:
			cout << "rehashing " << t.L;
			reHash(t);
			cout << "->" << t.L;
			cout << "\n---completed---\n\n";
			break;
		default:
			break;
		}
	}
	cout << "---exit---";
	
	/*cout << "searching key 1589: " << searchInHashTable(1589, t) << "\n";
	cout << "searching key 1321: " << searchInHashTable(1321, t) << "\n";
	cout << "searching key 1044: " << searchInHashTable(1044, t) << "\n";
	deleteFromHashTable(1105, t);
	deleteFromHashTable(1522, t);
	printTable(t);
	int a = 5;
	int* b = &a;
	*b = 66;
	cout << a;*/
}