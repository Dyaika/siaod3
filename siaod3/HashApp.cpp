#include "HashApp.h"

HashApp::HashApp()
{
	zadanie1();
}

void HashApp::clearscreen(int n) {
	for (int i = 0; i < n; i++) {
		cout << "\n";
	}
}
void HashApp::zadanie1()
{
	int task = 1;
	while (task < 3 and task > 0) {
		cout << "1) Test binary manipulations\n2) Test hash table manipulations\n3) Test bin-hash manipulations\n";
		cin >> task;
		switch (task) {
		case 1:
			testBinF();
			//clearscreen();
			break;
		case 2:
			testHashT();
			//clearscreen();
			break;
		case 3:
			testBinaryHash();
			//clearscreen();
			break;
		default:
			cout << "---exit---\n";
			break;
		}
	}
	
	//string str = testBinF();
	//testHashT();

}
