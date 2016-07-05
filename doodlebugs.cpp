/*********************************************************************
* Written by: Alex Hildreth
*
* The program simulates a predator/prey relationship between
* doodlebugs and ants in a 20x20 game world. Turns are randomized
* each round, which ends when all Organisms have gone. Each round
* they can move, and reproduce if enough turns have passed. If
* a doodlebug has not eaten in three turns, it dies. This repeats 
* until the user wishes to exit.
*
* Note that the tempArray is no longer necesarry, but was left in 
* place in case needed in the future or for testing purposes.
*
* Input: none
* Output: the game world displayed as a grid of o, X, and .
**********************************************************************/
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include "creatures.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;

//prototype classes
void initializeWorld(Organism* worldArray[20][20], Organism* tempArray[20][20]);
void printWorld(Organism* worldArray[20][20]);
void printStats(Organism* worldArray[20][20]);
void doodlebugTurn(Organism* worldArray[20][20], Organism* tempArray[20][20]);
void antTurn(Organism* worldArray[20][20], Organism* tempArray[20][20]);
void updateArray(Organism* worldArray[20][20], Organism* tempArray[20][20]);
void fillRandomizer(vector<int> &v);
int pickTurn(vector<int> &v);

//main
int main (int argc, char *argv[])
{
	bool escape = false; //to escape the game loop
	int turnRow, turnCol; //holds the grid coordinates for the organism whos turn it is
	
	//game world grid as array of Organism pointers
	Organism* worldArray[20][20];
	Organism* tempArray[20][20];
	
	initializeWorld(worldArray, tempArray);//initializes the world with the organisms
	printWorld(worldArray);//prints the grid
	
	//create a vector of vectors for keeping track of turns
	vector<int> turnRandomizer;
	
	
	
	//game loop
	while(escape == false)
	{
		/*old turn method
		doodlebugTurn(worldArray, tempArray);
		updateArray(worldArray, tempArray);
		antTurn(worldArray, tempArray);
		updateArray(worldArray, tempArray);
		printWorld(worldArray);
		
		cout << endl << "Type 'x' to escape, or hit return to continue" << endl;
		if (cin.get() == 'x'){
			break;}
		*/
	//new turn method with full randomization
		fillRandomizer(turnRandomizer);//resets the random turn vector
		for(int i = 0; i < 400; ++i)
		{
			int turn = pickTurn(turnRandomizer);
			//turnRow = turn / 20; //number over 20 rounded down //no longer necesarry
			//turnCol = turn % 20; //leftover from number over 20
			
			//search through array to find the object whos turn it is
			for(int x = 0; x < 20; ++x)
			{
				for(int y = 0; y < 20; ++y)
				{
					if(worldArray[x][y]->getTurnNum() == turn)
					{
						turnRow = x;
						turnCol = y;
						break;
					}
				}
			}
			
			//call the move function for the object whos turn it is
			worldArray[turnRow][turnCol]->move(worldArray, tempArray, turnRow, turnCol);
			
			//updateArray(worldArray, tempArray);
			//cout << endl << turnRandomizer.size(); //for testing
		}
		printStats(worldArray);//prints the ratio of doodlebugs and ants
		printWorld(worldArray);
		
		//enter x to escape, or just hit return to continue to next round
		cout << endl << "Type 'x' to escape, or hit return to continue" << endl;
		if (cin.get() == 'x')
		{
			break;
		}
	}
	
	return 0;
}


//initializes the game world array with 5 doodlebugs, 100 ants,
//and the rest blank. Puts these in a vector, randomly picks one
//as it iterates through the array, then deletes that vector member.
void initializeWorld(Organism* worldArray[20][20], Organism* tempArray[20][20])
{
	vector<char> v;//stores the organisms
	srand(time(NULL));//random seed
	int randPick;
	int turnNumber = 0;//gives the objects a permanent turn number for randomization purposes
	//fill the vector
	for(int i = 0; i < 5; ++i)
	{
		v.push_back('d');
	}
	for(int i = 0; i < 100; ++i)
	{
		v.push_back('a');
	}
	for(int i = 0; i < 295; ++i)
	{
		v.push_back('x');
	}
	
	//fill game world from vector
	for(int i = 0; i < 20; ++i)
	{
		for(int j = 0; j < 20; ++j)
		{
			randPick = rand() % v.size();
			
			if(v.at(randPick) == 'd')
			{
				worldArray[i][j] = new Doodlebug(turnNumber);
				tempArray[i][j] = worldArray[i][j];
			}
			else if(v.at(randPick) == 'a')
			{
				worldArray[i][j] = new Ant(turnNumber);
				tempArray[i][j] = worldArray[i][j];
			}
			else
			{
				worldArray[i][j] = new Organism();
				tempArray[i][j] = worldArray[i][j];
				worldArray[i][j]->setTurnNum(turnNumber);//need to set the turn number outside of the constructor
			}
			
			v.erase(v.begin()+randPick);//erase that organism from vector
			turnNumber++;//go to next turn number
		}
	}
	
	return;
}


//prints out the current iteration of the world
void printWorld(Organism* worldArray[20][20])
{
	cout << endl << endl;
	
	for(int i = 0; i < 20; ++i)
	{
		for(int j = 0; j < 20; ++j)
		{
			cout << worldArray[i][j]->getChar() << " ";
		}
		
		cout << endl;
	}
	
	return;
}

//fills the turn randomizer 2d vector for each round
void fillRandomizer(vector<int> &v)
{
	for(int i = 0; i < 400; ++i)
	{
		v.push_back(i);
	}
	
	return;
}

//randomly picks a value from the turn vector and returns it
int pickTurn(vector<int> &v)
{
	int turn;
	
	turn = rand() % v.size();
	
	v.erase(v.begin()+turn);//erase that slot from the vector
	
	return turn;
}

//prints out the ratio of doodlebugs to ants
void printStats(Organism* worldArray[20][20])
{
	int antCount = 0;
	int doodleCount = 0;
	float antRat, doodleRat;
	
	for(int i = 0; i < 20; ++i)
	{
		for(int j = 0; j < 20; ++j)
		{
			if(worldArray[i][j]->getChar() == 'o')
			{
				antCount++;
			}
			else if(worldArray[i][j]->getChar() == 'X')
			{
				doodleCount++;
			}
		}
	}
	
	antRat = antCount/doodleCount;
	doodleRat = doodleCount/antCount;
	
	cout << endl << endl << "Ants: " << antCount 
				 << endl << "Doodlebugs: " << doodleCount << endl;
	return;
}

/* No longer necesarry for fully random turns
//doodlebug turn
void doodlebugTurn(Organism* worldArray[20][20], Organism* tempArray[20][20])
{
	for(int i = 0; i < 20; ++i)
	{
		for(int j = 0; j < 20; ++j)
		{
			if(worldArray[i][j]->getChar() == 'X')
			{
				worldArray[i][j]->move(worldArray, tempArray, i, j);
			}
		}
	}
	return;
}

//ant turn
void antTurn(Organism* worldArray[20][20], Organism* tempArray[20][20])
{
	for(int i = 0; i < 20; ++i)
	{
		for(int j = 0; j < 20; ++j)
		{
			if(worldArray[i][j]->getChar() == 'o')
			{
				worldArray[i][j]->move(worldArray, tempArray, i, j);
			}
		}
	}
	return;
}

//update the array with the temp array
void updateArray(Organism* worldArray[20][20], Organism* tempArray[20][20])
{
	for(int i = 0; i < 20; ++i)
	{
		for(int j = 0; j < 20; ++j)
		{
			worldArray[i][j] = tempArray[i][j];
		}
	}
	return;
}

*/


