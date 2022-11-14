#pragma once

#include "ofMain.h"
#include "Agent.h"
#include "LevelController.h"
#include "ofxGui.h"
#include "Bullet.h"
#include "Particle.h"
#include "ParticleEmitter.h"

//Questions for teach:
// is it possible to assign an image outside of ofApp.cpp
// 1) can i make it so the bullet image is loaded elsewhere?
// instead of having the program pass it all the way thorugh?
// 2) When i create bullets it makes a weapon. When that enemy 
// diappears so does the bullet.
// 3) the movement is tied to the enemy movement

//dont actually clear the enemy 


class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	//Custom functions
	void updateFromGui();
	void spawnEnemies();
	void drawElapsedTime();
	void drawFrameRate();
	void drawStart();
	void draw_lives();

	//General
	enum GameState { Title, Play, End };
	GameState gs;
	ofImage bgImg;
	float startTime,endTime;
	bool bHide, death = false;
	glm::vec3 center;
	ofTrueTypeFont myFont, my32Font, fonty;
	int rotation, enterWidth, instWidth, gameOverWidth,
		instHeight, circum, shapeDegRot, shapeSize;
	string instructions, enter, gameOver,endTimeStr,spaceText;
	LevelController lc;
	ofSoundPlayer collideSound,thrustSound, expSound,shootSound;

	ParticleEmitter emitter, orbitalEmitter;
	// adding forces
		//
	TurbulenceForce* turbForce;
	GravityForce* gravityForce;
	ImpulseRadialForce* radialForce;

	//Bullets
	//ofImage gBullet;
	Bullet b;
	ofImage gBull;
	//vector <Bullet> projectiles;

	ofxPanel gui;
	ofxLabel label;
	ofxButton button;
	ofParameterGroup mainGroup;
	ofParameter<int> levelSlider;
	//Hero
	Hero hero;
	float timeAlive;
	ofImage heroImg, hBulletImg;
	ofParameterGroup heroGroup;
	ofParameter<int> heroSpeedSlider;
	ofParameter<bool> hRetroRSlider;
	ofParameter<float> heroRotationSpeedSlider, heroSizeSlider, hRetroRSpeedSlider;
	ofParameter<int> bulletSpeedSlider;

	//Enemies
	ofImage eBulletImg;
	ofParameterGroup enemyGroup;
	ofParameter<int> enemySpeedSlider, eSpawnAmnt;
	ofParameter<float> eSpawnRate, eLifespan, eFireRate;

};
