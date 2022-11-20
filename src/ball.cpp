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
	checkCollision(bricks, paddle);
	coord.x += speed * direction.x / 2;
	coord.y += speed * direction.y;
}

void Ball::checkCollision(std::vector<std::vector<Brick>>& bricks, Paddle& paddle)
{
	Coordinate2D futurePositionX{ coord.x + direction.x * speed / 2, coord.y};
	Coordinate2D futurePositionY{ coord.x, coord.y + direction.y };
	if (checkWallCollision(paddle, futurePositionX)) {}
	else if (checkPaddleCollision(paddle, futurePositionX))
	{
		direction.y = -1;
		coord.y += direction.y * speed;
	}
	else if(checkPaddleCollision(paddle, futurePositionY))
	{
		direction.y = -1;
		direction.x *= -1;
		coord.x += direction.x * speed;
		coord.y += direction.y * speed;
	}
	else if(futurePositionY.y < ofGetHeight()/3)
	{
		if (checkBrickCollision(bricks, futurePositionY))
		{
			direction.y *= -1;
		}
		else if (checkBrickCollision(bricks, futurePositionX))
		{
			direction.x *= -1;
		}

	}

}

bool Ball::checkWallCollision(Paddle& paddle, Coordinate2D futurePosition)
{
	if (futurePosition.x + direction.x * speed + radius * 2 > ofGetWidth() || futurePosition.x - radius * 2 < 0)
	{
		direction.x *= -1;
		coord.x += direction.x * speed * 0.5;
		return true;
	}
	if (futurePosition.y - radius * 2 < 0)
	{
		if (!playerStats.hitTop)
		{
			playerStats.hitTop = true;
			paddle.shrink();
		}
		direction.y *= -1;
		coord.y += direction.y * speed;
		return true;
	}
	else if (futurePosition.y + direction.y * speed + radius * 2 > ofGetHeight())
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
		return true;
	}
	return false;
}

bool Ball::checkBrickCollision(std::vector<std::vector<Brick>>& bricks, Coordinate2D futurePosition)
{
	for (int i = 0; i < bricks.size(); i++)
	{
		for (int j = 0; j < bricks[0].size(); j++)
		{
			if (bricks[i][j].checkCollision(futurePosition, radius)) {
				playerStats.score += bricks[i][j].getScoreValue();
				playerStats.hitCount++;

				if(bricks[i][j].getColor() == Brick::Color::Orange && !playerStats.hitOrange)
				{
					playerStats.hitOrange = true;
					speed+= 1.0f;
				}
				else if(bricks[i][j].getColor() == Brick::Color::Red && !playerStats.hitRed)
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

bool Ball::checkPaddleCollision(Paddle paddle, Coordinate2D futurePosition)
{
	return paddle.checkCollision(futurePosition, radius);
}




