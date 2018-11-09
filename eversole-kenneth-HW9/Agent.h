// Agent.h

/*==============================================================================
| Author: Kenneth Eversole
| Class: Cpts 440 at Washington State University
| Project HW5
==============================================================================*/

#ifndef AGENT_H
#define AGENT_H

#include "Action.h"
#include "Percept.h"
#include "WorldState.h"
#include "Search.h"
#include <queue>
#include "Location.h"
#include <list>
#include <vector>
#include <map>
#include <math.h>   

class Agent
{
public:
	Agent ();
	~Agent ();
	void Initialize ();
	Action Process (Percept& percept);
	void UpdateState (Percept& percept);
	void ExecuteAction (Action action);
	void GameOver (int score);


	void UpdatePosition(Action action);
	Action chooseNextMove();
	void determineSafe();
	bool consisCheck(list<Location> locList, Location curQPit);


	WorldState worldState;	
	SearchEngine searchEngine;
	list<Action> actionList;
	bool knowsGoldLocation;
	bool vistedLocations[5][5];
	bool unsafeLocations[5][5];
	Location nextMove;
	

	list< tuple<Location,bool> > known; 
	list<Location> frontier;
	list<Location> breeze;

};

#endif // AGENT_H
