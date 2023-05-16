#ifndef GAME_H
#define GAME_H

#include "lib.h"
#include "Button.h"
#include "Level.h"
#include "Scene.h"
#include "Player.h"
//#include "Slider.h"
//#include "TextInput.h"

class Game
{
private:

	struct block {
		int t;
		int dir;
		bool tr;
	};

	Player player;

	//Variables

	enum stages { MAIN_MENU, SETTINGS_MENU, GAME, SELECT_GAME };

	//All one tap key variables
	bool MousePressed;
	bool UpPressed;
	bool DownPressed;
	bool Tpressed;
	bool Spressed;
	bool RightPressed;
	bool LeftPressed;
	bool EscPressed;

	//Other variables
	int fps;
	int currentTex;
	int resolution;
	block brush;
	bool trBrush;

	bool passTransparency;

	bool playMode;

	bool TileArrange;

	float sizeRelation;

	bool paused;

	//Scene sceneSelector;

	ifstream readFile;
	string Info;

	int scene;

	bool codeLoaded;

	//Window
	RenderWindow window;
	VideoMode videoMode;
	Event ev;

	//Game objects
	Sprite tile;
	Texture tileT;

	Sprite pauseBackground;
	Texture pauseBackTex;

	Font font;
	Text text;

	View view;

	//Private functions
	void initVariables();
	void PauseMenu();
	void initWindow();
	void initGrid();
	void setCam();
	void setPlaceTile();
	void saveCode();
	void loadCode();
	void kill();

	void refreshTile(Vector2i tPos, bool o = false);

	bool touching();
	int strToInt(string s);

	float lerp(float a, float b, float t);

	Vector2f mousePos();

	

	//Scene controllers -> class Scene

	void mmenuUpdate();
	void gameUpdate();
	void settingsUpdate();
	void loadCodeUpdate();

	void mmenuRender();
	void gameRender();
	void settingsRender();
	void loadCodeRender();





	/*
		Here comes the game code
	*/

	//Tile grid based code
	//Here goes all the map variables, functions, and Game objects

	//Player variables
	int px;
	int py;
	float sx;
	float sy;
	int gravity;
	int psy;

	//Camera variables
	int camX;
	int camY;

	//Game objects
	Button* button;

	//Functions
	void genLevel();
	void setTex(int num);

	Level level;

public:
	void test();
	//Accessors
	const bool running();

	//Constructors / destructors
	Game(int _fps, int tgx, int tgy);
	virtual ~Game();

	//Functions
	void pollEvents();
	void update();
	void render();

};

#endif