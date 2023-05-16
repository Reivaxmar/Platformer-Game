#include "Game.h"

//Constructors / Destructors

Game::Game(int _fps, int tgx, int tgy):
	window(VideoMode::getDesktopMode(), "Game", Style::Fullscreen),
	level(100, 30),
	player(1)
	//sceneSelector(1)
{
	font.loadFromFile("Assets/Textures/Arial.ttf");
	button = new Button(font, Color(200, 200, 200), Color(150, 150, 150), Color(100, 100, 100), Color::Black, Vector2f(1920.f, 1080.f));

	gravity = 10;
	fps = _fps;

	//sceneSelector.addScene(Scene::func("Game", &test));

	initVariables();
	initWindow();
	initGrid();
}


Game::~Game()
{
	//delete window;
	delete button;
}

//Accessors

const bool Game::running() {
	return window.isOpen();
}


//Functions

void Game::pollEvents() {

	//If close button pressed or escape key pressed close the window and finish the program
	while (window.pollEvent(ev)) {
		if (ev.type == Event::Closed)
			window.close();
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {

			if (EscPressed == false && scene == GAME) {
				PauseMenu();
			}

			EscPressed = true;
		}
		else {
			EscPressed = false;
		}
	}
}

void Game::PauseMenu() {
	paused = !paused;
}

void Game::update() {
	pollEvents();

	switch (scene) {
	case 0:
		mmenuUpdate();
		break;
	case 1:
		settingsUpdate();
		break;
	case 2:
		gameUpdate();
		break;
	}
}

void Game::mmenuUpdate() {

}

void Game::settingsUpdate() {

}

void Game::gameUpdate() {
	//Code goes here
	//Player controller and collisions scrpits

	/*
		Acceleration: x = 0, y = -1
		Speed: x = sx, y = psy
		Position: x = px, y = py
	*/

	//Add Gravity(1 pixel per frame)
	if (!paused && playMode) {

		player.update(level, Player::PLAYING);

		/*psy++;

		//Move player on the x axis
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			sx++;
		}

		if (Keyboard::isKeyPressed(Keyboard::A)) {
			sx--;
		}

		//Smooth the movement a bit
		sx *= 0.85f;
		px += round(sx) * 2;

		//Collisions on the x axis
		if (touching()) {
			if (round(sx * 100) / 100 < 0) {
				while (touching()) {
					sx = 0;
					px++;
				}
			}
			else if (round(sx * 100) / 100 > 0) {
				while (touching()) {
					sx = 0;
					px--;
				}

			}
		}

		//Add velocity
		py += psy;

		//Collisions in the y axis
		if (abs(psy) == psy) {
			while (touching()) {
				py--;
				psy = 0;
			}
		}
		else {
			while (touching()) {
				py++;
				psy = 0;
			}
		}

		//Touching ground condition
		py++;

		//Jump!
		if (Keyboard::isKeyPressed(Keyboard::W) && touching()) {
			psy = -35;
		}

		py--;

		if (py > level.getSize().y * 100 - 50) {
			kill();
		}*/

		setCam();


	}
	else if (!playMode && !paused) {

		setPlaceTile();

		player.update(level, Player::EDITOR);

		
		/*//Move player on the x axis
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			sx++;
		}

		if (Keyboard::isKeyPressed(Keyboard::A)) {
			sx--;
		}

		//Move player on the y axis
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			sy++;
		}

		if (Keyboard::isKeyPressed(Keyboard::W)) {
			sy--;
		}

		//Smooth the movement a bit
		sx *= 0.85f;
		px += round(sx) * 2;

		sy *= 0.85f;
		py += round(sy) * 2;

		//Collisions for getting out of the map
		if (px < 100) {
			px = 100;
		}
		if (px > level.getSize().x * 100 - 200) {
			px = level.getSize().x * 100 - 200;
		}

		if (py < 100) {
			py = 100;
		}
		if (py > level.getSize().y * 100 - 100 && !playMode) {
			py = level.getSize().y * 100 - 100;
		}*/


		//Place the tile when the left click is pressed
		if (Mouse::isButtonPressed(Mouse::Left)) {
			//Do things in multiple frames
			int x = mousePos().x + camX;
			int y = mousePos().y + camY;

			x = round(x / 100);
			y = round(y / 100);

			button->addButton(20.f, 960.f, 200.f, 100.f, "");
			if (button->state == Button::IDLE) {
				level.setTile(x, y, Level::tile(brush.t, brush.dir, brush.tr));
				refreshTile(Vector2i(x, y));
			}

			if (!MousePressed) {
				//Do things once until mouse released

			}
			MousePressed = true;
		}
		else {
			MousePressed = false;
		}

		//Move the camera
		setCam();
	}
}

void Game::setCam() {
	camX -= (camX - (player.getPosition().x - 860)) / 7;

	camY -= (camY - (player.getPosition().y - 490)) / 5;

	if (camX < 100) {
		camX = 100;
	}
	else if (camX > level.getSize().x * 100 - 2020) {
		camX = level.getSize().x * 100 - 2020;
	}

	if (camY < 100) {
		camY = 100;
	}
	else if (camY > level.getSize().y * 100 - 1080) {
		camY = level.getSize().y * 100 - 1080;
	}
}

bool Game::touching() {
	bool ret = level.getTile((px - 0) / 100, (py + 1) / 100).type != 0 && level.getTile((px - 0) / 100, (py + 1) / 100).transparent == false || level.getTile((px - 1) / 100 + 1, (py - 0) / 100 + 1).type != 0 && level.getTile((px - 1) / 100 + 1, (py - 0) / 100 + 1).transparent == false || level.getTile((px - 1) / 100 + 1, (py + 1) / 100).type != 0 && level.getTile((px - 1) / 100 + 1, (py + 1) / 100).transparent == false || level.getTile((px - 0) / 100, (py - 0) / 100 + 1).type != 0 && level.getTile((px - 0) / 100, (py - 0) / 100 + 1).transparent == false;
	return ret;
}

void Game::setPlaceTile() {
	if (Keyboard::isKeyPressed(Keyboard::T)) {

		if (Tpressed == false) {
			trBrush = !trBrush;
		}

		Tpressed = true;
	}
	else {
		Tpressed = false;
	}

	brush.tr = trBrush;

	if (brush.t == 8) {
		brush.tr = true;
	}

	if (Keyboard::isKeyPressed(Keyboard::Up)) {

		if (UpPressed == false) {
			brush.t++;
		}

		UpPressed = true;
	}
	else {
		UpPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::Down)) {

		if (DownPressed == false) {
			brush.t--;
		}

		DownPressed = true;
	}
	else {
		DownPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::Left)) {

		if (LeftPressed == false) {
			brush.dir += 270;
		}

		LeftPressed = true;
	}
	else {
		LeftPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::Right)) {

		if (RightPressed == false) {
			brush.dir += 90;
		}

		RightPressed = true;
	}
	else {
		RightPressed = false;
	}

	if (brush.t < 0) {
		brush.t = 0;
	}
}

void Game::render() {

	//Clear the window
	window.clear(Color(0, 255, 255, 255));

	//Draw everything
	switch (scene) {
	case MAIN_MENU:
		mmenuRender();
		break;
	case SETTINGS_MENU:
		settingsRender();
		break;
	case GAME:
		gameRender();
		break;
	}

	//Show on-screen everything
	window.display();
}

void Game::mmenuRender() {

	button->addButton(0, 0, 200.f, 100.f, "Play Game");
	if (button->state == Button::PRESSED) {
		loadCode();
		//if(codeLoaded)
			scene = GAME;
	}
	button->render(window);

	button->addButton(0, 100.f, 200.f, 100.f, "Settings");
	if (button->state == Button::PRESSED) {
		scene = SETTINGS_MENU;
	}
	button->render(window);

	button->addButton(0, 200.f, 200.f, 100.f, "Exit Game");
	if (button->state == Button::PRESSED) {
		saveCode();
		window.close();
	}
	button->render(window);
}

void Game::settingsRender() {
	button->addButton(0, 0, 300.f, 150.f, "Back To Game");
	if (button->state == Button::PRESSED) {
		scene = GAME;
	}
	button->render(window);

	button->addButton(0, 150.f, 300.f, 150.f, "Reset World");
	if (button->state == Button::PRESSED) {
		genLevel();
	}
	button->render(window);

	button->addButton(0, 300.f, 300.f, 150.f, "Tile Arraging");
	if (button->state == Button::PRESSED) {
		TileArrange = !TileArrange;
	}
	button->render(window);

	button->addButton(0, 500.f, 300.f, 150.f, "Save Level");
	if (button->state == Button::PRESSED) {
		saveCode();
	}
	button->render(window);

	button->addButton(0, 650.f, 300.f, 150.f, "Load Level");
	if (button->state == Button::PRESSED) {
		loadCode();
	}
	button->render(window);

	button->addButton(0, 850.f, 300.f, 150.f, "Reset Player Pos");
	if (button->state == Button::PRESSED) {
		kill();
	}
	button->render(window);

	button->addButton(350.f, 0.f, 300.f, 150.f, "Add Transparency");
	if (button->state == Button::PRESSED) {
		passTransparency = !passTransparency;
	}
	button->render(window);
}

void Game::gameRender() {
	//Tile grid render

	for (int x = 0; x < level.getSize().x; x++) {
		for (int y = 0; y < level.getSize().y; y++) {
			if (level.getTile(x, y).type != 0) {
				if (!(x * 100 - camX > 1920 || y * 100 - camY > 1080 || x * 100 - camX < -100 || y * 100 - camY < -100)) {
					int xpos = x;
					int ypos = y;
					if (currentTex != level.getTile(xpos, ypos).type) {
						setTex(level.getTile(xpos, ypos).type);
					}
					tile.setRotation(level.getTile(xpos, ypos).dir);
					//Center the rotation
					if (level.getTile(x, y).dir % 360 == 90) {
						xpos++;
					}
					if (level.getTile(x, y).dir % 360 == 180) {
						xpos++;
						ypos++;
					}
					if (level.getTile(x, y).dir % 360 == 270) {
						ypos++;
					}

					tile.setPosition(xpos * 100 - camX, ypos * 100 - camY);
					//Add transparency if the block is traspasable
					if (passTransparency) {
						if (level.getTile(x, y).transparent) {
							tile.setColor(Color(255, 255, 255, 200));
						}
						else {
							tile.setColor(Color(255, 255, 255, 255));
						}
					}
					window.draw(tile);
				}
			}
		}
	}

	//Player render
	setTex(0);
	tile.setColor(Color(255, 255, 255, 255));
	tile.setRotation(0.f);
	tile.setPosition(player.getPosition().x - camX, player.getPosition().y - camY);
	window.draw(tile);

	//Render the tile in the mouse
	int x = mousePos().x + camX;
	int y = mousePos().y + camY;
	x = round(x / 100);
	y = round(y / 100);

	setTex(brush.t);

	button->addButton(20.f, 960.f, 200.f, 100.f, "Play/Editor");
	if (button->state == Button::PRESSED) {
		sx = 0.f;
		psy = 0.f;
		sy = 0.f;
		playMode = !playMode;
	}
	button->render(window);

	//Center the rotation
	tile.setRotation(brush.dir);
	if (brush.dir % 360 == 90) {
		x++;
	}
	if (brush.dir % 360 == 180) {
		x++;
		y++;
	}
	if (brush.dir % 360 == 270) {
		y++;
	}

	tile.setColor(Color(255, 255, 255, 127));
	tile.setPosition(x * 100 - camX, y * 100 - camY);

	if (brush.t != 0) {
		if (!playMode) {
			window.draw(tile);
		}
	}

	if (paused) {

		//Pause Menu Background
		window.draw(pauseBackground);

		//Buttons
		button->addButton(640.f, 340.f, 640.f, 100.f, "Back To Game");
		if (button->state == Button::PRESSED) {
			paused = false;
		}
		button->render(window);

		button->addButton(640.f, 490.f, 640.f, 100.f, "Settings");
		if (button->state == Button::PRESSED) {
			scene = 1;
			//paused = false;
		}
		button->render(window);

		button->addButton(640.f, 640.f, 640.f, 100.f, "Main Menu");
		if (button->state == Button::PRESSED) {
			scene = 0;
			//window.close();
		}
		button->render(window);
	}

	tile.setColor(Color(255, 255, 255, 255));
}


void Game::kill() {
	px = 200;
	py = 200;
	psy = 0;
	sx = 0.f;
}

//Private functions

void Game::initVariables() {
	genLevel();

	codeLoaded = false;

	brush.t = 1;
	brush.dir = 0;
	brush.tr = false;
	paused = false;

	playMode = false;

	kill();

	TileArrange = true;

	trBrush = false;

	scene = 0;

	passTransparency = false;

	readFile.open("Assets/INFO.txt", ios::in);

	if (readFile.fail()) {
		MessageBox(0, L"The program couldn't find the INFO.txt file. Be sure that is written well.", L"Error!", MB_OK | MB_ICONERROR);
		window.close();
	}

	while (!readFile.eof()) {
		getline(readFile, Info);
	}
	resolution = strToInt(Info);
}

void Game::initWindow() {
	//Set the Framerate Limit
	window.setFramerateLimit(fps);

	//Set the viewport to be compatible with every resolution (like if you have an 8k monitor you'll see more than a 2k one)
	view.reset(FloatRect(0, 0, 1920, 1080));
	window.setVerticalSyncEnabled(true);
	window.setView(view);
}

void Game::initGrid() {
	//Import the texture atlas
	tileT.loadFromFile("Assets/Textures/TexturesAtlas.png");

	//Set the tile size
	tile.setScale(100.f / resolution, 100.f / resolution);
	tile.setTexture(tileT);
	tile.setRotation(0);

	//Set the pause menu background texture
	pauseBackTex.loadFromFile("Assets/Textures/PauseBackground.png");
	pauseBackTex.setRepeated(true);

	//Set the sprite for the pause menu
	pauseBackground.setColor(Color(255, 255, 255, 240));
	pauseBackground.setScale(100.f / resolution, 100.f / resolution);
	pauseBackground.setTextureRect(IntRect(0, 0, 1920, 1080));
	pauseBackground.setTexture(pauseBackTex);
}

void Game::genLevel() {

	for (int i = 0; i < level.getSize().x; i++) {
		level.setTile(i, 0, Level::tile(4, 0));
		level.setTile(i, level.getSize().y - 1, Level::tile(1, 0));
	}

	for (int i = 1; i < level.getSize().y; i++) {

		level.setTile(0, i, Level::tile(4, 0));
		level.setTile(level.getSize().x - 1, i, Level::tile(4, 0));
	}

	//Fill the rest with air
	for (int x = 1; x < level.getSize().x - 1; x++) {
		for (int y = 1; y < level.getSize().y - 1; y++) {
			level.setTile(x, y, Level::tile(0, 0));
		}
	}

}

void Game::saveCode() {
	level.safeFile("world1.gmm");
}

void Game::loadCode() {

	//Code for getting the list of saves

	codeLoaded = false;

	string path = "Assets/Saves/";
	string ext = ".gmm";
	vector<string> files;
	for (const auto& entry : fs::directory_iterator(path))
		if(entry.path().extension() == ext)
			files.push_back(entry.path().filename().string());

	level.loadFile("world1.gmm");
}

void Game::setTex(int num) {
	int res = resolution;
	int y = num / res;
	tile.setTextureRect(IntRect(num * res % (res * 16), y * res, res, res));
	currentTex = num;
}

int Game::strToInt(string s) {
	return stoi(s);
}

float Game::lerp(float a, float b, float t) {
	return a + t * (b - a);
}

Vector2f Game::mousePos() {
	return Vector2f(Mouse::getPosition().x * (1920.f / videoMode.getDesktopMode().width), Mouse::getPosition().y * (1080.f / videoMode.getDesktopMode().height));
}

void Game::refreshTile(Vector2i tPos, bool o) {
	if (TileArrange == true) {

		if (!o) {
			refreshTile(tPos + Vector2i(1, 0), true);
			refreshTile(tPos - Vector2i(1, 0), true);
			refreshTile(tPos + Vector2i(0, 1), true);
			refreshTile(tPos - Vector2i(0, 1), true);
		}

		int tileTex = level.getTile(tPos).type;
		bool tileTransparent = level.getTile(tPos).transparent;



		int bu = level.getTile(tPos + Vector2i(0, -1)).type;
		int br = level.getTile(tPos + Vector2i(1, 0)).type;
		int bd = level.getTile(tPos + Vector2i(0, 1)).type;
		int bl = level.getTile(tPos + Vector2i(-1, 0)).type;

		if (bu != 0 && bu < 4) { // 4 is the max grass tile + 1
			bu = 1;
		}
		if (br != 0 && br < 4) { // 4 is the max grass tile + 1
			br = 1;
		}
		if (bd != 0 && bd < 4) { // 4 is the max grass tile + 1
			bd = 1;
		}
		if (bl != 0 && bl < 4) { // 4 is the max grass tile + 1
			bl = 1;
		}

		int code = bu * 1000 + br * 100 + bd * 10 + bl * 1;

		if (tileTex > 0 && tileTex < 4) {

			/*
				code works like this:
					up right down left

				example:
					up = 1, the rest = 0
					code would be: 1000
			*/

			if (bu == 1) {
				level.setTile(tPos, Level::tile(3, 0, tileTransparent));
			}
			else {
				level.setTile(tPos, Level::tile(1, 0, tileTransparent));
			}
		}
	}
}

void Game::test() {
	cout << "aaa" << endl;
}