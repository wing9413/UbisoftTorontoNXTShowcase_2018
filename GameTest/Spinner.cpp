#include "stdafx.h"
#include "Spinner.h"
#include "app\app.h"
#include <math.h>
#include <vector>
#include "Line.h"

//size of the spinner is defined
float spinnerPosition[5][4] = { { 379 ,398 ,363 ,443 },
{ 379, 398, 432 ,423 },
{ 379, 398 ,339, 392 },
{ 379, 398, 372, 361 },
{ 379, 398, 432, 374 } };





Spinner::Spinner()
{
	for (int i = 0; i < 5; i++) {
		line tempLine;
		tempLine.start_x = spinnerPosition[i][0];
		tempLine.start_y = spinnerPosition[i][1];
		tempLine.end_x = spinnerPosition[i][2];
		tempLine.end_y = spinnerPosition[i][3];
		this->lines.push_back(tempLine);
	}
	this->fix_x = 356;
	this->fix_y = 387;
}

void Spinner::drawSpinner()
{
	for (line tempLine : lines)
		App::DrawLine(tempLine.start_x, tempLine.start_y, tempLine.end_x, tempLine.end_y, 0.1, 0.6, 1.0);
}

void Spinner::rotate()
{
	float angle = 1;
	float s = sin(angle);
	float c = cos(angle);
	for (int i = 0; i < lines.size(); i++) 
	{
		float temp_startx = lines[i].start_x - fix_x;
		float temp_starty = lines[i].start_y - fix_y;
		float temp_endx = lines[i].end_x - fix_x;
		float temp_endy = lines[i].end_y - fix_y;

		//rotate point 
		float start_xnew = temp_startx * c + temp_starty * s;
		float start_ynew = temp_startx * s - temp_starty * c;
		float end_xnew = temp_endx * c + temp_endy * s;
		float end_ynew = temp_endx * s - temp_endy * c;

		lines[i].start_x = start_xnew + fix_x;
		lines[i].start_y = start_ynew + fix_y;
		lines[i].end_x = end_xnew + fix_x;
		lines[i].end_y = end_ynew + fix_y;

	}
}

Spinner::~Spinner()
{
}
