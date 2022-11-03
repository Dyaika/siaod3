#include "HashApp.h"

HashApp::HashApp()
{
	zadanie1();
}

void HashApp::zadanie1()
{
	int task = 1;
	while (task < 4 and task > 0) {
		cout << "1) Test binary manipulations\n2) Test hash table manipulations\n3) Test bin-hash manipulations\n";
		cin >> task;
		switch (task) {
		case 1:
			testBinF();
			break;
		case 2:
			testHashT();
			break;
		case 3:
			testBinaryHash();
			break;
		default:
			cout << "---exit---\n";
			break;
		}
	}
	
}
