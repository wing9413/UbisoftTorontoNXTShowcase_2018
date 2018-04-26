// ball.h : 
// Created by Jenny on 04/07/18.
#pragma once
#include <vector>
#include "Line.h"
#include "point.h"

class Ball
{
public:
	//properties of ball
	std::vector<line> lines;
	float velocity_X = 0;
	float velocity_Y = 0;
	bool notstart = true;

	//collision point
	std::vector<point> collisionPoints;

	//where the ball start
	std::vector<line> startPosition;

public:
	Ball();
	~Ball();

	//Draw a ball on the table
	void drawBall();
	
	//add gravity to the ball
	void setGravity();

	//Check the ball is still on the table
	void checkGameOver();

	//Update the ball's collision point
	void updateCollisionPoint();

	//When the ball hit a line and reaction
	int collisionDetection(float x1, float y1, float x2, float y2, char* string);

};

