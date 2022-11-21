#include "brick.h"

#include "ofGraphics.h"


/// <summary>
/// Checks if the ball collides with walls, bricks or the paddle.
/// </summary>
/// <param name="coord">The 2d vector of bricks to check collisions against.</param>
/// <param name="sizeX">The width of the paddle.</param>
///	<param name="sizeY">The height of the paddle.</param>
///	<param name="color">The color of the brick.</param>
/// <returns>True if a hit is detected.</returns>
Brick::Brick(const Coordinate2D coord,const int sizeX, const int sizeY, const Color color)
{
	this->coord = coord;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->brickColor = color;
}

/// <summary>
/// A default constructor for the brick.
/// </summary>
Brick::Brick()
{
}

/// <summary>
/// Draws the brick of the specified color.
/// </summary>
void Brick::draw() const
{
	if(!broken)
	{
		if (brickColor == Color::Yellow)
		{
			ofSetColor(255, 255, 0);
		}
		if (brickColor == Color::Green)
		{
			ofSetColor(0, 255, 0);
		}
		if (brickColor == Color::Orange)
		{
			ofSetColor(255, 165, 0);
		}
		if (brickColor == Color::Red)
		{
			ofSetColor(255, 0, 0);
		}
		ofDrawRectangle(coord.x, coord.y, sizeX, sizeY);
	}

}
/// <summary>
/// Checks if a collision is detected against the provided coordinates
/// </summary>
/// <param name="otherCoord">The position to check collisions against.</param>
/// <param name="otherSize">The size of the other object.</param>
/// <returns>True if a hit is detected.</returns>
bool Brick::checkCollision(Coordinate2D otherCoord, int otherSize)
{
	if (!broken && otherCoord.x + otherSize * 2 > coord.x && otherCoord.x < coord.x + sizeX + otherSize * 2 && otherCoord.y > coord.y && otherCoord.y < coord.y + sizeY + otherSize * 2)
	{
		broken = true;
		return true;
	}
	return false;
}

/// <summary>
/// Returns a score value of the brick based on its color.
/// </summary>
/// <returns>The score value of the brick based on its color.</returns>
int Brick::getScoreValue()
{
	if(brickColor == Color::Yellow)
	{
		return 1;
	}
	else if(brickColor == Color::Green)
	{
		return 3;
	}
	else if(brickColor == Color::Orange)
	{
		return 5;
	}
	else
	{
		return 7;
	}
}

/// <summary>
/// Checks if the brick is broken
/// </summary>
/// <returns>True if a the brick is broken.</returns>
bool Brick::getBroken()
{
	return broken;
}

/// <summary>
/// Checks the color of the brick.
/// </summary>
/// <returns>The color of the brick.</returns>
Brick::Color Brick::getColor()
{
	return brickColor;
}

void Brick::reset() {
	broken = false;
}

