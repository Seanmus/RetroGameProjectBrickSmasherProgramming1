#pragma once
#include "coord.h"
#include "ofGraphics.h"

/**
 * Outlines functionality for a paddle
 */
class Paddle {
	private:
		Coordinate2D coord;
		int speed;
		int paddleWidth = 100;
		int originalPaddleWidth;
		int paddleHeight = 20;
		bool shrunk = false;
	public:
		Paddle(const Coordinate2D& coord, int speed);
		void move(int direction);
		void draw() const;
		void shrink();
		bool checkCollision(Coordinate2D otherPosition, int otherSize) const;
		void reset();
};