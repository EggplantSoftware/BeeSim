#include "Display.h"

Display::Display(){}


void Display::initialize_vars() {
	/*SetConsoleDisplayMode(consoleOut, CONSOLE_FULLSCREEN_MODE, 0);
	GetConsoleScreenBufferInfo(consoleOut, &csbi);
	newSbSize.X = csbi.dwSize.X + 200;
	newSbSize.Y = csbi.dwSize.Y + 200;
	SetConsoleScreenBufferSize(consoleOut, newSbSize);*/

	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 25;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(consoleOut, FALSE, &cfi);
}

	const unsigned int dispX = 100;
	const unsigned int dispY = 30;

	char bufferScreen[dispX][dispY];
	char displayedScreen[dispX][dispY];

void Display::clear_screen() {
	COORD topLeft = { 0, 0 };
	cout.flush();
	if (!GetConsoleScreenBufferInfo(consoleOut, &csbi)) {
		// TODO: Handle failure!
		cout << "error getting screen size" << endl;
		abort();
	}
	DWORD length = csbi.dwSize.X * csbi.dwSize.Y;
	DWORD written;
	FillConsoleOutputCharacter(consoleOut, TEXT(' '), length, topLeft, &written);
	FillConsoleOutputAttribute(consoleOut, csbi.wAttributes, length, topLeft, &written);
	SetConsoleCursorPosition(consoleOut, topLeft);
}

void Display::draw_something(int x, int y) {
	cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(consoleOut, coord);

	SetCursorPos(x, y);
	cout << "Benis";
}

void Display::draw_box(int x1, int y1, int x2, int y2) {
	SetCursorPos(x1, y1);
	for (int ix = 0; ix != x2; ix++) {

	}
}

void Display::update_screen() {
	for (int y = 0; y != dispY; ++y)
	{
		for (int x = 0; x != dispX; ++x)
		{
			if (displayedScreen[x][y] == bufferScreen[x][y]) {
				continue;
			}
			SetCursorPos(x, y);
			cout << displayedScreen[x][y];
		}
	}
}

Display::~Display()
{
}