#include "ball.h"
#include <iostream>

#include "ofAppRunner.h"

Ball::Ball(const Coordinate2D coord, const int radius, const float speed)
{
	this->coord = coord;
	this->radius = radius;
	this->speed = speed;
	bounceSound.loadSound("bounce.wav");
	winSound.loadSound("win.wav");
	uiFont.loadFont("Sigmar.ttf", 30);
}

void Ball::draw()
{
	ofDrawCircle(coord.x, coord.y, radius);
	displayUI();
}

void Ball::displayUI() {
	std::string scoreString = "Score: " + std::to_string(playerStats.score);
	std::string livesString = "Lives: " + std::to_string(playerStats.lives);
	uiFont.drawString(scoreString, 50, 50);
	uiFont.drawString(livesString, 400, 50);
	if (playerStats.won == true) {
		uiFont.drawString("YOU WON!", 20, ofGetHeight() / 2);
	}
	else if (playerStats.lost == true) {
		uiFont.drawString("YOU LOST TRY AGAIN", 20, ofGetHeight() / 2);
	}
}

void Ball::move(std::vector<std::vector<Brick>>& bricks, Paddle& paddle)
{
	if (!playerStats.won) {
		if (checkCollision(bricks, paddle)) { bounceSound.play(); };
		coord.x += speed * direction.x / 2.3;
		coord.y += speed * direction.y;
	}
	else {
		std::cout << "You won";
	}

}

bool Ball::checkCollision(std::vector<std::vector<Brick>>& bricks, Paddle& paddle)
{
	bool hitEvent = false;
	Coordinate2D futurePositionX{ coord.x + direction.x * speed / 2, coord.y};
	Coordinate2D futurePositionY{ coord.x, coord.y + direction.y  * speed};
	if (checkWallCollision(paddle, futurePositionX)) { hitEvent = true; }
	else if(paddle.checkCollision(futurePositionY, radius))
	{
		direction.y = -1;
		coord.y += direction.y * speed;
		hitEvent = true;
	}
	else if (paddle.checkCollision(futurePositionX, radius))
	{
		direction.y = -1;
		direction.x *= -1;
		coord.y += direction.y * speed;
		coord.x += direction.x * speed;
		hitEvent = true;
	}
	else if(futurePositionY.y < ofGetHeight()/3)
	{
		if (checkBrickCollision(bricks, futurePositionY))
		{
			direction.y *= -1;
			hitEvent = true;
		}
		else if (checkBrickCollision(bricks, futurePositionX))
		{
			direction.x *= -1;
			hitEvent = true;
		}

	}
	return hitEvent;

}

bool Ball::checkWallCollision(Paddle& paddle, Coordinate2D futurePosition)
{
	bool collisionEvent = false;
	if (futurePosition.x + direction.x * speed + radius * 2 > ofGetWidth() || futurePosition.x - radius * 2 < 0)
	{
		direction.x *= -1;
		coord.x += direction.x * speed * 0.5;
		collisionEvent = true;
	}
	else if (futurePosition.y - radius * 2 < 0)
	{
		if (!playerStats.hitTop)
		{
			playerStats.hitTop = true;
			paddle.shrink();
		}
		direction.y *= -1;
		coord.y += direction.y * speed;
		collisionEvent = true;
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
			playerStats.lost = true;
			std::cout << "You lost";
		}
		collisionEvent = true;
	}
	return collisionEvent;
}

bool Ball::checkBrickCollision(std::vector<std::vector<Brick>>& bricks, Coordinate2D futurePosition)
{
	int bricksLeft = 0;
	for (int i = 0; i < bricks.size(); i++)
	{
		for (int j = 0; j < bricks[0].size(); j++)
		{
			if (!bricks[i][j].getBroken()) {

				bricksLeft++;
				if (bricks[i][j].checkCollision(futurePosition, radius)) {
					playerStats.score += bricks[i][j].getScoreValue();
					playerStats.brickCount++;

					if (bricks[i][j].getColor() == Brick::Color::Orange && !playerStats.hitOrange)
					{
						playerStats.hitOrange = true;
						speed += 1.0f;
					}
					else if (bricks[i][j].getColor() == Brick::Color::Red && !playerStats.hitRed)
					{
						playerStats.hitRed = true;
						speed += 1.0f;
					}

					if (playerStats.brickCount == 4) {
						speed += 1.0f;
					}
					else if (playerStats.brickCount == 12) {
						speed += 1.0f;
					}
					return true;
				}

			}
		}
	}
	if (bricksLeft == 0) {
		winSound.play();
		winSound.setLoop(true);
		playerStats.won = true;
	}

	return false;
}
