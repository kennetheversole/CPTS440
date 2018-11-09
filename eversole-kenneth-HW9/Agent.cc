// Agent.cc


/*==============================================================================
| Author: Kenneth Eversole
| Class: Cpts 440 at Washington State University
| Project HW5
==============================================================================*/
#include <iostream>
#include "Agent.h"

using namespace std;


//Setup the visited and unsafe locations
Agent::Agent ()
{
	knowsGoldLocation = false;


	//track visited location
	for (int i = 0; i<5; i++)
	{
		for (int j = 0; j<5; j++)
		{
			vistedLocations[i][j] = false;
		}
	}
	//track unsafe locations
	for (int i = 0; i<5; i++)
	{
		for (int j = 0; j<5; j++)
		{
			unsafeLocations[i][j] = false;
		}
	}
}



Agent::~Agent ()
{

}

//Initialize the agent
void Agent::Initialize ()
{

	worldState.worldSize = 4; 
	worldState.agentLocation = Location(1,1);
	worldState.agentOrientation = RIGHT;
	worldState.agentHasArrow = true;
	worldState.agentHasGold = false;
	worldState.wumpusAlive = true;

	searchEngine.AddSafeLocation(1,1);
	vistedLocations[worldState.agentLocation.Y][worldState.agentLocation.Y] = true;
	tuple<Location, bool>test = make_tuple(Location(1,1), false);
	known.push_back(test);
}



Action Agent::Process (Percept& percept)
{
	Action action;
	list<Action> actionList2;
	
	//add safe locations
	searchEngine.AddSafeLocation(worldState.agentLocation.X,worldState.agentLocation.Y);
	unsafeLocations[worldState.agentLocation.X][worldState.agentLocation.Y] = false;

	UpdateState(percept);
	if (percept.Glitter)
	{
		actionList.clear();
		actionList.push_front(GRAB);
		worldState.goldLocation.X = worldState.agentLocation.X;
		worldState.goldLocation.Y = worldState.agentLocation.Y;
		knowsGoldLocation = true;
	} 

	if (percept.Scream)
	{
		determineSafe();
		worldState.wumpusAlive = false;
	}


	//find and kill wumpus
	if ((percept.Stench) && (worldState.agentHasArrow)) 
	{
		actionList.clear();  
		

		//Could really make this better by making it look for odds a wumpus will be there
		//killing the wumpus changes our actions
		actionList.push_back(SHOOT);
	}

	
	if (actionList.empty())
	{
		if (worldState.agentHasGold)
		{	
			hasGold:
			// Goto (1,1) and CLIMB
			actionList2 = searchEngine.FindPath(worldState.agentLocation, worldState.agentOrientation, Location(1,1), worldState.agentOrientation);
			actionList.splice(actionList.end(), actionList2);
			actionList.push_back(CLIMB);
		}
		else if (knowsGoldLocation)
		{
			// Goto (1,1) and CLIMB
			actionList2 = searchEngine.FindPath(worldState.agentLocation, worldState.agentOrientation, worldState.goldLocation, worldState.agentOrientation);
			actionList.splice(actionList.end(), actionList2);
			actionList.push_back(GRAB);
		}
		else //randomly go
		{
			actionList.clear();

			actionList.push_back(chooseNextMove());
		}
	}
	perAction:

	action = actionList.front();
	actionList.pop_front();
	ExecuteAction (action);
	return action;
}

//Do an action and update the position of the agent
void Agent::ExecuteAction (Action action)
{
	if (action == GOFORWARD)
	{
		UpdatePosition(GOFORWARD);	
	} else if (action == TURNLEFT) {
		UpdatePosition(TURNLEFT);
	} else if (action == TURNRIGHT) {
		UpdatePosition(TURNRIGHT);
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

bool Agent::consisCheck(list<Location> locList, Location curQPit)
{


	if(breeze.empty())
	{
		return false;
	}

	for(auto& isBreeze: locList) // Iterating over rows
	{
		
	}

}

//When we have to do a random location add some logic to choose 
Action Agent::chooseNextMove()
{

	list< tuple<Location,float> > nextLocProb;  //for their to be a pit


	
	for(auto& query: frontier) // Iterating over rows
	{
		float pitTrue = 0.0;
		float pitFalse = 0.0;
		auto frontierPrime = frontier;
		frontierPrime.remove(query);


		//generate combinations
		
		if(!frontierPrime.empty())
		{
			//Need to look into 
			for(auto& location: frontierPrime) // Iterating over rows
			{
				float probFrontPrime = pow (.2, frontierPrime.size()) *  pow (.8, frontierPrime.size());

				list<Location> test;
				test.push_back(location);
				if(consisCheck(test,query))
				{
					pitTrue = pitTrue + probFrontPrime;
				}
				else
				{
					pitFalse = pitFalse + probFrontPrime;
				}
			}




			pitTrue = pitTrue * .2;
			pitFalse = pitFalse * .8;

			pitTrue = pitTrue/(pitTrue + pitFalse);

			nextLocProb.push_back(make_tuple(query, pitTrue));	
		}
	}


	//Need to look into 
	for(auto& location: nextLocProb) // Iterating over rows
	{
		int test = 0;		
	}
	

	//calculate the probilites
	//go through all probilbilites to see which has the lowest and go there, also check if I can go there




}


void Agent::UpdatePosition(Action action)
{
	// are we turning left?
	if (action == TURNLEFT)
	{
		if (worldState.agentOrientation == UP)
			worldState.agentOrientation = LEFT;
		else if (worldState.agentOrientation == LEFT)
			worldState.agentOrientation = DOWN;
		else if (worldState.agentOrientation == DOWN)
			worldState.agentOrientation = RIGHT;
		else if (worldState.agentOrientation == RIGHT)
			worldState.agentOrientation = UP;
	}

	// are we turning right?
	else if (action == TURNRIGHT)
	{
		if (worldState.agentOrientation == UP)
			worldState.agentOrientation = RIGHT;
		else if (worldState.agentOrientation == RIGHT)
			worldState.agentOrientation = DOWN;
		else if (worldState.agentOrientation == DOWN)
			worldState.agentOrientation = LEFT;
		else if (worldState.agentOrientation == LEFT)
			worldState.agentOrientation = UP;
	}
	// are we going forward?
	else if (action == GOFORWARD)
	{
		if (worldState.agentOrientation == UP)
			worldState.agentLocation.Y++;
		else if (worldState.agentOrientation == LEFT)
			worldState.agentLocation.X--;
		else if (worldState.agentOrientation == DOWN)
			worldState.agentLocation.Y--;
		else if (worldState.agentOrientation == RIGHT)
			worldState.agentLocation.X++;
		vistedLocations[worldState.agentLocation.X][worldState.agentLocation.Y] = true;
	}
} 



//Update the state of the agent
void Agent::UpdateState(Percept& percept)
{

	Location nextLocation;
	searchEngine.AddSafeLocation(worldState.agentLocation.X,worldState.agentLocation.Y);

	if((!percept.Stench || !worldState.wumpusAlive) && !percept.Breeze)
	{
		if(worldState.agentLocation.X > 1)
		{
			bool check_false = (std::find(known.begin(), known.end(), make_tuple(Location(worldState.agentLocation.X-1,worldState.agentLocation.Y), false)) != known.end());
			bool check_true = (std::find(known.begin(), known.end(), make_tuple(Location(worldState.agentLocation.X-1,worldState.agentLocation.Y), true)) != known.end());

			if (!check_false && !check_true)
			{
				frontier.push_back(Location(worldState.agentLocation.X-1,worldState.agentLocation.Y));
			}
		}
		if(worldState.agentLocation.X < 4)
		{
			bool check_false = (std::find(known.begin(), known.end(), make_tuple(Location(worldState.agentLocation.X+1,worldState.agentLocation.Y), false)) != known.end());
			bool check_true = (std::find(known.begin(), known.end(), make_tuple(Location(worldState.agentLocation.X+1,worldState.agentLocation.Y), true)) != known.end());
			
			if (!check_false && !check_true)
			{
				frontier.push_back(Location(worldState.agentLocation.X+1,worldState.agentLocation.Y));
			}
		}
		if(worldState.agentLocation.Y < 4)
		{
			bool check_false = (std::find(known.begin(), known.end(), make_tuple(Location(worldState.agentLocation.X,worldState.agentLocation.Y +1), false)) != known.end());
			bool check_true = (std::find(known.begin(), known.end(), make_tuple(Location(worldState.agentLocation.X,worldState.agentLocation.Y +1), true)) != known.end());

			if (!check_false && !check_true)
			{
				frontier.push_back(Location(worldState.agentLocation.X,worldState.agentLocation.Y +1));
			}
		}
		if(worldState.agentLocation.Y > 1)
		{
			bool check_false = (std::find(known.begin(), known.end(), make_tuple(Location(worldState.agentLocation.X,worldState.agentLocation.Y -1), false)) != known.end());
			bool check_true = (std::find(known.begin(), known.end(), make_tuple(Location(worldState.agentLocation.X,worldState.agentLocation.Y -1), true)) != known.end());
						
			if (!check_false && !check_true)
			{
				frontier.push_back(Location(worldState.agentLocation.X,worldState.agentLocation.Y-1));
			}
		}
	}
	else //update an unsafe location
	{
		if(worldState.agentLocation.X > 1)
		{
			if (!searchEngine.SafeLocation(worldState.agentLocation.X-1,worldState.agentLocation.Y))
			{
				unsafeLocations[worldState.agentLocation.X-1][worldState.agentLocation.Y] = true;								
			}
		}
		if(worldState.agentLocation.X < 4)
		{
			if (!searchEngine.SafeLocation(worldState.agentLocation.X+1,worldState.agentLocation.Y))
			{
				unsafeLocations[worldState.agentLocation.X+1][worldState.agentLocation.Y] = true;				
			}
		}
		if(worldState.agentLocation.Y < 4)
		{
			if (!searchEngine.SafeLocation(worldState.agentLocation.X,worldState.agentLocation.Y + 1))
			{
				unsafeLocations[worldState.agentLocation.X][worldState.agentLocation.Y+1] = true;			
			}
		}
		if(worldState.agentLocation.Y > 1)
		{
			if (!searchEngine.SafeLocation(worldState.agentLocation.X,worldState.agentLocation.Y -1))
			{
				unsafeLocations[worldState.agentLocation.X][worldState.agentLocation.Y-1] = true;
			}
		}
	}

	//update breeze list
	if(percept.Breeze)
	{
		Location newBreeze = Location(worldState.agentLocation.X,worldState.agentLocation.Y);
		breeze.push_back(newBreeze);	
	}
}


void Agent::determineSafe()
{
	if(worldState.agentOrientation == LEFT)
	{
		searchEngine.AddSafeLocation(worldState.agentLocation.X-1,worldState.agentLocation.Y);
		unsafeLocations[worldState.agentLocation.X-1][worldState.agentLocation.Y] = false;
	}
	else if(worldState.agentOrientation == RIGHT)
	{
		searchEngine.AddSafeLocation(worldState.agentLocation.X + 1,worldState.agentLocation.Y);
		unsafeLocations[worldState.agentLocation.X + 1][worldState.agentLocation.Y] = false;
	}
	else if(worldState.agentOrientation == UP)
	{	
		searchEngine.AddSafeLocation(worldState.agentLocation.X,worldState.agentLocation.Y+ 1);
		unsafeLocations[worldState.agentLocation.X][worldState.agentLocation.Y + 1] = false;
	}
	else if(worldState.agentOrientation == DOWN)
	{
		searchEngine.AddSafeLocation(worldState.agentLocation.X-1,worldState.agentLocation.Y -1);
		unsafeLocations[worldState.agentLocation.X][worldState.agentLocation.Y -1 ] = false;	
	}
}