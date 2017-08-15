#include "Display.h"

Display::Display(){}

void Display::initialize_vars() {
	GetConsoleScreenBufferInfo(consoleOut, &csbi);
	screenSize.X = 156;
	screenSize.Y = 40;
	SetConsoleScreenBufferSize(consoleOut, screenSize);

	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 25;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(consoleOut, FALSE, &cfi);
}

void Display::change_font_size(short int i) {
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y += i;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(consoleOut, FALSE, &cfi);
}

char currentChar;

//Default sizes for 1920 x 1080 p monitor below, change font size if text is off
const unsigned int dispX = 160;
const unsigned int dispY = 42;

char displayedScreen[dispX][dispY];
char bufferScreen[dispX][dispY];

void Display::draw_something(int x, int y) {
	cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(consoleOut, coord);

	SetCursorPos(x, y);
	cout << "Benis";
}

void Display::draw_border_hollow() {
	//Upper Left corner
	bufferScreen[0][0] = 201;
	for (int x = 1; x != dispX-1; x++) {
		//Horizontal
		bufferScreen[x][0] = 205;
	}
	//Upper Right corner
	bufferScreen[dispX-1][0] = 187;
	for (int y = 1; y != dispY-1; y++) {
		//Vertical
		bufferScreen[0][y] = 186;
	}
	//Lower Left corner
	bufferScreen[0][dispY-1] = 200;
	for (int x = 1; x != dispX-1; x++) {
		//Horizontal
		bufferScreen[x][dispY-1] = 205;
	}
	//Lower Right Corner
	bufferScreen[dispX-1][dispY-1] = 188;
	for (int y = 1; y != dispY - 1; y++) {
		//Vertical
		bufferScreen[dispX-1][y] = 186;
	}
}

void Display::draw_border_filled() {
	//Upper Left corner
	bufferScreen[0][0] = 218;
	for (int x = 1; x != dispX - 1; x++) {
		//Horizontal
		bufferScreen[x][0] = 196;
	}
	//Upper Right corner
	bufferScreen[dispX - 1][0] = 191;
	for (int y = 1; y != dispY - 1; y++) {
		//Vertical
		bufferScreen[0][y] = 179;
	}
	//Lower Left corner
	bufferScreen[0][dispY - 1] = 192;
	for (int x = 1; x != dispX - 1; x++) {
		//Horizontal
		bufferScreen[x][dispY - 1] = 196;
	}
	//Lower Right Corner
	bufferScreen[dispX - 1][dispY - 1] = 217;
	for (int y = 1; y != dispY - 1; y++) {
		//Vertical
		bufferScreen[dispX - 1][y] = 179;
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
			displayedScreen[x][y] = bufferScreen[x][y];
			tempDraw = { (SHORT)x, (SHORT)y };
			SetConsoleCursorPosition(consoleOut, tempDraw);
			cout << displayedScreen[x][y];
		}
	}
	tempDraw = { (SHORT)1, (SHORT)1 };
	SetConsoleCursorPosition(consoleOut, tempDraw);
	cout.flush();
}

void Display::add_chars(int x, int y, short unsigned int c[], float col) {
	for (int i = 0; i != sizeof(c); i++) {
		if (x + i < dispX) {
			bufferScreen[x + i][y] = c[i];
		}
		else {
			bufferScreen[x + i][y] = c[i];
		}
	}
}

Display::~Display()
{
}