#include "BarButton.h"


void BarButton::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
	target.draw(sprite);
	target.draw(text);
	}

BarButton::BarButton(std::string text, std::string action, double x, double y, sf::Texture& texture, sf::Font& font, sf::Color &color) : SbItem(Settings::sidebar_element::TYPE::button)
	{
	this->action = action;
	current = 0;
	changing = 0;

	sprite = sf::Sprite();
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 142, 48));
	sprite.setOrigin(142 / 2, 8);
	sprite.setPosition(x, y);
	sprite.setColor(color);

	collision = sf::IntRect(x - 64, y, 127, 31);

	int xx = 0;
	anim = std::vector<sf::IntRect>();
	for (usi i = 0; i < 16; i++)
		{
		anim.push_back(sf::IntRect(xx, 0, 142, 48));
		xx += 142;
		}

	//TEXTS
	this->text.setFont(font);
	this->text.setFillColor(color);
	this->text.setOutlineColor(color);
	this->text.setCharacterSize(12);
	this->text.setString(text);
	this->text.setOrigin(58, 8 - 16);
	this->text.setPosition(x, y);
	}

BarButton::~BarButton()
	{}

void BarButton::mouse_moved(sf::Vector2f mouse_pos)
	{
	if (collision.contains(sf::Vector2i(mouse_pos)))
		{
		if (current < (anim.size() - 1))
			{
			changing = +1;
			}
		/*else
		{
		changing = 0;
		}*/
		}
	else
		{
		if (current > 0)
			{
			changing = -1;
			}
		/*else
		{
		changing = 0;
		}*/
		}
	}

void BarButton::mouse_moved(sf::Vector2f mouse_pos_previous, sf::Vector2f mouse_pos)
	{
	float min_y = std::min(mouse_pos_previous.y, mouse_pos.y);
	float max_y = std::max(mouse_pos_previous.y, mouse_pos.y);
	if (((collision.top + collision.height) > min_y) and ((collision.top) < max_y) and (collision.left < mouse_pos.x))
		{
		if (current < (anim.size() - 1))
			{
			changing = +1;
			}

		}

	else
		{
		if (current > 0)
			{
			changing = -1;
			}
		}
	}

void BarButton::mouse_pressed(sf::Vector2f mouse_pos)
	{}

void BarButton::mouse_released(sf::Vector2f mouse_pos)
	{
	if (collision.contains(sf::Vector2i(mouse_pos)))
		{
		CA2W ca2w(action.c_str());
		ShellExecute(null, L"open", ca2w, null, null, SW_SHOW);
		}
	}

void BarButton::step()
	{
	if (changing)
		{
		if (changing == 1)
			{
			if (current == anim.size() - 1)
				{
				changing = 0;
				}
			else
				{
				current++;
				sprite.setPosition(sprite.getPosition().x - 0.75, sprite.getPosition().y);
				text.setPosition(sprite.getPosition());
				}
			}
		else if (changing == -1)
			{
			if (current == 0)
				{
				changing = 0;
				}
			else
				{
				current--;
				sprite.setPosition(sprite.getPosition().x + 0.75, sprite.getPosition().y);
				text.setPosition(sprite.getPosition());
				}
			}
		}
	sprite.setTextureRect(anim[current]);
	}