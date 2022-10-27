#pragma once
#include "ofMain.h"
#include "Bullet.h"


enum wType{dne, sCannon, lCannon, homing, mines, razor, muon, particleBeam };

class Weapon
{
protected:
	float fireRate, lastShotTime;
	wType type;
	ofImage* img;
	//vector <Bullet> bullets;
public:
	Weapon();
	bool shouldShoot();
	void shoot();
	void update();
	void setWeapon(wType type);
};
