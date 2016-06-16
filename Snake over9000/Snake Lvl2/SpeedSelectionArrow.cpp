#include "SpeedSelectionArrow.h"
#include "DrawEngine.h"
#include <iostream>

/*	SpeedSelectionArrow constructor
*	@param de DrawEngine which is drawing this player on screen.
*	@param x Initial X coordinate position on grid map
*	@param y Initial Y coordinate position on grid map
*	@param index Assign the sprite index that will be used to draw the Player Sprite.
*	@param initSpeed The initial speed at which the selection arrow will be pointed at.
*/
SpeedSelectionArrow::SpeedSelectionArrow(DrawEngine *de, int x, int y, int index, int initSpeed) : Sprite (de, x, y, index, true)
{
	de->DrawSprite(index, x, y);
	speedIndex = initSpeed;
}

SpeedSelectionArrow::~SpeedSelectionArrow()
{
	de->EraseSprite(GetX(), GetY()); //erases it from screen before deleting from memory
}

/*	Move the selection between speed indicators from 1 to 9
*	@param *key User input.
*	@param *gameSpeed Reference to the game speed.
*/
void SpeedSelectionArrow::SelectSpeed(char *key, int *gameSpeed)
{
	*key = GetKey(); //get user input
	int arrowDetector = *key; //detects if player is using the special arrow characters

	int x = 0;

	//move the arrow to the left to the previous speed indicator
	if ((*key == LEFT_KEY || arrowDetector == LEFT_ARROW) && speedIndex != 1)
	{
		speedIndex--;
		x = GetX() - 2; //each speed indicator is 2 grid spaces from each other
		Move(x);
	}

	//move the arrow to the right to the next speed indicator
	if ((*key == RIGHT_KEY || arrowDetector == RIGHT_ARROW) && speedIndex != 9)
	{
		speedIndex++;
		x = GetX() + 2; //each speed indicator is 2 grid spaces from each other
		Move(x);
	}

	if (arrowDetector == 13) //13 is the code for Return
	{
		*gameSpeed = SetSpeed();
	}
	
}

//returns the speed currently selected (speedIndex).
int SpeedSelectionArrow::SetSpeed(void)
{
	return speedIndex;
}

/*	Erase speed selection arrow, moves it to the new indicator and re-draw
*	@param x New X position in the grid map.
*/
void SpeedSelectionArrow::Move(int x)
{
	//erase current arrow
	de->EraseSprite(GetX(), GetY());

	SetX(x);

	//draw at new position
	de->DrawSprite(index, GetX(), GetY());
}
