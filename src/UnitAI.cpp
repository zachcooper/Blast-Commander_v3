/*
 * UnitAI.cpp

 *
 *  Created on: Apr 3, 2018
 *      Author: mmckissick
 */

#include <UnitAI.h>

UnitAI::UnitAI(Entity381* ent):Aspect(ent)
{
	interceptCommand = NULL;
	moveToCommand = NULL;
	followCommand = NULL;
}

UnitAI::~UnitAI()
{

}

void UnitAI::Tick(float dt)
{
	while(!commands.empty())
	{
		commands.front()->tick(dt);
		if(commands.front()->commandType == intercept)
		{
			interceptCommand = commands.front();
		}
		commands.pop();
	}

	if(interceptCommand != NULL)
	{
		interceptCommand->tick(dt);
	}

	if(moveToCommand != NULL)
	{
		moveToCommand->tick(dt);
	}
	if(followCommand != NULL)
	{
		followCommand->tick(dt);
	}
}

void UnitAI::SetCommand(Command *c)
{
	while(!commands.empty())
	{
		commands.pop();
	}
	interceptCommand = NULL;
	moveToCommand = NULL;
	followCommand = NULL;
	commands.push(c);
}


void UnitAI::AddCommand(Command *c)
{
	commands.push(c);
}



