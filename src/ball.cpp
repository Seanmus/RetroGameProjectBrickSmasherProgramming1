#include "ball.h"
#include <iostream>

#include "ofAppRunner.h"

Ball::Ball(const Coordinate2D coord, const int radius, const int speed)
{
	this->coord = coord;
	this->radius = radius;
	this->speed = speed;
}

void Ball::draw()
{
	ofDrawCircle(coord.x, coord.y, radius);
}

void Ball::move(std::vector<std::vector<Brick>>& bricks, Paddle paddle)
{
	if(coord.x + direction.x * speed  + radius * 2 > ofGetWidth() || coord.x - radius * 2 < 0)
	{
		direction.x *= -1;
		coord.x += direction.x * speed;
	}
	if (coord.y + direction.y * speed + radius * 2 > ofGetHeight() || coord.y - radius * 2 < 0)
	{
		direction.y *= -1;
		coord.y += direction.y * speed;
	}
	coord.x += direction.x * speed;
	if(checkBrickCollision(bricks))
	{
		direction.x *= -1;
		coord.x += direction.x * speed;
	}
	if (checkPaddleCollision(paddle))
	{
		direction.x *= -1;
		coord.x += direction.x * speed;
	}
	coord.y += direction.y * speed;
	if (checkBrickCollision(bricks))
	{
		direction.y *= -1;
		coord.y += direction.y * speed;
	}
	if (checkPaddleCollision(paddle))
	{
		direction.y *= -1;
		coord.y += direction.y * speed;
	}

	
}

bool Ball::checkBrickCollision(std::vector<std::vector<Brick>>& bricks)
{

	for (int i = 0; i < bricks.size(); i++)
	{
		for (int j = 0; j < bricks[0].size(); j++)
		{
			if(!bricks[i][j].getBroken() && coord.x + radius * 2 > bricks[i][j].coord.x && coord.x < bricks[i][j].coord.x + bricks[i][j].sizeX + radius * 2 && coord.y > bricks[i][j].coord.y && coord.y < bricks[i][j].coord.y + bricks[i][j].sizeY + radius * 2)
			{
				bricks[i][j].breakBrick();
				std::cout << "Broke brick" << i << "," << j;
				return true;
			}
		}
	}
	return false;
}

bool Ball::checkPaddleCollision(Paddle paddle)
{
	if (coord.x > paddle.getCoord().x - radius * 2 && coord.x < paddle.getCoord().x + paddle.getWidth() + radius * 2 && coord.y > paddle.getCoord().y && coord.y < paddle.getCoord().y + paddle.getHeight())
	{
		return true;
	}
	return false;
}




