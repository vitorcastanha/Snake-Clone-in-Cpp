#include "SnakeBody.h"
#include "DrawEngine.h"

/*	Snake body pieces constructor
*	@param *de DrawEngine which is drawing this player on screen.
*	@param posx Initial X coordinate position on grid map
*	@param posy Initial Y coordinate position on grid map
*	@param index Assign the sprite index that will be used to draw the Player Sprite.
*	@param draw If the sprite should be drawn on screen upon initializing it or not.
*	@param speed The game speed at which the player will move
*	@param *connection The connection is a piece by which this object will be attached to. It inherits its movement.
*/
SnakeBody::SnakeBody(DrawEngine * de, int posx, int posy, int index, bool draw, double speed, Player *connection) : Player(de, posx, posy, index, draw, speed, 0)
{
	this->connection = connection;
}

SnakeBody::~SnakeBody()
{
	//The player is responsible for deleting the body parts.
}

//Erases body piece, gets the last movement from its connection, copies it, re-draws body piece
void SnakeBody::Move(void)
{
	//erase current position
	de->EraseSprite(GetX(), GetY());

	lastPosition.posx = GetX();
	lastPosition.posy = GetY();

	//set new position, only after the connected snake piece has moved
	if (connection->GetLastPosition().posx != connection->GetX()
		|| connection->GetLastPosition().posy != connection->GetY())
	{
		SetX(connection->GetLastPosition().posx);
		SetY(connection->GetLastPosition().posy);
	}

	//draw new position
	de->DrawSprite(index, GetX(), GetY());
}

/*	Draws body piece in the target position.
*	@param x X coordinate in the grid map to be drawn.
*	@param y Y coordinate in the grid map to be drawn.
*/
void SnakeBody::SpawnAtPosition(int x, int y)
{
	de->DrawSprite(index, x, y);
}
