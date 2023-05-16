#include "Scene.h"

Scene::Scene(int numScenes)
{
}

void Scene::addScene(func f)
{
	sceneUpdates.push_back(f);
}
