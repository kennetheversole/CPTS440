// Agent.h

#ifndef AGENT_H
#define AGENT_H

#include "Action.h"
#include "Percept.h"

#include "Location.h"
#include "Orientation.h"
#include "WorldState.h"
#include "Search.h"
#include <list>

class Agent
{
public:
	Agent ();
	~Agent ();
	void Initialize ();
	Action Process (Percept& percept);
	void GameOver (int score);
	void UpdateState(Percept& percept);



	SearchEngine searchEngine;


	//agent knowledge
	bool agentHasGold;
	bool agentHasArrow;
	bool wumpusAlive;

	
	Location agentLocation;
	Orientation agentOrientation;
	list<Action> actionList;
	list<Location> unsafeLocations;
};

#endif // AGENT_H
