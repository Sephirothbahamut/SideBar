#pragma once

#include <Windows.h>

class autorun
	{
	private:
	public:
		autorun();
		~autorun();
		static void add(LPCWSTR name);
		static void remove(LPCWSTR name);
	};

