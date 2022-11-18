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
	if (coord.y - radius * 2 < 0)
	{
		direction.y *= -1;
		coord.y += direction.y * speed;
	}
	else if (coord.y + direction.y * speed + radius * 2 > ofGetHeight()) 
	{
		lives--;
		if (lives > 0) 
		{
			coord.x = ofGetHeight() / 2;
			coord.y = ofGetWidth() / 2;
		}
		else {
			std::cout << "You lost";
		}

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
			if (bricks[i][j].checkCollision(coord, radius)) {
				playerStats.score += bricks[i][j].getScoreValue();
				std::cout << "Score: " << playerStats.score;
				playerStats.hitCount++;
				if (playerStats.hitCount == 4) {
					speed += 1;
				}
				else if (playerStats.hitCount == 12) {
					speed += 1;
				}
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




