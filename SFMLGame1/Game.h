/* Author: Try Ajitiono 13512052 */
/* Filename: Game.h */
/* Header class for Minesweeper Game */

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"

class Game {
	public:
		Game();
		~Game();
		void init(int a, int b); //initializes the map
		Map getMap();
		bool isFinished(); //returns true if game has been finished / window has been closed
		void play(sf::RenderWindow &Window); //the game display
		bool isWindowClosed(); //returns true if the window has been closed
		bool isClicked(); //returns true if player left clicks mouse after the game finishes
		bool continuePlay(sf::RenderWindow &Window); //using isclicked method
		void reset(); //resets the attributes
	private:
		Map map;
		bool windowClosed;
		bool finished;
		bool clicked;
		sf::Texture tileTexture;
		sf::Sprite tiles;
		sf::Event Event;
		int mPosi, mPosj;
};

#endif