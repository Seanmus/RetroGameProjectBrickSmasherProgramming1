#include "paddle.h"
#include <ofAppRunner.h>

/// <summary>
/// Constructs the paddle object.
/// </summary>
/// <param name="coord">The starting position of the paddle.</param>
/// <param name="speed">The speed of the paddle</param>
Paddle::Paddle(const Coordinate2D& coord, const int speed)
{
	this->coord = coord;
	this->speed = speed;
	originalPaddleWidth = paddleWidth;
}

/// <summary>
/// Moves the paddle in the provided direction 
/// </summary>
/// <param name="direction">Positive moves right, negative moves left.</param>
void Paddle::move(const int direction)
{
	//Guard to stop paddle going Left off the screen
	if (direction == -1 && coord.x - static_cast<float>(speed) < 0) { return; }
	//Guard to stop paddle going Right off the screen
	if (direction == 1 && coord.x + static_cast<float>(speed + paddleWidth) > static_cast<float>(ofGetViewportWidth())) { return; }

	coord.x += static_cast<float>(speed * direction);
}

/// <summary>
/// Draws the paddle to the screen.
/// </summary>
void Paddle::draw() const
{
	ofDrawRectangle(coord.x, coord.y,  static_cast<float>(paddleWidth), static_cast<float>(paddleHeight));

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
/// <returns>True is a collision is detected.</returns>
bool Paddle::checkCollision(const Coordinate2D otherPosition, const int otherSize) const
{
	return (otherPosition.x > coord.x - static_cast<float>(otherSize * 2) && otherPosition.x < coord.x + static_cast<float>(paddleWidth + otherSize * 2) && otherPosition.y + static_cast<float>(otherSize) > coord.y && otherPosition.y < coord.y + static_cast<float>(paddleHeight));
}

/// <summary>
/// Resets the paddles position.
/// </summary>
void Paddle::reset() 
{
	paddleWidth = originalPaddleWidth;
	coord.x = static_cast<float>(ofGetWidth())/ 2;
}
