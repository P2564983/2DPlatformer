#include "World.h"

unsigned int Score::currentScore = 0;
unsigned int Score::highScore = 0;
Clock Score::gameTime;

void Score::addToScore(const unsigned int scoreChange)
{
	if (currentScore == 0)
		gameTime.restart();

	// Add score to current score and check if this is the new high score
	if ((currentScore += scoreChange) > highScore)
		highScore = currentScore;
}

void Score::resetCurrentScore()
{
	currentScore = 0;
	gameTime.restart();
	gameTime.getElapsedTime();
}
