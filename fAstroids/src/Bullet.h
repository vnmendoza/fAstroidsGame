#pragma once
#include "ofMain.h"

class Bullet
{
protected:
	glm::vec3 pos,vel;
	float speed, rotation, accuracy;
	float imgWidth,imgHeight;
	float damage;
	ofImage* img;
	bool fromPlayer;
	glm::vec3 scaler = glm::vec3(1.0, 1.0, 1.0);
public:
	Bullet();
	void setup(glm::vec3 position,  ofImage* bullet_image);
	void setup(glm::vec3* pposition,  ofImage* bullet_image);
	void draw();
	glm::vec3 getPos();
	float getWidth();
	float getDamage();
	void setDamage(float);
	glm::mat4 getMatrix();
	void setDirection(glm::vec3 mousePos);
	void move();
	void update();
};

class CannonBullet : public Bullet
{
protected:
public:
	CannonBullet();

};
