#include "settings.h"
#include <iostream>

void Settings::read()
	{
	//first inits
	window_width = 160;
	window_height = Win::Screen::get_height() - Win::Screen::get_taskbar_height();
	window_min_x = Win::Screen::get_width() - window_width;
	window_speed = 6;
	vertical_spacing = 8;
	part_amount = 8;
	main_rr = 0;
	main_gg = 240;
	main_bb = 255;
	sec_rr = 0;
	sec_gg = 0;
	sec_bb = 50;
	main_stay = false;
	enable_bottom_bar = false;
	enable_prompt = false;
	enable_wallpaper = true;
	prompt_height = Win::Screen::get_height() - Win::Screen::get_taskbar_height() + 2;

	//Read settings
	if (true)
		{
		tinyxml2::XMLDocument settings;
		xml::XMLError res = settings.LoadFile("files/settings.xml");
		xml::XMLNode* _root = settings.FirstChild();
		//colors
		if (true)
			{

			xml::XMLNode* _colors = _root->FirstChildElement("colors");
			//main
			xml::XMLElement* _main_color = _colors->FirstChildElement("main")->FirstChildElement("color");
			_main_color->QueryIntAttribute("rr", &main_rr);
			_main_color->QueryIntAttribute("gg", &main_gg);
			_main_color->QueryIntAttribute("bb", &main_bb);
			//sec
			xml::XMLElement* _sec_color = _colors->FirstChildElement("sec")->FirstChildElement("color");
			_sec_color->QueryIntAttribute("rr", &sec_rr);
			_sec_color->QueryIntAttribute("gg", &sec_gg);
			_sec_color->QueryIntAttribute("bb", &sec_bb);
			}
		//other
		if (true)
			{
			int tmp;
			xml::XMLNode* _other = _root->FirstChildElement("other");
			//part
			xml::XMLElement* _particles = _other->FirstChildElement("particles");
			_particles->QueryIntAttribute("amount", &part_amount);
			//win spd
			xml::XMLElement* _win_speed = _other->FirstChildElement("win_speed");
			_win_speed->QueryIntAttribute("value", &window_speed);
			//vert spacing
			xml::XMLElement* _vertical_spacing = _other->FirstChildElement("vertical_spacing");
			_vertical_spacing->QueryIntAttribute("value", &vertical_spacing);
			//bottom bar
			xml::XMLElement* _bottom_bar = _other->FirstChildElement("bottom_bar");
			_bottom_bar->QueryIntAttribute("enabled", &tmp); enable_bottom_bar = tmp;
			//prompt bar
			xml::XMLElement* _prompt = _other->FirstChildElement("prompt");
			_prompt->QueryIntAttribute("enabled", &tmp); enable_prompt = tmp;
			//wallpaper
			xml::XMLElement* _wallpaper = _other->FirstChildElement("wallpaper");
			_wallpaper->QueryIntAttribute("enabled", &tmp); enable_wallpaper = tmp;
			//stay
			xml::XMLElement* _stay = _other->FirstChildElement("stay");
			_stay->QueryIntAttribute("enabled", &tmp); main_stay = tmp;
			}
		// SideBar
		if (true)
			{
			xml::XMLNode* _sidebar = _root->FirstChildElement("sidebar");
			for (xml::XMLElement* e = _sidebar->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
				{

				if (std::string(e->Name()) == "button") { sidebar_elements.push_back({ e->Attribute("text"), e->Attribute("action") }); }
				else if (std::string(e->Name()) == "clock") { sidebar_elements.push_back({ sidebar_element::TYPE::clock }); }
				}
			}
		// Wallpaper
		if (true)
			{
			xml::XMLNode* _wallpaper = _root->FirstChildElement("wallpaper");
			for (xml::XMLElement* e = _wallpaper->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
				{
				wallpaper_elements.push_back({ e->Attribute("path"), e->FloatAttribute("x"), e->FloatAttribute("y"), e->FloatAttribute("x_offset"), e->FloatAttribute("y_offset") });
				std::cout << "path: " << e->Attribute("path") << "x_offset: " << e->FloatAttribute("x_offset") << ", y_offset: " << e->FloatAttribute("y_offset") << std::endl;

				}
			}
		}
	}

Settings::Settings()
	{
	}


Settings::~Settings()
	{
	}

Settings::sidebar_element::sidebar_element(std::string text, std::string action) : type(TYPE::button), text(text), action(action) {}
Settings::sidebar_element::sidebar_element(TYPE type) : type(type) {}

Settings::wallpaper_element::wallpaper_element(std::string path, float x, float y, float x_offset, float y_offset)
	: path(path), x(x), y(y), x_offset(x_offset), y_offset(y_offset), type(TYPE::picture) {}
