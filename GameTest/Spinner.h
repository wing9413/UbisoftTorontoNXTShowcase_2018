#pragma once
#include <vector>
#include "Line.h"
class Spinner
{
public:
	//properties of the paddle
	std::vector<line> lines;

	//fixed point for rotation, float fix_x and float fix_y
	float fix_x;
	float fix_y;



public:
	Spinner();
	void drawSpinner();
	void rotate();
	~Spinner();
};

