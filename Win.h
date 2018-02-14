#pragma once
#include <Windows.h>


class Win
	{
	public:

		static struct handle_data
			{
			unsigned long process_id;
			HWND best_handle;
			};

		static HWND find_main_window(unsigned long process_id);
		static BOOL CALLBACK enum_windows_callback(HWND handle, LPARAM lParam);
		static BOOL is_main_window(HWND handle);
		static bool spawn_prompt(STARTUPINFO* prompt_startupinfo, PROCESS_INFORMATION* prompt_processinfo, HWND* prompt_window);
		static void SetExeDirectory();

		static void mouse_set_position(int x, int y);
		static void mouse_click(int x, int y);
	};

