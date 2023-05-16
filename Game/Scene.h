#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include "lib.h"
#include "Game.h"

class Scene
{
public:

	struct func {
		func(string _name, function<void()> _f) {
			name = _name;
			f = _f;
		}

		string name;
		function<void()> f;
	};

	Scene(int numScenes);

	void addScene(func f);

private:
	vector<func> sceneUpdates;
};

#endif