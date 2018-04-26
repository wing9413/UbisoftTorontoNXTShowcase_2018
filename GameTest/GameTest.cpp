//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
//------------------------------------------------------------------------
#include "app\app.h"
#include "table.h"
#include "Paddles.h"
#include "ball.h"
#include "Spinner.h"

using namespace std;

//Initialize variable
CTable* pTable; //To store the pinball table
Paddles* leftPaddle;
Paddles* rightPaddle;
Ball* ball;
Spinner* spinner;

//Constant variable
const char* gameTitle = "Jenny's Pinball Game";
const char* fileName = "lineTable.txt";


int score = 0;
bool gameOver = false;
//------------------------------------------------------------------------




//Get a set of defined lines from the file
void loadFile() 
{
	std::fstream file;
	file.open(fileName, std::fstream::in);
	if (file.is_open()) {
		while (!file.eof()) {
			CLineSegment line;
			int type;
			file >> type;
			line.m_type = static_cast<LineType>(type);
			file >> line.m_start.m_x;
			file >> line.m_start.m_y;
			file >> line.m_end.m_x;
			file >> line.m_end.m_y;
			line.type = (char*)type;
			pTable->m_lines.push_back(line);
		}
	}
}



//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	pTable = new CTable;
	loadFile();

	leftPaddle = new Paddles(277,120);
	leftPaddle->setPaddleAngle(25);
	rightPaddle = new Paddles(566,120);
	rightPaddle->reflectPaddle(843);
	rightPaddle->setPaddleAngle(25);

	ball = new Ball();
	spinner = new Spinner();
}


void checkBallCollision() 
{
	//check ball collision with table
	for (auto& line : pTable->m_lines)
	{
		score += ball->collisionDetection(line.m_start.m_x, line.m_start.m_y, line.m_end.m_x, line.m_end.m_y, line.type);
		//OutputDebugString(_T("%f\n", ball->velocity_X));
	}

	//check ball collision with left paddle
	score += ball->collisionDetection(leftPaddle->lines[0].start_x, leftPaddle->lines[0].start_y,
		                     leftPaddle->lines[0].end_x, leftPaddle->lines[0].end_y, " ");

	//check ball collision with right paddle
	score += ball->collisionDetection(rightPaddle->lines[0].start_x, rightPaddle->lines[0].start_y,
		rightPaddle->lines[0].end_x, rightPaddle->lines[0].end_y, " ");
	
	for (int i = 0; i < spinner->lines.size(); i++)
	{
		score += ball->collisionDetection(spinner->lines[i].start_x, spinner->lines[i].start_y,
			spinner->lines[i].end_x, spinner->lines[i].end_y, "spinner");
	}
}


//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	
	//When the game is not start
	if (ball->notstart == true && App::IsKeyPressed(VK_SPACE)) {
		ball->notstart = false;
		ball->velocity_X = -1;
	}

	//When the game is start
	if (!ball->notstart)
	{
		ball->setGravity();
		ball->checkGameOver();
		score += 1;
		checkBallCollision(); 

		//update ball's position
		for (int i = 0; i < ball->lines.size(); i++) {
			ball->lines[i].start_x += ball->velocity_X;
			ball->lines[i].start_y += ball->velocity_Y;
			ball->lines[i].end_x += ball->velocity_X;
			ball->lines[i].end_y += ball->velocity_Y;
		}
		ball->updateCollisionPoint();
	}

	
	

	//Move the left paddle with Z
	if (App::IsKeyPressed('Z')) 
	{
		spinner->rotate();

		leftPaddle->flipPaddle();
		for (int i = 0; i < leftPaddle->lines.size(); i++)
		{
			score += ball->collisionDetection(leftPaddle->lines[i].start_x, leftPaddle->lines[i].start_y,
				leftPaddle->lines[i].end_x, leftPaddle->lines[i].end_y, "paddle");
		}
	}
	else
	{
		leftPaddle->releasePaddle();
	}

	//Move the right paddle with X
	if (App::IsKeyPressed('X'))
	{
		rightPaddle->flipPaddle();
		for (int i = 0; i < rightPaddle->lines.size(); i++)
		{
			score += ball->collisionDetection(rightPaddle->lines[i].start_x, rightPaddle->lines[i].start_y,
				rightPaddle->lines[i].end_x, rightPaddle->lines[i].end_y, "paddle");
		}
	}
	else
	{
		rightPaddle->releasePaddle();
	}
}


void printBackground() 
{
	for (auto& line : pTable->m_lines) {
		CLineDefinition& def = pTable->m_lineDefs[line.m_type];
		App::DrawLine(line.m_start.m_x, line.m_start.m_y, line.m_end.m_x, line.m_end.m_y, def.m_Red, def.m_Green, def.m_Blue);
	}
}

//print out the title and the contorl instructions
void printTitleandInstruction() 
{
	App::Print(380, 700, gameTitle, 0.8, 0.5, 0.65, GLUT_BITMAP_TIMES_ROMAN_24); // Title in Pink
	App::Print(25, 600, "Contorls:", 1.0, 0.61, 0.61, GLUT_BITMAP_HELVETICA_12);
	App::Print(25, 580, "Left paddle - Z", 1.0, 0.61, 0.61, GLUT_BITMAP_HELVETICA_12);
	App::Print(25, 560, "Right paddle - X", 1.0, 0.61, 0.61, GLUT_BITMAP_HELVETICA_12);
	App::Print(25, 540, "Drop the ball - SPACE", 1.0, 0.61, 0.61, GLUT_BITMAP_HELVETICA_12);
	App::Print(870, 640, "Time Stayed: ", 1.0, 0.61, 0.61, GLUT_BITMAP_HELVETICA_12);
	string Result;
	stringstream convert;
	convert << score;
	Result = convert.str();
	const char * c = Result.c_str();
	App::Print(870, 620, c, 1.0, 0.61, 0.61, GLUT_BITMAP_HELVETICA_12);
}


//------------------------------------------------------------------------
// Add your display calls here (DrawLine or Print) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	
	printTitleandInstruction();
	printBackground();
	leftPaddle->drawPaddle();
	rightPaddle->drawPaddle();
	ball->drawBall();
	spinner->drawSpinner();
	
	
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{
}