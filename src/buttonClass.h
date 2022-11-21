#pragma once
#include "ofImage.h"
#include "coord.h"
class ButtonClass
{
	public:
		ButtonClass(const Coordinate2D coord, std::string restingImagePath, std::string hoverImagePath);
		void checkHover(Coordinate2D mouseCoords);
		void draw();
		bool checkCollision(Coordinate2D mouseCoords) const;
	private:
		Coordinate2D coord;
		ofImage hoverImage;
		ofImage restingImage;
		ofImage currentImage;
};
