#pragma once
#include "Sprite.h"
#include <conio.h>

class DrawEngine;

class SpeedSelectionArrow : Sprite {
public:

	/*	SpeedSelectionArrow constructor
	*	@param de DrawEngine which is drawing this arrow on screen.
	*	@param x Initial X coordinate position on grid map
	*	@param y Initial Y coordinate position on grid map
	*	@param index Assign the sprite index that will be used to draw the SpeedSelectionArrow Sprite.
	*	@param initSpeed The initial speed at which the selection arrow will be pointed at.
	*/
	SpeedSelectionArrow(DrawEngine *de, int x, int y, int index, int initSpeed);
	~SpeedSelectionArrow();

	/*	Move the selection between speed indicators from 1 to 9
	*	@param *key User input.
	*	@param *gameSpeed Reference to the game speed.
	*/
	void SelectSpeed(char *key, int *gameSpeed);

	//returns the speed currently selected (speedIndex).
	int SetSpeed(void);

protected:
private:
	/*	Erase speed selection arrow, moves it to the new indicator and re-draw	
	*	@param x New X position in the grid map.
	*/
	void Move(int x);
	int speedIndex; //tracks the speed being selected.
};