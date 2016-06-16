#pragma once
#include "Player.h"

class DrawEngine;

class SnakeBody : public Player {
public:
	/*	Snake body pieces constructor
	*	@param *de DrawEngine which is drawing this body part on screen.
	*	@param posx Initial X coordinate position on grid map
	*	@param posy Initial Y coordinate position on grid map
	*	@param index Assign the sprite index that will be used to draw the body part Sprite.
	*	@param draw If the sprite should be drawn on screen upon initializing it or not.
	*	@param speed The game speed at which the player will move
	*	@param *connection The connection is a piece by which this object will be attached to. It inherits its movement.
	*/
	SnakeBody(DrawEngine *de, int posx, int posy, int index, bool draw, double speed, Player *connection); 
	~SnakeBody();

	//Erases body piece, gets the last movement from its connection, copies it, re-draws body piece
	void Move(void);

	/*	Draws body piece in the target position.
	*	@param x X coordinate in the grid map to be drawn.
	*	@param y Y coordinate in the grid map to be drawn.
	*/
	void SpawnAtPosition(int x, int y);

protected:

private:
	Player * connection; //the snakeBody part is always connected to another bodypart or the player

};