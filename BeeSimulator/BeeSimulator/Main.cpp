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
			disp.draw_box(2, 2, 7, 7);
		}
		if (GetKeyState('U') & 0x8000) {
			disp.update_screen();
		}
	}
	return 0;
}

