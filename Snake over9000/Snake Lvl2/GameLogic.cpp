#include "GameLogic.h"
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <mmsystem.h>

#define FRAME_PER_SECOND 1000/30 //how many frames per second the game will be limited at
#define BODY_SIZE 6 //the snake initial size in body parts

#define DRAW true
#define DONT_DRAW false

#define NO_SPEED_SELECTED -2
#define SUGESTED_SPEED 5
#define PLAYER_SPRITE 1
#define APPLE_SPRITE '*'
#define UI_ARROW_SPRITE '^'

GameLogic::GameLogic(void)
{
	frameCount = 0;
	PlaySound(TEXT("MusicLoop.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); //plays song
	
	Start(); //Play start once

	//Initializes variables
	double lastTime = timeGetTime();
	Time.deltaTime = 0;
	double currentTime = 0;
	double playTime = 0;
	gameSpeed = NO_SPEED_SELECTED;
	gameStarted = false;

	//If the key 'Q' is pressed, stop the game logic.
	while (key != 'q')
	{
		Time.deltaTime = (timeGetTime() - lastTime); //Calculate deltaTime
		currentTime += Time.deltaTime; //tracks time between frames
		playTime += Time.deltaTime; //tracks total play time

		//normilizes the frames per second the game will run at.
		if (currentTime > FRAME_PER_SECOND)
		{
			frameCount++;
			currentTime = 0;
			Update(); //Update game every frame

			//Draws the frame per seconds
			de->GoToXY(42, 0);
			cout << (frameCount / (playTime * 0.001)) << endl; //FRAME PER SECOND
		}
		

		lastTime = timeGetTime();
		
	}

}

GameLogic::~GameLogic(void)
{
	delete de; //Clears Draw Engine from memory
}

//Plays at the start of the game once
void GameLogic::Start(void)
{
	//Draw Game
	cout << "Welcome to SNAKE THE GAME vOver9000! FPS: ";
	de = new DrawEngine(24, 12);
	de->DrawLimits();
	de->DrawIntroScreen();
	de->CreateSprite(3, ' '); //Creates the 'empty area' sprite
	Sprite *startGame = new Sprite(de,0,0,3,false); //creates a temporary sprite to get the user input
	while (startGame->GetKey() != 13)
	{
		//wait for player to be ready.
	}
	de->EraseGameScreen();
	delete startGame; //delete temporary sprite from memory
	de->DrawSpeedSelection();
	de->CreateSprite(2, UI_ARROW_SPRITE); //Create the 'UI speed selection' arrow
	uiArrow = new SpeedSelectionArrow(de, 12, 8, 2, SUGESTED_SPEED);//instantiate the UI arrow
	de->DrawInstructions(30, 2);
}

//Plays every frame
void GameLogic::Update(void)
{
	//wait for player to choose the speed before moving on
	if (gameSpeed == NO_SPEED_SELECTED) {
		de->DrawHighScore(30, 12);
		uiArrow->SelectSpeed(&key, &gameSpeed);
		return;
	}
	
	//resets the game if gameStarted is true
	if (!gameStarted)
		StartGame();
		
	char * keyPointer = &key; //stores user input

	//AutoMove will control player inputs. We need the key pointer to update key from player so the Game Logic can check if
	//any game input is being recorded, such as quitting the game.
	player->AutoMove(keyPointer);
	de->DrawPointSystem(gameSpeed, player->GetAppleCount());

	//If there is no apple sprite drawn at the apple location, re-spawn the apple
	if (de->GetSpriteFromPosition(apple->GetX(), apple->GetY()) != APPLE_SPRITE)
	{
		apple->SpawnApple();
	}

	//Restart the game
	if (key == 'r')
	{
		player->ResetGame();
		de->EraseGameScreen();
		de->DrawSpeedSelection();
		de->CreateSprite(2, UI_ARROW_SPRITE);
		uiArrow = new SpeedSelectionArrow(de, 12, 8, 2, SUGESTED_SPEED);
		gameSpeed = NO_SPEED_SELECTED;
		gameStarted = false;
	}
}

//Gets player input
bool GameLogic::GetKey(void)
{
	if (_kbhit())
	{
		key = _getch();
		return true;
	}
	return false;
}

//Clean the game screen, initializes player and apple, delete UI from memory
void GameLogic::StartGame(void)
{
	//clean the UI from the game scene
	delete uiArrow;
	de->EraseGameScreen();

	//Create player
	de->CreateSprite(0, PLAYER_SPRITE);
	player = new Player(de, 11, 7, 0, DRAW, gameSpeed, BODY_SIZE);
	player->AutoMoveToggle(true);

	//Start the apple madness
	de->CreateSprite(1, APPLE_SPRITE);
	apple = new Apple(de, 0, 0, 1, DONT_DRAW);
	apple->SpawnApple();

	//make sure this function only run once, if the bool is false.
	gameStarted = true;
}