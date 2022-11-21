#include "paddle.h"
#include <ofAppRunner.h>

Paddle::Paddle(const Coordinate2D& coord, int speedMultiplier)
{
	this->coord = coord;
	this->speedMultiplier = speedMultiplier;
	originalPaddleWidth = paddleWidth;
}

void Paddle::move(int direction)
{
	//Guard to stop paddle going Left off the screen
	if (direction == -1 && coord.x - speedMultiplier < 0) { return; }
	//Guard to stop paddle going Right off the screen
	if (direction == 1 && coord.x + speedMultiplier + paddleWidth > ofGetViewportWidth()) { return; }

	coord.x += speedMultiplier * direction;
}

void Paddle::draw()
{
	ofDrawRectangle(coord.x, coord.y, paddleWidth, paddleHeight);

}

void Paddle::shrink()
{
	paddleWidth /= 2;
}

int Paddle::getWidth()
{
	return paddleWidth;
}

int Paddle::getHeight()
{
	return paddleHeight;
}

bool Paddle::checkCollision(Coordinate2D otherPosition, int otherSize)
{
	return (otherPosition.x > coord.x - otherSize * 2 && otherPosition.x < coord.x + paddleWidth + otherSize * 2 && otherPosition.y + otherSize > coord.y && otherPosition.y < coord.y + paddleHeight);
}

Coordinate2D Paddle::getCoord()
{
	return coord;
}

void Paddle::reset() 
{
	paddleWidth = originalPaddleWidth;
	coord.x = ofGetWidth() / 2;
}
