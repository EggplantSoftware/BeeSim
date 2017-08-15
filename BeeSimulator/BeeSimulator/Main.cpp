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
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	cout << "Press F11 for Full Screen" << endl;
	cout << "Press 'C' To Continue" << endl;
	while (isRunning == 1) {
		if (GetKeyState(VK_ESCAPE) & 0x8000) {
			isRunning = 0;
		}
		if (GetKeyState('C') & 0x8000) {
			disp.draw_border_filled(0x0F);
		}
		if (GetKeyState('D') & 0x8000) {
			disp.draw_border_hollow(0x0F);
		}
		if (GetKeyState('U') & 0x8000) {
			disp.update_screen();
		}
		if (GetKeyState('F') & 0x8000) {
			disp.add_chars(130, 6, { 123, 121 } , 0x0F);
		}
		if (GetKeyState('B') & 0x8000) {
			disp.make_button_list();
		}
		if (GetKeyState(VK_ADD) & 0x8000) {
			disp.change_font_size(1);
		}
		if (GetKeyState(VK_SUBTRACT) & 0x8000) {
			disp.change_font_size(-1);
		}
		Sleep(60);
	}
	return 0;
}

