
#include "Gracz.h"

void Gracz::initGracz(sf::RenderWindow* window)
{
	this->planszaGracza.initPlansza(window);
	this->planszaPrzeciwnika.initPlanszaPrzeciwnika();
	this->akcje = 1;
	this->ustawienie_statkow = 10;
}

//Rozgrywka
void Gracz::updateBoard(sf::Vector2f mousePosView, Gracz* planszaPrzeciwnika)
{
	for (int i = 0; i < this->sizeOfBorads; i++)
		for (int j = 0; j < this->sizeOfBorads; j++)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->akcje > 0)
			{
				if (this->planszaPrzeciwnika.getPole(i, j).getGlobalBounds().contains(mousePosView) && !this->planszaPrzeciwnika.czyWidoczne(i, j))
				{
					this->planszaPrzeciwnika.clicked(i, j);
					if (!planszaPrzeciwnika->clicked(i, j))
						this->akcje--;
					else
					{
						this->planszaPrzeciwnika.setRodzaj(i, j, RodzajPola::Wrak);
					}
				}
			}
	}
}

//Ustawianie statkow
void Gracz::updateBoard(sf::Vector2f mousePosView)
{
	for (int i = 0; i < this->sizeOfBorads; i++)
		for (int j = 0; j < this->sizeOfBorads; j++)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->ustawienie_statkow > 0 && this->akcje != 0)
			{
				if (this->planszaGracza.getPole(i, j).getGlobalBounds().contains(mousePosView) && !this->planszaGracza.czyJestStatek(i,j))
				{
					this->planszaGracza.clicked(i, j, RodzajPola::Statek);
					this->ustawienie_statkow--;
					this->akcje--;

				}
			}
		}
}

void Gracz::setPlayerName(std::string name)
{
	this->playerName = name;
}

void Gracz::renderBoard(sf::RenderWindow* window)
{
	for (int i = 0; i < this->sizeOfBorads; i++)
		for (int j = 0; j < this->sizeOfBorads; j++)
		{

			if (this->planszaGracza.czyPoleJestWolne(i, j))
				window->draw(this->planszaGracza.getPole(i, j));
			else
			{
				window->draw(this->planszaGracza.getSprite(i, j));
				
			}

			if (this->planszaPrzeciwnika.czyPoleJestWolne(i, j))
				window->draw(this->planszaPrzeciwnika.getPole(i, j));
			else
			{
				window->draw(this->planszaPrzeciwnika.getSprite(i, j));
			}

		}
}

bool Gracz::clicked(int positionx, int positiony)
{
	return this->planszaGracza.clicked(positionx, positiony);
}

void Gracz::resetMoves()
{
	this->akcje = 1;
}

int Gracz::getIloscUstawionych()
{
	return this->ustawienie_statkow;
}

bool Gracz::getAkcje()
{
	return this->akcje;
}

bool Gracz::czyJestStatek(int positionx, int positiony)
{
	return this->planszaGracza.czyJestStatek(positionx, positiony);
}

int Gracz::iloscTrafionych()
{
	return this->planszaGracza.iloscTrafionych();
}

bool Gracz::czyKoniec()
{
	if (this->planszaGracza.iloscTrafionych() == this->iloscStatkow)
	{
		this->czyPrzegrany = true;
		return true;
	}
	return false;
}

bool Gracz::czyPrzegral()
{
	return this->czyPrzegrany;
}

void Gracz::setPosition(int positionx, int positiony)
{
	this->planszaPrzeciwnika.setRodzaj(positionx, positiony, RodzajPola::Wrak);
}

std::string Gracz::getName()
{
	return this->playerName;
}

void Gracz::resetGracz()
{
	this->planszaGracza.resetPlansza();
	this->planszaPrzeciwnika.resetPlansza();
}
