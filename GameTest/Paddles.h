// paddle.h : 
// Created by Jenny on 04/06/18.
#pragma once
#include <vector>
#include "Line.h"


class Paddles
{
public:
	//properties of the paddle
	std::vector<line> lines;

	//fixed point for rotation, float fix_x and float fix_y
	float fix_x;
	float fix_y;

	
	std::vector<line> originalLines;
	std::vector<line> movedLines;
public:
	Paddles(float tempX, float tempY);
	~Paddles();

	//Set the paddle's moving angle, it rotates around a fixed point by float angle
	void setPaddleAngle(float angle);

	//Reflect the paddle and move horizontally on float on_fixx
	void reflectPaddle(float on_fixx);

	//Draw a paddle on the table
	void drawPaddle();

	//move the paddle when key is pressed
	void flipPaddle();

	//release the paddle when key is released
	void releasePaddle();
};

