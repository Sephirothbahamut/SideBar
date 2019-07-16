#include "Win.h"

#include <tchar.h>
#include <Shlwapi.h>

namespace Win
	{
	namespace Autorun
		{
		void add(LPCWSTR name)
			{
			TCHAR szPath[MAX_PATH];
			GetModuleFileName(NULL, szPath, MAX_PATH);
			HKEY key;
			RegOpenKey(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", &key);
			RegSetValueEx(key, name, 0, REG_SZ, (LPBYTE)szPath, sizeof(szPath));
			RegCloseKey(key);
			}

		void remove(LPCWSTR name)
			{
			TCHAR szPath[MAX_PATH];
			GetModuleFileName(NULL, szPath, MAX_PATH);
			HKEY key;
			RegOpenKey(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", &key);
			RegDeleteValue(key, name);
			RegCloseKey(key);
			}
		}

	namespace Screen
		{
		int get_min_x() { return GetSystemMetrics(SM_CXMINTRACK); }
		int get_max_x() { return GetSystemMetrics(SM_CXMAXTRACK); }
		int get_min_y() { return GetSystemMetrics(SM_CYMINTRACK); }
		int get_max_y() { return GetSystemMetrics(SM_CYMAXTRACK); }

		int get_width()
			{
			//return GetSystemMetrics(SM_CXVIRTUALSCREEN); //virtual screen (0 is top left)
			return GetSystemMetrics(SM_CXSCREEN); //single monitor
			}

		int get_height()
			{
			//return GetSystemMetrics(SM_CYVIRTUALSCREEN);
			return GetSystemMetrics(SM_CYSCREEN);
			}

		int get_taskbar_height()
			{
			RECT rect;
			HWND taskBar = FindWindow(L"Shell_traywnd", NULL);
			if (taskBar && GetWindowRect(taskBar, &rect))
				{
				return rect.bottom - rect.top;
				}
			}
		}

	HWND find_main_window(unsigned long process_id)
		{
		handle_data data;
		data.process_id = process_id;
		data.best_handle = 0;
		EnumWindows(enum_windows_callback, (LPARAM)&data);
		return data.best_handle;
		}

	BOOL CALLBACK enum_windows_callback(HWND handle, LPARAM lParam)
		{
		handle_data& data = *(handle_data*)lParam;
		unsigned long process_id = 0;
		GetWindowThreadProcessId(handle, &process_id);
		if (data.process_id != process_id || !is_main_window(handle))
			{
			return TRUE;
			}
		data.best_handle = handle;
		return FALSE;
		}

	BOOL is_main_window(HWND handle)
		{
		return GetWindow(handle, GW_OWNER) == (HWND)0 && IsWindowVisible(handle);
		}

	bool spawn_prompt(STARTUPINFO* prompt_startupinfo, PROCESS_INFORMATION* prompt_processinfo, HWND* prompt_window)
		{
		// additional information
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		pi.hProcess;
		// set the size of the structures
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		// start the program up
		CreateProcess(L"C:\\Windows\\System32\\cmd.exe",   // the path
			L"",        // Command line
			NULL,           // Process handle not inheritable
			NULL,           // Thread handle not inheritable
			FALSE,          // Set handle inheritance to FALSE
			0,              // No creation flags
			NULL,           // Use parent's environment block
			NULL,           // Use parent's starting directory 
			&si,            // Pointer to STARTUPINFO structure
			&pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
		);
		Sleep(1000);
		HWND pw = Win::find_main_window(pi.dwProcessId);
		*prompt_startupinfo = si;
		*prompt_processinfo = pi;
		*prompt_window = pw;
		return false;
		}

	TCHAR* GetDirFromPath(TCHAR* dest, size_t destSize)
		{
		if (!dest) return NULL;
		if (MAX_PATH > destSize) return NULL;

		DWORD length = GetModuleFileName(NULL, dest, destSize);
		PathRemoveFileSpec(dest);
		return dest;
		}
	void SetExeDirectory()
		{
		TCHAR dir[_MAX_PATH];
		GetModuleFileName(NULL, dir, _MAX_PATH);
		GetDirFromPath(dir, _MAX_PATH);
		SetCurrentDirectory(dir);
		}

	void mouse_set_position(int x, int y)
		{
		long fScreenWidth = GetSystemMetrics(SM_CXSCREEN) - 1;
		long fScreenHeight = GetSystemMetrics(SM_CYSCREEN) - 1;

		// http://msdn.microsoft.com/en-us/library/ms646260(VS.85).aspx
		// If MOUSEEVENTF_ABSOLUTE value is specified, dx and dy contain normalized absolute coordinates between 0 and 65,535.
		// The event procedure maps these coordinates onto the display surface.
		// Coordinate (0,0) maps onto the upper-left corner of the display surface, (65535,65535) maps onto the lower-right corner.
		float fx = x * (65535.0f / fScreenWidth);
		float fy = y * (65535.0f / fScreenHeight);

		INPUT Input = { 0 };
		Input.type = INPUT_MOUSE;

		Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;

		Input.mi.dx = (long)fx;
		Input.mi.dy = (long)fy;

		SendInput(1, &Input, sizeof(INPUT));
		}

	void mouse_click(int x, int y)
		{
		mouse_set_position(x, y);
		INPUT Input = { 0 };													// Create our input.

		Input.type = INPUT_MOUSE;									// Let input know we are using the mouse.
		Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;							// We are setting left mouse button down.
		SendInput(1, &Input, sizeof(INPUT));								// Send the input.

		ZeroMemory(&Input, sizeof(INPUT));									// Fills a block of memory with zeros.
		Input.type = INPUT_MOUSE;									// Let input know we are using the mouse.
		Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;								// We are setting left mouse button up.
		SendInput(1, &Input, sizeof(INPUT));								// Send the input.

		}
	}