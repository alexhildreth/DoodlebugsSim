//header file for Organism class and its children
//see creatures.cpp for implimentation
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

//base creature class
class Organism
{
	public:
		Organism(); //default constructor*******************************************
		virtual void move(Organism* worldArray[20][20], Organism* tempArray[20][20], int i, int j); //moves the creature according to child class
		virtual void reproduce(Organism* worldArray[20][20], Organism* tempArray[20][20], int i, int j); //called from move(). checks turns 
		virtual void resetTurnsEat(); //resets the turns since eating counter
		virtual int getTurnsEat(); //returns the turns since eating
		virtual void starve(Organism* worldArray[20][20], Organism* tempArray[20][20], int i, int j); //if over 3 turns, kills the doodlebug
		virtual void increaseTurnsEat(); //increases the turns since eating counter
		void increaseTurns(); //alter the turns variable plus one
		void resetTurns(); //resets turns to zero
		void setTurnNum(int theNum); //sets the turn number
		int getTurns(); //returns turns
		int getTurnNum(); //returns turn number
		char getChar(); //returns the char to display in the printed out world grid
		
	protected:
		char charDisp; //the character representing the organism
		int turns; //turns since reproducing
		int turnNum; //used for turn randomization. assigned a unique number identifier
		
};

//ant subclass
class Ant : public Organism
{
	public:
		Ant(int turnNumber); //default constructor for new ants*********************************************
		//Ant(int turns); //constructor for ant after moving in order to retain number of turns
		void move(Organism* worldArray[20][20], Organism* tempArray[20][20], int i, int j);
		void reproduce(Organism* worldArray[20][20], Organism* tempArray[20][20], int i, int j);
};

class Doodlebug : public Organism
{
	public:
		Doodlebug(int turnNumber);//***************************************************************************
		//Doodlebug(int newTurns, int newTurnsEat);
		void move(Organism* worldArray[20][20], Organism* tempArray[20][20], int i, int j);
		void reproduce(Organism* worldArray[20][20], Organism* tempArray[20][20], int i, int j);
		void starve(Organism* worldArray[20][20], Organism* tempArray[20][20], int i, int j);
		void increaseTurnsEat();
		void resetTurnsEat();
		int getTurnsEat(); //returns the turns since eating
	
	private:
		int turnsEat; //variable storing turns since eating
};