#pragma once
#include <windows.h>

class Screen
	{
	public:
		Screen();
		~Screen();

		static int get_width();
		static int get_height();
		static int get_taskbar_height();

	};

