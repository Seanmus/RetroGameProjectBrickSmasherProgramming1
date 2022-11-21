#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	const int rows = 8;
	const int columns = 14;
	const int brickWidth = ofGetWidth() / columns;
	const int brickHeight = (ofGetHeight() / 5) / rows;

	backgroundMusic.loadSound("music.wav");
	backgroundMusic.setLoop(true);
	backgroundMusic.play();

	logo.load("logo.png");
	logo.setAnchorPoint(logo.getWidth() / 2, logo.getHeight() / 2);
	buttonImage.load("button.png");
	buttonImage.setAnchorPoint(buttonImage.getWidth() / 2, buttonImage.getHeight() / 2);

	for(int i = 0; i < rows; i++)
	{
		vector<Brick> bricksRow{0};
		for(int j = 0; j < columns; j++)
		{
			Brick::Color brickColor;
			if(i <= 1)
			{
				brickColor = Brick::Color::Red;
			}
			else if(i <= 3)
			{
				brickColor = Brick::Color::Orange;
			}
			else if (i <= 5)
			{
				brickColor = Brick::Color::Green;
			}
			else
			{
				brickColor = Brick::Color::Yellow;
			}
			Coordinate2D coord{ static_cast<float>(brickWidth * j), static_cast<float>(brickHeight * (i + 4) + 10)};
			Brick brick{ coord,brickWidth - 5, brickHeight - 5, brickColor };
			bricksRow.push_back(brick);
		}
		bricks.push_back(bricksRow);
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	if(playing)
	{
		if (movingLeft)
		{
			paddle.move(-1);
		}
		else if (movingRight)
		{
			paddle.move(1);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofColor bottomColor(255, 0, 128);
	ofColor topColor(128, 128, 0);
	ofBackgroundGradient(topColor, bottomColor, OF_GRADIENT_LINEAR);

	if(playing)
	{
		ofSetColor(255);
		paddle.draw();
		ball.draw();
		ball.move(bricks, paddle);
		for (int i = 0; i < static_cast<int>(bricks.size()); i++)
		{
			for (int j = 0; j < static_cast<int>(bricks[0].size()); j++)
			{
				bricks[i][j].draw();
			}
		}
	}
	else
	{
		logo.draw(ofGetWidth() / 2, ofGetHeight() / 5);
		buttonImage.draw(ofGetWidth() / 2, ofGetHeight() / 1.5);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(playing)
	{
		if (key == 57356) {
			movingLeft = true;
			movingRight = false;
		}
		else if (key == 57358) {
			movingRight = true;
			movingLeft = false;
		}
		else if (key == 114) {
			reset();
		}
	}
}

void ofApp::reset() {
	ball.reset();
	paddle.reset();
	for (int i = 0; i < static_cast<int>(bricks.size()); i++)
	{
		for (int j = 0; j < static_cast<int>(bricks[0].size()); j++)
		{
			bricks[i][j].reset();
			playing = false;
			ofSetColor(255, 255, 255, 255);
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == 57356) {
		movingLeft = false;

	}
	else if (key == 57358) {
		movingRight = false;
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
	if(x >= ofGetWidth() / 2  - buttonImage.getWidth() / 2 && x <= ofGetWidth() / 2 + buttonImage.getWidth() / 2 
		&& y >= ofGetHeight() / 1.5 - buttonImage.getHeight() / 2 && y <= ofGetWidth() / 1.5 + buttonImage.getHeight() / 2 )
	{
		playing = true;
	}
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
