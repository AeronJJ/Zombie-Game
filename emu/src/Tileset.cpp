#include "Tileset.h"

Tileset::Tileset() {}

Tile* Tileset::getTile(int tileNum) {
	return &tiles_[tileNum];
}


int Tileset::getNum() { return numberOfTiles_; }
