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
	void update_screen();
	void draw_border_hollow(float);
	void draw_border_filled(float);
	void initialize_vars();
	void change_font_size(short int);
	void add_chars(int, int, vector<int>, float);
	void make_button_list();
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