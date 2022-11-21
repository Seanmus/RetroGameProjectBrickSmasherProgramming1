#pragma once
#include "coord.h"
#include "brick.h"
#include "paddle.h"
#include <vector>
#include "stats.h"
#include <ofTrueTypeFont.h>
#include <ofSoundPlayer.h>

/**
 * Header file for the ball class that stores lives and score
 */
class Ball {
public:
	Stats playerStats{0, 0, 3, false, false, false};
	Ball(const Coordinate2D coord, const int radius, const float speed);
	void draw();
	void move(std::vector<std::vector<Brick>>& bricks, Paddle& paddle);
	bool checkCollision(std::vector<std::vector<Brick>>& bricks, Paddle& paddle);
	bool checkWallCollision(Paddle& paddle, Coordinate2D futurePosition);
	bool checkBrickCollision(std::vector<std::vector<Brick>>& bricks, Coordinate2D futurePosition);
	void reset();
private:
	Coordinate2D coord;
	Coordinate2D direction{ 1, 1 };
	int radius;
	float speed;
	float originalSpeed;
	ofSoundPlayer bounceSound;
	ofSoundPlayer winSound;
	ofTrueTypeFont uiFont;
	void displayUI() const;

};
