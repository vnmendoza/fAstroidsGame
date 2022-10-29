#include "Weapon.h"

Weapon::Weapon()
{
	fireRate = 2;
	lastShotTime = ofGetElapsedTimef();
	type = dne;
	heading = glm::vec3(0);
}

bool Weapon::shouldShoot()
{
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

void Weapon::shoot()
{
	Bullet b;
	b.setup(pos, img);


}



//~~~~~~~~~sml_Cannon~~~~~~~~~~

Sml_Cannon::Sml_Cannon() : Weapon()
{
	
}

void Sml_Cannon::shoot()
{

}
