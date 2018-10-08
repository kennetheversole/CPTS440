// Agent.cc

#include <iostream>
#include <list>
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
	actionList.clear();


	//init agent 
	agentHasArrow = true;
	agentHasGold = false;
	wumpusAlive = true;
	agentOrientation = LEFT;
	agentLocation.X = 1;
	agentLocation.Y = 1;

}

Action Agent::Process (Percept& percept)
{

	//update the state of the agent
	UpdateState(percept);


	list<Action> actionList2;
	if (actionList.empty()) {

		// Works only for test world (you won't initially know gold location)
		if (!agentHasGold) {


			if(percept.Glitter)
			{
				actionList2 = searchEngine.FindPath(agentLocation, agentOrientation, Location(2,3), RIGHT);
				actionList.splice(actionList.end(), actionList2);
				actionList.push_back(GRAB);
			}
			agentHasGold = true;
		} else {
			// Goto (1,1) and CLIMB
			actionList2 = searchEngine.FindPath(agentLocation, agentOrientation, Location(1,1), RIGHT);
			actionList.splice(actionList.end(), actionList2);
			actionList.push_back(CLIMB);
		}

	}


	//return action to do
	Action action = actionList.front();
	actionList.pop_front();
	return action;
}

void Agent::GameOver (int score)
{
	
}




void Agent::UpdateState(Percept& percept)
{
	//add location to safe location
	searchEngine.AddSafeLocation(agentLocation.X, agentLocation.Y);

	//check the percept
	if ((!percept.Scream || !wumpusAlive) && !percept.Breeze)
	{
		// Adjacent locations are safe
		if (agentLocation.X > 1)
			searchEngine.AddSafeLocation(agentLocation.X - 1, agentLocation.Y);
		if (agentLocation.X < 4)
			searchEngine.AddSafeLocation(agentLocation.X + 1, agentLocation.Y);
		if (agentLocation.Y > 1)
			searchEngine.AddSafeLocation(agentLocation.X, agentLocation.Y - 1);
		if (agentLocation.Y < 4)
			searchEngine.AddSafeLocation(agentLocation.X, agentLocation.Y + 1);
	}
	else
	{
		unsafeLocations.push_back(agentLocation);
	}
	
	
}