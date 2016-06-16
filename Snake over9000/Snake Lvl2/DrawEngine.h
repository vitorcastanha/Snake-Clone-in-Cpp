#pragma once
#include "Sprite.h"
#include <string>

#define TOP_BORDER 2
#define LEFT_BORDER 1

enum
{
	PLAYER_INDEX,
	APPLE_INDEX
};

class DrawEngine {
public:
	
	/*	DrawEngine constructor.
	*	@param xSize How many units the grid map has horizontally.
	*	@param ySize How many units the grid map has vertically.
	*/
	DrawEngine(int xSize = 30, int ySize = 20);
	~DrawEngine();
	
	/*	This method creates a sprite(ASCII character) for a certain index.
	*	@param index Index of the array spriteImage where the character will be stored.
	*	@param c Defines the sprite(ASCII character).
	*/
	void CreateSprite(int index, char c);
	
	/*	Sets the target sprite index to NULL.
	*	@param index Index of the array spriteImage to be cleared.
	*/
	void DeleteSprite(int index);
	
	/*	Returns the sprite at the target index.
	*	@param index Index of the array spriteImage to be returned.
	*/
	char GetSpriteFromIndex(int index);

	/*	Draws sprite at the target coordinate
	*	@param index Index of the array spriteImage to be drawn.
	*	@param posx X position in the grid
	*	@param posy Y position in the grid
	*/
	void DrawSprite(int index, int posx, int posy);

	/*	Draws a space at the target coordinate. Overrides whatever is written there.
	*	@param posx X position in the grid
	*	@param posy Y position in the grid
	*/
	void EraseSprite(int posx, int posy);
	
	/*	Move the Console's cursor to the target location
	*	@param posx X position in the console
	*	@param posy Y position in the console
	*/
	void GoToXY(int posx, int posy);

	//	Hides the cursor in the Console
	void HideCursor(void);

	//	Returns the screen width defined by the DrawEngine
	int GetScreenWidth(void);

	//	Returns the screen height defined by the DrawEngine
	int GetScreenHeight(void);

	//	Draws the game screen borders
	void DrawLimits(void);

	/*	Draws on screen how many points the user have and how many apples he ate.
	*	@param gameSpeed The speed by which the game is set.
	*	@param appleCount How many apples the player ate.
	*/
	void DrawPointSystem(int gameSpeed, int appleCount);

	/*	Sets the character in the grid matrix at the target position
	*	@param posx X position in the grid matrix.
	*	@param posy Y position in the grid matrix.
	*	@param c Character to be stored in the matrix.
	*/
	void RecordPositionOnGrid(int posx, int posy, char c);

	/*	Returns the sprite that is located at the target position
	*	@param posx X position in the grid
	*	@param posy Y position in the grid
	*/
	char GetSpriteFromPosition(int posx, int posy);
	
	/*	Draws the Game Over screen.
	*	Calculates the player score and store it in an external file in order to track Highscores.
	*	@param gameSpeed The speed by which the game is set.
	*	@param appleCount How many apples the player ate.
	*/
	void DrawEndGame(int gameSpeed, int appleCount);

	//	Erase the Game Over screen.
	void EraseEndGame(void);

	//	Draw the introduction screen.
	void DrawIntroScreen(void);

	//	Draw the speed selection screen.
	void DrawSpeedSelection(void);

	//	Erase the game screen.
	void EraseGameScreen(void);

	/*	Draws the controls on screen.
	*	@param x X position on the console to start drawing.
	*	@param y Y position on the console to start drawing.
	*/
	void DrawInstructions(int x, int y);

	/*	Read the highscore from the external file and draw it on screen.
	*	@param x X position on the console to start drawing.
	*	@param y Y position on the console to start drawing.
	*/
	void DrawHighScore(int x, int y);

protected:
	int screenWidth, screenHeight; //map length and height in units.

private:
	char spriteImage[16];	//sprite container
	char **gridMap;		//gridMap matrix. It is used to track where the sprites are located in the game map.

private:
	
	/*	Initializes the gridMap based on the map size.
	*	@param xSize The map length in units.
	*	@param ySize The map height in units.
	*/
	void CreateGrid(int xSize, int ySize);
};