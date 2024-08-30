#pragma once

struct Pos {
	Pos(int x = 0, int y = 0);
	int x;
	int y;
};

class Tile {
	public:
	Tile();
	Tile(int x, int y, bool col = 0);
	void flip();
	void set(bool col);
	Pos getPos();
	bool getColour();

	private:
	bool colour_;
	Pos pos_;
};
