/* Author: Try Ajitiono 13512052 */
/* Filename: Pregame.cpp */
/* Realization of header class for Minesweeper Pregame */

#include "Pregame.h"

Pregame::Pregame() {
	started = false;
	windowClosed = false;
	for (int i = 0; i < 3; i++) {
		bombs[i] = false;
		field[i] = false;
	}
	//default
	bombs[2] = true;
	field[0] = true;
}

Pregame::~Pregame() {}

bool Pregame::isStarted() {
	return started;
}

void Pregame::Choose(sf::RenderWindow &win) {
	//variables
	sf::Event Event;
	sf::Texture tileTexture, tileTexture2;
	sf::Sprite background, buttons;
	int mPosi, mPosj, k, dum;
	//initialization
	tileTexture.loadFromFile("imgs/background.png");
	tileTexture2.loadFromFile("imgs/pregame.png");
	background.setTexture(tileTexture);
	buttons.setTexture(tileTexture2);
	//algorithm
	while (win.pollEvent(Event) && !started) {
		if (Event.type == sf::Event::Closed) {
			win.close();
			windowClosed = true;
			started = true;
		}
		else if (Event.type == Event.MouseButtonReleased && Event.mouseButton.button == sf::Mouse::Left) {
			mPosi = sf::Mouse::getPosition(win).x / 16;
			mPosj = sf::Mouse::getPosition(win).y / 32;
			if (mPosi >= 1 && mPosi < 19) {
				toggleButton(mPosi, mPosj);
			}
		}
		win.clear();
		win.draw(background);
		for (int i = 1; i < 9; i++) { //row
			k = 0;
			for (int j = 1; j < 19; j++) { //column
				if (i == 1 && j == 1) { //choose field size
					buttons.setPosition(16, 32);
					buttons.setTextureRect(sf::IntRect(0, 0, 288, 32));
				}
				else if (i == 2) { //buttons for field size
					if (j == 1 || j == 7 || j == 13) {
						dum = i;
						buttons.setPosition(j * 16, i * 32);
						if (!field[k]) {
							dum--;
						}
						buttons.setTextureRect(sf::IntRect((j * 16) - 16, dum * 32, 96, 32));
						k++;
					}
				}
				else if (i == 4) { //choose bombs number
					buttons.setPosition(16, 128);
					buttons.setTextureRect(sf::IntRect(0, 96, 288, 32));
				}
				else if (i == 5) { //buttons for bombs number
					if (j == 1 || j == 7 || j == 13) {
						dum = i;
						buttons.setPosition(j * 16, i * 32);
						if (!bombs[k]) {
							dum--;
						}
						buttons.setTextureRect(sf::IntRect((j * 16) - 16, dum * 32, 96, 32));
						k++;
					}
				}
				else if (i == 7) {
					buttons.setPosition(16, 224);
					buttons.setTextureRect(sf::IntRect(0, 192, 288, 32));
				}
				win.draw(buttons);
			}
		}
		win.display();
	}
}

void Pregame::toggleButton(int Box, int BoF) {
	switch (BoF) {
		case 2: //field
			if (Box >= 1 && Box < 7) {
				field[0] = true;
				field[1] = false;
				field[2] = false;
			}
			else if (Box >= 7 && Box < 13) {
				field[0] = false;
				field[1] = true;
				field[2] = false;
			}
			else if (Box >= 13 && Box < 19) {
				field[0] = false;
				field[1] = false;
				field[2] = true;
			}
			break;
		case 5: //bomb
			if (Box >= 1 && Box < 7) {
				bombs[0] = true;
				bombs[1] = false;
				bombs[2] = false;
			}
			else if (Box >= 7 && Box < 13) {
				bombs[0] = false;
				bombs[1] = true;
				bombs[2] = false;
			}
			else if (Box >= 13 && Box < 19) {
				bombs[0] = false;
				bombs[1] = false;
				bombs[2] = true;
			}
			break;
		case 7: //start
			started = true;
			break;
	}
}

int Pregame::getBombChoice() {
	int i = 0;
	bool found = false;
	while (i < 3 && !found) {
		if (bombs[i]) {
			found = true;
		}
		else {
			i++;
		}
	}
	return i;
}

int Pregame::getFieldChoice() {
	int i = 0;
	bool found = false;
	while (i < 3 && !found) {
		if (field[i]) {
			found = true;
		}
		else {
			i++;
		}
	}
	return i;
}

bool Pregame::isWindowClosed() {
	return windowClosed;
}

void Pregame::reset() {
	started = false;
	windowClosed = false;
	for (int i = 0; i < 3; i++) {
		bombs[i] = false;
		field[i] = false;
	}
	//default
	bombs[2] = true;
	field[0] = true;
	windowClosed = false;
}