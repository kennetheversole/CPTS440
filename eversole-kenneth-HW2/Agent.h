// Agent.h


/*==============================================================================
| Author: Kenneth Eversole
| Class: Cpts 440 at Washington State University
==============================================================================*/

#ifndef AGENT_H
#define AGENT_H

#include "Action.h"
#include "Percept.h"
#include "WorldState.h"
#include <list>

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

	WorldState worldState;	
	bool visitedLocations[5][5];//I need to figure out how to use this in the future. 
	list<Action> actions;
};

#endif // AGENT_H
