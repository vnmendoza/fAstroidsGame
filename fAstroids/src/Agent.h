#pragma once
#include "ofMain.h"
#include "Weapon.h"
#include "Bullet.h"
#include "ParticleEmitter.h"
#include "Particle.h"


class Agent
{

protected:
	glm::vec3 pos, velocity, acceleration,force;
	float mass, damping, angularForce, angularVelocity, angularAcceleration;
	bool thrust,retroRocket;
	int speed, nEnergy,maxNRG;
	ofColor color;
	float width, rotation;
	glm::vec3 scaler = glm::vec3(1.0, 1.0, 1.0);
	ofImage* sprite;
	float imgWidth, imgHeight;
public:
	//Weapon weapon;
	ofImage *bulletImg;
	bool alive;
	Agent();
	int getSpeed();
	void setSpeed(int);
	void setPos(glm::vec3);
	glm::vec3 getPos();
	bool collisionCheck(glm::vec3 objPos, float objWidth);
	float getWidth();
	glm::vec3 heading();
	void drawHeading();
	glm::vec3 translate(glm::vec3 trans);
	void setShapeColor(ofColor color);
	glm::mat4 getMatrix();
	ofColor getColor();
	void setup(ofImage* mySprite);
	void draw();
	void update();
	void move();
	void retrograde();
	void setRetroRocket(bool rr);
	bool getRetroRocket();
	void setRetroSpeed(float speed);
	Bullet shoot();
	Bullet shoot(glm::vec3 targetPos);

};

class Hero : public Agent
{
protected:
	float rotSpeed;
	bool is_left_pressed, is_right_pressed, is_down_pressed, is_up_pressed;
public:
	Hero();
	void wallCollisions();
	void update();
	void setSize(float size);
	void setRotationSpeed(float rotationSpeed);
	void setUpPressed(bool);
	void setLeftPressed(bool);
	void setDownPressed(bool);
	void setRightPressed(bool);
	void loseNRG();
	int getNRG();
	void gainNRG();
	void setNRG(int energy);
	void move();
	};

class Enemy : public Agent
{
protected:
	int sides;
	glm::vec3 direction,heroPos;
	float lifespan;
	float birthday;
	float fireRate, lastShotTime;

public:
	Enemy();
	void setLifespan(float lspn);
	void setup(int shapeSize, int numSides);
	void update();
	virtual void move();
	float getBirthday();
	float getLifespan();
	void setHeroPos(glm::vec3 heroPosition);
	virtual void draw();
	void setFireRate(float fr);
	void drawWeapon();
	virtual bool shouldShoot();
	Bullet shoot(glm::vec3 targetPos);
};


class Triangle : public Enemy
{
private:
public:
	Triangle();
	void move();
	void move(glm::vec3);
	void update(glm::vec3 heroPosition);
	void draw();
	void drawHeading();
	bool shouldShoot();
	//glm::vec3 heading();
};

//~~~~~~~~~Square

class Square : public Enemy
{
private:
public:
	Square();
	void move();
	//void update();
	void setBulletImage(ofImage *image);
};

class Hexagon : public Enemy
{
private:
public:
	Hexagon();
	void move();
	void update();
};


