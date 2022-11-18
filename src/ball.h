#pragma once
#include "coord.h"
#include "brick.h"
#include "paddle.h"
#include <vector>
#include "stats.h"

class Ball {
public:
	Stats playerStats{0, 0, 99, false, false, false};
	Ball(const Coordinate2D coord, const int radius, const int speed);
	void draw();
	void move(std::vector<std::vector<Brick>>& bricks, Paddle& paddle);
	void checkWallCollision(Paddle& paddle);
	bool checkBrickCollision(std::vector<std::vector<Brick>>& bricks);
	bool checkPaddleCollision(Paddle paddle);
private:
	Coordinate2D coord;
	Coordinate2D direction{ 1, 1 };
	int radius;
	int speed;
};
