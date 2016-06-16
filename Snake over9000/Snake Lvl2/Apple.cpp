#include "Apple.h"
#include <stdlib.h>
#include "DrawEngine.h"
#include <time.h>

Apple::Apple(DrawEngine * de, int posx, int posy, int index, bool draw) : Sprite (de, posx, posy, index, draw)
{
	//resets srand
	srand(time(NULL));
}

Apple::~Apple()
{

}

void Apple::SpawnApple(void)
{
	//the +1's are to account for the walls
	int x = rand() % (de->GetScreenWidth() -2) + LEFT_BORDER +1;
	int y = rand() % (de->GetScreenHeight() -3) + TOP_BORDER + 1;
	
	//if the random location is being occupied by the player, try to spawn again.
	if (de->GetSpriteFromPosition(x,y) == de->GetSpriteFromIndex(PLAYER_INDEX))
	{
		SpawnApple();
		return;
	}

	//set the location
	SetX(x);
	SetY(y);

	//draw apple sprite at the randomized location
	de->DrawSprite(index, x, y);
}
