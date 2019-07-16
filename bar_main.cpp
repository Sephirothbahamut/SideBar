#include "modules.h"

extern sf::Texture pt_texture;

extern Settings settings;

int bar_main()
	{
	int screen_max_x = Win::Screen::get_width();
	//create window
	sf::RenderWindow window(sf::VideoMode(settings.window_width, settings.window_height), "SideBar", sf::Style::None);
	window.setPosition({ (screen_max_x - settings.window_width), 0 });

	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	HWND windows_window = window.getSystemHandle();
	//always on top
	SetWindowPos(windows_window, HWND_TOPMOST, settings.window_min_x, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	//do not show in toolbar 
	SetWindowLong(windows_window, GWL_EXSTYLE, WS_EX_TOOLWINDOW);

	//Transparent window
	MARGINS margins;
	margins.cxLeftWidth = -1;
	SetWindowLong(windows_window, GWL_STYLE, WS_POPUP | WS_VISIBLE);
	DwmExtendFrameIntoClientArea(window.getSystemHandle(), &margins);
	//End transparent window

	//Background beg
	sf::Texture bg_texture;
	if (not bg_texture.loadFromFile("textures/t_bg.png"))
		{/*handle error*/
		}
	sf::Sprite bg_sprite(bg_texture);
	bg_sprite.setScale(1, settings.window_height);
	bg_sprite.setColor(sf::Color(settings.sec_rr, settings.sec_gg, settings.sec_bb, 255));
	//Background end

	//Settings beg
	//sf::Texture se_texture;
	//if (not se_texture.loadFromFile("textures/settings.png"))
	//	{/*handle error*/
	//	}
	//sf::Sprite se_sprite(se_texture);
	//se_sprite.setScale(1, 1);
	//se_sprite.setPosition(WINDOW_WIDTH - 32, 0);
	//se_sprite.setColor(sf::Color(255, 255, 255, 255));
	//Settings end

	//Particle system beg
	sf::Sprite pt_sprite(pt_texture);
	pt_sprite.setColor(sf::Color(settings.main_rr, settings.main_gg, settings.main_bb, 76.5));
	PartSystem ps(pt_sprite, 180, 15, 1.2, 0.4, 0.8, 0.2, 90, 15, settings.part_amount, 1, sf::FloatRect(settings.window_width + 16, 0, 0, settings.window_height));
	
	//Particle system end

	//Elements beg
	std::vector<SbItem*> items;

	sf::Texture btn_texture;
	sf::Font btn_font;
	
	if (not btn_texture.loadFromFile("textures/t_button.png"))
		{/*handle error*/
		}
	btn_texture.setSmooth(true);
	if (not btn_font.loadFromFile("fonts/times.ttf"))
		{/*handle herror*/
		}
	usi yy = settings.vertical_spacing;
	//Buttons beg

	for (auto i : settings.sidebar_elements)
		{

		switch(i.type)
			{
			case Settings::sidebar_element::TYPE::clock:
				items.push_back(new BarnackClock((settings.window_width / 2), yy, settings.main_rr, settings.main_gg, settings.main_bb));
				break;
			case Settings::sidebar_element::TYPE::button:
				items.push_back(new BarButton(i.text, i.action, 96, yy, btn_texture, btn_font, sf::Color(settings.main_rr, settings.main_gg, settings.main_bb, 255)));
				break;
			}

		yy += items.back()->collision.height + settings.vertical_spacing;
		}
	//Buttons end
	//Elements end

	bool outside = false;
	bool exiting = false;
	sf::Vector2f mouse_pos(0, 0);
	sf::Vector2f mouse_pos_previous(0, 0);


	while (window.isOpen())
		{
		//std::cout << window.getPosition().x << std::endl;

		//Window move beg
		if(not settings.main_stay)
			{
			int mx = sf::Mouse::getPosition().x;
			int my = sf::Mouse::getPosition().y;
			int wx = window.getPosition().x;
			if ((mx >= wx - 1) and not exiting)
				{
				if ((not outside) or (my > 32))
					{
					if (wx > settings.window_min_x)
						{
						wx -= settings.window_speed;
						if (wx < settings.window_min_x)
							{
							wx = settings.window_min_x;
							}
						}
					outside = false;
					window.setFramerateLimit(60);
					}
				}
			else if (wx < screen_max_x)
				{
				wx += settings.window_speed;
				exiting = true;
				if (wx >= screen_max_x)
					{
					wx = screen_max_x;
					outside = true;
					exiting = false;
					window.setFramerateLimit(5);
					}
				}
			
			window.setPosition(sf::Vector2i(wx, 0));
			}
		//Window move end

		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
			{
			// "close requested" event: we close the window
			mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			if (event.type == sf::Event::Closed)
				{
				window.close();
				}
			else if (event.type == sf::Event::MouseMoved)
				{
				for (auto i : items)
					{
					i->mouse_moved(mouse_pos_previous, mouse_pos);
					}
				}
			else if (event.type == sf::Event::MouseButtonPressed)
				{
				for (auto i : items)
					{
					i->mouse_pressed(mouse_pos);
					}
				}
			else if (event.type == sf::Event::MouseButtonReleased)
				{
				for (auto i : items)
					{
					i->mouse_released(mouse_pos);
					}
				}
			}
		window.clear(sf::Color::Transparent);
		if (not outside)
			{
			bg_sprite.setColor(sf::Color(settings.sec_rr, settings.sec_gg, settings.sec_bb));
			pt_sprite.setColor(sf::Color(settings.sec_rr, settings.sec_gg, settings.sec_bb));

			//step
			ps.step();
			for (auto i : items)
				{
				i->step();
				}
			mouse_pos_previous = mouse_pos;

			//draw
			//window.clear(sf::Color(000, 000, 050, 255));
			window.draw(bg_sprite);

			ps.draw(window);
			//window.draw(se_sprite);
			for (auto i : items)
				{
				window.draw(*i);
				}
			}
		window.display();
		}

	auto i = items.begin();
	while(i != items.end())
		{
		delete *i;
		i = items.begin();
		}

	return(0);
	}