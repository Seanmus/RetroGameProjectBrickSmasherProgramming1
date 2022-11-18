#pragma once

#include "ofMain.h"
#include "paddle.h"
#include <vector>
#include "brick.h"
#include "ball.h"


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
		Coordinate2D paddleCoord{100,600};
		
		Paddle paddle{ paddleCoord, 8 };
		std::vector<std::vector<Brick>> bricks;
		Ball ball{ Coordinate2D{300, 300},10, 3 };
		bool movingLeft = false;
		bool movingRight = false;
};
