#include "Agent.h"


Agent::Agent()
{
	width = 10;
	speed = 40;
	rotation = 0;
	nEnergy = 5;
	mass = 1.0;
	damping = 0.98;
	angularForce ,angularAcceleration,angularVelocity= 0;
	velocity, acceleration, force = glm::vec3(0);
	retroRocket = true;
	alive = true;
	cout << "agent created\n";
}

void Agent::update()
{
	move();
	//weapon.fire();
}

void Agent::move()
{
	float framerate = ofGetFrameRate();
	float dt = 1.0 / framerate;

	pos += (velocity * dt);
	glm::vec3 accel = acceleration;
	velocity += accel * dt;

	//cout << "force: " <<  angularForce << endl;
	//cout << "velocity: " << angularVelocity << endl;
	//cout << "accel: " << angularAcceleration << endl;
	//cout << "pos: " << pos << endl;
	rotation += (angularVelocity * dt);
	float a = angularAcceleration = 0;
	a += (angularForce * 1.0 / mass);
	angularVelocity += a * dt;

	if (retroRocket)
		retrograde();
}

void Agent::retrograde()
{
	velocity *= damping;
	angularVelocity *= damping;
}

void Agent::setRetroRocket(bool rr)
{
	retroRocket = rr;
}

bool Agent::getRetroRocket()
{
	return retroRocket;
}
void Agent::setRetroSpeed(float speed)
{
	damping = speed;
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
	glm::vec3 triPoint = (glm::vec3(0, -120, 0));
	glm::vec3 center = (glm::vec3(0, 0, 0));

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
	drawHeading();
	ofPopMatrix();
}



Bullet Agent::shoot()
{
	return shoot(heading());
}

Bullet Agent::shoot(glm::vec3 targetPosition)
{
	Bullet b;
	b.setup(pos, bulletImg);
	b.setDirection(targetPosition);
	return b;
}



// ~~~~~~~~~~~~~~HERO~~~~~~~~~~~~
Hero::Hero() : Agent()
{
	width = 5;
	speed = 5;
	nEnergy = 5;
	pos = glm::vec3(ofGetWidth() / 2, ofGetHeight() / 2, 0);
	rotation = 0;
	rotSpeed = 10;
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

		pos.x = width;
		//pos.x = ofGetWidth() - width;
	}

	if (pos.x < width) {
		//pos.x = width;
		pos.x = ofGetWidth() - width;
	}

	if (pos.y > ofGetHeight() - width) {
		pos.y = width;
		//pos.y = ofGetHeight() - width;
	}

	if (pos.y < width) {
		//pos.y = width;
		pos.y = ofGetHeight() - width;
	}

}


void Hero::setSize(float size)
{
	scaler = glm::vec3(size, size, size);
	imgWidth = sprite->getWidth() * size;
	imgHeight = sprite->getHeight() * size;
	width = imgWidth/5;
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
		velocity += speed * heading();
	}
	if (is_left_pressed)
	{
		//activate lft thruster
		angularVelocity -= rotSpeed;
	}
	if (is_down_pressed)
	{
		velocity -= speed * heading();
	}
	if (is_right_pressed)
	{
		angularVelocity += rotSpeed;
	}
	Agent::move();
}



//~~~~~~~~~~~~~~~~~ENEMY~~~~~~~~~~~~~~~~~~


Enemy::Enemy() : Agent()
{
	heroPos = glm::vec3(0);
	sides = 3;
	width = 70;
	lifespan = 5;
	birthday = ofGetElapsedTimef();
	cout << "enemy created\n";
	fireRate = 2;
	lastShotTime = ofGetElapsedTimef();

}

float Enemy::getBirthday()
{
	return birthday;
}

void Enemy::setHeroPos(glm::vec3 hp)
{
	heroPos = hp;
}

float Enemy::getLifespan()
{
	return lifespan;
}

void Enemy::setLifespan(float lspn)
{
	lifespan = lspn;
}

void Enemy::setFireRate(float fr)
{
	//TODO: Create firerate that goes to weapon
}

void Enemy::setup(int shapeSize, int numSides)
{
	width = shapeSize;
	sides = numSides;
	rotation = ofRandom(0, 360);
	pos = glm::vec3(ofRandom(width, ofGetWindowWidth() - width), ofRandom(width, ofGetWindowHeight() - width), 0);
}
void Enemy::update()
{
	//cout << "enemyUdate\n";
	move();
	//weapon.update(heroPos);
}
void Enemy::move()
{
	cout << "from Enemy\n";
}
void Enemy::draw()
{
	//weapon.draw();
	//if (alive)
	{
		ofPushMatrix();
		ofMultMatrix(getMatrix());
		ofSetCircleResolution(sides);
		ofDrawCircle(0, 0, width);
		ofPopMatrix();
	}
}

bool Enemy::shouldShoot()
{
	//cout << "shouldShoot\n";
	if (fireRate < ofGetElapsedTimef() - lastShotTime)
	{
		lastShotTime = ofGetElapsedTimef();
		return true;
	}
	return false;
}




//~~~~~~~~~~~~~~~~~~Triangle~~~~~~~~~~~~~~~~~~~~

Triangle::Triangle() : Enemy()
{
	sides = 3;
	angularAcceleration, angularVelocity, angularForce = 0;
	rotation = 0;
	cout << "triangle created\n";
}

void Triangle::move()
{
	direction = pos - heroPos;
	//normalize
	direction = glm::normalize(direction);
	//multiply by speed
	direction *= -speed;
	//add to position
	//pos += direction;
	//velocity = glm::vec3(0);
	velocity += direction;
	float deg = glm::degrees(glm::orientedAngle(heading(), glm::normalize(direction), glm::vec3(0, 0, 1)));
	//the 30 is for a weird offset.
	angularVelocity = deg + 30;
	Agent::move();
}

void Triangle::draw()
{
	drawHeading();
	Enemy::draw();
}
void Triangle::drawHeading()
{
	ofPushMatrix();
	ofMultMatrix(getMatrix());
	ofRotate(-30);
	Agent::drawHeading();
	ofPopMatrix();
}



//~~~~~~~~~~~~~~~~~~~~~Square~~~~~~~~~~~~~~~~~~

Square::Square() {
	//lastShotTime = ofGetElapsedTimef();
	//fireRate = 3;
	//weapon = 
	cout << "sqr created\n";
	//weapon = Sml_Cannon();
//	weapon.setPos(&pos);

}

void Square::setBulletImage(ofImage* img)
{
//	weapon.setImage(img);

}

void Square::move()
{
	//stationary
	force, velocity, acceleration = glm::vec3(0);

	//rotation
	direction = pos - heroPos;
	//normalize
	direction = glm::normalize(direction);

	float deg = glm::degrees(glm::orientedAngle(heading(), glm::normalize(direction), glm::vec3(0, 0, 1)));
	angularVelocity = deg;
	Agent::move();

}



//~~~~~~~~~~~~~~~Hexagon~~~~~~~~~~~~~
Hexagon::Hexagon()
{

}
void Hexagon::move()
{

}
