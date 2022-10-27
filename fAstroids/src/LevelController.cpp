#include "LevelController.h"

LevelController::LevelController()
{
	startTime = ofGetElapsedTimef();
	spawnRate = 2.0;
	spawnAmount = 1;
	level = 0;
}

bool LevelController::shouldSpawn()
{
	if (ofGetElapsedTimef() - startTime > spawnRate)
	{
		startTime = ofGetElapsedTimef();
		return true;
	}
	return false;
}

void LevelController::update(float spawn_rate, int spawn_amount)
{
	spawnRate = spawn_rate;
	spawnAmount = spawn_amount;
}

void LevelController::update(float spawn_rate, int spawn_amount, int lvl)
{
	level = lvl;
	update(spawn_rate, spawn_amount);
}

void LevelController::setSpawnAmount(int amount)
{
	spawnAmount = amount;
}

int LevelController::getSpawnAmount()
{
	return spawnAmount;
}

int LevelController::getLevel()
{
	return level;
}

void LevelController::setLevel(int lvl)
{
	level = lvl;
}

void LevelController::setEnemies(vector <Enemy> *nme)
{
	enemies = nme;
}

