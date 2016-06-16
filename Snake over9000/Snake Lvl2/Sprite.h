#pragma once

class DrawEngine;

struct vector2
{
	double posx;
	double posy;
};

//Player Inputs
#define LEFT_KEY 'a'
#define LEFT_ARROW 75
#define RIGHT_KEY 'd'
#define RIGHT_ARROW 77
#define UP_KEY 'w'
#define UP_ARROW 72
#define DOWN_KEY 's'
#define DOWN_ARROW 80

class Sprite {
public:
	/*	Sprite constructor
	*	@param de DrawEngine which is drawing this sprite on screen.
	*	@param posx Initial X coordinate position on grid map
	*	@param posy Initial Y coordinate position on grid map
	*	@param index Assign the sprite index that will be used to draw the Sprite.
	*	@param draw If the sprite should be drawn on screen upon initializing it or not.
	*/
	Sprite(DrawEngine *de, int posx, int posy, int index, bool draw);
	~Sprite();

	//Returns the X position of the sprite
	int GetX(void);
	//Returns the Y position of the sprite
	int GetY(void);

	/*	Set the X position of the sprite in the grid map.
	*	@param posx New X position
	*/
	void SetX(int posx);

	/*	Set the Y position of the sprite in the grid map.
	*	@param posx New Y position
	*/
	void SetY(int posy);

	//Tells the player sprite which was the last input in order to set the new movement trajectory
	char GetKey(void);

protected:
	DrawEngine *de; //draw engine associated with this sprite
	int index; //the index of each sprite, used as reference to functions such as GetSpriteFromIndex(PLAYER_INDEX)

	/*	Calls the DrawEngine DrawSprite function
	*	@param posx X position in the grid
	*	@param posy Y position in the grid
	*/
	void Draw(int posx, int posy);

	/*	Calls the DrawEngine EraseSprite function
	*	@param posx X position in the grid
	*	@param posy Y position in the grid
	*/
	void Erase(int posx, int posy);

private:
	//Sprite Coordinates
	int posx;
	int posy;

};