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
	//for (ParticleEmitter& p : emitters)
		//p.update();
	pArr[0].update();
	//pArr[1].update();
	if (shouldSpawn())
		spawnEnemies();
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
		if (enemies[i]->shouldShoot())
			bullets.push_back(enemies[i]->shoot(heroPos));
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
			spawnTriangle();
			spawnSquare();
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
	cout << "pushing tri into enemies" << endl;
	//t->weapon.bullets = &bullets;
	enemies.push_back(t);

}

void LevelController::spawnSquare()
{
	Square* s = new Square();
	s->setup(size, 4);
	s->bulletImg = gBullImg;
	//cout<< "square: " <<  s->bulletImg->getWidth()<<endl;
	//s->weapon.setWeapon(sCannon);
	//s->setBulletImage()
	enemies.push_back(s);

}

void LevelController::spawnHexagon()
{
	Hexagon* h = new Hexagon();
	h->setup(size, 6);
	h->bulletImg = mineImg;
	//h->weapon.setWeapon(mines);
	enemies.push_back(h);
}
void LevelController::drawEnemies()
{
	for (auto e : enemies)
		e->draw();
}

void LevelController::drawBullets()
{
	for (Bullet& b : bullets)
		b.draw();
}

void LevelController::updateBullets()
{
	for (Bullet& b : bullets)
		b.update();
}


void LevelController::bulletCollisions()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		bool deleteBullet = false;
		//check if OOB
		if (bullets[i].getPos().y < 0 ||
			bullets[i].getPos().y > ofGetHeight() ||
			bullets[i].getPos().x < 0 ||
			bullets[i].getPos().x > ofGetWidth())
		{
			//cout << "oob\n";
			deleteBullet = true;
		}	
		//check If bullet hits any agents

		//check if player Bullet hits enemy
		if (bullets[i].fromPlayer && !deleteBullet)
		{
			for (int e = 0; e < enemies.size(); e++)
			{
				float bullet2Enemy = glm::distance(bullets[i].getPos(), enemies[e]->getPos());
				float imgWidthCompensation = (enemies[e]->getWidth() + bullets[i].getWidth()) / 2;
				if (bullet2Enemy < imgWidthCompensation) {
					glm::vec3 enemyPos = enemies[e]->getPos();
					//cout << enemyPos << endl;
					particleExplosion(enemyPos);
					hero->gainNRG();
					deleteBullet = true;
					enemies.erase(enemies.begin() + e);
					expSound->play();
					//emitters[e].start();
					//emitters[e+1].start();
					pArr[0].start();
				//	pArr[1].start();
				}
			}
			

		}
		//check if enemy bullet hits player
		else if(!bullets[i].fromPlayer && !deleteBullet)
		{
				float bullet2Hero = glm::distance(bullets[i].getPos(), hero->getPos());
				float imgWidthCompensation = (hero->getWidth() + bullets[i].getWidth()) / 2;
				if (bullet2Hero < imgWidthCompensation) {
					hero->loseNRG();
					deleteBullet = true;
				}


		}
		
		if(deleteBullet)
			bullets.erase(bullets.begin() + i);
	}
}

void LevelController::particleExplosion(glm::vec3 position)
{
	ParticleEmitter emitter, orbitalEmitter;
	TurbulenceForce* turbForce;
	GravityForce* gravityForce;
	ImpulseRadialForce* radialForce;
	turbForce = new TurbulenceForce(ofVec3f(-20, -20, -20), ofVec3f(20, 20, 20));
	gravityForce = new GravityForce(ofVec3f(0, -10, 0));
	radialForce = new ImpulseRadialForce(1000.0);

	emitter.sys->addForce(turbForce);
	emitter.sys->addForce(gravityForce);
	emitter.sys->addForce(radialForce);

	orbitalEmitter.sys->addForce(turbForce);
	orbitalEmitter.sys->addForce(gravityForce);
	orbitalEmitter.sys->addForce(radialForce);
	emitter.setPos(position);
	orbitalEmitter.setPos(position);
	pArr[0] = emitter;
	pArr[1] = orbitalEmitter;

	//emitters.push_back(emitter);
	//emitters.push_back(orbitalEmitter);
	//cout << "emitters size: " << emitters.size() << endl;
}

void LevelController::drawParticles()
{
	//for (ParticleEmitter& p : emitters)
		//p.draw();
	pArr[0].draw();
	//pArr[1].draw();

}

void LevelController::agentCollisions()
{
	for (int e = 0; e < enemies.size(); e++)
	{
		float enemy2Hero = glm::distance(enemies[e]->getPos(), hero->getPos());
		float imgWidthCompensation = (hero->getWidth() + enemies[e]->getWidth()) / 2;
		if (enemy2Hero < imgWidthCompensation) {
			hero->loseNRG();
			enemies.erase(enemies.begin() + e);
			collideSound->play();

		}
	}

}

void LevelController::collisionCheck()
{
	bulletCollisions();
	agentCollisions();
}

void LevelController::restart()
{
	enemies.clear();
	bullets.clear();
}

