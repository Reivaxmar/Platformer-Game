#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H

#include <SFML/Graphics.hpp>
using namespace sf;

#include "Level.h"

class Player
{
private:
	Vector2f pos;
	Vector2f speed;
	bool touching(Level& level);
	void kill();
public:
	enum GameState { EDITOR, PLAYING };
	Player(float gravity);
	Vector2f getPosition();
	void update(Level& level, GameState gs);
};

#endif