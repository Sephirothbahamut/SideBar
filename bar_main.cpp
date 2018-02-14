#include "modules.h"

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
extern int WINDOW_MIN_X;
extern int WINDOW_SPEED;
extern int VERTICAL_SPACING;
extern int PART_AMOUNT;
extern int MAIN_RR;
extern int MAIN_GG;
extern int MAIN_BB;
extern int SEC_RR;
extern int SEC_GG;
extern int SEC_BB;
extern int MAIN_STAY; //bool

extern sf::Texture pt_texture;
extern sf::Sprite pt_sprite;

extern int PROMPT_HEIGHT;
extern bool TEST;

int bar_main()
	{
	//create window
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SideBar", sf::Style::None);
	window.setPosition({ (Screen::get_width() - WINDOW_WIDTH), 0 });
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	HWND windows_window = window.getSystemHandle();
	//always on top
	SetWindowPos(windows_window, HWND_TOPMOST, WINDOW_MIN_X, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
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
	bg_sprite.setScale(1, WINDOW_HEIGHT);
	bg_sprite.setColor(sf::Color(SEC_RR, SEC_GG, SEC_BB, 255));
	//Background end

	//Particle system beg
	sf::Sprite pt_sprite(pt_texture);
	pt_sprite.setColor(sf::Color(MAIN_RR, MAIN_GG, MAIN_BB, 76.5));

	PartSystem ps = PartSystem(pt_sprite, 180, 15, 1.2, 0.4, 0.8, 0.2, 90, 15, PART_AMOUNT, 1, sf::FloatRect(WINDOW_WIDTH + 16, 0, 0, WINDOW_HEIGHT));
	//Particle system end
	//Elements beg
	BarnackClock clock = BarnackClock((WINDOW_WIDTH / 2), 84, MAIN_RR, MAIN_GG, MAIN_BB);
	std::vector<BarButton> buttons = std::vector<BarButton>();

	//Read buttons beg
	sf::Texture btn_texture;
	sf::Font btn_font;
	{
	if (not btn_texture.loadFromFile("textures/t_button.png"))
		{/*handle error*/
		}
	btn_texture.setSmooth(true);
	if (not btn_font.loadFromFile("fonts/times.ttf"))
		{/*handle herror*/
		}
	xml::XMLDocument file;
	xml::XMLError res = file.LoadFile("files/buttons.xml");
	xml::XMLNode* root = file.FirstChild();
	xml::XMLNode* buttons_list = root->FirstChildElement("list");
	usi yy = 200;
	for (xml::XMLElement* e = buttons_list->FirstChildElement("button"); e != NULL; e = e->NextSiblingElement("button"))
		{
		buttons.push_back(BarButton(e->Attribute("text"), e->Attribute("action"), 96, yy, btn_texture, btn_font, sf::Color(MAIN_RR, MAIN_GG, MAIN_BB, 255)));
		yy += 32 + VERTICAL_SPACING;
		}
	}
	//Read buttons end
	//Elements end

	bool outside = false;
	bool exiting = false;
	sf::Vector2f mouse_pos(0, 0);
	sf::Vector2f mouse_pos_previous(0, 0);


	while (window.isOpen())
		{
		//Window move beg
		if(MAIN_STAY)
			{
			int mx = sf::Mouse::getPosition().x;
			int my = sf::Mouse::getPosition().y;
			int wx = window.getPosition().x;
			if ((mx >= wx - 1) and not exiting)
				{
				if ((not outside) or (my > 32))
					{
					if (wx > WINDOW_MIN_X)
						{
						wx -= WINDOW_SPEED;
						if (wx < WINDOW_MIN_X)
							{
							wx = WINDOW_MIN_X;
							}
						}
					outside = false;
					window.setFramerateLimit(60);
					}
				}
			else if (wx < Screen::get_width())
				{
				wx += WINDOW_SPEED;
				exiting = true;
				if (wx >= Screen::get_width())
					{
					wx = Screen::get_width();
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
				for (BarButton& btn : buttons)
					{
					btn.mouse_moved(mouse_pos_previous, mouse_pos);
					}
				}
			else if (event.type == sf::Event::MouseButtonPressed)
				{
				for (BarButton& btn : buttons)
					{
					btn.mouse_pressed(mouse_pos);
					}
				}
			else if (event.type == sf::Event::MouseButtonReleased)
				{
				for (BarButton& btn : buttons)
					{
					btn.mouse_released(mouse_pos);
					}
				}
			}
		window.clear(sf::Color::Transparent);
		if (not outside)
			{
			//step
			ps.step();
			for (BarButton& btn : buttons)
				{
				btn.step();
				}
			clock.step();
			mouse_pos_previous = mouse_pos;

			//draw
			//window.clear(sf::Color(000, 000, 050, 255));
			window.draw(bg_sprite);

			ps.draw(window);
			window.draw(clock);
			for (BarButton& btn : buttons)
				{
				window.draw(btn);
				}
			}
		window.display();
		}
	std::exit(0);
	}