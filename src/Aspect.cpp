/*
 * Aspect.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */

#include <Aspect.h>
#include <Entity381.h>  //Aspect includes Entity381.h
#include <DebugDrawer.h>


Aspect::Aspect(Entity381 *ent){
	entity = ent;
}

Aspect::~Aspect(){}

void Aspect::Tick(float dt){

}




Renderable::Renderable(Entity381* ent):Aspect(ent){

}

Renderable::~Renderable(){

}

void Renderable::Tick(float dt){
	if(entity->meshfilename != "robot.mesh"){
		entity->sceneNode->setPosition(entity->position);
	}
}
