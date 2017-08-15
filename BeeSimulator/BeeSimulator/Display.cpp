#include "Display.h"

Display::Display(){}

//Various class definitions here
class Button {
public:
	Button(unsigned int, unsigned int, vector <int>, float, float, bool);
	void button_is_selected(bool);
	vector <int> get_display_name();
	float get_standing_color();
	float get_selected_color();
private:
	vector <int> displayedName;
	bool buttonIsSelected = 0;
	float standingColor = 0x0F;
	float selectedColor = 0xF0;
	unsigned int posx;
	unsigned int posy;
};

class ButtonList {
public: 
	ButtonList(int, int, int, int, bool, vector<vector<int>>, vector <float>, vector<float>);
	void select_button(short int);
	void print_buttons();
	short int get_selected_button();
private:
	int selectedButton = 0;
	int actualSpacing = 0;
	bool stackDirection = 0;
	int posY;
	int posX;
	vector <unique_ptr<Button>> buttonList;
	vector <int> tempOutput;
};

#pragma region display

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
float displayColor[dispX][dispY];
float bufferColor[dispX][dispY];

ButtonList* currentList;

void Display::draw_border_hollow(float c) {
	//Upper Left corner
	bufferScreen[0][0] = 201;
	bufferColor[0][0] = c;
	for (int x = 1; x != dispX-1; x++) {
		//Horizontal
		bufferScreen[x][0] = 205;
		bufferColor[x][0] = c;
	}
	//Upper Right corner
	bufferScreen[dispX-1][0] = 187;
	bufferColor[dispX-1][0] = c;
	for (int y = 1; y != dispY-1; y++) {
		//Vertical
		bufferScreen[0][y] = 186;
		bufferColor[0][y] = c;
	}
	//Lower Left corner
	bufferScreen[0][dispY-1] = 200;
	bufferColor[0][dispY-1] = c;
	for (int x = 1; x != dispX-1; x++) {
		//Horizontal
		bufferScreen[x][dispY-1] = 205;
		bufferColor[x][dispY - 1] = c;
	}
	//Lower Right Corner
	bufferScreen[dispX-1][dispY-1] = 188;
	bufferColor[dispX-1][dispY - 1] = c;
	for (int y = 1; y != dispY - 1; y++) {
		//Vertical
		bufferScreen[dispX-1][y] = 186;
		bufferColor[dispX-1][y] = c;
	}
}

void Display::draw_border_filled(float c) {
	//Upper Left corner
	bufferScreen[0][0] = 218;
	bufferColor[0][0] = c;
	for (int x = 1; x != dispX - 1; x++) {
		//Horizontal
		bufferScreen[x][0] = 196;
		bufferColor[x][0] = c;
	}
	//Upper Right corner
	bufferScreen[dispX - 1][0] = 191;
	bufferColor[dispX - 1][0] = c;
	for (int y = 1; y != dispY - 1; y++) {
		//Vertical
		bufferScreen[0][y] = 179;
		bufferColor[0][y] = c;
	}
	//Lower Left corner
	bufferScreen[0][dispY - 1] = 192;
	bufferColor[0][dispY - 1] = c;
	for (int x = 1; x != dispX - 1; x++) {
		//Horizontal
		bufferScreen[x][dispY - 1] = 196;
		bufferColor[x][dispY - 1] = c;
	}
	//Lower Right Corner
	bufferScreen[dispX - 1][dispY - 1] = 217;
	bufferColor[dispX - 1][dispY - 1] = c;
	for (int y = 1; y != dispY - 1; y++) {
		//Vertical
		bufferScreen[dispX - 1][y] = 179;
		bufferColor[dispX - 1][y] = c;
	}
}

void Display::update_screen() {
	for (int y = 0; y != dispY; ++y)
	{
		for (int x = 0; x != dispX; ++x)
		{
			if (displayedScreen[x][y] == bufferScreen[x][y] && displayColor[x][y] == bufferColor[x][y]) {
				continue;
			}
			displayColor[x][y] = bufferColor[x][y];
			SetConsoleTextAttribute(consoleOut, displayColor[x][y]);
			displayedScreen[x][y] = bufferScreen[x][y];
			tempDraw = { (SHORT)x, (SHORT)y };
			SetConsoleCursorPosition(consoleOut, tempDraw);
			cout << displayedScreen[x][y];
		}
	}
	cout.flush();
}

void Display::add_chars(int x, int y, vector<int> c, float col) {
	for (int i = 0; i != c.size(); i++) {
		bufferScreen[x + i][y] = c[i];
		bufferColor[x + i][y] = col;
	}
}

Display::~Display() {};

#pragma endregion

#pragma region button

float Button::get_standing_color() { return standingColor; }
float Button::get_selected_color() { return selectedColor; }

Button::Button(unsigned int x, unsigned int y, vector<int> name, float stCol, float seCol, bool isSel) {
	posx = x;
	posy = y;
	displayedName = name;
	standingColor = stCol;
	selectedColor = seCol;
	buttonIsSelected = isSel;
}

void Button::button_is_selected(bool b) {
	buttonIsSelected = b;
}

vector<int> Button::get_display_name() {
	return displayedName;
}

#pragma endregion

#pragma region buttonList

//ButtonList implementation below

short int ButtonList::get_selected_button() { return selectedButton; }

ButtonList::ButtonList(int x, int y, int num, int spacing, bool stack, vector<vector<int>> names, vector<float> stCol, vector<float> seCol) {
	delete(currentList);
	actualSpacing = spacing;
	stackDirection = stack;
	posX = x;
	posY = y;
	for (int i = 0; i != num; i++) {
		buttonList.emplace_back(make_unique<Button>(x, y, names[i], stCol[i], seCol[i], 0));
	}
	this->print_buttons();
}

void ButtonList::print_buttons() {
	if (stackDirection == 1) {
		for (int b = 0; b != buttonList.size(); b++) {
			tempOutput = buttonList[b]->get_display_name();
			for (int i = 0; i != tempOutput.size(); i++) {
				bufferScreen[posX + i + (b*actualSpacing)][posY] = tempOutput[i];
				if (selectedButton == b) {
					bufferColor[posX + i + (b*actualSpacing)][posY] = buttonList[b]->get_selected_color();
				}
				else {
					bufferColor[posX + i + (b*actualSpacing)][posY] = buttonList[b]->get_standing_color();
				}
			}
			tempOutput.resize(0);
		}
	} else {
		for (int b = 0; b != buttonList.size(); b++) {
			tempOutput = buttonList[b]->get_display_name();
			for (int i = 0; i != tempOutput.size(); i++) {
				bufferScreen[posX][posY + i + (b*actualSpacing)] = tempOutput[i];
				if (selectedButton == b) {
					bufferColor[posX + i + (b*actualSpacing)][posY] = buttonList[b]->get_selected_color();
				}
				else {
					bufferColor[posX + i + (b*actualSpacing)][posY] = buttonList[b]->get_standing_color();
				}
			}
			tempOutput.resize(0);
		}
	}
}

void ButtonList::select_button(short int i) {
	if (selectedButton =! i) {
		buttonList[selectedButton]->button_is_selected(0);
		if (i > buttonList.size()) {
			buttonList[buttonList.size()]->button_is_selected(1);
		}
		else if (i < 0) {
			buttonList[0]->button_is_selected(1);
		}
		else {
			buttonList[buttonList.size()]->button_is_selected(1);
		}
	}
}

#pragma endregion

//Test function for testing only
void Display::make_button_list() {
	ButtonList testList(1, 1, 4, 2, 1, { {232}, {232}, {232}, {232}, }, { 0x0F, 0x0E, 0x0D, 0x0C }, { 0x1F, 0x1E, 0x1D, 0x1C });
}