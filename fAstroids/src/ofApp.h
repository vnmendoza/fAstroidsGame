#pragma once

#include "ofMain.h"
#include "Agent.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		//Custom functions
		void spawnEnemies();
		void drawElapsedTime();
		void drawStart();

		//General
		enum GameState { Title, Play, End };
		GameState gs;
		ofImage bgImg;
		float startTime;
		bool bHide, death = false;
		glm::vec3 center;
		ofTrueTypeFont myFont, my32Font, fonty;
		int rotation, enterWidth, instWidth, gameOverWidth,
			instHeight, circum, shapeDegRot, shapeSize;
		string instructions, enter, gameOver;


		ofxPanel gui;
		ofxLabel label;
		ofxButton button;
		ofxToggle spriteToggle;
		ofParameterGroup mainGroup;
		ofParameter<int> levelSlider;
		//Hero
		Hero hero;
		float timeAlive;
		ofImage heroImg, hBulletImg;
		ofParameterGroup heroGroup;
		ofParameter<int> heroSpeedSlider;
		ofParameter<float> heroRotationSpeedSlider, heroSizeSlider;
		ofParameter<int> bulletSpeedSlider;
		vector<PlayerBullet> playerBullets;

		//Enemies
		ofImage eBulletImg;
		ofParameterGroup enemyGroup;
		ofParameter<int> enemySpeedSlider, eSpawnAmnt;
		ofParameter<float> eSpawnRate, eLifespan, eFireRate;
		vector<Triangle> triangles;
		vector<Pentagon> pentagons;
		vector<Enemy> enemies;
		vector<EnemyBullet> enemyBullets;
};
