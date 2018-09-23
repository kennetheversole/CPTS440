// Agent.cc


/*==============================================================================
| Author: Kenneth Eversole
| Class: Cpts 440 at Washington State University
==============================================================================*/
#include <iostream>
#include "Agent.h"

using namespace std;

Agent::Agent ()
{
}

Agent::~Agent ()
{

}

void Agent::Initialize ()
{
	worldState.worldSize = 4; // Given in HW2 problem definition
	worldState.agentLocation = Location(1,1);
	worldState.agentOrientation = RIGHT;
	worldState.agentHasArrow = true;
	worldState.agentHasGold = false;
	worldState.wumpusAlive = true;

	//setup the boolen array
	for (int x = 1; x <= 4; x++)
	{
		for (int y = 1; y <= 4; y++)
		{
			visitedLocations[x][y] = false;
		}
	}
	visitedLocations[1][1] = true;
}


Action Agent::Process (Percept& percept)
{
	Action action;
	if (percept.Glitter)
	{
		actions.push_back(GRAB);//we should just grab the gold
	} else if ((percept.Stench) && (worldState.agentHasArrow)) {
		
		actions.clear();  //killing the wumpus changes our actions
		actions.push_back(SHOOT);
	}
	if (actions.empty())
	{
		if(!percept.Bump)
		{
			actions.push_back(GOFORWARD);
		}
		else
		{
			actions.push_back(TURNLEFT);
		}
		
	}
	action = actions.front();
	actions.pop_front();
	ExecuteAction (action);
	return action;

	
}


void Agent::ExecuteAction (Action action)
{
	if (action == GOFORWARD)
	{
		visitedLocations[worldState.agentLocation.X][worldState.agentLocation.Y] = true;
	} else if (action == TURNLEFT) {
		//change postions//
	} else if (action == TURNRIGHT) {
		//change postions
	} else if (action == GRAB) {
		worldState.agentHasGold = true;
	} else if (action == SHOOT) {
		worldState.agentHasArrow = false;
	} else if (action == CLIMB) {
		//leave game
	}
}


void Agent::GameOver (int score)
{

}

