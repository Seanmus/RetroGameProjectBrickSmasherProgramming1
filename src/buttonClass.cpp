#include "buttonClass.h"


ButtonClass::ButtonClass(const Coordinate2D coord, std::string restingImagePath, std::string hoverImagePath)
{
	this->coord = coord;
	restingImage.load(restingImagePath);
	hoverImage.load(hoverImagePath);
	currentImage = restingImage;
	currentImage.setAnchorPoint(currentImage.getWidth() / 2, currentImage.getHeight() / 2);
}

void ButtonClass::checkHover(Coordinate2D mouseCoords)
{
	if(checkCollision(mouseCoords))
	{
		currentImage = hoverImage;
	}
	else
	{
		currentImage = restingImage;
	}
}

void ButtonClass::draw()
{
	currentImage.draw(coord.x, coord.y);
}

bool ButtonClass::checkCollision(Coordinate2D mouseCoords) const
{
	if (mouseCoords.x >= coord.x - currentImage.getWidth() / 2 && mouseCoords.x <= coord.x + currentImage.getWidth() / 2
		&& mouseCoords.y >= coord.y - currentImage.getHeight() / 2 && mouseCoords.y <= coord.y + currentImage.getHeight() / 2)
	{
		return true;
	}
	return false;
}



