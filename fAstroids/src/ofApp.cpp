#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (gs)
	{
	case Title:
		if (key == OF_KEY_RETURN || key == ' ')
		{
			startTime = ofGetElapsedTimef();
			lc.setLevel(1);
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
		if (key == 'p')
		{
			Pentagon p;
			p.setup(shapeSize, 5, homing, 0, &heroImg);
			pentagons.push_back(p);
			//enemies.push_back(p);
		}
		if (key == 't')
		{
			Triangle t;
			t.setup(shapeSize, 3, sCannon, 10, &heroImg);
			//t.setup(shapeSize, 3);
			triangles.push_back(t);
			//enemies.push_back(t);
		}
		if (key == 'h' || key == 'H')
		{
			bHide = !bHide;
		}

		break;
	case End:
		if (key == ' ')
		{
			death = false;
			enemyBullets.clear();
			playerBullets.clear();
			pentagons.clear();
			triangles.clear();
			hero.setPos(glm::vec3(ofGetWidth() / 2, ofGetHeight() / 2, 0));
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
