#include "brick.h"

#include "ofGraphics.h"


Brick::Brick(const Coordinate2D coord,const int sizeX, const int sizeY, const Color color)
{
	this->coord = coord;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->brickColor = color;
}

Brick::Brick()
{
}


void Brick::draw() const
{
	if(!broken)
	{
		if (brickColor == Color::Yellow)
		{
			ofSetColor(255, 255, 0);
		}
		if (brickColor == Color::Green)
		{
			ofSetColor(0, 255, 0);
		}
		if (brickColor == Color::Orange)
		{
			ofSetColor(255, 165, 0);
		}
		if (brickColor == Color::Red)
		{
			ofSetColor(255, 0, 0);
		}
		ofDrawRectangle(coord.x, coord.y, sizeX, sizeY);
	}

}

void Brick::breakBrick()
{
	if(brickColor == Color::Yellow)
	{
	//	ofApp::score++;
	}
	else if(brickColor == Color::Green)
	{
	//	ofApp::score += 3;
	}
	else if(brickColor == Color::Orange)
	{
	//	ofApp::score += 5;
	}
	else
	{
	//	ofApp::score += 7;
	}
	std::cout << "Score: " << "hi" << "\n";
	broken = true;
}

bool Brick::getBroken()
{
	return broken;
}

