#include "DrawEngine.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#define SCORE_FILE "SnakeOver9000.bin"

/*	This method creates a sprite(ASCII character) for a certain index.
*	@param index Index of the array spriteImage where the character will be stored.
*	@param c Defines the sprite(ASCII character).
*/
void DrawEngine::CreateSprite(int index, char c)
{
	if (index >= 16 || index < 0) //makes sure that the index is within the array range.
	{
		cout << "index out of range for Create Sprite." << endl;
		getchar(); //stops the console until the user hits a key.
		return;
	}
	spriteImage[index] = c;
}

/*	DrawEngine constructor.
*	@param xSize How many units the grid map has horizontally.
*	@param ySize How many units the grid map has vertically.
*/
DrawEngine::DrawEngine(int xSize, int ySize)
{
	screenWidth = xSize;
	screenHeight = ySize;

	//Initializes the gridMap
	CreateGrid(xSize, ySize);

	//set cursor visibility to false
	HideCursor();
}

DrawEngine::~DrawEngine()
{
	//delete all variables in the matrix
	for (int i = 0; i < GetScreenWidth(); i++)
	{
		delete gridMap[i];
	}
	//delete matrix
	delete gridMap;
}

/*	Sets the target sprite index to NULL.
*	@param index Index of the array spriteImage to be cleared.
*/
void DrawEngine::DeleteSprite(int index)
{
	spriteImage[index] = NULL;
}

/*	Returns the sprite at the target index.
*	@param index Index of the array spriteImage to be returned.
*/
char DrawEngine::GetSpriteFromIndex(int index)
{
	return spriteImage[index];
}

/*	Draws sprite at the target coordinate
*	@param index Index of the array spriteImage to be drawn.
*	@param posx X position in the grid
*	@param posy Y position in the grid
*/
void DrawEngine::DrawSprite(int index, int posx, int posy)
{
	GoToXY(posx, posy);
	cout << spriteImage[index];
	RecordPositionOnGrid(posx, posy, GetSpriteFromIndex(index)); //record the sprite on the grid
}

/*	Draws a space at the target coordinate. Overrides whatever is written there.
*	@param posx X position in the grid
*	@param posy Y position in the grid
*/
void DrawEngine::EraseSprite(int posx, int posy)
{
	GoToXY(posx, posy);
	cout << " ";
	RecordPositionOnGrid(posx, posy, ' '); //erases the sprite from the grid
}

/*	Move the Console's cursor to the target location
*	@param posx X position in the console
*	@param posy Y position in the console
*/
void DrawEngine::GoToXY(int posx, int posy)
{
	HANDLE h = NULL;
	if (!h)
	{
		h = GetStdHandle(STD_OUTPUT_HANDLE); //make sure the we have the correct handle
	}
	COORD c = { posx, posy };
	SetConsoleCursorPosition(h, c);
}

//	Hides the cursor in the Console
void DrawEngine::HideCursor(void)
{
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.bVisible = 0; //set cursor visibility to 0
	info.dwSize = 1; //set percentage of the character cell filled by cursor. from 1-100
	SetConsoleCursorInfo(h, &info);
}

//	Returns the screen width defined by the DrawEngine
int DrawEngine::GetScreenWidth(void)
{
	return screenWidth;
}

//	Returns the screen height defined by the DrawEngine
int DrawEngine::GetScreenHeight(void)
{
	return screenHeight;
}

//	Draws the game screen borders
void DrawEngine::DrawLimits(void)
{
	for (int i = TOP_BORDER; i < GetScreenHeight() + 1; i++)
	{
		for (int j = LEFT_BORDER; j < GetScreenWidth() + 1; j++)
		{
			//the screen height and width are equivalent to the Y and X axis of the bottom and right borders.
			if (i == TOP_BORDER || i == GetScreenHeight() ||
				j == LEFT_BORDER || j == GetScreenWidth())
			{
				GoToXY(j, i);
				gridMap[j][i] = 219; //219 is the ASCII code to fill the whole character cell.
				cout << gridMap[j][i];
			}
		}
	}
}

/*	Draws on screen how many points the user have and how many apples he ate.
*	@param gameSpeed The speed by which the game is set.
*	@param appleCount How many apples the player ate.
*/
void DrawEngine::DrawPointSystem(int gameSpeed, int appleCount)
{
	//aligned to the left
	GoToXY(LEFT_BORDER, GetScreenHeight() + 1);
	cout << "Score: " << appleCount * gameSpeed << "    "; // the extra spaces help reseting the score later.

	//aligned to the right
	GoToXY(GetScreenWidth() - 7, GetScreenHeight() + 1);
	cout << "Speed: " << gameSpeed;
}

/*	Sets the character in the grid matrix at the target position
*	@param posx X position in the grid matrix.
*	@param posy Y position in the grid matrix.
*	@param c Character to be stored in the matrix.
*/
void DrawEngine::RecordPositionOnGrid(int posx, int posy, char c)
{
	gridMap[posx][posy] = c;
}

/*	Returns the sprite that is located at the target position
*	@param posx X position in the grid
*	@param posy Y position in the grid
*/
char DrawEngine::GetSpriteFromPosition(int posx, int posy)
{
	return gridMap[posx][posy];
}

/*	Draws the Game Over screen.
*	Calculates the player score and store it in an external file in order to track Highscores.
*	@param gameSpeed The speed by which the game is set.
*	@param appleCount How many apples the player ate.
*/
void DrawEngine::DrawEndGame(int gameSpeed, int appleCount)
{
	//calculates player score
	int score = gameSpeed * appleCount;
	//will store current high score
	int currentScore = 0;

	//draws game over screen
	GoToXY(3, 15);
	cout << "Game Over! \n Press 'R' to play again!";

	//open score file and read it
	ifstream myfile;
	myfile.open(SCORE_FILE);
	//will store the recorded value
	string recordedScore;
	while (getline(myfile, recordedScore))
	{
		string::size_type st;
		currentScore = stoi(recordedScore, &st); //convert it to an int for future computations
	}
	myfile.close();

	//if necessary open file and store new value
	if (currentScore < score)
	{
		ofstream myfile;
		myfile.open(SCORE_FILE);
		myfile << score;
		myfile.close();
	}
}

//	Erase the Game Over screen.
void DrawEngine::EraseEndGame(void)
{
	GoToXY(3, 15);
	cout << "           \n                         ";
}

//	Draw the introduction screen.
void DrawEngine::DrawIntroScreen(void) {
	
	//Draws the snake during a zig-zag movement
	{
		GoToXY(3, 5);
		char brush = 1; //ASCII code that is used on the character
		cout << brush << brush << brush;
		GoToXY(5, 6);
		cout << brush;
		GoToXY(5, 7);
		cout << brush;
		GoToXY(5, 7);
		cout << brush << brush << brush;
		GoToXY(7, 6);
		cout << brush;
		GoToXY(7, 5);
		cout << brush << brush << brush;
		GoToXY(9, 6);
		cout << brush;
		GoToXY(9, 7);
		cout << brush << brush << brush << brush << brush << brush << brush << brush;
	}

	//Draws the apple
	cout << "   " << '*';
	GoToXY(3, 9);
	cout << "Press ENTER to play!";
}

//	Draw the speed selection screen.
void DrawEngine::DrawSpeedSelection(void)
{
	GoToXY(4, 5);
	cout << "Select the speed:";
	GoToXY(4, 7);
	cout << "1 2 3 4 5 6 7 8 9";
	GoToXY(3, 10);
	cout << "Press Enter to start";
}

//	Erase the game screen.
void DrawEngine::EraseGameScreen(void)
{
	int y = TOP_BORDER + 1;
	int x = LEFT_BORDER + 1;
	GoToXY(x, y);
	for (int i = 0; i < GetScreenHeight() -3; i++) // -3 because of title and wall
	{
		for (int j = 0; j < GetScreenWidth() -2; j++) // -2 because of both walls
		{
			cout << ' ';
		}
		GoToXY(x, ++y);//go to next line
	}

}

/*	Draws the controls on screen.
*	@param x X position on the console to start drawing.
*	@param y Y position on the console to start drawing.
*/
void DrawEngine::DrawInstructions(int x, int y)
{
	GoToXY(x, y);
	cout << "CONTROLS:";
	GoToXY(x, y+2);
	char c = 24; //Up arrow special characters varible.
	cout << c << " or 'W': Move up";
	GoToXY(x, y + 3);
	c = 25; //Down arrow special characters varible.
	cout << c << " or 'S': Move down";
	GoToXY(x, y + 4);
	c = 27;//Left arrow special characters varible.
	cout << c << " or 'A': Move left";
	GoToXY(x, y + 5);
	c = 26;//Right arrow special characters varible.
	cout << c << " or 'D': Move right";
	GoToXY(x, y + 7);
	cout << "R: Restart game";
	GoToXY(x, y + 8);
	cout << "Q: Quit game";
}

/*	Read the highscore from the external file and draw it on screen.
*	@param x X position on the console to start drawing.
*	@param y Y position on the console to start drawing.
*/
void DrawEngine::DrawHighScore(int x, int y)
{
	GoToXY(x,y);
	cout << "High Score: ";
	ifstream myfile (SCORE_FILE);
	string score;

	//open score external file and draws the score on screen.
	while (getline(myfile, score))
	{
		cout << score;
	}
	myfile.close();
}

/*	Initializes the gridMap based on the map size.
*	@param xSize The map length in units.
*	@param ySize The map height in units.
*/
void DrawEngine::CreateGrid(int xSize, int ySize)
{

	xSize += LEFT_BORDER;
	ySize += TOP_BORDER;

	//creates the grid based on the screen size
	gridMap = new char*[xSize];

	for (int i = 0; i < xSize; i++)
	{
		gridMap[i] = new char[ySize];
	}

	for (int i = 0; i < xSize; i++)
	{
		for (int j = 0; j < ySize; j++)
		{
			gridMap[i][j] = ' '; //initiates it as a empty space
		}
	}
}


