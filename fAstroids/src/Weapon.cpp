#include "Weapon.h"

ofImage gBullet;

Weapon::Weapon()
{
	fireRate = 2;
	lastShotTime = ofGetElapsedTimef();
	type = dne;
	heading = glm::vec3(0);
}

bool Weapon::shouldShoot()
{
	//cout << "shouldShoot\n";
	if (fireRate < ofGetElapsedTimef() - lastShotTime)
	{
		lastShotTime = ofGetElapsedTimef();
		return true;
	}
			return false;
}

void Weapon::setWeapon(wType t)
{
	type = t;
}

void Weapon::setPos(glm::vec3* position)
{
	pos = position;
}

void Weapon::shoot(glm::vec3 targetPosition)
{
	cout << "shooting\n";
	Bullet b;
	b.setup(pos, img);
	b.setDirection(targetPosition);
	bullets->push_back(b);
}

void Weapon::update(glm::vec3 tp)
{
	if (shouldShoot())
		shoot(tp);
	//tell each bullet to update
	for (Bullet& b : *bullets)
		b.update();
	
}

void Weapon::setBullets(vector <Bullet>* blt)
{
	//bullets = blt;
}

void Weapon::draw()
{
	for (Bullet& b : *bullets)
		b.draw(); 
}

void Weapon::setImage(ofImage* image)
{
	img = image;
}


//~~~~~~~~~sml_Cannon~~~~~~~~~~

Sml_Cannon::Sml_Cannon() : Weapon()
{
	gBullet.load("greenCannon.png");
	img = &gBullet;
}



