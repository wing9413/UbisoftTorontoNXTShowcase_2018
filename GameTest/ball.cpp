#include "stdafx.h"
#include "ball.h"
#include "app\app.h"
#include <math.h>
#include <cmath>

const float gravity = 9.81f; // Gravity of Earth in m/s2

//get the distance from two points
float distance(float x1, float y1, float x2, float y2)
{
	float temp1 = pow((x2 - x1), 2);
	float temp2 = pow((y2 - y1), 2);
	float distance = sqrt(temp1 + temp2);
	return distance;
}


//Set the size of the ball
float ballPosition[][4] = { { 688 ,645 ,709 ,645},
{ 709 ,645 ,709 ,626 },
{ 709 ,626 ,688 ,626 },
{ 688 ,645 ,688 ,626 }
};


Ball::Ball()
{
	for (int i = 0; i < 4; i++) {
		line tempLine;
		tempLine.start_x = ballPosition[i][0];
		tempLine.start_y = ballPosition[i][1];
		tempLine.end_x = ballPosition[i][2];
		tempLine.end_y = ballPosition[i][3];
		this->lines.push_back(tempLine);

		point newPoint;
		newPoint.x = tempLine.start_x;
		newPoint.y = tempLine.start_y;
		this->collisionPoints.push_back(newPoint);
	}
	this->startPosition = lines;
}

//Draw a ball on the table
void Ball::drawBall()
{
	for (line tempLine : lines)
		App::DrawLine(tempLine.start_x, tempLine.start_y, tempLine.end_x, tempLine.end_y, 1.0, 1.0, 0.7);
}



//Add gravity to the ball
void Ball::setGravity()
{
	velocity_Y -= gravity * 4/1000;
}

//Check the ball is on the table
void Ball::checkGameOver()
{
	for (int i = 0; i < lines.size(); i++) {
		if (lines[i].start_y > -200 || lines[i].end_y > -200) return;
	}
	notstart = true;
	lines = startPosition;
	velocity_X = 0;
	velocity_Y = 0;

}

//Update the ball's collition point
void Ball::updateCollisionPoint()
{
	for (int i = 0; i < lines.size(); i++)
	{
		collisionPoints[i].x = lines[i].start_x;
		collisionPoints[i].y = lines[i].start_y;
	}
}

bool lineLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	float uA = ((x4 - x3)*(y1 - y3) - (y4 - y3)*(x1 - x3)) / ((y4 - y3)*(x2 - x1) - (x4 - x3)*(y2 - y1));
	float uB = ((x2 - x1)*(y1 - y3) - (y2 - y1)*(x1 - x3)) / ((y4 - y3)*(x2 - x1) - (x4 - x3)*(y2 - y1));

	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {
		return true;
	}
	return false;
}

int Ball::collisionDetection(float x1, float y1, float x2, float y2, char* string)
{
	float rx = lines[0].start_x;
	float ry = lines[0].start_y;
	float rw = 21;
	float rh = 19;

	int score = 0;

	//left side
	if (lineLine(x1, y1, x2, y2, rx - 15, ry, rx - 15, ry - rh))
	{
		velocity_X *= -1;
		OutputDebugString(_T("Hit left side!!!\n"));
		if (string == "5 ") score = 10;
	}

	//right side
	 if (lineLine(x1, y1, x2, y2, rx + rw + 5, ry - 5, rx + rw + 5, ry - rh + 5))
	{
		velocity_X *= -1;
		OutputDebugString(_T("Hit right side!!!\n"));
		if (string == "5 ") score = 10;
	}

	//top side
	 if (lineLine(x1, y1, x2, y2, rx, ry, rx + rw, ry))
	{
		velocity_Y *= -1;
		OutputDebugString(_T("Hit top side!!!\n"));
		if (string == "5 ") score = 10;
	}

	//bottom side
	 if (lineLine(x1, y1, x2, y2, rx, ry - rh -5, rx + rw, ry - rh -5))
	{
		 if (string == "paddle") 
		 {
			 //velocity_X += 3;
			 velocity_Y += 5;
		 }
		velocity_Y *= -1;
		if (string == "5 ") score = 10;
		OutputDebugString(_T("Hit bottom side!!!\n"));
		
	}

	 return score;
}


Ball::~Ball()
{
}
