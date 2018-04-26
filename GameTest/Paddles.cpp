#include "stdafx.h"
#include "Paddles.h"
#include "app\app.h"
#include <math.h>
#include <vector>
#include "Line.h"

//size of the paddle is defined
float paddlePosition[3][4] = { { 277, 120, 405, 82 },
{ 405, 82, 271, 110 },
{ 271, 110, 277, 120 } };



Paddles::Paddles(float tempX, float tempY)
{
	for (int i = 0; i < 3; i++) {
		line tempLine;
		tempLine.start_x = paddlePosition[i][0];
		tempLine.start_y = paddlePosition[i][1];
		tempLine.end_x = paddlePosition[i][2];
		tempLine.end_y = paddlePosition[i][3];
		this->lines.push_back(tempLine);
	}
	this->fix_x = tempX;
	this->fix_y = tempY;
}

//Paddle rotates around a fixed point by float angle
void Paddles::setPaddleAngle(float angle)
{
	originalLines = lines;
	float s = sin(angle);
	float c = cos(angle);


	for (int i = 0; i < lines.size(); i++) {
		float temp_startx = lines[i].start_x - fix_x;
		float temp_starty = lines[i].start_y - fix_y;
		float temp_endx = lines[i].end_x - fix_x;
		float temp_endy = lines[i].end_y - fix_y;

		//rotate point 
		float start_xnew = temp_startx *c + temp_starty *s;
		float start_ynew = temp_startx *s - temp_starty *c;
		float end_xnew = temp_endx *c + temp_endy *s;
		float end_ynew = temp_endx *s - temp_endy *c;

		temp_startx = start_xnew + fix_x;
		temp_starty = start_ynew + fix_y;
		temp_endx = end_xnew + fix_x;
		temp_endy = end_ynew + fix_y;

		line newLine;
		newLine.start_x = temp_startx;
		newLine.start_y = temp_starty;
		newLine.end_x = temp_endx;
		newLine.end_y = temp_endy;
		movedLines.push_back(newLine);
	}
}

//Reflect the paddle and move horizontally on float on_fixx
void Paddles::reflectPaddle(float on_fixx)
{
	for (int i = 0; i < lines.size(); i++) {
		lines[i].start_x = -(lines[i].start_x) + on_fixx;
		lines[i].end_x = -(lines[i].end_x) + on_fixx;
	}
}

//Draw the paddle on the table
void Paddles::drawPaddle()
{
	for (line tempLine : lines) 
		App::DrawLine(tempLine.start_x, tempLine.start_y, tempLine.end_x, tempLine.end_y, 0.3, 1.0, 0.65);
}

//move the paddle when key is pressed
void Paddles::flipPaddle()
{
	lines = movedLines;
}

//release the paddle when key is released
void Paddles::releasePaddle() 
{
	lines = originalLines;
}

Paddles::~Paddles()
{
}
