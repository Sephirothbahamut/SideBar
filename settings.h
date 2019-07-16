#pragma once
#include "Win.h"
#include "tinyxml2.h"
#include <tuple>
#include <list>
#include <string>
namespace xml = tinyxml2;

class Settings
	{
	public:
		struct sidebar_element
			{
			enum TYPE { button, clock };
			TYPE type;
			std::string text;
			std::string action;
			sidebar_element(std::string text, std::string action);
			sidebar_element(TYPE type);
			};
		struct wallpaper_element
			{
			enum TYPE { picture };
			TYPE type;
			std::string path;
			float x, y, x_offset, y_offset;
			wallpaper_element(std::string path, float x, float y, float x_offset, float y_offset);
			};

		int window_width;
		int window_height;
		int window_min_x;
		int window_speed;
		int vertical_spacing;
		int part_amount;
		int main_rr;
		int main_gg;
		int main_bb;
		int sec_rr;
		int sec_gg;
		int sec_bb;
		bool main_stay; //bool
		bool enable_bottom_bar; //bool
		bool enable_prompt; //bool
		bool enable_wallpaper; //bool
		int prompt_height;

		std::list<sidebar_element> sidebar_elements;
		std::list<wallpaper_element> wallpaper_elements;

		void read();
		Settings();
		~Settings();
	};

