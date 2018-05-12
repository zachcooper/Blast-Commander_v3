/*
 * Command.cpp
 *
 *  Created on: Apr 3, 2018
 *      Author: mmckissick
 */
#include <Command.h>
#include <iostream>


Command::Command(Entity381* ent, COMMAND_TYPE ct)
{
	entity = ent;
	commandType = ct;

}

Command::~Command()
{

}


void Command::init()
{

}

void Command::tick(float dt)
{

}

bool Command::done()
{
	return true;;
}


MoveTo::MoveTo(Entity381* ent, Ogre::Vector3 location): Command(ent, follow)
{
	entity = ent;
	Ogre::Vector3 diff;
	diff = location - entity->position;
	entity->desiredHeading = atan2(diff.z, diff.x) * 180/3.14;
	entity->desiredSpeed = entity->maxSpeed;
	pos = location;
	MOVE_DISTANCE_THRESHOLD = 10.0;
}

MoveTo::~MoveTo()
{

}

void MoveTo::init()
{

}

void MoveTo::tick(float dt)
{
	done();
}

bool MoveTo::done()
{
	Ogre::Vector3 diff = entity->position - pos;

	if(diff.length() < MOVE_DISTANCE_THRESHOLD)
	{
		entity->desiredSpeed = 0;
		return true;
	}
	return false;
}

Intercept::Intercept(Entity381* ent, Ogre::SceneNode* node): Command(ent, intercept)
{
	entity = ent;
	targetNode = node;
	MOVE_DISTANCE_THRESHOLD = 50.0;
}

Intercept::~Intercept()
{

}

void Intercept::init()
{

}


void Intercept::tick(float dt)
{
	Ogre::Vector3 diff;
	Ogre::Vector3 relVel;
	float t;
	float d;
	float r;

	d = diff.distance(targetNode->getPosition() - entity->position);
	diff = targetNode->getPosition() - entity->position;
	r = relVel.distance(targetNode->getPosition() - entity->velocity);
	entity->desiredSpeed = entity->maxSpeed;
	t = d/r;
	targetLocation = targetNode->getPosition();// + targetEntity->velocity * t;
	diff = targetLocation - entity->position;
	entity->desiredHeading = atan2(diff.z, diff.x) * 180/3.141578;

}

bool Intercept::done()
{
	return true;
}

Follow::Follow(Entity381* ent, Ogre::SceneNode* node): Command(ent, follow)
{
	entity = ent;
	targetNode = node;
	MOVE_DISTANCE_THRESHOLD = 20.0;
}
Follow::~Follow()
{

}

void Follow::init()
{

}

void Follow::tick(float dt)
{
	/*
	Ogre::Vector3 diff;
	Ogre::Vector3 relVel;

	diff = targetNode->getPosition() - entity->position;
	entity->desiredHeading = atan2(diff.z, diff.x) * 180/3.14;
	entity->desiredSpeed = entity->maxSpeed;

	*/
	Ogre::Vector3 diff;
	Ogre::Vector3 relVel;
	float t;
	float d;
	float r;

	d = diff.distance(targetNode->getPosition() - entity->position);
	diff = targetNode->getPosition() - entity->position;
	r = relVel.distance(targetNode->getPosition() - entity->velocity);
	entity->desiredSpeed = entity->maxSpeed;
	t = d/r;
	targetLocation = targetNode->getPosition();// + targetEntity->velocity * t;
	diff = targetLocation - entity->position;
	entity->desiredHeading = atan2(diff.z, diff.x) * 180/3.141578;

}

bool Follow::done()
{
	return true;
}






