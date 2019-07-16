#include "modules.h"
#include <thread>
#include "settings.h"

#if defined(UNICODE) || defined(_UNICODE)
#define tcout std::wcout
#else
#define tcout std::cout
#endif

sf::Texture pt_texture;
Settings settings;

//program
int main()
	{
	settings.read();
	

#ifdef _DEBUG
	TCHAR NPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, NPath);
	std::wcout << "OPENED FROM:     " << NPath << std::endl;
#endif
	Win::SetExeDirectory();
#ifdef _DEBUG
	DWORD b = GetCurrentDirectory(MAX_PATH, NPath);
	std::wcout << "NOW CURRENT DIR: " << NPath << std::endl << std::flush;
#endif

	//create particle texture
	if (not pt_texture.loadFromFile("textures/particles/s_particle.png"))
		{/*handle error*/
		}
	pt_texture.setSmooth(true);

	std::thread THREAD_PROMPT;
	std::thread THREAD_BOTTOM_BAR;
	std::thread THREAD_WALLPAPER;
	//std::thread THREAD_MOUSE_EFFECTS;


	//create bottom bar
	if (settings.enable_bottom_bar)
		{
		THREAD_BOTTOM_BAR = std::thread(bottom_main);
		}
	//create prompt
	if (settings.enable_prompt)
		{
		THREAD_PROMPT = std::thread(prompt_main);
		}
	//create wallpaper
	if (settings.enable_wallpaper)
		{
		THREAD_WALLPAPER = std::thread(wallpaper_main);
		}
	//THREAD_MOUSE_EFFECTS = std::thread(mouse_effects_main);

	bar_main();

	THREAD_BOTTOM_BAR.join();
	THREAD_PROMPT.join();
	THREAD_WALLPAPER.join();
	//THREAD_MOUSE_EFFECTS.join();

	return(0);
	}
