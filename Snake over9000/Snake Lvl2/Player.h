#pragma once
#include "Sprite.h"
#include <list>

class Sprite;
class DrawEngine;
class SnakeBody;

class Player : public Sprite {
public:
	/*	Player constructor
	*	@param de DrawEngine which is drawing this player on screen.
	*	@param posx Initial X coordinate position on grid map
	*	@param posy Initial Y coordinate position on grid map
	*	@param index Assign the sprite index that will be used to draw the Player Sprite.
	*	@param draw If the sprite should be drawn on screen upon initializing it or not.
	*	@param speed The game speed at which the player will move
	*	@param extraParts How many extra body parts will the player start with.
	*/
	Player(DrawEngine *de, int posx, int posy, int index, bool draw, double speed, int extraParts);
	~Player(void);

	/*	Set the player movement speed.
	*	@param speed The new player speed.
	*/
	void SetSpeed(double speed);

	/*	Return the player's position from the previous frame.
	*	This method is used to calculate the movement for other player's body pieces.
	*/
	vector2 GetLastPosition(void);

	//Erases player, recalculate face direction, move player, re-draw player.
	void Move(void);
	
	/*	Automatically calls Move on the player and all body parts every frame. Gets player input to change it's direction.
	*	@param *key Player input.
	*/
	void AutoMove(char *key);

	//Flips the autoMove bool.
	void AutoMoveToggle(void);

	/*	Sets the autoMove bool.
	*	@param start New value for autoMove
	*/
	void AutoMoveToggle(bool start);

	//Returns how many apples were eaten this game.
	int GetAppleCount(void);

	//Increments appleCount by 1
	void EatApple(void);

	//Clears all body parts and the list, erases screen, deletes player from memory.
	void ResetGame(void);

protected:
	using Sprite::de;
	vector2 lastPosition;

private:
	int faceDir; //direction the player is facing
	int lastDir; //last direction player was facing. Used to guide body parts
	bool autoMoving; //if player is auto moving
	double speed;
	double movement; //how much movement the player has accumulated. When above 1, players move one cell and this value resets
	int appleCount; //how many apples player ate
	std::list<SnakeBody*> snakeList; //list containing all player body parts
	int initialLength; //how many body parts the player starts with

private:
	/*	Checks if the next player movement will collide with another body part or an apple.
	*	@param posx X position on grid for the next movement cell.
	*	@param posy Y position on grid for the next movement cell.
	*	return Returns true if player hit itself and draws Game Over screen
	*/
	bool CheckCollision(int posx, int posy);

	/*	Grows the snake by a set amount of pieces.
	*	@param quantity How many body parts to add to the snake.
	*/
	void GrowBodyPart(int quantity);
	
};