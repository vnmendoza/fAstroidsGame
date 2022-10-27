#pragma once
#include "ofMain.h"
#include "Agent.h"

class LevelController
{
private:
	float startTime;
	float spawnRate;
	int spawnAmount;
	int level;
	vector<Enemy> *enemies;
public:
	LevelController();
	bool shouldSpawn();
	void update(float spawn_rate, int spawn_amount);
	void update(float spawn_rate, int spawn_amount, int lvl);
	void setSpawnAmount(int amount);
	int getSpawnAmount();
	int getLevel();
	void setLevel(int lvl);
	void setEnemies(vector<Enemy> *nme);
};

