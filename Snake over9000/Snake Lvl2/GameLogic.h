#pragma once
#include <iostream>
#include "DrawEngine.h"
#include "Player.h"
#include "Apple.h"
#include "SpeedSelectionArrow.h"

using namespace std;

//time between last frame and current frame
struct timeStruct {
	double deltaTime;
};

class GameLogic {
public:
	
	GameLogic(void);
	~GameLogic(void);
	timeStruct Time; //keeps track of deltaTime

protected:
	virtual void Start(void); //Plays at the start of the game once
	virtual void Update(void); //Plays every frame
	virtual bool GetKey(void); //Gets player input
private:
	DrawEngine * de; //DrawEngine reference
	Player *player; //stores the current player being used
	Apple *apple; //stores the current apple being used
	SpeedSelectionArrow *uiArrow; //stores the UI speed selection arrow
	char key; //stores player Input
	int frameCount; //count frames to calculate FPS
	int gameSpeed; //current game speed
	bool gameStarted; //True if the game is running

private:
	//Clean the game screen, initializes player and apple, delete UI from memory
	void StartGame(void);
};