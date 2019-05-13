#include "modules.h"
#include "particles.h"

#include <conio.h>

extern int MAIN_RR;
extern int MAIN_GG;
extern int MAIN_BB;
extern int SEC_RR;
extern int SEC_GG;
extern int SEC_BB;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
	{
	HWND p = FindWindowEx(hwnd, NULL, L"SHELLDLL_DefView", NULL);
	HWND* ret = (HWND*)lParam;

	if (p)
		{
		*ret = FindWindowEx(NULL, hwnd, L"WorkerW", NULL);
		}
	return true;
	}

HWND get_wallpaper_window()
	{
	HWND progman = FindWindow(L"ProgMan", NULL);
	SendMessageTimeout(progman, 0x052C, 0, 0, SMTO_NORMAL, 1000, nullptr);
	HWND wallpaper_hwnd = nullptr;
	EnumWindows(EnumWindowsProc, (LPARAM)&wallpaper_hwnd);
	return wallpaper_hwnd;
	}

float get_mouse_proportional()
	{
	// +1 is rightmost, -1 is leftmost
	float halfscreen = Screen::get_width() / 2;
	float mdist = sf::Mouse::getPosition().x - halfscreen;
	float mdist_proportional = mdist / halfscreen;
	return mdist_proportional;
	}

class moving_sprite : public sf::Drawable
	{
	private:
		float delta_x;
		float y, x;
		sf::Sprite sprite;
	public:
		moving_sprite(sf::Texture &tex, float delta_x, float x, float y) : sprite(tex), x(x), y(y), delta_x(delta_x) {}
		void step()
			{
			sprite.setPosition(x + (-delta_x + get_mouse_proportional() * delta_x), y);
			}
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
			{
			target.draw(sprite, states);
			}
		void scale(float x, float y) { sprite.scale(x, y); }
		void center_x_origin() { sprite.setOrigin(floor(sprite.getGlobalBounds().width / 2), 0); }
		void left_x_origin() { sprite.setOrigin(floor(sprite.getGlobalBounds().width), 0); }

	};

int wallpaper_main()
	{
	sf::RenderWindow window(get_wallpaper_window());
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	//wallpaper beg

	sf::Texture bg_tex;
	if (!bg_tex.loadFromFile("textures/bg3.png"))
		{
		std::cout << "Wallpaper image failed to load. Wallpaper disabled." << std::endl;
		return 0;
		}
	moving_sprite bg(bg_tex, 8, -12, 0); 
	if (true)
		{//scale to screen
		float sw = Screen::get_width()*2;
		float sh = Screen::get_height();
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
	sf::Texture textures[3];
	if (!textures[0].loadFromFile("textures/0.png"))
		{
		std::cout << "Wallpaper foreground image failed to load. Wallpaper disabled." << std::endl;
		return 0;
		}
	if (!textures[1].loadFromFile("textures/1.png"))
		{
		std::cout << "Wallpaper foreground image failed to load. Wallpaper disabled." << std::endl;
		return 0;
		}
	if (!textures[2].loadFromFile("textures/2.png"))
		{
		std::cout << "Wallpaper foreground image failed to load. Wallpaper disabled." << std::endl;
		return 0;
		}

	moving_sprite moving_sprites[3] =
		{
		moving_sprite(textures[0], 64, -float(textures[0].getSize().x / 8.f), Screen::get_height() - float(textures[0].getSize().y + 64)),
		moving_sprite(textures[1], 50, -float(textures[0].getSize().x / 8.f) + (textures[0].getSize().x / 1.8f), Screen::get_height() - float(textures[0].getSize().y + 180)),
		moving_sprite(textures[2], 20, Screen::get_width() - 400, 0)
		};
	/*if (true)
		{//scale to screen
		float sw = Screen::get_width() * 2 / 3;
		float sh = Screen::get_height();
		float sr = sw / sh;
		float iw = fg.getGlobalBounds().width;
		float ih = fg.getGlobalBounds().height;
		float ir = iw / ih;

		float scale = (sr > ir) ? (sw / iw) : (sh / ih);
		fg.scale(scale, scale);
		}*/
	//moving_sprite end

	while (window.isOpen())
		{
		sf::Event event;
		while (window.pollEvent(event))
			{
			// "close requested" event: we close the window
			switch (event.type)
				{
				case sf::Event::Closed: window.close(); break;
				}
			}

		bg.step();
		moving_sprites[2].step();
		moving_sprites[1].step();
		moving_sprites[0].step();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right) || sf::Mouse::isButtonPressed(sf::Mouse::Middle))
			{
			
			}
		//draw

		window.clear(sf::Color(SEC_RR, SEC_GG, SEC_BB, 200));
		window.draw(bg);
		window.draw(moving_sprites[2]);
		window.draw(moving_sprites[1]);
		window.draw(moving_sprites[0]);
		window.display();
		}

	return(0);
	}