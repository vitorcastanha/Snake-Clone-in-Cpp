#include "Player.h"
#include <conio.h>
#include "DrawEngine.h"
#include "SnakeBody.h"

enum
{
	NO_MOVE, //player hasn't moved yet
	DOWN_MOVE,
	UP_MOVE,
	LEFT_MOVE,
	RIGHT_MOVE
};

/*	Player constructor
*	@param de DrawEngine which is drawing this player on screen.
*	@param posx Initial X coordinate position on grid map
*	@param posy Initial Y coordinate position on grid map
*	@param index Assign the sprite index that will be used to draw the Player Sprite.
*	@param draw If the sprite should be drawn on screen upon initializing it or not.
*	@param speed The game speed at which the player will move
*	@param extraParts How many extra body parts will the player start with.
*/
Player::Player(DrawEngine * de, int posx, int posy, int index, bool draw, double speed, int lentgh) : Sprite (de, posx, posy, index, draw)
{
	this->speed = speed * 0.1; //normal speed uses higher number to make it easier to work with, however it would be too fast.
	GrowBodyPart(lentgh);
	initialLength = lentgh;
	movement = 0;
	appleCount = 0;
}

Player::~Player(void)
{
	//deconstruct player
	de->EraseSprite(GetX(), GetY());
}

/*	Set the player movement speed.
*	@param speed The new player speed.
*/
void Player::SetSpeed(double speed)
{
	this->speed = speed;
}

/*	Return the player's position from the previous frame.
*	This method is used to calculate the movement for other player's body pieces.
*/
vector2 Player::GetLastPosition(void)
{
	return this->lastPosition;
}

//Erases player, recalculate face direction, move player, re-draw player.
void Player::Move(void)
{
	movement += this->speed; //auto move speed

	//erase current location
	Erase(GetX(), GetY());

	//change position when enough motion has occured.
	if (movement > 1)
	{
		//last position can only be updated on move, otherwise the body parts will move every frame
		lastPosition.posx = GetX();
		lastPosition.posy = GetY();

		//updates next movement according to current face direction
		switch (faceDir)
		{
		case NO_MOVE:
			break;
		case LEFT_MOVE:
			SetX(GetX() - 1);
			lastDir = LEFT_MOVE;
			break;
		case RIGHT_MOVE:
			SetX(GetX() + 1);
			lastDir = RIGHT_MOVE;
			break;
		case UP_MOVE:
			SetY(GetY() - 1); //inverted on windows console
			lastDir = UP_MOVE;
			break;
		case DOWN_MOVE:
			SetY(GetY() + 1);
			lastDir = DOWN_MOVE;
			break;
		default:
			break;
		}

		movement = 0; //resets accumulated movement
	}

	//If player reaches the end of the map, he teleports to the other end. Around the world trip.
	//All the +1's and -1's are to account for the walls
	//LEFT BORDER
	if (GetX() > de->GetScreenWidth() - 1)
	{
		SetX(LEFT_BORDER + 1);
	}
	//RIGHT BORDER
	if (GetX() < LEFT_BORDER + 1)
	{
		SetX(de->GetScreenWidth() - 1);
	}
	//BOTTOM BORDER
	if (GetY() > de->GetScreenHeight() - 1)
	{
		SetY( TOP_BORDER + 1);
	}
	//TOP BORDER
	if (GetY() < TOP_BORDER + 1)
	{
		SetY( de->GetScreenHeight() - 1);
	}

	//check for collision
	if (CheckCollision(GetX(), GetY())) {
		return;
	}

	//draw in new position
	Draw(GetX(), GetY());

}

/*	Checks if the next player movement will collide with another body part or an apple.
*	@param posx X position on grid for the next movement cell.
*	@param posy Y position on grid for the next movement cell.
*	return Returns true if player hit itself and draws Game Over screen
*/
bool Player::CheckCollision(int posx, int posy)
{
	//if player is colliding with itself
	if (de->GetSpriteFromPosition(posx, posy) == de->GetSpriteFromIndex(PLAYER_INDEX))
	{
		AutoMoveToggle();
		de->DrawEndGame(speed * 10, appleCount); //draws Game Over screen
		return true;
	}

	//if player is colliding with an apple
	else if (de->GetSpriteFromPosition(posx, posy) == de->GetSpriteFromIndex(APPLE_INDEX))
	{
		EatApple();
		GrowBodyPart(1); //increase snake body by 1 piece.
	}
	return false;
}

/*	Grows the snake by a set amount of pieces.
*	@param quantity How many body parts to add to the snake.
*/
void Player::GrowBodyPart(int quantity)
{
	int x = 0;
	int y = 0;

	for (int i = 1; i < quantity + 1; i++)
	{
		if (snakeList.size() == 0)
		{
			if (faceDir == NO_MOVE)
			{
				x = GetX() - 1;
				y = GetY();
			}
			else {
				//this should never happen naturally.
				x = GetLastPosition().posx;
				y = GetLastPosition().posy;
			}

			SnakeBody * bodyPart = new SnakeBody(de, x, y, 0, 1, this->speed, this);
			snakeList.push_back(bodyPart);
		}
		else {
			if (faceDir == NO_MOVE)
			{
				x = snakeList.back()->GetX() - 1;
				y = snakeList.back()->GetY();
			}
			else
			{
				//this should happen very often
				x = snakeList.back()->GetLastPosition().posx;
				y = snakeList.back()->GetLastPosition().posy;
			}
			

			SnakeBody * bodyPart = new SnakeBody(de, x, y, 0, 1, this->speed, snakeList.back());
			snakeList.push_back(bodyPart);
		}
		
	}
	
}

//Clears all body parts and the list, erases screen, deletes player from memory.
void Player::ResetGame(void) {

	//clean memory from body parts
	for (int i = snakeList.size(); i > 0; i--)
	{
		SnakeBody * temp = snakeList.back();
		snakeList.pop_back();
		delete temp;
	}

	//remove the End game message
	de->EraseEndGame();
	delete this;
}

/*	Automatically calls Move on the player and all body parts every frame. Gets player input to change it's direction.
*	@param *key Player input.
*/
void Player::AutoMove(char *key)
{
	*key = GetKey(); //get player input

	if (!autoMoving)
	{
		return; //player not moving
	}
	
	int arrowKeyChecker = *key; //gets the input in an integer code format. We use this to check for arrow inputs below

	if ((*key == LEFT_KEY || arrowKeyChecker == LEFT_ARROW) && lastDir != RIGHT_MOVE && faceDir != NO_MOVE) // player can't do a 180º turn
	{
		faceDir = LEFT_MOVE;
	}
	else if ((*key == RIGHT_KEY || arrowKeyChecker == RIGHT_ARROW) && lastDir != LEFT_MOVE)
	{
		faceDir = RIGHT_MOVE;
	}
	else if ((*key == UP_KEY || arrowKeyChecker == UP_ARROW) && lastDir != DOWN_MOVE)
	{
		faceDir = UP_MOVE;
	}
	else if ((*key == DOWN_KEY || arrowKeyChecker == DOWN_ARROW) && lastDir != UP_MOVE)
	{
		faceDir = DOWN_MOVE;
	}

	Move();
	
	if (faceDir == NO_MOVE) //means the player hasn't moved yet this game
	{
		return;
	}

	//goes through the body parts list and move all of them.
	std::list<SnakeBody*>::iterator Iter;
	for (Iter = snakeList.begin(); Iter != snakeList.end(); Iter++)
	{
		(*Iter)->Move();
	}
}

//Flips the autoMove bool.
void Player::AutoMoveToggle(void)
{
	autoMoving = !autoMoving;
}

/*	Sets the autoMove bool.
*	@param start New value for autoMove
*/
void Player::AutoMoveToggle(bool start)
{
	autoMoving = start;
}

//Returns how many apples were eaten this game.
int Player::GetAppleCount(void)
{
	return appleCount;
}

//Increments appleCount by 1
void Player::EatApple(void)
{
	appleCount++;
}