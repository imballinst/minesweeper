/* Author: Try Ajitiono 13512052 */
/* Filename: Pregame.h */
/* Header class for Minesweeper Pregame */

#ifndef PREGAME_H
#define PREGAME_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Pregame {
	public:
		Pregame();
		~Pregame();
		bool isStarted(); //returns bool started
		void Choose(sf::RenderWindow &win); //pregame window
		void toggleButton(int Box, int BoF); //toggles the button according to mPosi or mPosj
		int getBombChoice(); //returns the index of the bomb choice user has chosen
		int getFieldChoice(); //returns the index of the field choice user has chosen
		bool isWindowClosed(); //checks if the window status
		void reset(); //reset if the player wants to play again
	private:
		bool started;
		bool windowClosed;
		bool bombs[3];
		bool field[3];
};

#endif