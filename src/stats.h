#pragma once
/**
 * Stores lives score and game states
 */
struct Stats{
	int score = 0;
	int brickCount = 0;
	int lives = 0;
	bool won = false;
	bool lost = false;
	bool hitRed = false;
	bool hitOrange = false;
};