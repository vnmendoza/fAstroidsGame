#include "Agent.h"


Agent::Agent()
{
	width = 10;
	speed = 10;
	rotation = 0;
	nEnergy = 5;
}

void Agent::update()
{
	move();
	//weapon.fire();
}

void Agent::move()
{

}

void Agent::setShapeColor(ofColor c)
{
	color = c;
}

ofColor Agent::getColor()
{
	return color;
}

glm::mat4 Agent::getMatrix()
{
	glm::mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(pos));
	glm::mat4 rot = glm::rotate(glm::mat4(1.0), glm::radians(rotation), glm::vec3(0, 0, 1));
	glm::mat4 scale = glm::scale(glm::mat4(1.0), scaler);
	return (trans * rot * scale);
}

int Agent::getSpeed()
{
	return speed;
}

void Agent::setSpeed(int s)
{
	speed = s;
}

void Agent::setPos(glm::vec3 p)
{
	pos = p;
}


glm::vec3 Agent::getPos()
{
	return pos;
}
bool Agent::collisionCheck(glm::vec3 objPos, float objWidth)
{
	//see if were touching something
	//if its an enemy 
	float obj2me = glm::distance(objPos, pos);
	float imgWidthCompensation = (objWidth + width);
	return obj2me < imgWidthCompensation;


}

float Agent::getWidth()
{
	return width;
}

glm::vec3 Agent::heading()
{
	glm::vec3 triPoint = translate(glm::vec3(0, -10, 0));
	glm::vec3 center = translate(glm::vec3(0, 0, 0));
	return glm::normalize(triPoint - center);
}

void Agent::drawHeading()
{
	glm::vec3 triPoint = translate(glm::vec3(0, -120, 0));
	glm::vec3 center = translate(glm::vec3(0, 0, 0));
	ofDrawLine(triPoint, center);
}

glm::vec3 Agent::translate(glm::vec3 trans)
{
	return glm::vec3(getMatrix() * glm::vec4(trans, 1.0));
}

void Agent::setup(ofImage* mySprite)
{
	sprite = mySprite;
	imgWidth = sprite->getWidth() * 0.5;
	imgHeight = sprite->getHeight() * 0.5;
	sprite->setAnchorPoint(imgWidth / 2, imgHeight / 2);
	speed = 10;
	nEnergy = 5;
	width = imgWidth / 3;
}

void Agent::draw()
{
	ofPushMatrix();
	ofSetColor(color);
	ofMultMatrix(getMatrix());
	sprite->setAnchorPoint(imgWidth / 2, imgHeight / 2);
	sprite->draw(0, 0, imgWidth, imgHeight);
	ofPopMatrix();
}

// ~~~~~~~~~~~~~~HERO~~~~~~~~~~~~
Hero::Hero() : Agent()
{
	width = 5;
	speed = 5;
	nEnergy = 5;
	is_up_pressed = false;
	is_left_pressed = false;
	is_down_pressed = false;
	is_right_pressed = false;

}



void Hero::setRotationSpeed(float rots)
{
	rotSpeed = rots;
}

void Hero::update()
{
	move();
	wallCollisions();
	//agentCollisions();
}


void Hero::wallCollisions()
{
	if (pos.x > ofGetWidth() - width) {
		pos.x = ofGetWidth() - width;
	}

	if (pos.x < width) {
		pos.x = width;
	}

	if (pos.y > ofGetHeight() - width) {
		pos.y = ofGetHeight() - width;
	}

	if (pos.y < width) {
		pos.y = width;
	}

}


void Hero::setSize(float size)
{
	scaler = glm::vec3(size, size, size);
	imgWidth = sprite->getWidth() * size;
	imgHeight = sprite->getHeight() * size;
}

void Hero::setLeftPressed(bool b)
{
	is_left_pressed = b;
}

void Hero::setUpPressed(bool b)
{
	is_up_pressed = b;
}

void Hero::setDownPressed(bool b)
{
	is_down_pressed = b;
}

void Hero::setRightPressed(bool b)
{
	is_right_pressed = b;
}

void Hero::loseNRG()
{
	nEnergy--;
}

int Hero::getNRG()
{
	return nEnergy;
}

void Hero::setNRG(int energy)
{
	nEnergy = energy;
}

void Hero::move()
{
	if (is_up_pressed)
	{
		//activate fwd thruster
		vel = speed * heading();
		pos += vel;
	}
	if (is_left_pressed)
	{
		//activate lft thruster
		rotation -= rotSpeed;
	}
	if (is_down_pressed)
	{
		vel = speed * heading();
		pos -= vel;
	}
	if (is_right_pressed)
	{
		rotation += rotSpeed;
	}
}


//~~~~~~~~~~~~~~~~~ENEMY~~~~~~~~~~~~~~~~~~


Enemy::Enemy()
{
	sides = 3;
	width = 70;
	lifespan = 5;
	birthday = ofGetElapsedTimef();
}

float Enemy::getBirthday()
{
	return birthday;
}

float Enemy::getLifespan()
{
	return lifespan;
}

void Enemy::setLifespan(float lspn)
{
	lifespan = lspn;
}

void Enemy::setup(int shapeSize, int numSides)
{
	width = shapeSize;
	sides = numSides;
	rotation = ofRandom(0, 360);
	pos = glm::vec3(ofRandom(width, ofGetWindowWidth() - width), ofRandom(width, ofGetWindowHeight() - width), 0);
}

void Enemy::move()
{

}

//~~~~~~~~~~~~~~~~~~Triangle~~~~~~~~~~~~~~~~~~~~

Triangle::Triangle() {}

void Triangle::move()
{

}

void Triangle::move(glm::vec3 heroPos)
{

	direction = pos - heroPos;
	//normalize
	direction = glm::normalize(direction);
	//multiply by speed
	direction *= -speed;
	//add to position
	pos += direction;

}

void Triangle::update(glm::vec3 mousePos)
{
	move(mousePos);
	//rotation
	//cout << glm::degrees(glm::orientedAngle(heading(), direction, glm::vec3(0, 0, 1)))<<endl;
	ofSetColor(ofColor::gray);
	drawHeading();
	float deg = glm::degrees(glm::orientedAngle(glm::vec3(0, 1, 0), glm::normalize(direction), glm::vec3(0, 0, 1)));
	//the 30 is for a weird offset.
	rotation = deg - 30;
}

//~~~~~~~~~~~~~~~~~~~~~Pentagon~~~~~~~~~~~~~~~~~~

Pentagon::Pentagon() {
	//lastShotTime = ofGetElapsedTimef();
	//fireRate = 3;
	//weapon = 
}

void Pentagon::update()
{

}

void Pentagon::move()
{
	//stationary
}

