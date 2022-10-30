#include "LevelController.h"

LevelController::LevelController()
{
	startTime = ofGetElapsedTimef();
	spawnRate = 2.0;
	spawnAmount = 1;
	level = 0;
	size = 40;
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
	//if (shouldSpawn())
		//spawnEnemies();
}


void LevelController::updateEnemies(float lifeSpan, int spd, float fireRate,glm::vec3 heroPos)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->setHeroPos(heroPos);
		enemies[i]->setLifespan(lifeSpan);
		enemies[i]->setSpeed(spd);
		enemies[i]->setFireRate(fireRate);
		enemies[i]->update();
		if (ofGetElapsedTimef() - enemies[i]->getBirthday() > enemies[i]->getLifespan())
			enemies.erase(enemies.begin() + i);
	}
}



void LevelController::update(float spawn_rate, int spawn_amount, int lvl)
{
	level = lvl;
	update(spawn_rate, spawn_amount);

}

void LevelController::setLifespan(float ls)
{
	for (auto e : enemies)
		e->setLifespan(ls);
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

void LevelController::spawnEnemies()
{
	for (int i = 0; i < spawnAmount; i++)
	{
		switch(level)
		{
		case 1:
			spawnTriangle();
			break;
		case 2:
			spawnSquare();
			break;
		case 3:
			spawnHexagon();
			break;
		default:
			break;
			
				

		}

	}

}
void LevelController::spawnTriangle()
{
	Triangle* t = new Triangle();
	t->setup(size, 3);
	enemies.push_back(t);

}

void LevelController::spawnSquare()
{
	Square* s = new Square();
	s->setup(size, 4);
	s->weapon.setWeapon(sCannon);
	//s->setBulletImage()
	enemies.push_back(s);

}

void LevelController::spawnHexagon()
{
	Hexagon* h = new Hexagon();
	h->setup(size, 6);
	h->weapon.setWeapon(mines);
	enemies.push_back(h);
}
void LevelController::drawEnemies()
{
	for (auto e : enemies)
		e->draw();
}
