#include "autorun.h"

void autorun::add(LPCWSTR name)
	{
	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);
	HKEY key;
	RegOpenKey(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", &key);
	RegSetValueEx(key, name, 0, REG_SZ, (LPBYTE)szPath, sizeof(szPath));
	RegCloseKey(key);
	}

void autorun::remove(LPCWSTR name)
	{
	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);
	HKEY key;
	RegOpenKey(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", &key);
	RegDeleteValue(key, name);
	RegCloseKey(key);
	}

autorun::autorun()
	{}


autorun::~autorun()
	{}