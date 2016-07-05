//implimentation of the creature class and child classes
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include "creatures.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;

//default constructor to fill slots not occupied by ant or doodlebug
Organism::Organism()
{
	this->charDisp = '.';
	this->turns = 0;
	//this->turnNum = turnNumber; //fill this separately using setTurnNum(int)
}

//alters the number of turns variable
void Organism::increaseTurns()
{
	turns++;
	return;
}

void Organism::resetTurns() //resets turns to zero
{
	this->turns = 0;
}

//returns turns
int Organism::getTurns()
{
	return turns;
}

//returns the character to display in the world grid
char Organism::getChar()
{
	return charDisp;
}

//does nothing for base class
void Organism::move(Organism* worldArray[20][20], Organism* tempArray[20][20], int i, int j)
{
	return;
}

//does nothing for base class
void Organism::reproduce(Organism* worldArray[20][20], Organism* tempArray[20][20], int i, int j)
{
	return;
}

//does nothing for base class
void Organism::resetTurnsEat()
{
	return;
}

//does nothing for base class
void Organism::starve(Organism* worldArray[20][20], Organism* tempArray[20][20], int i, int j)
{
	return;
}

//does nothing for base class
void Organism::increaseTurnsEat()
{
	return;
}

//does nothing for base class
int Organism::getTurnsEat()
{
	return 0;
}

//sets the turn nubmer identifier
void Organism::setTurnNum(int theNum)
{
	this->turnNum = theNum;
	return;
}

//returns the turn number identifier
int Organism::getTurnNum()
{
	return turnNum;
}
//////////////////////////////////////////////////////////////////////

//ant default constructor for new ants
Ant::Ant(int turnNumber)
{
	this->charDisp = 'o';
	this->turns = 0;
	this->turnNum = turnNumber;
}

//ant constructor with turns
/*
Ant::Ant(int newTurns)
{
	this->charDisp = 'o';
	this->turns = newTurns;
}
*/

//doodlebug default constructor for new doodlebugs
Doodlebug::Doodlebug(int turnNumber)
{
	this->charDisp = 'X';
	this->turns = 0;
	this->turnsEat = 0;
	this->turnNum = turnNumber;
}

//doodlebug constructor with turns
/*
Doodlebug::Doodlebug(int newTurns, int newTurnsEat)
{
	this->charDisp = 'X';
	this->turns = newTurns;
	this->turnsEat = newTurnsEat;
}
*/

//returns the turns since eat variable
int Doodlebug::getTurnsEat()
{
	return turnsEat;
}

//increases turns since eating
void Doodlebug::increaseTurnsEat()
{
	this->turnsEat++;
	return;
}

void Doodlebug::resetTurnsEat() //resets turns since eating to zero
{
	this->turnsEat = 0;
}

//ant move function
void Ant::move(Organism* worldArray[20][20], Organism* tempArray[20][20], int i, int j)
{
	//srand(time(NULL));
	int randPick, tempTurns;
	
	//after ant moves, holds new coordinates for passing to next function
	int newi = i;
	int newj = j;
	
	//used for moving organisms
	Organism* tempPtr;
	
	//random move direction
	randPick = rand() % 4 + 1;
	
	//increase the turns since reproduction
	worldArray[i][j]->increaseTurns();
	
	//try to move left
	if(randPick == 1 && j > 0)
	{
		if(worldArray[i][j-1]->getChar() == '.')
		{
			tempPtr = worldArray[i][j-1];
			worldArray[i][j-1] = worldArray[i][j]; //swap pointer values
			worldArray[i][j] = tempPtr;
			newj--; //set new j coordinate for passing later
		}
	}
	//try to move up
	else if(randPick == 2 && i > 0) 
	{
		if(worldArray[i-1][j]->getChar() == '.')
		{
			tempPtr = worldArray[i-1][j];
			worldArray[i-1][j] = worldArray[i][j];
			worldArray[i][j] = tempPtr;
			newi--;
		}
	}
	//try to move right
	else if(randPick == 3 && j < 19)
	{
		if(worldArray[i][j+1]->getChar() == '.')
		{
			tempPtr = worldArray[i][j+1];
			worldArray[i][j+1] = worldArray[i][j];
			worldArray[i][j] = tempPtr;
			newj++;
		}
	}
	//try to move down
	else if(randPick == 4 && i < 19)
	{
		if(worldArray[i+1][j]->getChar() == '.')
		{
			tempPtr = worldArray[i+1][j];
			worldArray[i+1][j] = worldArray[i][j];
			worldArray[i][j] = tempPtr;
			newi++;
		}
	}
	
	//reproduce
	worldArray[newi][newj]->reproduce(worldArray, tempArray, newi, newj);
	
	//reset turns after reproducing
	if(worldArray[newi][newj]->getTurns() == 3)
	{
		worldArray[newi][newj]->resetTurns();
	}
	
	return;
}

//ant reproduction function. Attemps to create a new ant in an empty space around the parent ant
void Ant::reproduce(Organism* worldArray[20][20], Organism* tempArray[20][20], int i, int j)
{
	int theTurn; //holds turn number from deleted base organism to give to new ant
	
	if(worldArray[i][j]->getTurns() != 3) //return if not after 3 turns
	{
		return;
	}
	else if(worldArray[i][j]->getTurns() == 3)
	{
		//srand(time(NULL));
		int randPick = rand() % 4 + 1;
		
		//within game grid interior, not on edge
		if(0 < i && i < 19 && 0 < j && j < 19)
		{
			if(worldArray[i+1][j]->getChar() == '.')
			{
				theTurn = worldArray[i+1][j]->getTurnNum(); //gets turn identifier to pass to new ant
				delete worldArray[i+1][j]; //deletes the base class
				worldArray[i+1][j] = new Ant(theTurn); //creates new ant with same turn identifier
			}
			else if(worldArray[i][j+1]->getChar() == '.')
			{
				theTurn = worldArray[i][j+1]->getTurnNum();
				delete worldArray[i][j+1];
				worldArray[i][j+1] = new Ant(theTurn);
			}
			else if(worldArray[i-1][j]->getChar() == '.')
			{
				theTurn = worldArray[i-1][j]->getTurnNum();
				delete worldArray[i-1][j];
				worldArray[i-1][j] = new Ant(theTurn);
			}
			else if(worldArray[i][j-1]->getChar() == '.')
			{
				theTurn = worldArray[i][j-1]->getTurnNum();
				delete worldArray[i][j-1];
				worldArray[i][j-1] = new Ant(theTurn);
			}
			else
			{
				return;
			}
		}
		
		//edges
		else if(0 < i && i < 19 && (j == 0 || j == 19))
		{
			//left edge
			if(j == 0)
			{
				if(worldArray[i+1][j]->getChar() == '.')
				{
					theTurn = worldArray[i+1][j]->getTurnNum();
					delete worldArray[i+1][j];
					worldArray[i+1][j] = new Ant(theTurn);
				}
				else if(worldArray[i][j+1]->getChar() == '.')
				{
					theTurn = worldArray[i][j+1]->getTurnNum();
					delete worldArray[i][j+1];
					worldArray[i][j+1] = new Ant(theTurn);
				}
				else if(worldArray[i-1][j]->getChar() == '.')
				{
					theTurn = worldArray[i-1][j]->getTurnNum();
					delete worldArray[i-1][j];
					worldArray[i-1][j] = new Ant(theTurn);
				}
				else
				{
					return;
				}
			}
			//right edge
			else if(j == 19)
			{
				if(worldArray[i+1][j]->getChar() == '.')
				{
					theTurn = worldArray[i+1][j]->getTurnNum();
					delete worldArray[i+1][j];
					worldArray[i+1][j] = new Ant(theTurn);
				}
				else if(worldArray[i][j-1]->getChar() == '.')
				{
					theTurn = worldArray[i][j-1]->getTurnNum();
					delete worldArray[i][j-1];
					worldArray[i][j-1] = new Ant(theTurn);
				}
				else if(worldArray[i-1][j]->getChar() == '.')
				{
					theTurn = worldArray[i-1][j]->getTurnNum();
					delete worldArray[i-1][j];
					worldArray[i-1][j] = new Ant(theTurn);
				}
				else
				{
					return;
				}
			}
		}
		else if((i == 0 || i == 19) && 0 < j && j < 19)
		{
			//top edge
			if(i == 0)
			{
				if(worldArray[i+1][j]->getChar() == '.')
				{
					theTurn = worldArray[i+1][j]->getTurnNum();
					delete worldArray[i+1][j];
					worldArray[i+1][j] = new Ant(theTurn);
				}
				else if(worldArray[i][j+1]->getChar() == '.')
				{
					theTurn = worldArray[i][j+1]->getTurnNum();
					delete worldArray[i][j+1];
					worldArray[i][j+1] = new Ant(theTurn);
				}
				else if(worldArray[i][j-1]->getChar() == '.')
				{
					theTurn = worldArray[i][j-1]->getTurnNum();
					delete worldArray[i][j-1];
					worldArray[i][j-1] = new Ant(theTurn);
				}
				else
				{
					return;
				}
			}
			//bottom edge
			else if(i == 19)
			{
				if(worldArray[i][j+1]->getChar() == '.')
				{
					theTurn = worldArray[i][j+1]->getTurnNum();
					delete worldArray[i][j+1];
					worldArray[i][j+1] = new Ant(theTurn);
				}
				else if(worldArray[i][j-1]->getChar() == '.')
				{
					theTurn = worldArray[i][j-1]->getTurnNum();
					delete worldArray[i][j-1];
					worldArray[i][j-1] = new Ant(theTurn);
				}
				else if(worldArray[i-1][j]->getChar() == '.')
				{
					theTurn = worldArray[i-1][j]->getTurnNum();
					delete worldArray[i-1][j];
					worldArray[i-1][j] = new Ant(theTurn);
				}
				else
				{
					return;
				}
			}
		}
		//top left corner
		else if(i == 0 && j == 0)
		{
			if(worldArray[i][j+1]->getChar() == '.')
				{
					theTurn = worldArray[i][j+1]->getTurnNum();
					delete worldArray[i][j+1];
					worldArray[i][j+1] = new Ant(theTurn);
				}
			else if(worldArray[i+1][j]->getChar() == '.')
				{
					theTurn = worldArray[i+1][j]->getTurnNum();
					delete worldArray[i+1][j];
					worldArray[i+1][j] = new Ant(theTurn);
				}
			else
				{
					return;
				}
		}
		//bottom left corner
		else if(i == 19 && j == 0)
		{
			if(worldArray[i][j+1]->getChar() == '.')
				{
					theTurn = worldArray[i][j+1]->getTurnNum();
					delete worldArray[i][j+1];
					worldArray[i][j+1] = new Ant(theTurn);
				}
			else if(worldArray[i-1][j]->getChar() == '.')
				{
					theTurn = worldArray[i-1][j]->getTurnNum();
					delete worldArray[i-1][j];
					worldArray[i-1][j] = new Ant(theTurn);
				}
			else
				{
					return;
				}
		}
		//top right corner
		else if(i == 0 && j == 19)
		{
			if(worldArray[i][j-1]->getChar() == '.')
				{
					theTurn = worldArray[i][j-1]->getTurnNum();
					delete worldArray[i][j-1];
					worldArray[i][j-1] = new Ant(theTurn);
				}
			else if(worldArray[i+1][j]->getChar() == '.')
				{
					theTurn = worldArray[i+1][j]->getTurnNum();
					delete worldArray[i+1][j];
					worldArray[i+1][j] = new Ant(theTurn);
				}
			else
				{
					return;
				}
		}
		//bottom right corner
		else if(i == 19 && j == 19)
		{
			if(worldArray[i][j-1]->getChar() == '.')
				{
					theTurn = worldArray[i][j-1]->getTurnNum();
					delete worldArray[i][j-1];
					worldArray[i][j-1] = new Ant(theTurn);
				}
			else if(worldArray[i-1][j]->getChar() == '.')
				{
					theTurn = worldArray[i-1][j]->getTurnNum();
					delete worldArray[i-1][j];
					worldArray[i-1][j] = new Ant(theTurn);
				}
			else
				{
					return;
				}
		}
	}
	return;
}

//doodlebug move function. same principles as ant move function.
void Doodlebug::move(Organism* worldArray[20][20], Organism* tempArray[20][20], int i, int j)
{
	//srand(time(NULL));
	int randPick, tempTurns, tempTurnsEat;
	int newi = i;
	int newj = j;
	int theTurn;
	
	Organism* tempPtr;
	
	randPick = rand() % 4 + 1;
	
	worldArray[i][j]->increaseTurns();
	worldArray[i][j]->increaseTurnsEat(); //increase turns since eating
	
	//try to move left
	if(randPick == 1 && j > 0)
	{
		if(worldArray[i][j-1]->getChar() == '.' || worldArray[i][j-1]->getChar() == 'o')
		{
			tempPtr = worldArray[i][j-1];
			worldArray[i][j-1] = worldArray[i][j];
			worldArray[i][j] = tempPtr;
			newj--;
			
			//if "eats" an ant
			if(worldArray[i][j]->getChar() == 'o') 
			{
				worldArray[i][j-1]->resetTurnsEat(); //reset turns since eating
				theTurn = worldArray[i][j]->getTurnNum(); //gets turn identifier to pass to new base organism
				delete worldArray[i][j];
				worldArray[i][j] = new Organism();
				worldArray[i][j]->setTurnNum(theTurn); //pass turn identifier to new organism
			}
			
			//reproduce
			worldArray[i][j-1]->reproduce(worldArray, tempArray, newi, newj);
	
			//starve
			worldArray[i][j-1]->starve(worldArray, tempArray, newi, newj);
		}
		else
		{	
			//reproduce
			worldArray[i][j]->reproduce(worldArray, tempArray, newi, newj);
	
			//starve
			worldArray[i][j]->starve(worldArray, tempArray, newi, newj);
		}
	}
	//try to move up
	else if(randPick == 2 && i > 0)
	{
		if(worldArray[i-1][j]->getChar() == '.' || worldArray[i-1][j]->getChar() == 'o')
		{
			tempPtr = worldArray[i-1][j];
			worldArray[i-1][j] = worldArray[i][j];
			worldArray[i][j] = tempPtr;
			newi--;
			
			if(worldArray[i][j]->getChar() == 'o')
			{
				worldArray[i-1][j]->resetTurnsEat();
				theTurn = worldArray[i][j]->getTurnNum();
				delete worldArray[i][j];
				worldArray[i][j] = new Organism();
				worldArray[i][j]->setTurnNum(theTurn);
			}
			
			//reproduce
			worldArray[i-1][j]->reproduce(worldArray, tempArray, newi, newj);
	
			//starve
			worldArray[i-1][j]->starve(worldArray, tempArray, newi, newj);
		}
		else
		{	
			//reproduce
			worldArray[i][j]->reproduce(worldArray, tempArray, newi, newj);
	
			//starve
			worldArray[i][j]->starve(worldArray, tempArray, newi, newj);
		}
	}
	//try to move right
	else if(randPick == 3 && j < 19)
	{
		if(worldArray[i][j+1]->getChar() == '.' || worldArray[i][j+1]->getChar() == 'o')
		{
			if(worldArray[i][j+1]->getChar() == '.' || worldArray[i][j+1]->getChar() == 'o')
			{
				tempPtr = worldArray[i][j+1];
				worldArray[i][j+1] = worldArray[i][j];
				worldArray[i][j] = tempPtr;
				newj++;
			
				if(worldArray[i][j]->getChar() == 'o')
				{
					worldArray[i][j+1]->resetTurnsEat();
					theTurn = worldArray[i][j]->getTurnNum();
					delete worldArray[i][j];
					worldArray[i][j] = new Organism();
					worldArray[i][j]->setTurnNum(theTurn);
				}
			
				//reproduce
				worldArray[i][j+1]->reproduce(worldArray, tempArray, newi, newj);
	
				//starve
				worldArray[i][j+1]->starve(worldArray, tempArray, newi, newj);
			}
			else
			{	
				//reproduce
				worldArray[i][j]->reproduce(worldArray, tempArray, newi, newj);
	
				//starve
				worldArray[i][j]->starve(worldArray, tempArray, newi, newj);
			}
		}
	}
	//try to move down
	else if(randPick == 4 && i < 19) 
	{
		if(worldArray[i+1][j]->getChar() == '.' || worldArray[i+1][j]->getChar() == 'o')
		{
			tempPtr = worldArray[i+1][j];
			worldArray[i+1][j] = worldArray[i][j];
			worldArray[i][j] = tempPtr;
			newi++;
			
			if(worldArray[i][j]->getChar() == 'o')
			{
				worldArray[i+1][j]->resetTurnsEat();
				theTurn = worldArray[i][j]->getTurnNum();
				delete worldArray[i][j];
				worldArray[i][j] = new Organism();
				worldArray[i][j]->setTurnNum(theTurn);
			}
			
			//reproduce
			worldArray[i+1][j]->reproduce(worldArray, tempArray, newi, newj);
	
			//starve
			worldArray[i+1][j]->starve(worldArray, tempArray, newi, newj);
		}
		else
		{	
			//reproduce
			worldArray[i][j]->reproduce(worldArray, tempArray, newi, newj);
	
			//starve
			worldArray[i][j]->starve(worldArray, tempArray, newi, newj);
		}
	}
	
	return;
}

//doodlebug reproduction every 8 turns. Same principle as ant reproduction.
void Doodlebug::reproduce(Organism* worldArray[20][20], Organism* tempArray[20][20], int i, int j)
{
	int theTurn;
	
	if(worldArray[i][j]->getTurns() != 8)
	{
		return;
	}
	else if(worldArray[i][j]->getTurns() == 8)
	{
		//srand(time(NULL));
		int randPick = rand() % 4 + 1;
		
		//interior, not on edges
		if(0 < i && i < 19 && 0 < j && j < 19)
		{
			if(worldArray[i+1][j]->getChar() == '.' || worldArray[i+1][j]->getChar() == 'o')
			{
				theTurn = worldArray[i+1][j]->getTurnNum();
				delete worldArray[i+1][j];
				worldArray[i+1][j] = new Doodlebug(theTurn);
			}
			else if(worldArray[i][j+1]->getChar() == '.' || worldArray[i+1][j]->getChar() == 'o')
			{
				theTurn = worldArray[i][j+1]->getTurnNum();
				delete worldArray[i][j+1];
				worldArray[i][j+1] = new Doodlebug(theTurn);
			}
			else if(worldArray[i-1][j]->getChar() == '.' || worldArray[i+1][j]->getChar() == 'o')
			{
				theTurn = worldArray[i-1][j]->getTurnNum();
				delete worldArray[i-1][j];
				worldArray[i-1][j] = new Doodlebug(theTurn);
			}
			else if(worldArray[i][j-1]->getChar() == '.' || worldArray[i+1][j]->getChar() == 'o')
			{
				theTurn = worldArray[i][j-1]->getTurnNum();
				delete worldArray[i][j-1];
				worldArray[i][j-1] = new Doodlebug(theTurn);
			}
			else
			{
				return;
			}
		}
		
		//edges
		else if(0 < i && i < 19 && (j == 0 || j == 19))
		{
			//left edge
			if(j == 0)
			{
				if(worldArray[i+1][j]->getChar() == '.' || worldArray[i+1][j]->getChar() == 'o')
				{
					theTurn = worldArray[i+1][j]->getTurnNum();
					delete worldArray[i+1][j];
					worldArray[i+1][j] = new Doodlebug(theTurn);
				}
				else if(worldArray[i][j+1]->getChar() == '.' || worldArray[i+1][j]->getChar() == 'o')
				{
					theTurn = worldArray[i][j+1]->getTurnNum();
					delete worldArray[i][j+1];
					worldArray[i][j+1] = new Doodlebug(theTurn);
				}
				else if(worldArray[i-1][j]->getChar() == '.' || worldArray[i+1][j]->getChar() == 'o')
				{
					theTurn = worldArray[i-1][j]->getTurnNum();
					delete worldArray[i-1][j];
					worldArray[i-1][j] = new Doodlebug(theTurn);
				}
				else
				{
					return;
				}
			}
			//right edge
			else if(j == 19)
			{
				if(worldArray[i+1][j]->getChar() == '.' || worldArray[i+1][j]->getChar() == 'o')
				{
					theTurn = worldArray[i+1][j]->getTurnNum();
					delete worldArray[i+1][j];
					worldArray[i+1][j] = new Doodlebug(theTurn);
				}
				else if(worldArray[i][j-1]->getChar() == '.' || worldArray[i+1][j]->getChar() == 'o')
				{
					theTurn = worldArray[i][j-1]->getTurnNum();
					delete worldArray[i][j-1];
					worldArray[i][j-1] = new Doodlebug(theTurn);
				}
				else if(worldArray[i-1][j]->getChar() == '.' || worldArray[i+1][j]->getChar() == 'o')
				{
					theTurn = worldArray[i-1][j]->getTurnNum();
					delete worldArray[i-1][j];
					worldArray[i-1][j] = new Doodlebug(theTurn);
				}
				else
				{
					return;
				}
			}
		}
		else if((i == 0 || i == 19) && 0 < j && j < 19)
		{
			//top edge
			if(i == 0)
			{
				if(worldArray[i+1][j]->getChar() == '.' || worldArray[i+1][j]->getChar() == 'o')
				{
					theTurn = worldArray[i+1][j]->getTurnNum();
					delete worldArray[i+1][j];
					worldArray[i+1][j] = new Doodlebug(theTurn);
				}
				else if(worldArray[i][j+1]->getChar() == '.' || worldArray[i+1][j]->getChar() == 'o')
				{
					theTurn = worldArray[i][j+1]->getTurnNum();
					delete worldArray[i][j+1];
					worldArray[i][j+1] = new Doodlebug(theTurn);
				}
				else if(worldArray[i][j-1]->getChar() == '.' || worldArray[i+1][j]->getChar() == 'o')
				{
					theTurn = worldArray[i][j-1]->getTurnNum();
					delete worldArray[i][j-1];
					worldArray[i][j-1] = new Doodlebug(theTurn);
				}
				else
				{
					return;
				}
			}
			//bottom edge
			else if(i == 19)
			{
				if(worldArray[i][j+1]->getChar() == '.' || worldArray[i+1][j]->getChar() == 'o')
				{
					theTurn = worldArray[i][j+1]->getTurnNum();
					delete worldArray[i][j+1];
					worldArray[i][j+1] = new Doodlebug(theTurn);
				}
				else if(worldArray[i][j-1]->getChar() == '.' || worldArray[i+1][j]->getChar() == 'o')
				{
					theTurn = worldArray[i][j-1]->getTurnNum();
					delete worldArray[i][j-1];
					worldArray[i][j-1] = new Doodlebug(theTurn);
				}
				else if(worldArray[i-1][j]->getChar() == '.' || worldArray[i+1][j]->getChar() == 'o')
				{
					theTurn = worldArray[i-1][j]->getTurnNum();
					delete worldArray[i-1][j];
					worldArray[i-1][j] = new Doodlebug(theTurn);
				}
				else
				{
					return;
				}
			}
		}
		//top left corner
		else if(i == 0 && j == 0)
		{
			if(worldArray[i][j+1]->getChar() == '.' || worldArray[i+1][j]->getChar() == 'o')
				{
					theTurn = worldArray[i][j+1]->getTurnNum();
					delete worldArray[i][j+1];
					worldArray[i][j+1] = new Doodlebug(theTurn);
				}
			else if(worldArray[i+1][j]->getChar() == '.' || worldArray[i+1][j]->getChar() == 'o')
				{
					theTurn = worldArray[i+1][j]->getTurnNum();
					delete worldArray[i+1][j];
					worldArray[i+1][j] = new Doodlebug(theTurn);
				}
		}
		//bottom left corner
		else if(i == 19 && j == 0)
		{
			if(worldArray[i][j+1]->getChar() == '.' || worldArray[i+1][j]->getChar() == 'o')
				{
					theTurn = worldArray[i][j+1]->getTurnNum();
					delete worldArray[i][j+1];
					worldArray[i][j+1] = new Doodlebug(theTurn);
				}
			else if(worldArray[i-1][j]->getChar() == '.' || worldArray[i+1][j]->getChar() == 'o')
				{
					theTurn = worldArray[i-1][j]->getTurnNum();
					delete worldArray[i-1][j];
					worldArray[i-1][j] = new Doodlebug(theTurn);
				}
		}
		//top right corner
		else if(i == 0 && j == 19)
		{
			if(worldArray[i][j-1]->getChar() == '.' || worldArray[i+1][j]->getChar() == 'o')
				{
					theTurn = worldArray[i][j-1]->getTurnNum();
					delete worldArray[i][j-1];
					worldArray[i][j-1] = new Doodlebug(theTurn);
				}
			else if(worldArray[i+1][j]->getChar() == '.' || worldArray[i+1][j]->getChar() == 'o')
				{
					theTurn = worldArray[i+1][j]->getTurnNum();
					delete worldArray[i+1][j];
					worldArray[i+1][j] = new Doodlebug(theTurn);
				}
		}
		//bottom right corner
		else if(i == 19 && j == 19)
		{
			if(worldArray[i][j-1]->getChar() == '.' || worldArray[i+1][j]->getChar() == 'o')
				{
					theTurn = worldArray[i][j-1]->getTurnNum();
					delete worldArray[i][j-1];
					worldArray[i][j-1] = new Doodlebug(theTurn);
				}
			else if(worldArray[i-1][j]->getChar() == '.' || worldArray[i+1][j]->getChar() == 'o')
				{
					theTurn = worldArray[i-1][j]->getTurnNum();
					delete worldArray[i-1][j];
					worldArray[i-1][j] = new Doodlebug(theTurn);
				}
		}
	}
	
	//reset the turns since eating counter
	worldArray[i][j]->resetTurns();
	return;
}

//if not eaten in three turns, replaces the doodlebug in the temp array with blank organism to kill it
void Doodlebug::starve(Organism* worldArray[20][20], Organism* tempArray[20][20], int i, int j)
{
	int theTurn;
	
	if(worldArray[i][j]->getTurnsEat() != 3)
	{
		return;
	}
	else if(worldArray[i][j]->getTurnsEat() >= 3)
	{
		theTurn = worldArray[i][j]->getTurnNum();
		delete worldArray[i][j];
		worldArray[i][j] = new Organism();
		worldArray[i][j]->setTurnNum(theTurn);
	}
	
	return;
}