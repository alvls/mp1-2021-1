#ifndef __MYDISPLAY_H__
#define __MYDISPLAY_H__

#include <windows.h>

class MyDisplay
{
private:
	HANDLE console;
	CONSOLE_CURSOR_INFO cursor;
public:
	MyDisplay();
	~MyDisplay();
	void ShowCursor();
	void HideCursor();
	void ClsConsole();
	void PauseConsole();
	void ChangePosCursor(int x, int y);
	void GoAndDrawSymbol(int x, int y, char symbol);
	void SetColor(int color_text, int color_back_ground);
};

#endif __MYDISPLAY_H__
