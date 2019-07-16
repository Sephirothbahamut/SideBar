#include "modules.h"
#include "PartSystem.h"
#include "settings.h"
#include <conio.h>
#include <list>

extern Settings settings;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
	{
	HWND p = FindWindowEx(hwnd, NULL, L"SHELLDLL_DefView", NULL);
	HWND* ret = (HWND*)lParam;

	if (p)
		{
		// Gets the WorkerW Window after the current one.
		*ret = FindWindowEx(NULL, hwnd, L"WorkerW", NULL);
		}
	return true;
	}

HWND get_wallpaper_window()
	{
	// Fetch the Progman window
	HWND progman = FindWindow(L"ProgMan", NULL);
	// Send 0x052C to Progman. This message directs Progman to spawn a 
	// WorkerW behind the desktop icons. If it is already there, nothing 
	// happens.
	SendMessageTimeout(progman, 0x052C, 0, 0, SMTO_NORMAL, 1000, nullptr);
	// We enumerate all Windows, until we find one, that has the SHELLDLL_DefView 
	// as a child. 
	// If we found that window, we take its next sibling and assign it to workerw.
	HWND wallpaper_hwnd = nullptr;
	EnumWindows(EnumWindowsProc, (LPARAM)&wallpaper_hwnd);
	return wallpaper_hwnd;
	}

float get_mouse_proportional()
	{
	// +1 is rightmost, -1 is leftmost
	float halfscreen = Win::Screen::get_width() / 2;
	float mdist = sf::Mouse::getPosition().x - halfscreen;
	float mdist_proportional = mdist / halfscreen;
	return mdist_proportional;
	}

class moving_sprite : public sf::Drawable
	{
	private:
		float delta_x, delta_y;
		float y, x;
		sf::Sprite sprite;
	public:
		moving_sprite(sf::Texture &tex, float x, float y, float delta_x, float delta_y) : sprite(tex), x(x), y(y), delta_x(delta_x), delta_y(delta_y) { sprite.setPosition(x, y); }

		void step() 
			{
			sprite.setPosition(x + (-delta_x + get_mouse_proportional() * delta_x), y);
			}

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(sprite, states); }

		void scale(float x, float y) { sprite.scale(x, y); }
		void center_x_origin() { sprite.setOrigin(floor(sprite.getGlobalBounds().width / 2), 0); }
		void left_x_origin() { sprite.setOrigin(floor(sprite.getGlobalBounds().width), 0); }

	};

int wallpaper_main()
	{
	sf::ContextSettings csettings;
	csettings.antialiasingLevel = 16;
	sf::RenderWindow window(get_wallpaper_window(), csettings);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	
	std::list<sf::Texture> textures;
	std::list<moving_sprite> sprites;
	for (auto i : settings.wallpaper_elements)
		{
		textures.push_back({});
		if (!textures.back().loadFromFile(i.path))
			{
			std::cout << "Wallpaper images failed to load. Wallpaper disabled." << std::endl;
			return 0;
			}
		textures.back().setSmooth(true);
		}
	auto it = textures.begin();
	for (auto i : settings.wallpaper_elements) 
		{
		sprites.push_back({ *it, i.x, i.y, i.x_offset, i.y_offset });
		it++;
		}

	//wallpaper beg
	/*
	sf::Texture bg_tex;
	if (!bg_tex.loadFromFile("textures/bg3.png"))
		{
		std::cout << "Wallpaper image failed to load. Wallpaper disabled." << std::endl;
		return 0;
		}
	bg_tex.setSmooth(true);

	moving_sprite bg(bg_tex, -12, 0, 8, 0);
	if (true)
		{//scale to screen
		float sw = Win::Screen::get_width() * 2;
		float sh = Win::Screen::get_height();
		float sr = sw / sh;
		float iw = bg_tex.getSize().x;
		float ih = bg_tex.getSize().y;
		float ir = iw / ih;

		float scale = (sr > ir) ? (sw / iw) : (sh / ih);
		//bg.scale(scale, scale);
		//bg.left_x_origin();
		}
	//wallpaper end

	//moving_sprites beg
	sf::Texture textures3[3];
	if (!textures3[0].loadFromFile("textures/0.png"))
		{
		std::cout << "Wallpaper foreground image failed to load. Wallpaper disabled." << std::endl;
		return 0;
		}
	if (!textures3[1].loadFromFile("textures/1.png"))
		{
		std::cout << "Wallpaper foreground image failed to load. Wallpaper disabled." << std::endl;
		return 0;
		}
	if (!textures3[2].loadFromFile("textures/2.png"))
		{
		std::cout << "Wallpaper foreground image failed to load. Wallpaper disabled." << std::endl;
		return 0;
		}
	textures3[0].setSmooth(true);
	textures3[1].setSmooth(true);
	textures3[2].setSmooth(true);

	moving_sprite moving_sprites[3] =
		{
		moving_sprite(textures3[0], -float(textures3[0].getSize().x / 8.f), Win::Screen::get_height() - float(textures3[0].getSize().y + 64), 64, 0),
		moving_sprite(textures3[1], -float(textures3[0].getSize().x / 8.f) + (textures3[0].getSize().x / 1.8f), Win::Screen::get_height() - float(textures3[0].getSize().y + 180), 50, 0),
		moving_sprite(textures3[2], Win::Screen::get_width() - 400, 0, 20, 0)
		};
	/*if (true)
	{//scale to screen
	float sw = Win::Screen::get_width() * 2 / 3;
	float sh = Win::Screen::get_height();
	float sr = sw / sh;
	float iw = fg.getGlobalBounds().width;
	float ih = fg.getGlobalBounds().height;
	float ir = iw / ih;

	float scale = (sr > ir) ? (sw / iw) : (sh / ih);
	fg.scale(scale, scale);
	}*/
	//moving_sprite end
	
	sf::Vector2i prev = sf::Mouse::getPosition();
	prev.x += 1;	//draws first frame even if mouse didn't move

	while (window.isOpen())
		{
		sf::Event event;
		while (window.pollEvent(event))
			{
			// "close requested" event: we close the window
			switch (event.type) { case sf::Event::Closed: window.close(); break; }
			}

		if (true || prev != sf::Mouse::getPosition())
			{
			prev = sf::Mouse::getPosition();
			//bg.step();
			//moving_sprites[0].step();
			//moving_sprites[1].step();
			//moving_sprites[2].step();
			//for(auto s : sprites)
			for (auto s = sprites.begin(); s != sprites.end(); s++) 
				{ s->step(); }
			window.clear(sf::Color(settings.sec_rr, settings.sec_gg, settings.sec_bb, 200));
			//window.draw(bg);
			//window.draw(moving_sprites[0]);
			//window.draw(moving_sprites[1]);
			//window.draw(moving_sprites[2]);
			for (auto s : sprites) { window.draw(s); }
			window.display();
			}
		else { Sleep(16); }
		}

	return(0);
	}