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
	void clear_screen();
	void draw_something(int, int);
	void update_screen();
	void draw_box(int, int, int, int);
	void initialize_vars();
	void print_screen_size();
	~Display();
private:
	HANDLE consoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE consoleIn = GetStdHandle(STD_INPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	CONSOLE_FONT_INFOEX cfi;
	COORD newSbSize;
};

//Display ration is 41:157 at font Y size 25

#endif