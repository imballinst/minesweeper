/* Author: Try Ajitiono 13512052 */
/* Filename: Main.cpp */
/* Main program for Minesweeper */

#include "Map.h"
#include "Pregame.h"
#include "Game.h"

int main() {
	//declaration
	Pregame pregame;
	Game game;
	int a, b;
	//initialization
	bool playing = true;
	//algorithm
	while (playing) {
		if (!game.isWindowClosed()) {
			sf::RenderWindow Window(sf::VideoMode(320, 320, 32), "Minesweeper v0", sf::Style::Close);
			//pre-game
			while (!pregame.isStarted()) {
				pregame.Choose(Window);
			}
			Window.close();
		}
		//transition
		a = pregame.getBombChoice();
		b = pregame.getFieldChoice();
		game.init(a, b);
		//game
		if (!pregame.isWindowClosed()) {
			sf::RenderWindow gameWindow(sf::VideoMode(32 * game.getMap().getFieldSize(), 32 * game.getMap().getFieldSize(), 32), "Minesweeper v0", sf::Style::Close);
			while (!game.isFinished()) {
				game.play(gameWindow);
			}
			if (pregame.isWindowClosed() || game.isWindowClosed()) {
				playing = false;
			}
			else {
				while (!game.isClicked() && !game.isWindowClosed()) {
					playing = game.continuePlay(gameWindow);
				}
				if (playing) {
					game.getMap().reset();
					pregame.reset();
					game.reset();
				}
			}
		}
		else {
			playing = false;
		}
	}
	return 0;
}