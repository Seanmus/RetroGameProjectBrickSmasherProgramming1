#include "paddle.h"

Paddle::Paddle(const Coordinate2D& coord, int speedMultiplier)
{
	this->coord = coord;
	this->speedMultiplier = speedMultiplier;
}

void Paddle::move(int direction)
{
	//Guard to stop paddle going Left off the screen
	if (direction == -1 && coord.x - speedMultiplier < 0) { return; }
	//Guard to stop paddle going Right oof the screen
	if (direction == 1 && coord.x + speedMultiplier + paddleWidth > 1024) { return; }

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

Coordinate2D Paddle::getCoord()
{
	return coord;
}
