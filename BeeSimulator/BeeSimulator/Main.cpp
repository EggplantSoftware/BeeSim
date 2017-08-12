#include <iostream>
#include <Windows.h>
#include <stdlib.h>

//Header inclusions
#include "Display.h"

using namespace std;

bool isRunning = 1;

Display disp;

int main() {
	disp.initialize_vars();
	cout << "YEAS" << endl;
	while (isRunning == 1) {
		if (GetKeyState(VK_ESCAPE) & 0x8000) {
			isRunning = 0;
		}
		if (GetKeyState('C') & 0x8000) {
			disp.clear_screen();
		}
		if (GetKeyState('D') & 0x8000) {
			disp.draw_something(5, 3);
		}
	}
	return 0;
}