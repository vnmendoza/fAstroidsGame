#pragma once
#include "ofMain.h"

class Bullet
{
protected:
	glm::vec3 pos,vel;
	float speed, rotation;
	float imgWidth,imgHeight;
	float damage;
	ofImage* img;
	glm::vec3 scaler = glm::vec3(1.0, 1.0, 1.0);
public:
	Bullet();
	void setup(glm::vec3 position,  ofImage* bullet_image);
	virtual	void update();
	void draw();
	glm::vec3 getPos();
	float getWidth();
	float getDamage();
	void setDamage(float);
	glm::mat4 getMatrix();
	void setDirection(glm::vec3 mousePos);
};

class PlayerBullet : public Bullet
{
protected:
	float accuracy;
public:
	PlayerBullet();
	void move();
	void update();
};

class EnemyBullet : public Bullet
{
protected: 
public:
	EnemyBullet();

	void update();


};

