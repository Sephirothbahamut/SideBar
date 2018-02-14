#include "Screen.h"



Screen::Screen()
	{}


Screen::~Screen()
	{}

int Screen::get_width()
	{
	return GetSystemMetrics(SM_CXSCREEN);
	}

int Screen::get_height()
	{
	return GetSystemMetrics(SM_CYSCREEN);
	}

int Screen::get_taskbar_height()
	{
	RECT rect;
	HWND taskBar = FindWindow(L"Shell_traywnd", NULL);
	if (taskBar && GetWindowRect(taskBar, &rect))
		{
		return rect.bottom - rect.top;
		}
	}
