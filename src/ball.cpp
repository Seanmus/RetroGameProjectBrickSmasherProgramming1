#include "ball.h"
#include <iostream>

#include "ofAppRunner.h"

/// <summary>
/// Constructs the ball
/// </summary>
/// <param name="coord">The inital starting position of the ball.</param>
/// <param name="radius">The radius of the ball.</param>
/// <param name="speed">The initial speed of the ball.</param>
Ball::Ball(const Coordinate2D coord, const int radius, const float speed)
{
	this->coord = coord;
	this->radius = radius;
	this->speed = speed;
	bounceSound.loadSound("bounce.wav");
	winSound.loadSound("win.wav");
	uiFont.loadFont("Sigmar.ttf", 30);
	originalSpeed = speed;
}

/// <summary>
/// Draws the ball and calls the display UI method
/// </summary>
void Ball::draw()
{
	ofDrawCircle(coord.x, coord.y, radius);
	displayUI();
}

/// <summary>
/// Displays the UI including a win and lost message, score and lives counter.
/// </summary>
void Ball::displayUI() {
	std::string scoreString = "Score: " + std::to_string(playerStats.score);
	std::string livesString = "Lives: " + std::to_string(playerStats.lives);
	uiFont.drawString(scoreString, 50, 50);
	uiFont.drawString(livesString, 400, 50);
	if (playerStats.won == true) {
		uiFont.drawString("YOU WON!", 200, ofGetHeight() / 2);
	}
	else if (playerStats.lost == true) {
		uiFont.drawString("YOU LOST, TRY AGAIN", ofGetWidth() / 2 - 250, ofGetHeight() / 2);
	}
}

/// <summary>
/// Moves the player if they have not won or lost.
/// </summary>
/// <param name="bricks"></param>
/// <param name="paddle"></param>
void Ball::move(std::vector<std::vector<Brick>>& bricks, Paddle& paddle)
{
	if (!playerStats.won && !playerStats.lost) {
		if (checkCollision(bricks, paddle)) { bounceSound.play(); };
		coord.x += speed * direction.x / 2.3;
		coord.y += speed * direction.y;
	}
}

/// <summary>
/// Checks if the ball collides with walls, bricks or the paddle.
/// </summary>
/// <param name="bricks">The 2d vector of bricks to check collisions against.</param>
/// <param name="paddle">The paddle to check collisions against.</param>
/// <returns>True if a hit is detected.</returns>
bool Ball::checkCollision(std::vector<std::vector<Brick>>& bricks, Paddle& paddle)
{
	bool hitEvent = false;
	Coordinate2D futurePositionX{ coord.x + direction.x * speed / 2, coord.y};
	Coordinate2D futurePositionY{ coord.x, coord.y + direction.y  * speed};
	if (checkWallCollision(paddle, futurePositionX)) { hitEvent = true; }
	else if(paddle.checkCollision(futurePositionY, radius))
	{
		direction.y = -1;
		hitEvent = true;
	}
	else if (paddle.checkCollision(futurePositionX, radius))
	{
		direction.y = -1;
		direction.x *= -1;
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

/// <summary>
/// Checks if the ball has collided with any of the walls. If it hits the bottom a life is taken away.
/// </summary>
/// <param name="paddle">The paddle the player controls. shrinks the first time the player hits the top wall.</param>
/// <param name="futurePosition">The future position of the ball to check collisions against.</param>
/// <returns>True if a collision is detected.</returns>
bool Ball::checkWallCollision(Paddle& paddle, Coordinate2D futurePosition)
{
	bool collisionEvent = false;
	if (futurePosition.x + direction.x * speed + radius * 2 > ofGetWidth() || futurePosition.x - radius * 2 < 0)
	{
		direction.x *= -1;
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
		collisionEvent = true;
	}
	else if (futurePosition.y + direction.y * speed + radius * 2 > ofGetHeight())
	{
		//Respawns the player
		if (playerStats.lives > 1)
		{
			playerStats.lives--;
			coord.y = ofGetHeight() / 3;
			coord.x = radius * 2 + 5;
			direction.x = 1;
			direction.y = 1;
		}
		//Sets the game to be in a lost state
		else {
			playerStats.lost = true;
		}
		collisionEvent = true;
	}
	return collisionEvent;
}

/// <summary>
/// Checks if the ball collides with any of the bricks.
/// </summary>
/// <param name="bricks">The 2d vector of bricks at the top of the screen.</param>
/// <param name="futurePosition">The future position of the ball to check collisions against.</param>
/// <returns>True if a collision is detected.</returns>
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

/// <summary>
/// Resets the ball to its initial state including stats.
/// </summary>
void Ball::reset() {
	playerStats.lives = 3;
	playerStats.score = 0;
	playerStats.brickCount = 0;
	playerStats.won = false;
	playerStats.lost = false;
	playerStats.hitOrange = false;
	playerStats.hitRed = false;
	playerStats.hitTop = false;
	speed = originalSpeed;
	coord.x = ofGetWidth() / 2;
	coord.y = ofGetHeight() / 3;
	direction.x = 1;
	direction.y = 1;
	winSound.setLoop(false);
}
