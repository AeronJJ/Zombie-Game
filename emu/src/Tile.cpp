#include "Tile.h"

Pos::Pos(int x, int y) {
	x = x;
	y = y;
}

Tile::Tile() {
	colour_ = 0;
}

Tile::Tile(int x, int y, bool col) {
	colour_ = col;
	pos_.x = x;
	pos_.y = y;
}

void Tile::set(bool col) {
	colour_ = col;
}

void Tile::flip() {
	colour_ = !colour_;
}

Pos Tile::getPos() {
	return pos_;
}

bool Tile::getColour() {
	return colour_;
}
