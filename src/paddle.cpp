#include "paddle.h"
#include <ofAppRunner.h>

/// <summary>
/// Constructs the paddle object.
/// </summary>
/// <param name="coord">The starting position of the paddle.</param>
/// <param name="speedMultiplier">The speed of the paddle</param>
Paddle::Paddle(const Coordinate2D& coord, int speed)
{
	this->coord = coord;
	this->speed = speed;
	originalPaddleWidth = paddleWidth;
}

/// <summary>
/// Moves the paddle in the provided direction 
/// </summary>
/// <param name="direction">Positive moves right, negative moves left.</param>
void Paddle::move(int direction)
{
	//Guard to stop paddle going Left off the screen
	if (direction == -1 && coord.x - speed < 0) { return; }
	//Guard to stop paddle going Right off the screen
	if (direction == 1 && coord.x + speed + paddleWidth > ofGetViewportWidth()) { return; }

	coord.x += speed * direction;
}

/// <summary>
/// Draws the paddle to the screen.
/// </summary>
void Paddle::draw()
{
	ofDrawRectangle(coord.x, coord.y, paddleWidth, paddleHeight);

}

/// <summary>
/// Shrinks the paddle to half its original size.
/// </summary>
void Paddle::shrink()
{
	paddleWidth /= 2;
}

/// <summary>
/// Checks for collisions against the provided otherPosition using its size.
/// </summary>
/// <param name="otherPosition">The position of the other object.</param>
/// <param name="otherSize">The size of the other object.</param>
/// <returns></returns>
bool Paddle::checkCollision(Coordinate2D otherPosition, int otherSize)
{
	return (otherPosition.x > coord.x - otherSize * 2 && otherPosition.x < coord.x + paddleWidth + otherSize * 2 && otherPosition.y + otherSize > coord.y && otherPosition.y < coord.y + paddleHeight);
}

/// <summary>
/// Resets the paddles position.
/// </summary>
void Paddle::reset() 
{
	paddleWidth = originalPaddleWidth;
	coord.x = ofGetWidth() / 2;
}
