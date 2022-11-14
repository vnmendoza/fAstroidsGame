#pragma once
#include "ofMain.h"
#include "Agent.h"
#include "ParticleEmitter.h"

class LevelController
{
private:
	float startTime;
	float spawnRate;
	int spawnAmount,size;
	int level;
	vector<Enemy*> enemies;
	ParticleEmitter pArr[2];
	//vector<ParticleEmitter> emitters;
public:
	LevelController();
	Hero* hero;
	ofImage* gBullImg, *mineImg, *hBullImg;
	vector<Bullet> bullets;
	ofSoundPlayer *collideSound, *expSound;
	bool shouldSpawn();
	void update(float spawn_rate, int spawn_amount);
	void update(float spawn_rate, int spawn_amount, int lvl);
	void updateEnemies(float lifeSpan, int spd, float fireRate,glm::vec3 heroPosition);
	void setSpawnAmount(int amount);
	void setLifespan(float lifespan);
	int getSpawnAmount();
	int getLevel();
	void setLevel(int lvl);
	void setgBullImg(ofImage* img);
	//void setEnemies(vector<Enemy> *nme);
	void spawnEnemies();
	void spawnTriangle();
	void spawnSquare();
	void spawnHexagon();
	void drawEnemies();
	void drawBullets();
	void updateBullets();
	void bulletCollisions();
	void agentCollisions();
	void collisionCheck();
	void particleExplosion(glm::vec3 position);
	void drawParticles();
	void restart();

};

