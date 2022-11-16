#pragma once
#include "coord.h"
#include "brick.h"
#include "paddle.h"
#include <vector>

class Ball {
public:
	Ball(const Coordinate2D coord, const int radius, const int speed);
	void draw();
	void move(std::vector<std::vector<Brick>>& bricks, Paddle paddle);
	bool checkBrickCollision(std::vector<std::vector<Brick>>& bricks);
	bool checkPaddleCollision(Paddle paddle);
private:
	Coordinate2D coord;
	Coordinate2D direction{ 1, 1 };
	int radius;
	int speed;
};
