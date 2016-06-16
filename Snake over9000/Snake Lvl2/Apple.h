#pragma once
#include "Sprite.h"
class DrawEngine;

class Apple : public Sprite {
public:
	/*	Apple constructor
	*	@param de DrawEngine which is drawing this apple on screen.
	*	@param posx Initial X coordinate position on grid map
	*	@param posy Initial Y coordinate position on grid map
	*	@param index Assign the sprite index that will be used to draw the Apple Sprite.
	*	@param draw If the sprite should be drawn on screen upon initializing it or not.
	*/
	Apple(DrawEngine *de, int posx, int posy, int index, bool draw);
	~Apple();

	//Randomizes a location not being occupied by the player and draws the apple there.
	void SpawnApple(void);

protected:
	using Sprite::de;
	using Sprite::index;

};