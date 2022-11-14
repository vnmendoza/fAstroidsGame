#pragma once
#include "ofMain.h"
#include "Bullet.h"


enum wType{dne, sCannon, lCannon, homing, mines, razor, muon, particleBeam };
//ofImage gBullet;

class Weapon
{
protected:
	float fireRate, lastShotTime;
	wType type;
	ofImage* img;

	glm::vec3* pos;
	glm::vec3 targetPos;
public:
	Weapon();
	vector <Bullet>* bullets;
	bool shouldShoot();
	void shoot(glm::vec3 targetPos);
	void update(glm::vec3 tagetPosition);
	void setWeapon(wType type);
	void setPos(glm::vec3* position);
	void setTargetPos(glm::vec3 targetPosition);
	void setImage(ofImage* image);
	void draw();
	void setBullets(vector <Bullet>* blt);

	glm::vec3 heading;
};

class Sml_Cannon: public Weapon
{
public:
	Sml_Cannon();
};

class Lrg_Cannon : public Weapon
{

};
