#include "modules.h"
#include "particles.h"
#include <conio.h>
/*
extern int MAIN_RR;
extern int MAIN_GG;
extern int MAIN_BB;
extern int SEC_RR;
extern int SEC_GG;
extern int SEC_BB;

extern int PART_AMOUNT;
extern sf::Texture pt_texture;


extern BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);

extern HWND get_wallpaper_window();

int mouse_effects_main()
	{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;
	sf::RenderWindow window(get_wallpaper_window(), settings);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	//Particle system beg
	sf::Sprite pt_sprite_back(pt_texture);
	pt_sprite_back.setColor(sf::Color(SEC_RR, SEC_GG, SEC_BB, 76.5));
	PartSystem ps_back(pt_sprite_back, 90, 10, 0.5, 0.3, 4, 0.4, 420, 10, PART_AMOUNT / 2, 1, sf::FloatRect(0, -16, Win::Screen::get_width(), 0));

	sf::Sprite pt_sprite(pt_texture);
	pt_sprite.setColor(sf::Color(MAIN_RR, MAIN_GG, MAIN_BB, 76.5));
	PartSystem ps(pt_sprite, 90, 15, 2.0, 0.8, 1.2, 0.4, 280, 20, PART_AMOUNT, 1, sf::FloatRect(0, -16, Win::Screen::get_width(), 0));
	//Particle system end


	while (window.isOpen())
		{
		sf::Event event;
		while (window.pollEvent(event))
			{
			// "close requested" event: we close the window
			switch (event.type) { case sf::Event::Closed: window.close(); break; }
			}

		ps.step();
		ps_back.step();*/
		/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
		ps.position_push(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y, 1000);
		ps_back.position_push(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y, 1000);
		}*/
/*
		window.clear(sf::Color(SEC_RR, SEC_GG, SEC_BB, 0));
		ps_back.draw(window);
		ps.draw(window);
		window.display();
		}

	return(0);
	}*/