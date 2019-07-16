#include "modules.h"
#include "settings.h"
extern Settings settings;


int prompt_main()
	{
	//create terminal window beg
	STARTUPINFO prompt_startupinfo;
	PROCESS_INFORMATION prompt_processinfo;
	HWND prompt_window;

	Win::spawn_prompt(&prompt_startupinfo, &prompt_processinfo, &prompt_window);
	//always on bottom
	SetWindowPos(prompt_window, HWND_TOPMOST, 0, -settings.prompt_height + 2, Win::Screen::get_width(), settings.prompt_height, SWP_SHOWWINDOW);
	SetWindowLong(prompt_window, GWL_EXSTYLE, GetWindowLong(prompt_window, GWL_EXSTYLE) | WS_EX_TOOLWINDOW);
	SetWindowLong(prompt_window, GWL_STYLE, WS_POPUP | WS_VISIBLE);

	//create terminal window end

	bool outside = false;
	bool exiting = false;
	while (IsWindow(prompt_window))
		{
		//Console move beg
		int my = sf::Mouse::getPosition().y;
		int mx = sf::Mouse::getPosition().x;
		RECT rect;
		GetWindowRect(prompt_window, &rect);
		int wy = rect.bottom;
		if ((my <= wy + 1) and not exiting)
			{
			if ((not outside) or (mx < 32))
				{
				if (wy < settings.prompt_height)
					{
					wy += settings.window_speed * 4;
					if (wy > settings.prompt_height)
						{
						wy = settings.prompt_height;
						}
					SetWindowPos(prompt_window, 0, 0, wy - settings.prompt_height, 0, 0, SWP_NOSIZE);
					if (outside)
						{
						outside = false;
						Win::mouse_click(1, 1);
						}
					}
				}
			}
		else if (wy > 0)
			{
			wy -= settings.window_speed * 4;
			exiting = true;
			if (wy <= 0)
				{
				wy = 0;
				outside = true;
				exiting = false;
				}
			SetWindowPos(prompt_window, 0, 0, wy - settings.prompt_height, 0, 0, SWP_NOSIZE);
			}
		//Console move end
		Sleep(1000 / 60);
		}
	// Close prompt process and thread handles.
	CloseHandle(prompt_processinfo.hProcess);
	CloseHandle(prompt_processinfo.hThread);
	return(0);
	}