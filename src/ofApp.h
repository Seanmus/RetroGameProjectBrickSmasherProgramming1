#pragma once

#include "ofMain.h"
#include "paddle.h"
#include <vector>
#include "brick.h"
#include "ball.h"

/**
 * Handles the overarching game logic and start menu
 */
class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void reset();
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseReleased(int x, int y, int button);

		Coordinate2D paddleCoord{100,600};
		
		Paddle paddle{ paddleCoord, 8 };
		std::vector<std::vector<Brick>> bricks;
		Ball ball{Coordinate2D{ 300, 300 }, 5, 3};
		bool movingLeft = false;
		bool movingRight = false;

		bool playing = false;
		ofImage logo;
		ofImage startButtonImage;
		Coordinate2D startButtonCoord{static_cast<float>(ofGetWidth()) / 2, static_cast<float>(ofGetHeight() / 1.5)};

		ofSoundPlayer backgroundMusic;
		

};
