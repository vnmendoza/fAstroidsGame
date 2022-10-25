#include "Weapon.h"

Weapon::Weapon()
{
	fireRate = 2;
	lastShotTime = ofGetElapsedTimef();
	type = dne;
}

bool Weapon::shouldShoot()
{
	return false;
}
