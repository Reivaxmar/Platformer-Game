#ifndef LEVEL_CLASS_H
#define LEVEL_CLASS_H

#include "lib.h"

class Level
{
public:

	struct tile {
		tile(int _type, int _dir, bool _transparent = false) {
			type = _type;
			dir = _dir;
			transparent = _transparent;
		}
		int type;
		int dir;
		bool transparent;
	};

	Level(uint32_t width, uint32_t height);

	void setTile(Vector2i pos, tile t);
	void setTile(int x, int y, tile t);

	tile getTile(Vector2i pos);
	tile getTile(int x, int y);

	Vector2i getSize();

	void loadFile(string file);
	void safeFile(string name);

private:
	Vector2i levelSize;
	vector<vector<tile>> grid;

};



#endif
