#pragma once

#include "Tile.h"

class Tileset {
	public:
	Tileset();
	Tile* getTile(int tileNum);
	int getNum();

	private:
	static const int numberOfTiles_ = 4032;
	Tile tiles_[numberOfTiles_];
};
