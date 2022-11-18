#include "ball.h"
#include <iostream>

#include "ofAppRunner.h"

Ball::Ball(const Coordinate2D coord, const int radius, const float speed)
{
	this->coord = coord;
	this->radius = radius;
	this->speed = speed;
}

void Ball::draw()
{
	std::string scoreString = "Score: " + std::to_string(playerStats.score);
	std::string livesString = "Lives: " + std::to_string(playerStats.lives);
	ofDrawCircle(coord.x, coord.y, radius);
	ofDrawBitmapString(scoreString, 100, 500);
	ofDrawBitmapString(livesString, 100, 550);
	
}

void Ball::move(std::vector<std::vector<Brick>>& bricks, Paddle& paddle)
{
	checkWallCollision(paddle);
	coord.x += direction.x * speed * 0.5;
	if(checkBrickCollision(bricks))
	{
		direction.x *= -1;
		coord.x += direction.x * speed;
	}
	if (checkPaddleCollision(paddle))
	{
		direction.y = -1;
		direction.x *= -1;
		coord.x += direction.x * speed;
		coord.y += direction.y * speed;
	}
	coord.y += direction.y * speed;
	if (checkBrickCollision(bricks))
	{
		direction.y *= -1;
		coord.y += direction.y * speed;
	}
	if (checkPaddleCollision(paddle))
	{
		direction.y = -1;
		coord.y += direction.y * speed;
	}
}

void Ball::checkWallCollision(Paddle& paddle)
{
	if (coord.x + direction.x * speed + radius * 2 > ofGetWidth() || coord.x - radius * 2 < 0)
	{
		direction.x *= -1;
		coord.x += direction.x * speed * 0.5;
	}
	if (coord.y - radius * 2 < 0)
	{
		if (!playerStats.hitTop)
		{
			playerStats.hitTop = true;
			paddle.shrink();
		}
		direction.y *= -1;
		coord.y += direction.y * speed;
	}
	else if (coord.y + direction.y * speed + radius * 2 > ofGetHeight())
	{
		if (playerStats.lives > 0)
		{
			playerStats.lives--;
			coord.y = ofGetHeight() / 3;
			coord.x = radius * 2 + 5;
			direction.x = 1;
			direction.y = 1;
		}
		else {
			speed = 0;
			std::cout << "You lost";
		}

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
				playerStats.hitCount++;

				if(i == 3 && !playerStats.hitOrange)
				{
					playerStats.hitOrange = true;
					speed+= 1.0f;
				}
				else if(i == 1 && !playerStats.hitRed)
				{
					playerStats.hitRed = true;
					speed+= 1.0f;
				}

				if (playerStats.hitCount == 4) {
					speed += 1.0f;
				}
				else if (playerStats.hitCount == 12) {
					speed += 1.0f;
				}
				return true;
			}
		}
	}
	return false;
}

bool Ball::checkPaddleCollision(Paddle paddle)
{
	if (coord.x > paddle.getCoord().x - radius * 2 && coord.x < paddle.getCoord().x + paddle.getWidth() + radius * 2 && coord.y + radius > paddle.getCoord().y && coord.y < paddle.getCoord().y + paddle.getHeight())
	{
		return true;
	}
	return false;
}




