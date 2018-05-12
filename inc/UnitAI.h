/*
 * UnitAI.h
 *
 *  Created on: Mar 28, 2018
 *      Author: sushil
 */

#ifndef UNITAI_H_
#define UNITAI_H_

#include <Aspect.h>
#include <Command.h>
#include <list>

class Command;

class UnitAI: public Aspect {

public:

	std::queue<Command*> commands;
	//std::list<Command*> commands;
	Command* interceptCommand;
	Command* moveToCommand;
	Command* followCommand;

	UnitAI(Entity381* ent);
	~UnitAI();

	void Tick(float dt);
	void SetCommand(Command *c);
	void AddCommand(Command *c);

};





#endif /* UNITAI_H_ */
