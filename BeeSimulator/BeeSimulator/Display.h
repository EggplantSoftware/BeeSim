#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <math.h>
#include <Windows.h>
#include <stdlib.h>

using namespace std;

//Header inclusions below

class Display
{
public:
	Display();
	void draw_something(int, int);
	void update_screen();
	void draw_border_hollow();
	void draw_border_filled();
	void initialize_vars();
	void change_font_size(short int);
	void add_chars(int, int, short unsigned int[], float);
	~Display();
private:
	HANDLE consoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE consoleIn = GetStdHandle(STD_INPUT_HANDLE);
	CONSOLE_FONT_INFOEX cfi;
	COORD screenSize = { (SHORT)160, (SHORT)42 };
	COORD tempDraw;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
};

//Display ration is 41:157 at font Y size 25

#endif