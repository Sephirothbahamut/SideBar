#include "modules.h"

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
extern int WINDOW_MIN_X;
extern int WINDOW_SPEED;

extern sf::Texture pt_texture;
extern sf::Sprite pt_sprite;

extern int PROMPT_HEIGHT;
extern bool TEST;

int prompt_main()
	{

	//create terminal window beg
	STARTUPINFO prompt_startupinfo;
	PROCESS_INFORMATION prompt_processinfo;
	HWND prompt_window;

	Win::spawn_prompt(&prompt_startupinfo, &prompt_processinfo, &prompt_window);
	//always on bottom
	SetWindowPos(prompt_window, HWND_TOPMOST, 0, -PROMPT_HEIGHT + 2, Screen::get_width(), PROMPT_HEIGHT, SWP_SHOWWINDOW);
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
				if (wy < PROMPT_HEIGHT)
					{
					wy += WINDOW_SPEED * 4;
					if (wy > PROMPT_HEIGHT)
						{
						wy = PROMPT_HEIGHT;
						}
					SetWindowPos(prompt_window, 0, 0, wy - PROMPT_HEIGHT, 0, 0, SWP_NOSIZE);
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
			wy -= WINDOW_SPEED * 4;
			exiting = true;
			if (wy <= 0)
				{
				wy = 0;
				outside = true;
				exiting = false;
				}
			SetWindowPos(prompt_window, 0, 0, wy - PROMPT_HEIGHT, 0, 0, SWP_NOSIZE);
			}
		//Console move end
		Sleep(1000 / 60);
		}
	// Close prompt process and thread handles.
	CloseHandle(prompt_processinfo.hProcess);
	CloseHandle(prompt_processinfo.hThread);
	std::cout << "Terminal subprocess closed" << std::endl;
	return(0);
	}