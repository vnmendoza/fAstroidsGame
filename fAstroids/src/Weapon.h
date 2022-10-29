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
	glm::vec3* pos;
	vector <Bullet> bullets;
public:
	Weapon();
	bool shouldShoot();
	virtual void shoot();
	void update();
	void setWeapon(wType type);
	void setPos(glm::vec3* position);

	glm::vec3 heading;
};

class Sml_Cannon: public Weapon
{
public:
	Sml_Cannon();
	void shoot();
};

class Lrg_Cannon : public Weapon
{

};
