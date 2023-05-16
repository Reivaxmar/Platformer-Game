#include "Player.h"

Player::Player(float gravity)
{
}

Vector2f Player::getPosition()
{
	return pos;
}

void Player::update(Level& level, GameState gs)
{
	if (gs == PLAYING) {
		speed.y++;

		//Move player on the x axis
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			speed.x++;
		}

		if (Keyboard::isKeyPressed(Keyboard::A)) {
			speed.x--;
		}

		//Smooth the movement a bit
		speed.x *= 0.85f;
		pos.x += round(speed.x) * 2;

		//Collisions on the x axis
		if (touching(level)) {
			if (round(speed.x * 100) / 100 < 0) {
				while (touching(level)) {
					speed.x = 0;
					pos.x++;
				}
			}
			else if (round(speed.x * 100) / 100 > 0) {
				while (touching(level)) {
					speed.x = 0;
					pos.x--;
				}

			}
		}

		//Add velocity
		pos.y += speed.y;

		//Collisions in the y axis
		if (abs(speed.y) == speed.y) {
			while (touching(level)) {
				pos.y--;
				speed.y = 0;
			}
		}
		else {
			while (touching(level)) {
				pos.y++;
				speed.y = 0;
			}
		}

		//Touching ground condition
		pos.y++;

		//Jump!
		if (Keyboard::isKeyPressed(Keyboard::W) && touching(level)) {
			speed.y = -35;
		}

		pos.y--;

		if (pos.y > level.getSize().y * 100 - 50) {
			kill();
		}
	}
	else if (gs == EDITOR) {
		//Move player on the x axis
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			speed.x++;
		}

		if (Keyboard::isKeyPressed(Keyboard::A)) {
			speed.x--;
		}

		//Move player on the y axis
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			speed.y++;
		}

		if (Keyboard::isKeyPressed(Keyboard::W)) {
			speed.y--;
		}

		//Smooth the movement a bit
		speed.x *= 0.85f;
		pos.x += round(speed.x) * 2;

		speed.y *= 0.85f;
		pos.y += round(speed.y) * 2;

		//Collisions for getting out of the map
		if (pos.x < 100) {
			pos.x = 100;
		}
		if (pos.x > level.getSize().x * 100 - 200) {
			pos.x = level.getSize().x * 100 - 200;
		}

		if (pos.y < 100) {
			pos.y = 100;
		}
		if (pos.y > level.getSize().y * 100 - 100) {
			pos.y = level.getSize().y * 100 - 100;
		}
	}
	else {
		std::cout << "Error: not a possible editor" << std::endl;
	}
}

bool Player::touching(Level& level) {
	bool ret = level.getTile((pos.x - 0) / 100, (pos.y + 1) / 100).type != 0 && level.getTile((pos.x - 0) / 100, (pos.y + 1) / 100).transparent == false || level.getTile((pos.x - 1) / 100 + 1, (pos.y - 0) / 100 + 1).type != 0 && level.getTile((pos.x - 1) / 100 + 1, (pos.y - 0) / 100 + 1).transparent == false || level.getTile((pos.x - 1) / 100 + 1, (pos.y + 1) / 100).type != 0 && level.getTile((pos.x - 1) / 100 + 1, (pos.y + 1) / 100).transparent == false || level.getTile((pos.x - 0) / 100, (pos.y - 0) / 100 + 1).type != 0 && level.getTile((pos.x - 0) / 100, (pos.y - 0) / 100 + 1).transparent == false;
	return ret;
}

void Player::kill() {
	pos = Vector2f(200, 200);
	speed = Vector2f(0, 0);
}