#include "BarnackClock.h"
#include <time.h>
#include <iostream>
#include <string>

BarnackClock::BarnackClock(double x, double y, usi red, usi green, usi blue)
	{
	if (not texture.loadFromFile("textures/clock/t_clock.png"))
		{/*handle error*/
		}
	texture.setSmooth(true);

	if (!font.loadFromFile("fonts/times.ttf"))
		{/*handle herror*/
		}
	//SPRITES
	//background
	clock = sf::Sprite();
	clock.setTexture(texture);
	clock.setTextureRect(sf::IntRect(0, 0, 160, 160));
	clock.setOrigin(80, 80);
	clock.setPosition(x, y);
	clock.setColor(sf::Color(red, green, blue, 255));
	//analog
	analog_field = sf::Sprite();
	analog_field.setTexture(texture);
	analog_field.setTextureRect(sf::IntRect(160, 80, 82, 32));
	analog_field.setOrigin(82 / 2, 32 / 2);
	analog_field.setPosition(x, y + (160 / 5));
	analog_field.setColor(sf::Color(red, green, blue, 255));
	//day
	day_field = sf::Sprite();
	day_field.setTexture(texture);
	day_field.setTextureRect(sf::IntRect(160, 120, 54, 32));
	day_field.setOrigin(54 / 2, 32 / 2);
	day_field.setPosition(x, y - (160 / 5));
	day_field.setColor(sf::Color(red, green, blue, 255));
	//pointers
	//seconds
	secs = sf::Sprite();
	secs.setTexture(texture);
	secs.setTextureRect(sf::IntRect(160, 0, 32, 80));
	secs.setOrigin(15, 72);
	secs.setPosition(x, y);
	secs.setColor(sf::Color(red, green, blue, 255));
	//minutes
	mins = sf::Sprite();
	mins.setTexture(texture);
	mins.setTextureRect(sf::IntRect(192, 0, 32, 80));
	mins.setOrigin(15, 72);
	mins.setPosition(x, y);
	mins.setColor(sf::Color(red, green, blue, 255));
	//hours
	hous = sf::Sprite();
	hous.setTexture(texture);
	hous.setTextureRect(sf::IntRect(224, 0, 32, 80));
	hous.setOrigin(15, 72);
	hous.setPosition(x, y);
	hous.setColor(sf::Color(red, green, blue, 255));
	//end
	//TEXTS
	//analog
	analog.setFont(font);
	analog.setFillColor(sf::Color(red, green, blue, 255));
	analog.setCharacterSize(12);
	analog.setString("00:00:00");
	analog.setPosition(x - 21, y + (160 / 5) - 7);
	day.setFont(font);
	day.setFillColor(sf::Color(red, green, blue, 255));
	day.setCharacterSize(15);
	day.setString("MMM");
	day.setPosition(x - 14, y - (160 / 5) - 9);
	}


BarnackClock::~BarnackClock()
	{}

void BarnackClock::step()
	{
	struct tm ptm;
	time_t now = time(0);
	localtime_s(&ptm, &now);

	secs.setRotation((ptm.tm_sec) * 360 / 60);
	mins.setRotation((ptm.tm_min) * 360 / 60);
	hous.setRotation((ptm.tm_hour) * 360 / 12);
	std::string hh = (ptm.tm_hour > 9) ? std::to_string(ptm.tm_hour) : "0" + std::to_string(ptm.tm_hour);
	std::string mm = (ptm.tm_min > 9) ? std::to_string(ptm.tm_min) : "0" + std::to_string(ptm.tm_min);
	std::string ss = (ptm.tm_sec > 9) ? std::to_string(ptm.tm_sec) : "0" + std::to_string(ptm.tm_sec);
	analog.setString(hh + ":" + mm + ":" + ss);
	std::string dd;
	switch (ptm.tm_wday)
		{
		case 0: dd = "Dom"; break;
		case 1: dd = "Lun"; break;
		case 2: dd = "Mar"; break;
		case 3: dd = "Mer"; break;
		case 4: dd = "Gio"; break;
		case 5: dd = "Ven"; break;
		case 6: dd = "Sab"; break;
		default: dd = "N/A"; break;
		}
	day.setString(dd);
	}

void BarnackClock::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
	target.draw(clock);
	target.draw(analog_field);
	target.draw(analog);
	target.draw(day_field);
	target.draw(day);
	target.draw(secs);
	target.draw(mins);
	target.draw(hous);
	}