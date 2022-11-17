#pragma once
#include "coord.h"

class Brick {
	public:
		enum class Color { Red, Orange, Green, Yellow };
		Brick(const Coordinate2D coord, const int sizeX, const int sizeY, const Color color);
		Brick();
		void draw() const;
		bool checkCollision(Coordinate2D otherCoord, int otherSize);
		int getScoreValue();
		bool getBroken();
		Coordinate2D coord;
		int sizeX{};
		int sizeY{};
		
	private:
		Color brickColor;
		bool broken = false;
};

