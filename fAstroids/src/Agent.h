#pragma once
#include "ofMain.h"

class Agent
{
protected:
	glm::vec3 pos, vel;
	int speed, nEnergy;
	ofColor color;
	float width, rotation;
	glm::vec3 scaler = glm::vec3(1.0, 1.0, 1.0);
	ofImage* sprite;
	float imgWidth, imgHeight;
public:
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
	void setNRG(int energy);
	void move();
};

class Enemy : public Agent
{
protected:
	int sides;
	glm::vec3 direction;
	float lifespan;
	float birthday;
public:
	Enemy();
	void setLifespan(float lspn);
	void setup(int shapeSize, int numSides);
	void update();
	float getBirthday();
	float getLifespan();
};






