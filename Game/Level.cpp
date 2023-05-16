#include "Level.h"

Level::Level(uint32_t width, uint32_t height)
{
	levelSize = Vector2i(width, height);
	grid.resize(levelSize.x, vector<tile>(levelSize.y, tile(0, 0, false)));
}

void Level::setTile(Vector2i pos, tile t)
{
	if (pos.x < 0 || pos.x >= levelSize.x) {
		return;
	}

	if (pos.y < 0 || pos.y >= levelSize.y) {
		return;
	}

	grid[pos.x][pos.y] = t;
}

void Level::setTile(int x, int y, tile t)
{
	if (x < 0 || x >= levelSize.x) {
		return;
	}

	if (y < 0 || y >= levelSize.y) {
		return;
	}

	grid[x][y] = t;
}

Level::tile Level::getTile(Vector2i pos)
{
	if (pos.x < 0 || pos.x >= levelSize.x) {
		return tile(0, 0, 0);
	}

	if (pos.y < 0 || pos.y >= levelSize.y) {
		return tile(0, 0, 0);
	}

	return grid[pos.x][pos.y];
}

Level::tile Level::getTile(int x, int y)
{
	if (x < 0 || x >= levelSize.x) {
		return tile(0, 0, 0);
	}

	if (y < 0 || y >= levelSize.y) {
		return tile(0, 0, 0);
	}

	return grid[x][y];
}

Vector2i Level::getSize()
{
	return levelSize;
}

void Level::loadFile(string file)
{
	ifstream in("Assets/Saves/" + file);

	if (in.is_open()) {
		//Decode
		in >> levelSize.x;
		in >> levelSize.y;

		grid.resize(levelSize.x, vector<tile>(levelSize.y, tile(0, 0, false)));

		for (int x = 0; x < levelSize.x; x++) {
			for (int y = 0; y < levelSize.y; y++) {
				in >> grid[x][y].type;
				in >> grid[x][y].transparent;
				in >> grid[x][y].dir;
			}
		}

		char nothing;
		in >> nothing;
	}

	in.close();
}

void Level::safeFile(string name)
{
	ofstream out("Assets/Saves/" + name);

	if (out.is_open()) {
		//Encode
		out << levelSize.x << ' ';
		out << levelSize.y << ' ';

		for (int x = 0; x < levelSize.x; x++) {
			for (int y = 0; y < levelSize.y; y++) {
				out << grid[x][y].type << ' ';
				out << grid[x][y].transparent << ' ';
				out << grid[x][y].dir << ' ';
			}
		}

		out << ';' << '\n';
	}

	out.close();
}
