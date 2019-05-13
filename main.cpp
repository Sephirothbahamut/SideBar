#include "modules.h"
#include <thread>

#if defined(UNICODE) || defined(_UNICODE)
#define tcout std::wcout
#else
#define tcout std::cout
#endif

int WINDOW_WIDTH;
int WINDOW_HEIGHT;
int WINDOW_MIN_X;
int WINDOW_SPEED;
int VERTICAL_SPACING;
int PART_AMOUNT;
int MAIN_RR;
int MAIN_GG;
int MAIN_BB;
int SEC_RR;
int SEC_GG;
int SEC_BB;
int MAIN_STAY; //bool
int BOTTOM_BAR; //bool
int PROMPT; //bool
int WALLPAPER; //bool

sf::Texture pt_texture;

int PROMPT_HEIGHT;

//program
int main()
	{
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


	//first inits
	WINDOW_WIDTH = 160;
	WINDOW_HEIGHT = Screen::get_height() - Screen::get_taskbar_height();
	WINDOW_MIN_X = Screen::get_width() - WINDOW_WIDTH;
	WINDOW_SPEED = 6;
	VERTICAL_SPACING = 8;
	PART_AMOUNT = 8;
	MAIN_RR = 0;
	MAIN_GG = 240;
	MAIN_BB = 255;
	SEC_RR = 0;
	SEC_GG = 0;
	SEC_BB = 50;

	BOTTOM_BAR = false;
	PROMPT = false;
	WALLPAPER = true;

	MAIN_STAY = false;
	PROMPT_HEIGHT = Screen::get_height() - Screen::get_taskbar_height() + 2;

	//Read settings beg
	if (true)
		{
		xml::XMLDocument settings;
		xml::XMLError res = settings.LoadFile("files/settings.xml");
		xml::XMLNode* root = settings.FirstChild();
		//colors
		if (true)
			{

			xml::XMLNode* colors = root->FirstChildElement("colors");
			//main
			xml::XMLElement* main_color = colors->FirstChildElement("main")->FirstChildElement("color");
			main_color->QueryIntAttribute("rr", &MAIN_RR);
			main_color->QueryIntAttribute("gg", &MAIN_GG);
			main_color->QueryIntAttribute("bb", &MAIN_BB);
			//sec
			xml::XMLElement* sec_color = colors->FirstChildElement("sec")->FirstChildElement("color");
			sec_color->QueryIntAttribute("rr", &SEC_RR);
			sec_color->QueryIntAttribute("gg", &SEC_GG);
			sec_color->QueryIntAttribute("bb", &SEC_BB);
			}
		//other
		if (true)
			{
			xml::XMLNode* other = root->FirstChildElement("other");
			//part
			xml::XMLElement* particles = other->FirstChildElement("particles");
			particles->QueryIntAttribute("amount", &PART_AMOUNT);
			//win spd
			xml::XMLElement* win_speed = other->FirstChildElement("win_speed");
			win_speed->QueryIntAttribute("value", &WINDOW_SPEED);
			//vert spacing
			xml::XMLElement* vertical_spacing = other->FirstChildElement("vertical_spacing");
			vertical_spacing->QueryIntAttribute("value", &VERTICAL_SPACING);
			//bottom bar
			xml::XMLElement* bottom_bar = other->FirstChildElement("bottom_bar");
			bottom_bar->QueryIntAttribute("enabled", &BOTTOM_BAR);
			//prompt bar
			xml::XMLElement* prompt = other->FirstChildElement("prompt");
			prompt->QueryIntAttribute("enabled", &PROMPT);
			//wallpaper
			xml::XMLElement* wallpaper = other->FirstChildElement("wallpaper");
			wallpaper->QueryIntAttribute("enabled", &PROMPT);
			//stay
			xml::XMLElement* stay = other->FirstChildElement("stay");
			stay->QueryIntAttribute("enabled", &MAIN_STAY);
			}
		}

	//create particle texture
	if (not pt_texture.loadFromFile("textures/particles/s_particle.png"))
		{/*handle error*/
		}
	pt_texture.setSmooth(true);
	//Read settings end

	std::thread THREAD_PROMPT;
	std::thread THREAD_BOTTOM_BAR;
	std::thread THREAD_WALLPAPER;


	//create bottom bar
	if (BOTTOM_BAR)
		{
		THREAD_BOTTOM_BAR = std::thread(bottom_main);
		}
	//create prompt
	if (PROMPT)
		{
		THREAD_PROMPT = std::thread(prompt_main);
		}
	//create wallpaper
	if (WALLPAPER)
		{
		THREAD_WALLPAPER = std::thread(wallpaper_main);
		}

	bar_main();

	THREAD_BOTTOM_BAR.join();
	THREAD_PROMPT.join();
	THREAD_WALLPAPER.join();

	return(0);
	}
