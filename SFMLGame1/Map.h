/* Author: Try Ajitiono 13512052 */
/* Filename: Map.h */
/* Header class for Minesweeper Map */

#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Map {
	public:
		Map();
		~Map();
		void makeEmpty(); //make an empty map
		bool getRevealState(int i, int j); //returns reveal boolan of i-j cell
		//click actions
		void reveal(int i, int j); //reveal the tile
		void revealTopBlanks(int i, int j); //reveal the top blank tiles
		void revealRightBlanks(int i, int j); //reveal the right blank tiles
		void revealBotBlanks(int i, int j); //reveal the bot blank tiles
		void revealLeftBlanks(int i, int j); //reveal the left blank tiles
		int countBomb(int i, int j); //counting bombs around a node
		sf::Vector2i getBlock(int i, int j);
		void flagTile(int i, int j); //flag/qmark the corresponding tile
		bool isFlagged(int i, int j);
		bool isQMarked(int i, int j);
		bool isBomb(int i, int j); //check if corresponding tile is a bomb
		//initialization
		void setBlank(); //set all 0,0 tile into 2,1
		void placeBomb(); //place random bombs
		void placeNumbers(); //number placers around a bomb
		int getBombNum();
		void setBombNum(int x);
		int getFieldSize();
		void setFieldSize(int x);
		void reset();
		//finish states
		void revealBombs(); //reveal bombs
		void flagBombs(); //reveal bombs
		bool checkFinish(); //check if all non-bomb tile have been revealed
	private:
		int Size; //field size
		int Bomb; //number of bombs
		sf::Vector2i **Block; //map
		bool **Revealed; //boolean tile reveal
		bool **Flag; //boolean tile flagged
		bool **QMark; //boolean tile question marked
};

#endif