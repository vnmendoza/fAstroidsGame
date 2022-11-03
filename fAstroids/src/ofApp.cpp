#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetWindowTitle("fAstroids");
	gs = Title;
	ofSetFrameRate(30);

	//set global variables
	center = glm::vec3(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2, 0);
	bgImg.load("background.png");
	shapeDegRot = 45;
	shapeSize = 40;

	//sound
	//shootSound.load("pathToSound.mp4");
	//shootSound.setLoop(true);
	

	//bullets
	//gBullet.load("greenCannon.png");
	gBull.load("greenCannon.png");
	b.setup(center, &gBull);
	
	//LevelController
	lc.gBullImg = &gBull;
	cout << "lc" << lc.gBullImg->getWidth() << endl;
	

	//Hero
	heroImg.load("Hero_ship.png");
	hero.setup(&heroImg);
		//Hero Sliders
	heroGroup.setName("Hero");
	heroGroup.add(heroSpeedSlider.set("Hero Speed", 15, 0, 80));
	heroGroup.add(heroRotationSpeedSlider.set("Hero Rotation Speed", 5, 0, 20));
	heroGroup.add(heroSizeSlider.set("Hero Size", 0.75, 0, 3));
	heroGroup.add(hRetroRSpeedSlider.set("Retro Dampners", 0.98, 0.8, 0.999));
	heroGroup.add(hRetroRSlider.set("RetroRockets",true));
	gui.setup(heroGroup);
	//Enemy
		//EnemySliders
	enemyGroup.setName("Enemies");
	enemyGroup.add(enemySpeedSlider.set("Enemy Speed", 5, 0, 50));
	enemyGroup.add(eSpawnRate.set("Enemy Spawn Rate", 3, 0.5, 15));
	enemyGroup.add(eSpawnAmnt.set("Enemy Spawn Amount", 1, 1, 10));
	enemyGroup.add(eLifespan.set("Enemy Lifespan", 4, 0, 10));
	enemyGroup.add(eFireRate.set("Enemy FireRate", 3, 0.5, 10));
	//General Sliders
	mainGroup.add(levelSlider.set("Level", 1, 1, 3));
	//Add to gui
	mainGroup.add(heroGroup);
	mainGroup.add(enemyGroup);
	gui.setup(mainGroup);

	//Instuctions
	myFont.load("Hexgon-2xwv.otf", 28, true, true);
	fonty.load("Caveat-Regular.ttf", 32, true, true);
	my32Font.load("Hexgon-2xwv.otf", 32, true, true);
	instructions = "     WASD to move\nleft click to shoot";
	enter = "push SPACE to begin";
	instWidth = my32Font.stringWidth(instructions) / 2;
	instHeight = my32Font.stringHeight(instructions) / 2;
	enterWidth = myFont.stringWidth(enter) / 2;
	circum = instWidth + shapeDegRot;
	gameOver = "Game Over";
	gameOverWidth = myFont.stringWidth(gameOver);
}

void ofApp::updateFromGui()
{
	hero.setSpeed(heroSpeedSlider);
	hero.setRotationSpeed(heroRotationSpeedSlider);
	hero.setSize(heroSizeSlider);
	hero.setRetroRocket(hRetroRSlider);
	hero.setRetroSpeed(hRetroRSpeedSlider);
	lc.update(eSpawnRate, eSpawnAmnt,levelSlider);
	lc.updateEnemies(eLifespan,enemySpeedSlider,eFireRate,hero.getPos());
}

//--------------------------------------------------------------
void ofApp::update(){
	switch (gs)
	{
	case Title:
		rotation++;
		break;
	case Play:
		updateFromGui();
		hero.update();
		//LevelController
		lc.updateBullets();
		break;
	case End:
		break;
	default:
		break;
	}

}


//--------------------------------------------------------------
void ofApp::draw(){
	switch (gs)
	{
	case Title:
		drawStart();
		break;
	case Play:
		gui.draw();
		hero.draw();
		lc.drawEnemies();
		lc.drawBullets();
		draw_lives();
		b.draw();
		break;
	case End:
		break;
	default:
		break;
	}
}

void ofApp::drawStart()
{
	//Start Screen
	ofSetColor(255);
	my32Font.drawString(instructions, center.x - instWidth, center.y - instHeight);
	myFont.drawString(enter, center.x - enterWidth, center.y + instHeight);
	//Draw Enemies Circling
	ofTranslate(center);
	ofRotateDeg(rotation);
	ofFill();
	//Triangle
	ofPushMatrix();
	ofTranslate(circum, 0, 0);
	ofSetCircleResolution(3);
	ofSetColor(ofColor::paleVioletRed);
	ofDrawCircle(0, 0, shapeSize);
	ofPopMatrix();
	//Rectangle
	ofPushMatrix();
	ofRotateDeg(shapeDegRot);
	ofTranslate(circum, 0, 0);
	ofSetColor(ofColor::aqua);
	ofSetCircleResolution(4);
	ofDrawCircle(0, 0, shapeSize);
	ofPopMatrix();
	//Square
	ofPushMatrix();
	ofRotateDeg(shapeDegRot * 2);
	ofTranslate(circum, 0, 0);
	ofSetColor(ofColor::moccasin);
	ofSetCircleResolution(5);
	ofDrawCircle(0, 0, shapeSize);
	ofPopMatrix();
	//Hexagon
	ofPushMatrix();
	ofRotateDeg(shapeDegRot * 3);
	ofTranslate(circum, 0, 0);
	ofSetColor(ofColor::green);
	ofSetCircleResolution(6);
	ofDrawCircle(0, 0, shapeSize);
	ofPopMatrix();
	//Heptagon
	ofPushMatrix();
	ofRotateDeg(shapeDegRot * 4);
	ofTranslate(circum, 0, 0);
	ofSetColor(ofColor::magenta);
	ofSetCircleResolution(7);
	ofDrawCircle(0, 0, shapeSize);
	ofPopMatrix();
	//Octogon
	ofPushMatrix();
	ofRotateDeg(shapeDegRot * 5);
	ofTranslate(circum, 0, 0);
	ofSetColor(ofColor::yellow);
	ofSetCircleResolution(8);
	ofDrawCircle(0, 0, shapeSize);
	ofPopMatrix();
	//Nonogon
	ofPushMatrix();
	ofRotateDeg(shapeDegRot * 6);
	ofTranslate(circum, 0, 0);
	ofSetColor(ofColor::blue);
	ofSetCircleResolution(9);
	ofDrawCircle(0, 0, shapeSize);
	ofPopMatrix();
	//Decagon
	ofPushMatrix();
	ofRotateDeg(shapeDegRot * 7);
	ofTranslate(circum, 0, 0);
	ofSetColor(ofColor::silver);
	ofSetCircleResolution(10);
	ofDrawCircle(0, 0, shapeSize);
	ofPopMatrix();
	// Add background music
	// Add Start sound

}

void ofApp::draw_lives() {
	for (int i = 0; i < hero.getNRG(); i++) {
		ofPushMatrix();
		ofSetColor(hero.getColor());
		heroImg.setAnchorPoint(heroImg.getWidth() / 2, heroImg.getHeight() / 2);
		heroImg.draw(ofGetWindowWidth() - (i * 100) + 100, 250, 100, 100);
		ofPopMatrix();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (gs)
	{
	case Title:
		if (key == OF_KEY_RETURN || key == ' ')
		{
			startTime = ofGetElapsedTimef();
			//lc.setLevel(1);
			gs = Play;
		}
		break;
	case Play:
		if (key == OF_KEY_UP || key == 'w')
			hero.setUpPressed(true);
		if (key == OF_KEY_LEFT || key == 'a')
			hero.setLeftPressed(true);
		if (key == OF_KEY_DOWN || key == 's')
			hero.setDownPressed(true);
		if (key == OF_KEY_RIGHT || key == 'd')
			hero.setRightPressed(true);
		if (key == ' ') {
			cout << "space" << endl;
		}
		if (key == 'h' || key == 'H')
		{
			bHide = !bHide;
		}
		if (key == '1')
			lc.spawnTriangle();
		if (key == '2')
			lc.spawnSquare();
		if (key == '3')
			lc.spawnHexagon();




		break;
	case End:
		if (key == ' ')
		{
			death = false;
			hero.setPos(center);
			hero.setNRG(5);
			gs = Title;
		}
		break;
	default:
		cout << "error in keyPressed" << endl;
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	if (key == OF_KEY_UP || key == 'w') {
		hero.setUpPressed(false);
	}
	if (key == OF_KEY_LEFT || key == 'a') {
		hero.setLeftPressed(false);
	}
	if (key == OF_KEY_DOWN || key == 's') {
		hero.setDownPressed(false);
	}
	if (key == OF_KEY_RIGHT || key == 'd') {
		hero.setRightPressed(false);
	}
	if (key == 'f')
	{
		ofToggleFullscreen();
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
