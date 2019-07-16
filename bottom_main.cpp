#include "modules.h"

extern Settings settings;
extern sf::Texture pt_texture;

int bottom_main()
	{

	sf::RenderWindow window(sf::VideoMode(Win::Screen::get_width(), Win::Screen::get_taskbar_height()), "BottomBar", sf::Style::None);
	window.setPosition(sf::Vector2i(0, Win::Screen::get_height() - Win::Screen::get_taskbar_height()));
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	HWND windows_window = window.getSystemHandle();
	//always on bottom
	SetWindowPos(windows_window, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	//do not show in toolbar 
	SetWindowLong(windows_window, GWL_EXSTYLE, WS_EX_TOOLWINDOW);
	//Transparent window
	MARGINS margins;
	margins.cxLeftWidth = -1;
	SetWindowLong(windows_window, GWL_STYLE, WS_POPUP | WS_VISIBLE);
	DwmExtendFrameIntoClientArea(window.getSystemHandle(), &margins);

	//Particle system beg

	sf::Sprite pt_sprite(pt_texture);
	pt_sprite.setColor(sf::Color(settings.main_rr, settings.main_gg, settings.main_bb, 76.5));

	PartSystem ps = PartSystem(pt_sprite, 180, 8, 1.8, 0.6, 0.8, 0.2, 512, 64, 2, 1, sf::FloatRect(Win::Screen::get_width() + 16, -16, 0, 32 + Win::Screen::get_taskbar_height()));

	//Particle system end
	while (window.isOpen())
		{
		sf::Event event;
		while (window.pollEvent(event))
			{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
			}
		ps.step();

		window.clear(sf::Color(settings.sec_rr, settings.sec_gg, settings.sec_bb, 200));

		ps.draw(window);
		window.display();
		}

	return(0);
	}