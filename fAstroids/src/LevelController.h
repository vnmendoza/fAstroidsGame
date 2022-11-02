#pragma once
#include "ofMain.h"
#include "Agent.h"

class LevelController
{
private:
	float startTime;
	float spawnRate;
	int spawnAmount,size;
	int level;
	vector<Enemy*> enemies;
	vector<Bullet> bullets;
public:
	LevelController();
	bool shouldSpawn();
	void update(float spawn_rate, int spawn_amount);
	void update(float spawn_rate, int spawn_amount, int lvl);
	void updateEnemies(float lifeSpan, int spd, float fireRate,glm::vec3 heroPosition);
	void setSpawnAmount(int amount);
	void setLifespan(float lifespan);
	int getSpawnAmount();
	int getLevel();
	void setLevel(int lvl);
	//void setEnemies(vector<Enemy> *nme);
	void spawnEnemies();
	void spawnTriangle();
	void spawnSquare();
	void spawnHexagon();
	void drawEnemies();
};

