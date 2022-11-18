#pragma once
#include "coord.h"
#include "ofGraphics.h"

class Paddle {
	private:
		Coordinate2D coord;
		int speedMultiplier;
		int paddleWidth = 100;
		int paddleHeight = 20;
	public:
		Paddle(const Coordinate2D& coord, int speedMultiplier);
		void move(int direction);
		void draw();
		void shrink();
		int getWidth();
		int getHeight();
		Coordinate2D getCoord();
};