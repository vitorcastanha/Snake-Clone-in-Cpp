#include "Sprite.h"
#include "DrawEngine.h"
#include <conio.h>

/*	Sprite constructor
*	@param de DrawEngine which is drawing this sprite on screen.
*	@param posx Initial X coordinate position on grid map
*	@param posy Initial Y coordinate position on grid map
*	@param index Assign the sprite index that will be used to draw the Sprite.
*	@param draw If the sprite should be drawn on screen upon initializing it or not.
*/
Sprite::Sprite(DrawEngine * de, int posx, int posy, int index, bool draw)
{
	this->de = de;
	this->posx = posx;
	this->posy = posy;
	this->index = index;
	//xMovement = 0;
	//yMovement = 0;
	if (draw)
	{
		Draw(this->posx, this->posy);
	}
}

Sprite::~Sprite()
{
}

//Returns the X position of the sprite
int Sprite::GetX()
{
	return posx;
}

//Returns the Y position of the sprite
int Sprite::GetY(void)
{
	return posy;
}

/*	Set the X position of the sprite in the grid map.
*	@param posx New X position
*/
void Sprite::SetX(int posx)
{
	this->posx = posx;
}

/*	Set the Y position of the sprite in the grid map.
*	@param posx New Y position
*/
void Sprite::SetY(int posy)
{
	this->posy = posy;
}

/*	Calls the DrawEngine DrawSprite function
*	@param posx X position in the grid
*	@param posy Y position in the grid
*/
void Sprite::Draw(int posx, int posy)
{
	de->DrawSprite(index, posx, posy);
}

/*	Calls the DrawEngine EraseSprite function
*	@param posx X position in the grid
*	@param posy Y position in the grid
*/
void Sprite::Erase(int posx, int posy)
{
	de->EraseSprite(posx, posy);
}

//Tells the player sprite which was the last input in order to set the new movement trajectory
char Sprite::GetKey(void)
{
	if (_kbhit())
	{
		return _getch();
	}
	return ' ';
}