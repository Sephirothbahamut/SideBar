#pragma once

//#define NOMINMAX // https://codewarrior.windows.narkive.com/SouEiY8w/problems-compiling-gdi-gdiplus-example-from-msdn
#include <Windows.h>
//#include <minmax.h>
//#include <gdiplus.h>
/*namespace Gdiplus
	{
	using std::min;
	using std::max;
	}*/


namespace Win
	{
	namespace Autorun
		{
		void add(LPCWSTR name);
		void remove(LPCWSTR name);
		};
	namespace Screen
		{
		int get_min_x();
		int get_max_x();
		int get_min_y();
		int get_max_y();
		int get_width();
		int get_height();
		int get_taskbar_height();
		};

	struct handle_data
		{
		unsigned long process_id;
		HWND best_handle;
		};

	HWND find_main_window(unsigned long process_id);
	BOOL CALLBACK enum_windows_callback(HWND handle, LPARAM lParam);
	BOOL is_main_window(HWND handle);
	bool spawn_prompt(STARTUPINFO* prompt_startupinfo, PROCESS_INFORMATION* prompt_processinfo, HWND* prompt_window);
	void SetExeDirectory();

	void mouse_set_position(int x, int y);
	void mouse_click(int x, int y);
	};

