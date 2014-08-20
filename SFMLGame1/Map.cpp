/* Author: Try Ajitiono 13512052 */
/* Filename: Map.cpp */
/* Realization of header class for Minesweeper Map */

#include "Map.h"

Map::Map() {
	//initialization
	Size = 10;
	Bomb = 20;
}

Map::~Map() {}

void Map::makeEmpty() {
	//algorithm
	Block = new sf::Vector2i*[Size];
	Revealed = new bool*[Size];
	Flag = new bool*[Size];
	QMark = new bool*[Size];
	for (int i = 0; i < Size; i++) {
		Block[i] = new sf::Vector2i[Size];
		Revealed[i] = new bool[Size];
		Flag[i] = new bool[Size];
		QMark[i] = new bool[Size];
		for (int j = 0; j < Size; j++) {
			Block[i][j].x = 0;
			Block[i][j].y = 0;
			Revealed[i][j] = false;
			Flag[i][j] = false;
			QMark[i][j] = false;
		}
	}
}

int Map::getBombNum() {
	//algorithm
	return Bomb;
}

int Map::getFieldSize() {
	return Size;
}

void Map::placeBomb() {
	//variables
	int RNG;
	//algorithm
	sf::Vector2i loadCounter = sf::Vector2i(0, 0); //vector counter
	srand(time(NULL));
	while (Bomb > 0) {
		RNG = (rand() % 20) + 1; //random between 1 to 20
		if (RNG == 10) {
			//bomb tile
			Block[loadCounter.x][loadCounter.y].x = 5;
			Block[loadCounter.x][loadCounter.y].y = 1;
			Bomb--;
		}
		//increment counter
		loadCounter.x++;
		if (loadCounter.x == Size) {
			loadCounter.x = 0;
			loadCounter.y++;
			if (loadCounter.y == Size) {
				loadCounter.y = 0;
			}
		}
	}
	//endwhile
}

void Map::placeNumbers() {
	//algorithm
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			if (Block[i][j].x != 5 && Block[i][j].y != 1) {
				Block[i][j].x = countBomb(i, j);
				if (Block[i][j].x > 6) {
					Block[i][j].x -= 6;
					Block[i][j].y++;
				}
			}
		}
	}
}

sf::Vector2i Map::getBlock(int i, int j) {
	return Block[i][j];
}

bool Map::getRevealState(int i, int j) {
	return Revealed[i][j];
}

void Map::reveal(int i, int j) {
	Revealed[i][j] = true;
	if (countBomb(i, j) == 0 && !isBomb(i, j)) {
		if (i != 0) {
			revealTopBlanks(i - 1, j);
			Revealed[i - 1][j] = true;
		}
		if (i != (Size - 1)) {
			revealBotBlanks(i + 1, j);
			Revealed[i + 1][j] = true;
		}
		if (j != (Size - 1)) {
			revealRightBlanks(i, j + 1);
			Revealed[i][j + 1] = true;
		}
		if (j != 0) {
			revealLeftBlanks(i, j - 1);
			Revealed[i][j - 1] = true;
		}
	}
}

void Map::revealTopBlanks(int i, int j) {
	if (countBomb(i,j) == 0 && !Revealed[i][j]) {
		Revealed[i][j] = true;
		if (i != 0) {
			revealTopBlanks(i - 1, j);
			Revealed[i - 1][j] = true;
		}
		if (j != (Size - 1)) {
			revealRightBlanks(i, j + 1);
			Revealed[i][j + 1] = true;
		}
		if (j != 0) {
			revealLeftBlanks(i, j - 1);
			Revealed[i][j - 1] = true;
		}
	}
}

void Map::revealRightBlanks(int i, int j) {
	if (countBomb(i, j) == 0 && !Revealed[i][j]) {
		Revealed[i][j] = true;
		if (i != 0) {
			revealTopBlanks(i - 1, j);
			Revealed[i - 1][j] = true;
		}
		if (j != (Size - 1)) {
			revealRightBlanks(i, j + 1);
			Revealed[i][j + 1] = true;
		}
		if (i != (Size - 1)) {
			revealBotBlanks(i + 1, j);
			Revealed[i + 1][j] = true;
		}
	}
}

void Map::revealBotBlanks(int i, int j) {
	if (countBomb(i, j) == 0 && !Revealed[i][j]) {
		Revealed[i][j] = true;
		if (j != (Size - 1)) {
			revealRightBlanks(i, j + 1);
			Revealed[i][j + 1] = true;
		}
		if (i != (Size - 1)) {
			revealBotBlanks(i + 1, j);
			Revealed[i + 1][j] = true;
		}
		if (j != 0) {
			revealLeftBlanks(i, j - 1);
			Revealed[i][j - 1] = true;
		}
	}
}

void Map::revealLeftBlanks(int i, int j) {
	if (countBomb(i, j) == 0 && !Revealed[i][j]) {
		Revealed[i][j] = true;
		if (i != 0) {
			revealTopBlanks(i - 1, j);
			Revealed[i - 1][j] = true;
		}
		if (i != (Size - 1)) {
			revealBotBlanks(i + 1, j);
			Revealed[i + 1][j] = true;
		}
		if (j != 0) {
			revealLeftBlanks(i, j - 1);
			Revealed[i][j - 1] = true;
		}
	}
}

void Map::setBlank() {
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			if (Block[i][j].x == 0 && Block[i][j].y == 0) {
				Block[i][j].x = 2;
				Block[i][j].y = 1;
			}
		}
	}
}

int Map::countBomb(int i, int j) {
	int count = 0;
	if (i == 0) { //top
		if (j == 0) { //top left
			if (Block[i + 1][j + 1].x == 5 && Block[i + 1][j + 1].y == 1) {
				count++;
			}
			if (Block[i + 1][j].x == 5 && Block[i + 1][j].y == 1) {
				count++;
			}
			if (Block[i][j + 1].x == 5 && Block[i][j + 1].y == 1) {
				count++;
			}
		}
		else if (j == (Size - 1)) { //top right
			if (Block[i + 1][j - 1].x == 5 && Block[i + 1][j - 1].y == 1) {
				count++;
			}
			if (Block[i + 1][j].x == 5 && Block[i + 1][j].y == 1) {
				count++;
			}
			if (Block[i][j - 1].x == 5 && Block[i][j - 1].y == 1) {
				count++;
			}
		}
		else if (j > 0 && j < (Size - 1)) { //top mid
			if (Block[i + 1][j + 1].x == 5 && Block[i + 1][j + 1].y == 1) {
				count++;
			}
			if (Block[i + 1][j - 1].x == 5 && Block[i + 1][j - 1].y == 1) {
				count++;
			}
			if (Block[i + 1][j].x == 5 && Block[i + 1][j].y == 1) {
				count++;
			}
			if (Block[i][j + 1].x == 5 && Block[i][j + 1].y == 1) {
				count++;
			}
			if (Block[i][j - 1].x == 5 && Block[i][j - 1].y == 1) {
				count++;
			}
		}
	}
	else if (i == (Size - 1)) {
		if (j == 0) { //bot left
			if (Block[i - 1][j + 1].x == 5 && Block[i - 1][j + 1].y == 1) {
				count++;
			}
			if (Block[i - 1][j].x == 5 && Block[i - 1][j].y == 1) {
				count++;
			}
			if (Block[i][j + 1].x == 5 && Block[i][j + 1].y == 1) {
				count++;
			}
		}
		else if (j == (Size - 1)) { //bot right
			if (Block[i - 1][j - 1].x == 5 && Block[i - 1][j - 1].y == 1) {
				count++;
			}
			if (Block[i - 1][j].x == 5 && Block[i - 1][j].y == 1) {
				count++;
			}
			if (Block[i][j - 1].x == 5 && Block[i][j - 1].y == 1) {
				count++;
			}
		}
		else if (j > 0 && j < (Size - 1)) { //bot mid
			if (Block[i - 1][j + 1].x == 5 && Block[i - 1][j + 1].y == 1) {
				count++;
			}
			if (Block[i - 1][j - 1].x == 5 && Block[i - 1][j - 1].y == 1) {
				count++;
			}
			if (Block[i - 1][j].x == 5 && Block[i - 1][j].y == 1) {
				count++;
			}
			if (Block[i][j + 1].x == 5 && Block[i][j + 1].y == 1) {
				count++;
			}
			if (Block[i][j - 1].x == 5 && Block[i][j - 1].y == 1) {
				count++;
			}
		}
	}
	else if (i > 0 && i < (Size - 1)) { //mid
		if (j == 0) { //mid left
			if (Block[i - 1][j + 1].x == 5 && Block[i - 1][j + 1].y == 1) {
				count++;
			}
			if (Block[i - 1][j].x == 5 && Block[i - 1][j].y == 1) {
				count++;
			}
			if (Block[i][j + 1].x == 5 && Block[i][j + 1].y == 1) {
				count++;
			}
			if (Block[i + 1][j + 1].x == 5 && Block[i + 1][j + 1].y == 1) {
				count++;
			}
			if (Block[i + 1][j].x == 5 && Block[i + 1][j].y == 1) {
				count++;
			}
		}
		else if (j == (Size - 1)) { //mid right
			if (Block[i - 1][j - 1].x == 5 && Block[i - 1][j - 1].y == 1) {
				count++;
			}
			if (Block[i - 1][j].x == 5 && Block[i - 1][j].y == 1) {
				count++;
			}
			if (Block[i][j - 1].x == 5 && Block[i][j - 1].y == 1) {
				count++;
			}
			if (Block[i + 1][j - 1].x == 5 && Block[i + 1][j - 1].y == 1) {
				count++;
			}
			if (Block[i + 1][j].x == 5 && Block[i + 1][j].y == 1) {
				count++;
			}
		}
		else if (j > 0 && j < (Size - 1)) { //mid mid
			if (Block[i - 1][j - 1].x == 5 && Block[i - 1][j - 1].y == 1) {
				count++;
			}
			if (Block[i - 1][j].x == 5 && Block[i - 1][j].y == 1) {
				count++;
			}
			if (Block[i][j - 1].x == 5 && Block[i][j - 1].y == 1) {
				count++;
			}
			if (Block[i + 1][j - 1].x == 5 && Block[i + 1][j - 1].y == 1) {
				count++;
			}
			if (Block[i + 1][j].x == 5 && Block[i + 1][j].y == 1) {
				count++;
			}
			if (Block[i - 1][j + 1].x == 5 && Block[i - 1][j + 1].y == 1) {
				count++;
			}
			if (Block[i][j + 1].x == 5 && Block[i][j + 1].y == 1) {
				count++;
			}
			if (Block[i + 1][j + 1].x == 5 && Block[i + 1][j + 1].y == 1) {
				count++;
			}
		}
	}
	return count;
}

void Map::flagTile(int i, int j) {
	if (!Revealed[i][j]) {
		if (Flag[i][j]) { //flagged
			Flag[i][j] = false;
			QMark[i][j] = true;
		}
		else if (QMark[i][j]) { //qmarked
			QMark[i][j] = false;
		}
		else { //neither
			Flag[i][j] = true;
		}
	}
}

bool Map::isFlagged(int i, int j) {
	return Flag[i][j];
}

bool Map::isQMarked(int i, int j) {
	return QMark[i][j];
}

bool Map::isBomb(int i, int j) {
	if (Block[i][j].x == 5 && Block[i][j].y == 1) {
		return true;
	}
	else {
		return false;
	}
}

void Map::revealBombs() {
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			if (isBomb(i,j)) {
				Revealed[i][j] = true;
			}
		}
	}
}

bool Map::checkFinish() {
	bool finish = true;
	int i = 0, j = 0;
	while (finish && i < Size && j < Size) {
		if (!Revealed[i][j] && !isBomb(i, j)) {
			finish = false;
		}
		j++;
		if (j > (Size - 1)) {
			j = 0;
			i++;
		}
	}
	return finish;
}

void Map::setBombNum(int x) {
	switch (x) {
		case 0: Bomb = 10; break;
		case 1: Bomb = 15; break;
		case 2: Bomb = 20; break;
	}
}

void Map::setFieldSize(int x) {
	switch (x) {
		case 0: Size = 10; break;
		case 1: Size = 15; break;
		case 2: Size = 20; break;
	}
}

void Map::reset() {
	Size = 10;
	Bomb = 20;
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			Block[i][j].x = 0;
			Block[i][j].y = 0;
			Revealed[i][j] = false;
			Flag[i][j] = false;
			QMark[i][j] = false;
		}
	}
}

void Map::flagBombs() {
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			if (isBomb(i, j)) {
				Flag[i][j] = true;
			}
		}
	}
}