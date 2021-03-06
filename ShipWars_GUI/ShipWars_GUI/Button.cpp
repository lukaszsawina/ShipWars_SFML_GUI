#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, int size )
{
	this->x = x;
	this->y = y;
	this->buttonState = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(size);



	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->shape.setFillColor(this->idleColor);
	this->hideButton();
}

Button::~Button()
{
}


//Accessors
const bool Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;
	
	return false;
}

//Functions
void Button::setTextPosition()
{
	
	int text_width = this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.0f) - (this->text.getGlobalBounds().width / 2.0f);
	int text_height = this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.0f) - (this->text.getGlobalBounds().height / 2.0f) - 4;
	this->text.setPosition(sf::Vector2f(text_width, text_height));
}

void Button::update(const sf::Vector2f mousePos)
{
	//idle
	this->buttonState = BTN_IDLE;
	//hover
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;
		
		//pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::render(sf::RenderTarget* target)
{
	setTextPosition();
	target->draw(this->shape);
	target->draw(this->text);
}

void Button::hideButton()
{
	
	this->shape.setPosition(sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
}

void Button::showButton()
{
	this->shape.setPosition(sf::Vector2f(this->x, this->y));
}

void Button::changePos(float x, float y, std::string text)
{
	this->x = x;
	this->y = y;
	this->text.setString(text);
}
