/* Author: Try Ajitiono 13512052 */
/* Filename: Game.cpp */
/* Realization of header class for Minesweeper Game */

#include "Game.h"

Game::Game() {
	//initialization
	finished = false;
	clicked = false;
	windowClosed = false;
	tileTexture.loadFromFile("imgs/tiles.png");
	tiles.setTexture(tileTexture);
}

Game::~Game() {}

void Game::init(int a, int b) {
	map.setBombNum(a);
	map.setFieldSize(b);
	map.makeEmpty();
	map.placeBomb();
	map.placeNumbers();
	map.setBlank();
}

Map Game::getMap() {
	return map;
}

bool Game::isFinished() {
	return finished;
}

void Game::play(sf::RenderWindow &Window) {
	//algorithm
	while (Window.pollEvent(Event) && !finished) {
		if (Event.type == sf::Event::Closed) {
			Window.close();
			windowClosed = true;
			finished = true;
		}
		else if (Event.type == Event.MouseButtonReleased && Event.mouseButton.button == sf::Mouse::Left) {
			mPosi = sf::Mouse::getPosition(Window).x / 32;
			mPosj = sf::Mouse::getPosition(Window).y / 32;
			map.reveal(mPosi, mPosj);
			if (map.isBomb(mPosi, mPosj)) {
				map.revealBombs();
				finished = true;
			}
		}
		else if (Event.type == Event.MouseButtonReleased && Event.mouseButton.button == sf::Mouse::Right) {
			mPosi = sf::Mouse::getPosition(Window).x / 32;
			mPosj = sf::Mouse::getPosition(Window).y / 32;
			map.flagTile(mPosi, mPosj);
		}
		if (map.checkFinish()) {
			map.flagBombs();
			finished = true;
		}
	}
	Window.clear();
	for (int i = 0; i < map.getFieldSize(); i++) {
		for (int j = 0; j < map.getFieldSize(); j++) {
			tiles.setPosition(i * 32, j * 32);
			if (map.getRevealState(i, j)) { //reveal true
				tiles.setTextureRect(sf::IntRect(map.getBlock(i, j).x * 32, map.getBlock(i, j).y * 32, 32, 32));
			}
			else { //reveal false
				if (map.isFlagged(i, j)) { //tile is flagged
					tiles.setTextureRect(sf::IntRect(4 * 32, 1 * 32, 32, 32));
				}
				else if (map.isQMarked(i, j)) { //tile is qmarked
					tiles.setTextureRect(sf::IntRect(3 * 32, 1 * 32, 32, 32));
				}
				else { //neither
					tiles.setTextureRect(sf::IntRect(0, 0, 32, 32));
				}
			}
			Window.draw(tiles);
		}
	}
	Window.display();
}

bool Game::isWindowClosed() {
	return windowClosed;
}

bool Game::continuePlay(sf::RenderWindow &Window) {
	bool cont = false;
	while (Window.pollEvent(Event) && !cont && !windowClosed) {
		Window.clear();
		for (int i = 0; i < map.getFieldSize(); i++) {
			for (int j = 0; j < map.getFieldSize(); j++) {
				tiles.setPosition(i * 32, j * 32);
				if (map.getRevealState(i, j)) { //reveal true
					tiles.setTextureRect(sf::IntRect(map.getBlock(i, j).x * 32, map.getBlock(i, j).y * 32, 32, 32));
				}
				else { //reveal false
					if (map.isFlagged(i, j)) { //tile is flagged
						tiles.setTextureRect(sf::IntRect(4 * 32, 1 * 32, 32, 32));
					}
					else if (map.isQMarked(i, j)) { //tile is qmarked
						tiles.setTextureRect(sf::IntRect(3 * 32, 1 * 32, 32, 32));
					}
					else { //neither
						tiles.setTextureRect(sf::IntRect(0, 0, 32, 32));
					}
				}
				Window.draw(tiles);
			}
		}
		Window.display();
		if (Event.type == sf::Event::Closed) {
			Window.close();
			windowClosed = true;
		}
		else if (Event.type == Event.MouseButtonReleased && Event.mouseButton.button == sf::Mouse::Left) {
			cont = true;
			clicked = true;
		}
	}
	return cont;
}

bool Game::isClicked() {
	return clicked;
}

void Game::reset() {
	finished = false;
	clicked = false;
	windowClosed = false;
	map.reset();
}