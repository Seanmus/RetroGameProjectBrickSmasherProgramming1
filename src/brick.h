#pragma once
#include "coord.h"

/**
 * Header file for the brick outlines functionality for the brick class.
 */
class Brick {
	public:
		enum class Color { Red, Orange, Green, Yellow };
		Brick(const Coordinate2D coord, const int sizeX, const int sizeY, const Color color);
		Brick();
		void draw() const;
		void reset();
		bool checkCollision(Coordinate2D otherCoord, int otherSize);
		int getScoreValue();
		bool getBroken();
		Color getColor();
		Coordinate2D coord;
		int sizeX{};
		int sizeY{};
		
	private:
		Color brickColor;
		bool broken = false;
};

